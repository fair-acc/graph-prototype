#include <array>
#include <fmt/core.h>

#include "graph.hpp"

template<typename T, int Depth>
    requires(Depth > 0)
class delay : public fair::graph::node<delay<T, Depth>, fair::graph::make_input_ports<T>, fair::graph::make_output_ports<T>> {
    std::array<T, Depth> buffer = {};
    int                  pos    = 0;

public:
    [[nodiscard]] constexpr T process_one(T in) noexcept {
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

template<typename T, typename R = decltype(std::declval<T>() + std::declval<T>())>
class adder : public fair::graph::node<adder<T>, fair::graph::make_input_ports<T, T>, fair::graph::make_output_ports<R>> {
public:
    [[nodiscard]] constexpr R process_one(T a, T b) const noexcept { return a + b; }
};

template<typename T, T Scale, typename R = decltype(std::declval<T>() * std::declval<T>())>
class scale : public fair::graph::node<scale<T, Scale, R>, fair::graph::make_input_ports<T>, fair::graph::make_output_ports<R>> {
public:
    [[nodiscard]] constexpr R process_one(T a) const noexcept { return a * Scale; }
};




struct node_left {
    static constexpr size_t inputs_count = 4;
    const short in_power = 0;
    const short in_freq = 1;
    const short in_amplitude = 2;
    const short in_something = 3;
};

struct node_right {
    static constexpr size_t inputs_count = 8;
    const short in_power = 0;
    const short in_freq = 1;
    const short in_amplitude = 2;
    const short in_something = 3;
    const short in_power_backup = 4;
    const short in_freq_backup = 5;
    const short in_amplitude_backup = 6;
    const short in_something_backup = 7;

};

struct node_mid {
    static constexpr size_t inputs_count = 1;
    const short in_power = 0;
};

namespace detail {
template <typename Object, typename Type>
Object extract_object(Type Object::* o)
{
}

template <typename ...T>
struct error_print_types;
} // namespace detail

// Doesn't support merging nodes of the same type
template <typename Left, typename Right>
struct merged_node {
    static constexpr size_t inputs_count = Left::inputs_count + Right::inputs_count;
    using merged_node_tag = std::true_type;
    Left left;
    Right right;

    template <typename Accessor>
    constexpr auto index_of(Accessor accessor) {
        using owner = decltype(detail::extract_object(accessor));

        if constexpr (std::is_same_v<Left, owner>) {
            return (left.*accessor);

        } else if constexpr (std::is_same_v<Right, owner>) {
            return Left::inputs_count + (right.*accessor);

        } else if constexpr (requires { typename Left::merged_node_tag; }) {
            return left.index_of(accessor);

        } else if constexpr (requires { typename Right::merged_node_tag; }) {
            return Left::inputs_count + right.index_of(accessor);

        } else {
            return detail::error_print_types<merged_node<Left, Right>, owner, Accessor>{}; // Passed index accessor doesn't apply to this merged node
        }
    }
};





int main() {
    using fair::graph::merge;
    // declare flow-graph: 2 x in -> adder -> scale-by-2 -> scale-by-minus1 -> output
    auto merged = merge<0, 0>(scale<int, -1>(), merge<0, 0>(scale<int, 2>(), adder<int>()));

    // execute graph
    std::array<int, 4> a = { 1, 2, 3, 4 };
    std::array<int, 4> b = { 10, 10, 10, 10 };

    int                r = 0;
    for (int i = 0; i < 4; ++i) {
        auto [neg, scale, z] = merged.process_one(a[i], b[i]);
        r += z;
    }

    // TEST
    merged_node<node_left, node_right> x;
    fmt::print("Index : {} \n", x.index_of(&node_left::in_freq));
    fmt::print("Index : {} \n", x.index_of(&node_right::in_power));
    // ERROR: fmt::print("Index : {} \n", x.index_of(&node_mid::in_power));

    merged_node<node_left, merged_node<node_mid, node_right>> y;
    fmt::print("Index : {} \n", y.index_of(&node_left::in_freq));
    fmt::print("Index : {} \n", y.index_of(&node_right::in_power));
    fmt::print("Index : {} \n", y.index_of(&node_mid::in_power));


    return r == 20 ? 0 : 1;



}
