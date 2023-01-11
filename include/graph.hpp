#ifndef GRAPH_PROTOTYPE_GRAPH_HPP
#define GRAPH_PROTOTYPE_GRAPH_HPP

#include "buffer.hpp"
#include "circular_buffer.hpp"
#ifndef GRAPH_PROTOTYPE_TYPELIST_HPP
#include "typelist.hpp"
#endif

#include "vir/simd.h"

#include <iostream>
#include <ranges>
#include <tuple>
#include <variant>
#include <complex>
#include <map>

#if !__has_include(<source_location>)
#define HAVE_SOURCE_LOCATION 0
#else
#include <source_location>
#if defined __cpp_lib_source_location && __cpp_lib_source_location >= 201907L
#define HAVE_SOURCE_LOCATION 1
#else
#define HAVE_SOURCE_LOCATION 0
#endif
#endif

namespace fair::graph {

namespace stdx = vir::stdx;

namespace detail {
template <class... T>
constexpr bool always_false = false;
}

using fair::meta::fixed_string;

namespace detail {
#if HAVE_SOURCE_LOCATION
    [[gnu::always_inline]] inline void
    precondition(bool cond, const std::source_location loc = std::source_location::current()) {
        struct handle {
            [[noreturn]] static void
            failure(std::source_location const &loc) {
                std::clog << "failed precondition in " << loc.file_name() << ':' << loc.line() << ':'
                          << loc.column() << ": `" << loc.function_name() << "`\n";
                __builtin_trap();
            }
        };

        if (not cond) [[unlikely]]
            handle::failure(loc);
    }
#else
    [[gnu::always_inline]] inline void
    precondition(bool cond) {
        struct handle {
            [[noreturn]] static void
            failure() {
                std::clog << "failed precondition\n";
                __builtin_trap();
            }
        };

        if (not cond) [[unlikely]]
            handle::failure();
    }
#endif

    template<typename V, typename T = void>
    concept any_simd = stdx::is_simd_v<V>
                    && (std::same_as<T, void> || std::same_as<T, typename V::value_type>);

    template<typename V, typename T>
    concept t_or_simd = std::same_as<V, T> || any_simd<V, T>;

    template<typename T>
    concept vectorizable = std::constructible_from<stdx::simd<T>>;

    template<typename A, typename B>
    struct wider_native_simd_size
        : std::conditional<(stdx::native_simd<A>::size() > stdx::native_simd<B>::size()), A, B> {};

    template<typename A>
    struct wider_native_simd_size<A, A> {
        using type = A;
    };

    template<typename V>
    struct rebind_simd_helper {
        template<typename T>
        using rebind = stdx::rebind_simd_t<T, V>;
    };

    struct simd_load_ctor {
        template<detail::any_simd W>
        static constexpr W
        apply(typename W::value_type const *ptr) {
            return W(ptr, stdx::element_aligned);
        }
    };

    template<typename List>
    using reduce_to_widest_simd = stdx::native_simd<meta::reduce<wider_native_simd_size, List>>;

    template<typename V, typename List>
    using transform_by_rebind_simd = meta::transform_types<rebind_simd_helper<V>::template rebind, List>;

    template<typename List>
    using transform_to_widest_simd = transform_by_rebind_simd<reduce_to_widest_simd<List>, List>;

    template<typename Node>
    concept any_node = requires(Node &n, typename Node::input_port_types::tuple_type const &inputs) {
        { n.in } -> std::same_as<typename Node::input_port_types const &>;
        { n.out } -> std::same_as<typename Node::output_port_types const &>;
        {
            []<std::size_t... Is>(Node &n, auto const &tup, std::index_sequence<Is...>)
                    -> decltype(n.process_one(std::get<Is>(tup)...)) {
                return {};
            }(n, inputs, std::make_index_sequence<Node::input_port_types::size>())
        } -> std::same_as<typename Node::return_type>;
    };

    template<typename Node>
    concept node_can_process_simd
            = any_node<Node>
           && requires(Node &n,
                       typename transform_to_widest_simd<typename Node::input_port_types>::
                               template apply<std::tuple> const &inputs) {
                  {
                      []<std::size_t... Is>(Node &n, auto const &tup, std::index_sequence<Is...>)
                              -> decltype(n.process_one(std::get<Is>(tup)...)) {
                          return {};
                      }(n, inputs, std::make_index_sequence<Node::input_port_types::size>())
                  } -> detail::any_simd<typename Node::return_type>;
              };

} // namespace detail

// #### default supported types -- TODO: to be replaced by pmt::pmtv declaration
using supported_type = std::variant<
    uint8_t, uint32_t, int8_t, int16_t, int32_t, float, double, std::complex<float>, std::complex<double> /*, ...*/>;

enum class port_direction_t { INPUT, OUTPUT, ANY }; // 'ANY' only for query and not to be used for port declarations
enum class connection_result_t { SUCCESS, FAILED };
enum class port_kind_t { STREAM, MESSAGE };
enum class port_domain_t { CPU, GPU, NET, FPGA, DSP, MLU };


template<class T>
concept Port = requires(T t, const std::size_t n_items) { // dynamic definitions
    typename T::value_type;
    { t.pmt_type() }             -> std::same_as<supported_type>;
    { t.kind() }                 -> std::same_as<port_kind_t>;
    { t.direction() }            -> std::same_as<port_direction_t>;
    { t.name() }                 -> std::same_as<std::string_view>;
    { t.resize_buffer(n_items) } -> std::same_as<connection_result_t>;
    { t.disconnect() }           -> std::same_as<connection_result_t>;
};

class edge;
class dynamic_port;
class block;

template<class T>
concept Block = requires(T& t, const std::size_t src_port, T& dst_block, const std::size_t dst_port, port_direction_t direction, dynamic_port& port) {
    { t.name() } -> std::same_as<std::string_view>;
    { t.work() } -> std::same_as<void>; // primary function to be called by scheduler
    //{ t.template add_port<port_direction_t::INPUT>(port) } -> std::same_as<dynamic_port&>;
    { t.input_ports() } -> std::same_as<std::span<const dynamic_port>>;
    { t.output_ports() } -> std::same_as<std::span<const dynamic_port>>;
    //{ t.connect(src_port, dst_block, dst_port) } -> std::same_as<std::vector<connection_result_t>>;
};


template<port_direction_t PortDirection,
         typename T,
         fixed_string PortName,
         port_kind_t PortKind>
struct port_definition {
    using port_definition_tag = std::true_type;

    using type = T;

    static inline constexpr fixed_string name = PortName;
    static inline constexpr port_kind_t kind = PortKind;
    static inline constexpr port_direction_t direction = PortDirection;

    static_assert(direction != port_direction_t::ANY);
};

template<typename T>
concept has_port_definition_v = requires { typename T::port_definition_tag; };

template<typename T>
using has_port_definition = std::integral_constant<bool, has_port_definition_v<T>>;

template <typename T>
struct has_port_definition_or_list : std::false_type {};

template <typename T>
    requires has_port_definition_v<T>
struct has_port_definition_or_list<T> : std::true_type {};

template <typename T>
    requires (meta::is_typelist_v<T> and T::template all_of<has_port_definition>)
struct has_port_definition_or_list<T> : std::true_type {};


template<typename Port>
using port_definition_type = typename Port::port_definition_tag::type;

template<typename Port>
using is_in_port = std::integral_constant<bool, Port::port_definition_tag::direction == port_direction_t::INPUT>;

template<typename Port>
using is_out_port = std::integral_constant<bool, Port::port_definition_tag::direction == port_direction_t::OUTPUT>;

// simple non-reentrant circular buffer
template<typename T, fixed_string PortName, port_kind_t PortKind, port_direction_t PortDirection, // TODO: sort default arguments
    std::size_t N_HISTORY = std::dynamic_extent, std::size_t MIN_SAMPLES = std::dynamic_extent, std::size_t MAX_SAMPLES = std::dynamic_extent, bool OPTIONAL = false,
    gr::Buffer BufferType = gr::circular_buffer<T>>
class static_port {
public:
    using port_definition_tag = port_definition<PortDirection, T, PortName, PortKind>;

    static_assert(PortDirection != port_direction_t::ANY, "ANY reserved for queries and not port direction declarations");

    using value_type = T;
    static constexpr bool IS_INPUT = PortDirection == port_direction_t::INPUT;
    static constexpr bool IS_OUTPUT = PortDirection == port_direction_t::OUTPUT;

    using static_port_tag = std::true_type;

private:
    using ReaderType = decltype(std::declval<BufferType>().new_reader());
    using WriterType = decltype(std::declval<BufferType>().new_writer());
    using IoType = std::conditional_t<IS_INPUT, ReaderType, WriterType>;

    std::string _name{PortName};
    std::int16_t _priority = 0; // → dependents of a higher-prio port should be scheduled first (Q: make this by order of ports?)
    std::size_t _n_history = N_HISTORY;
    std::size_t _min_samples = MIN_SAMPLES;
    std::size_t _max_samples = MAX_SAMPLES;
    bool _connected = false;

    IoType _ioHandler = new_io_handler();

    constexpr auto new_io_handler() noexcept {
        if constexpr (IS_INPUT) {
            return BufferType(4096).new_reader();
        } else {
            return BufferType(4096).new_writer(); 
        }
    }

    void* writer_handler_internal() noexcept {
        // QUESTION: This doesn't do anything, right?
        //           if IS_OUTPUT then assert that it IS_OUTPUT
        // if constexpr (IS_OUTPUT) {
        //     static_assert(IS_OUTPUT, "only to be used with output ports");
        // }
        return static_cast<void*>(std::addressof(_ioHandler));
    }

    bool update_reader_internal(void* buffer_writer_handler_other) noexcept {
        // QUESTION: This doesn't do anything, right?
        //           if IS_INPUT then assert that it IS_INPUT
        // if constexpr (IS_INPUT) {
        //     static_assert(IS_INPUT, "only to be used with input ports");
        // }
        try {
            // QUESTION: static_cast doesn't throw and no checks are performed,
            //           is this try meant for setBuffer (as the assert in catch
            //           doesn't state this)
            auto typed_buffer_writer = static_cast<WriterType*>(buffer_writer_handler_other);
            if (typed_buffer_writer == nullptr) {
                return false;
            }
            setBuffer(typed_buffer_writer->buffer());
        } catch (...) {
            // needed for runtime polymorphism
            assert(false && "invalid static_cast from 'void* -> WriterType*' in update_reader_internal()");
            return false;
        }
        return true;
    }

public:
    static_port() = default;
    static_port(const static_port&) = delete;
    auto operator=(const static_port&) = delete;

    constexpr static_port(std::string port_name, std::int16_t priority = 0, std::size_t n_history = 0,
                          std::size_t min_samples = 0U, std::size_t max_samples = SIZE_MAX) noexcept
        : _name(std::move(port_name))
        , _priority{priority}
        , _n_history(n_history)
        , _min_samples(min_samples)
        , _max_samples(max_samples) {
        static_assert(PortName.empty(), "port name must be exclusively declared via NTTP or constructor parameter");
    }

    constexpr static_port(static_port&& other) noexcept
        : _name(std::move(other._name))
        , _priority{other._priority}
        , _n_history(other._n_history)
        , _min_samples(other._min_samples)
        , _max_samples(other._max_samples) {
    }

    constexpr static_port& operator=(static_port&& other) {
        static_port tmp(std::move(other));
        std::swap(_name, tmp._name);
        std::swap(_priority, tmp._priority);
        std::swap(_n_history, tmp._n_history);
        std::swap(_min_samples, tmp._min_samples);
        std::swap(_max_samples, tmp._max_samples);
        std::swap(_connected, tmp._connected);
        std::swap(_ioHandler, tmp._ioHandler);
        return *this;
    }

    [[nodiscard]] constexpr static port_kind_t kind() noexcept { return PortKind; }
    [[nodiscard]] constexpr static port_direction_t direction() noexcept { return PortDirection; }

    template<bool enable = !PortName.empty()>
    [[nodiscard]] static constexpr std::enable_if_t<enable,decltype(PortName)> static_name() noexcept { return PortName; }

    [[nodiscard]] constexpr supported_type pmt_type() const noexcept { return T(); }
    [[nodiscard]] constexpr std::string_view name() const noexcept {
        if constexpr (!PortName.empty()) {
            return static_cast<std::string_view>(PortName);
        } else {
            return _name;
        }
    }

    [[nodiscard]] constexpr static bool is_optional() noexcept { return OPTIONAL; }
    [[nodiscard]] constexpr std::int16_t priority() const noexcept { return _priority; }

    [[nodiscard]] constexpr static std::size_t available() noexcept { return 0; } //  ↔ maps to Buffer::Buffer[Reader, Writer].available()
    [[nodiscard]] constexpr std::size_t n_history() const noexcept {
        if constexpr (N_HISTORY == std::dynamic_extent) {
            return _n_history;
        } else {
            return N_HISTORY;
        }
    }
    [[nodiscard]] constexpr std::size_t min_buffer_size() const noexcept {
        if constexpr (MIN_SAMPLES == std::dynamic_extent) {
            return _min_samples;
        } else {
            return MIN_SAMPLES;
        }
    }
    [[nodiscard]] constexpr std::size_t max_buffer_size() const noexcept {
        if constexpr (MAX_SAMPLES == std::dynamic_extent) {
            return _max_samples;
        } else {
            return MAX_SAMPLES;
        }
    }

    [[nodiscard]] constexpr connection_result_t resize_buffer(std::size_t min_size) noexcept {
        if constexpr (IS_INPUT) {
            // This can not be requires clause as Port concept checks for
            // resize_buffer
            static_assert(IS_INPUT, "can only resize output buffers");
        } else {
            try {
                _ioHandler =  BufferType(min_size).new_writer();
            } catch (...) {
                return connection_result_t::FAILED;
            }
        }
        return connection_result_t::SUCCESS;
    }
    [[nodiscard]] BufferType buffer() { return _ioHandler.buffer(); }

    void setBuffer(gr::Buffer auto buffer) {
        if constexpr (IS_INPUT) {
            _ioHandler = std::move(buffer.new_reader());
            _connected = true;
        } else {
            _ioHandler = std::move(buffer.new_writer()); 
        }
    }

    [[nodiscard]] ReaderType& reader() noexcept {
        if constexpr (IS_OUTPUT) {
            static_assert(detail::always_false<T>, "reader() not applicable for outputs (yet)");
        }
        return _ioHandler;
    }

    [[nodiscard]] WriterType& writer() noexcept {
        if constexpr (IS_INPUT) {
            static_assert(detail::always_false<T>, "writer() not applicable for inputs (yet)");
        }
        return _ioHandler;
    }

    [[nodiscard]] connection_result_t disconnect() noexcept {
        if (_connected == false) {
            // QUESTION: API design - should this return if we did anything
            //           or should it return whether post-condition is valid -
            //           that is, if we are not connected after calling
            //           disconnect (regardless of the previous state),
            //           should disconnect return success?
            return connection_result_t::FAILED;
        }
        _ioHandler = new_io_handler();
        _connected = false;
        return connection_result_t::SUCCESS;
    }

    friend class dynamic_port;
};

namespace detail {
    template<typename T, auto>
    using just_t = T;

    template<typename T, std::size_t... Is>
    consteval fair::meta::typelist<just_t<T, Is>...>
    repeated_ports_impl(std::index_sequence<Is...>) {
        return {};
    }
} // namespace detail

// TODO: Add port index to BaseName
template<std::size_t Count, typename T, fixed_string BaseName, port_kind_t PortKind, port_direction_t PortDirection, std::size_t MIN_SAMPLES = std::dynamic_extent, std::size_t MAX_SAMPLES = std::dynamic_extent>
using repeated_ports =
    decltype(detail::repeated_ports_impl<static_port<T, BaseName, PortKind, PortDirection, MIN_SAMPLES, MAX_SAMPLES>>(std::make_index_sequence<Count>()));

template<typename T, fixed_string PortName = "", std::size_t MIN_SAMPLES = std::dynamic_extent, std::size_t MAX_SAMPLES = std::dynamic_extent>
using IN = static_port<T, PortName, port_kind_t::STREAM, port_direction_t::INPUT, MIN_SAMPLES, MAX_SAMPLES>;
template<typename T, fixed_string PortName = "", std::size_t MIN_SAMPLES = std::dynamic_extent, std::size_t MAX_SAMPLES = std::dynamic_extent>
using OUT = static_port<T, PortName, port_kind_t::STREAM, port_direction_t::OUTPUT, MIN_SAMPLES, MAX_SAMPLES>;
template<typename T, fixed_string PortName = "", std::size_t MIN_SAMPLES = std::dynamic_extent, std::size_t MAX_SAMPLES = std::dynamic_extent>
using IN_MSG = static_port<T, PortName, port_kind_t::MESSAGE, port_direction_t::INPUT, MIN_SAMPLES, MAX_SAMPLES>;
template<typename T, fixed_string PortName = "", std::size_t MIN_SAMPLES = std::dynamic_extent, std::size_t MAX_SAMPLES = std::dynamic_extent>
using OUT_MSG = static_port<T, PortName, port_kind_t::MESSAGE, port_direction_t::OUTPUT, MIN_SAMPLES, MAX_SAMPLES>;

class dynamic_port {
    struct model {
        virtual ~model() = default;

        [[nodiscard]] virtual supported_type pmt_type() const noexcept = 0;
        [[nodiscard]] virtual port_kind_t kind() const noexcept = 0;
        [[nodiscard]] virtual port_direction_t direction() const noexcept = 0;
        [[nodiscard]] virtual std::string_view name() const noexcept = 0;
        [[nodiscard]] virtual connection_result_t resize_buffer(std::size_t min_size) noexcept = 0;
        [[nodiscard]] virtual connection_result_t disconnect() noexcept = 0;
        [[nodiscard]] virtual connection_result_t connect(dynamic_port& dst_port) noexcept = 0;

        // internal runtime polymorphism access
        [[nodiscard]] virtual bool update_reader_internal(void* buffer_other) noexcept = 0;
    };

    std::unique_ptr<model> _accessor;

    template<Port T>
    class wrapper final : public model {
        using PortType = std::decay_t<T>;
        PortType _value; // N.B. only initialised when dynamic_port is initialised with an rvalue
        PortType& _value_ref;

        [[nodiscard]] void* writer_handler_internal() noexcept { return _value_ref.writer_handler_internal(); };
        [[nodiscard]] bool update_reader_internal(void* buffer_other) noexcept override {
            return _value_ref.update_reader_internal(buffer_other);
        }

    public:
        template<Port P>
        explicit constexpr wrapper(P &arg) noexcept : _value_ref{ arg } {
            if constexpr (P::IS_INPUT) {
                static_assert(requires { arg.writer_handler_internal(); }, "'private void* writer_handler_internal()' not implemented");
            } else {
                static_assert(requires { arg.update_reader_internal(std::declval<void*>()); }, "'private bool update_reader_internal(void* buffer)' not implemented");
            }
        }

        template<Port P>
        explicit constexpr wrapper(P &&arg) noexcept : _value{ std::forward<P>(arg)}, _value_ref{ _value } {
            if constexpr (P::IS_INPUT) {
                static_assert(requires { arg.writer_handler_internal(); }, "'private void* writer_handler_internal()' not implemented");
            } else {
                static_assert(requires { arg.update_reader_internal(std::declval<void*>()); }, "'private bool update_reader_internal(void* buffer)' not implemented");
            }
            // N.B. we keep a reference if ports have been passed as rvalue
        }

        ~wrapper() override = default;

        [[nodiscard]] constexpr supported_type pmt_type() const noexcept override { return _value_ref.pmt_type(); }
        [[nodiscard]] constexpr port_kind_t kind() const noexcept override { return _value_ref.kind(); }
        [[nodiscard]] constexpr port_direction_t direction() const noexcept override { return _value_ref.direction(); }
        [[nodiscard]] constexpr std::string_view name() const noexcept override {  return _value_ref.name(); }
        [[nodiscard]] connection_result_t resize_buffer(std::size_t min_size) noexcept override {  return _value_ref.resize_buffer(min_size); }
        [[nodiscard]] connection_result_t disconnect() noexcept override {  return _value_ref.disconnect(); }
        [[nodiscard]] connection_result_t connect(dynamic_port& dst_port) noexcept override {
            auto src_buffer = _value_ref.writer_handler_internal();
            return dst_port.update_reader_internal(src_buffer) ? connection_result_t::SUCCESS: connection_result_t::FAILED;
        }
    };

    bool update_reader_internal(void* buffer_other)  noexcept { return _accessor->update_reader_internal(buffer_other); }

public:
    using value_type = void;

    constexpr dynamic_port() = delete;

    template<Port T>
    constexpr dynamic_port(const T &arg) = delete;
    template<Port T>
    explicit constexpr dynamic_port(T &arg) noexcept : _accessor{ std::make_unique<wrapper<T>>(arg) } {}

    template<Port T>
    explicit constexpr dynamic_port(T &&arg) noexcept : _accessor{ std::make_unique<wrapper<T>>(std::forward<T>(arg)) } {}

    [[nodiscard]] supported_type pmt_type() const noexcept { return _accessor->pmt_type(); }
    [[nodiscard]] port_kind_t kind() const noexcept { return _accessor->kind(); }
    [[nodiscard]] port_direction_t direction() const noexcept { return _accessor->direction(); }
    [[nodiscard]] std::string_view name() const noexcept { return _accessor->name(); }

    [[nodiscard]] connection_result_t resize_buffer(std::size_t min_size) {
        if (direction() == port_direction_t::OUTPUT) {
            return _accessor->resize_buffer(min_size);
        }
        return connection_result_t::FAILED;
    }

    [[nodiscard]] connection_result_t disconnect() noexcept {  return _accessor->disconnect(); }
    [[nodiscard]] connection_result_t connect(dynamic_port& dst_port) noexcept { return _accessor->connect(dst_port); }
};
static_assert(Port<dynamic_port>);



#ifdef NOT_YET_PORTED_AS_IT_IS_UNUSED
template<typename T, std::size_t Size>
class port_data {
public:
    static_assert(std::has_single_bit(Size), "Size must be a power-of-2 value");
    alignas(64) std::array<T, Size> m_buffer       = {};
    std::size_t                     m_read_offset  = 0;
    std::size_t                     m_write_offset = 0;

    static inline constexpr std::size_t s_bitmask      = Size - 1;

public:
    static inline constexpr std::integral_constant<std::size_t, Size> size = {};

    std::size_t
    can_read() const {
        return m_write_offset >= m_read_offset ? m_write_offset - m_read_offset
                                               : size - m_read_offset;
    }

    std::size_t
    can_write() const {
        return m_write_offset >= m_read_offset ? size - m_write_offset
                                               : m_read_offset - m_write_offset;
    }

    std::span<const T>
    request_read() {
        return request_read(can_read());
    }

    std::span<const T>
    request_read(std::size_t n) {
        detail::precondition(can_read() >= n);
        const auto begin = m_buffer.begin() + m_read_offset;
        m_read_offset += n;
        m_read_offset &= s_bitmask;
        return std::span<const T>{ begin, n };
    }

    std::span<T>
    request_write() {
        return request_write(can_write());
    }

    std::span<T>
    request_write(std::size_t n) {
        detail::precondition(can_write() >= n);
        const auto begin = m_buffer.begin() + m_write_offset;
        m_write_offset += n;
        m_write_offset &= s_bitmask;
        return std::span<T>{ begin, n };
    }
};
#endif

template<typename...>
struct node_ports_data;

template<meta::is_typelist_v InputPorts, meta::is_typelist_v OutputPorts>
    requires InputPorts::template all_of<has_port_definition>
          && OutputPorts::template all_of<has_port_definition>
struct node_ports_data<InputPorts, OutputPorts> {
    using input_ports = InputPorts;
    using output_ports = OutputPorts;

    using input_port_types =
        typename input_ports
        ::template transform<port_definition_type>;
    using output_port_types =
        typename output_ports
        ::template transform<port_definition_type>;

    using all_ports = meta::concat<input_ports, output_ports>;

    static_assert(all_ports::size > 0);
    static_assert(input_ports::size > 0);
    static_assert(output_ports::size > 0);
};

template<has_port_definition_v... Ports>
struct node_ports_data<Ports...> {
    using all_ports = meta::concat<
        std::conditional_t<fair::meta::is_typelist_v<Ports>,
            Ports,
            meta::typelist<Ports>
        >...>;

    using input_ports =
        typename all_ports
        ::template filter<is_in_port>;
    using output_ports =
        typename all_ports
        ::template filter<is_out_port>;

    using input_port_types =
        typename input_ports
        ::template transform<port_definition_type>;
    using output_port_types =
        typename output_ports
        ::template transform<port_definition_type>;

    static_assert(all_ports::size > 0);
    static_assert(input_ports::size > 0);
    static_assert(output_ports::size > 0);
};

// Ports can either be a list of port_definition instances,
// or two typelists containing port_definition instances -- one for input
// ports and one for output ports
template<typename Derived, typename... Arguments>
class static_node: public meta::typelist<Arguments...>
                       ::template filter<has_port_definition_or_list>
                       ::template apply<node_ports_data> {
public:
    using base = typename meta::typelist<Arguments...>
                     ::template filter<has_port_definition_or_list>
                     ::template apply<node_ports_data>;

    using all_ports = typename base::all_ports;
    using input_ports = typename base::input_ports;
    using output_ports = typename base::output_ports;
    using input_port_types = typename base::input_port_types;
    using output_port_types = typename base::output_port_types;

    using return_type = typename output_port_types::tuple_or_type;

    static inline constexpr input_port_types  in  = {};
    static inline constexpr output_port_types out = {};

    Derived* self() { return this; }
    const Derived* self() const { return this; }

    template<std::size_t N>
    [[gnu::always_inline]] constexpr bool
    process_batch_simd_epilogue(std::size_t n, auto out_ptr, auto... in_ptr) {
        if constexpr (N == 0) return true;
        else if (N <= n) {
            using In0 = meta::first_type<input_port_types>;
            using V   = stdx::resize_simd_t<N, stdx::native_simd<In0>>;
            using Vs  = meta::transform_types<detail::rebind_simd_helper<V>::template rebind,
                                              input_port_types>;
            const std::tuple input_simds = Vs::template construct<detail::simd_load_ctor>(
                    std::tuple{ in_ptr... });
            const stdx::simd result = std::apply(
                    [this](auto... args) {
                        return self()->process_one(args...);
                    },
                    input_simds);
            result.copy_to(out_ptr, stdx::element_aligned);
            return process_batch_simd_epilogue<N / 2>(n, out_ptr + N, (in_ptr + N)...);
        } else
            return process_batch_simd_epilogue<N / 2>(n, out_ptr, in_ptr...);
    }

#ifdef NOT_YET_PORTED_AS_IT_IS_UNUSED
    template<std::ranges::forward_range... Ins>
        requires(std::ranges::sized_range<Ins> && ...)
        && input_port_types::template are_equal<std::ranges::range_value_t<Ins>...>
    constexpr bool
    process_batch(port_data<return_type, 1024> &out, Ins &&...inputs) {
        const auto  &in0    = std::get<0>(std::tie(inputs...));
        const std::size_t n = std::ranges::size(in0);
        detail::precondition(((n == std::ranges::size(inputs)) && ...));
        auto &&out_range = out.request_write(n);
        // if SIMD makes sense (i.e. input and output ranges are contiguous and all types are
        // vectorizable)
        if constexpr ((std::ranges::contiguous_range<decltype(out_range)> && ... && std::ranges::contiguous_range<Ins>)
                      && detail::vectorizable<return_type>
                      && detail::node_can_process_simd<Derived>
                      && input_port_types
                         ::template transform<stdx::native_simd>
                         ::template all_of<std::is_constructible>) {
            using V  = detail::reduce_to_widest_simd<input_port_types>;
            using Vs = detail::transform_by_rebind_simd<V, input_port_types>;
            std::size_t i = 0;
            for (i = 0; i + V::size() <= n; i += V::size()) {
                const std::tuple input_simds = Vs::template construct<detail::simd_load_ctor>(
                        std::tuple{ (std::ranges::data(inputs) + i)... });
                const stdx::simd result = std::apply(
                        [this](auto... args) {
                            return self()->process_one(args...);
                        },
                        input_simds);
                result.copy_to(std::ranges::data(out_range) + i, stdx::element_aligned);
            }

            return process_batch_simd_epilogue<std::bit_ceil(V::size())
                                               / 2>(n - i, std::ranges::data(out_range) + i,
                                                    (std::ranges::data(inputs) + i)...);
        } else { // no explicit SIMD
            auto             out_it    = out_range.begin();
            std::tuple       it_tuple  = { std::ranges::begin(inputs)... };
            const std::tuple end_tuple = { std::ranges::end(inputs)... };
            while (std::get<0>(it_tuple) != std::get<0>(end_tuple)) {
                *out_it = std::apply(
                        [this](auto &...its) {
                            return self()->process_one((*its++)...);
                        },
                        it_tuple);
                ++out_it;
            }
            return true;
        }
    }
#endif

protected:
    constexpr static_node() noexcept = default;
};

template<
    detail::any_node Left,
    detail::any_node Right,
    int OutId,
    int InId
    >
class static_merged_node
    : public static_node<
        static_merged_node<Left, Right, OutId, InId>,
        meta::concat<
            typename Left::input_ports,
            meta::remove_at<InId, typename Right::input_ports>
        >,
        meta::concat<
            meta::remove_at<OutId, typename Left::output_ports>,
            typename Right::output_ports
        >
    >{
private:
    // copy-paste from above, keep in sync
    using base = static_node<
        static_merged_node<Left, Right, OutId, InId>,
        meta::concat<
            typename Left::input_ports,
            meta::remove_at<InId, typename Right::input_ports>
        >,
        meta::concat<
            meta::remove_at<OutId, typename Left::output_ports>,
            typename Right::output_ports
        >
    >;

    Left  left;
    Right right;

    template<std::size_t I>
    [[gnu::always_inline]] constexpr auto
    apply_left(auto &&input_tuple) {
        return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
            return left.process_one(std::get<Is>(input_tuple)...);
        } (std::make_index_sequence<I>());
    }

    template<std::size_t I, std::size_t J>
    [[gnu::always_inline]] constexpr auto
    apply_right(auto &&input_tuple, auto &&tmp) {
        return [&]<std::size_t... Is, std::size_t... Js>(std::index_sequence<Is...>, std::index_sequence<Js...>) {
            constexpr int first_offset  = Left::input_port_types::size;
            constexpr int second_offset = Left::input_port_types::size + sizeof...(Is);
            static_assert(second_offset + sizeof...(Js)
                          == std::tuple_size_v<std::remove_cvref_t<decltype(input_tuple)>>);
            return right.process_one(std::get<first_offset + Is>(input_tuple)..., std::move(tmp),
                                     std::get<second_offset + Js>(input_tuple)...);
        } (std::make_index_sequence<I>(), std::make_index_sequence<J>());
    }

public:
    using input_port_types  = typename base::input_port_types;
    using output_port_types = typename base::output_port_types;
    using return_type  = typename base::return_type;

    [[gnu::always_inline]] constexpr static_merged_node(Left l, Right r)
        : left(std::move(l)), right(std::move(r)) {}

    template<detail::any_simd... Ts>
        requires detail::vectorizable<return_type>
        && input_port_types::template are_equal<typename std::remove_cvref_t<Ts>::value_type...>
        && detail::node_can_process_simd<Left>
        && detail::node_can_process_simd<Right>
    constexpr stdx::rebind_simd_t<return_type, meta::first_type<meta::typelist<std::remove_cvref_t<Ts>...>>>
    process_one(Ts... inputs) {
        return apply_right<InId, Right::input_port_types::size() - InId - 1>
            (std::tie(inputs...), apply_left<Left::input_port_types::size()>(std::tie(inputs...)));
    }

    template<typename... Ts>
        // In order to have nicer error messages, this is checked in the function body
        // requires input_port_types::template are_equal<std::remove_cvref_t<Ts>...>
    constexpr return_type
    process_one(Ts &&...inputs) {
        if constexpr (!input_port_types::template are_equal<std::remove_cvref_t<Ts>...>) {
            meta::print_types<
                decltype(this),
                input_port_types,
                std::remove_cvref_t<Ts>...> error{};
        }

        if constexpr (Left::output_port_types::size
                      == 1) { // only the result from the right node needs to be returned
            return apply_right<InId, Right::input_port_types::size() - InId - 1>
                (std::forward_as_tuple(std::forward<Ts>(inputs)...),
                               apply_left<Left::input_port_types::size()>(std::forward_as_tuple(std::forward<Ts>(inputs)...)));

        } else {
            // left produces a tuple
            auto left_out = apply_left<Left::input_port_types::size()>
                            (std::forward_as_tuple(std::forward<Ts>(inputs)...));
            auto right_out = apply_right<InId, Right::input_port_types::size() - InId - 1>
                             (std::forward_as_tuple(std::forward<Ts>(inputs)...), std::move(std::get<OutId>(left_out)));

            if constexpr (Left::output_port_types::size == 2 && Right::output_port_types::size == 1) {
                return std::make_tuple(std::move(std::get<OutId ^ 1>(left_out)),
                                       std::move(right_out));

            } else if constexpr (Left::output_port_types::size == 2) {
                return std::tuple_cat(std::make_tuple(std::move(std::get<OutId ^ 1>(left_out))),
                                      std::move(right_out));

            } else if constexpr (Right::output_port_types::size == 1) {
                return [&]<std::size_t... Is, std::size_t... Js>(std::index_sequence<Is...>,
                                                                 std::index_sequence<Js...>) {
                    return std::make_tuple(std::move(std::get<Is>(left_out))...,
                                           std::move(std::get<OutId + 1 + Js>(left_out))...,
                                           std::move(right_out));
                }(std::make_index_sequence<OutId>(),
                  std::make_index_sequence<Left::output_port_types::size - OutId - 1>());

            } else {
                return [&]<std::size_t... Is, std::size_t... Js,
                           std::size_t... Ks>(std::index_sequence<Is...>,
                                              std::index_sequence<Js...>,
                                              std::index_sequence<Ks...>) {
                    return std::make_tuple(std::move(std::get<Is>(left_out))...,
                                           std::move(std::get<OutId + 1 + Js>(left_out))...,
                                           std::move(std::get<Ks>(right_out)...));
                }(std::make_index_sequence<OutId>(),
                  std::make_index_sequence<Left::output_port_types::size - OutId - 1>(),
                  std::make_index_sequence<Right::output_port_types::size>());
            }
        }
    }
};

template<int OutId, int InId, detail::any_node A, detail::any_node B>
[[gnu::always_inline]] constexpr auto
merge_by_index(A &&a, B &&b) -> static_merged_node<std::remove_cvref_t<A>, std::remove_cvref_t<B>, OutId, InId> {
    if constexpr(!std::is_same_v<typename std::remove_cvref_t<A>::output_port_types::template at<OutId>,
                                 typename std::remove_cvref_t<B>::input_port_types::template at<InId>>) {
        fair::meta::print_types<
            fair::meta::message_type<"OUTPUT_PORTS_ARE:">,
            typename std::remove_cvref_t<A>::output_port_types,
            std::integral_constant<int, OutId>,
            typename std::remove_cvref_t<A>::output_port_types::template at<OutId>,

            fair::meta::message_type<"INPUT_PORTS_ARE:">,
            typename std::remove_cvref_t<A>::input_port_types,
            std::integral_constant<int, InId>,
            typename std::remove_cvref_t<A>::input_port_types::template at<InId>>{};
    }
    return { std::forward<A>(a), std::forward<B>(b) };
}

namespace detail {
    template<fixed_string Name, typename PortList>
    consteval int indexForName() {
        auto helper = [] <std::size_t... Ids> (std::index_sequence<Ids...>) {
            int result = -1;
            ((PortList::template at<Ids>::port_definition_tag::name == Name ? (result = Ids) : 0), ...);
            return result;
        };
        return helper(std::make_index_sequence<PortList::size>());
    }
} // namespace detail

template<fixed_string OutName, fixed_string InName, detail::any_node A, detail::any_node B>
[[gnu::always_inline]] constexpr auto
merge(A &&a, B &&b) {
    constexpr int OutId = detail::indexForName<OutName, typename A::output_ports>();
    constexpr int InId = detail::indexForName<InName, typename B::input_ports>();
    static_assert(OutId != -1);
    static_assert(InId != -1);
    static_assert(std::same_as<typename std::remove_cvref_t<A>::output_port_types::template at<OutId>,
                               typename std::remove_cvref_t<B>::input_port_types::template at<InId>>,
                  "Port types do not match");
    return static_merged_node<std::remove_cvref_t<A>, std::remove_cvref_t<B>, OutId, InId>{ std::forward<A>(a), std::forward<B>(b) };
}


class block {
    using setting_map = std::map<std::string, int, std::less<>>;
    std::string _name;
    std::vector<dynamic_port> _input_ports{};
    std::vector<dynamic_port> _output_ports{};
    setting_map _exec_metrics{}; //  →  std::map<string, pmt> → fair scheduling, 'int' stand-in for pmtv

    friend class edge;

public:
    explicit block(std::string name)
        : _name(std::move(name)) {}

    [[nodiscard]] std::string_view name() const noexcept { return _name; }

    template<typename T>
    void add_port(T&& port) {
        switch (port.direction()) {
            case port_direction_t::INPUT:
                if (auto portID = port_index<port_direction_t::INPUT>(port.name()); portID.has_value()) {
                    throw std::invalid_argument(fmt::format("port already has a defined input port named '{}' at ID {}",
                                port.name(), portID.value()));
                }
                _input_ports.emplace_back(std::forward<T>(port));
                break;
            case port_direction_t::OUTPUT:
                if (auto portID = port_index<port_direction_t::OUTPUT>(port.name()); portID.has_value()) {
                    throw std::invalid_argument(fmt::format("port already has a defined output port named '{}' at ID {}",
                                                            port.name(), portID.value()));
                }
                _output_ports.emplace_back(std::forward<T>(port));
                break;
            default:
                assert(false && "cannot add port with ANY designation");
        }
    }

    template<port_direction_t direction>
    [[nodiscard]] std::optional<dynamic_port*> port(std::size_t index) {
        if constexpr (direction == port_direction_t::INPUT) {
            return index < _input_ports.size() ? std::optional{&_input_ports[index] } : std::nullopt;
        } else if constexpr (direction == port_direction_t::OUTPUT) {
            return index < _output_ports.size() ? std::optional{&_output_ports[index] } : std::nullopt;
        }
        return std::nullopt;
    }

    template<port_direction_t direction>
    [[nodiscard]] std::optional<std::size_t> port_index(std::string_view name) const {
        const auto matcher = [&name](const dynamic_port& port){ return port.name() == name; };
        if constexpr (direction == port_direction_t::INPUT) {
            const auto it = std::find_if(_input_ports.cbegin(), _input_ports.cend(), matcher);
            return  it != _input_ports.cend() ? std::optional{it - _input_ports.cbegin()} : std::nullopt;

        } else if constexpr (direction == port_direction_t::OUTPUT) {
            const auto it = std::find_if(_output_ports.cbegin(), _output_ports.cend(), matcher);
            return  it != _output_ports.cend() ? std::optional{it - _output_ports.cbegin()} : std::nullopt;
        }
        return std::nullopt;
    }

    template<port_direction_t direction>
    [[nodiscard]] std::optional<dynamic_port*> port(std::string_view name) {
        if (const auto index = port_index<direction>(name); index.has_value()) {
            if constexpr (direction == port_direction_t::INPUT) {
                return &_input_ports[*index];
            } else if constexpr (direction == port_direction_t::OUTPUT) {
                return &_output_ports[*index];
            }
        }
        return std::nullopt;
    }

    void work() noexcept { /* to be implemented in derived classes */ }
    [[nodiscard]] std::span<const dynamic_port> input_ports() const noexcept { return _input_ports; }
    [[nodiscard]] std::span<const dynamic_port> output_ports() const noexcept { return _output_ports; }

    [[nodiscard]] setting_map &exec_metrics() noexcept { return _exec_metrics; }
    [[nodiscard]] setting_map const &exec_metrics() const noexcept { return _exec_metrics; }
};
static_assert(Block<block>);

class graph {
private:
    class edge {
    public:
        using port_direction_t::INPUT;
        using port_direction_t::OUTPUT;
        std::shared_ptr<block> _src_block;
        std::shared_ptr<block> _dst_block;
        std::size_t _src_port_index;
        std::size_t _dst_port_index;
        int32_t _weight;
        std::string _name; // custom edge name
        bool _connected;

    public:
        edge() = delete;
        edge& operator=(const edge&) = delete;
        edge(std::shared_ptr<block> src_block, std::size_t src_port_index, std::shared_ptr<block> dst_block, std::size_t dst_port_index, int32_t weight, std::string_view name) :
                _src_block(src_block), _dst_block(dst_block), _src_port_index(src_port_index), _dst_port_index(dst_port_index), _weight(weight), _name(name) {
            if (!src_block->port<OUTPUT>(_src_port_index)) {
                throw fmt::format("source block '{}' has not output port id {}", _src_block->name(), _src_port_index);
            }
            if (!dst_block->port<INPUT>(_dst_port_index)) {
                throw fmt::format("destination block '{}' has not output port id {}", _dst_block->name(), _dst_port_index);
            }
            const dynamic_port& src_port = *src_block->port<OUTPUT>(_src_port_index).value();
            const dynamic_port& dst_port = *dst_block->port<INPUT>(_dst_port_index).value();
            if (src_port.pmt_type().index() != dst_port.pmt_type().index()) {
                throw fmt::format("edge({}::{}<{}> -> {}::{}<{}>, weight: {}, name:\"{}\") incompatible to type id='{}'",
                    _src_block->name(), src_port.name(), src_port.pmt_type().index(),
                    _dst_block->name(), dst_port.name(), dst_port.pmt_type().index(),
                    _weight, _name, dst_port.pmt_type().index());
            }
        }
        edge(std::shared_ptr<block> src_block, std::string_view src_port_name, std::shared_ptr<block> dst_block, std::string_view dst_port_name, int32_t weight, std::string_view name) :
                _src_block(src_block), _dst_block(dst_block), _weight(weight), _name(name) {
            const auto src_id = _src_block->port_index<OUTPUT>(src_port_name);
            const auto dst_id = _dst_block->port_index<INPUT>(dst_port_name);
            if (!src_id) {
                throw std::invalid_argument(fmt::format("source block '{}' has not output port '{}'", _src_block->name(), src_port_name));
            }
            if (!dst_id) {
                throw fmt::format("destination block '{}' has not output port '{}'", _dst_block->name(), dst_port_name);
            }
            _src_port_index = src_id.value();
            _dst_port_index = dst_id.value();
            const dynamic_port& src_port = *src_block->port<OUTPUT>(_src_port_index).value();
            const dynamic_port& dst_port = *dst_block->port<INPUT>(_dst_port_index).value();
            if (src_port.pmt_type().index() != dst_port.pmt_type().index()) {
                throw fmt::format("edge({}::{}<{}> -> {}::{}<{}>, weight: {}, name:\"{}\") incompatible to type id='{}'",
                                  _src_block->name(), src_port.name(), src_port.pmt_type().index(),
                                  _dst_block->name(), dst_port.name(), dst_port.pmt_type().index(),
                                  _weight, _name, dst_port.pmt_type().index());
            }
        }

        [[nodiscard]] constexpr int32_t weight() const noexcept { return _weight; }
        [[nodiscard]] constexpr std::string_view name() const noexcept { return _name; }
        [[nodiscard]] constexpr bool connected() const noexcept { return _connected; }
        [[nodiscard]] connection_result_t connect() const noexcept { return connection_result_t::FAILED; }
        [[nodiscard]] connection_result_t disconnect() const noexcept { return _dst_block->port<INPUT>(_dst_port_index).value()->disconnect(); }
    };
    std::vector<edge> _edges;

public:
    [[nodiscard]] connection_result_t add_edge(std::shared_ptr<block> src_block, std::size_t src_port_index,
                                               std::shared_ptr<block> dst_block, std::size_t dst_port_index,
                                               int32_t weight = 0, std::string_view name = "unnamed edge") noexcept {
        try {
            _edges.emplace_back(src_block, src_port_index, dst_block, dst_port_index, weight, name);
            return connection_result_t::SUCCESS;
        } catch (...) {
            // TODO: add logger or other communication of sorts (dynamic failure case)
            return connection_result_t::FAILED;
        }
    }

    // TODO: alt versions to be completed once ports are integrated into the node
    [[nodiscard]] connection_result_t add_edge(std::shared_ptr<block> src_block, std::string_view src_port_name,
                                               std::shared_ptr<block> dst_block, std::string_view dst_port_name,
                                               int32_t weight = 0, std::string_view name = "unnamed edge") noexcept {
        try {
            _edges.emplace_back(src_block, src_port_name, dst_block, dst_port_name, weight, name);
            return connection_result_t::SUCCESS;
        } catch (...) {
            // TODO: add logger or other communication of sorts (dynamic failure case)
            return connection_result_t::FAILED;
        }
        // impl detail:
        // check if port name exists -> get dyn_port
        // call add_edge(... dyn_port&) variant
        // else
        // fail - verbose:
        // a) duplicate names -> recommend to connect by ID
        // b) indicate block::port type mismatches
        return connection_result_t::FAILED;
    }

    auto edges_count() const {
        return _edges.size();
    }

};

// TODO: add nicer enum formatter
inline std::ostream& operator<<(std::ostream& os, const connection_result_t& value) {
    return os << static_cast<int>(value);
}
inline std::ostream& operator<<(std::ostream& os, const port_kind_t& value) {
    return os << static_cast<int>(value);
}
inline std::ostream& operator<<(std::ostream& os, const port_direction_t& value) {
    return os << static_cast<int>(value);
}
inline std::ostream& operator<<(std::ostream& os, const port_domain_t& value) {
    return os << static_cast<int>(value);
}

} // namespace fair::graph

#endif // GRAPH_PROTOTYPE_GRAPH_HPP
