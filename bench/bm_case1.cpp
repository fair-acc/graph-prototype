#include "benchmark.hpp"

#include <algorithm>
#include <boost/ut.hpp>
#include <functional>

#include <graph.hpp>

// #define RUN_SIMD_TESTS

inline constexpr std::size_t N_ITER = 1;
inline constexpr std::size_t N_SAMPLES = 1'000'000;

#ifndef __EMSCRIPTEN__
auto
this_source_location(std::source_location l = std::source_location::current()) {
    return fmt::format("{}:{},{}", l.file_name(), l.line(), l.column());
}
#else
auto
this_source_location() {
    return "not yet implemented";
}
#endif // __EMSCRIPTEN__

namespace fg                       = fair::graph;
inline constexpr std::size_t N_MAX = std::numeric_limits<std::size_t>::max();

namespace test {
std::size_t n_samples_produced = 0LU;

template<typename T, std::size_t min = 0, std::size_t count = 8192, bool use_bulk_operation = true>
class source : public fg::node<source<T, min, count>, fg::OUT<T, "out">, fg::limits<min, count>> {
         using base = fg::node<source<T, min, count>, fg::OUT<T, "out">, fg::limits<min, count>>;
private:
    std::size_t _n_samples_max;

public:
    source(std::size_t n_samples, std::string name = this_source_location()) //
        : base(std::move(name))
        , _n_samples_max(n_samples) {}

    [[nodiscard]] constexpr T
    process_one() const noexcept {
        n_samples_produced++;
        return T{};
    }

    fair::graph::work_result
    work() {
        const std::size_t n_to_publish = _n_samples_max - n_samples_produced;
        if (n_to_publish > 0) {
            auto &port   = base::template port<fair::graph::port_direction_t::OUTPUT, "out">();
            auto &writer = port.writer();

            if constexpr (use_bulk_operation) {
                std::size_t n_write = std::clamp(n_to_publish, 0UL, std::min(writer.available(), port.max_buffer_size()));
                if (n_write == 0) {
                    return fair::graph::work_result::error;
                }
                auto [data, token] = writer.get(n_write);
                for (auto& item: data) {
                    item = process_one();
                }
                writer.publish(token, n_write);
                // TODO: This API doesn't work, investigate
                // writer.publish(
                //         [this](std::span<T> output) {
                //             throw "NOT CALLED";
                //             for (auto &val : output) {
                //                 if (fair::graph::global_work_debug)
                //                     fmt::print("    calling process_one\n");
                //                 val = process_one();
                //             }
                //         },
                //         n_write);
            } else {
                auto [data, token] = writer.get(1);
                if (data.size() == 0) {
                    return fair::graph::work_result::error;
                }
                data[0] = process_one();
                writer.publish(token, 1);
            }
            return fair::graph::work_result::success;
        } else {
            return fair::graph::work_result::inputs_empty;
        }
    }
};

std::size_t n_samples_consumed = 0LU;

template<typename T, std::size_t N_MIN = 0, std::size_t N_MAX = N_MAX>
class sink : public fg::node<sink<T, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>> {
       using base = fg::node<sink<T, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>>;
public:
    sink(std::string name = this_source_location()) //
        : base(std::move(name)) {}

    template<fair::meta::t_or_simd<T> V>
    [[nodiscard]] constexpr auto
    process_one(V a) const noexcept {
        n_samples_consumed++;
        benchmark::do_not_optimize(a);
    }
};

} // namespace test

template<typename T, std::size_t N_MIN = 0, std::size_t N_MAX = N_MAX>
class copy : public fg::node<copy<T, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::OUT<T, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>> {
       using base = fg::node<copy<T, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::OUT<T, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>>;
public:
    copy(std::string name = this_source_location()) //
        : base(std::move(name)) {}

    template<fair::meta::t_or_simd<T> V>
    [[nodiscard]] constexpr T
    process_one(V a) const noexcept {
        return a;
    }
};

template<typename T1, typename T2, std::size_t N_MIN = 0, std::size_t N_MAX = N_MAX>
class convert : public fg::node<convert<T1, T2, N_MIN, N_MAX>, fg::IN<T1, "in", N_MIN, N_MAX>, fg::OUT<T2, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>> {
          using base = fg::node<convert<T1, T2, N_MIN, N_MAX>, fg::IN<T1, "in", N_MIN, N_MAX>, fg::OUT<T2, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>>;
public:
    convert(std::string name = this_source_location()) //
        : base(std::move(name)) {}

    template<fair::meta::t_or_simd<T1> V>
    [[nodiscard]] constexpr T2
    process_one(V a) const noexcept {
        return a;
    }
};

template<typename T, int addend, std::size_t N_MIN = 0, std::size_t N_MAX = N_MAX>
class add : public fg::node<add<T, addend, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::OUT<T, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>> {
      using base = fg::node<add<T, addend, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::OUT<T, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>>;
public:
    add(std::string name = this_source_location()) //
        : base(std::move(name)) {}

    template<fair::meta::t_or_simd<T> V>
    [[nodiscard]] constexpr T
    process_one(V a) const noexcept {
        return a + addend;
    }
};

template<typename T, std::size_t N_MIN = 0, std::size_t N_MAX = N_MAX>
class multiply : public fg::node<multiply<T, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::OUT<T, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>> {
           using base = fg::node<multiply<T, N_MIN, N_MAX>, fg::IN<T, "in", N_MIN, N_MAX>, fg::OUT<T, "out", N_MIN, N_MAX>, fg::limits<N_MIN, N_MAX>>;
    T _factor = static_cast<T>(1.0f);

public:
    multiply(std::string name = this_source_location()) //
        : base(std::move(name)) {}

    multiply() = delete;

    explicit multiply(T factor, std::string name = this_source_location()) : base(name), _factor(factor) {}

    template<fair::meta::t_or_simd<T> V>
    [[nodiscard]] constexpr T
    process_one(V a) noexcept {
        return a * _factor;
    }
};

template<std::size_t N, typename base, typename aggregate>
constexpr auto
cascade(
        aggregate &&src, std::function<base()> generator = [] { return base(); }) {
    if constexpr (N <= 1) {
        return src;
    } else {
        return cascade<N - 1, base>(fair::graph::merge_by_index<0, 0>(std::forward<aggregate>(src), generator()), generator);
    }
}

inline const boost::ut::suite _constexpr_bm = [] {
    using namespace boost::ut;
    using namespace benchmark;
    using fair::graph::merge_by_index;
    using fair::graph::merge;

    {
        auto merged_node = merge<"out", "in">(test::source<float>(N_SAMPLES), test::sink<float>());
        //
        "constexpr src->sink overhead V1"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };

        "constexpr src->sink overhead V2"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.work();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }

    {
        auto merged_node = merge<"out", "in">(merge<"out", "in">(test::source<float>(N_SAMPLES), copy<float>()), test::sink<float>());
        //
        "constexpr src->copy->sink V1"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };

        "constexpr src->copy->sink V2"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.work();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }

    {
        auto merged_node = merge<"out", "in">(merge<"out", "in">(test::source<float>(N_SAMPLES), cascade<10, copy<float>>(copy<float>())), test::sink<float>());
        "constexpr src->copy^10->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }

#ifdef RUN_SIMD_TESTS
    using std::experimental::fixed_size_simd;
    using std::experimental::simd;
    using std::experimental::native_simd;
    using float_simd = native_simd<float>;
    fmt::print(stderr, "float_simd::size() = {}\n", float_simd::size());
    {
        auto merged_node = merge<"out", "in">(merge<"out", "in">(merge<"out", "in">(test::source<float>(N_SAMPLES), convert<float, float_simd>()), copy<float_simd>()), test::sink<float_simd>());
        "constexpr src->copy->sink (SIMD)"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }

    {
        auto merged_node = merge<"out", "in">(merge<"out", "in">(test::source<float_simd>(N_SAMPLES), cascade<10, copy<float_simd>>(copy<float_simd>())), test::sink<float_simd>());
        "constexpr src->copy^10->sink (SIMD)"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }
#endif // - #RUN_SIMD_TESTS

    {
        auto merged_node = merge<"out", "in">(merge<"out", "in">(merge<"out", "in">(merge<"out", "in">(test::source<float, 1024, 1024>(N_SAMPLES), copy<float, 0, 128>()), copy<float, 0, 1024>()),
                                                                 copy<float, 32, 128>()),
                                              test::sink<float>());
        "constexpr src(N=1024)->b1(N≤128)->b2(N=1024)->b3(N=32...128)->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }

    {
        auto gen_mult_block_float = [] { return merge<"out", "in">(multiply<float>(2.0f), merge<"out", "in">(multiply<float>(0.5f), add<float, -1>())); };
        auto merged_node          = merge<"out", "in">(merge<"out", "in">(test::source<float>(N_SAMPLES), gen_mult_block_float()), test::sink<float>());
        "constexpr src->mult(2.0)->mult(0.5)->add(-1)->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }

    {
        auto gen_mult_block_float = [] { return merge<"out", "in">(multiply<float>(2.0f), merge<"out", "in">(multiply<float>(0.5f), add<float, -1>())); };
        auto merged_node          = merge<"out", "in">(merge<"out", "in">(test::source<float>(N_SAMPLES), //
                                                                 cascade<10, decltype(gen_mult_block_float())>(gen_mult_block_float(), gen_mult_block_float)),
                                              test::sink<float>());
        "constexpr src->(mult(2.0)->mult(0.5)->add(-1))^10->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&merged_node]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            for (std::size_t i = 0; i < N_SAMPLES; i++) {
                merged_node.process_one();
            }
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough samples";
        };
    }
#ifdef RUN_SIMD_TESTS
    auto src_constraint_sink_SIMD = merge<"out", "in">(merge<"out", "in">(merge<"out", "in">(merge<"out", "in">(test::source<float_simd, 1024, 1024>(N_SAMPLES), copy<float_simd, 0, 128>()),
                                                                                             copy<float_simd, 0, 1024>()),
                                                                          copy<float_simd, 32, 128>()),
                                                       test::sink<float_simd>());
    "constexpr src(N=1024)->b1(N≤128)->b2(N=1024)->b3(N=32...128)->sink (SIMD)"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&src_constraint_sink_SIMD]() { src_constraint_sink_SIMD.process_one(); };

    auto gen_mult_block_simd_float = [] { return merge<"out", "in">(multiply<float_simd>(2.0f), merge<"out", "in">(multiply<float_simd>(0.5f), add<float_simd, -1>())); };

    auto src_mult_sink_SIMD        = merge<"out", "in">(merge<"out", "in">(test::source<float_simd>(N_SAMPLES), gen_mult_block_simd_float()), test::sink<float_simd>());
    "constexpr src->mult(2.0)->mult(0.5)->add(-1)->sink (SIMD)"_benchmark.repeat<N_ITER, N_SAMPLES>()      = [&src_mult_sink_SIMD]() { src_mult_sink_SIMD.process_one(); };

    auto src_mult_n_sink_SIMD                                                                              = merge<"out", "in">(merge<"out", "in">(test::source<float_simd>(N_SAMPLES),
                                                                      cascade<10, decltype(gen_mult_block_simd_float())>(gen_mult_block_simd_float(), gen_mult_block_simd_float)),
                                                   test::sink<float_simd>());
    "constexpr src->(mult(2.0)->mult(0.5)->add(-1))^10->sink (SIMD)"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&src_mult_n_sink_SIMD]() { src_mult_n_sink_SIMD.process_one(); };

#endif // - #RUN_SIMD_TESTS
};

inline const boost::ut::suite _runtime_tests = [] {
    using namespace boost::ut;
    using namespace benchmark;

    {
        test::source<float> src(N_SAMPLES);
        test::sink<float>   sink;

        fg::graph           flow_graph;
        flow_graph.register_node(src);
        flow_graph.register_node(sink);
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, sink)));

        "runtime   src->sink overhead"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph, &src, &sink]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            flow_graph.work();
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough output samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough input samples";
        };
    }

    {
        test::source<float> src(N_SAMPLES);
        test::sink<float>   sink;
        copy<float>         cpy;

        fg::graph           flow_graph;
        flow_graph.register_node(src);
        flow_graph.register_node(cpy);
        flow_graph.register_node(sink);
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, cpy)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(cpy, sink)));
        "runtime   src->copy->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph, &src, &sink]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            flow_graph.work();
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough output samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough input samples";
        };
    }

    {
        test::source<float> src(N_SAMPLES);
        test::sink<float>   sink;

        fg::graph           flow_graph;
        flow_graph.register_node(src);
        flow_graph.register_node(sink);

        std::vector<copy<float>> cpy(10);

        //
        // src
        //  |
        //  v
        //  c0 -> c1 -> ... -> cn
        //                     |
        //                     v
        //                     sink
        //

        for (std::size_t i = 0; i < cpy.size(); i++) {
            cpy[i].set_name(fmt::format("copy {} at {}", i, this_source_location()));
            flow_graph.register_node(cpy[i]);

            if (i == 0) {
                expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, cpy[i])));
            } else {
                expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(cpy[i - 1], cpy[i])));
            }
        }

        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(cpy[cpy.size() - 1], sink)));

        "runtime   src->copy^10->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph, &src]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            flow_graph.work();
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough output samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough input samples";
        };
    }

#ifdef RUN_SIMD_TESTS
    using std::experimental::fixed_size_simd;
    using std::experimental::simd;
    using std::experimental::native_simd;
    using float_simd = native_simd<float>;

    {
        test::source<float_simd> src(N_SAMPLES);
        test::sink<float_simd>   sink;
        copy<float_simd>         cpy;

        fg::graph                flow_graph;
        flow_graph.register_node(src);
        flow_graph.register_node(cpy);
        flow_graph.register_node(sink);
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, cpy)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(cpy, sink)));
        "runtime   src->copy->sink SIMD"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph]() { flow_graph.work(); };
    }

    {
        test::source<float_simd> src(N_SAMPLES);
        test::sink<float_simd>   sink;

        fg::graph                flow_graph;
        flow_graph.register_node(src);

        std::vector<copy<float_simd>> cpy(10);
        for (std::size_t i = 0LU; i < cpy.size(); i++) {
            flow_graph.register_node(cpy[i]);
            if (i == 0) {
                expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, cpy[i])));
            } else {
                expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(cpy[i], cpy[i - 1])));
            }
        }

        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(cpy[cpy.size() - 1], sink)));

        "runtime   src->copy^10->sink SIMD"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph]() { flow_graph.work(); };
    }

#endif // RUN_SIMD_TESTS

    {
        test::source<float, 0, 1024> src(N_SAMPLES);
        copy<float, 0, 128>          b1;
        copy<float, 1024, 1024>      b2;
        copy<float, 32, 128>         b3;
        test::sink<float>            sink;

        fg::graph                    flow_graph;
        flow_graph.register_node(src);
        flow_graph.register_node(b1);
        flow_graph.register_node(b2);
        flow_graph.register_node(b3);
        flow_graph.register_node(sink);
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, b1)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(b1, b2)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(b2, b3)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(b3, sink)));
        "runtime   src(N=1024)->b1(N≤128)->b2(N=1024)->b3(N=32...128)->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            flow_graph.work();
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough output samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough input samples";
        };
    }

    {
        test::source<float> src(N_SAMPLES);
        multiply<float>     mult1(2.0f);
        multiply<float>     mult2(0.5f);
        add<float, -1>      add1;
        test::sink<float>   sink;

        fg::graph           flow_graph;
        flow_graph.register_node(src);
        flow_graph.register_node(mult1);
        flow_graph.register_node(mult2);
        flow_graph.register_node(add1);
        flow_graph.register_node(sink);
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, mult1)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(mult1, mult2)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(mult2, add1)));
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(add1, sink)));
        "runtime   src->mult(2.0)->mult(0.5)->add(-1)->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            flow_graph.work();
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough output samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough input samples";
        };
    }

    {
        test::source<float> src(N_SAMPLES);
        test::sink<float>   sink;

        fg::graph           flow_graph;
        flow_graph.register_node(src);

        std::vector<multiply<float>> mult1;
        std::vector<multiply<float>> mult2;
        std::vector<add<float, -1>>  add1(10);
        for (std::size_t i = 0; i < add1.size(); i++) {
            mult1.emplace_back(2.0f);
            mult2.emplace_back(0.5f);
            add1[i].set_name(fmt::format("add1.{}", i));
            mult1[i].set_name(fmt::format("mult1.{}", i));
            mult2[i].set_name(fmt::format("mult2.{}", i));
        }

        for (std::size_t i = 0; i < add1.size(); i++) {
            flow_graph.register_node(mult1[i]);
            flow_graph.register_node(mult2[i]);
            flow_graph.register_node(add1[i]);
        }

        //
        //  src
        //  |
        //  v
        //  m0     m1     m2     m3     m4     m5     m6
        //  |     /|     /|     /|     /|     /|     /|
        //  |    v |    v |    v |    v |    v |    v |
        //  |  a0  |  a1  |  a2  |  a3  |  a4  |  a5  |  a6
        //  |  ^   |  ^   |  ^   |  ^   |  ^   |  ^   | ^ |
        //  v /    v /    v /    v /    v /    v /    v/  |
        //  M0     M1     M2     M3     M4     M5     M6  |
        //                                                v
        //                                                sink
        //
        for (std::size_t i = 0; i < add1.size(); i++) {
            if (i == 0) {
                expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(src, mult1[i])));
            } else {
                expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(mult1[i], add1[i - 1])));
            }
            expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(mult1[i], mult2[i])));
            expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(mult2[i], add1[i])));
        }
        expect(eq(fg::connection_result_t::SUCCESS, flow_graph.connect<"out", "in">(add1[add1.size() - 1], sink)));

        skip / "runtime   src->(mult(2.0)->mult(0.5)->add(-1))^10->sink"_benchmark.repeat<N_ITER, N_SAMPLES>() = [&flow_graph]() {
            test::n_samples_produced = 0LU;
            test::n_samples_consumed = 0LU;
            flow_graph.work();
            expect(eq(test::n_samples_produced, N_SAMPLES)) << "did not produce enough output samples";
            expect(eq(test::n_samples_consumed, N_SAMPLES)) << "did not consume enough input samples";
        };
    }
};

int
main() { /* not needed by the UT framework */
}
