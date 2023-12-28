#include <boost/ut.hpp>

#include <gnuradio-4.0/meta/utils.hpp>

#include <gnuradio-4.0/Block.hpp>
#include <gnuradio-4.0/Graph.hpp>
#include <gnuradio-4.0/Scheduler.hpp>

#include <gnuradio-4.0/basic/clock_source.hpp>
#include <gnuradio-4.0/basic/FunctionGenerator.hpp>
#include <gnuradio-4.0/basic/StreamToDataSet.hpp>
#include <gnuradio-4.0/testing/ImChartMonitor.hpp>
#include <gnuradio-4.0/testing/TagMonitors.hpp>

namespace detail {

gr::property_map
timingTag(std::string_view eventName, std::string_view context) {
    return {};
}

} // namespace detail

const boost::ut::suite SelectorTest = [] {
    using namespace boost::ut;
    using namespace gr;
    using namespace gr::basic;
    using namespace gr::testing;
    constexpr static std::uint64_t n_samples = 1024;

    constexpr bool verbose_console = false;
    using namespace function_generator;
    constexpr std::uint64_t lengthSeconds = 20;
    constexpr std::uint32_t N             = 1000 * lengthSeconds;
    constexpr float         sample_rate   = 1'000.f;

    Graph graph;
    auto &clockSrc = graph.emplaceBlock<gr::basic::ClockSource<float>>({ { "sample_rate", sample_rate }, { "n_samples_max", N }, { "name", "ClockSource" } });

    auto addTimeTagEntry = []<typename T>(gr::basic::ClockSource<T> &clockSource, std::uint64_t timeInNanoseconds, const std::string &value) {
        clockSource.tag_times.push_back(timeInNanoseconds);
        clockSource.tag_values.push_back(value);
    };

    // all times are in nanoseconds
    constexpr std::uint64_t ms = 1'000'000; // ms -> ns conversion factor (wish we had a proper C++ units-lib integration)
    addTimeTagEntry(clockSrc, 10 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=1");
    addTimeTagEntry(clockSrc, 100 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=2");
    addTimeTagEntry(clockSrc, 300 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=3");
    addTimeTagEntry(clockSrc, 350 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=4");
    addTimeTagEntry(clockSrc, 550 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=5");
    addTimeTagEntry(clockSrc, 650 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=6");
    addTimeTagEntry(clockSrc, 800 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=7");
    addTimeTagEntry(clockSrc, 850 * ms, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=8");
    clockSrc.repeat_period      = 1000 * ms;
    clockSrc.do_zero_order_hold = true;
    auto &funcGen               = graph.emplaceBlock<FunctionGenerator<float>>({ { "sample_rate", sample_rate }, { "name", "FunctionGenerator" } });
    funcGen.match_pred          = [](const auto &tableEntry, const auto &searchEntry, const auto attempt) -> std::optional<bool> {
        if (searchEntry.find("context") == searchEntry.end()) {
            return std::nullopt;
        }
        if (tableEntry.find("context") == tableEntry.end()) {
            return false;
        }

        const pmtv::pmt searchEntryContext = searchEntry.at("context");
        const pmtv::pmt tableEntryContext  = tableEntry.at("context");
        if (std::holds_alternative<std::string>(searchEntryContext) && std::holds_alternative<std::string>(tableEntryContext)) {
            const auto searchString = std::get<std::string>(searchEntryContext);
            const auto tableString  = std::get<std::string>(tableEntryContext);

            if (!searchString.starts_with("CMD_BP_START:")) {
                return std::nullopt;
            }

            if (attempt >= searchString.length()) {
                return std::nullopt;
            }
            auto [it1, it2] = std::ranges::mismatch(searchString, tableString);
            if (std::distance(searchString.begin(), it1) == static_cast<std::ptrdiff_t>(searchString.length() - attempt)) {
                return true;
            }
        }
        return false;
    };

    using gr::tag::TRIGGER_NAME;
    using gr::tag::CONTEXT;
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=1" } }, createConstPropertyMap(5.f));
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=2" } }, createLinearRampPropertyMap(5.f, 30.f, 0.2f /* [s]*/));
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=3" } }, createConstPropertyMap(30.f));
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=4" } }, createParabolicRampPropertyMap(30.f, 20.f, .1f, 0.02f /* [s]*/));
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=5" } }, createConstPropertyMap(20.f));
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=6" } }, createCubicSplinePropertyMap(20.f, 10.f, 0.1f /* [s]*/));
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=7" } }, createConstPropertyMap(10.f));
//    funcGen.addFunctionTableEntry({ { TRIGGER_NAME, "CMD_BP_START" }, { CONTEXT, "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=8" } }, createImpulseResponsePropertyMap(10.f, 20.f, 0.02f /* [s]*/, 0.06f /* [s]*/));

    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=1" } }, createConstPropertyMap(5.f));
    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=2" } }, createLinearRampPropertyMap(5.f, 30.f, 0.2f /* [s]*/));
    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=3" } }, createConstPropertyMap(30.f));
    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=4" } }, createParabolicRampPropertyMap(30.f, 20.f, .1f, 0.02f /* [s]*/));
    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=5" } }, createConstPropertyMap(20.f));
    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=6" } }, createCubicSplinePropertyMap(20.f, 10.f, 0.1f /* [s]*/));
    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=7" } }, createConstPropertyMap(10.f));
    funcGen.addFunctionTableEntry({ { "context", "CMD_BP_START:FAIR.SELECTOR.C=1:S=1:P=8" } }, createImpulseResponsePropertyMap(10.f, 20.f, 0.02f /* [s]*/, 0.06f /* [s]*/));

    auto &sink = graph.emplaceBlock<TagSink<float, ProcessFunction::USE_PROCESS_ONE>>({ { "name", "SampleGeneratorSink" } });
    auto &uiSink = graph.emplaceBlock<testing::ImChartMonitor<float>>({ { "name", "ImChartSinkFull" } });
    expect(eq(ConnectionResult::SUCCESS, graph.connect<"out">(clockSrc).to<"in">(funcGen)));
    expect(eq(ConnectionResult::SUCCESS, graph.connect<"out">(funcGen).to<"in">(sink)));
    expect(eq(ConnectionResult::SUCCESS, graph.connect<"out">(funcGen).to<"in">(uiSink)));


    auto &filteredSink = graph.emplaceBlock<TagSink<float, ProcessFunction::USE_PROCESS_ONE>>({ { "name", "FilteredSink" }, { "verbose_console", verbose_console } });
    auto &block        = graph.emplaceBlock<StreamToDataSet<float>>({ { "name", "StreamToDataSet" } });
    expect(eq(gr::ConnectionResult::SUCCESS, graph.connect<"out">(funcGen).template to<"in">(block)));
    expect(eq(gr::ConnectionResult::SUCCESS, graph.connect<"out">(block).template to<"in">(filteredSink)));

    auto &uiSinkFiltered = graph.emplaceBlock<testing::ImChartMonitor<float>>({ { "name", "ImChartSinkFiltered" } });
    expect(eq(ConnectionResult::SUCCESS, graph.connect<"out">(block).to<"in">(uiSinkFiltered)));

    // <event name 1>:FAIR.SELECTOR.C=1:S=2:P=3:T=0
    // <event name 2>:FAIR.SELECTOR.C=4:S=5:P=6
    // <event name 3>:FAIR.SELECTOR.C=7:T=8
    // FAIR.SELECTOR.P=2
    // FAIR.SELECTOR.C=2
    // FAIR.SELECTOR.C=1:S=2
    // FAIR.SELECTOR.C=1:P=3
    // A:B:C:FAIR.SELECTOR.C=1:S=2:P=3:T=0
    // A:B:C:FAIR.SELECTOR.P=3
    // FAIR.SELECTOR.S=1:C=2

    std::thread uiLoop([&uiSink, &uiSinkFiltered]() {
        int i = 0;
        fmt::println("start UI thread");
        bool drawUI = true;
        while (drawUI) { // mocks UI update loop
            drawUI = false;
            drawUI |= uiSink.draw() != work::Status::DONE;
            drawUI |= uiSinkFiltered.draw(ResetChartView::KEEP) != work::Status::DONE;
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
        }
        fmt::println("asked to finish UI thread");
        std::this_thread::sleep_for(std::chrono::seconds(2)); // wait for another 2 seconds before closing down
        fmt::println("finished UI thread");
    });

    gr::scheduler::Simple sched{ std::move(graph) };
    sched.runAndWait();

    fmt::println("n_samples_produced = {}, n-tags = {} vs. {}", sink.n_samples_produced, sink.tags.size(), clockSrc.tags.size());
    uiLoop.join();
};

int
main() { /* not needed for UT */
}
