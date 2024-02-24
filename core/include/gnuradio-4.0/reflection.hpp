#ifndef GNURADIO_REFLECTION_HPP
#define GNURADIO_REFLECTION_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <refl.hpp>

/**
 * The following macros are helpers to wrap around the existing refl-cpp macros: https://github.com/veselink1/refl-cpp
 * The are basically needed to do a struct member-field introspections, to support
 *   a) compile-time serialiser generation between std::map<std::string, pmt::pmtv> <-> user-defined settings structs
 *   b) allow for block ports being defined a member fields rather than as NTTPs of the node<T, ...> template

 * Their use is limited to the namespace scope where the block is defined (i.e. not across .so boundaries) and will be
 * supplanted once the compile-time reflection language feature is merged with the C++ standard, e.g.
 * Matúš Chochlík, Axel Naumann, David Sankel: Static reflection, P0194R3, ISO/IEC JTC1 SC22 WG21
 *    https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0194r3.html
 *
 *  These macros need to be defined in a global scope due to relying on template specialisation that cannot be done in
 *  any other namespace than the one they were declared -- for illustration see, for example:
 *  https://github.com/veselink1/refl-cpp/issues/59
 *  https://compiler-explorer.com/z/MG7fxzK4j
 *
 *  For practical purposes, the macro can be defined either at the end of the struct declaring namespace or the specific
 *  namespace exited/re-enteres such as
 *  @code
 *  namespace private::library {
 *     struct my_struct {
 *         int field_a;
 *         std::string field_b;
 *     };
 *  }
 *  ENABLE_REFLECTION(private::library:my_struct, field_a, field_b)
 *  namespace private::library {
 *   // ...
 *  @endcode
 *
 *  And please, if you want to accelerator the compile-time reflection process, please give your support and shout-out
 *  to the above authors, and contact your C++ STD Committee representative that this feature should not be delayed.
 */

/**
 * This macro can be used for simple non-templated structs and classes, e.g.
 * @code
 * struct my_struct {
 *     int field_a;
 *      std::string field_b;
 * };
 * ENABLE_REFLECTION(private::library:my_struct, field_a, field_b)
 */
#define ENABLE_REFLECTION(TypeName, ...) \
    REFL_TYPE(TypeName __VA_OPT__(, )) \
    REFL_DETAIL_FOR_EACH(REFL_DETAIL_EX_1_field __VA_OPT__(, ) __VA_ARGS__) \
    REFL_END

/**
 * This macro can be used for arbitrary templated structs and classes, that depend
 * on mixed typename and NTTP parameters
 * @code
 * template<typename T, std::size_t size>
 * struct custom_struct {
 *     T field_a;
 *     T field_b;
 *
 *     [[nodiscard]] constexpr std::size_t size() const noexcept { return size; }
 * };
 * ENABLE_REFLECTION_FOR_TEMPLATE_FULL(typename T, std::size_t size), (custom_struct<T, size>), field_a, field_a);
 */
#define ENABLE_REFLECTION_FOR_TEMPLATE_FULL(TemplateDef, TypeName, ...) \
    REFL_TEMPLATE(TemplateDef, TypeName __VA_OPT__(, )) \
    REFL_DETAIL_FOR_EACH(REFL_DETAIL_EX_1_field __VA_OPT__(, ) __VA_ARGS__) \
    REFL_END

/**
 * This macro can be used for simple templated structs and classes, that depend
 * only on pure typename-template lists
 * @code
 * template<typename T>
 * struct my_templated_struct {
 *     T field_a;
 *     T field_b;
 * };
 * ENABLE_REFLECTION_FOR_TEMPLATE(my_templated_struct, field_a, field_b);
 */
#define ENABLE_REFLECTION_FOR_TEMPLATE(Type, ...) ENABLE_REFLECTION_FOR_TEMPLATE_FULL((typename... Ts), (Type<Ts...>), __VA_ARGS__)

#define GR_CONCAT_IMPL(x, y) x##y
#define GR_MACRO_CONCAT(x, y) GR_CONCAT_IMPL(x, y)

#define GR_REGISTER_BLOCK_IMPL(Register, Name, ...) gr::detail::RegisterBlock<Name, __VA_ARGS__> GR_MACRO_CONCAT(GR_REGISTER_BLOCK_, __COUNTER__)(Register, #Name);
/**
 * This macro can be used to register a block with the block
 * registry to be used with the plugin system for runtime instantiation
 * of blocks based on their stringified types.
 *
 * The arguments are:
 *  - a reference to the registry (common to use gr::globalBlockRegistry)
 *  - the block template class
 *  - list of valid template parameters for this block type
 *
 * To register adder<T> block to be instantiatiatable with float and double:
 *     GR_REGISTER_BLOCK(gr::globalBlockRegistry(), adder, float, double)
 *
 * To register converter<From, To> block to be instantiatiatable
 * with <float, double> and <double, float>:
 *     GR_REGISTER_BLOCK(gr::globalBlockRegistry(), converter, BlockParameters<double, float>, BlockParameters<float, double>)
 */
#define GR_REGISTER_BLOCK(Register, Name, ...) \
    namespace { \
    using gr::detail::BlockParameters; \
    GR_REGISTER_BLOCK_IMPL(Register, Name, __VA_ARGS__); \
    }
#define GR_REGISTER_BLOCK_RUNTIME(Register, Name, ...) \
    { \
        using gr::detail::BlockParameters; \
        GR_REGISTER_BLOCK_IMPL(Register, Name, __VA_ARGS__); \
    }

#pragma GCC diagnostic pop
#endif // GNURADIO_REFLECTION_HPP
