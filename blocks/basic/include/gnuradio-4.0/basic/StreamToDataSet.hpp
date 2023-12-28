#ifndef GNURADIO_STREAMTODATASET_HPP
#define GNURADIO_STREAMTODATASET_HPP

#include <gnuradio-4.0/Block.hpp>
#include <gnuradio-4.0/DataSet.hpp>
#include <gnuradio-4.0/HistoryBuffer.hpp>

#include <gnuradio-4.0/meta/utils.hpp>

#include <gnuradio-4.0/basic/TriggerMatcher.hpp>

namespace gr::basic {

using StreamToDataSetDoc = Doc<R""(
@brief Converts stream of input data into chunked discrete DataSet<T> based on tag-based pre- / post-conditions

)"">;

template<typename T, TriggerMatcher TMatcher = BasicTriggerNameMatcher>
struct StreamToDataSet : Block<StreamToDataSet<T, TMatcher>, StreamToDataSetDoc> {
    // optional shortening
    template<typename U, gr::meta::fixed_string description = "", typename... Arguments>
    using A                                      = Annotated<U, description, Arguments...>;
    constexpr static std::size_t MIN_BUFFER_SIZE = 1024;

    // port definitions
    MsgPortIn  filter;
    PortIn<T>  in;
    PortOut<T> out;

    // settings
    A<std::string, "trigger", Visible, Doc<"trigger name">, Visible>                    trigger;
    A<std::string, "start", Visible, Doc<"stop trigger name">, Visible>                 start = "*";
    A<std::string, "stop", Visible, Doc<"stop trigger name">, Visible>                  stop;
    A<std::uint64_t, "n_max", Visible, Doc<"maximum number of samples (0: infinite)">>  n_max           = 0U;
    A<std::uint64_t, "n_pre", Visible, Doc<"number of pre-trigger samples">, Visible>   n_pre           = 0U;
    A<std::uint64_t, "n_post", Visible, Doc<"number of post-trigger samples">, Visible> n_post          = 0U;
    A<bool, "verbose_console", Doc<"true: print-out start/stop-matching conditions">>   verbose_console = false;

    std::vector<T> _history{};

    TMatcher matcher{};
    bool     _matcherChanged = false;

    void
    settingsChanged(const gr::property_map &old_settings, const gr::property_map &new_settings) {
        if (new_settings.contains("n_max") || new_settings.contains("n_pre") || new_settings.contains("n_post")) {
            fmt::print("{}: configuration changed: n_inputs {} -> {}, trigger_port {} -> {}\n", static_cast<void *>(this), old_settings.at("n_inputs"),
                       new_settings.contains("n_inputs") ? new_settings.at("n_inputs") : "same", old_settings.at("trigger_port"),
                       new_settings.contains("trigger_port") ? new_settings.at("trigger_port") : "same");

            auto newBuffer = HistoryBuffer<T>(MIN_BUFFER_SIZE + n_pre + n_max + n_post);
            newBuffer.push_back_bulk(_history);
            //_history = std::move(newBuffer);
        }
        if (new_settings.contains("trigger_port")) {
            fmt::print("{}: configuration changed: trigger_port {} -> {}\n", static_cast<void *>(this), old_settings.at("trigger_port"),
                       new_settings.contains("trigger_port") ? new_settings.at("trigger_port") : "same");
        }

        if (new_settings.contains("matcher")) {
            fmt::print("{}: configuration changed: matcher {} -> {}\n", static_cast<void *>(this), old_settings.at("matcher"), new_settings.contains("matcher") ? new_settings.at("matcher") : "same");
            _matcherChanged = true;
        }
    }

    bool matching = false;

    gr::work::Status
    processBulk(std::span<const T> inSamples, PublishableSpan auto &outSamples) {
        // TODO remove debug:
        // fmt::println(stderr, "invoked processBulk - in {} -> out {}", gr::meta::type_name<decltype(inSamples)>(), gr::meta::type_name<decltype(outSamples)>());
        // fmt::println("invoked processBulk tag present: {} - size {}", !this->mergedInputTag().map.empty(), inSamples.size());
        if (!this->mergedInputTag().map.empty()) {
            const Tag& tag = this->mergedInputTag();
            if (tag.map.contains("trigger_meta_info")) {
                const auto& meta = std::get<property_map>(tag.map.at("trigger_meta_info"));
                if (meta.contains("context")) {
                    const auto &ctx = std::get<std::string>(meta.at("context"));
                    std::array  matchingBPs{ "P=1", "P=2", "P=3" };
                    matching = std::ranges::any_of(matchingBPs, [&ctx](const std::string &sub) { return ctx.find(sub) != std::string::npos; });
                } else {
                    //fmt::println("received tag w/o TRIGGER_META_INFO does not contain CONTEXT: {}", meta);
                }
            } else {
                //fmt::println("received tag w/o {} : {}", gr::tag::TRIGGER_META_INFO.shortKey(), this->mergedInputTag().map);
            }
        }
        if (matching) {
            std::copy(inSamples.begin(), inSamples.end(), outSamples.begin());
            outSamples.publish(inSamples.size());
        } else {
            outSamples.publish(0UZ);
        }
        _matcherChanged = false;
        return work::Status::OK;
    }
};
} // namespace gr::basic

ENABLE_REFLECTION_FOR_TEMPLATE_FULL((typename T, typename Matcher), (gr::basic::StreamToDataSet<T, Matcher>), filter, in, out, trigger, start, stop, n_max, n_pre, n_post, verbose_console);
static_assert(gr::HasProcessBulkFunction<gr::basic::StreamToDataSet<float>>);

#endif // GNURADIO_STREAMTODATASET_HPP
