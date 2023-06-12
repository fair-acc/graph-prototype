#include <boost/ut.hpp>

#include <graph.hpp>
#include <node.hpp>
#include <scheduler.hpp>
#include <tag.hpp>

#include "blocklib/core/sources/clock_source.hpp"
#include "blocklib/core/unit-test/tag_monitors.hpp"

#include <ctime>

#if defined(__clang__) && __clang_major__ >= 15
// clang 16 does not like ut's default reporter_junit due to some issues with stream buffers and output redirection
template<>
auto boost::ut::cfg<boost::ut::override> = boost::ut::runner<boost::ut::reporter<>>{};
#endif

const boost::ut::suite TagTests = [] {
    using namespace boost::ut;
    using namespace fair::graph;
    using namespace fair::graph::sources;
    using namespace fair::graph::tag_test;

    "tag_source"_test = [] {
        const std::uint64_t n_samples   = 1900;
        const float         sample_rate = 2000.f;
        graph               flow_graph;
        auto               &src = flow_graph.make_node<fair::graph::sources::ClockSource<float>>({ { "sample_rate", sample_rate }, { "n_samples_max", n_samples }, { "name", "TagSource" } });
        src.tags                = {
            // TODO: allow parameter settings to include maps?!?
            { 0, { { "key", "value@0" } } },       //
            { 1, { { "key", "value@1" } } },       //
            { 100, { { "key", "value@100" } } },   //
            { 150, { { "key", "value@150" } } },   //
            { 1000, { { "key", "value@1000" } } }, //
            { 1001, { { "key", "value@1001" } } }, //
            { 1002, { { "key", "value@1002" } } }, //
            { 1023, { { "key", "value@1023" } } }  //
        };
        auto &sink1 = flow_graph.make_node<TagSink<float, ProcessFunction::USE_PROCESS_BULK>>({ { "name", "TagSink1" } });
        auto &sink2 = flow_graph.make_node<TagSink<float, ProcessFunction::USE_PROCESS_ONE>>({ { "name", "TagSink2" } });
        expect(eq(connection_result_t::SUCCESS, flow_graph.connect<"out">(src).to<"in">(sink1)));
        expect(eq(connection_result_t::SUCCESS, flow_graph.connect<"out">(src).to<"in">(sink2)));

        scheduler::simple sched{ std::move(flow_graph) };
        sched.run_and_wait();

        expect(eq(src.n_samples_produced, n_samples)) << "src did not produce enough output samples";
        expect(eq(static_cast<std::uint64_t>(sink1.n_samples_produced), n_samples)) << "sink1 did not consume enough input samples";
        expect(eq(static_cast<std::uint64_t>(sink1.n_samples_produced), n_samples)) << "sink2 did not consume enough input samples";
        expect(approx(sink1.effective_sample_rate(), sample_rate, 500.f)) << "effective sample rate does not match";
        expect(approx(sink2.effective_sample_rate(), sample_rate, 500.f)) << "effective sample rate does not match";

        auto equal_tag_lists = [](const std::vector<tag_t> &tags1, const std::vector<tag_t> &tags2) {
            if (tags1.size() != tags2.size()) {
                fmt::print("vectors have different sizes ({} vs {})\n", tags1.size(), tags2.size());
                return false;
            }

            if (const auto [mismatchedTag1, mismatchedTag2] = std::mismatch(tags1.begin(), tags1.end(), tags2.begin(), std::equal_to<>()); mismatchedTag1 != tags1.end()) {
                const auto index = static_cast<size_t>(std::distance(tags1.begin(), mismatchedTag1));
                fmt::print("mismatch at index {}", index);
                if (mismatchedTag1->index != mismatchedTag2->index) {
                    fmt::print("  - different index: {} vs {}\n", mismatchedTag1->index, mismatchedTag2->index);
                }
                if (mismatchedTag1->map != mismatchedTag2->map) {
                    fmt::print("  - different map content:\n");
                    for (const auto &[key, value] : mismatchedTag1->map) {
                        if (!mismatchedTag2->map.contains(key)) {
                            fmt::print("    key '{}' is present in the first map but not in the second\n", key);
                        } else if (mismatchedTag2->map.at(key) != value) {
                            fmt::print("    key '{}' has different values ('{}' vs '{}')\n", key, value, mismatchedTag2->map.at(key));
                        }
                    }
                    for (const auto &[key, value] : mismatchedTag2->map) {
                        if (!mismatchedTag1->map.contains(key)) {
                            fmt::print("    key '{}' is present in the second map but not in the first\n", key);
                        }
                    }
                }
                return false;
            }

            return true;
        };

        expect(equal_tag_lists(src.tags, sink1.tags)) << "sink1 did not receive the required tags";
        expect(equal_tag_lists(src.tags, sink2.tags)) << "sink1 did not receive the required tags";
    };
};

class CustomClock {
public:
    using rep                       = int64_t;
    using period                    = std::nano;
    using duration                  = std::chrono::duration<rep, period>;
    using time_point                = std::chrono::time_point<CustomClock>;

    static constexpr bool is_steady = false;

    static time_point
    now() noexcept {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts); // POSIX call to get the time
        return time_point(duration(static_cast<rep>(ts.tv_sec) * 1000000000 + ts.tv_nsec));
    }

    static void
    waitForTimePoint(const time_point &tp) {
        fmt::print("called me\n");
        time_point now_tp = now();
        if (tp > now_tp) {
            duration sleep_duration = tp - now_tp;
            std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_duration.count()));
        }
    }

    // additional functionality for custom clock such as meta-information retrieval
    // get last meta-info
};

int
main() { /* not needed for UT */
}
