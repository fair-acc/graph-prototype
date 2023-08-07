#ifndef GNURADIO_PROFILER_H
#define GNURADIO_PROFILER_H

#include "circular_buffer.hpp"

#include <fmt/format.h>

#include <chrono>
#include <fstream>
#include <string>
#include <string_view>
#include <thread>

#include <unistd.h>

namespace flow::graph::profiling {

using arg_value = std::pair<std::string, std::variant<std::string, int, double>>;

namespace detail {
using clock      = std::chrono::high_resolution_clock;
using time_point = clock::time_point;

enum class EventType {
    DurationBegin = 'B', // Duration Event (begin).
    DurationEnd   = 'E', // Duration Event (end).
    Complete      = 'X', // Complete Event.
    Instant       = 'I', // Instant Event.
    Counter       = 'C', // Counter Event.
    AsyncStart    = 'b', // Async Event (start).
    AsyncStep     = 'n', // Async Event (step).
    AsyncEnd      = 'e', // Async Event (end).
    FlowStart     = 's', // Flow Event (start).
    FlowStep      = 't', // Flow Event (step).
    FlowEnd       = 'f'  // Flow Event (end).
};

inline std::string
format_args(const std::vector<arg_value> &args) {
    if (args.empty()) {
        return "{}";
    }
    std::string r = "{";
    for (std::size_t i = 0; i < args.size(); ++i) {
        if (i > 0) {
            r += ",";
        }
        if (std::holds_alternative<std::string>(args[i].second)) {
            r += fmt::format("\"{}\":\"{}\"", args[i].first, std::get<std::string>(args[i].second));
        } else if (std::holds_alternative<double>(args[i].second)) {
            r += fmt::format("\"{}\":{}", args[i].first, std::get<double>(args[i].second));
        } else {
            r += fmt::format("\"{}\":{}", args[i].first, std::get<int>(args[i].second));
        }
    }
    r += "}";
    return r;
}

struct TraceEvent {
    std::thread::id           thread_id;
    std::string               name; // Event name.
    EventType                 type; // Event type.
    std::chrono::microseconds ts;   // Timestamp
    std::chrono::microseconds dur;  // Duration of the event, for 'X' type.
    std::string               id;   // ID for matching async or flow events.
    std::string               cat;  // Event categories.
    std::vector<arg_value>    args; // Event arguments.

    // Function to format a TraceEvent into JSON format.
    std::string
    toJSON(int pid, int tid) const {
        using enum EventType;
        switch (type) {
        case DurationBegin:
        case DurationEnd:
        case Counter:
        case Instant:
            return fmt::format(R"({{"name": "{}", "ph": "{}", "ts": {}, "pid": {}, "tid": {}, "cat": "{}", "args": {}}})", name, static_cast<char>(type), ts.count(), pid, tid, cat, format_args(args));
        case Complete:
            return fmt::format(R"({{"name": "{}", "ph": "C", "ts": {}, "pid": {}, "tid": {}, "dur": {}, "cat": "{}", "args": {}}})", name, ts.count(), pid, tid, dur.count(), cat, format_args(args));
        case AsyncStart:
        case AsyncStep:
        case AsyncEnd:
            return fmt::format(R"({{"name": "{}", "ph": "{}", "ts": {}, "pid": {}, "tid": {}, "id": {}, "cat": "{}", "args": {}}})", name, static_cast<char>(type), ts.count(), pid, tid, id, cat,
                               format_args(args));
        default: // TODO
            return fmt::format(R"({{"name": "{}", "ph": "{}", "ts": {}, "pid": {}, "tid": {}, "cat": "{}", "args": {}}})", name, static_cast<char>(type), ts.count(), pid, tid, id, cat,
                               format_args(args));
        }

        return {};
    }
};
} // namespace detail

template<typename T>
concept SimpleEvent = requires(T e) {
    { e.finish() } -> std::same_as<void>;
};

template<typename T>
concept StepEvent = requires(T e) {
    { e.finish() } -> std::same_as<void>;
    { e.step() } -> std::same_as<void>;
};

template<typename T>
concept Profiler = requires(T p, std::string_view name, std::string_view categories, std::initializer_list<arg_value> args) {
    { p.reset() } -> std::same_as<void>;
    { p.start_duration_event(name, categories, args) } -> SimpleEvent;
    { p.start_complete_event(name, categories, args) } -> SimpleEvent;
    { p.start_async_event(name, categories, args) } -> StepEvent;
    { p.instant_event(name, categories, args) } -> std::same_as<void>;
    { p.counter_event(name, categories, args) } -> std::same_as<void>;
};

namespace null {
class step_event {
public:
    constexpr void
    step() const noexcept {}

    constexpr void
    finish() const noexcept {}
};

class simple_event {
public:
    constexpr void
    finish() const noexcept {}
};

class profiler {
public:
    constexpr void
    reset() const {}

    constexpr void
    instant_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) const noexcept {
        std::ignore = name;
        std::ignore = categories;
        std::ignore = args;
    }

    constexpr void
    counter_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) const noexcept {
        std::ignore = name;
        std::ignore = categories;
        std::ignore = args;
    }

    [[nodiscard]] constexpr simple_event
    start_duration_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) const noexcept {
        std::ignore = name;
        std::ignore = categories;
        std::ignore = args;
        return simple_event{};
    }

    [[nodiscard]] constexpr simple_event
    start_complete_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) const noexcept {
        std::ignore = name;
        std::ignore = categories;
        std::ignore = args;
        return simple_event{};
    }

    [[nodiscard]] constexpr step_event
    start_async_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) const noexcept {
        std::ignore = name;
        std::ignore = categories;
        std::ignore = args;
        return step_event{};
    }
};
} // namespace null

template<typename Profiler>
class duration_event {
    Profiler              &_profiler;
    std::string            _name;
    std::string            _categories;
    std::vector<arg_value> _args;
    bool                   _finished = false;
    detail::time_point     _start    = detail::clock::now();

public:
    explicit duration_event(Profiler &profiler, std::string_view name, std::string_view categories, std::initializer_list<arg_value> args)
        : _profiler(profiler), _name{ name }, _categories{ categories }, _args{ args } {
        auto r    = _profiler.reserve_event();
        r[0].name = _name;
        r[0].type = detail::EventType::DurationBegin;
        r[0].cat  = _categories;
        r[0].args = _args;
        r.publish(1);
    }

    ~duration_event() { finish(); }

    duration_event(const duration_event &) = delete;
    duration_event &
    operator=(const duration_event &)
            = delete;
    duration_event(duration_event &&) noexcept = default;
    duration_event &
    operator=(duration_event &&) noexcept
            = default;

    void
    finish() noexcept {
        if (_finished) {
            return;
        }
        auto r    = _profiler.reserve_event();
        r[0].type = detail::EventType::DurationEnd;
        r.publish(1);
        _finished = true;
    }
};

template<typename Profiler>
class complete_event {
    Profiler              &_profiler;
    std::string            _name;
    std::string            _categories;
    std::vector<arg_value> _args;
    bool                   _finished = false;
    detail::time_point     _start    = detail::clock::now();

public:
    explicit complete_event(Profiler &profiler, std::string_view name, std::string_view categories, std::initializer_list<arg_value> args)
        : _profiler(profiler), _name{ name }, _categories{ categories }, _args{ args } {}

    ~complete_event() { finish(); }

    complete_event(const complete_event &) = delete;
    complete_event &
    operator=(const complete_event &)
            = delete;
    complete_event(complete_event &&) noexcept = default;
    complete_event &
    operator=(complete_event &&) noexcept
            = default;

    void
    finish() noexcept {
        if (_finished) {
            return;
        }
        const auto elapsed = detail::clock::now() - _start;
        auto       r       = _profiler.reserve_event();
        r[0].name          = _name;
        r[0].type          = detail::EventType::Complete;
        r[0].dur           = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
        r[0].cat           = _categories;
        r[0].args          = _args;
        r.publish(1);
        _finished = true;
    }
};

template<typename Profiler>
class async_event {
    Profiler   &_profiler;
    bool        _finished = false;
    std::string _id;
    std::string _name;

public:
    explicit async_event(Profiler &profiler, std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) : _profiler(profiler), _name{ name } {
        // TODO generate ID or pass as argument?
        post_event(detail::EventType::AsyncStart, categories, args);
    }

    ~async_event() { finish(); }

    async_event(const async_event &) = delete;
    async_event &
    operator=(const async_event &)
            = delete;
    async_event(async_event &&) noexcept = default;
    async_event &
    operator=(async_event &&) noexcept
            = default;

    void
    step() noexcept {
        post_event(detail::EventType::AsyncStep);
    }

    void
    finish() noexcept {
        if (_finished) {
            return;
        }
        post_event(detail::EventType::AsyncEnd);
        _finished = true;
    }

private:
    void
    post_event(detail::EventType type, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) noexcept {
        auto r    = _profiler.reserve_event();
        r[0].name = _name;
        r[0].type = type;
        r[0].id   = _id;
        r[0].cat  = std::string{ categories };
        r[0].args = args;
        r.publish(1);
    }
};

struct options {
    std::string output_file;
};

class profiler {
    gr::circular_buffer<detail::TraceEvent> _buffer;
    decltype(_buffer.new_writer())          _writer   = _buffer.new_writer();
    decltype(_buffer.new_reader())          _reader   = _buffer.new_reader();

    std::atomic<bool>                       _finished = false;
    std::jthread                            _eventHandler;
    detail::time_point                      _start = detail::clock::now();

public:
    explicit profiler(const options &options = {}) : _buffer(500000) {
        _eventHandler = std::jthread([options, &reader = _reader, &finished = _finished]() {
            auto file_name = options.output_file;
            if (file_name.empty()) {
                static std::atomic<int> counter = 0;
                file_name                       = fmt::format("profile.{}.{}.trace", getpid(), counter++);
            }
            auto out_file = std::ofstream(file_name, std::ios::out | std::ios::binary);
            int  pid      = getpid();

            // assign numerical values to threads as we see them
            std::unordered_map<std::thread::id, int> mapped_threads;
            bool                                     seen_finished = false;

            fmt::print(out_file, "[\n");
            bool is_first = true;
            while (!seen_finished) {
                seen_finished = finished;
                while (reader.available() > 0) {
                    auto event = reader.get(1);
                    auto it    = mapped_threads.find(event[0].thread_id);
                    if (it == mapped_threads.end()) {
                        it = mapped_threads.insert({ event[0].thread_id, static_cast<int>(mapped_threads.size()) }).first;
                    }
                    if (!is_first) {
                        fmt::print(out_file, ",\n{}", event[0].toJSON(pid, it->second));
                    } else {
                        fmt::print(out_file, "{}", event[0].toJSON(pid, it->second));
                    }
                    is_first    = false;
                    std::ignore = reader.consume(1);
                }
            }
            fmt::print(out_file, "\n]\n");
        });

        reset();
    }

    ~profiler() { _finished = true; }

    void
    reset() noexcept {
        _start = detail::clock::now();
    }

    auto
    reserve_event() noexcept {
        const auto elapsed = detail::clock::now() - _start;
        auto       r       = _writer.reserve_output_range(1);
        r[0].thread_id     = std::this_thread::get_id();
        r[0].ts            = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
        return r;
    }

    void
    instant_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) noexcept {
        auto r    = reserve_event();
        r[0].name = std::string{ name };
        r[0].type = detail::EventType::Instant;
        r[0].cat  = std::string{ categories };
        r[0].args = args;
        r.publish(1);
    }

    void
    counter_event(std::string_view name, std::string_view categories, std::initializer_list<arg_value> args = {}) noexcept {
        auto r    = reserve_event();
        r[0].name = std::string{ name };
        r[0].type = detail::EventType::Counter;
        r[0].cat  = std::string{ categories };
        r[0].args = args;
        r.publish(1);
    }

    [[nodiscard]] duration_event<profiler>
    start_duration_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) noexcept {
        return duration_event<profiler>{ *this, name, categories, args };
    }

    [[nodiscard]] complete_event<profiler>
    start_complete_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) noexcept {
        return complete_event<profiler>{ *this, name, categories, args };
    }

    [[nodiscard]] async_event<profiler>
    start_async_event(std::string_view name, std::string_view categories = {}, std::initializer_list<arg_value> args = {}) noexcept {
        return async_event<profiler>{ *this, name, categories, args };
    }
};

} // namespace flow::graph::profiling

#endif // include guard
