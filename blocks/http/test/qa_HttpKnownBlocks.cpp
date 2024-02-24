#include <boost/ut.hpp>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <gnuradio-4.0/http/all.hpp>

const boost::ut::suite KnownBlockTests = [] {
    using namespace boost::ut;
    using namespace std::string_literals;

    "Registered"_test = [] {
        auto known = gr::globalBlockRegistry().knownBlocks();
        std::ranges::sort(known);

        std::vector<std::string> desired{
            //
            "gr::http::HttpBlock"s, //
        };
        std::ranges::sort(desired);

        expect((std::ranges::includes(known, desired)));
    };
};

int
main() {
    boost::ut::cfg<boost::ut::override>.run();
}
