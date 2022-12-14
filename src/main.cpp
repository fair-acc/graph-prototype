#include <array>
#include <fmt/core.h>

#include <cassert>

#include "graph.hpp"

namespace fg = fair::graph;

template<typename T, int Depth>
    requires(Depth > 0)
class delay : public fg::node<delay<T, Depth>, fg::in<"in", T>, fg::out<"out", T>> {
    std::array<T, Depth> buffer = {};
    int                  pos    = 0;

public:
    [[nodiscard]] constexpr T
    process_one(T in) noexcept {
        T ret       = buffer[pos];
        buffer[pos] = in;
        if (pos == Depth - 1) {
            pos = 0;
        } else {
            ++pos;
        }
        return ret;
    }
};

template<typename T, int Count = 2>
class duplicate : public fg::node<
                             duplicate<T, Count>,
                             fair::meta::typelist<fg::in<"in", T>>,
                             fg::repeated_ports<Count, fg::port_direction::out, "out", T>> {

    using base = fg::node<
                     duplicate<T, Count>,
                     fair::meta::typelist<fg::in<"in", T>>,
                     fg::repeated_ports<Count, fg::port_direction::out, "out", T>>;

public:
    using return_type = typename base::return_type;

    [[nodiscard]] constexpr return_type
    process_one(T a) const noexcept {
        return [&a]<std::size_t... Is>(std::index_sequence<Is...>) {
            return std::make_tuple(((void) Is, a)...);
        }(std::make_index_sequence<Count>());
    }
};

template<typename T, typename R = decltype(std::declval<T>() + std::declval<T>())>
class adder : public fg::node<adder<T>, fg::in<"addend0", T>, fg::in<"addend1", T>, fg::out<"sum", R>> {
public:
    template<fg::detail::t_or_simd<T> V>
    [[nodiscard]] constexpr auto
    process_one(V a, V b) const noexcept {
        return a + b;
    }
};

template<typename T, T Scale, typename R = decltype(std::declval<T>() * std::declval<T>())>
class scale : public fg::node<scale<T, Scale, R>, fg::in<"original", T>, fg::out<"scaled", R>> {
public:
    template<fg::detail::t_or_simd<T> V>
    [[nodiscard]] constexpr auto
    process_one(V a) const noexcept {
        return a * Scale;
    }
};

int
main() {
    using fg::merge_by_index;
    using fg::merge;

    {
        // declare flow-graph: 2 x in -> adder -> scale-by-2 -> scale-by-minus1 -> output
        auto merged = merge_by_index<0, 0>(scale<int, -1>(), merge_by_index<0, 0>(scale<int, 2>(), adder<int>()));

        // execute graph
        std::array<int, 4> a = { 1, 2, 3, 4 };
        std::array<int, 4> b = { 10, 10, 10, 10 };

        int                r = 0;
        for (int i = 0; i < 4; ++i) {
            r += merged.process_one(a[i], b[i]);
        }

        fmt::print("Result of graph execution: {}\n", r);

        assert(r == 20);
    }

    {
        auto merged = merge_by_index<0, 0>(duplicate<int, 2>(), scale<int, 2>());

        // execute graph
        std::array<int, 4> a = { 1, 2, 3, 4 };
        std::array<int, 4> b = { 10, 10, 10, 10 };

        int                r = 0;
        for (int i = 0; i < 4; ++i) {
            auto tuple = merged.process_one(a[i]);
            auto [r1, r2] = tuple;
            fmt::print("{} {} \n", r1, r2);
        }
    }

    {
        auto merged = merge<"scaled", "addend1">(scale<int, 2>(), adder<int>());

        // execute graph
        std::array<int, 4> a = { 1, 2, 3, 4 };
        std::array<int, 4> b = { 10, 10, 10, 10 };

        int                r = 0;
        for (int i = 0; i < 4; ++i) {
            r += merged.process_one(a[i], b[i]);
        }

        fmt::print("Result of graph execution: {}\n", r);

        assert(r == 60);
    }

    {
        auto merged = merge_by_index<1,0>(merge_by_index<0, 0>(duplicate<int, 4>(), scale<int, 2>()), scale<int, 2>());

        // execute graph
        std::array<int, 4> a = { 1, 2, 3, 4 };
        std::array<int, 4> b = { 10, 10, 10, 10 };

        int                r = 0;
        for (int i = 0; i < 4; ++i) {
            auto tuple = merged.process_one(a[i]);
            auto [r1, r2, r3, r4] = tuple;
            fmt::print("{} {} {} {} \n", r1, r2, r3, r4);
        }
    }

    {
        auto delayed = delay<int, 2>{};
    }

}
