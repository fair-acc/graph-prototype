#include <boost/ut.hpp>

#include <fmt/ranges.h>

#include "buffer.hpp"
#include "graph_contracts.hpp"
#include "refl.hpp"

struct test_block : fair::block {
    test_block() : fair::block("test_block") {

    }
};

const boost::ut::suite PortApiTests = [] {
    using namespace boost::ut;
    using namespace gr;
    using namespace fair;

    "PortApi"_test = [] {
        static_assert(Port<IN<float, "in">>);
        static_assert(Port<decltype(IN<float>("in"))>);
        static_assert(Port<OUT<float, "out">>);
        static_assert(Port<IN_MSG<float, "in_msg">>);
        static_assert(Port<OUT_MSG<float, "out_msg">>);

        static_assert(IN<float, "in">::static_name() == fixed_string("in"));
        static_assert(requires { IN<float>("in").name(); });
    };

    "PortBufferApi"_test = [] {
        OUT<float, "out0"> output_port;
        BufferWriter auto& writer = output_port.writer();
        expect(ge(writer.available(), 32U));

        IN<float, "int0"> input_port;
        const BufferReader auto& reader = input_port.reader();
        expect(eq(reader.available(), 0U));
        input_port.setBuffer(output_port.buffer());

        expect(eq(output_port.buffer().n_readers(), 1U));

        int offset = 1;
        auto lambda = [&offset](auto& w) {
            std::iota(w.begin(), w.end(), offset);
            fmt::print("typed-port connected output vector: {}\n", w);
            offset += w.size();
        };

        expect(writer.try_publish(lambda, 32));
    };

    "RuntimePortApi"_test = [] {
        // declare in block
        OUT<float, "out"> out;
        IN<float, "in"> in;
        std::vector<dyn_port> port_list;

        port_list.emplace_back(out);
        port_list.emplace_back(in);

        expect(eq(port_list.size(), 2U));
    };

    "ConnectionApi"_test = [] {
        using port_direction_t::INPUT;
        using port_direction_t::OUTPUT;
        OUT<float, "out0"> output_port;
        BufferWriter auto& writer = output_port.writer();
        IN<float, "in0"> input_port;

        auto source = std::make_shared<block>("source");
        source->add_port(output_port);
        source->add_port(OUT<float, "out1">());
        expect(eq(source->output_ports().size(), 2U));
        expect(eq(source->input_ports().size(), 0U));

        auto sink = std::make_shared<block>("sink");
        expect(nothrow([&sink, &input_port] () { sink->add_port(input_port); } ));
        expect(nothrow([&sink] () { sink->add_port(IN<float, "in1">()); } ));
        expect(nothrow([&sink] () { sink->add_port(IN<float>("in2")); } ));
        expect(throws([&sink] () { sink->add_port(IN<float>("in1")); } ));
        expect(eq(sink->output_ports().size(), 0U));
        expect(eq(sink->input_ports().size(), 3U));

        std::vector<edge> edges;

        expect(eq(edges.size(), 0U));

        expect(eq(add_edge(edges, source, "out0", sink, "in0"), connection_result_t::SUCCESS));
        // N.B. should discourage indexed-based access <-> error prone, we test this anyway
        expect(eq(add_edge(edges, source, 0, sink, 1), connection_result_t::SUCCESS));

        expect(eq(edges.size(), 2U));

        auto mismatched_sink = std::make_shared<block>("mismatched_sink");
        IN<int32_t, "in0"> mismatched_typed_port;
        mismatched_sink->add_port(mismatched_typed_port);

        expect(eq(add_edge(edges, source, 0, mismatched_sink, 0), connection_result_t::FAILED));

        expect(eq(edges.size(), 2U));


        // test runtime growing of src ports
        expect(ge(writer.available(), 32U));
        expect(eq(output_port.buffer().n_readers(), 0U));
        const auto old_size = writer.available();
        expect(eq(source->port<OUTPUT>("out0").value()->resize_buffer(old_size+1), connection_result_t::SUCCESS));
        expect(gt(writer.available(), old_size)) << fmt::format("runtime increase of buffer size {} -> {}", old_size, writer.available());

        // test runtime connection between ports
        expect(eq(output_port.buffer().n_readers(), 0U));
        expect(eq(source->port<OUTPUT>("out0").value()->connect(*sink->port<INPUT>("in0").value()), connection_result_t::SUCCESS)) << "fist connection";
        expect(eq(source->port<OUTPUT>("out0").value()->connect(*sink->port<INPUT>("in0").value()), connection_result_t::SUCCESS)) << "double connection";
        expect(eq(source->port<OUTPUT>("out0").value()->connect(*sink->port<INPUT>("in1").value()), connection_result_t::SUCCESS)) << "second connection";

        const BufferReader auto& reader = input_port.reader();
        expect(eq(reader.available(), 0U)) << fmt::format("reader already has some bytes pending: {}", reader.available());

        expect(eq(output_port.buffer().n_readers(), 2U));

        constexpr auto lambda = [](auto& w) {
            std::iota(w.begin(), w.end(), 0U);
            fmt::print("dyn_port connected sink output: {}\n", w);
        };

        expect(writer.try_publish(lambda, 32U));
        expect(eq(input_port.reader().available(), 32U));
    };
};


int main() { /* tests are statically executed */ }
