#ifndef GNURADIO_GRAPH_HPP
#define GNURADIO_GRAPH_HPP

// #include <gnuradio-4.0/Block.hpp>
#ifndef GNURADIO_BLOCK_HPP
#define GNURADIO_BLOCK_HPP

#include <limits>
#include <map>
#include <source_location>

// #include <pmtv/pmt.hpp>



// #include "base64/base64.h"
/*
 * Copyright (c) 2003 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * Copyright (c) 1999-2003 Apple Computer, Inc.  All Rights Reserved.
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/* ====================================================================
 * Copyright (c) 1995-1999 The Apache Group.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * 4. The names "Apache Server" and "Apache Group" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Group.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * THIS SOFTWARE IS PROVIDED BY THE APACHE GROUP ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE APACHE GROUP OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Group and was originally based
 * on public domain software written at the National Center for
 * Supercomputing Applications, University of Illinois, Urbana-Champaign.
 * For more information on the Apache Group and the Apache HTTP server
 * project, please see <http://www.apache.org/>.
 *
 */


#ifndef _BASE64_H_
#define _BASE64_H_

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// int Base64encode_len(int len);
// int Base64encode(char* coded_dst, const char* plain_src, int len_plain_src);

// int Base64decode_len(const char* coded_src);
// int Base64decode(char* plain_dst, const char* coded_src);

// #ifdef __cplusplus
// }
// #endif

/* Base64 encoder/decoder. Originally Apache file ap_base64.c
 */

/* aaaack but it's fast and const should make it shared text page. */
static const unsigned char pr2six[256] = {
    /* ASCII table */
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 62, 64, 64, 64, 63, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64,
    64, 64, 64, 64, 64, 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64, 64, 26, 27, 28,
    29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

static inline int Base64decode_len(const char* bufcoded)
{
    const auto* bufin {reinterpret_cast<const unsigned char*>(bufcoded)};
    while (pr2six[*(bufin++)] <= 63)
        ;
    auto nprbytes {static_cast<int>(bufin - reinterpret_cast<const unsigned char*>(bufcoded)) - 1};
    return ((nprbytes + 3) / 4) * 3 + 1;
}

static inline int Base64decode(char* bufplain, const char* bufcoded)
{
    const auto* bufin {reinterpret_cast<const unsigned char*>(bufcoded)};
    while (pr2six[*(bufin++)] <= 63)
        ;
    auto nprbytes {static_cast<int>(bufin - reinterpret_cast<const unsigned char*>(bufcoded)) - 1};

    auto* bufout {reinterpret_cast<unsigned char*>(bufplain)};
    bufin = reinterpret_cast<const unsigned char*>(bufcoded);

    while (nprbytes > 4) {
        *(bufout++) = static_cast<unsigned char>(pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
        *(bufout++) = static_cast<unsigned char>(pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
        *(bufout++) = static_cast<unsigned char>(pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
        bufin += 4;
        nprbytes -= 4;
    }

    /* Note: (nprbytes == 1) would be an error, so just ingore that case */
    if (nprbytes > 1) {
        *(bufout++) = static_cast<unsigned char>(pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
    }
    if (nprbytes > 2) {
        *(bufout++) = static_cast<unsigned char>(pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
    }
    if (nprbytes > 3) {
        *(bufout++) = static_cast<unsigned char>(pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
    }

    *(bufout++) = '\0';
    return ((nprbytes + 3) / 4) * 3 - ((4 - nprbytes) & 3);
}

static const char basis_64[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static inline int Base64encode_len(int len) { return ((len + 2) / 3 * 4) + 1; }

static inline int Base64encode(char* encoded, const char* string, int len)
{
    int i {0};
    char* p {encoded};
    for (i = 0; i < len - 2; i += 3) {
        *p++ = basis_64[(string[i] >> 2) & 0x3F];
        *p++ = basis_64[((string[i] & 0x3) << 4) | ((string[i + 1] & 0xF0) >> 4)];
        *p++ = basis_64[((string[i + 1] & 0xF) << 2) | ((string[i + 2] & 0xC0) >> 6)];
        *p++ = basis_64[string[i + 2] & 0x3F];
    }
    if (i < len) {
        *p++ = basis_64[(string[i] >> 2) & 0x3F];
        if (i == (len - 1)) {
            *p++ = basis_64[((string[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else {
            *p++ = basis_64[((string[i] & 0x3) << 4) | ((string[i + 1] & 0xF0) >> 4)];
            *p++ = basis_64[((string[i + 1] & 0xF) << 2)];
        }
        *p++ = '=';
    }

    *p++ = '\0';
    return static_cast<int>(p - encoded);
}

#ifdef __cplusplus
}
#endif

#endif //_BASE64_H_
// #include <pmtv/type_helpers.hpp>


#include <complex>
#include <concepts>
#include <map>
#include <memory>
#include <ranges>
#include <variant>
#include <vector>

// #include <pmtv/rva_variant.hpp>
/*
From https://github.com/codeinred/recursive-variant

Note that is may not be needed anymore in c++23.  
See https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2162r0.html

Boost Software License - Version 1.0 - August 17th, 2003

© 2021 Alecto Irene Perez

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by this
license (the "Software") to use, reproduce, display, distribute, execute, and
transmit the Software, and to prepare derivative works of the Software, and to
permit third-parties to whom the Software is furnished to do so, all subject to
the following:

The copyright notices in the Software and this entire statement, including the
above license grant, this restriction and the following disclaimer, must be
included in all copies of the Software, in whole or in part, and all derivative
works of the Software, especially those created in whole or in part by Deep
Neural Networks, Language Models, or other such programs advertised as "AI" or
as "Artificial Intelligence" or as "Machine Learning", either with or without
human input or intervention, unless such copies or derivative works are solely
in the form of machine-executable object code generated by a source language
processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES
OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef RECURSIVE_VARIANT_AUTHORITY_VARIANT_HPP
#define RECURSIVE_VARIANT_AUTHORITY_VARIANT_HPP
#include <cstdint>
#include <variant>

namespace rva {
/**
 * @brief replace is a template type used to implement replace_t. It provides
 * member, a using declaration named `type`.
 *
 * @tparam T the type to transform.
 * @tparam Find the type to find
 * @tparam Replace the type to replace it with.
 */
template <class T, class Find, class Replace>
struct replace;
/**
 * @brief replace is a template that takes a type T (which itself might be a
 * template), and replaces all instances of *Find* with *Replace*. For example:
 *
 * - `replace_t<char, char, int>` -> `int`
 * - `replace_t<std::vector<char>, char, int>` -> `std::vector<int>`
 *
 * @tparam T the type to transform.
 * @tparam Find the type to find
 * @tparam Replace the type to replace it with.
 */
template <class T, class Find, class Replace>
using replace_t = typename replace<T, Find, Replace>::type;

struct self_t {
};

// See: https://en.cppreference.com/w/cpp/utility/variant
template <class... T>
class variant : public std::variant<replace_t<T, self_t, variant<T...>>...>
{
public:
    using base_type = std::variant<replace_t<T, self_t, variant<T...>>...>;
    constexpr static bool nothrow_swappable = std::is_nothrow_swappable_v<base_type>;

    using base_type::base_type;

    // Observers
    using base_type::index;
    using base_type::valueless_by_exception;

    // Modifiers
    using base_type::operator=;
    using base_type::emplace;
    using base_type::swap;

    variant() = default;
    variant(variant const&) = default;
    variant(variant&&) = default;

    variant& operator=(variant const&) = default;
    variant& operator=(variant&&) = default;

    constexpr void swap(variant& other) noexcept(nothrow_swappable)
    {
        base_type::swap(other);
    }
    constexpr base_type& get_base() & noexcept { return *this; }
    constexpr base_type const& get_base() const& noexcept { return *this; }
    constexpr base_type&& get_base() && noexcept { return *this; }
    constexpr base_type const&& get_base() const&& noexcept { return *this; }

    constexpr base_type* get_pointer_to_base() noexcept { return this; }
    constexpr base_type const* get_pointer_to_base() const noexcept { return this; }

    auto operator<=>(variant const&) const = default;
    bool operator==(variant const&) const = default;

    size_t size()
    {
        return std::visit(
            [](const auto& arg) -> size_t {
                using TYPE = std::decay_t<decltype(arg)>;
                if constexpr (std::same_as<std::monostate, TYPE>)
                    return 0;
                else if constexpr (std::ranges::range<TYPE>)
                    return arg.size();
                return 1;
            },
            get_base());
    }
};

// See: https://en.cppreference.com/w/cpp/utility/variant/visit
template <class Visitor, class... Variants>
constexpr decltype(auto) visit(Visitor&& visitor, Variants&&... variants)
{
    return std::visit(std::forward<Visitor>(visitor),
                      std::forward<Variants>(variants).get_base()...);
}
template <class R, class Visitor, class... Variants>
constexpr R visit(Visitor&& visitor, Variants&&... variants)
{
    return std::visit<R>(std::forward<Visitor>(visitor),
                         std::forward<Variants>(variants).get_base()...);
}

// See: https://en.cppreference.com/w/cpp/utility/variant/get
template <std::size_t I, class... Types>
constexpr decltype(auto) get(rva::variant<Types...>& v)
{
    return std::get<I>(std::forward<decltype(v)>(v).get_base());
}
template <std::size_t I, class... Types>
constexpr decltype(auto) get(rva::variant<Types...>&& v)
{
    return std::get<I>(std::forward<decltype(v)>(v).get_base());
}
template <std::size_t I, class... Types>
constexpr decltype(auto) get(const rva::variant<Types...>& v)
{
    return std::get<I>(std::forward<decltype(v)>(v).get_base());
}
template <std::size_t I, class... Types>
constexpr decltype(auto) get(const rva::variant<Types...>&& v)
{
    return std::get<I>(std::forward<decltype(v)>(v).get_base());
}
template <class T, class... Types>
constexpr T& get(rva::variant<Types...>& v)
{
    return std::get<T>(std::forward<decltype(v)>(v).get_base());
}
template <class T, class... Types>
constexpr T&& get(rva::variant<Types...>&& v)
{
    return std::get<T>(std::forward<decltype(v)>(v).get_base());
}
template <class T, class... Types>
constexpr const T& get(const rva::variant<Types...>& v)
{
    return std::get<T>(std::forward<decltype(v)>(v).get_base());
}
template <class T, class... Types>
constexpr const T&& get(const rva::variant<Types...>&& v)
{
    return std::get<T>(std::forward<decltype(v)>(v).get_base());
}

// See: https://en.cppreference.com/w/cpp/utility/variant/get_if
template <std::size_t I, class... Types>
constexpr auto* get_if(rva::variant<Types...>* pv) noexcept
{
    return std::get_if<I>(pv->get_pointer_to_base());
}
template <std::size_t I, class... Types>
constexpr auto const* get_if(const rva::variant<Types...>* pv) noexcept
{
    return std::get_if<I>(pv->get_pointer_to_base());
}
template <class T, class... Types>
constexpr auto* get_if(rva::variant<Types...>* pv) noexcept
{
    return std::get_if<T>(pv->get_pointer_to_base());
}
template <class T, class... Types>
constexpr auto const* get_if(const rva::variant<Types...>* pv) noexcept
{
    return std::get_if<T>(pv->get_pointer_to_base());
}

template <class T, class... Types>
constexpr bool holds_alternative(const rva::variant<Types...>& v) noexcept
{
    return std::holds_alternative(v.get_base());
}
} // namespace rva

template <class... T>
struct std::hash<rva::variant<T...>> : std::hash<std::variant<T...>> {
    using base_type = std::hash<std::variant<T...>>;
    using base_type::base_type;
    hash() = default;
    hash(hash const&) = default;
    hash(hash&&) = default;
    size_t operator()(rva::variant<T...> const& v) const
    {
        return base_type::operator()(v.get_base());
    }
};

template <class... Types>
struct std::variant_size<rva::variant<Types...>>
    : std::integral_constant<std::size_t, sizeof...(Types)> {
};
template <class... Types>
struct std::variant_size<const rva::variant<Types...>>
    : std::integral_constant<std::size_t, sizeof...(Types)> {
};

template <std::size_t I, class... Types>
struct std::variant_alternative<I, rva::variant<Types...>>
    : std::variant_alternative<I, typename rva::variant<Types...>::base_type> {
};
template <std::size_t I, class... Types>
struct std::variant_alternative<I, const rva::variant<Types...>>
    : std::variant_alternative<I, typename rva::variant<Types...>::base_type> {
};

// Implementation for replace
namespace rva {
template <class T, class Find, class Replace>
struct replace {
    using type = T;
};
template <class Find, class Replace>
struct replace<Find, Find, Replace> {
    using type = Replace;
};
template <class Find, class Replace>
struct replace<Find*, Find, Replace> {
    using type = Replace*;
};
template <class Find, class Replace>
struct replace<Find&, Find, Replace> {
    using type = Replace&;
};
template <class Find, class Replace>
struct replace<Find&&, Find, Replace> {
    using type = Replace&&;
};
template <class Find, class Replace>
struct replace<Find[], Find, Replace> {
    using type = Replace[];
};
template <class Find, class Replace, std::size_t N>
struct replace<Find[N], Find, Replace> {
    using type = Replace[N];
};
template <class Find, class Replace>
struct replace<const Find, Find, Replace> {
    using type = const Replace;
};
template <class Find, class Replace>
struct replace<const Find*, Find, Replace> {
    using type = const Replace*;
};
template <class Find, class Replace>
struct replace<const Find&, Find, Replace> {
    using type = const Replace&;
};
template <class Find, class Replace>
struct replace<const Find[], Find, Replace> {
    using type = const Replace[];
};
template <class Find, class Replace, std::size_t N>
struct replace<const Find[N], Find, Replace> {
    using type = const Replace[N];
};
template <class T, class Find, class Replace>
struct replace<T*, Find, Replace> {
    using type = replace_t<T, Find, Replace>*;
};
template <class T, class Find, class Replace>
struct replace<T&, Find, Replace> {
    using type = replace_t<T, Find, Replace>&;
};
template <class T, class Find, class Replace>
struct replace<T&&, Find, Replace> {
    using type = replace_t<T, Find, Replace>&&;
};
template <class T, class Find, class Replace>
struct replace<T[], Find, Replace> {
    using type = replace_t<T, Find, Replace>[];
};
template <class T, class Find, class Replace, std::size_t N>
struct replace<T[N], Find, Replace> {
    using type = replace_t<T, Find, Replace>[N];
};
template <class T, class Find, class Replace>
struct replace<const T, Find, Replace> {
    using type = replace_t<T, Find, Replace> const;
};
template <class T, class Find, class Replace>
struct replace<const T*, Find, Replace> {
    using type = replace_t<T, Find, Replace> const*;
};
template <class T, class Find, class Replace>
struct replace<const T&, Find, Replace> {
    using type = replace_t<T, Find, Replace> const&;
};
template <class T, class Find, class Replace>
struct replace<const T[], Find, Replace> {
    using type = replace_t<T, Find, Replace> const[];
};
template <class T, class Find, class Replace, std::size_t N>
struct replace<const T[N], Find, Replace> {
    using type = replace_t<T, Find, Replace> const[N];
};

template <template <class...> class T, class... Ts, class Find, class Replace>
struct replace<T<Ts...>, Find, Replace> {
    using type = T<replace_t<Ts, Find, Replace>...>;
};

// Add shortcut for rva::variant to avoid replacing into instances of an
// rva::variant that's given as a template parameter to another rva::variant
template <class... Ts, class Find, class Replace>
struct replace<rva::variant<Ts...>, Find, Replace> {
    using type = rva::variant<Ts...>;
};
} // namespace rva

#endif


namespace pmtv {

namespace detail {

// Convert a list of types to the full set used for the pmt.
template<template<typename... > class VariantType, typename... Args>
struct as_pmt {
    using type = VariantType<std::monostate,
                             Args...,
                             std::vector<Args>...,
                             std::string,
                             std::vector<std::string>,
                             std::vector<rva::self_t>,
                             std::map<std::string, rva::self_t, std::less<>>
                             >;
};

template<template<typename... > class TemplateType, typename ...T>
struct as_pmt<TemplateType, std::tuple<T...>> {
    using type = typename as_pmt<TemplateType, T...>::type;
};
}


template<template<typename... > class VariantType, class... Args>
using as_pmt_t = typename detail::as_pmt<VariantType, Args...>::type;

// Check if `std::size_t` has the same type as `uint16_t` or `uint32_t` or `uint64_t`.
// If it has the same type, then there is no need to add `std::size_t` the supported types.
// Otherwise, `std::size_t` is added to the supported types.
// This can happen if one builds using Emscripten where `std::size_t` is defined as `unsigned long` and
// `uint32_t` and `uint64_t` are defined as `unsigned int` and `unsigned long long`, respectively.
static constexpr bool support_size_t = !std::is_same_v<std::size_t, uint16_t> && !std::is_same_v<std::size_t, uint32_t> && !std::is_same_v<std::size_t, uint64_t>;

// Note that per the spec, std::complex is undefined for any type other than float, double, or long_double
using default_supported_types_without_size_t = std::tuple<bool,
        uint8_t, uint16_t, uint32_t, uint64_t,
        int8_t, int16_t, int32_t, int64_t,
        float, double, std::complex<float>, std::complex<double>>;

// Add std::size_t to default_supported_types_without_size_t
using default_supported_types_with_size_t = decltype(std::tuple_cat(std::declval<default_supported_types_without_size_t>(), std::declval<std::tuple<std::size_t>>()));

using default_supported_types = typename std::conditional_t<support_size_t, default_supported_types_with_size_t, default_supported_types_without_size_t>;

// initialisation via type list stored in tuple (N.B. tuple could be extended by user with custom OOT types)
using pmt_var_t = as_pmt_t<rva::variant, default_supported_types>;

using pmt_null = std::monostate;


template <typename T>
concept PmtNull = std::is_same_v<T, std::monostate>;

template <typename T>
concept Complex =
    std::is_same_v<T, std::complex<float>> || std::is_same_v<T, std::complex<double>>;

template <typename T>
concept Scalar = std::same_as<T, bool> || std::integral<T> || std::floating_point<T> || Complex<T>;

template <typename T>
concept UniformVector =
    std::ranges::contiguous_range<T> && Scalar<typename T::value_type>;

// A vector of bool can be optimized to one bit per element, so it doesn't satisfy UniformVector
template <typename T>
concept UniformBoolVector = 
    std::ranges::range<T> && std::same_as<typename T::value_type, bool>;

template <typename T>
concept UniformStringVector =
    std::ranges::range<T> && std::same_as<typename T::value_type, std::string>;

template <typename T>
concept PmtMap = std::is_same_v<T, std::map<std::string, pmt_var_t, std::less<>>>;

template <typename T>
concept String = std::is_same_v<T, std::string>;

template <typename T>
concept PmtVector =
    std::ranges::range<T> && std::is_same_v<typename T::value_type, pmt_var_t>;

} // namespace pmtv

// #include <pmtv/version.hpp>


#include <stdint.h>

namespace pmtv {
static const uint16_t pmt_version = 1;
}
#include <complex>
#include <cstddef>
#include <ranges>
#include <span>

#ifdef __GNUC__
#pragma GCC diagnostic push // ignore warning of external libraries that from this lib-context we do not have any control over
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif

// #include <refl.hpp>
// The MIT License (MIT)
//
// Copyright (c) 2020 Veselin Karaganev (@veselink1) and Contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef REFL_INCLUDE_HPP
#define REFL_INCLUDE_HPP

#include <stddef.h> // size_t
#include <cstring>
#include <array>
#include <utility> // std::move, std::forward
#include <optional>
#include <tuple>
#include <type_traits>
#include <ostream>
#include <sstream>
#include <iomanip> // std::quoted
#include <memory>
#include <complex>

#ifdef _MSC_VER
// Disable VS warning for "Not enough arguments for macro"
// (emitted when a REFL_ macro is not provided any attributes)
#pragma warning( disable : 4003 )
#endif

#if defined(__clang__)
  #if __has_feature(cxx_rtti)
    #define REFL_RTTI_ENABLED
  #endif
#elif defined(__GNUG__)
  #if defined(__GXX_RTTI)
    #define REFL_RTTI_ENABLED
  #endif
#elif defined(_MSC_VER)
  #if defined(_CPPRTTI)
    #define REFL_RTTI_ENABLED
  #endif
#endif

/**
 * @brief The top-level refl-cpp namespace
 * It contains a few core refl-cpp namespaces and directly exposes core classes and functions.
 * <ul>
 * <li>util - utility functions (for_each, map_to_tuple, etc.)</li>
 * <li>trait - type-traits and other operations on types (is_function_v, map_t, etc.)</li>
 * <li>runtime - utility functions and classes that always have a runtime overhead (proxy<T>, debug_str, etc.)</li>
 * <li>member - contains the empty classes member and function (used for tagging)</li>
 * <li>descriptor - contains the non-specialized member types (type|field_descriptor<T, N>, and operations on them (get_property, get_display_name, etc.))</li>
 * </ul>
 *
 * using util::type_list; <br>
 * using descriptor::type_descriptor; <br>
 * using descriptor::field_descriptor; <br>
 * using descriptor::function_descriptor; <br>
 * using util::const_string; <br>
 * using util::make_const_string; <br>
 */
namespace refl
{
    /**
     * @brief Contains utility types and functions for working with those types.
     */
    namespace util
    {
        /**
         * Converts a compile-time available const char* value to a const_string<N>.
         * The argument must be a *core constant expression* and be null-terminated.
         *
         * @see refl::util::const_string
         */
#define REFL_MAKE_CONST_STRING(CString) \
    (::refl::util::detail::copy_from_unsized<::refl::util::detail::strlen(CString)>(CString))

        /**
         * Represents a compile-time string. Used in refl-cpp
         * for representing names of reflected types and members.
         * Supports constexpr concatenation and substring,
         * and is explicitly-convertible to const char* and std::string.
         * REFL_MAKE_CONST_STRING can be used to create an instance from a literal string.
         *
         * @typeparam <N> The length of the string excluding the terminating '\0' character.
         * @see refl::descriptor::base_member_descriptor::name
         */
        template <size_t N>
        struct const_string
        {
            /** The largest positive value size_t can hold. */
            static constexpr size_t npos = static_cast<size_t>(-1);

            /** The length of the string excluding the terminating '\0' character. */
            static constexpr size_t size = N;

            /**
             * The statically-sized character buffer used for storing the string.
             */
            char data[N + 1];

            /**
             * Creates an empty const_string.
             */
            constexpr const_string() noexcept
                : data{}
            {
            }

            /**
             * Creates a copy of a const_string.
             */
            constexpr const_string(const const_string<N>& other) noexcept
                : const_string(other, std::make_index_sequence<N>())
            {
            }

            /**
             * Creates a const_string by copying the contents of data.
             */
            constexpr const_string(const char(&data)[N + 1]) noexcept
                : const_string(data, std::make_index_sequence<N>())
            {
            }

            /**
             * Explicitly converts to const char*.
             */
            explicit constexpr operator const char*() const noexcept
            {
                return data;
            }

            /**
             * Explicitly converts to std::string.
             */
            explicit operator std::string() const noexcept
            {
                return data;
            }

            /**
             * Returns a pointer to the contained zero-terminated string.
             */
            constexpr const char* c_str() const noexcept
            {
                return data;
            }

            /**
             * Returns the contained string as an std::string.
             */
            std::string str() const noexcept
            {
                return data;
            }

            /**
             * A constexpr version of std::string::substr.
             *
             * \code{.cpp}
             * make_const_string("Hello, World!").template substr<0, 4>() -> (const_string<4>) "Hell"
             * make_const_string("Hello, World!").template substr<1, 4>() -> (const_string<3>) "ell"
             * \endcode
             */
            template <size_t Pos, size_t Count = npos>
            constexpr auto substr() const noexcept
            {
                static_assert(Pos <= N);
                constexpr size_t NewSize = (std::min)(Count, N - Pos);

                char buf[NewSize + 1]{};
                for (size_t i = 0; i < NewSize; i++) {
                    buf[i] = data[Pos + i];
                }

                return const_string<NewSize>(buf);
            }

            /**
             * Searches the string for the first occurrence of the character and returns its position.
             *
             * \code{.cpp}
             * make_const_string("Hello, World!").find('e') -> 1
             * make_const_string("Hello, World!").find('z') -> static_cast<size_t>(-1)
             * \endcode
             */
            constexpr auto find(char ch, size_t pos = 0) const noexcept
            {
                for (size_t i = pos; i < N; i++) {
                    if (data[i] == ch) {
                        return i;
                    }
                }
                return npos;
            }

            /**
             * Searches the string for the last occurrence of the character and returns its position.
             *
             * \code{.cpp}
             * make_const_string("Hello, World!").rfind('o') -> 8
             * make_const_string("Hello, World!").rfind('z') -> static_cast<size_t>(-1)
             * \endcode
             */
            constexpr auto rfind(char ch, size_t pos = npos) const noexcept
            {
                for (size_t i = (pos == npos ? N - 1 : pos); i + 1 > 0; i--) {
                    if (data[i] == ch) {
                        return i;
                    }
                }
                return npos;
            }

        private:

            /**
             * Creates a copy of a const_string.
             */
            template <size_t... Idx>
            constexpr const_string(const const_string<N>& other, std::index_sequence<Idx...>) noexcept
                : data{ other.data[Idx]... }
            {
            }

            /**
             * Creates a const_string by copying the contents of data.
             */
            template <size_t... Idx>
            constexpr const_string(const char(&data)[sizeof...(Idx) + 1], std::index_sequence<Idx...>) noexcept
                : data{ data[Idx]... }
            {
            }

        };

        /**
         * Creates an empty instance of const_string<N>
         *
         * @see refl::util::const_string
         */
        constexpr const_string<0> make_const_string() noexcept
        {
            return {};
        }

        /**
         * Creates an instance of const_string<N>
         *
         * @see refl::util::const_string
         */
        template <size_t N>
        constexpr const_string<N - 1> make_const_string(const char(&str)[N]) noexcept
        {
            return str;
        }

        /**
         * Creates an instance of const_string<N>
         *
         * @see refl::util::const_string
         */
        constexpr const_string<1> make_const_string(char ch) noexcept
        {
            const char str[2]{ ch, '\0' };
            return make_const_string(str);
        }

        /**
         * Concatenates two const_strings together.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr const_string<N + M> operator+(const const_string<N>& a, const const_string<M>& b) noexcept
        {
            char data[N + M + 1] { };
            for (size_t i = 0; i < N; i++)
                data[i] = a.data[i];
            for (size_t i = 0; i < M; i++)
                data[N + i] = b.data[i];
            return data;
        }

        /**
         * Concatenates a const_string with a C-style string.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr const_string<N + M - 1> operator+(const const_string<N>& a, const char(&b)[M]) noexcept
        {
            return a + make_const_string(b);
        }

        /**
         * Concatenates a C-style string with a const_string.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr const_string<N + M - 1> operator+(const char(&a)[N], const const_string<M>& b) noexcept
        {
            return make_const_string(a) + b;
        }

        /**
         * Compares two const_strings for equality.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr bool operator==(const const_string<N>& a, const const_string<M>& b) noexcept
        {
            if constexpr (N != M) {
                return false;
            }
            else {
                for (size_t i = 0; i < M; i++) {
                    if (a.data[i] != b.data[i]) {
                        return false;
                    }
                }
                return true;
            }
        }

        /**
         * Compares two const_strings for equality.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr bool operator!=(const const_string<N>& a, const const_string<M>& b) noexcept
        {
            return !(a == b);
        }

        /**
         * Compares a const_string with a C-style string for equality.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr bool operator==(const const_string<N>& a, const char(&b)[M]) noexcept
        {
            return a == make_const_string(b);
        }

        /**
         * Compares a const_string with a C-style string for equality.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr bool operator!=(const const_string<N>& a, const char(&b)[M]) noexcept
        {
            return a != make_const_string(b);
        }

        /**
         * Compares a C-style string with a const_string for equality.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr bool operator==(const char(&a)[N], const const_string<M>& b) noexcept
        {
            return make_const_string(a) == b;
        }

        /**
         * Compares a C-style string with a const_string for equality.
         *
         * @see refl::util::const_string
         */
        template <size_t N, size_t M>
        constexpr bool operator!=(const char(&a)[N], const const_string<M>& b) noexcept
        {
            return make_const_string(a) != b;
        }

        template <size_t N>
        constexpr std::ostream& operator<<(std::ostream& os, const const_string<N>& str) noexcept
        {
            return os << str.c_str();
        }

        namespace detail
        {
            constexpr size_t strlen(const char* const str)
            {
                return *str ? 1 + strlen(str + 1) : 0;
            }

            template <size_t N>
            constexpr const_string<N> copy_from_unsized(const char* const str)
            {
                const_string<N> cstr;
                for (size_t i = 0; i < N; i++) {
                    cstr.data[i] = str[i];
                }
                return cstr;
            }
        } // namespace detail

        /**
         * Represents a compile-time list of types provided as variadic template parameters.
         * type_list is an empty TrivialType. Instances of it can freely be created to communicate
         * the list of represented types. type_lists support many standard operations that are
         * implicitly available with ADL-lookup. type_list is used by refl-cpp mostly to represent
         * the list of refl::field_descriptor, refl::function_descriptor specializations that
         * allow the compile-time reflection of a type's members.
         *
         * @see refl::util::for_each
         * @see refl::util::map_to_array
         * @see refl::util::map_to_tuple
         * @see refl::member_list
         *
         * # Examples
         * ```
         * for_each(type_list<int, float>(), [](auto) { ... });
         * ```
         */
        template <typename... Ts>
        struct type_list
        {
            /** The number of types in this type_list */
            static constexpr intptr_t size = sizeof...(Ts);
        };

        template <typename T>
        struct type_list<T>
        {
            typedef T type;
            static constexpr intptr_t size = 1;
        };

        template <typename T>
        using type_tag = type_list<T>;

    } // namespace util

    using util::const_string;
    using util::make_const_string;
    using util::type_list;
    using util::type_tag;

    /**
     * The contents of the refl::detail::macro_exports namespace
     * is implicitly available in the context of REFL_TYPE/FIELD/FUNC macros.
     * It is used to export the refl::attr:: standard attributes.
     */
    namespace detail
    {
        namespace macro_exports
        {
        }
    }

} // namespace refl

/**
 * refl_impl is an internal namespace that should not be used by the users of refl-cpp.
 */
namespace refl_impl
{
    /**
     * Contains the generated metadata types.
     * (i.e. type_info__)
     */
    namespace metadata
    {
        // Import everyting from macro_exports here to make it visible in REFL_ macro context.
        using namespace refl::detail::macro_exports;

        /**
         * The core reflection metadata type.
         * type_info__ holds data for a type T.
         *
         * The non-specialized type_info__ type has a member typedef invalid_marker
         * that can be used to detect it.
         *
         * Specializations of this type should provide all members of this
         * generic definition, except invalid_marker.
         *
         * @typeparam <T> The reflected type.
         */
        template <typename T>
        struct type_info__
        {
            /** Used for detecting this non-specialized type_info__ instance. */
            struct invalid_marker{};

            /**
             * This is a placeholder definition of which no type instances should be created.
             */
            template <size_t, typename>
            struct member;

            /** The number of reflected members of the target type T. */
            static constexpr size_t member_count{ 0 };

            /** This is a placeholder definition which shold not be referenced by well-formed programs. */
            static constexpr refl::const_string<0> name{ "" };

            /** This is a placeholder definition which shold not be referenced by well-formed programs. */
            static constexpr std::tuple<> attributes{ };
        };

        /**
         * Specializes type_info__ so that a type's const-qualification is effectively discarded.
         */
        template <typename T>
        struct type_info__<const T> : public type_info__<T> {};

        /**
         * Specializes type_info__ so that a type's volatile-qualification is effectively discarded.
         */
        template <typename T>
        struct type_info__<volatile T> : public type_info__<T> {};

        /**
         * Specializes type_info__ so that a type's const-volatile-qualification is effectively discarded.
         */
        template <typename T>
        struct type_info__<const volatile T> : public type_info__<T> {};

    } // namespace metadata

} // namespace refl_impl

namespace refl
{
    namespace detail
    {
        template <typename T>
        using type_info = refl_impl::metadata::type_info__<T>;

        template <typename T, size_t N>
        using member_info = typename type_info<T>::template member<N>;
    } // namespace detail

    /**
     * @brief Contains tag types denoting the different types of reflectable members.
     *
     * This namespace contains a number of empty types that correspond to
     * the different member types that refl-cpp supports reflection over.
     */
    namespace member
    {
        /**
         * An empty type which is equivalent to refl::member_descriptor_base::member_type
         * when the reflected member is a field.
         *
         * @see refl::descriptor::field_descriptor
         */
        struct field {};

        /**
         * An empty type which is equivalent to refl::member_descriptor_base::member_type
         * when the reflected member is a function.
         *
         * @see refl::descriptor::function_descriptor
         */
        struct function {};
    }

    namespace descriptor
    {
        template <typename>
        class type_descriptor;

        template <typename, size_t>
        class field_descriptor;

        template <typename, size_t>
        class function_descriptor;
    } // namespace descriptor

    /**
     * @brief Provides type-level operations for refl-cpp related use-cases.
     *
     * The refl::trait namespace provides type-level operations useful
     * for compile-time metaprogramming.
     */
    namespace trait
    {/**
         * Removes all reference and cv-qualifiers from T.
         * Equivalent to std::remove_cvref which is not currently
         * available on all C++17 compilers.
         */
        template <typename T>
        struct remove_qualifiers
        {
            typedef std::remove_cv_t<std::remove_reference_t<T>> type;
        };

        /**
         * Removes all reference and cv-qualifiers from T.
         * Equivalent to std::remove_cvref_t which is not currently
         * available on all C++17 compilers.
         */
        template <typename T>
        using remove_qualifiers_t = typename remove_qualifiers<T>::type;

        namespace detail
        {
            /** SFIANE support for detecting whether there is a type_info__ specialization for T. */
            template <typename T>
            decltype(typename refl::detail::type_info<T>::invalid_marker{}, std::false_type{}) is_reflectable_test(int);

            /** SFIANE support for detecting whether there is a type_info__ specialization for T. */
            template <typename T>
            std::true_type is_reflectable_test(...);
        } // namespace detail

        /**
         * Checks whether there is reflection metadata for the type T.
         * Inherits from std::bool_constant<>
         *
         * @see REFL_TYPE
         * @see REFL_AUTO
         * @see refl::is_reflectable
         */
        template <typename T>
        struct is_reflectable : decltype(detail::is_reflectable_test<T>(0))
        {
        };

        /**
         * Checks whether there is reflection metadata for the type T.
         * Inherits from std::bool_constant<>
         *
         * @see refl::trait::is_reflectable
         */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_reflectable_v{ is_reflectable<T>::value };

        namespace detail
        {
            /** SFIANE support for detecting whether the type T supports member .begin() and .end() operations. */
            template <typename U>
            [[maybe_unused]] static auto is_container_test(int) -> decltype(std::declval<U>().begin(), std::declval<U>().end(), std::true_type{});

            /** SFIANE support for detecting whether the type T supports member .begin() and .end() operations. */
            template <typename U>
            [[maybe_unused]] static std::false_type is_container_test(...);
        }

        /**
         * Checks whether objects of the type T support member .begin() and .end() operations.
         */
        template <typename T>
        struct is_container : decltype(detail::is_container_test<T>(0))
        {
        };

        /**
         * Checks whether objects of the type T support member .begin() and .end() operations.
         */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_container_v{ is_container<T>::value };

        namespace detail
        {

            template <size_t D, size_t N, typename... Ts>
            struct get;

            template <size_t D, size_t N>
            struct get<D, N>
            {
                static_assert(N > 0, "Missing arguments list for get<N, Ts...>!");
            };

            template <size_t N, typename T, typename... Ts>
            struct get<1, N, T, Ts...> : public get<
                                             (N > 16 ? (N > 64 ? 64 : 16) : 1),
                                             N - 1, Ts...>
            {
            };

            template <typename T, typename... Ts>
            struct get<1, 0, T, Ts...>
            {
                typedef T type;
            };

            template <typename T, typename... Ts>
            struct get<16, 0, T, Ts...>
            {
                typedef T type;
            };

            template <typename T, typename... Ts>
            struct get<64, 0, T, Ts...>
            {
                typedef T type;
            };

            template <
                size_t N, typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename T7, typename T8,
                typename T9, typename T10, typename T11, typename T12,
                typename T13, typename T14, typename T15, typename... Ts>
            struct get<
                16, N, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
                T13, T14, T15, Ts...> : get<1, N - 16, Ts...>
            {
            };

            template <
                size_t N, typename T0, typename T1, typename T2, typename T3,
                typename T4, typename T5, typename T6, typename T7, typename T8,
                typename T9, typename T10, typename T11, typename T12,
                typename T13, typename T14, typename T15, typename T16,
                typename T17, typename T18, typename T19, typename T20,
                typename T21, typename T22, typename T23, typename T24,
                typename T25, typename T26, typename T27, typename T28,
                typename T29, typename T30, typename T31, typename T32,
                typename T33, typename T34, typename T35, typename T36,
                typename T37, typename T38, typename T39, typename T40,
                typename T41, typename T42, typename T43, typename T44,
                typename T45, typename T46, typename T47, typename T48,
                typename T49, typename T50, typename T51, typename T52,
                typename T53, typename T54, typename T55, typename T56,
                typename T57, typename T58, typename T59, typename T60,
                typename T61, typename T62, typename T63, typename... Ts>
            struct get<
                64, N, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
                T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25,
                T26, T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38,
                T39, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49, T50, T51,
                T52, T53, T54, T55, T56, T57, T58, T59, T60, T61, T62, T63,
                Ts...> : get<1, N - 64, Ts...>
            {
            };

            template <size_t N, typename...>
            struct skip;

            template <size_t N, typename T, typename... Ts>
            struct skip<N, T, Ts...> : skip<N - 1, Ts...>
            {
            };

            template <typename T, typename... Ts>
            struct skip<0, T, Ts...>
            {
                typedef type_list<T, Ts...> type;
            };

            template <>
            struct skip<0>
            {
                typedef type_list<> type;
            };
        }

        /// \private
        template <size_t, typename>
        struct get;

        /**
         * Provides a member typedef type which is the
         * N-th type in the provided type_list.
         *
         * \code{.cpp}
         * typename get<0, type_list<int, float>>::type -> int
         * typename get<1, type_list<int, float>>::type -> float
         * \endcode
         */
        template <size_t N, typename... Ts>
        struct get<N, type_list<Ts...>> : detail::get<1, N, Ts...>
        {
        };

        /**
         * The N-th type in the provided type_list.
         * @see get
         */
        template <size_t N, typename TypeList>
        using get_t = typename get<N, TypeList>::type;

        /// \private
        template <size_t, typename>
        struct skip;

        /**
         * Skips the first N types in the provided type_list.
         * Provides a member typedef equivalent to the resuling type_list.
         *
         * \code{.cpp}
         * typename skip<1, type_list<int, float, double>>::type -> type_list<float, double>
         * typename skip<0, type_list<int, float, double>>::type -> type_list<int, float, double>
         * \endcode
         */
        template <size_t N, typename... Ts>
        struct skip<N, type_list<Ts...>> : detail::skip<N, Ts...>
        {
        };

        /**
         * Skips the first N types in the provided type_list.
         * @see skip
         */
        template <size_t N, typename TypeList>
        using skip_t = typename skip<N, TypeList>::type;

        /// \private
        template <typename>
        struct as_type_list;

        /**
         * Provides a member typedef type which is a type_list with
         * template type parameters equivalent to the type parameters of the provided
         * type. The provided type must be a template instance.
         *
         * \code{.cpp}
         * typename as_type_list<std::tuple<int, float>>::type -> type_list<int, float>
         * \endcode
         */
        template <template <typename...> typename T, typename... Ts>
        struct as_type_list<T<Ts...>>
        {
            typedef type_list<Ts...> type;
        };

        /// \private
        template <typename T>
        struct as_type_list : as_type_list<remove_qualifiers_t<T>>
        {
        };

        /**
         * A typedef for a type_list with
         * template type parameters equivalent to the type parameters of the provided
         * type. The provided type must be a template instance.
         * @see as_type_list
         */
        template <typename T>
        using as_type_list_t = typename as_type_list<T>::type;

        /// \private
        template <typename>
        struct as_tuple;

        /**
         * Provides a member typedef which is a std::tuple specialization with
         * template type parameters equivalent to the type parameters of the provided
         * type. The provided type must be a template specialization.
         *
         * \code{.cpp}
         * typename as_tuple<type_list<int, float>>::type -> std::tuple<int, float>
         * \endcode
         */
        template <template <typename...> typename T, typename... Ts>
        struct as_tuple<T<Ts...>>
        {
            typedef std::tuple<Ts...> type;
        };

        /// \private
        template <typename T>
        struct as_tuple : as_tuple<remove_qualifiers_t<T>>
        {
        };

        /**
         * A typedef for a std::tuple specialization with
         * template type parameters equivalent to the type parameters of the provided
         * type. The provided type must be a template specialization.
         * @see as_tuple
         */
        template <typename T>
        using as_tuple_t = typename as_tuple<T>::type;

        /**
         * Accesses first type in the list.
         */
        template <typename TypeList>
        using first = get<0, TypeList>;

        /**
         * Accesses last type in the list.
         * @see last
         */
        template <typename TypeList>
        using first_t = typename first<TypeList>::type;

        /**
         * Accesses last type in the list.
         */
        template <typename TypeList>
        using last = get<TypeList::size - 1, TypeList>;

        /**
         * Accesses last type in the list.
         * @see last
         */
        template <typename TypeList>
        using last_t = typename last<TypeList>::type;

        /**
         * Returns all but the first element of the list.
         */
        template <typename TypeList>
        using tail = skip<1, TypeList>;

        /**
         * Returns all but the first element of the list.
         * @see tail
         */
        template <typename TypeList>
        using tail_t = typename tail<TypeList>::type;

        namespace detail
        {
            template <typename, size_t, typename>
            struct take;

            template <typename... Us>
            struct take<type_list<Us...>, 0, type_list<>>
            {
                using type = type_list<Us...>;
            };

            template <typename... Us, typename T, typename... Ts>
            struct take<type_list<Us...>, 0, type_list<T, Ts...>>
            {
                using type = type_list<Us...>;
            };

            template <size_t N, typename... Us, typename T, typename... Ts>
            struct take<type_list<Us...>, N, type_list<T, Ts...>>
            {
                using type = typename take<type_list<Us..., T>, N - 1, type_list<Ts...>>::type;
            };
        }

        /**
         * Returns the first N elements of the list.
         */
        template <size_t N, typename TypeList>
        using take = detail::take<type_list<>, N, TypeList>;

        /**
         * Returns the first N elements of the list.
         */
        template <size_t N, typename TypeList>
        using take_t = typename take<N, TypeList>::type;

        /**
         * Returns all but the last element of the list.
         */
        template <typename TypeList>
        using init = take<TypeList::size - 1, TypeList>;

        /**
         * Returns all but the last element of the list.
         * @see tail
         */
        template <typename TypeList>
        using init_t = typename init<TypeList>::type;

        namespace detail
        {
            template <typename, typename>
            struct reverse_impl;

            template <typename... Us>
            struct reverse_impl<type_list<Us...>, type_list<>>
            {
                using type = type_list<Us...>;
            };

            template <typename... Us, typename T, typename... Ts>
            struct reverse_impl<type_list<Us...>, type_list<T, Ts...>>
            {
                using type = typename reverse_impl<type_list<T, Us...>, type_list<Ts...>>::type;
            };
        } // namespace detail

        /**
         * Reverses a list of types.
         *
         * \code{.cpp}
         * typename reverse<type_list<int, float>>::type -> type_list<float, int>
         * \endcode
         */
        template <typename TypeList>
        struct reverse : detail::reverse_impl<type_list<>, TypeList>
        {
        };

        /**
         * Reverses a list of types.
         * @see reverse
         */
        template <typename TypeList>
        using reverse_t = typename reverse<TypeList>::type;

        /**
         * Concatenates N lists together.
         *
         * \code{.cpp}
         * typename concat<type_list<int, float>, type_list<double>, type_list<long>>::type -> type_list<int, float, double, long>
         * \endcode
         */
        template <typename...>
        struct concat;

        /// \private
        template <>
        struct concat<>
        {
            using type = type_list<>;
        };

        /// \private
        template <typename... Ts>
        struct concat<type_list<Ts...>>
        {
            using type = type_list<Ts...>;
        };

        /**
         * Concatenates two lists together.
         */
        /// \private
        template <typename... Ts, typename... Us>
        struct concat<type_list<Ts...>, type_list<Us...>>
        {
            using type = type_list<Ts..., Us...>;
        };

        /**
         * Concatenates N lists together.
         */
        /// \private
        template <typename TypeList1, typename TypeList2, typename... TypeLists>
        struct concat<TypeList1, TypeList2, TypeLists...> : concat<typename concat<TypeList1, TypeList2>::type, TypeLists...>
        {
        };

        /**
         * Concatenates two lists together.
         * @see concat
         */
        template <typename... Ts>
        using concat_t = typename concat<Ts...>::type;

        /**
         * Appends a type to the list.
         */
        template <typename T, typename TypeList>
        struct append : concat<TypeList, type_list<T>>
        {
        };

        /**
         * Appends a type to the list.
         * @see prepend
         */
        template <typename T, typename TypeList>
        using append_t = typename append<T, TypeList>::type;

        template <typename, typename>
        struct prepend;

        /**
         * Prepends a type to the list.
         */
        template <typename T, typename TypeList>
        struct prepend : concat<type_list<T>, TypeList>
        {
        };

        /**
         * Prepends a type to the list.
         * @see prepend
         */
        template <typename T, typename TypeList>
        using prepend_t = typename prepend<T, TypeList>::type;

        namespace detail
        {
            template <template<typename> typename, typename...>
            struct filter_impl;

            template <template<typename> typename Predicate>
            struct filter_impl<Predicate>
            {
                using type = type_list<>;
            };

            template <template<typename> typename Predicate, typename Head, typename... Tail>
            struct filter_impl<Predicate, Head, Tail...>
            {
                using type = std::conditional_t<Predicate<Head>::value,
                    prepend_t<Head, typename filter_impl<Predicate, Tail...>::type>,
                    typename filter_impl<Predicate, Tail...>::type
                >;
            };

            template <template<typename> typename, typename...>
            struct map_impl;

            template <template<typename> typename Mapper>
            struct map_impl<Mapper>
            {
                using type = type_list<>;
            };

            template <template<typename> typename Mapper, typename Head, typename ...Tail>
            struct map_impl<Mapper, Head, Tail...>
            {
                using type = typename prepend<typename Mapper<Head>::type,
                    typename map_impl<Mapper, Tail...>::type>::type;
            };
        }

        /// \private
        template <template<typename> typename, typename>
        struct filter;

        /**
         * Filters a type_list according to a predicate template.
         *
         * \code{.cpp}
         * typename filter<std::is_reference, type_list<int, float&, double>>::type -> type_list<float&>
         * \endcode
         */
        template <template<typename> typename Predicate, typename... Ts>
        struct filter<Predicate, type_list<Ts...>>
        {
            using type = typename detail::filter_impl<Predicate, Ts...>::type;
        };

        /**
         * Filters a type_list according to a predicate template
         * with a static boolean member named "value" (e.g. std::is_trivial)
         * @see filter
         */
        template <template<typename> typename Predicate, typename TypeList>
        using filter_t = typename filter<Predicate, TypeList>::type;

        /// \private
        template <template<typename> typename, typename>
        struct map;

        /**
         * Transforms a type_list according to a predicate template.
         *
         * \code{.cpp}
         * typename map<std::add_reference, type_list<int, float&, double>>::type -> type_list<int&, float&, double&>
         * \endcode
         */
        template <template<typename> typename Mapper, typename... Ts>
        struct map<Mapper, type_list<Ts...>>
        {
            using type = typename detail::map_impl<Mapper, Ts...>::type;
        };

        /**
         * Transforms a type_list according to a predicate template
         * with a typedef named "type" (e.g. std::remove_reference)
         * @see map
         */
        template <template<typename> typename Mapper, typename... Ts>
        using map_t = typename map<Mapper, Ts...>::type;

        namespace detail
        {
            template <typename T>
            struct is_instance : public std::false_type {};

            template <template<typename...> typename T, typename... Args>
            struct is_instance<T<Args...>> : public std::true_type {};
        } // namespace detail

        /**
         * Detects whether T is a template specialization.
         * Inherits from std::bool_constant<>.
         *
         * \code{.cpp}
         * is_instance<type_list<>>::value -> true
         * is_instance<int>::value -> false
         * \endcode
         */
        template <typename T>
        struct is_instance : detail::is_instance<T>
        {
        };

        /**
         * Detects whether T is a template specialization.
         * @see is_instance
         */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_instance_v{ is_instance<T>::value };

        namespace detail
        {
            /**
             * Checks if T == U<Args...>.
             * If U<Args...> != T or is invalid the result is false.
             */
            template <typename T, template<typename...> typename U, typename... Args>
            struct is_same_template
            {
                template <template<typename...> typename V, typename = V<Args...>>
                static auto test(int) -> std::is_same<V<Args...>, T>;

                template <template<typename...> typename V>
                static std::false_type test(...);

                static constexpr bool value{decltype(test<U>(0))::value};
            };

            template <template<typename...> typename T, typename U>
            struct is_instance_of : public std::false_type {};

            template <template<typename...> typename T, template<typename...> typename U, typename... Args>
            struct is_instance_of<T, U<Args...>> : public is_same_template<U<Args...>, T, Args...>
            {
            };
        }

        /**
         * Detects whther the type U is a template specialization of T.
         * (e.g. is_instance_of<std::vector<>, std::vector<int>>)
         * Inherits from std::bool_constant<>.
         *
         * \code{.cpp}
         * is_instance_of<type_list, type_list<int>>::value -> true
         * is_instance_of<type_list, std::tuple<int>>::value -> false
         * \endcode
         */
        template <template<typename...>typename T, typename U>
        struct is_instance_of : detail::is_instance_of<T, std::remove_cv_t<U>>
        {
        };

        /**
         * Detects whther the type U is a template specialization of T.
         * @see is_instance_of_v
         */
        template <template<typename...>typename T, typename U>
        [[maybe_unused]] static constexpr bool is_instance_of_v{ is_instance_of<T, U>::value };

        /// \private
        template <typename, typename>
        struct contains;

        /**
         * Checks whether T is contained in the list of types.
         * Inherits from std::bool_constant<>.
         *
         * \code{.cpp}
         * contains<int, type_list<int, float>>::value -> true
         * contains<double, type_list<int, float>>::value -> false
         * \endcode
         */
        template <typename T, typename... Ts>
        struct contains<T, type_list<Ts...>> : std::disjunction<std::is_same<std::remove_cv_t<T>, std::remove_cv_t<Ts>>...>
        {
        };

        /**
         * Checks whether T is contained in the list of types.
         * @see contains
         */
        template <typename T, typename TypeList>
        [[maybe_unused]] static constexpr bool contains_v = contains<T, TypeList>::value;

        /// \private
        template <template<typename...> typename, typename>
        struct contains_instance;

        /**
         * Checks whether an instance of the template T is contained in the list of types.
         * Inherits from std::bool_constant<>.
         *
         * \code{.cpp}
         * contains_instance<std::tuple, type_list<int, float, std::tuple<short, double>>>::value -> true
         * contains_instance<std::vector, type_list<int, float, std::tuple<short, double>>>::value -> false
         * \endcode
         */
        template <template<typename...> typename T, typename... Ts>
        struct contains_instance<T, type_list<Ts...>> : std::disjunction<trait::is_instance_of<T, std::remove_cv_t<Ts>>...>
        {
        };

        /**
         * Checks whether an instance of the template T is contained in the list of types.
         * @see contains_instance
         */
        template <template<typename...> typename T, typename TypeList>
        [[maybe_unused]] static constexpr bool contains_instance_v = contains_instance<T, TypeList>::value;

        /// \private
        template <typename, typename>
        struct contains_base;

        /**
         * Checks whether a type deriving from T is contained in the list of types.
         * Inherits from std::bool_constant<>.
         *
         * \code{.cpp}
         * struct Base {};
         * struct Derived : Base {};
         * contains_base<Base, type_list<int, float, Derived>>::value -> true
         * contains_base<Base, type_list<int, float, Base>>::value -> true
         * contains_base<int, type_list<int, float, Derived>>::value -> false
         * \endcode
         */
        template <typename T, typename... Ts>
        struct contains_base<T, type_list<Ts...>> : std::disjunction<std::is_base_of<std::remove_cv_t<T>, std::remove_cv_t<Ts>>...>
        {
        };

        /**
         * Checks whether a type deriving from T is contained in the list of types.
         * @see contains_base
         */
        template <typename T, typename TypeList>
        [[maybe_unused]] static constexpr bool contains_base_v = contains_base<T, TypeList>::value;

        namespace detail
        {
            template <typename T, ptrdiff_t N, typename... Ts>
            constexpr ptrdiff_t index_of() noexcept
            {
                if constexpr (sizeof...(Ts) <= N) return -1;
                else if constexpr (std::is_same_v<T, trait::get_t<N, type_list<Ts...>>>) return N;
                else return index_of<T, N + 1, Ts...>();
            }

            template <typename T, ptrdiff_t N, typename... Ts>
            constexpr ptrdiff_t index_of_base() noexcept
            {
                if constexpr (sizeof...(Ts) <= N) return -1;
                else if constexpr (std::is_base_of_v<T, trait::get_t<N, type_list<Ts...>>>) return N;
                else return index_of_base<T, N + 1, Ts...>();
            }

            template <template<typename...> typename T, ptrdiff_t N, typename... Ts>
            constexpr ptrdiff_t index_of_instance() noexcept
            {
                if constexpr (sizeof...(Ts) <= N) return -1;
                else if constexpr (is_instance_of_v<T, trait::get_t<N, type_list<Ts...>>>) return N;
                else return index_of_instance<T, N + 1, Ts...>();
            }

            // This variable template was introduced to fix the build on VS2017, which
            // chokes when invoking index_of_instance() directly from struct index_of_instance.
            template <template<typename...> typename T, ptrdiff_t N, typename... Ts>
            static constexpr ptrdiff_t index_of_instance_v = index_of_instance<T, N, Ts...>();
        } // namespace detail

        /// \private
        template <typename, typename>
        struct index_of;

        /**
         * The index of the type in the type list, -1 if it doesn't exist.
         * @see contains
         */
        template <typename T, typename... Ts>
        struct index_of<T, type_list<Ts...>> : std::integral_constant<ptrdiff_t, detail::index_of<T, 0, Ts...>()>
        {
        };

        /**
         * The index of the type in the type list, -1 if it doesn't exist.
         * @see index_of
         */
        template <typename T, typename TypeList>
        static constexpr ptrdiff_t index_of_v = index_of<T, TypeList>::value;

        /// \private
        template <typename, typename>
        struct index_of_base;

        /**
         * The index of the type in the type list that is derived from T, -1 if it doesn't exist.
         * @see contains_base
         */
        template <typename T, typename... Ts>
        struct index_of_base<T, type_list<Ts...>> : std::integral_constant<ptrdiff_t, detail::index_of_base<T, 0, Ts...>()>
        {
        };

        /**
         * The index of the type in the type list that is derived from T, -1 if it doesn't exist.
         * @see index_of_base
         */
        template <typename T, typename TypeList>
        static constexpr ptrdiff_t index_of_base_v = index_of_base<T, TypeList>::value;

        /// \private
        template <template<typename...> typename, typename>
        struct index_of_instance;

        /**
         * The index of the type in the type list that is a template instance of T, -1 if it doesn't exist.
         * @see contains_instance
         */
        template <template<typename...> typename T, typename... Ts>
        struct index_of_instance<T, type_list<Ts...>> : std::integral_constant<ptrdiff_t, detail::index_of_instance_v<T, 0, Ts...>>
        {
        };

        /**
         * The index of the type in the type list that is a template instance of T, -1 if it doesn't exist.
         * @see index_of_instance
         */
        template <template<typename...> typename T, typename TypeList>
        static constexpr ptrdiff_t index_of_instance_v = index_of_instance<T, TypeList>::value;

        namespace detail
        {
            template <typename, typename>
            struct unique_impl;

            template <typename UniqueList>
            struct unique_impl<UniqueList, type_list<>>
            {
                using type = UniqueList;
            };

            template <typename UniqueList, typename T, typename... Ts>
            struct unique_impl<UniqueList, type_list<T, Ts...>> :
                std::conditional_t<contains_v<T, UniqueList>,
                    unique_impl<UniqueList, type_list<Ts...>>,
                    unique_impl<append_t<T, UniqueList>, type_list<Ts...>>>
            {
            };
        } // namespace detail

        /**
         * Creates a new list containing the repeating elements in the source list only once.
         *
         * \code{.cpp}
         * typename unique<type_list<int, float, int>>::type -> type_list<int, float>
         * \endcode
         */
        template <typename T>
        struct unique : detail::unique_impl<type_list<>, T>
        {
        };

        /**
         * Creates a new list containing the repeating elements in the source list only once.
         */
        template <typename T>
        using unique_t = typename unique<T>::type;

    } // namespace trait

    namespace util
    {
        /**
         * Ignores all parameters. Can take an optional template parameter
         * specifying the return type of ignore. The return object is iniailized by {}.
         */
        template <typename T = int, typename... Ts>
        constexpr int ignore(Ts&&...) noexcept
        {
            return {};
        }

        /**
         * Returns the input paratemeter as-is. Useful for expanding variadic
         * template lists when only one arguments is known to be present.
         */
        template <typename T>
        constexpr decltype(auto) identity(T&& t) noexcept
        {
            return std::forward<T>(t);
        }

        /**
         * Adds const to the input reference.
         */
        template <typename T>
        constexpr const T& make_const(const T& value) noexcept
        {
            return value;
        }

        /**
         * Adds const to the input reference.
         */
        template <typename T>
        constexpr const T& make_const(T& value) noexcept
        {
            return value;
        }

        /**
        * Creates an array of type 'T' from the provided tuple.
        * The common type T needs to be specified, in order to prevent any
        * errors when using the overload taking an empty std::tuple (as there is no common type then).
        */
        template <typename T, typename... Ts>
        constexpr std::array<T, sizeof...(Ts)> to_array(const std::tuple<Ts...>& tuple) noexcept
        {
            return std::apply([](auto&& ... args) -> std::array<T, sizeof...(Ts)> { return { std::forward<decltype(args)>(args)... }; }, tuple);
        }

        /**
         * Creates an empty array of type 'T.
         */
        /// \private
        template <typename T>
        constexpr std::array<T, 0> to_array(const std::tuple<>&) noexcept
        {
            return {};
        }

        namespace detail
        {
            template <typename T, size_t... Idx>
            constexpr auto to_tuple([[maybe_unused]] const std::array<T, sizeof...(Idx)>& array, std::index_sequence<Idx...>) noexcept
            {
                if constexpr (sizeof...(Idx) == 0) return std::tuple<>{};
                else return std::make_tuple(std::get<Idx>(array)...);
            }
        }

        /**
         * Creates a tuple from the provided array.
         */
        template <typename T, size_t N>
        constexpr auto to_tuple(const std::array<T, N>& array) noexcept
        {
            return detail::to_tuple<T>(array, std::make_index_sequence<N>{});
        }

        /**
         * Creates a matching std::tuple from a type_list.
         * Types in the type_list must be Trivial.
         */
        template <typename... Ts>
        constexpr std::tuple<Ts...> as_tuple(type_list<Ts...>) noexcept
        {
            static_assert((... && std::is_trivial_v<Ts>), "Non-trivial types in type_list as not allowed!");
            return {};
        }

        /**
         * Creates a matching type_list from a std::tuple.
         */
        template <typename... Ts>
        constexpr type_list<Ts...> as_type_list(const std::tuple<Ts...>&) noexcept
        {
            return {};
        }

        namespace detail
        {
            template <typename F, typename T>
            constexpr auto invoke_optional_index(F&& f, T&& t, size_t idx, int) -> decltype(f(std::forward<T>(t), idx))
            {
                return f(std::forward<T>(t), idx);
            }

            template <typename F, typename T>
            constexpr auto invoke_optional_index(F&& f, T&& t, size_t, ...) -> decltype(f(std::forward<T>(t)))
            {
                return f(std::forward<T>(t));
            }

            template <typename F, typename... Carry>
            constexpr auto eval_in_order_to_tuple(type_list<>, std::index_sequence<>, F&&, Carry&&... carry)
            {
                if constexpr (sizeof...(Carry) == 0) return std::tuple<>{};
                else return std::make_tuple(std::forward<Carry>(carry)...);
            }

            // This workaround is needed since C++ does not specify
            // the order in which function arguments are evaluated and this leads
            // to incorrect order of evaluation (noticeable when using indexes).
            // Otherwise we could simply do std::make_tuple(f(Ts{}, Idx)...).
            template <typename F, typename T, typename... Ts, size_t I, size_t... Idx, typename... Carry>
            constexpr auto eval_in_order_to_tuple(type_list<T, Ts...>, std::index_sequence<I, Idx...>, F&& f, Carry&&... carry)
            {
                static_assert(std::is_trivial_v<T>, "Argument is a non-trivial type!");

                auto&& result = invoke_optional_index(f, T{}, I, 0);
                return eval_in_order_to_tuple(
                    type_list<Ts...>{},
                    std::index_sequence<Idx...>{},
                    std::forward<F>(f),
                    std::forward<Carry>(carry)..., // carry the previous results over
                    std::forward<decltype(result)>(result) // pass the current result after them
                );
            }

            template <typename F>
            constexpr void eval_in_order(type_list<>, std::index_sequence<>, [[maybe_unused]]F&& f)
            {
            }

            // This workaround is needed since C++ does not specify
            // the order in which function arguments are evaluated and this leads
            // to incorrect order of evaluation (noticeable when using indexes).
            template <typename F, typename T, typename... Ts, size_t I, size_t... Idx>
            constexpr void eval_in_order(type_list<T, Ts...>, std::index_sequence<I, Idx...>, F&& f)
            {
                static_assert(std::is_trivial_v<T>, "Argument is a non-trivial type!");

                invoke_optional_index(f, T{}, I, 0);
                return eval_in_order(
                    type_list<Ts...>{},
                    std::index_sequence<Idx...>{},
                    std::forward<F>(f)
                );
            }
        }

        /**
         * Applies function F to each type in the type_list, aggregating
         * the results in a tuple. F can optionally take an index of type size_t.
         *
         * \code{.cpp}
         * map_to_tuple(reflect_types(type_list<int, float, double>{}), [](auto td) {
         *   return get_name(td);
         * })
         *   -> std::tuple{const_string{"int"}, const_string{"float"}, const_string{"double"}}
         * \endcode
         */
        template <typename F, typename... Ts>
        constexpr auto map_to_tuple(type_list<Ts...> list, F&& f)
        {
            return detail::eval_in_order_to_tuple(list, std::make_index_sequence<sizeof...(Ts)>{}, std::forward<F>(f));
        }

        /**
         * Applies function F to each type in the type_list, aggregating
         * the results in an array. F can optionally take an index of type size_t.
         *
         * \code{.cpp}
         * map_to_array<std::string>(reflect_types(type_list<int, float, double>{}), [](auto td) {
         *   return get_name(td).str();
         * })
         *   -> std::array{std::string{"int"}, std::string{"float"}, std::string{"double"}}
         * \endcode
         */
        template <typename T, typename F, typename... Ts>
        constexpr auto map_to_array(type_list<Ts...> list, F&& f)
        {
            return to_array<T>(map_to_tuple(list, std::forward<F>(f)));
        }

        /**
         * Applies function F to each type in the type_list.
         * F can optionally take an index of type size_t.
         *
         * \code{.cpp}
         * for_each(reflect_types(type_list<int, float, double>{}), [](auto td) {
         *   std::cout << get_name(td) << '\n';
         * });
         * \endcode
         */
        template <typename F, typename... Ts>
        constexpr void for_each(type_list<Ts...> list, F&& f)
        {
            detail::eval_in_order(list, std::make_index_sequence<sizeof...(Ts)>{}, std::forward<F>(f));
        }

        /*
         * Returns the initial_value unchanged.
         */
        /// \private
        template <typename R, typename F, typename... Ts>
        constexpr R accumulate(type_list<>, F&&, R&& initial_value)
        {
            return std::forward<R>(initial_value);
        }

        /*
        * Applies an accumulation function F to each type in the type_list.
        * Note: Breaking changes introduced in v0.7.0:
        *   Behaviour changed to imitate std::accumulate.
        *   F can now no longer take a second index argument.
        */
        template <typename R, typename F, typename T, typename... Ts>
        constexpr auto accumulate(type_list<T, Ts...>, F&& f, R&& initial_value)
        {
            static_assert(std::is_trivial_v<T>, "Argument is a non-trivial type!");

            return accumulate(type_list<Ts...> {},
                std::forward<F>(f),
                std::forward<std::invoke_result_t<F&&, R&&, T&&>>(
                    f(std::forward<R>(initial_value), T {})));
        }

        /**
         * Counts the number of times the predicate F returns true.
        * Note: Breaking changes introduced in v0.7.0:
        *   F can now no longer take a second index argument.
         */
        template <typename F, typename... Ts>
        constexpr size_t count_if(type_list<Ts...> list, F&& f)
        {
            return accumulate<size_t>(list,
                [&](size_t acc, const auto& t) -> size_t { return acc + (f(t) ? 1 : 0); },
                0);
        }

        namespace detail
        {
            template <typename, bool...>
            struct apply_mask;

            template <>
            struct apply_mask<type_list<>>
            {
                using type = type_list<>;
            };

            template <typename T, typename... Ts, bool... Bs>
            struct apply_mask<type_list<T, Ts...>, true, Bs...>
            {
                static_assert(std::is_trivial_v<T>, "Argument is a non-trivial type!");
                using type = trait::prepend_t<T, typename apply_mask<type_list<Ts...>, Bs...>::type>;
            };

            template <typename T, typename... Ts, bool... Bs>
            struct apply_mask<type_list<T, Ts...>, false, Bs...> : apply_mask<type_list<Ts...>, Bs...>
            {
                static_assert(std::is_trivial_v<T>, "Argument is a non-trivial type!");
            };

            template <typename F, typename... Ts>
            constexpr auto filter([[maybe_unused]] F f, type_list<Ts...>)
            {
                return typename apply_mask<type_list<Ts...>, f(Ts{})...>::type{};
            }
        }

        /**
         * Filters the list according to a *constexpr* predicate.
         * Calling f(Ts{})... should be valid in a constexpr context.
         *
         * \code{.cpp}
         * filter(reflect_types(type_list<int, long, float>{}), [](auto td) {
         *   return std::is_integral_v<typename decltype(td)::type>;
         * })
         *   -> type_list<type_descriptor<int>, type_descriptor<long>>
         * \endcode
         */
        template <typename F, typename... Ts>
        constexpr auto filter(type_list<Ts...> list, F&& f)
        {
            return decltype(detail::filter(std::forward<F>(f), list))();
        }

        /**
         * Returns the first instance that matches the *constexpr* predicate.
         * Calling f(Ts{})... should be valid in a constexpr context.
         */
        template <typename F, typename... Ts>
        constexpr auto find_first(type_list<Ts...> list, F&& f)
        {
            using result_list = decltype(detail::filter(std::forward<F>(f), list));
            static_assert(result_list::size != 0, "find_first did not match anything!");
            return trait::get_t<0, result_list>{};
        }

        /**
         * Returns the only instance that matches the *constexpr* predicate.
         * If there is no match or multiple matches, fails with static_assert.
         * Calling f(Ts{})... should be valid in a constexpr context.
         */
        template <typename F, typename... Ts>
        constexpr auto find_one(type_list<Ts...> list, F&& f)
        {
            using result_list = decltype(detail::filter(std::forward<F>(f), list));
            static_assert(result_list::size != 0, "find_one did not match anything!");
            static_assert(result_list::size == 1, "Cannot resolve multiple matches in find_one!");
            return trait::get_t<0, result_list>{};
        }

        /**
         * Returns true if any item in the list matches the predicate.
         * Calling f(Ts{})... should be valid in a constexpr context.
         */
        template <typename F, typename... Ts>
        constexpr bool contains(type_list<Ts...> list, F&& f)
        {
            using result_list = decltype(detail::filter(std::forward<F>(f), list));
            return result_list::size > 0;
        }

        /**
         * Returns true if the type_list contains the specified type.
         * @see refl::trait::contains
         */
        template <typename T, typename... Ts>
        constexpr bool contains(type_list<Ts...>)
        {
            return trait::contains_v<T, type_list<Ts...>>;
        }

        /**
         * Returns true if the tuple contains the specified type or a supertype.
         * @see refl::trait::contains_base
         */
        template <typename T, typename... Ts>
        constexpr bool contains_base(const std::tuple<Ts...>&)
        {
            return trait::contains_base_v<T, type_list<Ts...>>;
        }

        /**
         * Returns true if the tuple contains an instance of the specified type.
         * @see refl::trait::contains_instance
         */
        template <template <typename...> typename T, typename... Ts>
        constexpr bool contains_instance(const std::tuple<Ts...>&)
        {
            return trait::contains_instance_v<T, type_list<Ts...>>;
        }

        /**
         * Applies a function to the elements of the type_list.
         *
         * \code{.cpp}
         * apply(reflect_types(type_list<int, long, float>{}), [](auto td_int, auto td_long, auto td_float) {
         *   return get_name(td_int) + " " +get_name(td_long) + " " + get_name(td_float);
         * })
         *   -> "int long float"
         * \endcode
         */
        template <typename... Ts, typename F>
        constexpr auto apply(type_list<Ts...>, F&& f)
        {
            return f(Ts{}...);
        }

        /** A synonym for std::get<N>(tuple). */
        template <size_t N, typename... Ts>
        constexpr auto& get(std::tuple<Ts...>& ts) noexcept
        {
            return std::get<N>(ts);
        }

        /** A synonym for std::get<N>(tuple). */
        template <size_t N, typename... Ts>
        constexpr const auto& get(const std::tuple<Ts...>& ts) noexcept
        {
            return std::get<N>(ts);
        }

        /** A synonym for std::get<T>(tuple). */
        template <typename T, typename... Ts>
        constexpr T& get(std::tuple<Ts...>& ts) noexcept
        {
            return std::get<T>(ts);
        }

        /** A synonym for std::get<T>(tuple). */
        template <typename T, typename... Ts>
        constexpr const T& get(const std::tuple<Ts...>& ts) noexcept
        {
            return std::get<T>(ts);
        }

        /** Returns the value of type U, where U is a template instance of T. */
        template <template<typename...> typename T, typename... Ts>
        constexpr auto& get_instance(std::tuple<Ts...>& ts) noexcept
        {
            static_assert((... || trait::is_instance_of_v<T, Ts>), "The tuple does not contain a type that is a template instance of T!");
            constexpr size_t idx = static_cast<size_t>(trait::index_of_instance_v<T, type_list<Ts...>>);
            return std::get<idx>(ts);
        }

        /** Returns the value of type U, where U is a template instance of T. */
        template <template<typename...> typename T, typename... Ts>
        constexpr const auto& get_instance(const std::tuple<Ts...>& ts) noexcept
        {
            static_assert((... || trait::is_instance_of_v<T, Ts>), "The tuple does not contain a type that is a template instance of T!");
            constexpr size_t idx = static_cast<size_t>(trait::index_of_instance_v<T, type_list<Ts...>>);
            return std::get<idx>(ts);
        }

        /**
         * Converts a type_list of types to a type_list of the type_descriptors for these types.
         *
         * \code{.cpp}
         * reflect_types(type_list<int, float>{}) -> type_list<type_descriptor<int>, type_descriptor<float>>{}
         * \endcode
         */
        template <typename... Ts>
        constexpr type_list<descriptor::type_descriptor<Ts>...> reflect_types(type_list<Ts...>) noexcept
        {
            return {};
        }

        /**
         * Converts a type_list of type_descriptors to a type_list of the target types.
         *
         * \code{.cpp}
         * unreflect_types(type_list<type_descriptor<int>, type_descriptor<float>>{}) -> type_list<int, float>{}
         * \endcode
         */
        template <typename... Ts>
        constexpr type_list<Ts...> unreflect_types(type_list<descriptor::type_descriptor<Ts>...>) noexcept
        {
            return {};
        }
    } // namespace util

    /**
     * @brief Contains the definitions of the built-in attributes
     *
     * Contains the definitions of the built-in attributes which
     * are implicitly available in macro context as well as the
     * attr::usage namespace which contains constraints
     * for user-provieded attributes.
     *
     * # Examples
     * ```
     * REFL_TYPE(Point, debug(custom_printer))
     *     REFL_FIELD(x)
     *     REFL_FIELD(y)
     * REFL_END
     * ```
     */
    namespace attr
    {
        /**
         * @brief Contains a number of constraints applicable to refl-cpp attributes.
         *
         * Contains base types which create compile-time constraints
         * that are verified by refl-cpp. These base-types must be inherited
         * by custom attribute types.
         */
        namespace usage
        {
            /**
             * Specifies that an attribute type inheriting from this type can
             * only be used with REFL_TYPE()
             */
            struct type {};

            /**
             * Specifies that an attribute type inheriting from this type can
             * only be used with REFL_FUNC()
             */
            struct function {};

            /**
             * Specifies that an attribute type inheriting from this type can
             * only be used with REFL_FIELD()
             */
            struct field {};

            /**
             * Specifies that an attribute type inheriting from this type can
             * only be used with REFL_FUNC or REFL_FIELD.
             */
            struct member : public function, public field{};

            /**
             * Specifies that an attribute type inheriting from this type can
             * only be used with any one of REFL_TYPE, REFL_FIELD, REFL_FUNC.
             */
            struct any : public member, public type {};
        }

        /**
         * Used to decorate a function that serves as a property.
         * Takes an optional friendly name.
         */
        struct property : public usage::function
        {
            const std::optional<const char*> friendly_name;

            constexpr property() noexcept
                : friendly_name{}
            {
            }

            constexpr property(const char* friendly_name) noexcept
                : friendly_name(friendly_name)
            {
            }
        };

        /**
         * Used to specify how a type should be displayed in debugging contexts.
         */
        template <typename F>
        struct debug : public usage::any
        {
            const F write;

            constexpr debug(F write)
                : write(write)
            {
            }
        };

        /**
         * Used to specify the base types of the target type.
         */
        template <typename... Ts>
        struct base_types : usage::type
        {
            /** An alias for a type_list of the base types. */
            typedef type_list<Ts...> list_type;

            /** An instance of a type_list of the base types. */
            static constexpr list_type list{ };
        };

        /**
         * Used to specify the base types of the target type.
         */
        template <typename... Ts>
        [[maybe_unused]] static constexpr base_types<Ts...> bases{ };
    } // namespace attr


    namespace detail
    {
        namespace macro_exports
        {
            using attr::property;
            using attr::debug;
            using attr::bases;
        }
    }

    namespace trait
    {
        namespace detail
        {
            template <typename T>
            auto member_type_test(int) -> decltype(typename T::member_type{}, std::true_type{});

            template <typename T>
            std::false_type member_type_test(...);
        }

        /**
         * A trait for detecting whether the type 'T' is a member descriptor.
         */
        template <typename T>
        struct is_member : decltype(detail::member_type_test<T>(0))
        {
        };

        /**
         * A trait for detecting whether the type 'T' is a member descriptor.
         */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_member_v{ is_member<T>::value };

        namespace detail
        {
            template <typename T>
            struct is_field_2 : std::is_base_of<typename T::member_type, member::field>
            {
            };
        }

        /**
         * A trait for detecting whether the type 'T' is a field descriptor.
         */
        template <typename T>
        struct is_field : std::conjunction<is_member<T>, detail::is_field_2<T>>
        {
        };

        /**
         * A trait for detecting whether the type 'T' is a field descriptor.
         */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_field_v{ is_field<T>::value };

        namespace detail
        {
            template <typename T>
            struct is_function_2 : std::is_base_of<typename T::member_type, member::function>
            {
            };
        }

        /**
         * A trait for detecting whether the type 'T' is a function descriptor.
         */
        template <typename T>
        struct is_function : std::conjunction<is_member<T>, detail::is_function_2<T>>
        {
        };

        /**
         * A trait for detecting whether the type 'T' is a function descriptor.
         */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_function_v{ is_function<T>::value };

        /**
         * Detects whether the type T is a type_descriptor.
         * Inherits from std::bool_constant<>.
         */
        template <typename T>
        struct is_type : is_instance_of<descriptor::type_descriptor, T>
        {
        };

        /**
         * Detects whether the type T is a type_descriptor.
         * @see is_type
         */
        template <typename T>
        [[maybe_unused]] constexpr bool is_type_v{ is_type<T>::value };

        /**
         * A trait for detecting whether the type 'T' is a refl-cpp descriptor.
         */
        template <typename T>
        struct is_descriptor : std::disjunction<is_type<T>, is_member<T>>
        {
        };

        /**
         * A trait for detecting whether the type 'T' is a refl-cpp descriptor.
         */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_descriptor_v{ is_descriptor<T>::value };


        /** Checks whether T is marked as a property. */
        template <typename T>
        struct is_property : std::bool_constant<
            trait::is_function_v<T> && trait::contains_v<attr::property, typename T::attribute_types>>
        {
        };

        /** Checks whether T is marked as a property. */
        template <typename T>
        [[maybe_unused]] static constexpr bool is_property_v{ is_property<T>::value };
    } // namespace trait

    /**
     * @brief Contains the basic reflection primitives
     * as well as functions operating on those primitives
     */
    namespace descriptor
    {
        namespace detail
        {
            template <typename Member>
            struct static_field_invoker
            {
                static constexpr auto invoke() -> decltype(*Member::pointer)
                {
                    return *Member::pointer;
                }

                template <typename U, typename M = Member, std::enable_if_t<M::is_writable, int> = 0>
                static constexpr auto invoke(U&& value) -> decltype(*Member::pointer = std::forward<U>(value))
                {
                    return *Member::pointer = std::forward<U>(value);
                }
            };

            template <typename Member>
            struct instance_field_invoker
            {
                template <typename T>
                static constexpr auto invoke(T&& target) -> decltype(target.*(Member::pointer))
                {
                    return target.*(Member::pointer);
                }

                template <typename T, typename U, typename M = Member, std::enable_if_t<M::is_writable, int> = 0>
                static constexpr auto invoke(T&& target, U&& value) -> decltype(target.*(Member::pointer) = std::forward<U>(value))
                {
                    return target.*(Member::pointer) = std::forward<U>(value);
                }
            };

            template <typename Member>
            static_field_invoker<Member> field_type_switch(std::true_type);

            template <typename Member>
            instance_field_invoker<Member> field_type_switch(std::false_type);

            template <typename Member>
            constexpr decltype(nullptr) get_function_pointer(...)
            {
                return nullptr;
            }

            template <typename Member>
            constexpr auto get_function_pointer(int) -> decltype(Member::pointer())
            {
                return Member::pointer();
            }

            template <typename Member, typename Pointer>
            constexpr decltype(nullptr) resolve_function_pointer(...)
            {
                return nullptr;
            }

            template <typename Member, typename Pointer>
            constexpr auto resolve_function_pointer(int) -> decltype(Member::template resolve<Pointer>())
            {
                return Member::template resolve<Pointer>();
            }

            template <typename T, size_t N>
            using make_descriptor = std::conditional_t<refl::trait::is_field_v<refl::detail::member_info<T, N>>,
                field_descriptor<T, N>,
                std::conditional_t<refl::trait::is_function_v<refl::detail::member_info<T, N>>,
                    function_descriptor<T, N>,
                    void
                >>;

            template <typename T>
            type_list<> enumerate_members(std::index_sequence<>);

            template <typename T, size_t... Idx>
            type_list<make_descriptor<T, Idx>...> enumerate_members(std::index_sequence<Idx...>);

            template <typename T>
            struct declared_member_list
            {
                static_assert(refl::trait::is_reflectable_v<T>, "This type does not support reflection!");
                using type = decltype(enumerate_members<T>(std::make_index_sequence<refl::detail::type_info<T>::member_count>{}));
            };

            template <typename T>
            using attribute_types = trait::as_type_list_t<std::remove_cv_t<decltype(refl::detail::type_info<T>::attributes)>>;

            template <typename>
            struct flatten;

            template <typename... TypeLists>
            struct flatten<type_list<TypeLists...>> : trait::concat<TypeLists...>
            {
            };

            template <typename T, typename Base>
            static constexpr void validate_base()
            {
                static_assert(std::is_base_of_v<Base, T>, "Base is not a base type of T!");
            }

            template <typename T, typename... Bases>
            static constexpr void validate_bases(type_list<Bases...>)
            {
                util::ignore((validate_base<T, Bases>(), 0)...);
            }

            template <typename T>
            static constexpr auto get_declared_base_type_list()
            {
                if constexpr (trait::contains_instance_v<attr::base_types, attribute_types<T>>) {
                    using base_types_type = trait::remove_qualifiers_t<decltype(util::get_instance<attr::base_types>(refl::detail::type_info<T>::attributes))>;
                    validate_bases<T>(base_types_type::list);
                    return typename base_types_type::list_type{};
                }
                else {
                    return type_list<>{};
                }
            }

            template <typename T>
            struct declared_base_type_list
            {
                using type = decltype(get_declared_base_type_list<T>());
            };

            template <typename T>
            struct base_type_list;

            template <typename T>
            static constexpr auto get_base_type_list()
            {
                if constexpr (trait::contains_instance_v<attr::base_types, attribute_types<T>>) {
                    using declared_bases = typename declared_base_type_list<T>::type;
                    using rec_bases = typename flatten<trait::map_t<base_type_list, declared_bases>>::type;
                    return trait::unique_t<trait::concat_t<declared_bases, rec_bases>>{};
                }
                else {
                    return type_list<>{};
                }
            }

            template <typename T>
            struct base_type_list
            {
                using type = decltype(get_base_type_list<T>());
            };

            template <typename T>
            struct member_list : flatten<trait::map_t<declared_member_list, trait::prepend_t<T, typename base_type_list<T>::type>>>
            {
            };

        } // namespace detail

        /** A type_list of the declared member descriptors of the target type T. */
        template <typename T>
        using declared_member_list = typename detail::declared_member_list<T>::type;

        /** A type_list of the declared and inherited member descriptors of the target type T. */
        template <typename T>
        using member_list = typename detail::member_list<T>::type;

        /**
         * @brief The base type for member descriptors.
         */
        template <typename T, size_t N>
        class member_descriptor_base
        {
        protected:

            typedef refl::detail::member_info<T, N> member;

        public:

            /**
             * An alias for the declaring type of the reflected member.
             *
             * \code{.cpp}
             * struct Foo { const int* x; };
             * REFL_AUTO(type(Foo), field(x))
             *
             * get_t<0, member_list<Foo>>::declaring_type -> Foo
             * \endcode
             */
            typedef T declaring_type;

            /** An alias specifying the member type of member. */
            typedef typename member::member_type member_type;

            /**
             * An alias specifying the types of the attributes of the member. (Removes CV-qualifiers.)
             * \copydetails refl::descriptor::get_attribute_types
             */
            typedef trait::as_type_list_t<std::remove_cv_t<decltype(member::attributes)>> attribute_types;

            /**
             * The type_descriptor of the declaring type.
             * \copydetails refl::descriptor::get_declarator
             */
            static constexpr type_descriptor<T> declarator{ };

            /**
             * The name of the reflected member.
             * \copydetails refl::descriptor::get_name
             */
            static constexpr auto name{ member::name };

            /**
             * The attributes of the reflected member.
             * \copydetails refl::descriptor::get_attributes
             */
            static constexpr auto attributes{ member::attributes };

        };

        /**
         * @brief Represents a reflected field.
         */
        template <typename T, size_t N>
        class field_descriptor : public member_descriptor_base<T, N>
        {
            using typename member_descriptor_base<T, N>::member;
            static_assert(trait::is_field_v<member>);

        public:

            /**
             * Type value type of the member.
             *
             * \code{.cpp}
             * struct Foo { const int* x; };
             * REFL_AUTO(type(Foo), field(x))
             *
             * get_t<0, member_list<Foo>>::value_type -> const int*
             * \endcode
             */
            typedef typename member::value_type value_type;

            /**
             * Whether the field is static or not.
             * \copydetails refl::descriptor::is_static
             */
            static constexpr bool is_static{ !std::is_member_object_pointer_v<decltype(member::pointer)> };

            /**
             * Whether the field is const or not.
             * @see refl::descriptor::is_const
             */
            static constexpr bool is_writable{ !std::is_const_v<value_type> };

            /**
             * A member pointer to the reflected field of the appropriate type.
             * \copydetails refl::descriptor::get_pointer
             */
            static constexpr auto pointer{ member::pointer };

        private:

            using invoker = decltype(detail::field_type_switch<field_descriptor>(std::bool_constant<is_static>{}));

        public:

            /**
             * Returns the value of the field. (for static fields).
             * \copydetails refl::descriptor::invoke
             */
            template <decltype(nullptr) = nullptr>
            static constexpr decltype(auto) get() noexcept
            {
                return *member::pointer;
            }

            /**
             * Returns the value of the field. (for instance fields).
             * \copydetails refl::descriptor::invoke
             */
            template <typename U>
            static constexpr decltype(auto) get(U&& target) noexcept
            {
                return target.*(member::pointer);
            }

            /**
             * A synonym for get().
             * \copydetails refl::descriptor::invoke
             */
            template <typename... Args>
            constexpr auto operator()(Args&&... args) const noexcept -> decltype(invoker::invoke(std::forward<Args>(args)...))
            {
                return invoker::invoke(std::forward<Args>(args)...);
            }

        };

        /**
         * @brief Represents a reflected function.
         */
        template <typename T, size_t N>
        class function_descriptor : public member_descriptor_base<T, N>
        {
            using typename member_descriptor_base<T, N>::member;
            static_assert(trait::is_function_v<member>);

        public:

            /**
             * Invokes the function with the given arguments.
             * If the function is an instance function, a reference
             * to the instance is provided as first argument.
             * \copydetails refl::descriptor::invoke
             */
            template <typename... Args>
            static constexpr auto invoke(Args&&... args) -> decltype(member::invoke(std::declval<Args>()...))
            {
                return member::invoke(std::forward<Args>(args)...);
            }

            /**
             * The return type of an invocation of this member with Args... (as if by invoke(...)).
             * \copydetails refl::descriptor::return_type
             */
            template <typename... Args>
            using return_type = decltype(member::invoke(std::declval<Args>()...));

            /**
             * A synonym for invoke(args...).
             * \copydetails refl::descriptor::invoke
             */
            template <typename... Args>
            constexpr auto operator()(Args&&... args) const -> decltype(invoke(std::declval<Args>()...))
            {
                return invoke(std::forward<Args>(args)...);
            }

            /**
             * Returns a pointer to a non-overloaded function.
             * \copydetails refl::descriptor::get_pointer
             */
            static constexpr auto pointer{ detail::get_function_pointer<member>(0) };

            /**
             * Whether the pointer member was correctly resolved to a concrete implementation.
             * If this field is false, resolve() would need to be called instead.
             * \copydetails refl::descriptor::is_resolved
             */
            static constexpr bool is_resolved{ !std::is_same_v<decltype(pointer), const decltype(nullptr)> };

            /**
             * Whether the pointer can be resolved as with the specified type.
             * \copydetails refl::descriptor::can_resolve
             */
            template <typename Pointer>
            static constexpr bool can_resolve()
            {
                return !std::is_same_v<decltype(resolve<Pointer>()), decltype(nullptr)>;
            }

            /**
             * Resolves the function pointer as being of type Pointer.
             * Required when taking a pointer to an overloaded function.
             *
             * \copydetails refl::descriptor::resolve
             */
            template <typename Pointer>
            static constexpr auto resolve()
            {
                return detail::resolve_function_pointer<member, Pointer>(0);
            }

        };

        /** Represents a reflected type. */
        template <typename T>
        class type_descriptor
        {
        private:

            static_assert(refl::trait::is_reflectable_v<T>, "This type does not support reflection!");

            typedef refl::detail::type_info<T> type_info;

        public:

            /**
             * The reflected type T.
             *
             * \code{.cpp}
             * struct Foo {};
             * REFL_AUTO(type(Foo))
             *
             * type_descriptor<Foo>::type -> Foo
             * \endcode
             */
            typedef T type;

            /**
             * The declared base types (via base_types<Ts...> attribute) of T.
             * \copydetails refl::descriptor::get_declared_base_types
             */
            typedef typename detail::declared_base_type_list<T>::type declared_base_types;

            /**
             * The declared and inherited base types of T.
             * \copydetails refl::descriptor::get_base_types
             */
            typedef typename detail::base_type_list<T>::type base_types;

            /**
             * A synonym for declared_member_list<T>.
             * \copydetails refl::descriptor::declared_member_list
             */
            typedef declared_member_list<T> declared_member_types;

            /**
             * A synonym for member_list<T>.
             * \copydetails refl::descriptor::member_list
             */
            typedef member_list<T> member_types;

            /**
             * An alias specifying the types of the attributes of the member. (Removes CV-qualifiers.)
             * \copydetails refl::descriptor::get_attribute_types
             */
            typedef detail::attribute_types<T> attribute_types;

            /**
             * The declared base types (via base_types<Ts...> attribute) of T.
             * \copydetails refl::descriptor::get_declared_base_types
             */
            static constexpr declared_base_types declared_bases{};

            /**
             * The declared  and inherited base types of T.
             * \copydetails refl::descriptor::get_base_types
             */
            static constexpr base_types bases{};

            /**
             * The list of declared member descriptors.
             * \copydetails refl::descriptor::get_declared_members
             */
            static constexpr declared_member_types declared_members{  };

            /**
             * The list of declared and inherited member descriptors.
             * \copydetails refl::descriptor::get_members
             */
            static constexpr member_types members{  };

            /**
             * The name of the reflected type.
             * \copydetails refl::descriptor::get_name
             */
            static constexpr const auto name{ type_info::name };

            /**
             * The attributes of the reflected type.
             * \copydetails refl::descriptor::get_attributes
              */
            static constexpr const auto attributes{ type_info::attributes };

        };

        /**
         * Returns the full name of the descriptor
         *
         * \code{.cpp}
         * namespace ns {
         *   struct Foo {
         *     int x;
         *   };
         * }
         * REFL_AUTO(type(ns::Foo), field(x))
         *
         * get_name(reflect<Foo>()) -> "ns::Foo"
         * get_name(get_t<0, member_list<Foo>>()) -> "x"
         * \endcode
         */
        template <typename Descriptor>
        constexpr auto get_name(Descriptor d) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return d.name;
        }

        /**
         * Returns a const reference to the descriptor's attribute tuple.
         *
         * \code{.cpp}
         * struct Foo {};
         * REFL_AUTO(type(Foo, bases<>, ns::serializable()))
         *
         * get_attributes(reflect<Foo>()) -> const std::tuple<attr::base_types<>, ns::serializable>&
         * \endcode
         */
        template <typename Descriptor>
        constexpr const auto& get_attributes(Descriptor d) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return d.attributes;
        }

        /**
         * Returns a type_list of the descriptor's attribute types.
         *
         * \code{.cpp}
         * struct Foo {};
         * REFL_AUTO(type(Foo, bases<>, ns::serializable()))
         *
         * get_attribute_types(reflect<Foo>()) -> type_list<attr::base_types<>, ns::serializable>
         * \endcode
         */
        template <typename Descriptor>
        constexpr auto get_attribute_types(Descriptor d) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return trait::as_type_list_t<std::remove_cv_t<decltype(d.attributes)>>{};
        }

        /**
         * Returns a type_list of the declared base types of the type.
         * Combine with reflect_types to obtain type_descriptors for those types.
         * @see reflect_types
         *
         * \code{.cpp}
         * struct Animal {};
         * REFL_AUTO(type(Animal))
         * struct Mammal : Animal {};
         * REFL_AUTO(type(Mammal, bases<Animal>))
         * struct Dog : Mammal {}:
         * REFL_AUTO(type(Dog, bases<Mammal>))
         *
         * get_base_types(reflect<Dog>()) -> type_list<Mammal>
         * \endcode
         */
        template <typename TypeDescriptor>
        constexpr auto get_declared_base_types(TypeDescriptor t) noexcept
        {
            static_assert(trait::is_type_v<TypeDescriptor>);
            return t.declared_bases;
        }

        /**
         * Returns a type_list of the declared and inherited base types of the type.
         * Combine with reflect_types to obtain type_descriptors for those types.
         * @see reflect_types
         *
         * \code{.cpp}
         * struct Animal {};
         * REFL_AUTO(type(Animal))
         * struct Mammal : Animal {};
         * REFL_AUTO(type(Mammal, bases<Animal>))
         * struct Dog : Mammal {}:
         * REFL_AUTO(type(Dog, bases<Mammal>))
         *
         * get_base_types(reflect<Dog>()) -> type_list<Mammal, Animal>
         * \endcode
         */
        template <typename TypeDescriptor>
        constexpr auto get_base_types(TypeDescriptor t) noexcept
        {
            static_assert(trait::is_type_v<TypeDescriptor>);
            return t.bases;
        }

        /**
         * Returns a type_list of the declared members of the type.
         *
         * \code{.cpp}
         * struct Base {
         *  int val;
         * };
         * struct Foo : Base {
         *   int bar, baz;
         * };
         * REFL_AUTO(type(Foo, bases<Base>), field(bar), field(baz))
         * get_declared_members(reflect<Foo>()) -> type_list<field_descriptor<Foo, 0> /bar/, field_descriptor<Foo, 1> /baz/>
         * \endcode
         */
        template <typename TypeDescriptor>
        constexpr auto get_declared_members(TypeDescriptor t) noexcept
        {
            static_assert(trait::is_type_v<TypeDescriptor>);
            return t.declared_members;
        }

        /**
         * Returns a type_list of the declared and inherited members of the type.
         *
         * \code{.cpp}
         * struct Base {
         *  int val;
         * };
         * struct Foo : Base {
         *   int bar, baz;
         * };
         * REFL_AUTO(type(Foo, bases<Base>), field(bar), field(baz))
         * get_members(reflect<Foo>()) -> type_list<field_descriptor<Foo, 0> /bar/, field_descriptor<Foo, 1> /baz/, field_descriptor<Base, 0> /val/>
         * \endcode
         */
        template <typename TypeDescriptor>
        constexpr auto get_members(TypeDescriptor t) noexcept
        {
            static_assert(trait::is_type_v<TypeDescriptor>);
            return t.members;
        }

        /**
         * Returns the type_descriptor of declaring type of the member.
         *
         * \code{.cpp}
         * struct Foo {
         *   int bar;
         * };
         * REFL_AUTO(type(Foo), field(bar)
         * get_declarator(get_t<0, member_list<Foo>>()) -> type_descriptor<Foo>{}
         * \endcode
         */
        template <typename MemberDescriptor>
        constexpr auto get_declarator(MemberDescriptor d) noexcept
        {
            static_assert(trait::is_member_v<MemberDescriptor>);
            return d.declarator;
        }

        /**
         * Returns a pointer to the reflected field/function.
         * When the member is a function, the return value might be nullptr
         * if the type of the function pointer cannot be resolved.
         * @see is_resolved
         * @see can_resolve
         * @see resolve
         *
         * \code{.cpp}
         * struct Foo {
         *   int bar;
         *   static int baz;
         * };
         * REFL_AUTO(type(Foo), field(bar), field(baz))
         * get_pointer(get_t<0, member_list<Foo>>()) -> (int Foo::*) &Foo::bar
         * get_pointer(get_t<1, member_list<Foo>>()) -> (int*) &Foo::baz
         * \endcode
         */
        template <typename MemberDescriptor>
        constexpr auto get_pointer(MemberDescriptor d) noexcept
        {
            static_assert(trait::is_member_v<MemberDescriptor>);
            return d.pointer;
        }

        /**
         * Invokes the member with the specified arguments.
         *
         * \code{.cpp}
         * struct Foo {
         *   int bar = 1;
         *   static int baz = 5;
         *   void foobar(int x) { return x * 2; }
         *   static void foobaz(int x) { return x * 3; }
         * };
         * REFL_AUTO(type(Foo), field(bar), field(baz), func(foobar), func(foobaz))
         * invoke(get_t<0, member_list<Foo>(), Foo()) -> 1 (Foo().bar)
         * invoke(get_t<1, member_list<Foo>>()) -> 5 (Foo::baz)
         * invoke(get_t<2, member_list<Foo>(), Foo(), 10) -> 20 (Foo().foobar())
         * invoke(get_t<3, member_list<Foo>>()) -> 30 (Foo::foobaz())
         * \endcode
         */
        template <typename MemberDescriptor, typename... Args>
        constexpr auto invoke(MemberDescriptor d, Args&&... args) noexcept -> decltype(d(std::forward<Args>(args)...))
        {
            return d(std::forward<Args>(args)...);
        }

        /**
         * Checks whether the field is declared as static.
         *
         * \code{.cpp}
         * struct Foo {
         *   int bar;
         *   static int baz;
         * };
         * REFL_AUTO(type(Foo), field(bar), field(baz))
         * is_static(get_t<0, member_list<Foo>>()) -> false
         * is_static(get_t<1, member_list<Foo>>()) -> true
         * \endcode
         */
        template <typename FieldDescriptor>
        constexpr auto is_static(FieldDescriptor d) noexcept
        {
            static_assert(trait::is_field_v<FieldDescriptor>);
            return d.is_static;
        }

        /**
         * Checks whether the value type of the field is const-qualified.
         *
         * \code{.cpp}
         * struct Foo {
         *   int bar;
         *   const int baz;
         * };
         * REFL_AUTO(type(Foo), field(bar), field(baz))
         * is_const(get_t<0, member_list<Foo>>()) -> false
         * is_const(get_t<1, member_list<Foo>>()) -> true
         * \endcode
         */
        template <typename FieldDescriptor>
        constexpr auto is_const(FieldDescriptor d) noexcept
        {
            static_assert(trait::is_field_v<FieldDescriptor>);
            return d.is_const;
        }

        /**
         * The return type when invoking the specified descriptor using the provided argument types.
         * Argument coversion will be applied as per C++ rules.
         */
        template <typename FunctionDescriptor, typename... Args>
        using result_type = typename FunctionDescriptor::template result_type<Args...>;

        /**
         * Checks whether the function pointer was automatically resolved.
         *
         * \code{.cpp}
         * struct Foo {
         *   void bar();
         *   void bar(int);
         *   void baz();
         * };
         * REFL_AUTO(type(Foo), func(bar), func(baz))
         * is_resolved(get_t<0, member_list<Foo>>()) -> false
         * is_resolved(get_t<1, member_list<Foo>>()) -> true
         * \endcode
         */
        template <typename FunctionDescriptor>
        constexpr auto is_resolved(FunctionDescriptor d) noexcept
        {
            static_assert(trait::is_function_v<FunctionDescriptor>);
            return d.is_resolved;
        }

        /**
         * Checks whether the function pointer can be resolved as
         * a pointer of the specified type.
         *
         * \code{.cpp}
         * struct Foo {
         *   void bar();
         *   void bar(int);
         * };
         * REFL_AUTO(type(Foo), func(bar))
         * can_resolve<void(Foo::*)()>(get_t<0, member_list<Foo>>()) -> true
         * can_resolve<void(Foo::*)(int)>(get_t<0, member_list<Foo>>()) -> true
         * can_resolve<void(Foo::*)(std::string)>(get_t<0, member_list<Foo>>()) -> false
         * \endcode
         */
        template <typename Pointer, typename FunctionDescriptor>
        constexpr auto can_resolve(FunctionDescriptor d) noexcept
        {
            static_assert(trait::is_function_v<FunctionDescriptor>);
            return d.template can_resolve<Pointer>();
        }

        /**
         * Resolves the function pointer as a pointer of the specified type.
         *
         * \code{.cpp}
         * struct Foo {
         *   void bar();
         *   void bar(int);
         * };
         * REFL_AUTO(type(Foo), func(bar))
         * resolve<void(Foo::*)()>(get_t<0, member_list<Foo>>()) -> <&Foo::bar()>
         * resolve<void(Foo::*)(int)>(get_t<0, member_list<Foo>>()) -> <&Foo::bar(int)>
         * resolve<void(Foo::*)(std::string)>(get_t<0, member_list<Foo>>()) -> nullptr
         * \endcode
         */
        template <typename Pointer, typename FunctionDescriptor>
        constexpr auto resolve(FunctionDescriptor d) noexcept
        {
            static_assert(trait::is_function_v<FunctionDescriptor>);
            return d.template resolve<Pointer>();
        }

        /**
         * Checks whether T is a field descriptor.
         *
         * @see refl::descriptor::field_descriptor
         *
         * \code{.cpp}
         * REFL_AUTO(type(Foo), func(bar), field(baz))
         * is_function(get_t<0, member_list<Foo>>()) -> false
         * is_function(get_t<1, member_list<Foo>>()) -> true
         * \endcode
         */
        template <typename Descriptor>
        constexpr bool is_field(Descriptor) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return trait::is_field_v<Descriptor>;
        }

        /**
         * Checks whether T is a function descriptor.
         *
         * @see refl::descriptor::function_descriptor
         *
         * \code{.cpp}
         * REFL_AUTO(type(Foo), func(bar), field(baz))
         * is_function(get_t<0, member_list<Foo>>()) -> true
         * is_function(get_t<1, member_list<Foo>>()) -> false
         * \endcode
         */
        template <typename Descriptor>
        constexpr bool is_function(Descriptor) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return trait::is_function_v<Descriptor>;
        }

        /**
         * Checks whether T is a type descriptor.
         *
         * @see refl::descriptor::type_descriptor
         *
         * \code{.cpp}
         * REFL_AUTO(type(Foo))
         * is_type(reflect<Foo>>()) -> true
         * \endcode
         */
        template <typename Descriptor>
        constexpr bool is_type(Descriptor) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return trait::is_type_v<Descriptor>;
        }

        /**
         * Checks whether T has an attribute of type A.
         *
         * \code{.cpp}
         * REFL_AUTO(type(User), func(get_name, property()), func(set_name, property()))
         * has_attribute<attr::property>(get_t<0, member_list<User>>{}) -> true
         * \endcode
         */
        template <typename A, typename Descriptor>
        constexpr bool has_attribute(Descriptor) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return trait::contains_base_v<A, typename Descriptor::attribute_types>;
        }

        /**
         * Checks whether T has an attribute of that is a template instance of A.
         *
         * \code{.cpp}
         * REFL_AUTO(type(Random, debug{ [](auto os, auto){ os << "[Random]"; } }))
         * has_attribute<attr::debug>(reflect<Random>()) -> true
         * \endcode
         */
        template <template<typename...> typename A, typename Descriptor>
        constexpr bool has_attribute(Descriptor) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return trait::contains_instance_v<A, typename Descriptor::attribute_types>;
        }

        /**
         * Returns the value of the attribute A on T.
         *
         * \code{.cpp}
         * REFL_AUTO(type(User), func(get_name, property()), func(set_name, property()))
         * get_attribute<attr::property>(get_t<0, member_list<User>>{}) -> property{ friendly_name = nullopt }
         * \endcode
         */
        template <typename A, typename Descriptor>
        constexpr const A& get_attribute(Descriptor d) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return util::get<A>(d.attributes);
        }

        /**
         * Returns the value of the attribute A on T.
         *
         * \code{.cpp}
         * REFL_AUTO(type(Random, debug{ [](auto os, auto){ os << "[Random]"; } }))
         * get_attribute<attr::debug>(reflect<Random>()) -> instance of debug<LambdaType>
         * \endcode
         */
        template <template<typename...> typename A, typename Descriptor>
        constexpr const auto& get_attribute(Descriptor d) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return util::get_instance<A>(d.attributes);
        }

        /**
         * Checks whether T is a member descriptor marked with the property attribute.
         *
         * @see refl::attr::property
         * @see refl::descriptor::get_property
         *
         * \code{.cpp}
         * REFL_AUTO(type(User), func(get_name, property("user_name")), func(set_name, property()))
         * is_property(get_t<0, member_list<User>>{}) -> true
         * \endcode
         */
        template <typename MemberDescriptor>
        constexpr bool is_property(MemberDescriptor d) noexcept
        {
            static_assert(trait::is_member_v<MemberDescriptor>);
            return has_attribute<attr::property>(d);
        }

        /**
         * Gets the property attribute.
         *
         * @see refl::attr::property
         * @see refl::descriptor::is_property
         *
         * \code{.cpp}
         * REFL_AUTO(type(User), func(get_name, property("user_name")), func(set_name, property()))
         * *get_property(get_t<0, member_list<User>>{}).friendly_name -> "user_name"
         * \endcode
         */
        template <typename FunctionDescriptor>
        constexpr attr::property get_property(FunctionDescriptor d) noexcept
        {
            static_assert(trait::is_function_v<FunctionDescriptor>);
            return get_attribute<attr::property>(d);
        }

        namespace detail
        {
            struct placeholder
            {
                template <typename T>
                operator T() const;
            };
        } // namespace detail

        /**
         * Checks if T is a 0-arg const-qualified member function with a property attribute or a field.
         *
         * \code{.cpp}
         * REFL_AUTO(type(User), func(get_name, property()), func(set_name, property()))
         * is_readable(get_t<0, member_list<User>>{}) -> true
         * is_readable(get_t<1, member_list<User>>{}) -> false
         * \endcode
         */
        template <typename MemberDescriptor>
        constexpr bool is_readable(MemberDescriptor) noexcept
        {
            static_assert(trait::is_member_v<MemberDescriptor>);
            if constexpr (trait::is_property_v<MemberDescriptor>) {
                if constexpr (std::is_invocable_v<MemberDescriptor, const typename MemberDescriptor::declaring_type&>) {
                    using return_type = typename MemberDescriptor::template return_type<const typename MemberDescriptor::declaring_type&>;
                    return !std::is_void_v<return_type>;
                }
                else {
                    return false;
                }
            }
            else {
                return trait::is_field_v<MemberDescriptor>;
            }
        }

        /**
         * Checks if T is a 1-arg non-const-qualified member function with a property attribute or a non-const field.
         *
         * \code{.cpp}
         * struct User { std::string get_name() const; }
         * REFL_AUTO(type(User), func(get_name, property()), func(set_name, property()))
         * is_writable(get_t<0, member_list<User>>{}) -> false
         * is_writable(get_t<1, member_list<User>>{}) -> true
         * \endcode
         */
        template <typename MemberDescriptor>
        constexpr bool is_writable(MemberDescriptor) noexcept
        {
            static_assert(trait::is_member_v<MemberDescriptor>);
            if constexpr (trait::is_property_v<MemberDescriptor>) {
                return std::is_invocable_v<MemberDescriptor, typename MemberDescriptor::declaring_type&, detail::placeholder>;
            }
            else if constexpr (trait::is_field_v<MemberDescriptor>) {
                return !std::is_const_v<typename trait::remove_qualifiers_t<MemberDescriptor>::value_type>;
            }
            else {
                return false;
            }
        }

        namespace detail
        {
            template <typename T>
            struct get_type_descriptor
            {
                typedef type_descriptor<T> type;
            };
        } // namespace detail

        /**
         * Checks if a type has a bases attribute.
         *
         * @deprecated Use has_base_types in combination with reflect_types instead.
         * @see refl::attr::bases
         * @see refl::descriptor::get_bases
         *
         * \code{.cpp}
         * REFL_AUTO(type(Dog, bases<Animal>))
         * has_bases(reflect<Dog>()) -> true
         * \endcode
         */
        template <typename TypeDescriptor>
        [[deprecated]] constexpr auto has_bases(TypeDescriptor t) noexcept
        {
            static_assert(trait::is_type_v<TypeDescriptor>);
            return has_attribute<attr::base_types>(t);
        }

        /**
         * Returns a list of the type_descriptor<T>s of the base types of the target,
         * as specified by the bases<A, B, ...> attribute.
         *
         * @deprecated Use get_base_types in combination with reflect_types instead.
         * @see refl::attr::bases
         * @see refl::descriptor::has_bases
         *
         * \code{.cpp}
         * REFL_AUTO(type(Dog, bases<Animal>))
         * get_bases(reflect<Dog>()) -> type_list<type_descriptor<Animal>>
         * \endcode
         */
        template <typename TypeDescriptor>
        [[deprecated]] constexpr auto get_bases(TypeDescriptor t) noexcept
        {
            static_assert(trait::is_type_v<TypeDescriptor>);
            static_assert(has_bases(t), "Target type does not have a bases<A, B, ...> attribute.");

            constexpr auto bases = get_attribute<attr::base_types>(t);
            using base_types = typename decltype(bases)::list_type;
            return trait::map_t<detail::get_type_descriptor, base_types>{};
        }

        /**
         * Returns the unqualified name of the type, discarding the namespace and typenames (if a template type).
         *
         * \code{.cpp}
         * get_simple_name(reflect<std::vector<float>>()) -> "vector"
         * \endcode
         */
        template <typename TypeDescriptor>
        constexpr auto get_simple_name(TypeDescriptor t)
        {
            static_assert(trait::is_type_v<TypeDescriptor>);
            constexpr size_t template_start = t.name.find('<');
            constexpr size_t scope_last = t.name.rfind(':', template_start);
            if constexpr (scope_last == const_string<0>::npos) {
                return t.name;
            }
            else {
                return t.name.template substr<scope_last + 1, template_start - scope_last - 1>();
            }
        }

        /**
         * Returns the debug name of T (In the form of 'declaring_type::member_name') as a const_string.
         *
         * \code{.cpp}
         * REFL_AUTO(type(Point), field(x), field(y))
         * get_debug_name_const(get_t<0, member_list<Point>>{}) -> "Point::x"
         * \endcode
         */
        template <typename MemberDescriptor>
        constexpr auto get_debug_name_const(MemberDescriptor d)
        {
            static_assert(trait::is_member_v<MemberDescriptor>);
            return d.declarator.name + "::" + d.name;
        }

        /**
         * Returns the debug name of T. (In the form of 'declaring_type::member_name').
         * \code{.cpp}
         * REFL_AUTO(type(Point), field(x), field(y))
         * get_debug_name(get_t<0, member_list<Point>>{}) -> "Point::x"
         * \endcode
         */
        template <typename MemberDescriptor>
        const char* get_debug_name(MemberDescriptor d)
        {
            static_assert(trait::is_member_v<MemberDescriptor>);
            static const std::string name(get_debug_name_const(d).str());
            return name.c_str();
        }

        namespace detail
        {
            constexpr bool is_upper(char ch)
            {
                return ch >= 'A' && ch <= 'Z';
            }

            constexpr char to_upper(char ch)
            {
                return ch >= 'a' && ch <= 'z'
                    ? char(ch + ('A' - 'a'))
                    : ch;
            }

            constexpr char to_lower(char ch)
            {
                return ch >= 'A' && ch <= 'Z'
                    ? char(ch + ('a' - 'A'))
                    : ch;
            }

            template <typename T, bool PreferUpper>
            constexpr auto normalize_bare_accessor_name()
            {
                constexpr auto str = T::name.template substr<3>();
                if constexpr (str.data[0] == '_') {
                    return str.template substr<1>();
                }
                else if constexpr (!PreferUpper && str.data[0] >= 'A' && str.data[0] <= 'Z') {
                    return make_const_string(to_lower(str.data[0])) + str.template substr<1>();
                }
                else if constexpr (PreferUpper) {
                    return make_const_string(to_upper(str.data[0])) + str.template substr<1>();
                }
                else {
                    return str;
                }
            }

            template <typename T>
            constexpr auto normalize_accessor_name(const T)
            {
                constexpr T t{};
                if constexpr (t.name.size > 3) {
                    constexpr auto prefix = t.name.template substr<0, 3>();
                    constexpr bool cont_snake_or_camel = (t.name.size > 4 && t.name.data[3] == '_' && !is_upper(t.name.data[4])) || is_upper(t.name.data[3]);
                    constexpr bool cont_pascal = is_upper(t.name.data[3]);

                    if constexpr ((is_readable(T{}) && ((prefix == "Get" && cont_pascal) || (prefix == "get" && cont_snake_or_camel)))
                        || (is_writable(T{}) && ((prefix == "Set" && cont_pascal) || (prefix == "set" && cont_snake_or_camel)))) {
                        constexpr bool prefer_upper = is_upper(prefix.data[0]);
                        return normalize_bare_accessor_name<T, prefer_upper>();
                    }
                    else {
                        return t.name;
                    }
                }
                else {
                    return t.name;
                }
            }

            template <typename T>
            constexpr auto get_display_name(const T t) noexcept
            {
                if constexpr (trait::is_property_v<T>) {
                    if constexpr (util::get<attr::property>(t.attributes).friendly_name) {
                        return REFL_MAKE_CONST_STRING(*util::get<attr::property>(t.attributes).friendly_name);
                    }
                    else {
                        return detail::normalize_accessor_name(t);
                    }
                }
                else {
                    return t.name;
                }
            }

            template <template <typename, size_t> typename MemberDescriptor, typename T, size_t N>
            constexpr size_t get_member_index(MemberDescriptor<T, N>) noexcept
            {
                return N;
            }

            // Compilers only instantiate templates once per set of template parameters.
            // Since each lambda is it's distinct type, and since we end up filtering
            // by these predicates in several places in the codebase, it is better to have
            // these lamdas defined here, to increase the likelihood that a template
            // instantiation of `util::filter` can be reused.
            static constexpr auto is_readable_p = [](auto m) { return is_readable(m); };
            static constexpr auto is_writable_p = [](auto m) { return is_writable(m); };

            template <typename Member>
            static constexpr auto display_name_equals_p = [](auto m) {
                return get_display_name_const(m) == get_display_name_const(Member{});
            };

            template <typename WritableMember>
            static constexpr bool has_reader_search(WritableMember)
            {
#ifdef REFL_DISALLOW_SEARCH_FOR_RW
                static_assert(WritableMember::name.data[0] == 0,
                    "REFL_DISALLOW_SEARCH_FOR_RW is defined. Make sure your property getters and setter are defined one after the other!");
#endif
                using member_types = typename type_descriptor<typename WritableMember::declaring_type>::declared_member_types;
                // Fallback to a slow linear search.
                using property_types = typename trait::filter_t<trait::is_property, member_types>;
                constexpr auto readable_properties = filter(property_types{}, detail::is_readable_p);
                return contains(readable_properties, display_name_equals_p<WritableMember>);
            }

            template <typename ReadableMember>
            static constexpr bool has_writer_search(ReadableMember)
            {
#ifdef REFL_DISALLOW_SEARCH_FOR_RW
                static_assert(ReadableMember::name.data[0] == 0,
                    "REFL_DISALLOW_SEARCH_FOR_RW is defined. Make sure your property getters and setter are defined one after the other!");
#endif
                using member_types = typename type_descriptor<typename ReadableMember::declaring_type>::declared_member_types;
                // Fallback to a slow linear search.
                using property_types = typename trait::filter_t<trait::is_property, member_types>;
                constexpr auto writable_properties = filter(property_types{}, detail::is_writable_p);
                return contains(writable_properties, display_name_equals_p<ReadableMember>);
            }

            template <typename WritableMember>
            static constexpr auto get_reader_search(WritableMember)
            {
#ifdef REFL_DISALLOW_SEARCH_FOR_RW
                static_assert(WritableMember::name.data[0] == 0,
                    "REFL_DISALLOW_SEARCH_FOR_RW is defined. Make sure your property getters and setter are defined one after the other!");
#endif
                using member_types = typename type_descriptor<typename WritableMember::declaring_type>::declared_member_types;
                // Fallback to a slow linear search.
                using property_types = typename trait::filter_t<trait::is_property, member_types>;
                constexpr auto readable_properties = filter(property_types{}, detail::is_readable_p);
                return find_one(readable_properties, display_name_equals_p<WritableMember>);
            }

            template <typename ReadableMember>
            static constexpr auto get_writer_search(ReadableMember)
            {
#ifdef REFL_DISALLOW_SEARCH_FOR_RW
                static_assert(ReadableMember::name.data[0] == 0,
                    "REFL_DISALLOW_SEARCH_FOR_RW is defined. Make sure your property getters and setter are defined one after the other!");
#endif
                using member_types = typename type_descriptor<typename ReadableMember::declaring_type>::declared_member_types;
                // Fallback to a slow linear search.
                using property_types = typename trait::filter_t<trait::is_property, member_types>;
                constexpr auto writable_properties = filter(property_types{}, detail::is_writable_p);
                return find_one(writable_properties, display_name_equals_p<ReadableMember>);
            }
        } // namespace detail

        /**
         * Returns the display name of T.
         * Uses the friendly_name of the property attribute, or the normalized name if no friendly_name was provided.
         *
         * \code{.cpp}
         * struct Foo {
         *   int get_foo() const;
         *   int GetFoo() const;
         *   int get_non_const() /missing const/;
         *   int get_custom() const;
         * };
         * REFL_AUTO(
         *   type(Foo),
         *   func(get_foo, property()),
         *   func(GetFoo, property()),
         *   func(get_non_const, property()),
         *   func(get_custom, property("value")),
         * )
         *
         * get_display_name(get_t<0, member_list<Foo>>{}) -> "foo"
         * get_display_name(get_t<1, member_list<Foo>>{}) -> "Foo"
         * get_display_name(get_t<2, member_list<Foo>>{}) -> "get_non_const"
         * get_display_name(get_t<3, member_list<Foo>>{}) -> "value"
         * \endcode
         */
        template <typename Descriptor>
        const char* get_display_name(Descriptor d) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            static const std::string name(detail::get_display_name(d));
            return name.c_str();
        }

        /**
         * Returns the display name of T as a const_string<N>.
         * Uses the friendly_name of the property attribute, or the normalized name if no friendly_name was provided.
         * @see get_display_name
         */
        template <typename Descriptor>
        constexpr auto get_display_name_const(Descriptor d) noexcept
        {
            static_assert(trait::is_descriptor_v<Descriptor>);
            return detail::get_display_name(d);
        }

        /**
         * Checks if there exists a member that has the same display name as the one provied and is writable.
         * For getter methods with a property attribute, the return value will be true if there exists a
         * reflected setter method with a property with the same display name (property name normalization applies automatically).
         * For fields, returns true only if the field is writable.
         */
        template <typename ReadableMember>
        constexpr bool has_writer(ReadableMember member)
        {
            static_assert(is_writable(member) || is_property(member));
            if constexpr (is_writable(member)) {
                return true;
            }
            else {
                [[maybe_unused]] constexpr auto match = [](auto m) {
                    return is_property(m) && is_writable(m) && get_display_name_const(m) == get_display_name_const(ReadableMember{});
                };

                using member_types = typename type_descriptor<typename ReadableMember::declaring_type>::declared_member_types;
                constexpr auto member_index = detail::get_member_index(member);

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != 0) {
                    using likely_match = trait::get_t<member_index - 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return true;
                    }
                }

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != member_types::size - 1) {
                    using likely_match = trait::get_t<member_index + 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return true;
                    }
                    else {
                        return detail::has_writer_search(member);
                    }
                }
                else {
                    return detail::has_writer_search(member);
                }
            }
        }

        /**
         * Checks if there exists a member that has the same display name as the one provied and is readable.
         * For setter methods with a property attribute, the return value will be true if there exists a
         * reflected getter method with a property with the same display name (property name normalization applies automatically).
         * For fields, returns true.
         */
        template <typename WritableMember>
        constexpr bool has_reader(WritableMember member)
        {
            static_assert(is_readable(member) || is_property(member));
            if constexpr (is_readable(member)) {
                return true;
            }
            else {
                [[maybe_unused]] constexpr auto match = [](auto m) {
                    return is_property(m) && is_readable(m) && get_display_name_const(m) == get_display_name_const(WritableMember{});
                };

                using member_types = typename type_descriptor<typename WritableMember::declaring_type>::declared_member_types;
                constexpr auto member_index = detail::get_member_index(member);

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != member_types::size - 1) {
                    using likely_match = trait::get_t<member_index + 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return true;
                    }
                }

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != 0) {
                    using likely_match = trait::get_t<member_index - 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return true;
                    }
                    else {
                        return detail::has_reader_search(member);
                    }
                }
                else {
                    return detail::has_reader_search(member);
                }
            }
        }

        /**
         * Returns a member that has the same display name as the one provied and is writable.
         * For getter methods with a property attribute, the return value will the
         * reflected setter method with a property with the same display name (property name normalization applies automatically).
         * For fields, returns the same descriptor if writable.
         */
        template <typename ReadableMember>
        constexpr auto get_writer(ReadableMember member)
        {
            static_assert(is_writable(member) || is_property(member));
            if constexpr (is_writable(member)) {
                return member;
            }
            else if constexpr (has_writer(member)) {
                constexpr auto match = [](auto m) {
                    return is_property(m) && is_writable(m) && get_display_name_const(m) == get_display_name_const(ReadableMember{});
                };

                using member_types = typename type_descriptor<typename ReadableMember::declaring_type>::declared_member_types;
                constexpr auto member_index = detail::get_member_index(member);

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != 0) {
                    using likely_match = trait::get_t<member_index - 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return likely_match{};
                    }
                }

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != member_types::size - 1) {
                    using likely_match = trait::get_t<member_index + 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return likely_match{};
                    }
                    else {
                        return detail::get_writer_search(member);
                    }
                }
                else {
                    return detail::get_writer_search(member);
                }
            }
            else {
                static_assert(has_writer(member), "The property is not writable (could not find a setter method)!");
            }
        }

        /**
         * Returns a member that has the same display name as the one provied and is readable.
         * For setter methods with a property attribute, the return value will be a
         * reflected getter method with a property with the same display name (property name normalization applies automatically).
         * For fields, returns the same descriptor.
         */
        template <typename WritableMember>
        constexpr auto get_reader(WritableMember member)
        {
            static_assert(is_readable(member) || is_property(member));
            if constexpr (is_readable(member)) {
                return member;
            }
            else if constexpr (has_reader(member)) {
                constexpr auto match = [](auto m) {
                    return is_property(m) && is_readable(m) && get_display_name_const(m) == get_display_name_const(WritableMember{});
                };

                using member_types = typename type_descriptor<typename WritableMember::declaring_type>::declared_member_types;
                constexpr auto member_index = detail::get_member_index(member);

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != member_types::size - 1) {
                    using likely_match = trait::get_t<member_index + 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return likely_match{};
                    }
                }

                // Optimisation for the getter defined after setter pattern.
                if constexpr (member_index != 0) {
                    using likely_match = trait::get_t<member_index - 1, member_types>;
                    if constexpr (match(likely_match{})) {
                        return likely_match{};
                    }
                    else {
                        return detail::get_reader_search(member);
                    }
                }
                else {
                    return detail::get_reader_search(member);
                }
            }
            else {
                static_assert(has_reader(member), "The property is not readable (could not find a getter method)!");
            }
        }

    } // namespace descriptor

    using descriptor::member_list;
    using descriptor::declared_member_list;
    using descriptor::field_descriptor;
    using descriptor::function_descriptor;
    using descriptor::type_descriptor;

    /** Returns true if the type T is reflectable. */
    template <typename T>
    constexpr bool is_reflectable() noexcept
    {
        return trait::is_reflectable_v<T>;
    }

    /** Returns true if the non-qualified type T is reflectable.*/
    template <typename T>
    constexpr bool is_reflectable(const T&) noexcept
    {
        return trait::is_reflectable_v<T>;
    }

    /** Returns the type descriptor for the type T. */
    template<typename T>
    constexpr type_descriptor<T> reflect() noexcept
    {
        return {};
    }

    /** Returns the type descriptor for the non-qualified type T. */
    template<typename T>
    constexpr type_descriptor<T> reflect(const T&) noexcept
    {
        return {};
    }

#ifndef REFL_DETAIL_FORCE_EBO
#ifdef _MSC_VER
#define REFL_DETAIL_FORCE_EBO __declspec(empty_bases)
#else
#define REFL_DETAIL_FORCE_EBO
#endif
#endif

    /**
     * @brief Contains utilities that can have runtime-overhead (like proxy, debug, invoke)
     */
    namespace runtime
    {
        template <typename Derived, typename Target>
        struct REFL_DETAIL_FORCE_EBO proxy;

        namespace detail
        {
            template <typename T>
            struct get_member_info;

            template <typename T, size_t N>
            struct get_member_info<refl::function_descriptor<T, N>>
            {
                using type = refl::detail::member_info<T, N>;
            };

            template <typename T, size_t N>
            struct get_member_info<refl::field_descriptor<T, N>>
            {
                using type = refl::detail::member_info<T, N>;
            };

            template <typename T, typename U>
            constexpr T& static_ref_cast(U& value) noexcept
            {
                return static_cast<T&>(value);
            }

            template <typename T, typename U>
            constexpr const T& static_ref_cast(const U& value) noexcept
            {
                return static_cast<const T&>(value);
            }

            template <typename... Results>
            constexpr type_list<Results...> get_members_skip_shadowed(type_list<>, type_list<Results...>)
            {
                return {};
            }

            template <typename Member, typename... Members, typename... Results>
            constexpr auto get_members_skip_shadowed(type_list<Member, Members...>, type_list<Results...>)
            {
                if constexpr ((... || (Results::name == Member::name))) {
                    return get_members_skip_shadowed(type_list<Members...>{}, type_list<Results...>{});
                }
                else {
                    return get_members_skip_shadowed(type_list<Members...>{}, type_list<Results..., Member>{});
                }
            }

            template <typename T>
            using members_skip_shadowed = decltype(get_members_skip_shadowed(member_list<T>{}, type_list<>{}));

            /** Implements a proxy for a reflected function. */
            template <typename Derived, typename Func>
            struct REFL_DETAIL_FORCE_EBO function_proxy : public get_member_info<Func>::type::template remap<function_proxy<Derived, Func>>
            {
                function_proxy()
                {
                }

                template <typename Self, typename... Args>
                static constexpr decltype(auto) invoke_impl(Self&& self, Args&& ... args)
                {
                    return Derived::template invoke_impl<Func>(static_ref_cast<Derived>(self), std::forward<Args>(args)...);
                }
            };

            template <typename, typename>
            struct REFL_DETAIL_FORCE_EBO function_proxies;

            /** Implements a proxy for all reflected functions. */
            template <typename Derived, typename... Members>
            struct REFL_DETAIL_FORCE_EBO function_proxies<Derived, type_list<Members...>> : public function_proxy<Derived, Members>...
            {
            };

            /** Implements a proxy for a reflected field. */
            template <typename Derived, typename Field>
            struct REFL_DETAIL_FORCE_EBO field_proxy : public get_member_info<Field>::type::template remap<field_proxy<Derived, Field>>
            {
                field_proxy()
                {
                }

                template <typename Self, typename... Args>
                static constexpr decltype(auto) invoke_impl(Self&& self, Args&& ... args)
                {
                    return Derived::template invoke_impl<Field>(static_ref_cast<Derived>(self), std::forward<Args>(args)...);
                }
            };


            template <typename, typename>
            struct REFL_DETAIL_FORCE_EBO field_proxies;

            /** Implements a proxy for all reflected fields. */
            template <typename Derived, typename... Members>
            struct REFL_DETAIL_FORCE_EBO field_proxies<Derived, type_list<Members...>> : public field_proxy<Derived, Members>...
            {
            };

            template <typename T>
            using functions = trait::filter_t<trait::is_function, members_skip_shadowed<T>>;

            template <typename T>
            using fields = trait::filter_t<trait::is_field, members_skip_shadowed<T>>;

        } // namespace detail

        /**
         * @brief A proxy object that has a static interface identical to the reflected functions and fields of the target.
         *
         * A proxy object that has a static interface identical to the reflected functions and fields of the target.
         * Users should inherit from this class and specify an invoke_impl(Member member, Args&&... args) function.
         *
         * # Examples:
         * \code{.cpp}
         * template <typename T>
         * struct dummy_proxy : refl::runtime::proxy<dummy_proxy<T>, T> {
         *     template <typename Member, typename Self, typename... Args>
         *     static int invoke_impl(Self&& self, Args&&... args) {
         *          std::cout << get_debug_name(Member()) << " called with " << sizeof...(Args) << " parameters!\n";
         *          return 0;
         *     }
         * };
         * \endcode
         */
        template <typename Derived, typename Target>
        struct REFL_DETAIL_FORCE_EBO proxy
            : public detail::function_proxies<proxy<Derived, Target>, detail::functions<Target>>
            , public detail::field_proxies<proxy<Derived, Target>, detail::fields<Target>>
        {
            static_assert(
                sizeof(detail::function_proxies<proxy<Derived, Target>, detail::functions<Target>>) == 1 &&
                sizeof(detail::field_proxies<proxy<Derived, Target>, detail::fields<Target>>) == 1,
                "Multiple inheritance EBO did not kick in! "
                "You could try defining the REFL_DETAIL_FORCE_EBO macro appropriately to enable it on the required types. "
                "Default for MSC is `__declspec(empty_bases)`.");

            static_assert(
                trait::is_reflectable_v<Target>,
                "Target type must be reflectable!");

            typedef Target target_type;

            constexpr proxy() noexcept {}

        private:

            template <typename P, typename F>
            friend struct detail::function_proxy;

            template <typename P, typename F>
            friend struct detail::field_proxy;

            // Called by one of the function_proxy/field_proxy bases.
            template <typename Member, typename Self, typename... Args>
            static constexpr decltype(auto) invoke_impl(Self&& self, Args&& ... args)
            {
                return Derived::template invoke_impl<Member>(detail::static_ref_cast<Derived>(self), std::forward<Args>(args)...);
            }

        };

    } // namespace runtime

    namespace trait
    {
        template <typename>
        struct is_proxy;

        template <typename T>
        struct is_proxy
        {
        private:
            template <typename Derived, typename Target>
            static std::true_type test(runtime::proxy<Derived, Target>*);
            static std::false_type test(...);
        public:
            static constexpr bool value{ !std::is_reference_v<T> && decltype(test(std::declval<remove_qualifiers_t<T>*>()))::value };
        };

        template <typename T>
        [[maybe_unused]] static constexpr bool is_proxy_v{ is_proxy<T>::value };
    }

    namespace runtime
    {
        template <typename CharT, typename T>
        void debug(std::basic_ostream<CharT>& os, const T& value, bool compact = false);

        namespace detail
        {
            template <typename CharT, typename T, typename = decltype(std::declval<std::basic_ostream<CharT>&>() << std::declval<T>())>
            std::true_type is_ostream_printable_test(int);

            template <typename CharT, typename T>
            std::false_type is_ostream_printable_test(...);

            template <typename CharT, typename T>
            constexpr bool is_ostream_printable_v{ decltype(is_ostream_printable_test<CharT, T>(0))::value };

            namespace
            {
                [[maybe_unused]] int next_depth(int depth)
                {
                    return depth == -1 || depth > 8
                        ? -1
                        : depth + 1;
                }
            }

            template <typename CharT>
            void indent(std::basic_ostream<CharT>& os, int depth)
            {
                for (int i = 0; i < depth; i++) {
                    os << "    ";
                }
            }

            template <typename CharT, typename T>
            void debug_impl(std::basic_ostream<CharT>& os, const T& value, [[maybe_unused]] int depth);

            template <typename CharT, typename T>
            void debug_detailed(std::basic_ostream<CharT>& os, const T& value, int depth)
            {
                using type_descriptor = type_descriptor<T>;
                bool compact = depth == -1;
                // print type with members enclosed in braces
                os << type_descriptor::name << " { ";
                if (!compact) os << '\n';

                constexpr auto readable_members = filter(type_descriptor::members, [](auto member) { return is_readable(member); });
                for_each(readable_members, [&](auto member, [[maybe_unused]] auto index) {
                    int new_depth = next_depth(depth);

                    indent(os, new_depth);
                    os << get_display_name(member) << " = ";

                    if constexpr (util::contains_instance<attr::debug>(member.attributes)) {
                        // use the debug attribute to print
                        auto debug_attr = util::get_instance<attr::debug>(member.attributes);
                        debug_attr.write(os, value);
                    }
                    else {
                        debug_impl(os, member(value), new_depth);
                    }

                    if (!compact || index + 1 != readable_members.size) {
                        os << ", ";
                    }
                    if (!compact) {
                        indent(os, depth);
                        os << '\n';
                    }
                });

                if (compact) os << ' ';
                indent(os, depth);
                os << '}';
            }

            template <typename CharT, typename T>
            void debug_reflectable(std::basic_ostream<CharT>& os, const T& value, [[maybe_unused]] int depth)
            {
                using type_descriptor = type_descriptor<T>;
                if constexpr (trait::contains_instance_v<attr::debug, typename type_descriptor::attribute_types>) {
                    // use the debug attribute to print
                    auto debug_attr = util::get_instance<attr::debug>(type_descriptor::attributes);
                    debug_attr.write(os, value);
                }
                else if constexpr (detail::is_ostream_printable_v<CharT, T>) {
                    // type supports printing natively, just use that
                    os << value;
                }
                else {
                    debug_detailed(os, value, depth);
                }
            }

            template <typename CharT, typename T>
            void debug_container(std::basic_ostream<CharT>& os, const T& value, int depth)
            {
                bool compact = depth == -1;
                os << "[";

                auto end = value.end();
                for (auto it = value.begin(); it != end; ++it)
                {
                    if (!compact) os << '\n';
                    int new_depth = next_depth(depth);
                    indent(os, new_depth);

                    debug_impl(os, *it, new_depth);
                    if (std::next(it, 1) != end) {
                        os << ", ";
                    }
                    else if (!compact) {
                        os << '\n';
                    }
                }

                indent(os, depth);
                os << "]";
            }

            template <typename CharT, typename T>
            void debug_impl(std::basic_ostream<CharT>& os, const T& value, [[maybe_unused]] int depth)
            {
                using no_pointer_t = std::remove_pointer_t<T>;

                if constexpr (std::is_same_v<bool, T>) {
                    os << (value ? "true" : "false");
                }
                else if constexpr (std::is_pointer_v<T> && !std::is_void_v<no_pointer_t> && trait::is_reflectable_v<no_pointer_t>) {
                    if (value == nullptr) {
                        os << "nullptr";
                    }
                    else {
                        os << '&';
                        debug_impl(os, *value, -1);
                    }
                }
                else if constexpr (trait::is_reflectable_v<T>) {
                    debug_reflectable(os, value, depth);
                }
                else if constexpr (detail::is_ostream_printable_v<CharT, T>) {
                    os << value;
                }
                else if constexpr (trait::is_container_v<T>) {
                    debug_container(os, value, depth);
                }
                else {
                    os << "(not printable)";
                }
            }
        }

        /**
         * Writes the debug representation of value to the given std::ostream.
         * Calls the function specified by the debug<F> attribute whenever possible,
         * before falling back to recursively interating the members and printing them.
         * Takes an optional arguments specifying whether to print a compact representation.
         * The compact representation contains no newlines.
         */
        template <typename CharT, typename T>
        void debug(std::basic_ostream<CharT>& os, const T& value, [[maybe_unused]] bool compact)
        {
            static_assert(trait::is_reflectable_v<T> || trait::is_container_v<T> || detail::is_ostream_printable_v<CharT, T>,
                "Type is not reflectable, not a container of reflectable types and does not support operator<<(std::ostream&, T)!");

            detail::debug_impl(os, value, compact ? -1 : 0);
        }

        /**
         * Writes the compact debug representation of the provided values to the given std::ostream.
         */
        template <typename CharT, typename... Ts>
        void debug_all(std::basic_ostream<CharT>& os, const Ts&... values)
        {
            refl::runtime::debug(os, std::forward_as_tuple(static_cast<const Ts&>(values)...), true);
        }

        /**
         * Writes the debug representation of the provided value to an std::string and returns it.
         * Takes an optional arguments specifying whether to print a compact representation.
         * The compact representation contains no newlines.
         */
        template <typename CharT = char, typename T>
        std::basic_string<CharT> debug_str(const T& value, bool compact = false)
        {
            std::basic_stringstream<CharT> ss;
            debug(ss, value, compact);
            return ss.str();
        }

        /**
         * Writes the compact debug representation of the provided values to an std::string and returns it.
         */
        template <typename CharT = char, typename... Ts>
        std::basic_string<CharT> debug_all_str(const Ts&... values)
        {
            return refl::runtime::debug_str(std::forward_as_tuple(static_cast<const Ts&>(values)...), true);
        }

        /**
         * Invokes the specified member with the provided arguments.
         * When used with a member that is a field, the function gets or sets the value of the field.
         * The list of members is initially filtered by the type of the arguments provided.
         * THe filtered list is then searched at runtime by member name for the specified member
         * and that member is then invoked by operator(). If no match is found,
         * an std::runtime_error is thrown.
         */
        template <typename U, typename T, typename... Args>
        U invoke(T&& target, const char* name, Args&&... args)
        {
            using type = std::remove_reference_t<T>;
            static_assert(refl::trait::is_reflectable_v<type>, "Unsupported type!");
            typedef type_descriptor<type> type_descriptor;

            std::conditional_t<std::is_void_v<U>, bool, std::optional<U>> result{};

            for_each(type_descriptor::members, [&](auto member) {
                using member_t = decltype(member);
                if (result) return;

                if constexpr (std::is_invocable_r_v<U, decltype(member), T, Args...>) {
                    if constexpr (trait::is_member_v<member_t>) {
                        if (std::strcmp(member.name.c_str(), name) == 0) {
                            if constexpr (std::is_void_v<U>) {
                                member(target, std::forward<Args>(args)...);
                                result = true;
                            }
                            else {
                                result.emplace(member(target, std::forward<Args>(args)...));
                            }
                        }
                    }
                }
            });

            if (!result) {
                throw std::runtime_error(std::string("The member ")
                    + type_descriptor::name.str() + "::" + name
                    + " is not compatible with the provided parameters or return type, is not reflected or does not exist!");
            }
            if constexpr (!std::is_void_v<U>) {
                return std::move(*result);
            }
        }

    } // namespace runtime

} // namespace refl

namespace refl::detail
{
    constexpr bool validate_attr_unique(type_list<>) noexcept
    {
        return true;
    }

    /** Statically asserts that all types in Ts... are unique. */
    template <typename T, typename... Ts>
    constexpr bool validate_attr_unique(type_list<T, Ts...>) noexcept
    {
        constexpr bool cond = (... && (!std::is_same_v<T, Ts> && validate_attr_unique(type_list<Ts>{})));
        static_assert(cond, "Some of the attributes provided have duplicate types!");
        return cond;
    }

    template <typename Req, typename Attr>
    constexpr bool validate_attr_usage() noexcept
    {
        return std::is_base_of_v<Req, Attr>;
    }

    /**
     * Statically asserts that all arguments inherit
     * from the appropriate bases to be used with Req.
     * Req must be one of the types defined in attr::usage.
     */
    template <typename Req, typename... Args>
    constexpr auto make_attributes(Args&&... args) noexcept
    {
        constexpr bool check_unique = validate_attr_unique(type_list<Args...>{});
        static_assert(check_unique, "Some of the supplied attributes cannot be used on this declaration!");

        constexpr bool check_usage = (... && validate_attr_usage<Req, trait::remove_qualifiers_t<Args>>());
        static_assert(check_usage, "Some of the supplied attributes cannot be used on this declaration!");

        return std::make_tuple(std::forward<Args>(args)...);
    }

    template <typename T, typename...>
    struct head
    {
        typedef T type;
    };

    /**
     * Accesses the first type T of Ts...
     * Used to allow for SFIANE to kick in in the implementation of REFL_FUNC.
     */
    template <typename T, typename... Ts>
    using head_t = typename head<T, Ts...>::type;

    template <typename T, typename U>
    struct transfer_const
    {
        using type = std::conditional_t<std::is_const_v<T>, std::add_const_t<U>, U>;
    };

    template <typename T, typename U>
    struct transfer_volatile
    {
        using type = std::conditional_t<std::is_volatile_v<T>, std::add_volatile_t<U>, U>;
    };

    template <typename T, typename U>
    struct transfer_cv : transfer_const<T, typename transfer_volatile<T, U>::type>
    {
    };

    template <typename T, typename U>
    struct transfer_lvalue_ref
    {
        using type = std::conditional_t<std::is_lvalue_reference_v<T>, std::add_lvalue_reference_t<U>, U>;
    };

    template <typename T, typename U>
    struct transfer_rvalue_ref
    {
        using type = std::conditional_t<std::is_rvalue_reference_v<T>, std::add_rvalue_reference_t<U>, U>;
    };

    template <typename T, typename U>
    struct transfer_ref : transfer_rvalue_ref<T, typename transfer_lvalue_ref<T, U>::type>
    {
    };

    template <typename T, typename U>
    struct transfer_cvref : transfer_ref<T, typename transfer_cv<std::remove_reference_t<T>, U>::type>
    {
    };

    template <typename T, typename U>
    constexpr auto forward_cast(std::remove_reference_t<T>& t) -> decltype(static_cast<typename transfer_cvref<T, U>::type&&>(t))
    {
        return static_cast<typename transfer_cvref<T, U>::type&&>(t);
    }

    template <typename T, typename U>
    constexpr auto forward_cast(std::remove_reference_t<T>&& t) -> decltype(static_cast<typename transfer_cvref<T, U>::type&&>(t))
    {
        static_assert(!std::is_lvalue_reference_v<T>, "template argument substituting T is an lvalue reference type");
        return static_cast<typename transfer_cvref<T, U>::type&&>(t);
    }

    template <typename T>
    constexpr auto get_type_name()
    {
        if constexpr (trait::is_reflectable_v<T>) {
            return type_descriptor<T>::name;
        }
        else {
            return make_const_string("(unknown)");
        }
    }

} // namespace refl::detail

/********************************/
/*  Metadata-generation macros  */
/********************************/

#define REFL_DETAIL_STR_IMPL(...) #__VA_ARGS__
/** Used to stringify input separated by commas (e.g. template specializations with multiple types). */
#define REFL_DETAIL_STR(...) REFL_DETAIL_STR_IMPL(__VA_ARGS__)
/** Used to group input containing commas (e.g. template specializations with multiple types). */
#define REFL_DETAIL_GROUP(...) __VA_ARGS__

/**
 * Expands to the appropriate attributes static member variable.
 * DeclType must be the name of one of the constraints defined in attr::usage.
 * __VA_ARGS__ is the list of attributes.
 */
#define REFL_DETAIL_ATTRIBUTES(DeclType, ...) \
        static constexpr auto attributes{ ::refl::detail::make_attributes<::refl::attr::usage:: DeclType>(__VA_ARGS__) }; \

/**
 * Expands to the body of a type_info__ specialization.
 */
#define REFL_DETAIL_TYPE_BODY(TypeName, ...) \
        typedef REFL_DETAIL_GROUP TypeName type; \
        REFL_DETAIL_ATTRIBUTES(type, __VA_ARGS__) \
        static constexpr auto name{ ::refl::util::make_const_string(REFL_DETAIL_STR(REFL_DETAIL_GROUP TypeName)) }; \
        static constexpr size_t member_index_offset = __COUNTER__ + 1; \
        template <size_t, typename = void> \
        struct member {};

/**
 * Creates reflection information for a specified type. Takes an optional attribute list.
 * This macro must only be expanded in the global namespace.
 *
 * # Examples:
 * ```
 * REFL_TYPE(Point)
 * ...
 * REFL_END
 * ```
 */
#define REFL_TYPE(TypeName, ...) \
    namespace refl_impl::metadata { template<> struct type_info__<TypeName> { \
        REFL_DETAIL_TYPE_BODY((TypeName), __VA_ARGS__)

/**
 * Creates reflection information for a specified type template. Takes an optional attribute list.
 * TemplateDeclaration must be a panenthesis-enclosed list declaring the template parameters. (e.g. (typename A, typename B)).
 * TypeName must be the fully-specialized type name and should also be enclosed in panenthesis. (e.g. (MyType<A, B>))
 * This macro must only be expanded in the global namespace.
 *
 * # Examples:
 * ```
 * REFL_TEMPLATE((typename T), (std::vector<T>))
 * ...
 * REFL_END
 * ```
 */
#define REFL_TEMPLATE(TemplateDeclaration, TypeName, ...) \
    namespace refl_impl::metadata { template <REFL_DETAIL_GROUP TemplateDeclaration> struct type_info__<REFL_DETAIL_GROUP TypeName> { \
        REFL_DETAIL_TYPE_BODY(TypeName, __VA_ARGS__)

/**
 * Terminated the declaration of reflection metadata for a particular type.
 *
 * # Examples:
 * ```
 * REFL_TYPE(Point)
 * ...
 * REFL_END
 */
#define REFL_END \
        static constexpr size_t member_count{ __COUNTER__ - member_index_offset }; \
    }; }

#define REFL_DETAIL_MEMBER_HEADER template<typename Unused__> struct member<__COUNTER__ - member_index_offset, Unused__>

#define REFL_DETAIL_MEMBER_COMMON(MemberType_, MemberName_, ...) \
        typedef ::refl::member::MemberType_ member_type; \
        static constexpr auto name{ ::refl::util::make_const_string(REFL_DETAIL_STR(MemberName_)) }; \
        REFL_DETAIL_ATTRIBUTES(MemberType_, __VA_ARGS__)

/** Creates the support infrastructure needed for the refl::runtime::proxy type. */
/*
    There can be a total of 12 differently qualified member functions with the same name.
    Providing remaps for non-const and const-only strikes a balance between compilation time and usability.
    And even though there are many other remap implementation possibilities (like virtual, field variants),
    adding them was considered to not be efficient from a compilation-time point of view.
*/
#define REFL_DETAIL_MEMBER_PROXY(MemberName_) \
        template <typename Proxy> struct remap { \
            template <typename... Args> decltype(auto) MemberName_(Args&&... args) { \
                return Proxy::invoke_impl(static_cast<Proxy&>(*this), ::std::forward<Args>(args)...); \
            } \
            template <typename... Args> decltype(auto) MemberName_(Args&&... args) const { \
                return Proxy::invoke_impl(static_cast<const Proxy&>(*this), ::std::forward<Args>(args)...); \
            } \
        }

/**
 * Creates reflection information for a public field. Takes an optional attribute list.
 */
#define REFL_FIELD(FieldName_, ...) \
    REFL_DETAIL_MEMBER_HEADER { \
        REFL_DETAIL_MEMBER_COMMON(field, FieldName_, __VA_ARGS__) \
    public: \
        typedef decltype(type::FieldName_) value_type; \
        static constexpr auto pointer{ &type::FieldName_ }; \
        REFL_DETAIL_MEMBER_PROXY(FieldName_); \
    };

/**
 * Creates reflection information for a public functions. Takes an optional attribute list.
 */
#define REFL_FUNC(FunctionName_, ...) \
    REFL_DETAIL_MEMBER_HEADER { \
        REFL_DETAIL_MEMBER_COMMON(function, FunctionName_, __VA_ARGS__) \
        public: \
        template<typename Self, typename... Args> static constexpr auto invoke(Self&& self, Args&&... args) -> decltype(::refl::detail::forward_cast<Self, type>(self).FunctionName_(::std::forward<Args>(args)...)) {\
            return ::refl::detail::forward_cast<Self, type>(self).FunctionName_(::std::forward<Args>(args)...); \
        } \
        template<typename... Args> static constexpr auto invoke(Args&&... args) -> decltype(::refl::detail::head_t<type, Args...>::FunctionName_(::std::declval<Args>()...)) { \
            return ::refl::detail::head_t<type, Args...>::FunctionName_(::std::forward<Args>(args)...); \
        } \
        template <typename Dummy = void> \
        static constexpr auto pointer() -> decltype(&::refl::detail::head_t<type, Dummy>::FunctionName_) { return &::refl::detail::head_t<type, Dummy>::FunctionName_; } \
        template <typename Pointer> \
        static constexpr auto resolve() -> ::std::decay_t<decltype(Pointer(&type::FunctionName_))> { return Pointer(&type::FunctionName_); } \
        REFL_DETAIL_MEMBER_PROXY(FunctionName_); \
    };

/********************************/
/*  Default Reflection Metadata */
/********************************/

#define REFL_DETAIL_PRIMITIVE(TypeName) \
    REFL_TYPE(TypeName) \
    REFL_END

    // Char types.
    REFL_DETAIL_PRIMITIVE(char)
    REFL_DETAIL_PRIMITIVE(wchar_t)
    REFL_DETAIL_PRIMITIVE(char16_t)
    REFL_DETAIL_PRIMITIVE(char32_t)
#ifdef __cpp_lib_char8_t
    REFL_DETAIL_PRIMITIVE(char8_t)
#endif

    // Integral types.
    REFL_DETAIL_PRIMITIVE(bool)
    REFL_DETAIL_PRIMITIVE(signed char)
    REFL_DETAIL_PRIMITIVE(unsigned char)
    REFL_DETAIL_PRIMITIVE(signed short)
    REFL_DETAIL_PRIMITIVE(unsigned short)
    REFL_DETAIL_PRIMITIVE(signed int)
    REFL_DETAIL_PRIMITIVE(unsigned int)
    REFL_DETAIL_PRIMITIVE(signed long)
    REFL_DETAIL_PRIMITIVE(unsigned long)
    REFL_DETAIL_PRIMITIVE(signed long long)
    REFL_DETAIL_PRIMITIVE(unsigned long long)

    // Floating point types.
    REFL_DETAIL_PRIMITIVE(float)
    REFL_DETAIL_PRIMITIVE(double)
    REFL_DETAIL_PRIMITIVE(long double)

    // Other types.
    REFL_DETAIL_PRIMITIVE(decltype(nullptr))

    // Void type.
    REFL_TYPE(void)
    REFL_END

#undef REFL_DETAIL_PRIMITIVE

#define REFL_DETAIL_POINTER(Ptr) \
        template<typename T> \
        struct type_info__<T Ptr> { \
            typedef T Ptr type; \
            template <size_t N> \
            struct member {}; \
            static constexpr auto name{ ::refl::detail::get_type_name<T>() + ::refl::util::make_const_string(#Ptr) }; \
            static constexpr ::std::tuple<> attributes{ }; \
            static constexpr size_t member_count{ 0 }; \
        }

    namespace refl_impl
    {
        namespace metadata
        {
            REFL_DETAIL_POINTER(*);
            REFL_DETAIL_POINTER(&);
            REFL_DETAIL_POINTER(&&);
        }
    }

#undef REFL_DETAIL_POINTER

namespace refl::detail
{
    template <typename CharT>
    std::basic_string<CharT> convert(const std::string& str)
    {
        return std::basic_string<CharT>(str.begin(), str.end());
    }

#ifdef __cpp_lib_string_view
    struct write_basic_string_view
    {
        template <typename CharT, typename Traits>
        void operator()(std::basic_ostream<CharT>& os, std::basic_string_view<CharT, Traits> str) const
        {
            // some vers of clang dont have std::quoted(string_view) overload
            if (!str.back()) { // no copy needed when null-terminated
                os << std::quoted(str.data());
            }
            else {
                os << std::quoted(std::basic_string<CharT, Traits>(str.begin(), str.end()));
            }
        }
    };
#endif

    struct write_basic_string
    {
        template <typename CharT, typename Traits, typename Allocator>
        void operator()(std::basic_ostream<CharT>& os, const std::basic_string<CharT, Traits, Allocator>& str) const
        {
            os << std::quoted(str);
        }
    };

    struct write_exception
    {
        template <typename CharT>
        void operator()(std::basic_ostream<CharT>& os, const std::exception& e) const
        {
            os << convert<CharT>("Exception");
    #ifdef REFL_RTTI_ENABLED
            os << convert<CharT>(" (") << convert<CharT>(typeid(e).name()) << convert<CharT>(")");
    #endif
            os << convert<CharT>(": `") << e.what() << convert<CharT>("`");
        }
    };

    struct write_tuple
    {
        template <typename CharT, typename Tuple, size_t... Idx>
        void write(std::basic_ostream<CharT>& os, Tuple&& t, std::index_sequence<Idx...>) const
        {
            os << CharT('(');
            for_each(type_list<std::integral_constant<size_t, Idx>...>{}, [&](auto idx_c) {
                using idx_t = decltype(idx_c);
                runtime::debug(os, std::get<idx_t::value>(t));
                if constexpr (sizeof...(Idx) - 1 != idx_t::value) {
                    os << convert<CharT>(", ");
                }
            });
            os << CharT(')');
        }

        template <typename CharT, typename... Ts>
        void operator()(std::basic_ostream<CharT>& os, const std::tuple<Ts...>& t) const
        {
            write(os, t, std::make_index_sequence<sizeof...(Ts)>{});
        }
    };

    struct write_pair
    {
        template <typename CharT, typename K, typename V>
        void operator()(std::basic_ostream<CharT>& os, const std::pair<K, V>& t) const
        {
            os << CharT('(');
            runtime::debug(os, t.first);
            os << convert<CharT>(", ");
            runtime::debug(os, t.second);
            os << CharT(')');
        }
    };

    struct write_unique_ptr
    {
        template <typename CharT, typename T, typename D>
        void operator()(std::basic_ostream<CharT>& os, const std::unique_ptr<T, D>& t) const
        {
            runtime::debug(os, t.get(), true);
        }
    };

    struct write_shared_ptr
    {
        template <typename CharT, typename T>
        void operator()(std::basic_ostream<CharT>& os, const std::shared_ptr<T>& t) const
        {
            runtime::debug(os, t.get(), true);
        }
    };

    struct write_weak_ptr
    {
        template <typename CharT, typename T>
        void operator()(std::basic_ostream<CharT>& os, const std::weak_ptr<T>& t) const
        {
            runtime::debug(os, t.lock().get(), true);
        }
    };

    struct write_complex
    {
        template <typename CharT, typename T>
        void operator()(std::basic_ostream<CharT>& os, const std::complex<T>& t) const
        {
            runtime::debug(os, t.real());
            os << CharT('+');
            runtime::debug(os, t.imag());
            os << CharT('i');
        }
    };
} // namespace refl::detail

// Custom reflection information for
// some common built-in types (std::basic_string, std::tuple, std::pair).

#ifndef REFL_NO_STD_SUPPORT

REFL_TYPE(std::exception, debug{ refl::detail::write_exception() })
    REFL_FUNC(what, property{ })
REFL_END

REFL_TEMPLATE(
    (typename Elem, typename Traits, typename Alloc),
    (std::basic_string<Elem, Traits, Alloc>),
    debug{ refl::detail::write_basic_string() })
    REFL_FUNC(size, property{ })
    REFL_FUNC(data, property{ })
REFL_END

#ifdef __cpp_lib_string_view

REFL_TEMPLATE(
    (typename Elem, typename Traits),
    (std::basic_string_view<Elem, Traits>),
    debug{ refl::detail::write_basic_string_view() })
    REFL_FUNC(size, property{ })
    REFL_FUNC(data, property{ })
REFL_END

#endif

REFL_TEMPLATE(
    (typename... Ts),
    (std::tuple<Ts...>),
    debug{ refl::detail::write_tuple() })
REFL_END

REFL_TEMPLATE(
    (typename T, typename D),
    (std::unique_ptr<T, D>),
    debug{ refl::detail::write_unique_ptr() })
REFL_END

REFL_TEMPLATE(
    (typename T),
    (std::shared_ptr<T>),
    debug{ refl::detail::write_shared_ptr() })
REFL_END

REFL_TEMPLATE(
    (typename K, typename V),
    (std::pair<K, V>),
    debug{ refl::detail::write_pair() })
REFL_END

#ifndef REFL_NO_STD_COMPLEX

REFL_TEMPLATE(
    (typename T),
    (std::complex<T>),
    debug{ refl::detail::write_complex() })
REFL_END

#endif // !REFL_NO_STD_COMPLEX

#endif // !REFL_NO_STD_SUPPORT

#ifndef REFL_NO_AUTO_MACRO

#define REFL_DETAIL_EXPAND(x) x
#define REFL_DETAIL_FOR_EACH_0(...)
#define REFL_DETAIL_FOR_EACH_1(what, x, ...) what(x)
#define REFL_DETAIL_FOR_EACH_2(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_1(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_3(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_2(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_4(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_3(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_5(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_4(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_6(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_5(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_7(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_6(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_8(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_7(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_9(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_8(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_10(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_9(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_11(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_10(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_12(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_11(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_13(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_12(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_14(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_13(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_15(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_14(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_16(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_15(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_17(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_16(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_18(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_17(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_19(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_18(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_20(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_19(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_21(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_20(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_22(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_21(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_23(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_22(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_24(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_23(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_25(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_24(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_26(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_25(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_27(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_26(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_28(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_27(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_29(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_28(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_30(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_29(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_31(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_30(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_32(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_31(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_33(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_32(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_34(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_33(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_35(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_34(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_36(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_35(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_37(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_36(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_38(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_37(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_39(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_38(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_40(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_39(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_41(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_40(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_42(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_41(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_43(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_42(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_44(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_43(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_45(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_44(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_46(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_45(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_47(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_46(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_48(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_47(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_49(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_48(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_50(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_49(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_51(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_50(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_52(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_51(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_53(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_52(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_54(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_53(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_55(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_54(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_56(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_55(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_57(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_56(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_58(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_57(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_59(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_58(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_60(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_59(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_61(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_60(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_62(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_61(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_63(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_62(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_64(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_63(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_65(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_64(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_66(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_65(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_67(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_66(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_68(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_67(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_69(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_68(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_70(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_69(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_71(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_70(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_72(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_71(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_73(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_72(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_74(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_73(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_75(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_74(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_76(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_75(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_77(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_76(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_78(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_77(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_79(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_78(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_80(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_79(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_81(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_80(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_82(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_81(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_83(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_82(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_84(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_83(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_85(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_84(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_86(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_85(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_87(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_86(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_88(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_87(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_89(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_88(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_90(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_89(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_91(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_90(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_92(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_91(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_93(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_92(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_94(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_93(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_95(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_94(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_96(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_95(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_97(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_96(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_98(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_97(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_99(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_98(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_100(what, x, ...) what(x) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_99(what, __VA_ARGS__))

#define REFL_DETAIL_FOR_EACH_NARG(...) REFL_DETAIL_FOR_EACH_NARG_(__VA_ARGS__, REFL_DETAIL_FOR_EACH_RSEQ_N())
#define REFL_DETAIL_FOR_EACH_NARG_(...) REFL_DETAIL_EXPAND(REFL_DETAIL_FOR_EACH_ARG_N(__VA_ARGS__))
#define REFL_DETAIL_FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, N, ...) N
#define REFL_DETAIL_FOR_EACH_RSEQ_N() 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define REFL_DETAIL_CONCATENATE(x, y) x##y
#define REFL_DETAIL_FOR_EACH_(N, what, ...) REFL_DETAIL_EXPAND(REFL_DETAIL_CONCATENATE(REFL_DETAIL_FOR_EACH_, N)(what, __VA_ARGS__))
#define REFL_DETAIL_FOR_EACH(what, ...) REFL_DETAIL_FOR_EACH_(REFL_DETAIL_FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

// Intellisense does not work nicely with passing variadic parameters (for the attributes)
// through all of the macro expansions and causes differently named member declarations to be
// used during code inspection.
#ifdef __INTELLISENSE__

#define REFL_DETAIL_EX_1_type(X, ...) REFL_TYPE(X)
#define REFL_DETAIL_EX_1_template(X, Y, ...) REFL_TEMPLATE(X, Y)
#define REFL_DETAIL_EX_1_field(X, ...) REFL_FIELD(X)
#define REFL_DETAIL_EX_1_func(X, ...) REFL_FUNC(X)

#else // !defined(__INTELLISENSE__)

#define REFL_DETAIL_EX_1_type(...) REFL_DETAIL_EX_EXPAND(REFL_DETAIL_EX_DEFER(REFL_TYPE)(__VA_ARGS__))
#define REFL_DETAIL_EX_1_template(...) REFL_DETAIL_EX_EXPAND(REFL_DETAIL_EX_DEFER(REFL_TEMPLATE)(__VA_ARGS__))
#define REFL_DETAIL_EX_1_field(...) REFL_DETAIL_EX_EXPAND(REFL_DETAIL_EX_DEFER(REFL_FIELD)(__VA_ARGS__))
#define REFL_DETAIL_EX_1_func(...) REFL_DETAIL_EX_EXPAND(REFL_DETAIL_EX_DEFER(REFL_FUNC)(__VA_ARGS__))

#endif // __INTELLISENSE__

#define REFL_DETAIL_EX_(Specifier, ...) REFL_DETAIL_EX_1_##Specifier __VA_ARGS__

#define REFL_DETAIL_EX_EMPTY()
#define REFL_DETAIL_EX_DEFER(Id) Id REFL_DETAIL_EX_EMPTY()
#define REFL_DETAIL_EX_EXPAND(...)  __VA_ARGS__

#define REFL_DETAIL_EX_END() REFL_END

#define REFL_AUTO(...) REFL_DETAIL_FOR_EACH(REFL_DETAIL_EX_, __VA_ARGS__) REFL_DETAIL_EX_EXPAND(REFL_DETAIL_EX_DEFER(REFL_DETAIL_EX_END)())

#endif // !defined(REFL_NO_AUTO_MACRO)

#endif // REFL_INCLUDE_HPP


#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

// Support for std::format is really spotty.
// Gcc12 does not support it.
// Eventually replace with std::format when that is widely available.
#include <fmt/format.h>

namespace pmtv {

using pmt = pmt_var_t;
using map_t = std::map<std::string, pmt, std::less<>>;

template <class T>
inline constexpr std::in_place_type_t<std::vector<T>> vec_t{};

template <typename T>
concept IsPmt = std::is_same_v<T, pmt>;

// template <class T, class V>
// auto get_vector(V value) -> decltype(std::get<std::vector<T>>(value) {
//     return std::get<std::vector<T>>(value);
// }
template <class T, class V>
std::vector<T>& get_vector(V value)
{
    return std::get<std::vector<T>>(value);
}

template <class T, class V>
std::span<T> get_span(V& value)
{
    return std::span(std::get<std::vector<T>>(value));
}

template <class V>
map_t& get_map(V& value)
{
    return std::get<map_t>(value);
}

template <IsPmt P>
size_t elements(const P& value)
{
    return std::visit(
        [](const auto& arg) -> size_t {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::same_as<std::monostate, T>)
                return 0;
            else if constexpr (std::ranges::range<T>)
                return arg.size();
            return 1;
        },
        value.get_base());
}

template <IsPmt P>
size_t bytes_per_element(const P& value)
{
    return std::visit(
        [](const auto& arg) -> size_t {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::same_as<std::monostate, T>)
                return 0;
            else if constexpr (std::ranges::range<T>)
                return sizeof(typename T::value_type);
            return sizeof(T);
        },
        value.get_base());
}


/*
 Functions for converting between structures and pmts.  Each member of the structure must be
 convertible to a pmt.  No data interpretation is done.  (For example a pointer and a length
 won't work because we don't know that they are related fields.  A span or a vector would.)
 An extra requirement is that we must use a macro to declare structures and fields that we
 want to use this way.

For example,
 struct my_data {
    float x;
    int y;
    std::complex<float> z;
 };

 REFL_AUTO(type(my_data), field(x), field(y), field(z))

 Note that any members not declared in the `REFL_AUTO` call will not be transferred with the
 data.

*/

template <typename T>
constexpr auto readable_members = filter(refl::member_list<T>{}, [](auto member) { return is_readable(member); });


/*********************Map Conversion Functions*****************************************/

// Functions for converting between pmt stuctures and maps.
template <class T>
constexpr void map_from_struct(const T& value, map_t& result) {
    // iterate over the members of T
    for_each(refl::reflect(value).members, [&](auto member)
    {
        if constexpr (is_readable(member))
        {
            result[get_display_name(member)] = member(value);
        }
    });
}

template <class T>
auto map_from_struct(const T& value) {
    // iterate over the members of T
    map_t result;
    map_from_struct(value, result);
    return result;
}

template <class T>
void to_struct(const map_t& value, T& result) {
    // iterate over the members of T
    for_each(refl::reflect(result).members, [&](auto member)
    {
        if constexpr (is_readable(member))
        {
            using member_type = std::decay_t<decltype(member(result))>;
            member(result) = std::get<member_type>(value.at(get_display_name(member)));
        }
    });
}

template <class T>
T to_struct(const map_t& value) {
    T result;
    to_struct(value, result);
    return result;
}

template <class T>
bool validate_map(const map_t& value, bool exact=false) {
    // Ensure that the map contains the members of the struct with the correct types.
    // iterate over the members of T
    T temp;
    if (exact && value.size() != readable_members<T>.size) return false;
    bool result = true;
    for_each(refl::reflect(temp).members, [&](auto member)
    {
        if constexpr (is_readable(member))
        {
            using member_type = std::decay_t<decltype(member(temp))>;
            // Does the map contain the key and hold the correct type?
            if (! value.count(get_display_name(member)) ||
                ! std::holds_alternative<member_type>(value.at(get_display_name(member))))
                result = false;
        }
    });
    return result;
}


template <class T>
constexpr uint8_t pmtTypeIndex()
{
    if constexpr (std::same_as<T, std::monostate>)
        return 0;
    else if constexpr (std::same_as<T, bool>)
        return 1;
    else if constexpr (std::signed_integral<T>)
        return 2;
    else if constexpr (std::unsigned_integral<T>)
        return 3;
    else if constexpr (std::floating_point<T>)
        return 4;
    else if constexpr (Complex<T>)
        return 5;
    else if constexpr (std::same_as<T, std::string>)
        return 6;
    else if constexpr (std::same_as<T, std::map<std::string, pmt, std::less<>>>)
        return 7;
    else if constexpr (std::same_as<T, std::vector<std::string>>)
        return 8;
    else if constexpr (std::ranges::range<T>) {
        if constexpr (UniformVector<T>) {
            return pmtTypeIndex<typename T::value_type>() << 4;
        }
        else {
            return 9; // for vector of PMTs
        }
    }
}

template <class T>
constexpr uint16_t serialId()
{
    if constexpr (Complex<T>) {
        return (pmtTypeIndex<T>() << 8) | sizeof(typename T::value_type);
    }
    else if constexpr (Scalar<T> || std::same_as<T, bool>) {
        static_assert(sizeof(T) < 32, "Can't serial data wider than 16 bytes");
        if constexpr (support_size_t && std::is_same_v<T, std::size_t>){
            return (pmtTypeIndex<uint64_t>() << 8) | sizeof(uint64_t);
        } else {
            return (pmtTypeIndex < T > () << 8) | sizeof(T);
        }
    }
    else if constexpr (UniformVector<T>) {
        static_assert(sizeof(typename T::value_type) < 32,
                      "Can't serial data wider than 16 bytes");
        return (pmtTypeIndex<T>() << 8) | sizeof(typename T::value_type);
    }
    else
        return pmtTypeIndex<T>() << 8;
}

// Forward decalaration so we can recursively serialize.
template <IsPmt P>
std::streamsize serialize(std::streambuf& sb, const P& value);

template <class T>
struct serialInfo {
    using value_type = std::conditional_t<support_size_t && std::is_same_v<T, std::size_t>, uint64_t, T>;
    static constexpr uint16_t value = serialId<T>();
};

inline std::streamsize _serialize_version(std::streambuf& sb) {
    return sb.sputn(reinterpret_cast<const char*>(&pmt_version), 2);
}

template <class T>
std::streamsize _serialize_id(std::streambuf& sb) {
    using Td = std::decay_t<T>;
    auto id = serialInfo<Td>::value;
    return sb.sputn(reinterpret_cast<const char*>(&id), 2);
}

template <PmtVector T>
std::streamsize _serialize(std::streambuf& sb, const T& arg) {
    auto length = _serialize_id<T>(sb);
    uint64_t sz = arg.size();
    length += sb.sputn(reinterpret_cast<const char*>(&sz), sizeof(uint64_t));
    for (auto& value: arg) {
        length += serialize(sb, value);
    }
    return length;
}

template <UniformBoolVector T>
std::streamsize _serialize(std::streambuf& sb, const T& arg) {
    auto length = _serialize_id<T>(sb);
    uint64_t sz = arg.size();
    length += sb.sputn(reinterpret_cast<const char*>(&sz), sizeof(uint64_t));
    char one = 1;
    char zero = 0;
    for (auto value : arg) {
        length += sb.sputn(value ? &one : &zero, sizeof(char));
    }
    return length;
}

template <UniformStringVector T>
std::streamsize _serialize(std::streambuf& sb, const T& arg) {
    auto length = _serialize_id<T>(sb);
    uint64_t sz = arg.size();
    length += sb.sputn(reinterpret_cast<const char*>(&sz), sizeof(uint64_t));
    for (auto& value: arg) {
        // Send length then value
        sz = value.size();
        length += sb.sputn(reinterpret_cast<const char*>(&sz), sizeof(uint64_t));
        length += sb.sputn(value.data(), static_cast<std::streamsize>(value.size()));
    }
    return length;
}

template <UniformVector T>
std::streamsize _serialize(std::streambuf& sb, const T& arg) {
    auto length = _serialize_id<T>(sb);
    uint64_t sz = arg.size();
    length += sb.sputn(reinterpret_cast<const char*>(&sz), sizeof(uint64_t));
    length += sb.sputn(reinterpret_cast<const char*>(arg.data()),static_cast<std::streamsize>(arg.size() * sizeof(arg[0])));
    return length;
}

template <PmtNull T>
std::streamsize _serialize(std::streambuf& sb, [[maybe_unused]] const T& arg) {
    return _serialize_id<T>(sb);
}

template <Scalar T>
std::streamsize _serialize(std::streambuf& sb, const T& arg) {
    if constexpr (support_size_t && std::is_same_v<T, std::size_t>) {
        uint64_t arg64 {arg};
        return _serialize_id<uint64_t>(sb) + sb.sputn(reinterpret_cast<const char*>(&arg64), sizeof(arg64));
    } else {
        return _serialize_id<T>(sb) +  sb.sputn(reinterpret_cast<const char*>(&arg), sizeof(arg));
    }
}

template <PmtMap T>
std::streamsize _serialize(std::streambuf& sb, const T& arg) {
    auto length = _serialize_id<T>(sb);
    uint32_t nkeys = uint32_t(arg.size());
    length += sb.sputn(reinterpret_cast<const char*>(&nkeys), sizeof(nkeys));
    uint32_t ksize;
    for (const auto& [k, v] : arg) {
        // For right now just prefix the size to the key and send it
        ksize = uint32_t(k.size());
        length +=
            sb.sputn(reinterpret_cast<const char*>(&ksize), sizeof(ksize));
        length += sb.sputn(k.c_str(), ksize);
        length += serialize(sb, v);
    }
    return length;
}

// FIXME - make this consistent endianness
template <IsPmt P>
std::streamsize serialize(std::streambuf& sb, const P& value)
{
    auto length = _serialize_version(sb);

    std::visit(
        [&length, &sb](auto&& arg) {
            length += _serialize(sb, arg);
        },
        value);

    return length;
}

template <class T>
T _deserialize_val(std::streambuf& sb);

static pmt deserialize(std::streambuf& sb)
{
    uint16_t version;
    // pmt_container_type container;
    sb.sgetn(reinterpret_cast<char*>(&version), sizeof(version));
    // sb.sgetn(reinterpret_cast<char*>(&container), sizeof(container));

    uint16_t receivedId;
    sb.sgetn(reinterpret_cast<char*>(&receivedId), sizeof(receivedId));

    pmt ret;

    switch (receivedId) {
    case serialInfo<bool>::value:
        return _deserialize_val<bool>(sb);
    case serialInfo<uint8_t>::value:
        return _deserialize_val<uint8_t>(sb);
    case serialInfo<uint16_t>::value:
        return _deserialize_val<uint16_t>(sb);
    case serialInfo<uint32_t>::value:
        return _deserialize_val<uint32_t>(sb);
    case serialInfo<uint64_t>::value:
        return _deserialize_val<uint64_t>(sb);
    case serialInfo<int8_t>::value:
        return _deserialize_val<int8_t>(sb);
    case serialInfo<int16_t>::value:
        return _deserialize_val<int16_t>(sb);
    case serialInfo<int32_t>::value:
        return _deserialize_val<int32_t>(sb);
    case serialInfo<int64_t>::value:
        return _deserialize_val<int64_t>(sb);
    case serialInfo<float>::value:
        return _deserialize_val<float>(sb);
    case serialInfo<double>::value:
        return _deserialize_val<double>(sb);
    case serialInfo<std::complex<float>>::value:
        return _deserialize_val<std::complex<float>>(sb);
    case serialInfo<std::complex<double>>::value:
        return _deserialize_val<std::complex<double>>(sb);

    // case serialInfo<std::vector<bool>>::value: return
    // _deserialize_val<std::vector<bool>>(sb);
    case serialInfo<std::vector<uint8_t>>::value:
        return _deserialize_val<std::vector<uint8_t>>(sb);
    case serialInfo<std::vector<uint16_t>>::value:
        return _deserialize_val<std::vector<uint16_t>>(sb);
    case serialInfo<std::vector<uint32_t>>::value:
        return _deserialize_val<std::vector<uint32_t>>(sb);
    case serialInfo<std::vector<uint64_t>>::value:
        return _deserialize_val<std::vector<uint64_t>>(sb);
    case serialInfo<std::vector<int8_t>>::value:
        return _deserialize_val<std::vector<int8_t>>(sb);
    case serialInfo<std::vector<int16_t>>::value:
        return _deserialize_val<std::vector<int16_t>>(sb);
    case serialInfo<std::vector<int32_t>>::value:
        return _deserialize_val<std::vector<int32_t>>(sb);
    case serialInfo<std::vector<int64_t>>::value:
        return _deserialize_val<std::vector<int64_t>>(sb);
    case serialInfo<std::vector<float>>::value:
        return _deserialize_val<std::vector<float>>(sb);
    case serialInfo<std::vector<double>>::value:
        return _deserialize_val<std::vector<double>>(sb);
    case serialInfo<std::vector<std::complex<float>>>::value:
        return _deserialize_val<std::vector<std::complex<float>>>(sb);
    case serialInfo<std::vector<std::complex<double>>>::value:
        return _deserialize_val<std::vector<std::complex<double>>>(sb);

    case serialInfo<std::string>::value:
        return _deserialize_val<std::string>(sb);
    case serialInfo<std::vector<std::string>>::value:
        return _deserialize_val<std::vector<std::string>>(sb);
    case serialInfo<std::vector<pmtv::pmt>>::value:
        return _deserialize_val<std::vector<pmtv::pmt>>(sb);
    case serialInfo<map_t>::value:
        return _deserialize_val<map_t>(sb);
    default:
        throw std::runtime_error("pmt::deserialize: Invalid PMT type type");
    }

    return ret;
}

template <class T>
T _deserialize_val(std::streambuf& sb)
{
    if constexpr (Scalar<T>) {
        T val;
        sb.sgetn(reinterpret_cast<char*>(&val), sizeof(val));
        return val;
    }
    else if constexpr (PmtVector<T>) {
        std::vector<pmt> val;
        uint64_t nelems;
        sb.sgetn(reinterpret_cast<char*>(&nelems), sizeof(nelems));
        for (uint64_t n = 0; n < nelems; n++) {
            val.push_back(deserialize(sb));
        }
        return val;
    }
    else if constexpr (UniformVector<T> && !String<T>) {
        uint64_t sz;
        sb.sgetn(reinterpret_cast<char*>(&sz), sizeof(uint64_t));
        std::vector<typename T::value_type> val(sz);
        sb.sgetn(reinterpret_cast<char*>(val.data()), static_cast<std::streamsize>(sz * sizeof(val[0])));
        return val;
    }
    else if constexpr (String<T>) {
        uint64_t sz;
        sb.sgetn(reinterpret_cast<char*>(&sz), sizeof(uint64_t));
        std::string val(sz, '0');
        sb.sgetn(reinterpret_cast<char*>(val.data()), static_cast<std::streamsize>(sz));
        return val;
    }
    else if constexpr (UniformStringVector<T>) {
        uint64_t sz;
        sb.sgetn(reinterpret_cast<char*>(&sz), sizeof(uint64_t));
        std::vector<typename T::value_type> val(sz);
        for (size_t i = 0; i < val.size(); i++) {
            sb.sgetn(reinterpret_cast<char*>(&sz), sizeof(uint64_t));
            val[i].resize(sz);
            sb.sgetn(val[i].data(), static_cast<std::streamsize>(sz));
        }
        return val;
    }
    else if constexpr (PmtMap<T>) {
        map_t val;

        uint32_t nkeys;
        sb.sgetn(reinterpret_cast<char*>(&nkeys), static_cast<std::streamsize>(sizeof(nkeys)));
        for (uint32_t n = 0; n < nkeys; n++) {
            uint32_t ksize;
            sb.sgetn(reinterpret_cast<char*>(&ksize), static_cast<std::streamsize>(sizeof(ksize)));
            std::vector<char> data;
            data.resize(ksize);
            sb.sgetn(data.data(), ksize);

            val[std::string(data.begin(), data.end())] = deserialize(sb);
        }
        return val;
    }
    else {
        throw std::runtime_error(
            "pmt::_deserialize_value: attempted to deserialize invalid PMT type");
    }
}


template <IsPmt P>
std::string to_base64(const P& value)
{
    std::stringbuf sb;
    auto nbytes = serialize(sb, value);
    std::string pre_encoded_str(static_cast<std::size_t>(nbytes), '0');
    sb.sgetn(pre_encoded_str.data(), nbytes);
    auto nencoded_bytes = Base64encode_len(static_cast<int>(nbytes));
    std::string encoded_str(static_cast<std::size_t>(nencoded_bytes), '0');
    auto nencoded = Base64encode(encoded_str.data(), pre_encoded_str.data(), static_cast<int>(nbytes));
    encoded_str.resize(static_cast<std::size_t>(nencoded - 1)); // because it null terminates
    return encoded_str;
}

[[maybe_unused]] static pmt from_base64(const std::string& encoded_str)
{
    std::string bufplain(encoded_str.size(), '0');
    Base64decode(bufplain.data(), encoded_str.data());
    std::stringbuf sb(bufplain);
    return deserialize(sb);
}

// Allows us to cast from a pmt like this: auto x = cast<float>(mypmt);
template <class T, IsPmt P>
T cast(const P& value)
{
    return std::visit(
        [](const auto& arg) -> T {
            using U = std::decay_t<decltype(arg)>;
            if constexpr (std::constructible_from<T, U>) {
                if constexpr(Complex<T>) {
                    if constexpr (std::integral<U> || std::floating_point<U>) {
                        return std::complex<typename T::value_type>(static_cast<typename T::value_type>(arg));
                    } else {
                         return static_cast<T>(arg);
                    }
                } else {
                    return static_cast<T>(arg);
                }
            }
            // else if constexpr (PmtMap<T> && PmtMap<U>) {
            //     return std::get<std::map<std::string, pmt_var_t, std::less<>>>(arg);
            // }
            else
                throw std::runtime_error(fmt::format(
                    "Invalid PMT Cast {} {}", typeid(T).name(), typeid(U).name()));
        },
        value);
}

} // namespace pmtv

namespace fmt {
template <>
struct formatter<pmtv::map_t::value_type> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const pmtv::map_t::value_type& kv, FormatContext& ctx) const {
        return fmt::format_to(ctx.out(), "{}: {}", kv.first, kv.second);
    }
};

template <pmtv::Complex C>
struct formatter<C> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const C& arg, FormatContext& ctx) const {
        if (arg.imag() >= 0)
            return fmt::format_to(ctx.out(), "{0}+j{1}", arg.real(), arg.imag());
        else
            return fmt::format_to(ctx.out(), "{0}-j{1}", arg.real(), -arg.imag());
    }
};


template<pmtv::IsPmt P>
struct formatter<P>
{

    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const P& value, FormatContext& ctx) const {
        // Due to an issue with the c++ spec that has since been resolved, we have to do something
        // funky here.  See
        // https://stackoverflow.com/questions/37526366/nested-constexpr-function-calls-before-definition-in-a-constant-expression-con
        // This problem only appears to occur in gcc 11 in certain optimization modes. The problem
        // occurs when we want to format a vector<pmt>.  Ideally, we can write something like:
        //      return fmt::format_to(ctx.out(), "[{}]", fmt::join(arg, ", "));
        // It looks like the issue effects clang 14/15 as well.
        // However, due to the above issue, it fails to compile.  So we have to do the equivalent
        // ourselves.  We can't recursively call the formatter, but we can recursively call a lambda
        // function that does the formatting.
        // It gets more complicated, because we need to pass the function into the lambda.  We can't
        // pass in the lamdba as it is defined, so we create a nested lambda.  Which accepts a function
        // as a argument.
        // Because we are calling std::visit, we can't pass non-variant arguments to the visitor, so we
        // have to create a new nested lambda every time we format a vector to ensure that it works.
        using namespace pmtv;
        using ret_type = decltype(fmt::format_to(ctx.out(), ""));
        auto format_func = [&ctx](const auto format_arg) {
            auto function_main = [&ctx](const auto arg, auto function) -> ret_type {
            using namespace pmtv;
            using T = std::decay_t<decltype(arg)>;
            if constexpr (Scalar<T> || Complex<T>)
                return fmt::format_to(ctx.out(), "{}", arg);
            else if constexpr (std::same_as<T, std::string>)
                return fmt::format_to(ctx.out(), "{}",  arg);
            else if constexpr (UniformVector<T> || UniformStringVector<T>)
                return fmt::format_to(ctx.out(), "[{}]", fmt::join(arg, ", "));
            else if constexpr (std::same_as<T, std::vector<pmt>>) {
                fmt::format_to(ctx.out(), "[");
                auto new_func = [&function](const auto new_arg) -> ret_type { return function(new_arg, function); };
                for (auto& a: std::span(arg).first(arg.size()-1)) {
                    std::visit(new_func, a);
                    fmt::format_to(ctx.out(), ", ");
                }
                std::visit(new_func, arg[arg.size()-1]);
                return fmt::format_to(ctx.out(), "]");
                // When we drop support for gcc11/clang15, get rid of the nested lambda and replace
                // the above with this line.
                //return fmt::format_to(ctx.out(), "[{}]", fmt::join(arg, ", "));
            } else if constexpr (PmtMap<T>) {
                fmt::format_to(ctx.out(), "{{");
                auto new_func = [&function](const auto new_arg) -> ret_type { return function(new_arg, function); };
                size_t i = 0;
                for (auto& [k, v]: arg) {
                    fmt::format_to(ctx.out(), "{}: ", k);
                    std::visit(new_func, v);
                    if (i++ < arg.size() - 1)
                        fmt::format_to(ctx.out(), ", ");
                }
                return fmt::format_to(ctx.out(), "}}");
                // When we drop support for gcc11/clang15, get rid of the nested lambda and replace
                // the above with this line.
                //return fmt::format_to(ctx.out(), "{{{}}}", fmt::join(arg, ", "));
            } else if constexpr (std::same_as<std::monostate, T>)
                return fmt::format_to(ctx.out(), "null");
            return fmt::format_to(ctx.out(), "unknown type {}", typeid(T).name());
            };
            return function_main(format_arg, function_main);
        };
        return std::visit(format_func, value);

    }
};

} // namespace fmt

namespace pmtv {
    template <IsPmt P>
    std::ostream& operator<<(std::ostream& os, const P& value) {
        os << fmt::format("{}", value);
        return os;
    }
}



#include <fmt/format.h>

// #include <gnuradio-4.0/meta/typelist.hpp>
#ifndef GNURADIO_TYPELIST_HPP
#define GNURADIO_TYPELIST_HPP

#include <bit>
#include <concepts>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace gr::meta {

template<typename... Ts>
struct typelist;

// concat ///////////////
namespace detail {
template<typename...>
struct concat_impl;

template<>
struct concat_impl<> {
    using type = typelist<>;
};

template<typename A>
struct concat_impl<A> {
    using type = typelist<A>;
};

template<typename... As>
struct concat_impl<typelist<As...>> {
    using type = typelist<As...>;
};

template<typename A, typename B>
struct concat_impl<A, B> {
    using type = typelist<A, B>;
};

template<typename... As, typename B>
struct concat_impl<typelist<As...>, B> {
    using type = typelist<As..., B>;
};

template<typename A, typename... Bs>
struct concat_impl<A, typelist<Bs...>> {
    using type = typelist<A, Bs...>;
};

template<typename... As, typename... Bs>
struct concat_impl<typelist<As...>, typelist<Bs...>> {
    using type = typelist<As..., Bs...>;
};

template<typename A, typename B, typename C>
struct concat_impl<A, B, C> {
    using type = typename concat_impl<typename concat_impl<A, B>::type, C>::type;
};

template<typename A, typename B, typename C, typename D, typename... More>
struct concat_impl<A, B, C, D, More...> {
    using type = typename concat_impl<typename concat_impl<A, B>::type, typename concat_impl<C, D>::type, typename concat_impl<More...>::type>::type;
};
} // namespace detail

template<typename... Ts>
using concat = typename detail::concat_impl<Ts...>::type;

// split_at, left_of, right_of ////////////////
namespace detail {
template<unsigned N>
struct splitter;

template<>
struct splitter<0> {
    template<typename...>
    using first = typelist<>;
    template<typename... Ts>
    using second = typelist<Ts...>;
};

template<>
struct splitter<1> {
    template<typename T0, typename...>
    using first = typelist<T0>;
    template<typename, typename... Ts>
    using second = typelist<Ts...>;
};

template<>
struct splitter<2> {
    template<typename T0, typename T1, typename...>
    using first = typelist<T0, T1>;
    template<typename, typename, typename... Ts>
    using second = typelist<Ts...>;
};

template<>
struct splitter<4> {
    template<typename T0, typename T1, typename T2, typename T3, typename...>
    using first = typelist<T0, T1, T2, T3>;
    template<typename, typename, typename, typename, typename... Ts>
    using second = typelist<Ts...>;
};

template<>
struct splitter<8> {
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename...>
    using first = typelist<T0, T1, T2, T3, T4, T5, T6, T7>;

    template<typename, typename, typename, typename, typename, typename, typename, typename, typename... Ts>
    using second = typelist<Ts...>;
};

template<>
struct splitter<16> {
    template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13,
             typename T14, typename T15, typename...>
    using first = typelist<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15>;

    template<typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename, typename... Ts>
    using second = typelist<Ts...>;
};

template<unsigned N>
struct splitter {
    static constexpr unsigned FirstSplit = std::has_single_bit(N) ? N / 2 : std::bit_floor(N);
    using A                              = splitter<FirstSplit>;
    using B                              = splitter<N - FirstSplit>;

    template<typename... Ts>
    using first = concat<typename A::template first<Ts...>, typename B::template first<typename A::template second<Ts...>>>;

    template<typename... Ts>
    using second = typename B::template second<typename A::template second<Ts...>>;
};

} // namespace detail

template<unsigned N, typename List>
struct split_at;

template<unsigned N, typename... Ts>
struct split_at<N, typelist<Ts...>> {
    using first  = typename detail::splitter<N>::template first<Ts...>;
    using second = typename detail::splitter<N>::template second<Ts...>;
};

template<std::size_t N, typename List>
using left_of = typename split_at<N, List>::first;

template<std::size_t N, typename List>
using right_of = typename split_at<N + 1, List>::second;

// remove_at /////////////
template<std::size_t Idx, typename List>
using remove_at = concat<left_of<Idx, List>, right_of<Idx, List>>;

// first_type ////////////
namespace detail {
template<typename List>
struct first_type_impl {};

template<typename T0, typename... Ts>
struct first_type_impl<typelist<T0, Ts...>> {
    using type = T0;
};
} // namespace detail

template<typename List>
using first_type = typename detail::first_type_impl<List>::type;

// transform_types ////////////
namespace detail {
template<template<typename> class Template, typename List>
struct transform_types_impl;

template<template<typename> class Template, typename... Ts>
struct transform_types_impl<Template, typelist<Ts...>> {
    using type = typelist<Template<Ts>...>;
};

template<template<typename> class Template, typename List>
struct transform_types_nested_impl;

template<template<typename> class Template, typename... Ts>
struct transform_types_nested_impl<Template, typelist<Ts...>> {
    using type = typelist<typename Template<Ts>::type...>;
};
} // namespace detail

template<template<typename> class Template, typename List>
using transform_types = typename detail::transform_types_impl<Template, List>::type;

template<template<typename> class Template, typename List>
using transform_types_nested = typename detail::transform_types_nested_impl<Template, List>::type;

// transform_value_type
template<typename T>
using transform_value_type = typename T::value_type;

namespace detail {
template<bool Cond, template<typename> class Tpl1, template<typename> class Tpl2, typename T>
struct conditional_specialization;

template<template<typename> class Tpl1, template<typename> class Tpl2, typename T>
struct conditional_specialization<true, Tpl1, Tpl2, T> {
    using type = Tpl1<T>;
};

template<template<typename> class Tpl1, template<typename> class Tpl2, typename T>
struct conditional_specialization<false, Tpl1, Tpl2, T> {
    using type = Tpl2<T>;
};

template<typename CondFun, template<typename> class Tpl1, template<typename> class Tpl2, typename List>
struct transform_conditional_impl;

template<typename CondFun, template<typename> class Tpl1, template<typename> class Tpl2, typename... Ts>
struct transform_conditional_impl<CondFun, Tpl1, Tpl2, typelist<Ts...>> {
    using type = decltype([]<std::size_t... Is>(std::index_sequence<Is...>) -> typelist<typename conditional_specialization<CondFun()(Is), Tpl1, Tpl2, Ts>::type...> {
        return {};
    }(std::make_index_sequence<sizeof...(Ts)>()));
};
} // namespace detail

// Transform all types in List:
// For all types T with index I in List:
// If CondFun()(I) is true use Tpl1<T>, otherwise use Tpl2<T>
template<class CondFun, template<typename> class Tpl1, template<typename> class Tpl2, typename List>
using transform_conditional = typename detail::transform_conditional_impl<CondFun, Tpl1, Tpl2, List>::type;

// reduce ////////////////
namespace detail {
template<template<typename, typename> class Method, typename List>
struct reduce_impl;

template<template<typename, typename> class Method, typename T0>
struct reduce_impl<Method, typelist<T0>> {
    using type = T0;
};

template<template<typename, typename> class Method, typename T0, typename T1, typename... Ts>
struct reduce_impl<Method, typelist<T0, T1, Ts...>> : public reduce_impl<Method, typelist<typename Method<T0, T1>::type, Ts...>> {};

template<template<typename, typename> class Method, typename T0, typename T1, typename T2, typename T3, typename... Ts>
struct reduce_impl<Method, typelist<T0, T1, T2, T3, Ts...>> : public reduce_impl<Method, typelist<typename Method<T0, T1>::type, typename Method<T2, T3>::type, Ts...>> {};
} // namespace detail

template<template<typename, typename> class Method, typename List>
using reduce = typename detail::reduce_impl<Method, List>::type;

namespace detail {

template<template<typename> typename Pred, typename... Items>
struct find_type;

template<template<typename> typename Pred>
struct find_type<Pred> {
    using type = typelist<>;
};

template<template<typename> typename Pred, typename First, typename... Rest>
struct find_type<Pred, First, Rest...> {
    using type = typename std::conditional_t<Pred<First>::value, typelist<First, typename find_type<Pred, Rest...>::type>, typename find_type<Pred, Rest...>::type>;
};

template<template<typename> typename Predicate, typename DefaultType, typename... Ts>
struct find_type_or_default_impl {
    using type = DefaultType;
};

template<template<typename> typename Predicate, typename DefaultType, typename Head, typename... Ts>
struct find_type_or_default_impl<Predicate, DefaultType, Head, Ts...>
    : std::conditional_t<Predicate<Head>::value, find_type_or_default_impl<Predicate, Head, Ts...>, find_type_or_default_impl<Predicate, DefaultType, Ts...>> {};

template<std::size_t Index, typename... Ts>
struct at_impl;

template<typename T0, typename... Ts>
struct at_impl<0, T0, Ts...> {
    using type = T0;
};

template<typename T0, typename T1, typename... Ts>
struct at_impl<1, T0, T1, Ts...> {
    using type = T1;
};

template<typename T0, typename T1, typename T2, typename... Ts>
struct at_impl<2, T0, T1, T2, Ts...> {
    using type = T2;
};

template<typename T0, typename T1, typename T2, typename T3, typename... Ts>
struct at_impl<3, T0, T1, T2, T3, Ts...> {
    using type = T3;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename... Ts>
struct at_impl<4, T0, T1, T2, T3, T4, Ts...> {
    using type = T4;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename... Ts>
struct at_impl<5, T0, T1, T2, T3, T4, T5, Ts...> {
    using type = T5;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename... Ts>
struct at_impl<6, T0, T1, T2, T3, T4, T5, T6, Ts...> {
    using type = T6;
};

template<typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename... Ts>
struct at_impl<7, T0, T1, T2, T3, T4, T5, T6, T7, Ts...> {
    using type = T7;
};

template<std::size_t Index, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename... Ts>
    requires(Index >= 8)
struct at_impl<Index, T0, T1, T2, T3, T4, T5, T6, T7, Ts...> : at_impl<Index - 8, Ts...> {};

} // namespace detail

// typelist /////////////////
template<typename T>
concept is_typelist_v = requires { typename T::typelist_tag; };

template<typename... Ts>
struct typelist {
    using this_t       = typelist<Ts...>;
    using typelist_tag = std::true_type;

    static inline constexpr std::integral_constant<std::size_t, sizeof...(Ts)> size = {};

    template<template<typename...> class Other>
    using apply = Other<Ts...>;

    template<class F, std::size_t... Is, typename... LeadingArguments>
    static constexpr void
    for_each_impl(F &&f, std::index_sequence<Is...>, LeadingArguments &&...args) {
        (f(std::forward<LeadingArguments>(args)..., std::integral_constant<std::size_t, Is>{}, Ts{}), ...);
    }

    template<class F, typename... LeadingArguments>
    static constexpr void
    for_each(F &&f, LeadingArguments &&...args) {
        for_each_impl(std::forward<F>(f), std::make_index_sequence<sizeof...(Ts)>{}, std::forward<LeadingArguments>(args)...);
    }

    template<std::size_t I>
    using at = detail::at_impl<I, Ts...>::type;

    template<typename... Heads>
    using prepend = typelist<Heads..., Ts...>;

    template<typename... Other>
    static constexpr inline bool are_equal = std::same_as<typelist, meta::typelist<Other...>>;

    template<typename... Other>
    static constexpr inline bool are_convertible_to = (std::convertible_to<Ts, Other> && ...);

    template<typename... Other>
    static constexpr inline bool are_convertible_from = (std::convertible_to<Other, Ts> && ...);

    template<typename F, typename Tup>
        requires(sizeof...(Ts) == std::tuple_size_v<std::remove_cvref_t<Tup>>)
    static constexpr auto
    construct(Tup &&args_tuple) {
        return std::apply([]<typename... Args>(Args &&...args) { return std::make_tuple(F::template apply<Ts>(std::forward<Args>(args))...); }, std::forward<Tup>(args_tuple));
    }

    template<template<typename> typename Trafo>
    using transform = meta::transform_types<Trafo, this_t>;

    template<template<typename...> typename Pred>
    constexpr static bool all_of = (Pred<Ts>::value && ...);

    template<template<typename...> typename Pred>
    constexpr static bool any_of = (Pred<Ts>::value || ...);

    template<template<typename...> typename Pred>
    constexpr static bool none_of = (!Pred<Ts>::value && ...);

    template<typename DefaultType>
    using safe_head_default = std::remove_pointer_t<decltype([] {
        if constexpr (sizeof...(Ts) > 0) {
            return static_cast<this_t::at<0> *>(nullptr);
        } else {
            return static_cast<DefaultType *>(nullptr);
        }
    }())>;

    using safe_head = std::remove_pointer_t<decltype([] {
        if constexpr (sizeof...(Ts) > 0) {
            return static_cast<this_t::at<0> *>(nullptr);
        } else {
            return static_cast<void *>(nullptr);
        }
    }())>;

    template<typename Matcher = typename this_t::safe_head>
    constexpr static bool all_same = ((std::is_same_v<Matcher, Ts> && ...));

    template<template<typename...> typename Predicate>
    using filter = concat<std::conditional_t<Predicate<Ts>::value, typelist<Ts>, typelist<>>...>;

    template<template<typename> typename Pred>
    using find = typename detail::find_type<Pred, Ts...>::type;

    template<template<typename> typename Pred, typename DefaultType>
    using find_or_default = typename detail::find_type_or_default_impl<Pred, DefaultType, Ts...>::type;

    template<typename Needle>
    static constexpr std::size_t
    index_of() {
        std::size_t result = static_cast<std::size_t>(-1);
        gr::meta::typelist<Ts...>::for_each([&](auto index, auto &&t) {
            if constexpr (std::is_same_v<Needle, std::remove_cvref_t<decltype(t)>>) {
                result = index;
            }
        });
        return result;
    }

    template<typename T>
    inline static constexpr bool contains = std::disjunction_v<std::is_same<T, Ts>...>;

    using tuple_type    = std::tuple<Ts...>;
    using tuple_or_type = std::remove_pointer_t<decltype([] {
        if constexpr (sizeof...(Ts) == 0) {
            return static_cast<void *>(nullptr);
        } else if constexpr (sizeof...(Ts) == 1) {
            return static_cast<at<0> *>(nullptr);
        } else {
            return static_cast<tuple_type *>(nullptr);
        }
    }())>;
};

template<typename T, typename... Ts>
constexpr bool is_any_of_v = std::disjunction_v<std::is_same<T, Ts>...>;

namespace detail {
template<template<typename...> typename OtherTypelist, typename... Args>
meta::typelist<Args...>
to_typelist_helper(OtherTypelist<Args...> *);
} // namespace detail

template<typename OtherTypelist>
using to_typelist = decltype(detail::to_typelist_helper(static_cast<OtherTypelist *>(nullptr)));

} // namespace gr::meta

#endif // GNURADIO_TYPELIST_HPP

// #include <gnuradio-4.0/meta/utils.hpp>
#ifndef GNURADIO_GRAPH_UTILS_HPP
#define GNURADIO_GRAPH_UTILS_HPP

#include <complex>
#include <cstdint>
#include <cxxabi.h>
#include <functional>
#include <iostream>
#include <map>
#include <new>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <typeinfo>
#include <unordered_map>

#include <algorithm> // TODO: simd misses the algorithm dependency for std::clamp(...) -> add to simd
// #include <vir/simd.h>
/* SPDX-License-Identifier: LGPL-3.0-or-later */
/* Copyright © 2022-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH
 *                       Matthias Kretz <m.kretz@gsi.de>
 */

#ifndef VIR_SIMD_H_
#define VIR_SIMD_H_

#if __cplusplus < 201703L
#error "simd requires C++17 or later"
#endif

#if __has_include (<experimental/simd>) && !defined VIR_DISABLE_STDX_SIMD && !defined __clang__
#include <experimental/simd>
#endif

#if defined __cpp_lib_experimental_parallel_simd && __cpp_lib_experimental_parallel_simd >= 201803

namespace vir::stdx
{
  using namespace std::experimental::parallelism_v2;
  using namespace std::experimental::parallelism_v2::__proposed;
}

#else

#include <cmath>
#include <cstring>
#ifdef _GLIBCXX_DEBUG_UB
#include <cstdio>
#endif
#include <functional>
#include <limits>
#include <tuple>
#include <type_traits>
#include <utility>

#ifdef VIR_SIMD_TS_DROPIN
namespace std::experimental
{
  inline namespace [[gnu::diagnose_as("virx")]] parallelism_v2
#else
namespace vir::stdx
#endif
{
  using std::size_t;

  namespace detail
  {
    template <typename T>
      struct type_identity
      { using type = T; };

    template <typename T>
      using type_identity_t = typename type_identity<T>::type;

    constexpr size_t
    bit_ceil(size_t x)
    {
      size_t r = 1;
      while (r < x)
        r <<= 1;
      return r;
    }

    constexpr size_t
    bit_floor(size_t x)
    {
      size_t r = x;
      do {
        r = x;
        x &= x - 1;
      } while (x);
      return r;
    }

    template <typename T>
      typename T::value_type
      value_type_or_identity_impl(int);

    template <typename T>
      T
      value_type_or_identity_impl(float);

    template <typename T>
      using value_type_or_identity_t
        = decltype(value_type_or_identity_impl<T>(int()));

    class ExactBool
    {
      const bool data;

    public:
      constexpr ExactBool(bool b) : data(b) {}

      ExactBool(int) = delete;

      constexpr operator bool() const { return data; }
    };

    template <typename... Args>
      [[noreturn]] [[gnu::always_inline]] inline void
      invoke_ub([[maybe_unused]] const char* msg,
                [[maybe_unused]] const Args&... args)
      {
#ifdef _GLIBCXX_DEBUG_UB
        std::fprintf(stderr, msg, args...);
        __builtin_trap();
#else
        __builtin_unreachable();
#endif
      }

    template <typename T>
      using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

    template <typename T>
      using L = std::numeric_limits<T>;

    template <bool B>
      using BoolConstant = std::integral_constant<bool, B>;

    template <size_t X>
      using SizeConstant = std::integral_constant<size_t, X>;

    template <size_t I, typename T, typename... Ts>
      constexpr auto
      pack_simd_subscript(const T& x0, const Ts&... xs)
      {
        if constexpr (I >= T::size())
          return pack_simd_subscript<I - T::size()>(xs...);
        else
          return x0[I];
      }

    template <class T>
      struct is_vectorizable : std::is_arithmetic<T>
      {};

    template <>
      struct is_vectorizable<bool> : std::false_type
      {};

    template <class T>
      inline constexpr bool is_vectorizable_v = is_vectorizable<T>::value;

    template <class T, typename = void>
      struct only_vectorizable
      {
        only_vectorizable() = delete;
        only_vectorizable(const only_vectorizable&) = delete;
        only_vectorizable(only_vectorizable&&) = delete;
        ~only_vectorizable() = delete;
      };

    template <class T>
      struct only_vectorizable<T, std::enable_if_t<is_vectorizable_v<T>>>
      {
      };

    // Deduces to a vectorizable type
    template <typename T, typename = std::enable_if_t<is_vectorizable_v<T>>>
      using Vectorizable = T;

    // Deduces to a floating-point type
    template <typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
      using FloatingPoint = T;

    // Deduces to a signed integer type
    template <typename T, typename = std::enable_if_t<std::conjunction_v<std::is_integral<T>,
                                                                         std::is_signed<T>>>>
      using SignedIntegral = T;

    // is_higher_integer_rank<T, U> (T has higher or equal integer rank than U)
    template <typename T, typename U, bool = (sizeof(T) > sizeof(U)),
              bool = (sizeof(T) == sizeof(U))>
      struct is_higher_integer_rank;

    template <typename T>
      struct is_higher_integer_rank<T, T, false, true>
      : public std::true_type
      {};

    template <typename T, typename U>
      struct is_higher_integer_rank<T, U, true, false>
      : public std::true_type
      {};

    template <typename T, typename U>
      struct is_higher_integer_rank<T, U, false, false>
      : public std::false_type
      {};

    // this may fail for char -> short if sizeof(char) == sizeof(short)
    template <typename T, typename U>
      struct is_higher_integer_rank<T, U, false, true>
      : public std::is_same<decltype(std::declval<T>() + std::declval<U>()), T>
      {};

    // is_value_preserving<From, To>
    template <typename From, typename To, bool = std::is_arithmetic_v<From>,
              bool = std::is_arithmetic_v<To>>
      struct is_value_preserving;

    // ignore "signed/unsigned mismatch" in the following trait.
    // The implicit conversions will do the right thing here.
    template <typename From, typename To>
      struct is_value_preserving<From, To, true, true>
      : public BoolConstant<L<From>::digits <= L<To>::digits
                              && L<From>::max() <= L<To>::max()
                              && L<From>::lowest() >= L<To>::lowest()
                              && !(std::is_signed_v<From> && std::is_unsigned_v<To>)> {};

    template <typename T>
      struct is_value_preserving<T, bool, true, true>
      : public std::false_type {};

    template <>
      struct is_value_preserving<bool, bool, true, true>
      : public std::true_type {};

    template <typename T>
      struct is_value_preserving<T, T, true, true>
      : public std::true_type {};

    template <typename From, typename To>
      struct is_value_preserving<From, To, false, true>
      : public std::is_convertible<From, To> {};

    template <typename From, typename To,
              typename = std::enable_if_t<is_value_preserving<remove_cvref_t<From>, To>::value>>
      using ValuePreserving = From;

    template <typename From, typename To,
              typename DecayedFrom = remove_cvref_t<From>,
              typename = std::enable_if_t<std::conjunction<
                                            std::is_convertible<From, To>,
                                            std::disjunction<
                                              std::is_same<DecayedFrom, To>,
                                              std::is_same<DecayedFrom, int>,
                                              std::conjunction<std::is_same<DecayedFrom, unsigned>,
                                                               std::is_unsigned<To>>,
                                              is_value_preserving<DecayedFrom, To>>>::value>>
      using ValuePreservingOrInt = From;

    // LoadStorePtr / is_possible_loadstore_conversion
    template <typename Ptr, typename ValueType>
      struct is_possible_loadstore_conversion
      : std::conjunction<is_vectorizable<Ptr>, is_vectorizable<ValueType>>
      {};

    template <>
      struct is_possible_loadstore_conversion<bool, bool> : std::true_type {};

    // Deduces to a type allowed for load/store with the given value type.
    template <typename Ptr, typename ValueType,
              typename = std::enable_if_t<
                           is_possible_loadstore_conversion<Ptr, ValueType>::value>>
      using LoadStorePtr = Ptr;
  }

  namespace simd_abi
  {
    struct scalar
    {};

    template <typename>
      inline constexpr int max_fixed_size = 32;

    template <int N>
      struct fixed_size
      {};

    template <class T>
      using native =
        std::conditional_t<(sizeof(T) > 8),
                           scalar,
                           fixed_size<
#ifdef __AVX512F__
                             64
#elif defined __AVX2__
                             32
#elif defined __AVX__
                             std::is_floating_point_v<T> ? 32 : 16
#else
                             16
#endif
                               / sizeof(T)
                           >
                          >;

    template <class T>
      using compatible = std::conditional_t<(sizeof(T) > 8),
                                            scalar,
                                            fixed_size<16 / sizeof(T)>>;

    template <typename T, size_t N, typename...>
      struct deduce
      { using type = std::conditional_t<N == 1, scalar, fixed_size<int(N)>>; };

    template <typename T, size_t N, typename... Abis>
      using deduce_t = typename deduce<T, N, Abis...>::type;
  }

  // flags //
  struct element_aligned_tag
  {};

  struct vector_aligned_tag
  {};

  template <size_t>
    struct overaligned_tag
    {};

  inline constexpr element_aligned_tag element_aligned{};

  inline constexpr vector_aligned_tag vector_aligned{};

  template <size_t N>
    inline constexpr overaligned_tag<N> overaligned{};

  // fwd decls //
  template <class T, class A = simd_abi::compatible<T>>
    class simd
    {
      simd() = delete;
      simd(const simd&) = delete;
      ~simd() = delete;
    };

  template <class T, class A = simd_abi::compatible<T>>
    class simd_mask
    {
      simd_mask() = delete;
      simd_mask(const simd_mask&) = delete;
      ~simd_mask() = delete;
    };

  // aliases //
  template <class T>
    using native_simd = simd<T, simd_abi::native<T>>;

  template <class T>
    using native_simd_mask = simd_mask<T, simd_abi::native<T>>;

  template <class T, int N>
    using fixed_size_simd = simd<T, simd_abi::fixed_size<N>>;

  template <class T, int N>
    using fixed_size_simd_mask = simd_mask<T, simd_abi::fixed_size<N>>;

  // Traits //
  template <class T>
    struct is_abi_tag : std::false_type
    {};

  template <class T>
    inline constexpr bool is_abi_tag_v = is_abi_tag<T>::value;

  template <>
    struct is_abi_tag<simd_abi::scalar> : std::true_type
    {};

  template <int N>
    struct is_abi_tag<simd_abi::fixed_size<N>> : std::true_type
    {};

  template <class T>
    struct is_simd : std::false_type
    {};

  template <class T>
    inline constexpr bool is_simd_v = is_simd<T>::value;

  template <class T, class A>
    struct is_simd<simd<T, A>>
    : std::conjunction<detail::is_vectorizable<T>, is_abi_tag<A>>
    {};

  template <class T>
    struct is_simd_mask : std::false_type
    {};

  template <class T>
    inline constexpr bool is_simd_mask_v = is_simd_mask<T>::value;

  template <class T, class A>
    struct is_simd_mask<simd_mask<T, A>>
    : std::conjunction<detail::is_vectorizable<T>, is_abi_tag<A>>
    {};

  template <class T>
    struct is_simd_flag_type : std::false_type
    {};

  template <class T>
    inline constexpr bool is_simd_flag_type_v = is_simd_flag_type<T>::value;

  template <class T, class A = simd_abi::compatible<T>>
    struct simd_size;

  template <class T, class A = simd_abi::compatible<T>>
    inline constexpr size_t simd_size_v = simd_size<T, A>::value;

  template <class T>
    struct simd_size<detail::Vectorizable<T>, simd_abi::scalar>
    : std::integral_constant<size_t, 1>
    {};

  template <class T, int N>
    struct simd_size<detail::Vectorizable<T>, simd_abi::fixed_size<N>>
    : std::integral_constant<size_t, N>
    {};

  template <class T, class U = typename T::value_type>
    struct memory_alignment;

  template <class T, class U = typename T::value_type>
    inline constexpr size_t memory_alignment_v = memory_alignment<T, U>::value;

  template <class T, class A, class U>
    struct memory_alignment<simd<T, A>, detail::Vectorizable<U>>
    : std::integral_constant<size_t, alignof(U)>
    {};

  template <class T, class A>
    struct memory_alignment<simd_mask<T, A>, bool>
    : std::integral_constant<size_t, alignof(bool)>
    {};

  template <class T, class V,
            class = typename std::conjunction<detail::is_vectorizable<T>,
                                              std::disjunction<is_simd<V>, is_simd_mask<V>>>::type>
    struct rebind_simd;

  template <class T, class V>
    using rebind_simd_t = typename rebind_simd<T, V>::type;

  template <class T, class U, class A>
    struct rebind_simd<T, simd<U, A>, std::true_type>
    { using type = simd<T, A>; };

  template <class T, class U, class A>
    struct rebind_simd<T, simd_mask<U, A>, std::true_type>
    { using type = simd_mask<T, A>; };

  template <int N, class V,
            class = typename std::conjunction<
                               detail::BoolConstant<(N > 0)>,
                               std::disjunction<is_simd<V>, is_simd_mask<V>>
                             >::type>
    struct resize_simd;

  template <int N, class V>
    using resize_simd_t = typename resize_simd<N, V>::type;

  template <int N, class T, class A>
    struct resize_simd<N, simd<T, A>, std::true_type>
    {
      using type = simd<T, std::conditional_t<N == 1, simd_abi::scalar, simd_abi::fixed_size<N>>>;
    };

  template <int N, class T, class A>
    struct resize_simd<N, simd_mask<T, A>, std::true_type>
    {
      using type = simd_mask<T, std::conditional_t<
                                  N == 1, simd_abi::scalar, simd_abi::fixed_size<N>>>;
    };

  // simd_mask (scalar)
  template <class T>
    class simd_mask<detail::Vectorizable<T>, simd_abi::scalar>
    : public detail::only_vectorizable<T>
    {
      bool data;

    public:
      using value_type = bool;
      using reference = bool&;
      using abi_type = simd_abi::scalar;
      using simd_type = simd<T, abi_type>;

      static constexpr size_t size() noexcept
      { return 1; }

      constexpr simd_mask() = default;
      constexpr simd_mask(const simd_mask&) = default;
      constexpr simd_mask(simd_mask&&) noexcept = default;
      constexpr simd_mask& operator=(const simd_mask&) = default;
      constexpr simd_mask& operator=(simd_mask&&) noexcept = default;

      // explicit broadcast constructor
      explicit constexpr
      simd_mask(bool x)
      : data(x) {}

      template <typename F>
        explicit constexpr
        simd_mask(F&& gen, std::enable_if_t<
                             std::is_same_v<decltype(std::declval<F>()(detail::SizeConstant<0>())),
                                            value_type>>* = nullptr)
        : data(gen(detail::SizeConstant<0>()))
        {}

      // load constructor
      template <typename Flags>
        simd_mask(const value_type* mem, Flags)
        : data(mem[0])
        {}

      template <typename Flags>
        simd_mask(const value_type* mem, simd_mask k, Flags)
        : data(k ? mem[0] : false)
        {}

      // loads [simd_mask.load]
      template <typename Flags>
        void
        copy_from(const value_type* mem, Flags)
        { data = mem[0]; }

      // stores [simd_mask.store]
      template <typename Flags>
        void
        copy_to(value_type* mem, Flags) const
        { mem[0] = data; }

      // scalar access
      constexpr reference
      operator[](size_t i)
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data;
      }

      constexpr value_type
      operator[](size_t i) const
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data;
      }

      // negation
      constexpr simd_mask
      operator!() const
      { return simd_mask(not data); }

      // simd_mask binary operators [simd_mask.binary]
      friend constexpr simd_mask
      operator&&(const simd_mask& x, const simd_mask& y)
      { return simd_mask(x.data && y.data); }

      friend constexpr simd_mask
      operator||(const simd_mask& x, const simd_mask& y)
      { return simd_mask(x.data || y.data); }

      friend constexpr simd_mask
      operator&(const simd_mask& x, const simd_mask& y)
      { return simd_mask(x.data & y.data); }

      friend constexpr simd_mask
      operator|(const simd_mask& x, const simd_mask& y)
      { return simd_mask(x.data | y.data); }

      friend constexpr simd_mask
      operator^(const simd_mask& x, const simd_mask& y)
      { return simd_mask(x.data ^ y.data); }

      friend constexpr simd_mask&
      operator&=(simd_mask& x, const simd_mask& y)
      {
        x.data &= y.data;
        return x;
      }

      friend constexpr simd_mask&
      operator|=(simd_mask& x, const simd_mask& y)
      {
        x.data |= y.data;
        return x;
      }

      friend constexpr simd_mask&
      operator^=(simd_mask& x, const simd_mask& y)
      {
        x.data ^= y.data;
        return x;
      }

      // simd_mask compares [simd_mask.comparison]
      friend constexpr simd_mask
      operator==(const simd_mask& x, const simd_mask& y)
      { return simd_mask(x.data == y.data); }

      friend constexpr simd_mask
      operator!=(const simd_mask& x, const simd_mask& y)
      { return simd_mask(x.data != y.data); }
    };

  // simd_mask (fixed_size)
  template <class T, int N>
    class simd_mask<detail::Vectorizable<T>, simd_abi::fixed_size<N>>
    : public detail::only_vectorizable<T>
    {
    private:
      template <typename V, int M, size_t Parts>
        friend std::enable_if_t<M == Parts * V::size() && is_simd_mask_v<V>, std::array<V, Parts>>
        split(const simd_mask<typename V::simd_type::value_type, simd_abi::fixed_size<M>>&);

      bool data[N];

      template <typename F, size_t... Is>
        constexpr
        simd_mask(std::index_sequence<Is...>, F&& init)
        : data {init(detail::SizeConstant<Is>())...}
        {}

    public:
      using value_type = bool;
      using reference = bool&;
      using abi_type = simd_abi::fixed_size<N>;
      using simd_type = simd<T, abi_type>;

      static constexpr size_t size() noexcept
      { return N; }

      constexpr simd_mask() = default;
      constexpr simd_mask(const simd_mask&) = default;
      constexpr simd_mask(simd_mask&&) noexcept = default;
      constexpr simd_mask& operator=(const simd_mask&) = default;
      constexpr simd_mask& operator=(simd_mask&&) noexcept = default;

      // explicit broadcast constructor
      explicit constexpr
      simd_mask(bool x)
      : simd_mask([x](size_t) { return x; })
      {}

      template <typename F>
        explicit constexpr
        simd_mask(F&& gen, std::enable_if_t<
                             std::is_same_v<decltype(std::declval<F>()(detail::SizeConstant<0>())),
                                            value_type>>* = nullptr)
        : simd_mask(std::make_index_sequence<N>(), std::forward<F>(gen))
        {}

      // implicit conversions
      template <typename U>
        constexpr
        simd_mask(const simd_mask<U, abi_type>& x)
        : simd_mask([&x](auto i) { return x[i]; })
        {}

      // load constructor
      template <typename Flags>
        simd_mask(const value_type* mem, Flags)
        : simd_mask([mem](size_t i) { return mem[i]; })
        {}

      template <typename Flags>
        simd_mask(const value_type* mem, const simd_mask& k, Flags)
        : simd_mask([mem, &k](size_t i) { return k[i] ? mem[i] : false; })
        {}

      // loads [simd_mask.load]
      template <typename Flags>
        void
        copy_from(const value_type* mem, Flags)
        { std::memcpy(data, mem, N * sizeof(bool)); }

      // stores [simd_mask.store]
      template <typename Flags>
        void
        copy_to(value_type* mem, Flags) const
        { std::memcpy(mem, data, N * sizeof(bool)); }

      // scalar access
      constexpr reference
      operator[](size_t i)
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data[i];
      }

      constexpr value_type
      operator[](size_t i) const
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data[i];
      }

      // negation
      constexpr simd_mask
      operator!() const
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = !data[i];
        return r;
      }

      // simd_mask binary operators [simd_mask.binary]
      friend constexpr simd_mask
      operator&&(const simd_mask& x, const simd_mask& y)
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = x.data[i] & y.data[i];
        return r;
      }

      friend constexpr simd_mask
      operator||(const simd_mask& x, const simd_mask& y)
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = x.data[i] | y.data[i];
        return r;
      }

      friend constexpr simd_mask
      operator&(const simd_mask& x, const simd_mask& y)
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = x.data[i] & y.data[i];
        return r;
      }

      friend constexpr simd_mask
      operator|(const simd_mask& x, const simd_mask& y)
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = x.data[i] | y.data[i];
        return r;
      }

      friend constexpr simd_mask
      operator^(const simd_mask& x, const simd_mask& y)
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = x.data[i] ^ y.data[i];
        return r;
      }

      friend constexpr simd_mask&
      operator&=(simd_mask& x, const simd_mask& y)
      {
        for (int i = 0; i < N; ++i)
          x.data[i] &= y.data[i];
        return x;
      }

      friend constexpr simd_mask&
      operator|=(simd_mask& x, const simd_mask& y)
      {
        for (int i = 0; i < N; ++i)
          x.data[i] |= y.data[i];
        return x;
      }

      friend constexpr simd_mask&
      operator^=(simd_mask& x, const simd_mask& y)
      {
        for (int i = 0; i < N; ++i)
          x.data[i] ^= y.data[i];
        return x;
      }

      // simd_mask compares [simd_mask.comparison]
      friend constexpr simd_mask
      operator==(const simd_mask& x, const simd_mask& y)
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = x.data[i] == y.data[i];
        return r;
      }

      friend constexpr simd_mask
      operator!=(const simd_mask& x, const simd_mask& y)
      {
        simd_mask r {};
        for (int i = 0; i < N; ++i)
          r.data[i] = x.data[i] != y.data[i];
        return r;
      }
    };

  // simd_mask reductions [simd_mask.reductions]
  template <typename T>
    constexpr bool
    all_of(simd_mask<T, simd_abi::scalar> k) noexcept
    { return k[0]; }

  template <typename T>
    constexpr bool
    any_of(simd_mask<T, simd_abi::scalar> k) noexcept
    { return k[0]; }

  template <typename T>
    constexpr bool
    none_of(simd_mask<T, simd_abi::scalar> k) noexcept
    { return not k[0]; }

  template <typename T>
    constexpr bool
    some_of(simd_mask<T, simd_abi::scalar>) noexcept
    { return false; }

  template <typename T>
    constexpr int
    popcount(simd_mask<T, simd_abi::scalar> k) noexcept
    { return static_cast<int>(k[0]); }

  template <typename T>
    constexpr int
    find_first_set(simd_mask<T, simd_abi::scalar> k) noexcept
    {
      if (not k[0])
        detail::invoke_ub("find_first_set(empty mask) is UB");
      return 0;
    }

  template <typename T>
    constexpr int
    find_last_set(simd_mask<T, simd_abi::scalar> k) noexcept
    {
      if (not k[0])
        detail::invoke_ub("find_last_set(empty mask) is UB");
      return 0;
    }

  template <typename T, int N>
    constexpr bool
    all_of(const simd_mask<T, simd_abi::fixed_size<N>>& k) noexcept
    {
      for (int i = 0; i < N; ++i)
        {
          if (not k[i])
            return false;
        }
      return true;
    }

  template <typename T, int N>
    constexpr bool
    any_of(const simd_mask<T, simd_abi::fixed_size<N>>& k) noexcept
    {
      for (int i = 0; i < N; ++i)
        {
          if (k[i])
            return true;
        }
      return false;
    }

  template <typename T, int N>
    constexpr bool
    none_of(const simd_mask<T, simd_abi::fixed_size<N>>& k) noexcept
    {
      for (int i = 0; i < N; ++i)
        {
          if (k[i])
            return false;
        }
      return true;
    }

  template <typename T, int N>
    constexpr bool
    some_of(const simd_mask<T, simd_abi::fixed_size<N>>& k) noexcept
    {
      bool last = k[0];
      for (int i = 1; i < N; ++i)
        {
          if (last != k[i])
            return true;
        }
      return false;
    }

  template <typename T, int N>
    constexpr int
    popcount(const simd_mask<T, simd_abi::fixed_size<N>>& k) noexcept
    {
      int cnt = k[0];
      for (int i = 1; i < N; ++i)
        cnt += k[i];
      return cnt;
    }

  template <typename T, int N>
    constexpr int
    find_first_set(const simd_mask<T, simd_abi::fixed_size<N>>& k) noexcept
    {
      for (int i = 0; i < N; ++i)
        {
          if (k[i])
            return i;
        }
      detail::invoke_ub("find_first_set(empty mask) is UB");
    }

  template <typename T, int N>
    constexpr int
    find_last_set(const simd_mask<T, simd_abi::fixed_size<N>>& k) noexcept
    {
      for (int i = N - 1; i >= 0; --i)
        {
          if (k[i])
            return i;
        }
      detail::invoke_ub("find_last_set(empty mask) is UB");
    }

  constexpr bool
  all_of(detail::ExactBool x) noexcept
  { return x; }

  constexpr bool
  any_of(detail::ExactBool x) noexcept
  { return x; }

  constexpr bool
  none_of(detail::ExactBool x) noexcept
  { return !x; }

  constexpr bool
  some_of(detail::ExactBool) noexcept
  { return false; }

  constexpr int
  popcount(detail::ExactBool x) noexcept
  { return x; }

  constexpr int
  find_first_set(detail::ExactBool)
  { return 0; }

  constexpr int
  find_last_set(detail::ExactBool)
  { return 0; }

  // scalar_simd_int_base
  template <class T, bool = std::is_integral_v<T>>
    class scalar_simd_int_base
    {};

  template <class T>
    class scalar_simd_int_base<T, true>
    {
      using Derived = simd<T, simd_abi::scalar>;

      constexpr T&
      d() noexcept
      { return static_cast<Derived*>(this)->data; }

      constexpr const T&
      d() const noexcept
      { return static_cast<const Derived*>(this)->data; }

    public:
      friend constexpr Derived&
      operator%=(Derived& lhs, Derived x)
      {
        lhs.d() %= x.d();
        return lhs;
      }

      friend constexpr Derived&
      operator&=(Derived& lhs, Derived x)
      {
        lhs.d() &= x.d();
        return lhs;
      }

      friend constexpr Derived&
      operator|=(Derived& lhs, Derived x)
      {
        lhs.d() |= x.d();
        return lhs;
      }

      friend constexpr Derived&
      operator^=(Derived& lhs, Derived x)
      {
        lhs.d() ^= x.d();
        return lhs;
      }

      friend constexpr Derived&
      operator<<=(Derived& lhs, Derived x)
      {
        lhs.d() <<= x.d();
        return lhs;
      }

      friend constexpr Derived&
      operator>>=(Derived& lhs, Derived x)
      {
        lhs.d() >>= x.d();
        return lhs;
      }

      friend constexpr Derived
      operator%(Derived x, Derived y)
      {
        x.d() %= y.d();
        return x;
      }

      friend constexpr Derived
      operator&(Derived x, Derived y)
      {
        x.d() &= y.d();
        return x;
      }

      friend constexpr Derived
      operator|(Derived x, Derived y)
      {
        x.d() |= y.d();
        return x;
      }

      friend constexpr Derived
      operator^(Derived x, Derived y)
      {
        x.d() ^= y.d();
        return x;
      }

      friend constexpr Derived
      operator<<(Derived x, Derived y)
      {
        x.d() <<= y.d();
        return x;
      }

      friend constexpr Derived
      operator>>(Derived x, Derived y)
      {
        x.d() >>= y.d();
        return x;
      }

      friend constexpr Derived
      operator<<(Derived x, int y)
      {
        x.d() <<= y;
        return x;
      }

      friend constexpr Derived
      operator>>(Derived x, int y)
      {
        x.d() >>= y;
        return x;
      }

      constexpr Derived
      operator~() const
      { return Derived(static_cast<T>(~d())); }
    };

  // simd (scalar)
  template <class T>
    class simd<T, simd_abi::scalar>
    : public scalar_simd_int_base<T>, public detail::only_vectorizable<T>
    {
      friend class scalar_simd_int_base<T>;

      T data;

    public:
      using value_type = T;
      using reference = T&;
      using abi_type = simd_abi::scalar;
      using mask_type = simd_mask<T, abi_type>;

      static constexpr size_t size() noexcept
      { return 1; }

      constexpr simd() = default;
      constexpr simd(const simd&) = default;
      constexpr simd(simd&&) noexcept = default;
      constexpr simd& operator=(const simd&) = default;
      constexpr simd& operator=(simd&&) noexcept = default;

      // simd constructors
      template <typename U>
        constexpr
        simd(detail::ValuePreservingOrInt<U, value_type>&& value) noexcept
        : data(value)
        {}

      // generator constructor
      template <typename F>
        explicit constexpr
        simd(F&& gen, detail::ValuePreservingOrInt<
                        decltype(std::declval<F>()(std::declval<detail::SizeConstant<0>&>())),
                        value_type>* = nullptr)
        : data(gen(detail::SizeConstant<0>()))
        {}

      // load constructor
      template <typename U, typename Flags>
        simd(const U* mem, Flags)
        : data(mem[0])
        {}

      // loads [simd.load]
      template <typename U, typename Flags>
        void
        copy_from(const detail::Vectorizable<U>* mem, Flags)
        { data = mem[0]; }

      // stores [simd.store]
      template <typename U, typename Flags>
        void
        copy_to(detail::Vectorizable<U>* mem, Flags) const
        { mem[0] = data; }

      // scalar access
      constexpr reference
      operator[](size_t i)
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data;
      }

      constexpr value_type
      operator[](size_t i) const
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data;
      }

      // increment and decrement:
      constexpr simd&
      operator++()
      {
        ++data;
        return *this;
      }

      constexpr simd
      operator++(int)
      {
        simd r = *this;
        ++data;
        return r;
      }

      constexpr simd&
      operator--()
      {
        --data;
        return *this;
      }

      constexpr simd
      operator--(int)
      {
        simd r = *this;
        --data;
        return r;
      }

      // unary operators
      constexpr mask_type
      operator!() const
      { return mask_type(not data); }

      constexpr simd
      operator+() const
      { return *this; }

      constexpr simd
      operator-() const
      { return -data; }

      // compound assignment [simd.cassign]
      constexpr friend simd&
      operator+=(simd& lhs, const simd& x)
      { return lhs = lhs + x; }

      constexpr friend simd&
      operator-=(simd& lhs, const simd& x)
      { return lhs = lhs - x; }

      constexpr friend simd&
      operator*=(simd& lhs, const simd& x)
      { return lhs = lhs * x; }

      constexpr friend simd&
        operator/=(simd& lhs, const simd& x)
      { return lhs = lhs / x; }

      // binary operators [simd.binary]
      constexpr friend simd
      operator+(const simd& x, const simd& y)
      { simd r = x; r.data += y.data; return r; }

      constexpr friend simd
      operator-(const simd& x, const simd& y)
      { simd r = x; r.data -= y.data; return r; }

      constexpr friend simd
      operator*(const simd& x, const simd& y)
      { simd r = x; r.data *= y.data; return r; }

      constexpr friend simd
      operator/(const simd& x, const simd& y)
      { simd r = x; r.data /= y.data; return r; }

      // compares [simd.comparison]
      constexpr friend mask_type
      operator==(const simd& x, const simd& y)
      { return mask_type(x.data == y.data); }

      constexpr friend mask_type
      operator!=(const simd& x, const simd& y)
      { return mask_type(x.data != y.data); }

      constexpr friend mask_type
      operator<(const simd& x, const simd& y)
      { return mask_type(x.data < y.data); }

      constexpr friend mask_type
      operator<=(const simd& x, const simd& y)
      { return mask_type(x.data <= y.data); }

      constexpr friend mask_type
      operator>(const simd& x, const simd& y)
      { return mask_type(x.data > y.data); }

      constexpr friend mask_type
      operator>=(const simd& x, const simd& y)
      { return mask_type(x.data >= y.data); }
    };

  // fixed_simd_int_base
  template <class T, int N, bool = std::is_integral_v<T>>
    class fixed_simd_int_base
    {};

  template <class T, int N>
    class fixed_simd_int_base<T, N, true>
    {
      using Derived = simd<T, simd_abi::fixed_size<N>>;

      constexpr T&
      d(int i) noexcept
      { return static_cast<Derived*>(this)->data[i]; }

      constexpr const T&
      d(int i) const noexcept
      { return static_cast<const Derived*>(this)->data[i]; }

    public:
      friend constexpr Derived&
      operator%=(Derived& lhs, const Derived& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.d(i) %= x.d(i);
        return lhs;
      }

      friend constexpr Derived&
      operator&=(Derived& lhs, const Derived& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.d(i) &= x.d(i);
        return lhs;
      }

      friend constexpr Derived&
      operator|=(Derived& lhs, const Derived& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.d(i) |= x.d(i);
        return lhs;
      }

      friend constexpr Derived&
      operator^=(Derived& lhs, const Derived& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.d(i) ^= x.d(i);
        return lhs;
      }

      friend constexpr Derived&
      operator<<=(Derived& lhs, const Derived& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.d(i) <<= x.d(i);
        return lhs;
      }

      friend constexpr Derived&
      operator>>=(Derived& lhs, const Derived& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.d(i) >>= x.d(i);
        return lhs;
      }

      friend constexpr Derived
      operator%(const Derived& x, const Derived& y)
      { return Derived([&](auto i) -> T { return x[i] % y[i]; }); }

      friend constexpr Derived
      operator&(const Derived& x, const Derived& y)
      { return Derived([&](auto i) -> T { return x[i] & y[i]; }); }

      friend constexpr Derived
      operator|(const Derived& x, const Derived& y)
      { return Derived([&](auto i) -> T { return x[i] | y[i]; }); }

      friend constexpr Derived
      operator^(const Derived& x, const Derived& y)
      { return Derived([&](auto i) -> T { return x[i] ^ y[i]; }); }

      friend constexpr Derived
      operator<<(const Derived& x, const Derived& y)
      { return Derived([&](auto i) -> T { return x[i] << y[i]; }); }

      friend constexpr Derived
      operator>>(const Derived& x, const Derived& y)
      { return Derived([&](auto i) -> T { return x[i] >> y[i]; }); }

      friend constexpr Derived
      operator<<(const Derived& x, int y)
      { return Derived([&](auto i) -> T { return x[i] << y; }); }

      friend constexpr Derived
      operator>>(const Derived& x, int y)
      { return Derived([&](auto i) -> T { return x[i] >> y; }); }

      constexpr Derived
      operator~() const
      { return Derived([&](auto i) -> T { return ~d(i); }); }
    };

  // simd (fixed_size)
  template <class T, int N>
    class simd<T, simd_abi::fixed_size<N>>
    : public fixed_simd_int_base<T, N>, public detail::only_vectorizable<T>
    {
    private:
      friend class fixed_simd_int_base<T, N>;

      template <typename V, int M, size_t Parts>
        friend std::enable_if_t<M == Parts * V::size() && is_simd_v<V>, std::array<V, Parts>>
        split(const simd<typename V::value_type, simd_abi::fixed_size<M>>&);

      template <size_t... Sizes, typename U>
        friend std::tuple<simd<U, simd_abi::deduce_t<U, int(Sizes)>>...>
        split(const simd<U, simd_abi::fixed_size<int((Sizes + ...))>>&);

      T data[N];

      template <typename F, size_t... Is>
        constexpr
        simd(std::index_sequence<Is...>, F&& init)
        : data {static_cast<value_type>(init(detail::SizeConstant<Is>()))...}
        {}

    public:
      using value_type = T;
      using reference = T&;
      using abi_type = simd_abi::fixed_size<N>;
      using mask_type = simd_mask<T, abi_type>;

      static constexpr size_t size() noexcept
      { return N; }

      constexpr simd() = default;
      constexpr simd(const simd&) = default;
      constexpr simd(simd&&) noexcept = default;
      constexpr simd& operator=(const simd&) = default;
      constexpr simd& operator=(simd&&) noexcept = default;

      // simd constructors
      template <typename U>
        constexpr
        simd(detail::ValuePreservingOrInt<U, value_type>&& value) noexcept
        : simd([v = static_cast<value_type>(value)](size_t) { return v; })
        {}

      // conversion constructors
      template <typename U,
                typename = std::enable_if_t<
                             std::conjunction_v<detail::is_value_preserving<U, value_type>,
                                                detail::is_higher_integer_rank<value_type, U>>>>
        constexpr
        simd(const simd<U, abi_type>& x)
        : simd([&x](auto i) { return static_cast<value_type>(x[i]); })
        {}

      // generator constructor
      template <typename F>
        explicit constexpr
        simd(F&& gen, detail::ValuePreservingOrInt<
                        decltype(std::declval<F>()(std::declval<detail::SizeConstant<0>&>())),
                        value_type>* = nullptr)
        : simd(std::make_index_sequence<N>(), std::forward<F>(gen))
        {}

      // load constructor
      template <typename U, typename Flags>
        simd(const U* mem, Flags)
        : simd([mem](auto i) -> value_type { return mem[i]; })
        {}

      // loads [simd.load]
      template <typename U, typename Flags>
        void
        copy_from(const detail::Vectorizable<U>* mem, Flags)
        {
          for (int i = 0; i < N; ++i)
            data[i] = mem[i];
        }

      // stores [simd.store]
      template <typename U, typename Flags>
        void
        copy_to(detail::Vectorizable<U>* mem, Flags) const
        {
          for (int i = 0; i < N; ++i)
            mem[i] = data[i];
        }

      // scalar access
      constexpr reference
      operator[](size_t i)
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data[i];
      }

      constexpr value_type
      operator[](size_t i) const
      {
        if (i >= size())
          detail::invoke_ub("Subscript %d is out of range [0, %d]", i, size() - 1);
        return data[i];
      }

      // increment and decrement:
      constexpr simd&
      operator++()
      {
        for (int i = 0; i < N; ++i)
          ++data[i];
        return *this;
      }

      constexpr simd
      operator++(int)
      {
        simd r = *this;
        for (int i = 0; i < N; ++i)
          ++data[i];
        return r;
      }

      constexpr simd&
      operator--()
      {
        for (int i = 0; i < N; ++i)
          --data[i];
        return *this;
      }

      constexpr simd
      operator--(int)
      {
        simd r = *this;
        for (int i = 0; i < N; ++i)
          --data[i];
        return r;
      }

      // unary operators
      constexpr mask_type
      operator!() const
      { return mask_type([&](auto i) { return !data[i]; }); }

      constexpr simd
      operator+() const
      { return *this; }

      constexpr simd
      operator-() const
      { return simd([&](auto i) -> value_type { return -data[i]; }); }

      // compound assignment [simd.cassign]
      constexpr friend simd&
      operator+=(simd& lhs, const simd& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.data[i] += x.data[i];
        return lhs;
      }

      constexpr friend simd&
      operator-=(simd& lhs, const simd& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.data[i] -= x.data[i];
        return lhs;
      }

      constexpr friend simd&
      operator*=(simd& lhs, const simd& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.data[i] *= x.data[i];
        return lhs;
      }

      constexpr friend simd&
      operator/=(simd& lhs, const simd& x)
      {
        for (int i = 0; i < N; ++i)
          lhs.data[i] /= x.data[i];
        return lhs;
      }

      // binary operators [simd.binary]
      constexpr friend simd
      operator+(const simd& x, const simd& y)
      { return simd([&](auto i) { return x.data[i] + y.data[i]; }); }

      constexpr friend simd
      operator-(const simd& x, const simd& y)
      { return simd([&](auto i) { return x.data[i] - y.data[i]; }); }

      constexpr friend simd
      operator*(const simd& x, const simd& y)
      { return simd([&](auto i) { return x.data[i] * y.data[i]; }); }

      constexpr friend simd
      operator/(const simd& x, const simd& y)
      { return simd([&](auto i) { return x.data[i] / y.data[i]; }); }

      // compares [simd.comparison]
      constexpr friend mask_type
      operator==(const simd& x, const simd& y)
      { return mask_type([&](auto i) { return x.data[i] == y.data[i]; }); }

      constexpr friend mask_type
      operator!=(const simd& x, const simd& y)
      { return mask_type([&](auto i) { return x.data[i] != y.data[i]; }); }

      constexpr friend mask_type
      operator<(const simd& x, const simd& y)
      { return mask_type([&](auto i) { return x.data[i] < y.data[i]; }); }

      constexpr friend mask_type
      operator<=(const simd& x, const simd& y)
      { return mask_type([&](auto i) { return x.data[i] <= y.data[i]; }); }

      constexpr friend mask_type
      operator>(const simd& x, const simd& y)
      { return mask_type([&](auto i) { return x.data[i] > y.data[i]; }); }

      constexpr friend mask_type
      operator>=(const simd& x, const simd& y)
      { return mask_type([&](auto i) { return x.data[i] >= y.data[i]; }); }
    };

  // casts [simd.casts]
  // static_simd_cast
  template <typename T, typename U, typename A,
            typename = std::enable_if_t<detail::is_vectorizable_v<T>>>
    constexpr simd<T, A>
    static_simd_cast(const simd<U, A>& x)
    { return simd<T, A>([&x](auto i) { return static_cast<T>(x[i]); }); }

  template <typename V, typename U, typename A,
            typename = std::enable_if_t<is_simd_v<V>>>
    constexpr V
    static_simd_cast(const simd<U, A>& x)
    { return V([&x](auto i) { return static_cast<typename V::value_type>(x[i]); }); }

  template <typename T, typename U, typename A,
            typename = std::enable_if_t<detail::is_vectorizable_v<T>>>
    constexpr simd_mask<T, A>
    static_simd_cast(const simd_mask<U, A>& x)
    { return simd_mask<T, A>([&x](auto i) { return x[i]; }); }

  template <typename M, typename U, typename A,
            typename = std::enable_if_t<M::size() == simd_size_v<U, A>>>
    constexpr M
    static_simd_cast(const simd_mask<U, A>& x)
    { return M([&x](auto i) { return x[i]; }); }

  // simd_cast
  template <typename T, typename U, typename A,
            typename To = detail::value_type_or_identity_t<T>>
    constexpr auto
    simd_cast(const simd<detail::ValuePreserving<U, To>, A>& x)
    -> decltype(static_simd_cast<T>(x))
    { return static_simd_cast<T>(x); }

  // to_fixed_size
  template <typename T, int N>
    constexpr fixed_size_simd<T, N>
    to_fixed_size(const fixed_size_simd<T, N>& x)
    { return x; }

  template <typename T, int N>
    constexpr fixed_size_simd_mask<T, N>
    to_fixed_size(const fixed_size_simd_mask<T, N>& x)
    { return x; }

  template <typename T>
    constexpr fixed_size_simd<T, 1>
    to_fixed_size(const simd<T> x)
    { return x[0]; }

  template <typename T>
    constexpr fixed_size_simd_mask<T, 1>
    to_fixed_size(const simd_mask<T> x)
    { return fixed_size_simd_mask<T, 1>(x[0]); }

  // to_native
  template <typename T>
    constexpr simd<T>
    to_native(const fixed_size_simd<T, 1> x)
    { return x[0]; }

  template <typename T>
    constexpr simd_mask<T>
    to_native(const fixed_size_simd_mask<T, 1> x)
    { return simd_mask<T>(x[0]); }

  // to_compatible
  template <typename T>
    constexpr simd<T>
    to_compatible(const fixed_size_simd<T, 1> x)
    { return x[0]; }

  template <typename T>
    constexpr simd_mask<T>
    to_compatible(const fixed_size_simd_mask<T, 1> x)
    { return simd_mask<T>(x[0]); }

  // split(simd)
  template <typename V, int N, size_t Parts = N / V::size()>
    std::enable_if_t<N == Parts * V::size() && is_simd_v<V>, std::array<V, Parts>>
    split(const simd<typename V::value_type, simd_abi::fixed_size<N>>& x)
    {
      const auto* data = x.data;
      return [&]<size_t... Is>(std::index_sequence<Is...>)
               -> std::array<V, Parts> {
                 return {V(data + Is * V::size(), element_aligned)...};
               }(std::make_index_sequence<Parts>());
    }

  // split(simd_mask)
  template <typename V, int N, size_t Parts = N / V::size()>
    std::enable_if_t<N == Parts * V::size() && is_simd_mask_v<V>, std::array<V, Parts>>
    split(const simd_mask<typename V::simd_type::value_type, simd_abi::fixed_size<N>>& x)
    {
      const auto* data = x.data;
      return [&]<size_t... Is>(std::index_sequence<Is...>)
               -> std::array<V, Parts> {
                 return {V(data + Is * V::size(), element_aligned)...};
               }(std::make_index_sequence<Parts>());
    }

  // split<Sizes...>
  template <size_t... Sizes, typename T>
    std::tuple<simd<T, simd_abi::deduce_t<T, int(Sizes)>>...>
    split(const simd<T, simd_abi::fixed_size<int((Sizes + ...))>>& x)
    {
      using R = std::tuple<simd<T, simd_abi::deduce_t<T, int(Sizes)>>...>;
      const auto* data = x.data;
      return [&]<size_t... Is>(std::index_sequence<Is...>) -> R {
        constexpr size_t offsets[sizeof...(Sizes)] = {
          []<size_t... Js>(std::index_sequence<Js...>) {
            constexpr size_t sizes[sizeof...(Sizes)] = {Sizes...};
            return (sizes[Js] + ... + 0);
          }(std::make_index_sequence<Is>())...
        };
        return {simd<T, simd_abi::deduce_t<T, int(Sizes)>>(data + offsets[Is],
                                                           element_aligned)...};
      }(std::make_index_sequence<sizeof...(Sizes)>());
    }

  // split<V>(V)
  template <typename V>
    std::enable_if_t<std::disjunction_v<is_simd<V>, is_simd_mask<V>>, std::array<V, 1>>
    split(const V& x)
    { return {x}; }

  // concat(simd...)
  template <typename T, typename... As>
    inline constexpr
    simd<T, simd_abi::deduce_t<T, (simd_size_v<T, As> + ...)>>
    concat(const simd<T, As>&... xs)
    {
      using R = simd<T, simd_abi::deduce_t<T, (simd_size_v<T, As> + ...)>>;
      return R([&](auto i) {
               return detail::pack_simd_subscript<i>(xs...);
             });
    }

  // concat(simd_mask...)
  template <typename T, typename... As>
    inline constexpr
    simd_mask<T, simd_abi::deduce_t<T, (simd_size_v<T, As> + ...)>>
    concat(const simd_mask<T, As>&... xs)
    {
      using R = simd_mask<T, simd_abi::deduce_t<T, (simd_size_v<T, As> + ...)>>;
      return R([&](auto i) -> bool {
               return detail::pack_simd_subscript<i>(xs...);
             });
    }

  // concat(array<simd>)
  template <typename T, typename A, size_t N>
    inline constexpr
    simd<T, simd_abi::deduce_t<T, N * simd_size_v<T, A>>>
    concat(const std::array<simd<T, A>, N>& x)
    {
      constexpr int K = simd_size_v<T, A>;
      using R = simd<T, simd_abi::deduce_t<T, N * K>>;
      return R([&](auto i) {
               return x[i / K][i % K];
             });
    }

  // concat(array<simd_mask>)
  template <typename T, typename A, size_t N>
    inline constexpr
    simd_mask<T, simd_abi::deduce_t<T, N * simd_size_v<T, A>>>
    concat(const std::array<simd_mask<T, A>, N>& x)
    {
      constexpr int K = simd_size_v<T, A>;
      using R = simd_mask<T, simd_abi::deduce_t<T, N * K>>;
      return R([&](auto i) -> bool {
               return x[i / K][i % K];
             });
    }

  // const_where_expression<M, T>
  template <typename M, typename V>
    class const_where_expression
    {
      static_assert(std::is_same_v<V, detail::remove_cvref_t<V>>);

      struct Wrapper { using value_type = V; };

    protected:
      using value_type =
        typename std::conditional_t<std::is_arithmetic_v<V>, Wrapper, V>::value_type;

      friend const M&
      get_mask(const const_where_expression& x)
      { return x.m_k; }

      friend const V&
      get_lvalue(const const_where_expression& x)
      { return x.m_value; }

      const M& m_k;
      V& m_value;

    public:
      const_where_expression(const const_where_expression&) = delete;
      const_where_expression& operator=(const const_where_expression&) = delete;

      constexpr const_where_expression(const M& kk, const V& dd)
      : m_k(kk), m_value(const_cast<V&>(dd)) {}

      constexpr V
      operator-() const &&
      {
        return V([&](auto i) {
                 return m_k[i] ? static_cast<value_type>(-m_value[i]) : m_value[i];
               });
      }

      template <typename Up, typename Flags>
        [[nodiscard]] constexpr V
        copy_from(const detail::LoadStorePtr<Up, value_type>* mem, Flags) const &&
        {
          return V([&](auto i) {
                   return m_k[i] ? static_cast<value_type>(mem[i]) : m_value[i];
                 });
        }

      template <typename Up, typename Flags>
        constexpr void
        copy_to(detail::LoadStorePtr<Up, value_type>* mem, Flags) const &&
        {
          for (size_t i = 0; i < V::size(); ++i)
            {
              if (m_k[i])
                mem[i] = static_cast<Up>(m_value[i]);
            }
        }
    };

  // const_where_expression<bool, T>
  template <typename V>
    class const_where_expression<bool, V>
    {
      using M = bool;

      static_assert(std::is_same_v<V, detail::remove_cvref_t<V>>);

      struct Wrapper { using value_type = V; };

    protected:
      using value_type =
        typename std::conditional_t<std::is_arithmetic_v<V>, Wrapper, V>::value_type;

      friend const M&
      get_mask(const const_where_expression& x)
      { return x.m_k; }

      friend const V&
      get_lvalue(const const_where_expression& x)
      { return x.m_value; }

      const bool m_k;
      V& m_value;

    public:
      const_where_expression(const const_where_expression&) = delete;
      const_where_expression& operator=(const const_where_expression&) = delete;

      constexpr const_where_expression(const bool kk, const V& dd)
      : m_k(kk), m_value(const_cast<V&>(dd)) {}

      constexpr V
      operator-() const &&
      { return m_k ? -m_value : m_value; }

      template <typename Up, typename Flags>
        [[nodiscard]] constexpr V
        copy_from(const detail::LoadStorePtr<Up, value_type>* mem, Flags) const &&
        { return m_k ? static_cast<V>(mem[0]) : m_value; }

      template <typename Up, typename Flags>
        constexpr void
        copy_to(detail::LoadStorePtr<Up, value_type>* mem, Flags) const &&
        {
          if (m_k)
            mem[0] = m_value;
        }
    };

  // where_expression<M, T>
  template <typename M, typename V>
    class where_expression : public const_where_expression<M, V>
    {
      static_assert(not std::is_const_v<V>,
                    "where_expression may only be instantiated with a non-const V parameter");

      using typename const_where_expression<M, V>::value_type;
      using const_where_expression<M, V>::m_k;
      using const_where_expression<M, V>::m_value;

      static_assert(std::is_same_v<typename M::abi_type, typename V::abi_type>);
      static_assert(M::size() == V::size());

      friend V&
      get_lvalue(where_expression& x)
      { return x.m_value; }

      template <typename Up>
        constexpr auto
        as_simd(Up&& x)
        {
          using UU = detail::remove_cvref_t<Up>;
          if constexpr (std::is_same_v<V, UU>)
            return x;
          else if constexpr (std::is_convertible_v<Up&&, value_type>)
            return V(static_cast<value_type>(static_cast<Up&&>(x)));
          else if constexpr (std::is_convertible_v<Up&&, V>)
            return static_cast<V>(static_cast<Up&&>(x));
          else
            return static_simd_cast<V>(static_cast<Up&&>(x));
        }

    public:
      where_expression(const where_expression&) = delete;
      where_expression& operator=(const where_expression&) = delete;

      constexpr where_expression(const M& kk, V& dd)
      : const_where_expression<M, V>(kk, dd)
      {}

      template <typename Up>
        constexpr void
        operator=(Up&& x) &&
        {
          const V& rhs = as_simd(x);
          for (size_t i = 0; i < V::size(); ++i)
            {
              if (m_k[i])
                m_value[i] = rhs[i];
            }
        }

#define SIMD_OP_(op)                              \
      template <typename Up>                      \
        constexpr void                            \
        operator op##=(Up&& x) &&                 \
        {                                         \
          const V& rhs = as_simd(x);              \
          for (size_t i = 0; i < V::size(); ++i)  \
            {                                     \
              if (m_k[i])                         \
                m_value[i] op##= rhs[i];          \
            }                                     \
        }                                         \
      static_assert(true)
      SIMD_OP_(+);
      SIMD_OP_(-);
      SIMD_OP_(*);
      SIMD_OP_(/);
      SIMD_OP_(%);
      SIMD_OP_(&);
      SIMD_OP_(|);
      SIMD_OP_(^);
      SIMD_OP_(<<);
      SIMD_OP_(>>);
#undef SIMD_OP_

      constexpr void operator++() &&
      {
        for (size_t i = 0; i < V::size(); ++i)
          {
            if (m_k[i])
              ++m_value[i];
          }
      }

      constexpr void operator++(int) &&
      {
        for (size_t i = 0; i < V::size(); ++i)
          {
            if (m_k[i])
              ++m_value[i];
          }
      }

      constexpr void operator--() &&
      {
        for (size_t i = 0; i < V::size(); ++i)
          {
            if (m_k[i])
              --m_value[i];
          }
      }

      constexpr void operator--(int) &&
      {
        for (size_t i = 0; i < V::size(); ++i)
          {
            if (m_k[i])
              --m_value[i];
          }
      }

      // intentionally hides const_where_expression::copy_from
      template <typename Up, typename Flags>
        constexpr void
        copy_from(const detail::LoadStorePtr<Up, value_type>* mem, Flags) &&
        {
          for (size_t i = 0; i < V::size(); ++i)
            {
              if (m_k[i])
                m_value[i] = mem[i];
            }
        }
    };

  // where_expression<bool, T>
  template <typename V>
    class where_expression<bool, V> : public const_where_expression<bool, V>
    {
      using M = bool;
      using typename const_where_expression<M, V>::value_type;
      using const_where_expression<M, V>::m_k;
      using const_where_expression<M, V>::m_value;

    public:
      where_expression(const where_expression&) = delete;
      where_expression& operator=(const where_expression&) = delete;

      constexpr where_expression(const M& kk, V& dd)
      : const_where_expression<M, V>(kk, dd) {}

#define SIMD_OP_(op)                                \
      template <typename Up>                        \
        constexpr void operator op(Up&& x) &&       \
        { if (m_k) m_value op static_cast<Up&&>(x); }

      SIMD_OP_(=)
      SIMD_OP_(+=)
      SIMD_OP_(-=)
      SIMD_OP_(*=)
      SIMD_OP_(/=)
      SIMD_OP_(%=)
      SIMD_OP_(&=)
      SIMD_OP_(|=)
      SIMD_OP_(^=)
      SIMD_OP_(<<=)
      SIMD_OP_(>>=)
#undef SIMD_OP_

      constexpr void operator++() &&
      { if (m_k) ++m_value; }

      constexpr void operator++(int) &&
      { if (m_k) ++m_value; }

      constexpr void operator--() &&
      { if (m_k) --m_value; }

      constexpr void operator--(int) &&
      { if (m_k) --m_value; }

      // intentionally hides const_where_expression::copy_from
      template <typename Up, typename Flags>
        constexpr void
        copy_from(const detail::LoadStorePtr<Up, value_type>* mem, Flags) &&
        { if (m_k) m_value = mem[0]; }
    };

  // where
  template <typename Tp, typename Ap>
    constexpr where_expression<simd_mask<Tp, Ap>, simd<Tp, Ap>>
    where(const typename simd<Tp, Ap>::mask_type& k, simd<Tp, Ap>& value)
    { return {k, value}; }

  template <typename Tp, typename Ap>
    constexpr const_where_expression<simd_mask<Tp, Ap>, simd<Tp, Ap>>
    where(const typename simd<Tp, Ap>::mask_type& k,
          const simd<Tp, Ap>& value)
    { return {k, value}; }

  template <typename Tp, typename Ap>
    constexpr where_expression<simd_mask<Tp, Ap>, simd_mask<Tp, Ap>>
    where(const std::remove_const_t<simd_mask<Tp, Ap>>& k,
          simd_mask<Tp, Ap>& value)
    { return {k, value}; }

  template <typename Tp, typename Ap>
    constexpr const_where_expression<simd_mask<Tp, Ap>, simd_mask<Tp, Ap>>
    where(const std::remove_const_t<simd_mask<Tp, Ap>>& k,
          const simd_mask<Tp, Ap>& value)
    { return {k, value}; }

  template <typename Tp>
    constexpr where_expression<bool, Tp>
    where(detail::ExactBool k, Tp& value)
    { return {k, value}; }

  template <typename Tp>
    constexpr const_where_expression<bool, Tp>
    where(detail::ExactBool k, const Tp& value)
    { return {k, value}; }

  template <typename Tp, typename Ap>
    constexpr void
    where(bool k, simd<Tp, Ap>& value) = delete;

  template <typename Tp, typename Ap>
    constexpr void
    where(bool k, const simd<Tp, Ap>& value) = delete;

  // reductions [simd.reductions]
  template <typename T, typename A, typename BinaryOperation = std::plus<>>
    constexpr T
    reduce(const simd<T, A>& v,
           BinaryOperation binary_op = BinaryOperation())
    {
      constexpr int N = simd_size_v<T, A>;
      if constexpr (N > 3)
        {
          constexpr int N2 = detail::bit_floor(N / 2);
          constexpr int NRem = N - 2 * N2;
          if constexpr (NRem > 0)
            {
              const auto [l, r, rem] = split<N2, N2, N - 2 * N2>(v);
              return binary_op(reduce(binary_op(l, r), binary_op), reduce(rem, binary_op));
            }
          else
            {
              const auto [l, r] = split<N2, N2>(v);
              return reduce(binary_op(l, r), binary_op);
            }
        }
      else
        {
          T r = v[0];
          for (size_t i = 1; i < simd_size_v<T, A>; ++i)
            r = binary_op(r, v[i]);
          return r;
        }
    }

  template <typename M, typename V, typename BinaryOperation = std::plus<>>
    typename V::value_type
    reduce(const const_where_expression<M, V>& x,
        typename V::value_type identity_element,
        BinaryOperation binary_op)
    {
      const M& k = get_mask(x);
      const V& v = get_lvalue(x);
      auto r = identity_element;
      if (any_of(k)) [[likely]]
        {
          for (size_t i = 0; i < V::size(); ++i)
            if (k[i])
              r = binary_op(r, v[i]);
        }
      return r;
    }

  template <typename M, typename V>
    typename V::value_type
    reduce(const const_where_expression<M, V>& x, std::plus<> binary_op = {})
    { return reduce(x, 0, binary_op); }

  template <typename M, typename V>
    typename V::value_type
    reduce(const const_where_expression<M, V>& x, std::multiplies<> binary_op)
    { return reduce(x, 1, binary_op); }

  template <typename M, typename V>
    typename V::value_type
    reduce(const const_where_expression<M, V>& x, std::bit_and<> binary_op)
    { return reduce(x, ~typename V::value_type(), binary_op); }

  template <typename M, typename V>
    typename V::value_type
    reduce(const const_where_expression<M, V>& x, std::bit_or<> binary_op)
    { return reduce(x, 0, binary_op); }

  template <typename M, typename V>
    typename V::value_type
    reduce(const const_where_expression<M, V>& x, std::bit_xor<> binary_op)
    { return reduce(x, 0, binary_op); }

  template <typename T, typename A>
    constexpr T
    hmin(const simd<T, A>& v) noexcept
    {
      return reduce(v, [](const auto& l, const auto& r) {
               using std::min;
               return min(l, r);
             });
    }

  template <typename T, typename A>
    constexpr T
    hmax(const simd<T, A>& v) noexcept
    {
      return reduce(v, [](const auto& l, const auto& r) {
               using std::max;
               return max(l, r);
             });
    }

  template <typename M, typename V>
    constexpr typename V::value_type
    hmin(const const_where_expression<M, V>& x) noexcept
    {
      using T = typename V::value_type;
      constexpr T id_elem =
#ifdef __FINITE_MATH_ONLY__
        std::numeric_limits<T>::max();
#else
        std::numeric_limits<T>::infinity();
#endif
      return reduce(x, id_elem, [](const auto& l, const auto& r) {
               using std::min;
               return min(l, r);
             });
    }

  template <typename M, typename V>
    constexpr
    typename V::value_type
    hmax(const const_where_expression<M, V>& x) noexcept
    {
      using T = typename V::value_type;
      constexpr T id_elem =
#ifdef __FINITE_MATH_ONLY__
        std::numeric_limits<T>::lowest();
#else
        -std::numeric_limits<T>::infinity();
#endif
      return reduce(x, id_elem, [](const auto& l, const auto& r) {
               using std::max;
               return max(l, r);
             });
    }

  // algorithms [simd.alg]
  template <typename T, typename A>
    constexpr simd<T, A>
    min(const simd<T, A>& a, const simd<T, A>& b)
    { return simd<T, A>([&](auto i) { return std::min(a[i], b[i]); }); }

  template <typename T, typename A>
    constexpr simd<T, A>
    max(const simd<T, A>& a, const simd<T, A>& b)
    { return simd<T, A>([&](auto i) { return std::max(a[i], b[i]); }); }

  template <typename T, typename A>
    constexpr
    std::pair<simd<T, A>, simd<T, A>>
    minmax(const simd<T, A>& a, const simd<T, A>& b)
    { return {min(a, b), max(a, b)}; }

  template <typename T, typename A>
    constexpr simd<T, A>
    clamp(const simd<T, A>& v, const simd<T, A>& lo,
        const simd<T, A>& hi)
    { return simd<T, A>([&](auto i) { return std::clamp(v[i], lo[i], hi[i]); }); }

  // math
#define SIMD_MATH_1ARG(name, return_temp)                                                          \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const simd<detail::FloatingPoint<T>, A>& x) noexcept                                      \
    { return return_temp<T, A>([&x](auto i) { return std::name(x[i]); }); }

#define SIMD_MATH_1ARG_FIXED(name, R)                                                              \
  template <typename T, typename A>                                                                \
    constexpr fixed_size_simd<R, simd_size_v<T, A>>                                                \
    name(const simd<detail::FloatingPoint<T>, A>& x) noexcept                                      \
    { return fixed_size_simd<R, simd_size_v<T, A>>([&x](auto i) { return std::name(x[i]); }); }

#define SIMD_MATH_2ARG(name, return_temp)                                                          \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const simd<detail::FloatingPoint<T>, A>& x, const simd<T, A>& y) noexcept                 \
    { return return_temp<T, A>([&](auto i) { return std::name(x[i], y[i]); }); }                   \
                                                                                                   \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const simd<detail::FloatingPoint<T>, A>& x,                                               \
         const detail::type_identity_t<simd<T, A>>& y) noexcept                                    \
    { return return_temp<T, A>([&](auto i) { return std::name(x[i], y[i]); }); }                   \
                                                                                                   \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const detail::type_identity_t<simd<T, A>>& x,                                             \
         const simd<detail::FloatingPoint<T>, A>& y) noexcept                                      \
    { return return_temp<T, A>([&](auto i) { return std::name(x[i], y[i]); }); }

#define SIMD_MATH_3ARG(name, return_temp)                                                          \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const simd<detail::FloatingPoint<T>, A>& x,                                               \
         const simd<T, A>& y, const simd<T, A> &z) noexcept                                        \
    { return return_temp<T, A>([&](auto i) { return std::name(x[i], y[i], z[i]); }); }             \
                                                                                                   \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const simd<detail::FloatingPoint<T>, A>& x,                                               \
         const detail::type_identity_t<simd<T, A>>& y,                                             \
         const detail::type_identity_t<simd<T, A>> &z) noexcept                                    \
    { return return_temp<T, A>([&](auto i) { return std::name(x[i], y[i], z[i]); }); }             \
                                                                                                   \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const detail::type_identity_t<simd<T, A>>& x,                                             \
         const simd<detail::FloatingPoint<T>, A>& y,                                               \
         const detail::type_identity_t<simd<T, A>> &z) noexcept                                    \
    { return return_temp<T, A>([&](auto i) { return std::name(x[i], y[i], z[i]); }); }             \
                                                                                                   \
  template <typename T, typename A>                                                                \
    constexpr return_temp<T, A>                                                                    \
    name(const detail::type_identity_t<simd<T, A>>& x,                                             \
         const detail::type_identity_t<simd<T, A>>& y,                                             \
         const simd<detail::FloatingPoint<T>, A> &z) noexcept                                      \
    { return return_temp<T, A>([&](auto i) { return std::name(x[i], y[i], z[i]); }); }

  template <typename T, typename A, typename U = detail::SignedIntegral<T>>
    constexpr simd<T, A>
    abs(const simd<T, A>& x) noexcept
    { return simd<T, A>([&x](auto i) { return std::abs(x[i]); }); }

  SIMD_MATH_1ARG(abs, simd)
  SIMD_MATH_1ARG(isnan, simd_mask)
  SIMD_MATH_1ARG(isfinite, simd_mask)
  SIMD_MATH_1ARG(isinf, simd_mask)
  SIMD_MATH_1ARG(isnormal, simd_mask)
  SIMD_MATH_1ARG(signbit, simd_mask)
  SIMD_MATH_1ARG_FIXED(fpclassify, int)

  SIMD_MATH_2ARG(hypot, simd)
  SIMD_MATH_3ARG(hypot, simd)

  template <typename T, typename A>
    constexpr simd<T, A>
    remquo(const simd<T, A>& x, const simd<T, A>& y,
           fixed_size_simd<int, simd_size_v<T, A>>* quo) noexcept
    { return simd<T, A>([&x, &y, quo](auto i) { return std::remquo(x[i], y[i], &(*quo)[i]); }); }

  SIMD_MATH_1ARG(erf, simd)
  SIMD_MATH_1ARG(erfc, simd)
  SIMD_MATH_1ARG(tgamma, simd)
  SIMD_MATH_1ARG(lgamma, simd)

  SIMD_MATH_2ARG(pow, simd)
  SIMD_MATH_2ARG(fmod, simd)
  SIMD_MATH_2ARG(remainder, simd)
  SIMD_MATH_2ARG(nextafter, simd)
  SIMD_MATH_2ARG(copysign, simd)
  SIMD_MATH_2ARG(fdim, simd)
  SIMD_MATH_2ARG(fmax, simd)
  SIMD_MATH_2ARG(fmin, simd)
  SIMD_MATH_2ARG(isgreater, simd_mask)
  SIMD_MATH_2ARG(isgreaterequal, simd_mask)
  SIMD_MATH_2ARG(isless, simd_mask)
  SIMD_MATH_2ARG(islessequal, simd_mask)
  SIMD_MATH_2ARG(islessgreater, simd_mask)
  SIMD_MATH_2ARG(isunordered, simd_mask)

  template <typename T, typename A>
    constexpr simd<T, A>
    modf(const simd<detail::FloatingPoint<T>, A>& x, simd<T, A>* iptr) noexcept
    { return simd<T, A>([&x, iptr](auto i) { return std::modf(x[i], &(*iptr)[i]); }); }

  template <typename T, typename A>
    constexpr simd<T, A>
    frexp(const simd<detail::FloatingPoint<T>, A>& x,
          fixed_size_simd<int, simd_size_v<T, A>>* exp) noexcept
    { return simd<T, A>([&x, exp](auto i) { return std::frexp(x[i], &(*exp)[i]); }); }

  template <typename T, typename A>
    constexpr simd<T, A>
    scalbln(const simd<detail::FloatingPoint<T>, A>& x,
            const fixed_size_simd<long int, simd_size_v<T, A>>& exp) noexcept
    { return simd<T, A>([&x, &exp](auto i) { return std::scalbln(x[i], exp[i]); }); }

  template <typename T, typename A>
    constexpr simd<T, A>
    scalbn(const simd<detail::FloatingPoint<T>, A>& x,
           const fixed_size_simd<int, simd_size_v<T, A>>& exp) noexcept
    { return simd<T, A>([&x, &exp](auto i) { return std::scalbn(x[i], exp[i]); }); }

  template <typename T, typename A>
    constexpr simd<T, A>
    ldexp(const simd<detail::FloatingPoint<T>, A>& x,
          const fixed_size_simd<int, simd_size_v<T, A>>& exp) noexcept
    { return simd<T, A>([&x, &exp](auto i) { return std::ldexp(x[i], exp[i]); }); }

  SIMD_MATH_1ARG(sqrt, simd)

  SIMD_MATH_3ARG(fma, simd)

  SIMD_MATH_1ARG(trunc, simd)
  SIMD_MATH_1ARG(ceil, simd)
  SIMD_MATH_1ARG(floor, simd)
  SIMD_MATH_1ARG(round, simd)
  SIMD_MATH_1ARG_FIXED(lround, long)
  SIMD_MATH_1ARG_FIXED(llround, long long)
  SIMD_MATH_1ARG(nearbyint, simd)
  SIMD_MATH_1ARG(rint, simd)
  SIMD_MATH_1ARG_FIXED(lrint, long)
  SIMD_MATH_1ARG_FIXED(llrint, long long)
  SIMD_MATH_1ARG_FIXED(ilogb, int)

  // trig functions
  SIMD_MATH_1ARG(sin, simd)
  SIMD_MATH_1ARG(cos, simd)
  SIMD_MATH_1ARG(tan, simd)
  SIMD_MATH_1ARG(asin, simd)
  SIMD_MATH_1ARG(acos, simd)
  SIMD_MATH_1ARG(atan, simd)
  SIMD_MATH_2ARG(atan2, simd)
  SIMD_MATH_1ARG(sinh, simd)
  SIMD_MATH_1ARG(cosh, simd)
  SIMD_MATH_1ARG(tanh, simd)
  SIMD_MATH_1ARG(asinh, simd)
  SIMD_MATH_1ARG(acosh, simd)
  SIMD_MATH_1ARG(atanh, simd)

  // logarithms
  SIMD_MATH_1ARG(log, simd)
  SIMD_MATH_1ARG(log10, simd)
  SIMD_MATH_1ARG(log1p, simd)
  SIMD_MATH_1ARG(log2, simd)
  SIMD_MATH_1ARG(logb, simd)

#undef SIMD_MATH_1ARG
#undef SIMD_MATH_1ARG_FIXED
#undef SIMD_MATH_2ARG
#undef SIMD_MATH_3ARG
}
#ifdef VIR_SIMD_TS_DROPIN
}

namespace vir::stdx
{
  using namespace std::experimental::parallelism_v2;
}
#endif

#endif
#endif  // VIR_SIMD_H_


// #include "typelist.hpp"


#ifndef DISABLE_SIMD
#define DISABLE_SIMD 0
#endif

namespace gr {

using Size_t = std::uint32_t; // strict type definition in view of cross-platform/cross-compiler/cross-network portability similar to 'std::size_t' (N.B. which is not portable)

namespace meta {

struct null_type {};

template<typename... Ts>
struct print_types;

template<typename CharT, std::size_t SIZE>
struct fixed_string {
    constexpr static std::size_t N              = SIZE;
    CharT                        _data[N + 1UZ] = {};

    constexpr fixed_string() = default;

    constexpr explicit(false) fixed_string(const CharT (&str)[N + 1]) noexcept {
        if constexpr (N != 0)
            for (std::size_t i = 0; i < N; ++i) _data[i] = str[i];
    }

    [[nodiscard]] constexpr std::size_t
    size() const noexcept {
        return N;
    }

    [[nodiscard]] constexpr bool
    empty() const noexcept {
        return N == 0;
    }

    [[nodiscard]] constexpr explicit(false) operator std::string_view() const noexcept { return { _data, N }; }

    [[nodiscard]] explicit
    operator std::string() const noexcept {
        return { _data, N };
    }

    [[nodiscard]] explicit
    operator const char *() const noexcept {
        return _data;
    }

    [[nodiscard]] constexpr bool
    operator==(const fixed_string &other) const noexcept {
        return std::string_view{ _data, N } == std::string_view(other);
    }

    template<std::size_t N2>
    [[nodiscard]] friend constexpr bool
    operator==(const fixed_string &, const fixed_string<CharT, N2> &) {
        return false;
    }

    constexpr auto
    operator<=>(const fixed_string &other) const noexcept
            = default;

    friend constexpr auto
    operator<=>(const fixed_string &fs, std::string_view sv) noexcept {
        return std::string_view(fs) <=> sv;
    }

    friend constexpr auto
    operator<=>(const fixed_string &fs, const std::string &str) noexcept {
        return std::string(fs) <=> str;
    }
};

template<typename CharT, std::size_t N>
fixed_string(const CharT (&str)[N]) -> fixed_string<CharT, N - 1>;

template<typename T>
struct is_fixed_string : std::false_type {};

template<typename CharT, std::size_t N>
struct is_fixed_string<gr::meta::fixed_string<CharT, N>> : std::true_type {};

template<typename T>
concept FixedString = is_fixed_string<T>::value;

template<typename CharT, std::size_t N1, std::size_t N2>
constexpr fixed_string<CharT, N1 + N2>
operator+(const fixed_string<CharT, N1> &lhs, const fixed_string<CharT, N2> &rhs) noexcept {
    meta::fixed_string<CharT, N1 + N2> result{};
    for (std::size_t i = 0; i < N1; ++i) {
        result._data[i] = lhs._data[i];
    }
    for (std::size_t i = 0; i < N2; ++i) {
        result._data[N1 + i] = rhs._data[i];
    }
    result._data[N1 + N2] = '\0';
    return result;
}

namespace detail {
constexpr int
log10(int n) noexcept {
    if (n < 10) return 0;
    return 1 + log10(n / 10);
}

constexpr int
pow10(int n) noexcept {
    if (n == 0) return 1;
    return 10 * pow10(n - 1);
}

template<int N, std::size_t... Idx>
constexpr fixed_string<char, sizeof...(Idx)>
make_fixed_string_impl(std::index_sequence<Idx...>) {
    constexpr auto numDigits = sizeof...(Idx);
    return { { ('0' + (N / pow10(numDigits - Idx - 1) % 10))..., 0 } };
}
} // namespace detail

template<int N>
constexpr auto
make_fixed_string() noexcept {
    if constexpr (N == 0) {
        return fixed_string{ "0" };
    } else {
        constexpr std::size_t digits = 1U + static_cast<std::size_t>(detail::log10(N));
        return detail::make_fixed_string_impl<N>(std::make_index_sequence<digits>());
    }
}

static_assert(fixed_string("0") == make_fixed_string<0>());
static_assert(fixed_string("1") == make_fixed_string<1>());
static_assert(fixed_string("2") == make_fixed_string<2>());
static_assert(fixed_string("123") == make_fixed_string<123>());
static_assert((fixed_string("out") + make_fixed_string<123>()) == fixed_string("out123"));

template<typename T>
[[nodiscard]] std::string
type_name() noexcept {
    std::string type_name = typeid(T).name();
    int         status;
    char       *demangled_name = abi::__cxa_demangle(type_name.c_str(), nullptr, nullptr, &status);
    if (status == 0) {
        std::string ret(demangled_name);
        free(demangled_name);
        return ret;
    } else {
        free(demangled_name);
        return typeid(T).name();
    }
}

template<fixed_string val>
struct message_type {};

template<class... T>
constexpr bool always_false = false;

constexpr std::size_t invalid_index              = -1UZ;
constexpr std::size_t default_message_port_index = -2UZ;

#if HAVE_SOURCE_LOCATION
[[gnu::always_inline]] inline void
precondition(bool cond, const std::source_location loc = std::source_location::current()) {
    struct handle {
        [[noreturn]] static void
        failure(std::source_location const &loc) {
            std::clog << "failed precondition in " << loc.file_name() << ':' << loc.line() << ':' << loc.column() << ": `" << loc.function_name() << "`\n";
            __builtin_trap();
        }
    };

    if (not cond) [[unlikely]]
        handle::failure(loc);
}
#else
[[gnu::always_inline]] inline void
precondition(bool cond) {
    struct handle {
        [[noreturn]] static void
        failure() {
            std::clog << "failed precondition\n";
            __builtin_trap();
        }
    };

    if (not cond) [[unlikely]]
        handle::failure();
}
#endif

/**
 * T is tuple-like if it implements std::tuple_size, std::tuple_element, and std::get.
 * Tuples with size 0 are excluded.
 */
template<typename T>
concept tuple_like = (std::tuple_size<T>::value > 0) && requires(T tup) {
    { std::get<0>(tup) } -> std::same_as<typename std::tuple_element_t<0, T> &>;
};

template<template<typename...> class Template, typename Class>
struct is_instantiation : std::false_type {};

template<template<typename...> class Template, typename... Args>
struct is_instantiation<Template, Template<Args...>> : std::true_type {};
template<typename Class, template<typename...> class Template>
concept is_instantiation_of = is_instantiation<Template, Class>::value;

template<typename T>
concept map_type = is_instantiation_of<T, std::map> || is_instantiation_of<T, std::unordered_map>;

template<typename T>
concept vector_type = is_instantiation_of<std::remove_cv_t<T>, std::vector>;

template<typename T>
struct is_std_array_type : std::false_type {};

template<typename T, std::size_t N>
struct is_std_array_type<std::array<T, N>> : std::true_type {};

template<typename T>
concept array_type = is_std_array_type<std::remove_cv_t<T>>::value;

template<typename T, typename V = void>
concept array_or_vector_type = (vector_type<T> || array_type<T>) &&(std::same_as<V, void> || std::same_as<typename T::value_type, V>);

namespace stdx = vir::stdx;

template<typename V, typename T = void>
concept any_simd = stdx::is_simd_v<V> && (std::same_as<T, void> || std::same_as<T, typename V::value_type>);

template<typename V, typename T>
concept t_or_simd = std::same_as<V, T> || any_simd<V, T>;

template<typename T>
concept vectorizable_v = std::constructible_from<stdx::simd<T>>;

template<typename T>
using vectorizable = std::integral_constant<bool, vectorizable_v<T>>;

template<typename T>
concept complex_like = std::is_same_v<T, std::complex<float>> || std::is_same_v<T, std::complex<double>>;

/**
 * Determines the SIMD width of the given structure. This can either be a stdx::simd object or a
 * tuple-like of stdx::simd (recursively). The latter requires that the SIMD width is homogeneous.
 * If T is not a simd (or tuple thereof), value is 0.
 */
template<typename T>
struct simdize_size : std::integral_constant<std::size_t, 0> {};

template<typename T, typename A>
struct simdize_size<stdx::simd<T, A>> : stdx::simd_size<T, A> {};

template<tuple_like Tup>
struct simdize_size<Tup> : simdize_size<std::tuple_element_t<0, Tup>> {
    static_assert([]<std::size_t... Is>(std::index_sequence<Is...>) {
        return ((simdize_size<std::tuple_element_t<0, Tup>>::value == simdize_size<std::tuple_element_t<Is, Tup>>::value) && ...);
    }(std::make_index_sequence<std::tuple_size_v<Tup>>()));
};

template<typename T>
inline constexpr std::size_t simdize_size_v = simdize_size<T>::value;

namespace detail {
/**
 * Shortcut to determine the stdx::simd specialization with the most efficient ABI tag for the
 * requested element type T and width N.
 */
template<typename T, std::size_t N>
using deduced_simd = stdx::simd<T, stdx::simd_abi::deduce_t<T, N>>;

template<typename T, std::size_t N>
struct simdize_impl {
    using type = T;
};

template<vectorizable_v T, std::size_t N>
    requires requires { typename stdx::native_simd<T>; }
struct simdize_impl<T, N> {
    using type = deduced_simd<T, N == 0 ? stdx::native_simd<T>::size() : N>;
};

template<std::size_t N>
struct simdize_impl<std::tuple<>, N> {
    using type = std::tuple<>;
};

template<tuple_like Tup, std::size_t N>
    requires requires { typename simdize_impl<std::tuple_element_t<0, Tup>, N>::type; }
struct simdize_impl<Tup, N> {
    static inline constexpr std::size_t size
            = N > 0 ? N
                    : []<std::size_t... Is>(std::index_sequence<Is...>) constexpr { return std::max({ simdize_size_v<typename simdize_impl<std::tuple_element_t<Is, Tup>, 0>::type>... }); }

                      (std::make_index_sequence<std::tuple_size_v<Tup>>());

    using type = decltype([]<std::size_t... Is>(std::index_sequence<Is...>) -> std::tuple<typename simdize_impl<std::tuple_element_t<Is, Tup>, size>::type...> {
        return {};
    }(std::make_index_sequence<std::tuple_size_v<Tup>>()));
};
} // namespace detail

/**
 * Meta-function that turns a vectorizable type or a tuple-like (recursively) of vectorizable types
 * into a stdx::simd or std::tuple (recursively) of stdx::simd. If N is non-zero, N determines the
 * resulting SIMD width. Otherwise, of all vectorizable types U the maximum
 * stdx::native_simd<U>::size() determines the resulting SIMD width.
 * If T is neither vectorizable nor a std::tuple with at least one member, simdize produces T.
 */
template<typename T, std::size_t N = 0>
using simdize = typename detail::simdize_impl<T, N>::type;

static_assert(std::same_as<simdize<std::tuple<std::tuple<int, double>, short, std::tuple<float>>>,
                           std::tuple<std::tuple<detail::deduced_simd<int, stdx::native_simd<short>::size()>, detail::deduced_simd<double, stdx::native_simd<short>::size()>>, stdx::native_simd<short>,
                                      std::tuple<detail::deduced_simd<float, stdx::native_simd<short>::size()>>>>);

template<fixed_string Name, typename PortList>
consteval std::size_t
indexForName() {
    auto helper = []<std::size_t... Ids>(std::index_sequence<Ids...>) {
        auto static_name_for_index = []<std::size_t Id> {
            using Port = typename PortList::template at<Id>;
            if constexpr (requires(Port port) {
                              { port.static_name() };
                          }) {
                return Port::Name;
            } else {
                return Port::value_type::Name;
            }
        };

        constexpr int n_matches = ((static_name_for_index.template operator()<Ids>() == Name) + ...);
        static_assert(n_matches <= 1, "Multiple ports with that name were found. The name must be unique. You can "
                                      "still use a port index instead.");
        static_assert(n_matches == 1, "No port with the given name exists.");
        std::size_t result = meta::invalid_index;
        ((static_name_for_index.template operator()<Ids>() == Name ? (result = Ids) : 0), ...);
        return result;
    };
    return helper(std::make_index_sequence<PortList::size>());
}

// template<template<typename...> typename Type, typename... Items>
// using find_type = decltype(std::tuple_cat(std::declval<std::conditional_t<is_instantiation_of<Items, Type>, std::tuple<Items>, std::tuple<>>>()...));

template<template<typename> typename Pred, typename... Items>
struct find_type;

template<template<typename> typename Pred>
struct find_type<Pred> {
    using type = std::tuple<>;
};

template<template<typename> typename Pred, typename First, typename... Rest>
struct find_type<Pred, First, Rest...> {
    using type = decltype(std::tuple_cat(std::conditional_t<Pred<First>::value, std::tuple<First>, std::tuple<>>(), typename find_type<Pred, Rest...>::type()));
};

template<template<typename> typename Pred, typename... Items>
using find_type_t = typename find_type<Pred, Items...>::type;

template<typename Tuple, typename Default = void>
struct get_first_or_default;

template<typename First, typename... Rest, typename Default>
struct get_first_or_default<std::tuple<First, Rest...>, Default> {
    using type = First;
};

template<typename Default>
struct get_first_or_default<std::tuple<>, Default> {
    using type = Default;
};

template<typename Tuple, typename Default = void>
using get_first_or_default_t = typename get_first_or_default<Tuple, Default>::type;

template<typename... Lambdas>
struct overloaded : Lambdas... {
    using Lambdas::operator()...;
};

template<typename... Lambdas>
overloaded(Lambdas...) -> overloaded<Lambdas...>;

namespace detail {
template<template<typename...> typename Mapper, template<typename...> typename Wrapper, typename... Args>
Wrapper<Mapper<Args>...> *
type_transform_impl(Wrapper<Args...> *);

template<template<typename...> typename Mapper, typename T>
Mapper<T> *
type_transform_impl(T *);

template<template<typename...> typename Mapper>
void *
type_transform_impl(void *);
} // namespace detail

template<template<typename...> typename Mapper, typename T>
using type_transform = std::remove_pointer_t<decltype(detail::type_transform_impl<Mapper>(static_cast<T *>(nullptr)))>;

template<typename Arg, typename... Args>
auto
safe_min(Arg &&arg, Args &&...args) {
    if constexpr (sizeof...(Args) == 0) {
        return arg;
    } else {
        return std::min(std::forward<Arg>(arg), std::forward<Args>(args)...);
    }
}

template<typename Arg, typename... Args>
auto
safe_pair_min(Arg &&arg, Args &&...args) {
    if constexpr (sizeof...(Args) == 0) {
        return arg;
    } else {
        return std::make_pair(std::min(std::forward<Arg>(arg).first, std::forward<Args>(args).first...), std::min(std::forward<Arg>(arg).second, std::forward<Args>(args).second...));
    }
}

template<typename Function, typename Tuple, typename... Tuples>
auto
tuple_for_each(Function &&function, Tuple &&tuple, Tuples &&...tuples) {
    static_assert(((std::tuple_size_v<std::remove_cvref_t<Tuple>> == std::tuple_size_v<std::remove_cvref_t<Tuples>>) &&...));
    return [&]<std::size_t... Idx>(std::index_sequence<Idx...>) {
        (([&function, &tuple, &tuples...](auto I) { function(std::get<I>(tuple), std::get<I>(tuples)...); }(std::integral_constant<std::size_t, Idx>{}), ...));
    }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<Tuple>>>());
}

template<typename Function, typename Tuple, typename... Tuples>
void
tuple_for_each_enumerate(Function &&function, Tuple &&tuple, Tuples &&...tuples) {
    static_assert(((std::tuple_size_v<std::remove_cvref_t<Tuple>> == std::tuple_size_v<std::remove_cvref_t<Tuples>>) &&...));
    [&]<std::size_t... Idx>(std::index_sequence<Idx...>) {
        ([&function](auto I, auto &&t0, auto &&...ts) { function(I, std::get<I>(t0), std::get<I>(ts)...); }(std::integral_constant<std::size_t, Idx>{}, tuple, tuples...), ...);
    }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<Tuple>>>());
}

template<typename Function, typename Tuple, typename... Tuples>
auto
tuple_transform(Function &&function, Tuple &&tuple, Tuples &&...tuples) {
    static_assert(((std::tuple_size_v<std::remove_cvref_t<Tuple>> == std::tuple_size_v<std::remove_cvref_t<Tuples>>) &&...));
    return [&]<std::size_t... Idx>(std::index_sequence<Idx...>) {
        return std::make_tuple([&function, &tuple, &tuples...](auto I) { return function(std::get<I>(tuple), std::get<I>(tuples)...); }(std::integral_constant<std::size_t, Idx>{})...);
    }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<Tuple>>>());
}

template<typename Function, typename Tuple, typename... Tuples>
auto
tuple_transform_enumerated(Function &&function, Tuple &&tuple, Tuples &&...tuples) {
    static_assert(((std::tuple_size_v<std::remove_cvref_t<Tuple>> == std::tuple_size_v<std::remove_cvref_t<Tuples>>) &&...));
    return [&]<std::size_t... Idx>(std::index_sequence<Idx...>) {
        return std::make_tuple([&function, &tuple, &tuples...](auto I) { return function(I, std::get<I>(tuple), std::get<I>(tuples)...); }(std::integral_constant<std::size_t, Idx>{})...);
    }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<Tuple>>>());
}

static_assert(std::is_same_v<std::vector<int>, type_transform<std::vector, int>>);
static_assert(std::is_same_v<std::tuple<std::vector<int>, std::vector<float>>, type_transform<std::vector, std::tuple<int, float>>>);
static_assert(std::is_same_v<void, type_transform<std::vector, void>>);

#ifdef __cpp_lib_hardware_interference_size
static inline constexpr const std::size_t kCacheLine = std::hardware_destructive_interference_size;
#else
static inline constexpr const std::size_t kCacheLine = 64;
#endif

namespace detail {

template<typename T>
concept HasValueType = requires { typename T::value_type; };

template<typename T, typename = void>
struct fundamental_base_value_type {
    using type = T;
};

template<HasValueType T>
struct fundamental_base_value_type<T> {
    using type = typename fundamental_base_value_type<typename T::value_type>::type;
};

} // namespace detail

template<typename T>
using fundamental_base_value_type_t = typename detail::fundamental_base_value_type<T>::type;

static_assert(std::is_same_v<fundamental_base_value_type_t<int>, int>);
static_assert(std::is_same_v<fundamental_base_value_type_t<std::vector<float>>, float>);
static_assert(std::is_same_v<fundamental_base_value_type_t<std::vector<std::complex<double>>>, double>);

template<typename T>
concept string_like = std::is_same_v<T, std::string> || std::is_same_v<T, std::string_view> || std::is_convertible_v<T, std::string_view>;

namespace detail {
template<typename T>
struct is_const_member_function : std::false_type {};

template<typename T, typename U, typename... args>
struct is_const_member_function<U (T::*)(args...) const> : std::true_type {};
} // namespace detail

template<typename T>
inline constexpr bool
is_const_member_function(T) noexcept {
    return std::is_member_function_pointer_v<T> && detail::is_const_member_function<T>::value;
}

} // namespace meta
} // namespace gr

#endif // include guard


// #include <gnuradio-4.0/BlockTraits.hpp>
#ifndef GNURADIO_NODE_NODE_TRAITS_HPP
#define GNURADIO_NODE_NODE_TRAITS_HPP

// #include <gnuradio-4.0/meta/utils.hpp>


// #include "Port.hpp"
#ifndef GNURADIO_PORT_HPP
#define GNURADIO_PORT_HPP

#include <any>
#include <complex>
#include <set>
#include <span>
#include <variant>

// #include <gnuradio-4.0/meta/utils.hpp>


// #include "annotated.hpp"
#ifndef GNURADIO_ANNOTATED_HPP
#define GNURADIO_ANNOTATED_HPP

#include <string_view>
#include <type_traits>
#include <utility>

#include <fmt/format.h>

// #include <gnuradio-4.0/meta/utils.hpp>


namespace gr {

/**
 * @brief a template wrapping structure, which holds a static documentation (e.g. mark down) string as its value.
 * It's used as a trait class to annotate other template classes (e.g. blocks or fields).
 */
template<gr::meta::fixed_string doc_string>
struct Doc {
    static constexpr gr::meta::fixed_string value = doc_string;
};

using EmptyDoc = Doc<"">; // nomen-est-omen

template<typename T>
struct is_doc : std::false_type {};

template<gr::meta::fixed_string N>
struct is_doc<Doc<N>> : std::true_type {};

template<typename T>
concept Documentation = is_doc<T>::value;

/**
 * @brief Unit is a template structure, which holds a static physical-unit (i.e. SI unit) string as its value.
 * It's used as a trait class to annotate other template classes (e.g. blocks or fields).
 */
template<gr::meta::fixed_string doc_string>
struct Unit {
    static constexpr gr::meta::fixed_string value = doc_string;
};

using EmptyUnit = Unit<"">; // nomen-est-omen

template<typename T>
struct is_unit : std::false_type {};

template<gr::meta::fixed_string N>
struct is_unit<Unit<N>> : std::true_type {};

template<typename T>
concept UnitType = is_unit<T>::value;

static_assert(Documentation<EmptyDoc>);
static_assert(UnitType<EmptyUnit>);
static_assert(!UnitType<EmptyDoc>);
static_assert(!Documentation<EmptyUnit>);

/**
 * @brief Annotates field etc. that the entity is visible from a UI perspective.
 */
struct Visible {};

/**
 * @brief Annotates block, indicating to calling schedulers that it may block due IO.
 */
template<bool UseIoThread = true>
struct BlockingIO {
    [[maybe_unused]] constexpr static bool useIoThread = UseIoThread;
};

/**
 * @brief Annotates block, indicating to perform resampling based on the provided ratio.
 *
 * The ratio between numerator and denominator defines the number of samples to be interpolated or decimated.
 * - If the ratio is greater than 1, interpolation occurs.
 * - If the ratio is less than 1, decimation occurs.
 * - If the ratio is 1, no effect on the sampling rate.
 *
 * @tparam numerator Top number in the input-to-output sample ratio.
 * @tparam denominator Bottom number in the input-to-output sample ratio.
 * @tparam isConst Specifies if the resampling ratio is constant or can be modified during run-time.
 */
template<gr::Size_t numerator = 1U, gr::Size_t denominator = 1U, bool isConst = false>
struct ResamplingRatio {
    static_assert(numerator > 0, "Numerator in ResamplingRatio must be >= 0");
    static constexpr gr::Size_t kNumerator   = numerator;
    static constexpr gr::Size_t kDenominator = denominator;
    static constexpr bool       kIsConst     = isConst;
    static constexpr bool       kEnabled     = !isConst || (kNumerator != 1LU) || (kDenominator != 1LU);
};

template<typename T>
concept IsResamplingRatio = requires {
    T::kNumerator;
    T::kDenominator;
    T::kIsConst;
    T::kEnabled;
} && std::is_base_of_v<ResamplingRatio<T::kNumerator, T::kDenominator, T::kIsConst>, T>;

template<typename T>
using is_resampling_ratio = std::bool_constant<IsResamplingRatio<T>>;

static_assert(is_resampling_ratio<ResamplingRatio<1, 1024>>::value);
static_assert(!is_resampling_ratio<int>::value);

/**
 * @brief Annotates block, indicating the stride control for data processing.
 *
 * Stride determines the number of samples between consecutive data processing events:
 * - If stride is less than N, it indicates overlap.
 * - If stride is greater than N, it indicates skipped samples.
 * - If stride is equal to 0, it indicates back-to-back processing without skipping.
 *
 * @tparam stride The number of samples between data processing events.
 * @tparam isConst Specifies if the stride is constant or can be modified during run-time.
 */
template<std::uint64_t stride = 0U, bool isConst = false>
struct Stride {
    static_assert(stride >= 0U, "Stride must be >= 0");

    static constexpr gr::Size_t kStride  = stride;
    static constexpr bool       kIsConst = isConst;
    static constexpr bool       kEnabled = !isConst || (stride > 0U);
};

template<typename T>
concept IsStride = requires {
    T::kStride;
    T::kIsConst;
    T::kEnabled;
} && std::is_base_of_v<Stride<T::kStride, T::kIsConst>, T>;

template<typename T>
using is_stride = std::bool_constant<IsStride<T>>;

static_assert(is_stride<Stride<10, true>>::value);
static_assert(!is_stride<int>::value);

enum class IncompleteFinalUpdateEnum { DROP, PULL_FORWARD, PUSH_BACKWARD };

template<IncompleteFinalUpdateEnum updatePolicy>
struct IncompleteFinalUpdatePolicy {
    static constexpr IncompleteFinalUpdateEnum kIncompleteFinalUpdatePolicy = updatePolicy;
};
template<typename T>
concept IsIncompleteFinalUpdatePolicy = requires {
    T::kIncompleteFinalUpdatePolicy;
} && std::is_base_of_v<IncompleteFinalUpdatePolicy<T::kIncompleteFinalUpdatePolicy>, T>;

template<typename T>
using is_incompleteFinalUpdatePolicy = std::bool_constant<IsIncompleteFinalUpdatePolicy<T>>;

static_assert(is_incompleteFinalUpdatePolicy<IncompleteFinalUpdatePolicy<IncompleteFinalUpdateEnum::DROP>>::value);

enum class UICategory { None, Toolbar, ChartPane, StatusBar, Menu };

/**
 * @brief Annotates block, indicating that it is drawable and provides a  mandatory `void draw()` method.
 *
 * @tparam category_ ui category where it
 * @tparam toolkit_ specifies the applicable UI toolkit (e.g. 'console', 'ImGui', 'Qt', etc.)
 */
template<UICategory category_, gr::meta::fixed_string toolkit_ = "">
struct Drawable {
    static constexpr UICategory             kCategorgy = category_;
    static constexpr gr::meta::fixed_string kToolkit   = toolkit_;
};

template<typename T>
concept IsDrawable = requires {
    T::kCategorgy;
    T::kToolkit;
} && std::is_base_of_v<Drawable<T::kCategorgy, T::kToolkit>, T>;

template<typename T>
using is_drawable = std::bool_constant<IsDrawable<T>>;

using NotDrawable = Drawable<UICategory::None, "">; // nomen-est-omen
static_assert(is_drawable<NotDrawable>::value);
static_assert(is_drawable<Drawable<UICategory::ChartPane, "console">>::value);
static_assert(!is_drawable<int>::value);

/**
 * @brief Annotates templated block, indicating which port data types are supported.
 */
template<typename... Ts>
struct SupportedTypes {};

template<typename T>
struct is_supported_types : std::false_type {};

template<typename... Ts>
struct is_supported_types<SupportedTypes<Ts...>> : std::true_type {};

using DefaultSupportedTypes = SupportedTypes<>;

static_assert(gr::meta::is_instantiation_of<DefaultSupportedTypes, SupportedTypes>);
static_assert(gr::meta::is_instantiation_of<SupportedTypes<float, double>, SupportedTypes>);

/**
 * @brief Represents limits and optional validation for an Annotated<..> type.
 *
 * The `Limits` structure defines lower and upper bounds for a value of type `T`.
 * Additionally, it allows for an optional custom validation function to be provided.
 * This function should take a value of type `T` and return a `bool`, indicating
 * whether the value passes the custom validation or not.
 *
 * Example:
 * ```
 * Annotated<float, "example float", Visible, Limits<0.f, 1024.f>>             exampleVar1;
 * // or:
 * constexpr auto isPowerOfTwo = [](const int &val) { return val > 0 && (val & (val - 1)) == 0; };
 * Annotated<float, "example float", Visible, Limits<0.f, 1024.f, isPowerOfTwo>> exampleVar2;
 * // or:
 * Annotated<float, "example float", Visible, Limits<0.f, 1024.f, [](const int &val) { return val > 0 && (val & (val - 1)) == 0; }>> exampleVar2;
 * ```
 */
template<auto LowerLimit, decltype(LowerLimit) UpperLimit, auto Validator = nullptr>
    requires(requires(decltype(Validator) f, decltype(LowerLimit) v) {
        { f(v) } -> std::same_as<bool>;
    } || Validator == nullptr)
struct Limits {
    using ValueType                                    = decltype(LowerLimit);
    static constexpr ValueType           MinRange      = LowerLimit;
    static constexpr ValueType           MaxRange      = UpperLimit;
    static constexpr decltype(Validator) ValidatorFunc = Validator;

    static constexpr bool
    validate(const ValueType &value) noexcept {
        if constexpr (LowerLimit == UpperLimit) { // ignore range checks
            if constexpr (Validator != nullptr) {
                try {
                    return Validator(value);
                } catch (...) {
                    return false;
                }
            } else {
                return true; // if no validator and limits are same, return true by default
            }
        }
        if constexpr (Validator != nullptr) {
            try {
                return value >= LowerLimit && value <= UpperLimit && Validator(value);
            } catch (...) {
                return false;
            }
        } else {
            return value >= LowerLimit && value <= UpperLimit;
        }
        return true;
    }
};

template<typename T>
struct is_limits : std::false_type {};

template<auto LowerLimit, decltype(LowerLimit) UpperLimit, auto Validator>
struct is_limits<Limits<LowerLimit, UpperLimit, Validator>> : std::true_type {};

template<typename T>
concept Limit = is_limits<T>::value;

using EmptyLimit = Limits<0, 0>; // nomen-est-omen

static_assert(Limit<EmptyLimit>);

/**
 * @brief Annotated is a template class that acts as a transparent wrapper around another type.
 * It allows adding additional meta-information to a type, such as documentation, unit, and visibility.
 * The meta-information is supplied as template parameters.
 */
template<typename T, gr::meta::fixed_string description_ = "", typename... Arguments>
struct Annotated {
    using value_type = T;
    using LimitType  = typename gr::meta::typelist<Arguments...>::template find_or_default<is_limits, EmptyLimit>;
    T value;

    Annotated() = default;

    template<typename U>
        requires std::constructible_from<T, U> && (!std::same_as<std::remove_cvref_t<U>, Annotated>)
    explicit(false) Annotated(U &&input) noexcept(std::is_nothrow_constructible_v<T, U>) : value(static_cast<T>(std::forward<U>(input))) {}

    template<typename U>
        requires std::assignable_from<T &, U>
    Annotated &
    operator=(U &&input) noexcept(std::is_nothrow_assignable_v<T, U>) {
        value = static_cast<T>(std::forward<U>(input));
        return *this;
    }

    inline explicit(false) constexpr
    operator T &() noexcept {
        return value;
    }

    inline explicit(false) constexpr
    operator const T &() const noexcept {
        return value;
    }

    constexpr bool
    operator==(const Annotated &other) const noexcept {
        return value == other.value;
    }

    template<typename U>
    constexpr bool
    operator==(const U &other) const noexcept {
        if constexpr (requires { other.value; }) {
            return value == other.value;
        } else {
            return value == other;
        }
    }

    template<typename U>
        requires std::is_same_v<std::remove_cvref_t<U>, T>
    [[nodiscard]] constexpr bool
    validate_and_set(U &&value_) {
        if constexpr (std::is_same_v<LimitType, EmptyLimit>) {
            value = std::forward<U>(value_);
            return true;
        } else {
            if (LimitType::validate(static_cast<typename LimitType::ValueType>(value_))) { // N.B. implicit casting needed until clang supports floats as NTTPs
                value = std::forward<U>(value_);
                return true;
            } else {
                return false;
            }
        }
    }

    operator std::string_view() const noexcept
        requires std::is_same_v<T, std::string>
    {
        return std::string_view(value); // Convert from std::string to std::string_view
    }

    // meta-information
    inline static constexpr std::string_view
    description() noexcept {
        return std::string_view{ description_ };
    }

    inline static constexpr std::string_view
    documentation() noexcept {
        using Documentation = typename gr::meta::typelist<Arguments...>::template find_or_default<is_doc, EmptyDoc>;
        return std::string_view{ Documentation::value };
    }

    inline static constexpr std::string_view
    unit() noexcept {
        using PhysicalUnit = typename gr::meta::typelist<Arguments...>::template find_or_default<is_unit, EmptyUnit>;
        return std::string_view{ PhysicalUnit::value };
    }

    inline static constexpr bool
    visible() noexcept {
        return gr::meta::typelist<Arguments...>::template contains<Visible>;
    }
};

template<typename T>
struct is_annotated : std::false_type {};

template<typename T, gr::meta::fixed_string str, typename... Args>
struct is_annotated<gr::Annotated<T, str, Args...>> : std::true_type {};

template<typename T>
concept AnnotatedType = is_annotated<T>::value;

template<typename T>
struct unwrap_if_wrapped {
    using type = T;
};

template<typename U, gr::meta::fixed_string str, typename... Args>
struct unwrap_if_wrapped<gr::Annotated<U, str, Args...>> {
    using type = U;
};

/**
 * @brief A type trait class that extracts the underlying type `T` from an `Annotated` instance.
 * If the given type is not an `Annotated`, it returns the type itself.
 */
template<typename T>
using unwrap_if_wrapped_t = typename unwrap_if_wrapped<T>::type;

} // namespace gr

template<typename... Ts>
struct gr::meta::typelist<gr::SupportedTypes<Ts...>> : gr::meta::typelist<Ts...> {};

template<typename T, gr::meta::fixed_string description, typename... Arguments>
struct fmt::formatter<gr::Annotated<T, description, Arguments...>> {
    using Type = std::remove_const_t<T>;
    fmt::formatter<Type> value_formatter;

    template<typename FormatContext>
    constexpr auto
    parse(FormatContext &ctx) {
        return value_formatter.parse(ctx);
    }

    template<typename FormatContext>
    constexpr auto
    format(const gr::Annotated<T, description, Arguments...> &annotated, FormatContext &ctx) {
        // TODO: add switch for printing only brief and/or meta-information
        return value_formatter.format(annotated.value, ctx);
    }
};

namespace gr {
template<typename T, gr::meta::fixed_string description, typename... Arguments>
inline std::ostream &
operator<<(std::ostream &os, const gr::Annotated<T, description, Arguments...> &v) {
    // TODO: add switch for printing only brief and/or meta-information
    return os << fmt::format("{}", v.value);
}
} // namespace gr

#endif // GNURADIO_ANNOTATED_HPP

// #include "CircularBuffer.hpp"
#ifndef GNURADIO_CIRCULARBUFFER_HPP
#define GNURADIO_CIRCULARBUFFER_HPP

#if defined(_LIBCPP_VERSION) and _LIBCPP_VERSION < 16000
#include <experimental/memory_resource>

namespace std::pmr {
using memory_resource = std::experimental::pmr::memory_resource;
template<typename T>
using polymorphic_allocator = std::experimental::pmr::polymorphic_allocator<T>;
} // namespace std::pmr
#else
#include <memory_resource>
#endif
#include <algorithm>
#include <atomic>
#include <bit>
#include <cassert> // to assert if compiled for debugging
#include <functional>
#include <numeric>
#include <ranges>
#include <span>
#include <stdexcept>
#include <system_error>

#include <fmt/format.h>

// header for creating/opening or POSIX shared memory objects
#include <cerrno>
#include <fcntl.h>
#if defined __has_include && not __EMSCRIPTEN__
#if __has_include(<sys/mman.h>) && __has_include(<sys/stat.h>) && __has_include(<unistd.h>)
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifdef __NR_memfd_create
namespace gr {
static constexpr bool has_posix_mmap_interface = true;
}

#define HAS_POSIX_MAP_INTERFACE
#else
namespace gr {
static constexpr bool has_posix_mmap_interface = false;
}
#endif
#else // #if defined __has_include -- required for portability
namespace gr {
static constexpr bool has_posix_mmap_interface = false;
}
#endif

// #include "Buffer.hpp"
#ifndef GNURADIO_BUFFER2_H
#define GNURADIO_BUFFER2_H

#include <bit>
#include <concepts>
#include <cstdint>
#include <span>
#include <type_traits>

namespace gr {
namespace util {
template<typename T, typename...>
struct first_template_arg_helper;

template<template<typename...> class TemplateType, typename ValueType, typename... OtherTypes>
struct first_template_arg_helper<TemplateType<ValueType, OtherTypes...>> {
    using value_type = ValueType;
};

template<typename T>
constexpr auto *
value_type_helper() {
    if constexpr (requires { typename T::value_type; }) {
        return static_cast<typename T::value_type *>(nullptr);
    } else {
        return static_cast<typename first_template_arg_helper<T>::value_type *>(nullptr);
    }
}

template<typename T>
using value_type_t = std::remove_pointer_t<decltype(value_type_helper<T>())>;

template<typename... A>
struct test_fallback {};

template<typename, typename ValueType>
struct test_value_type {
    using value_type = ValueType;
};

static_assert(std::is_same_v<int, value_type_t<test_fallback<int, float, double>>>);
static_assert(std::is_same_v<float, value_type_t<test_value_type<int, float>>>);
static_assert(std::is_same_v<int, value_type_t<std::span<int>>>);
static_assert(std::is_same_v<double, value_type_t<std::array<double, 42>>>);

} // namespace util

// TODO: find a better place for these 3 concepts
template<typename From, typename To>
concept convertible_from_lvalue_to = std::convertible_to<const std::remove_cvref_t<From> &, To>;

template<typename From, typename To>
concept convertible_from_rvalue_to = std::convertible_to<std::remove_cvref_t<From> &&, To>;

template<typename From, typename To>
concept convertible_from_lvalue_only = convertible_from_lvalue_to<From, To> && !convertible_from_rvalue_to<From, To>;

template<typename T>
concept SpanLike = std::convertible_to<T, std::span<std::remove_cvref_t<typename T::value_type>>>;

template<typename T>
concept ConstSpanLike = std::convertible_to<T, std::span<const std::remove_cvref_t<typename T::value_type>>>;

template<typename T>
concept ConstSpanLvalueLike = convertible_from_lvalue_only<T, std::span<const std::remove_cvref_t<typename T::value_type>>>;

template<typename T>
concept ConsumableSpan = std::ranges::contiguous_range<T> && ConstSpanLvalueLike<T> && requires(T &s) { s.consume(0); };

template<typename T>
concept PublishableSpan = std::ranges::contiguous_range<T> && std::ranges::output_range<T, std::remove_cvref_t<typename T::value_type>> && SpanLike<T> && requires(T &s) { s.publish(0UZ); };

// clang-format off
// disable formatting until clang-format (v16) supporting concepts
template<class T>
concept BufferReader = requires(T /*const*/ t, const std::size_t n_items) {
    { t.get(n_items) } ; // TODO: get() returns CircularBuffer::buffer_reader::ConsumableInputRange
    { t.position() }       -> std::same_as<std::make_signed_t<std::size_t>>;
    { t.available() }      -> std::same_as<std::size_t>;
    { t.buffer() };
};

template<class Fn, typename T, typename ...Args>
concept WriterCallback = std::is_invocable_v<Fn, std::span<T>&, std::make_signed_t<std::size_t>, Args...> || std::is_invocable_v<Fn, std::span<T>&, Args...>;

template<class T, typename ...Args>
concept BufferWriter = requires(T t, const std::size_t n_items, std::pair<std::size_t, std::make_signed_t<std::size_t>> token, Args ...args) {
    { t.publish([](std::span<util::value_type_t<T>> &/*writable_data*/, Args ...) { /* */ }, n_items, args...) }                                 -> std::same_as<void>;
    { t.publish([](std::span<util::value_type_t<T>> &/*writable_data*/, std::make_signed_t<std::size_t> /* writePos */, Args ...) { /* */  }, n_items, args...) }   -> std::same_as<void>;
    { t.try_publish([](std::span<util::value_type_t<T>> &/*writable_data*/, Args ...) { /* */ }, n_items, args...) }                             -> std::same_as<bool>;
    { t.try_publish([](std::span<util::value_type_t<T>> &/*writable_data*/, std::make_signed_t<std::size_t> /* writePos */, Args ...) { /* */  }, n_items, args...) }-> std::same_as<bool>;
    { t.reserve(n_items) };// TODO: reserve() returns CircularBuffer::buffer_writer::PublishableOutputRange
    { t.available() }         -> std::same_as<std::size_t>;
    { t.buffer() };
};

template<class T, typename ...Args>
concept Buffer = requires(T t, const std::size_t min_size, Args ...args) {
    { T(min_size, args...) };
    { t.size() }       -> std::same_as<std::size_t>;
    { t.new_reader() } -> BufferReader;
    { t.new_writer() } -> BufferWriter;
};

// compile-time unit-tests
namespace test {
template <typename T>
struct non_compliant_class {
};
template <typename T, typename... Args>
using WithSequenceParameter = decltype([](std::span<T>&, std::make_signed_t<std::size_t>, Args...) { /* */ });
template <typename T, typename... Args>
using NoSequenceParameter = decltype([](std::span<T>&, Args...) { /* */ });
} // namespace test

static_assert(!Buffer<test::non_compliant_class<int>>);
static_assert(!BufferReader<test::non_compliant_class<int>>);
static_assert(!BufferWriter<test::non_compliant_class<int>>);

static_assert(WriterCallback<test::WithSequenceParameter<int>, int>);
static_assert(!WriterCallback<test::WithSequenceParameter<int>, int, std::span<bool>>);
static_assert(WriterCallback<test::WithSequenceParameter<int, std::span<bool>>, int, std::span<bool>>);
static_assert(WriterCallback<test::NoSequenceParameter<int>, int>);
static_assert(!WriterCallback<test::NoSequenceParameter<int>, int, std::span<bool>>);
static_assert(WriterCallback<test::NoSequenceParameter<int, std::span<bool>>, int, std::span<bool>>);
// clang-format on
} // namespace gr

#endif // GNURADIO_BUFFER2_H

// #include "ClaimStrategy.hpp"
#ifndef GNURADIO_CLAIMSTRATEGY_HPP
#define GNURADIO_CLAIMSTRATEGY_HPP

#include <cassert>
#include <concepts>
#include <cstdint>
#include <memory>
#include <span>
#include <stdexcept>
#include <vector>

// #include <gnuradio-4.0/meta/utils.hpp>


// #include "Sequence.hpp"
#ifndef GNURADIO_SEQUENCE_HPP
#define GNURADIO_SEQUENCE_HPP

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <limits>
#include <memory>
#include <ranges>
#include <vector>

#include <fmt/format.h>

namespace gr {

#ifndef forceinline
// use this for hot-spots only <-> may bloat code size, not fit into cache and
// consequently slow down execution
#define forceinline inline __attribute__((always_inline))
#endif

#ifdef __cpp_lib_hardware_interference_size
using std::hardware_constructive_interference_size;
using std::hardware_destructive_interference_size;
#else
inline constexpr std::size_t hardware_destructive_interference_size  = 64;
inline constexpr std::size_t hardware_constructive_interference_size = 64;
#endif
static constexpr const std::make_signed_t<std::size_t> kInitialCursorValue = -1L;

/**
 * Concurrent sequence class used for tracking the progress of the ring buffer and event
 * processors. Support a number of concurrent operations including CAS and order writes.
 * Also attempts to be more efficient with regards to false sharing by adding padding
 * around the volatile field.
 */
class Sequence {
public:
    using signed_index_type = std::make_signed_t<std::size_t>;

private:
    alignas(hardware_destructive_interference_size) std::atomic<signed_index_type> _fieldsValue{};

public:
    Sequence(const Sequence &)  = delete;
    Sequence(const Sequence &&) = delete;
    void
    operator=(const Sequence &)
            = delete;

    explicit Sequence(signed_index_type initialValue = kInitialCursorValue) noexcept : _fieldsValue(initialValue) {}

    [[nodiscard]] forceinline signed_index_type
    value() const noexcept {
        return std::atomic_load_explicit(&_fieldsValue, std::memory_order_acquire);
    }

    forceinline void
    setValue(const signed_index_type value) noexcept {
        std::atomic_store_explicit(&_fieldsValue, value, std::memory_order_release);
    }

    [[nodiscard]] forceinline bool
    compareAndSet(signed_index_type expectedSequence, signed_index_type nextSequence) noexcept {
        // atomically set the value to the given updated value if the current value == the
        // expected value (true, otherwise folse).
        return std::atomic_compare_exchange_strong(&_fieldsValue, &expectedSequence, nextSequence);
    }

    [[nodiscard]] forceinline signed_index_type
    incrementAndGet() noexcept {
        return std::atomic_fetch_add(&_fieldsValue, 1L) + 1L;
    }

    [[nodiscard]] forceinline signed_index_type
    addAndGet(signed_index_type value) noexcept {
        return std::atomic_fetch_add(&_fieldsValue, value) + value;
    }

    void
    wait(signed_index_type oldValue) const noexcept {
        atomic_wait_explicit(&_fieldsValue, oldValue, std::memory_order_acquire);
    }

    void
    notify_all() noexcept {
        _fieldsValue.notify_all();
    }
};

namespace detail {

using signed_index_type = Sequence::signed_index_type;

/**
 * Get the minimum sequence from an array of Sequences.
 *
 * \param sequences sequences to compare.
 * \param minimum an initial default minimum.  If the array is empty this value will
 * returned. \returns the minimum sequence found or lon.MaxValue if the array is empty.
 */
inline signed_index_type
getMinimumSequence(const std::vector<std::shared_ptr<Sequence>> &sequences, signed_index_type minimum = std::numeric_limits<signed_index_type>::max()) noexcept {
    // Note that calls to getMinimumSequence get rather expensive with sequences.size() because
    // each Sequence lives on its own cache line. Also, this is no reasonable loop for vectorization.
    for (const auto &s : sequences) {
        const signed_index_type v = s->value();
        if (v < minimum) {
            minimum = v;
        }
    }
    return minimum;
}

inline void
addSequences(std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> &sequences, const Sequence &cursor, const std::vector<std::shared_ptr<Sequence>> &sequencesToAdd) {
    signed_index_type                                       cursorSequence;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> updatedSequences;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> currentSequences;

    do {
        currentSequences = std::atomic_load_explicit(&sequences, std::memory_order_acquire);
        updatedSequences = std::make_shared<std::vector<std::shared_ptr<Sequence>>>(currentSequences->size() + sequencesToAdd.size());

#if not defined(_LIBCPP_VERSION)
        std::ranges::copy(currentSequences->begin(), currentSequences->end(), updatedSequences->begin());
#else
        std::copy(currentSequences->begin(), currentSequences->end(), updatedSequences->begin());
#endif

        cursorSequence = cursor.value();

        auto index     = currentSequences->size();
        for (auto &&sequence : sequencesToAdd) {
            sequence->setValue(cursorSequence);
            (*updatedSequences)[index] = sequence;
            index++;
        }
    } while (!std::atomic_compare_exchange_weak(&sequences, &currentSequences, updatedSequences)); // xTODO: explicit memory order

    cursorSequence = cursor.value();

    for (auto &&sequence : sequencesToAdd) {
        sequence->setValue(cursorSequence);
    }
}

inline bool
removeSequence(std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> &sequences, const std::shared_ptr<Sequence> &sequence) {
    std::uint32_t                                           numToRemove;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> oldSequences;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> newSequences;

    do {
        oldSequences = std::atomic_load_explicit(&sequences, std::memory_order_acquire);
#if not defined(_LIBCPP_VERSION)
        numToRemove = static_cast<std::uint32_t>(std::ranges::count(*oldSequences, sequence)); // specifically uses identity
#else
        numToRemove = static_cast<std::uint32_t>(std::count((*oldSequences).begin(), (*oldSequences).end(), sequence)); // specifically uses identity
#endif
        if (numToRemove == 0) {
            break;
        }

        auto oldSize = static_cast<std::uint32_t>(oldSequences->size());
        newSequences = std::make_shared<std::vector<std::shared_ptr<Sequence>>>(oldSize - numToRemove);

        for (auto i = 0U, pos = 0U; i < oldSize; ++i) {
            const auto &testSequence = (*oldSequences)[i];
            if (sequence != testSequence) {
                (*newSequences)[pos] = testSequence;
                pos++;
            }
        }
    } while (!std::atomic_compare_exchange_weak(&sequences, &oldSequences, newSequences));

    return numToRemove != 0;
}

} // namespace detail

} // namespace gr

#include <fmt/core.h>
#include <fmt/ostream.h>

template<>
struct fmt::formatter<gr::Sequence> {
    template<typename ParseContext>
    constexpr auto
    parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto
    format(gr::Sequence const &value, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", value.value());
    }
};

namespace gr {
inline std::ostream &
operator<<(std::ostream &os, const Sequence &v) {
    return os << fmt::format("{}", v.value());
}
} // namespace gr

#endif // GNURADIO_SEQUENCE_HPP

// #include "WaitStrategy.hpp"
#ifndef GNURADIO_WAITSTRATEGY_HPP
#define GNURADIO_WAITSTRATEGY_HPP

#include <condition_variable>
#include <atomic>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// #include "Sequence.hpp"


namespace gr {
// clang-format off
/**
 * Wait for the given sequence to be available.  It is possible for this method to return a value less than the sequence number supplied depending on the implementation of the WaitStrategy.
 * A common use for this is to signal a timeout.Any EventProcessor that is using a WaitStrategy to get notifications about message becoming available should remember to handle this case.
 * The BatchEventProcessor<T> explicitly handles this case and will signal a timeout if required.
 *
 * \param sequence sequence to be waited on.
 * \param cursor Ring buffer cursor on which to wait.
 * \param dependentSequence on which to wait.
 * \param barrier barrier the IEventProcessor is waiting on.
 * \returns the sequence that is available which may be greater than the requested sequence.
 */
template<typename T>
inline constexpr bool isWaitStrategy = requires(T /*const*/ t, const std::int64_t sequence, const Sequence &cursor, std::vector<std::shared_ptr<Sequence>> &dependentSequences) {
    { t.waitFor(sequence, cursor, dependentSequences) } -> std::same_as<std::int64_t>;
};
static_assert(!isWaitStrategy<int>);

/**
 * signal those waiting that the cursor has advanced.
 */
template<typename T>
inline constexpr bool hasSignalAllWhenBlocking = requires(T /*const*/ t) {
    { t.signalAllWhenBlocking() } -> std::same_as<void>;
};
static_assert(!hasSignalAllWhenBlocking<int>);

template<typename T>
concept WaitStrategy = isWaitStrategy<T>;



/**
 * Blocking strategy that uses a lock and condition variable for IEventProcessor's waiting on a barrier.
 * This strategy should be used when performance and low-latency are not as important as CPU resource.
 */
class BlockingWaitStrategy {
    std::recursive_mutex        _gate;
    std::condition_variable_any _conditionVariable;

public:
    std::int64_t waitFor(const std::int64_t sequence, const Sequence &cursor, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) {
        if (cursor.value() < sequence) {
            std::unique_lock uniqueLock(_gate);

            while (cursor.value() < sequence) {
                // optional: barrier check alert
                _conditionVariable.wait(uniqueLock);
            }
        }

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            // optional: barrier check alert
        }

        return availableSequence;
    }

    void signalAllWhenBlocking() {
        std::unique_lock uniqueLock(_gate);
        _conditionVariable.notify_all();
    }
};
static_assert(WaitStrategy<BlockingWaitStrategy>);

/**
 * Busy Spin strategy that uses a busy spin loop for IEventProcessor's waiting on a barrier.
 * This strategy will use CPU resource to avoid syscalls which can introduce latency jitter.
 * It is best used when threads can be bound to specific CPU cores.
 */
struct BusySpinWaitStrategy {
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) const {
        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            // optional: barrier check alert
        }
        return availableSequence;
    }
};
static_assert(WaitStrategy<BusySpinWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<BusySpinWaitStrategy>);

/**
 * Sleeping strategy that initially spins, then uses a std::this_thread::yield(), and eventually sleep. T
 * his strategy is a good compromise between performance and CPU resource.
 * Latency spikes can occur after quiet periods.
 */
class SleepingWaitStrategy {
    static const std::int32_t _defaultRetries = 200;
    std::int32_t              _retries        = 0;

public:
    explicit SleepingWaitStrategy(std::int32_t retries = _defaultRetries)
        : _retries(retries) {
    }

    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) const {
        auto       counter    = _retries;
        const auto waitMethod = [&counter]() {
            // optional: barrier check alert

            if (counter > 100) {
                --counter;
            } else if (counter > 0) {
                --counter;
                std::this_thread::yield();
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));
            }
        };

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            waitMethod();
        }

        return availableSequence;
    }
};
static_assert(WaitStrategy<SleepingWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<SleepingWaitStrategy>);

struct TimeoutException : public std::runtime_error {
    TimeoutException() : std::runtime_error("TimeoutException") {}
};

class TimeoutBlockingWaitStrategy {
    using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>;
    Clock::duration             _timeout;
    std::recursive_mutex        _gate;
    std::condition_variable_any _conditionVariable;

public:
    explicit TimeoutBlockingWaitStrategy(Clock::duration timeout)
        : _timeout(timeout) {}

    std::int64_t waitFor(const std::int64_t sequence, const Sequence &cursor, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) {
        auto timeSpan = std::chrono::duration_cast<std::chrono::microseconds>(_timeout);

        if (cursor.value() < sequence) {
            std::unique_lock uniqueLock(_gate);

            while (cursor.value() < sequence) {
                // optional: barrier check alert

                if (_conditionVariable.wait_for(uniqueLock, timeSpan) == std::cv_status::timeout) {
                    throw TimeoutException();
                }
            }
        }

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            // optional: barrier check alert
        }

        return availableSequence;
    }

    void signalAllWhenBlocking() {
        std::unique_lock uniqueLock(_gate);
        _conditionVariable.notify_all();
    }
};
static_assert(WaitStrategy<TimeoutBlockingWaitStrategy>);
static_assert(hasSignalAllWhenBlocking<TimeoutBlockingWaitStrategy>);

/**
 * Yielding strategy that uses a Thread.Yield() for IEventProcessors waiting on a barrier after an initially spinning.
 * This strategy is a good compromise between performance and CPU resource without incurring significant latency spikes.
 */
class YieldingWaitStrategy {
    const std::size_t _spinTries = 100;

public:
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) const {
        auto       counter    = _spinTries;
        const auto waitMethod = [&counter]() {
            // optional: barrier check alert

            if (counter == 0) {
                std::this_thread::yield();
            } else {
                --counter;
            }
        };

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            waitMethod();
        }

        return availableSequence;
    }
};
static_assert(WaitStrategy<YieldingWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<YieldingWaitStrategy>);

struct NoWaitStrategy {
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> & /*dependentSequences*/) const {
        // wait for nothing
        return sequence;
    }
};
static_assert(WaitStrategy<NoWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<NoWaitStrategy>);


/**
 *
 * SpinWait is meant to be used as a tool for waiting in situations where the thread is not allowed to block.
 *
 * In order to get the maximum performance, the implementation first spins for `YIELD_THRESHOLD` times, and then
 * alternates between yielding, spinning and putting the thread to sleep, to allow other threads to be scheduled
 * by the kernel to avoid potential CPU contention.
 *
 * The number of spins, yielding, and sleeping for either '0 ms' or '1 ms' is controlled by the NTTP constants
 * @tparam YIELD_THRESHOLD
 * @tparam SLEEP_0_EVERY_HOW_MANY_TIMES
 * @tparam SLEEP_1_EVERY_HOW_MANY_TIMES
 */
template<std::int32_t YIELD_THRESHOLD = 10, std::int32_t SLEEP_0_EVERY_HOW_MANY_TIMES = 5, std::int32_t SLEEP_1_EVERY_HOW_MANY_TIMES = 20>
class SpinWait {
    using Clock         = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>;
    std::int32_t _count = 0;
    static void  spinWaitInternal(std::int32_t iterationCount) noexcept {
        for (auto i = 0; i < iterationCount; i++) {
            yieldProcessor();
        }
    }
#ifndef __EMSCRIPTEN__
    static void yieldProcessor() noexcept { asm volatile("rep\nnop"); }
#else
    static void yieldProcessor() noexcept { std::this_thread::sleep_for(std::chrono::milliseconds(1)); }
#endif

public:
    SpinWait() = default;

    [[nodiscard]] std::int32_t count() const noexcept { return _count; }
    [[nodiscard]] bool         nextSpinWillYield() const noexcept { return _count > YIELD_THRESHOLD; }

    void                       spinOnce() {
        if (nextSpinWillYield()) {
            auto num = _count >= YIELD_THRESHOLD ? _count - 10 : _count;
            if (num % SLEEP_1_EVERY_HOW_MANY_TIMES == SLEEP_1_EVERY_HOW_MANY_TIMES - 1) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            } else {
                if (num % SLEEP_0_EVERY_HOW_MANY_TIMES == SLEEP_0_EVERY_HOW_MANY_TIMES - 1) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(0));
                } else {
                    std::this_thread::yield();
                }
            }
        } else {
            spinWaitInternal(4 << _count);
        }

        if (_count == std::numeric_limits<std::int32_t>::max()) {
            _count = YIELD_THRESHOLD;
        } else {
            ++_count;
        }
    }

    void reset() noexcept { _count = 0; }

    template<typename T>
    requires std::is_nothrow_invocable_r_v<bool, T>
    bool
    spinUntil(const T &condition) const { return spinUntil(condition, -1); }

    template<typename T>
    requires std::is_nothrow_invocable_r_v<bool, T>
    bool
    spinUntil(const T &condition, std::int64_t millisecondsTimeout) const {
        if (millisecondsTimeout < -1) {
            throw std::out_of_range("Timeout value is out of range");
        }

        std::int64_t num = 0;
        if (millisecondsTimeout != 0 && millisecondsTimeout != -1) {
            num = getTickCount();
        }

        SpinWait spinWait;
        while (!condition()) {
            if (millisecondsTimeout == 0) {
                return false;
            }

            spinWait.spinOnce();

            if (millisecondsTimeout != 1 && spinWait.nextSpinWillYield() && millisecondsTimeout <= (getTickCount() - num)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] static std::int64_t getTickCount() { return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now().time_since_epoch()).count(); }
};

/**
 * Spin strategy that uses a SpinWait for IEventProcessors waiting on a barrier.
 * This strategy is a good compromise between performance and CPU resource.
 * Latency spikes can occur after quiet periods.
 */
struct SpinWaitWaitStrategy {
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequence) const {
        std::int64_t availableSequence;

        SpinWait     spinWait;
        while ((availableSequence = detail::getMinimumSequence(dependentSequence)) < sequence) {
            // optional: barrier check alert
            spinWait.spinOnce();
        }

        return availableSequence;
    }
};
static_assert(WaitStrategy<SpinWaitWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<SpinWaitWaitStrategy>);

struct NO_SPIN_WAIT {};

template<typename SPIN_WAIT = NO_SPIN_WAIT>
class AtomicMutex {
    std::atomic_flag _lock{};
    SPIN_WAIT        _spin_wait;

public:
    AtomicMutex()                    = default;
    AtomicMutex(const AtomicMutex &) = delete;
    AtomicMutex &operator=(const AtomicMutex &) = delete;

    //
    void lock() {
        while (_lock.test_and_set(std::memory_order_acquire)) {
            if constexpr (requires { _spin_wait.spin_once(); }) {
                _spin_wait.spin_once();
            }
        }
        if constexpr (requires { _spin_wait.spin_once(); }) {
            _spin_wait.reset();
        }
    }
    void unlock() { _lock.clear(std::memory_order::release); }
};


// clang-format on
} // namespace gr


#endif // GNURADIO_WAITSTRATEGY_HPP


namespace gr {

struct NoCapacityException : public std::runtime_error {
    NoCapacityException() : std::runtime_error("NoCapacityException"){};
};

// clang-format off

template<typename T>
concept ClaimStrategy = requires(T /*const*/ t, const std::vector<std::shared_ptr<Sequence>> &dependents, const std::size_t requiredCapacity,
        const std::make_signed_t<std::size_t> cursorValue, const std::make_signed_t<std::size_t> sequence, const std::make_signed_t<std::size_t> offset, const std::make_signed_t<std::size_t> availableSequence, const std::size_t n_slots_to_claim) {
    { t.hasAvailableCapacity(dependents, requiredCapacity, cursorValue) } -> std::same_as<bool>;
    { t.next(dependents, n_slots_to_claim) } -> std::same_as<std::make_signed_t<std::size_t>>;
    { t.tryNext(dependents, n_slots_to_claim) } -> std::same_as<std::make_signed_t<std::size_t>>;
    { t.getRemainingCapacity(dependents) } -> std::same_as<std::make_signed_t<std::size_t>>;
    { t.publish(offset, n_slots_to_claim) } -> std::same_as<void>;
    { t.isAvailable(sequence) } -> std::same_as<bool>;
    { t.getHighestPublishedSequence(sequence, availableSequence) } -> std::same_as<std::make_signed_t<std::size_t>>;
};

namespace claim_strategy::util {
constexpr unsigned    floorlog2(std::size_t x) { return x == 1 ? 0 : 1 + floorlog2(x >> 1); }
constexpr unsigned    ceillog2(std::size_t x) { return x == 1 ? 0 : floorlog2(x - 1) + 1; }
}

template<std::size_t SIZE = std::dynamic_extent, WaitStrategy WAIT_STRATEGY = BusySpinWaitStrategy>
class alignas(hardware_constructive_interference_size) SingleThreadedStrategy {
    using signed_index_type = Sequence::signed_index_type;
    const std::size_t _size;
    Sequence &_cursor;
    WAIT_STRATEGY &_waitStrategy;
    signed_index_type _nextValue{ kInitialCursorValue }; // N.B. no need for atomics since this is called by a single publisher
    mutable signed_index_type _cachedValue{ kInitialCursorValue };

public:
    SingleThreadedStrategy(Sequence &cursor, WAIT_STRATEGY &waitStrategy, const std::size_t buffer_size = SIZE)
        : _size(buffer_size), _cursor(cursor), _waitStrategy(waitStrategy){};
    SingleThreadedStrategy(const SingleThreadedStrategy &)  = delete;
    SingleThreadedStrategy(const SingleThreadedStrategy &&) = delete;
    void operator=(const SingleThreadedStrategy &) = delete;

    bool hasAvailableCapacity(const std::vector<std::shared_ptr<Sequence>> &dependents, const std::size_t requiredCapacity, const signed_index_type/*cursorValue*/) const noexcept {
        if (const signed_index_type wrapPoint = (_nextValue + static_cast<signed_index_type>(requiredCapacity)) - static_cast<signed_index_type>(_size); wrapPoint > _cachedValue || _cachedValue > _nextValue) {
            auto minSequence = detail::getMinimumSequence(dependents, _nextValue);
            _cachedValue     = minSequence;
            if (wrapPoint > minSequence) {
                return false;
            }
        }
        return true;
    }

    signed_index_type next(const std::vector<std::shared_ptr<Sequence>> &dependents, const std::size_t n_slots_to_claim = 1) noexcept {
        assert((n_slots_to_claim > 0 && n_slots_to_claim <= _size) && "n_slots_to_claim must be > 0 and <= bufferSize");

        auto nextSequence = _nextValue + static_cast<signed_index_type>(n_slots_to_claim);
        auto wrapPoint    = nextSequence - static_cast<signed_index_type>(_size);

        if (const auto cachedGatingSequence = _cachedValue; wrapPoint > cachedGatingSequence || cachedGatingSequence > _nextValue) {
            SpinWait     spinWait;
            signed_index_type minSequence;
            while (wrapPoint > (minSequence = detail::getMinimumSequence(dependents, _nextValue))) {
                if constexpr (hasSignalAllWhenBlocking<WAIT_STRATEGY>) {
                    _waitStrategy.signalAllWhenBlocking();
                }
                spinWait.spinOnce();
            }
            _cachedValue = minSequence;
        }
        _nextValue = nextSequence;

        return nextSequence;
    }

    signed_index_type tryNext(const std::vector<std::shared_ptr<Sequence>> &dependents, const std::size_t n_slots_to_claim) {
        assert((n_slots_to_claim > 0) && "n_slots_to_claim must be > 0");

        if (!hasAvailableCapacity(dependents, n_slots_to_claim, 0 /* unused cursor value */)) {
            throw NoCapacityException();
        }

        const auto nextSequence = _nextValue + static_cast<signed_index_type>(n_slots_to_claim);
        _nextValue              = nextSequence;

        return nextSequence;
    }

    signed_index_type getRemainingCapacity(const std::vector<std::shared_ptr<Sequence>> &dependents) const noexcept {
        const auto consumed = detail::getMinimumSequence(dependents, _nextValue);
        const auto produced = _nextValue;

        return static_cast<signed_index_type>(_size) - (produced - consumed);
    }

    void publish(signed_index_type offset, std::size_t n_slots_to_claim) {
        const auto sequence = offset + static_cast<signed_index_type>(n_slots_to_claim);
        _cursor.setValue(sequence);
        _nextValue = sequence;
        if constexpr (hasSignalAllWhenBlocking<WAIT_STRATEGY>) {
            _waitStrategy.signalAllWhenBlocking();
        }
    }

    [[nodiscard]] forceinline bool isAvailable(signed_index_type sequence) const noexcept { return sequence <= _cursor.value(); }
    [[nodiscard]] signed_index_type getHighestPublishedSequence(signed_index_type /*nextSequence*/, signed_index_type availableSequence) const noexcept { return availableSequence; }
};

static_assert(ClaimStrategy<SingleThreadedStrategy<1024, NoWaitStrategy>>);

template <std::size_t Size>
struct MultiThreadedStrategySizeMembers
{
    static_assert(std::has_single_bit(Size));
    static constexpr std::int32_t _size = Size;
    static constexpr std::int32_t _indexShift = std::bit_width(Size - 1);
};

template <>
struct MultiThreadedStrategySizeMembers<std::dynamic_extent> {
    const std::int32_t _size;
    const std::int32_t _indexShift;

    #ifdef __clang__
    explicit MultiThreadedStrategySizeMembers(std::size_t size) : _size(static_cast<std::int32_t>(size)), _indexShift(static_cast<std::int32_t>(std::bit_width(size - 1))) {} //NOSONAR
    #else
    #pragma GCC diagnostic push // std::bit_width seems to be compiler and platform specific
    #ifndef __clang__
    #pragma GCC diagnostic ignored "-Wuseless-cast"
    #endif
    explicit MultiThreadedStrategySizeMembers(std::size_t size) : _size(static_cast<std::int32_t>(size)), _indexShift(static_cast<std::int32_t>(std::bit_width(size - 1))) {
        assert(std::has_single_bit(size));
    } //NOSONAR
    #pragma GCC diagnostic pop
    #endif
};

/**
 * Claim strategy for claiming sequences for access to a data structure while tracking dependent Sequences.
 * Suitable for use for sequencing across multiple publisher threads.
 * Note on cursor:  With this sequencer the cursor value is updated after the call to SequencerBase::next(),
 * to determine the highest available sequence that can be read, then getHighestPublishedSequence should be used.
 *
 * The size argument (compile-time and run-time) must be a power-of-2 value.
 */
template<std::size_t SIZE = std::dynamic_extent, WaitStrategy WAIT_STRATEGY = BusySpinWaitStrategy>
requires (SIZE == std::dynamic_extent or std::has_single_bit(SIZE))
class alignas(hardware_constructive_interference_size) MultiThreadedStrategy
: private MultiThreadedStrategySizeMembers<SIZE> {
    Sequence &_cursor;
    WAIT_STRATEGY &_waitStrategy;
#if (__cpp_lib_atomic_ref >= 201806L)
    std::vector<std::int32_t> _availableBuffer; // tracks the state of each ringbuffer slot
#else // clang's libc++ does not yet support std::atomic_ref
    std::unique_ptr<std::atomic<std::int32_t>[]> _availableBuffer; // tracks the state of each ringbuffer slot
#endif
    std::shared_ptr<Sequence> _gatingSequenceCache = std::make_shared<Sequence>();
    using MultiThreadedStrategySizeMembers<SIZE>::_size;
    using MultiThreadedStrategySizeMembers<SIZE>::_indexShift;
    using signed_index_type = Sequence::signed_index_type;

public:
    MultiThreadedStrategy() = delete;

    explicit
    MultiThreadedStrategy(Sequence &cursor, WAIT_STRATEGY &waitStrategy) requires (SIZE != std::dynamic_extent)
    : _cursor(cursor), _waitStrategy(waitStrategy) {
#if (__cpp_lib_atomic_ref >= 201806L)
        _availableBuffer = std::vector<std::int32_t>(SIZE, -1);
#else // clang's libc++ does not yet support std::atomic_ref
        _availableBuffer = std::make_unique<std::atomic<std::int32_t>[]>(SIZE);
        std::fill(_availableBuffer.get(), _availableBuffer.get() + SIZE, -1);
#endif
    }

    explicit
    MultiThreadedStrategy(Sequence &cursor, WAIT_STRATEGY &waitStrategy, std::size_t buffer_size)
    requires (SIZE == std::dynamic_extent)
    : MultiThreadedStrategySizeMembers<SIZE>(buffer_size),
      _cursor(cursor), _waitStrategy(waitStrategy) {
#if (__cpp_lib_atomic_ref >= 201806L)
        _availableBuffer = std::vector<std::int32_t>(buffer_size, -1);
#else // clang's libc++ does not yet support std::atomic_ref
        _availableBuffer = std::make_unique<std::atomic<std::int32_t>[]>(buffer_size);
        std::fill(_availableBuffer.get(), _availableBuffer.get() + buffer_size, -1);
#endif
    }

    MultiThreadedStrategy(const MultiThreadedStrategy &)  = delete;
    MultiThreadedStrategy(const MultiThreadedStrategy &&) = delete;
    void               operator=(const MultiThreadedStrategy &) = delete;

    [[nodiscard]] bool hasAvailableCapacity(const std::vector<std::shared_ptr<Sequence>> &dependents, const std::size_t requiredCapacity, const signed_index_type cursorValue) const noexcept {
        const auto wrapPoint = (cursorValue + static_cast<signed_index_type>(requiredCapacity)) - static_cast<signed_index_type>(_size);

        if (const auto cachedGatingSequence = _gatingSequenceCache->value(); wrapPoint > cachedGatingSequence || cachedGatingSequence > cursorValue) {
            const auto minSequence = detail::getMinimumSequence(dependents, cursorValue);
            _gatingSequenceCache->setValue(minSequence);

            if (wrapPoint > minSequence) {
                return false;
            }
        }
        return true;
    }

    [[nodiscard]] signed_index_type next(const std::vector<std::shared_ptr<Sequence>> &dependents, std::size_t n_slots_to_claim = 1) {
        assert((n_slots_to_claim > 0) && "n_slots_to_claim must be > 0");

        signed_index_type current;
        signed_index_type next;

        SpinWait     spinWait;
        do {
            current = _cursor.value();
            next = current + static_cast<signed_index_type>(n_slots_to_claim);

            signed_index_type wrapPoint            = next - static_cast<signed_index_type>(_size);
            signed_index_type cachedGatingSequence = _gatingSequenceCache->value();

            if (wrapPoint > cachedGatingSequence || cachedGatingSequence > current) {
                signed_index_type gatingSequence = detail::getMinimumSequence(dependents, current);

                if (wrapPoint > gatingSequence) {
                    if constexpr (hasSignalAllWhenBlocking<WAIT_STRATEGY>) {
                        _waitStrategy.signalAllWhenBlocking();
                    }
                    spinWait.spinOnce();
                    continue;
                }

                _gatingSequenceCache->setValue(gatingSequence);
            } else if (_cursor.compareAndSet(current, next)) {
                break;
            }
        } while (true);

        return next;
    }

    [[nodiscard]] signed_index_type tryNext(const std::vector<std::shared_ptr<Sequence>> &dependents, std::size_t n_slots_to_claim = 1) {
        assert((n_slots_to_claim > 0) && "n_slots_to_claim must be > 0");

        signed_index_type current;
        signed_index_type next;

        do {
            current = _cursor.value();
            next    = current + static_cast<signed_index_type>(n_slots_to_claim);

            if (!hasAvailableCapacity(dependents, n_slots_to_claim, current)) {
                throw NoCapacityException();
            }
        } while (!_cursor.compareAndSet(current, next));

        return next;
    }

    [[nodiscard]] signed_index_type getRemainingCapacity(const std::vector<std::shared_ptr<Sequence>> &dependents) const noexcept {
        const auto produced = _cursor.value();
        const auto consumed = detail::getMinimumSequence(dependents, produced);

        return static_cast<signed_index_type>(_size) - (produced - consumed);
    }

    void publish(signed_index_type offset, std::size_t n_slots_to_claim) {
        for (std::size_t i = 0; i < n_slots_to_claim; i++) {
            setAvailable(offset + static_cast<signed_index_type>(i) + 1);
        }
        if constexpr (hasSignalAllWhenBlocking<WAIT_STRATEGY>) {
            _waitStrategy.signalAllWhenBlocking();
        }
    }

    [[nodiscard]] forceinline bool isAvailable(signed_index_type sequence) const noexcept {
        const auto index = calculateIndex(sequence);
        const auto flag  = calculateAvailabilityFlag(sequence);
#if (__cpp_lib_atomic_ref >= 201806L)
        return std::atomic_ref{_availableBuffer[index]} == flag;
#else // clang's libc++ does not yet support std::atomic_ref
        return _availableBuffer[index] == flag;
#endif
    }

    [[nodiscard]] forceinline signed_index_type getHighestPublishedSequence(const signed_index_type lowerBound, const signed_index_type availableSequence) const noexcept {
        for (signed_index_type sequence = lowerBound; sequence <= availableSequence; sequence++) {
            if (!isAvailable(sequence)) {
                return sequence - 1;
            }
        }

        return availableSequence;
    }

private:
    void                      setAvailable(signed_index_type sequence) noexcept { setAvailableBufferValue(calculateIndex(sequence), calculateAvailabilityFlag(sequence)); }
    forceinline void          setAvailableBufferValue(std::size_t index, std::int32_t flag) noexcept {
#if (__cpp_lib_atomic_ref >= 201806L)
        std::atomic_ref{_availableBuffer[index]} = flag;
#else // clang's libc++ does not yet support std::atomic_ref
        _availableBuffer[index] = flag;
#endif
    }
    [[nodiscard]] forceinline std::int32_t calculateAvailabilityFlag(const signed_index_type sequence) const noexcept { return static_cast<std::int32_t>(sequence >> _indexShift); }
    [[nodiscard]] forceinline std::size_t calculateIndex(const signed_index_type sequence) const noexcept { return static_cast<std::size_t>(static_cast<std::int32_t>(sequence) & (_size - 1)); }
};

static_assert(ClaimStrategy<MultiThreadedStrategy<1024, NoWaitStrategy>>);
// clang-format on

enum class ProducerType {
    /**
     * creates a buffer assuming a single producer-thread and multiple consumer
     */
    Single,

    /**
     * creates a buffer assuming multiple producer-threads and multiple consumer
     */
    Multi
};

namespace detail {
template<std::size_t size, ProducerType producerType, WaitStrategy WAIT_STRATEGY>
struct producer_type;

template<std::size_t size, WaitStrategy WAIT_STRATEGY>
struct producer_type<size, ProducerType::Single, WAIT_STRATEGY> {
    using value_type = SingleThreadedStrategy<size, WAIT_STRATEGY>;
};

template<std::size_t size, WaitStrategy WAIT_STRATEGY>
struct producer_type<size, ProducerType::Multi, WAIT_STRATEGY> {
    using value_type = MultiThreadedStrategy<size, WAIT_STRATEGY>;
};

template<std::size_t size, ProducerType producerType, WaitStrategy WAIT_STRATEGY>
using producer_type_v = typename producer_type<size, producerType, WAIT_STRATEGY>::value_type;

} // namespace detail

} // namespace gr

#endif // GNURADIO_CLAIMSTRATEGY_HPP

// #include "Sequence.hpp"

// #include "WaitStrategy.hpp"


namespace gr {

namespace util {
constexpr std::size_t
round_up(std::size_t num_to_round, std::size_t multiple) noexcept {
    if (multiple == 0) {
        return num_to_round;
    }
    const auto remainder = num_to_round % multiple;
    if (remainder == 0) {
        return num_to_round;
    }
    return num_to_round + multiple - remainder;
}
} // namespace util

// clang-format off
class double_mapped_memory_resource : public std::pmr::memory_resource {
    [[nodiscard]] void* do_allocate(const std::size_t required_size, std::size_t alignment) override {
        // the 2nd double mapped memory call mmap may fail and/or return an unsuitable return address which is unavoidable
        // this workaround retries to get a more favourable allocation up to three times before it throws the regular exception
        for (int retry_attempt = 0; retry_attempt < 3; retry_attempt++) {
            try {
                return do_allocate_internal(required_size, alignment);
            } catch (std::system_error& e) { // explicitly caught for retry
                fmt::print("system-error: allocation failed (VERY RARE) '{}' - will retry, attempt: {}\n", e.what(), retry_attempt);
            } catch (std::invalid_argument& e) { // explicitly caught for retry
                fmt::print("invalid_argument: allocation failed (VERY RARE) '{}' - will retry, attempt: {}\n", e.what(), retry_attempt);
            }
        }
        return do_allocate_internal(required_size, alignment);
    }
#ifdef HAS_POSIX_MAP_INTERFACE
    [[nodiscard]] static void* do_allocate_internal(const std::size_t required_size, std::size_t alignment) { //NOSONAR

        const std::size_t size = 2 * required_size;
        if (size % static_cast<std::size_t>(getpagesize()) != 0LU) {
            throw std::invalid_argument(fmt::format("incompatible buffer-byte-size: {} -> {} alignment: {} vs. page size: {}", required_size, size, alignment, getpagesize()));
        }
        const std::size_t size_half = size/2;

        static std::size_t _counter;
        const auto buffer_name = fmt::format("/double_mapped_memory_resource-{}-{}-{}", getpid(), size, _counter++);
        const auto memfd_create = [name = buffer_name.c_str()](unsigned int flags) {
            return syscall(__NR_memfd_create, name, flags);
        };
        auto shm_fd = static_cast<int>(memfd_create(0));
        if (shm_fd < 0) {
            throw std::system_error(errno, std::system_category(), fmt::format("{} - memfd_create error {}: {}",  buffer_name, errno, strerror(errno)));
        }

        if (ftruncate(shm_fd, static_cast<off_t>(size)) == -1) {
            std::error_code errorCode(errno, std::system_category());
            close(shm_fd);
            throw std::system_error(errorCode, fmt::format("{} - ftruncate {}: {}",  buffer_name, errno, strerror(errno)));
        }

        void* first_copy = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, static_cast<off_t>(0));
        if (first_copy == MAP_FAILED) {
            std::error_code errorCode(errno, std::system_category());
            close(shm_fd);
            throw std::system_error(errorCode, fmt::format("{} - failed munmap for first half {}: {}",  buffer_name, errno, strerror(errno)));
        }

        // unmap the 2nd half
        if (munmap(static_cast<char*>(first_copy) + size_half, size_half) == -1) {
            std::error_code errorCode(errno, std::system_category());
            close(shm_fd);
            throw std::system_error(errorCode, fmt::format("{} - failed munmap for second half {}: {}",  buffer_name, errno, strerror(errno)));
        }

        // Map the first half into the now available hole.
        // Note that the second_copy_addr mmap argument is only a hint and mmap might place the
        // mapping somewhere else: "If addr is not NULL, then the kernel takes it as  a hint about
        // where to place the mapping". The returned pointer therefore must equal second_copy_addr
        // for our contiguous mapping to work as intended.
        void* second_copy_addr = static_cast<char*> (first_copy) + size_half;
        if (const void* result = mmap(second_copy_addr, size_half, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, static_cast<off_t> (0)); result != second_copy_addr) {
            std::error_code errorCode(errno, std::system_category());
            close(shm_fd);
            if (result == MAP_FAILED) {
                throw std::system_error(errorCode, fmt::format("{} - failed mmap for second copy {}: {}",  buffer_name, errno, strerror(errno)));
            } else {
                ptrdiff_t diff2 = static_cast<const char*>(result) - static_cast<char*>(second_copy_addr);
                ptrdiff_t diff1 = static_cast<const char*>(result) - static_cast<char*>(first_copy);
                throw std::system_error(errorCode, fmt::format("{} - failed mmap for second copy: mismatching address -- result {} first_copy {} second_copy_addr {} - diff result-2nd {} diff result-1st {} size {}",
                                                     buffer_name, fmt::ptr(result), fmt::ptr(first_copy), fmt::ptr(second_copy_addr), diff2, diff1, 2*size_half));
            }
        }

        close(shm_fd); // file-descriptor is no longer needed. The mapping is retained.
        return first_copy;
}
#else
    [[nodiscard]] static void* do_allocate_internal(const std::size_t, std::size_t) { //NOSONAR
        throw std::invalid_argument("OS does not provide POSIX interface for mmap(...) and munmao(...)");
        // static_assert(false, "OS does not provide POSIX interface for mmap(...) and munmao(...)");
    }
#endif

#ifdef HAS_POSIX_MAP_INTERFACE
    void  do_deallocate(void* p, std::size_t size, std::size_t alignment) override { //NOSONAR

        if (munmap(p, size) == -1) {
            throw std::system_error(errno, std::system_category(), fmt::format("double_mapped_memory_resource::do_deallocate(void*, {}, {}) - munmap(..) failed", size, alignment));
        }
    }
#else
    void  do_deallocate(void*, std::size_t, size_t) override { }
#endif

    bool  do_is_equal(const memory_resource& other) const noexcept override { return this == &other; }

public:
    static inline double_mapped_memory_resource* defaultAllocator() {
        static auto instance = double_mapped_memory_resource();
        return &instance;
    }

    template<typename T>
    static inline std::pmr::polymorphic_allocator<T> allocator()
    {
        return std::pmr::polymorphic_allocator<T>(gr::double_mapped_memory_resource::defaultAllocator());
    }
};

/*
 * The enum determines how to handle samples if consume() or publish() was not called by the user in `processBulk` function.
 */
enum class SpanReleasePolicy {
    Terminate, //  terminates the program
    ProcessAll, // consume/publish all samples
    ProcessNone // consume/publish zero samples
};

/**
 * @brief circular buffer implementation using double-mapped memory allocations
 * where the first SIZE-ed buffer is mirrored directly its end to mimic wrap-around
 * free bulk memory access. The buffer keeps a list of indices (using 'Sequence')
 * to keep track of which parts can be tread-safely read and/or written
 *
 *                          wrap-around point
 *                                 |
 *                                 v
 *  | buffer segment #1 (original) | buffer segment #2 (copy of #1) |
 *  0                            SIZE                            2*SIZE
 *                      writeIndex
 *                          v
 *  wrap-free write access  |<-  N_1 < SIZE   ->|
 *
 *  readIndex < writeIndex-N_2
 *      v
 *      |<- N_2 < SIZE ->|
 *
 * N.B N_AVAILABLE := (SIZE + writeIndex - readIndex ) % SIZE
 *
 * citation: <find appropriate first and educational reference>
 *
 * This implementation provides single- as well as multi-producer/consumer buffer
 * combinations for thread-safe CPU-to-CPU data transfer (optionally) using either
 * a) the POSIX mmaped(..)/munmapped(..) MMU interface, if available, and/or
 * b) the guaranteed portable standard C/C++ (de-)allocators as a fall-back.
 *
 * for more details see
 */
template <typename T, std::size_t SIZE = std::dynamic_extent, ProducerType producer_type = ProducerType::Single, WaitStrategy WAIT_STRATEGY = SleepingWaitStrategy>
class CircularBuffer
{
    using Allocator         = std::pmr::polymorphic_allocator<T>;
    using BufferType        = CircularBuffer<T, SIZE, producer_type, WAIT_STRATEGY>;
    using ClaimType         = detail::producer_type_v<SIZE, producer_type, WAIT_STRATEGY>;
    using DependendsType    = std::shared_ptr<std::vector<std::shared_ptr<Sequence>>>;
    using signed_index_type = Sequence::signed_index_type;

    struct buffer_impl {
        Sequence                    _cursor;
        Allocator                   _allocator{};
        const bool                  _isMmapAllocated;
        const std::size_t             _size; // pre-condition: std::has_single_bit(_size)
        std::vector<T, Allocator>   _data;
        WAIT_STRATEGY               _wait_strategy = WAIT_STRATEGY();
        ClaimType                   _claimStrategy;
        // list of dependent reader indices
        DependendsType              _read_indices{ std::make_shared<std::vector<std::shared_ptr<Sequence>>>() };

        buffer_impl() = delete;
        buffer_impl(const std::size_t min_size, Allocator allocator) : _allocator(allocator), _isMmapAllocated(dynamic_cast<double_mapped_memory_resource *>(_allocator.resource())),
            _size(align_with_page_size(std::bit_ceil(min_size), _isMmapAllocated)), _data(buffer_size(_size, _isMmapAllocated), _allocator), _claimStrategy(ClaimType(_cursor, _wait_strategy, _size)) {
        }

#ifdef HAS_POSIX_MAP_INTERFACE
        static std::size_t align_with_page_size(const std::size_t min_size, bool _isMmapAllocated) {
            if (_isMmapAllocated) {
                const std::size_t pageSize = static_cast<std::size_t>(getpagesize());
                const std::size_t elementSize = sizeof(T);
                // least common multiple (lcm) of elementSize and pageSize
                std::size_t lcmValue = elementSize * pageSize / std::gcd(elementSize, pageSize);

                // adjust lcmValue to be larger than min_size
                while (lcmValue < min_size) {
                    lcmValue += lcmValue;
                }
                return lcmValue;
            } else {
                return min_size;
            }
        }
#else
        static std::size_t align_with_page_size(const std::size_t min_size, bool) {
            return min_size; // mmap() & getpagesize() not supported for non-POSIX OS
        }
#endif

        static std::size_t buffer_size(const std::size_t size, bool isMmapAllocated) {
            // double-mmaped behaviour requires the different size/alloc strategy
            // i.e. the second buffer half may not default-constructed as it's identical to the first one
            // and would result in a double dealloc during the default destruction
            return isMmapAllocated ? size : 2 * size;
        }
    }; // struct buffer_impl

    template<typename U = T>
    class buffer_writer;

    template<typename U = T, SpanReleasePolicy policy = SpanReleasePolicy::Terminate>
    class PublishableOutputRange {
        buffer_writer<U>* _parent = nullptr;

    public:
    using element_type = T;
    using value_type = typename std::remove_cv_t<T>;
    using iterator = typename std::span<T>::iterator;
    using reverse_iterator = typename std::span<T>::reverse_iterator;
    using pointer = typename std::span<T>::reverse_iterator;

    PublishableOutputRange() = delete;
    explicit PublishableOutputRange(buffer_writer<U>* parent) noexcept : _parent(parent) {
        _parent->_index = 0UZ;
        _parent->_offset = 0;
        _parent->_internalSpan = std::span<T>();
    #ifndef NDEBUG
        _parent->_rangesCounter++;
    #endif
    };
    explicit constexpr PublishableOutputRange(buffer_writer<U>* parent, std::size_t index, signed_index_type sequence, std::size_t nSlotsToClaim) noexcept :
        _parent(parent) {
        _parent->_index = index;
        _parent->_offset = sequence - static_cast<signed_index_type>(nSlotsToClaim);
        _parent->_internalSpan = std::span<T>(&_parent->_buffer->_data.data()[index], nSlotsToClaim);
    #ifndef NDEBUG
        _parent->_rangesCounter++;
    #endif
    }
    PublishableOutputRange(const PublishableOutputRange& other):_parent(other._parent) {
    #ifndef NDEBUG
        _parent->_rangesCounter++;
    #endif
    }
    PublishableOutputRange& operator=(const PublishableOutputRange& other) {
        if (this != &other) {
            _parent = other._parent;
    #ifndef NDEBUG
            _parent->_rangesCounter++;
    #endif
        }
    }

    ~PublishableOutputRange() {
    #ifndef NDEBUG
        _parent->_rangesCounter--;

        if constexpr (isMultiThreadedStrategy()) {
            if (_parent->_rangesCounter == 0 && !isFullyPublished()) {
                fmt::print(stderr, "CircularBuffer::multiple_writer::PublishableOutputRange() - did not publish {} samples\n", _parent->_internalSpan.size() - _parent->_nSlotsPublished);
                std::abort();
            }

        } else {
            if (_parent->_rangesCounter == 0 && !_parent->_internalSpan.empty() && !isPublished()) {
                fmt::print(stderr, "CircularBuffer::single_writer::PublishableOutputRange() - omitted publish call for {} reserved samples\n", _parent->_internalSpan.size());
                std::abort();
            }
        }
    #endif
    }

    [[nodiscard]] constexpr bool
    isPublished() const noexcept {
        return _parent->_isRangePublished;
    }

    [[nodiscard]] constexpr bool
    isFullyPublished() const noexcept {
        return _parent->_internalSpan.size() == _parent->_nSlotsPublished;
    }

    [[nodiscard]] constexpr static bool
    isMultiThreadedStrategy() noexcept {
        return std::is_base_of_v<MultiThreadedStrategy<SIZE, WAIT_STRATEGY>, ClaimType>;
    }

    [[nodiscard]] constexpr static SpanReleasePolicy
    spanReleasePolicy() noexcept {
        return policy;
    }

    [[nodiscard]] constexpr std::size_t size() const noexcept { return _parent->_internalSpan.size(); };
    [[nodiscard]] constexpr std::size_t size_bytes() const noexcept { return size() * sizeof(T); };
    [[nodiscard]] constexpr bool empty() const noexcept { return _parent->_internalSpan.empty(); }
    [[nodiscard]] constexpr iterator cbegin() const noexcept { return _parent->_internalSpan.cbegin(); }
    [[nodiscard]] constexpr iterator begin() const noexcept { return _parent->_internalSpan.begin(); }
    [[nodiscard]] constexpr iterator cend() const noexcept { return _parent->_internalSpan.cend(); }
    [[nodiscard]] constexpr iterator end() const noexcept { return _parent->_internalSpan.end(); }
    [[nodiscard]] constexpr reverse_iterator rbegin() const noexcept { return _parent->_internalSpan.rbegin(); }
    [[nodiscard]] constexpr reverse_iterator rend() const noexcept { return _parent->_internalSpan.rend(); }
    [[nodiscard]] constexpr T* data() const noexcept { return _parent->_internalSpan.data(); }
    T& operator [](std::size_t i) const noexcept  {return _parent->_internalSpan[i]; }
    T& operator [](std::size_t i) noexcept { return _parent->_internalSpan[i]; }
    explicit(false) operator std::span<T>&() const noexcept { return _parent->_internalSpan; }
    operator std::span<T>&() noexcept { return _parent->_internalSpan; }

    constexpr void publish(std::size_t nSlotsToPublish) noexcept {
        assert(nSlotsToPublish <= _parent->_internalSpan.size() - _parent->_nSlotsPublished && "n_produced must be <= than unpublished slots");
        if (!_parent->_isMmapAllocated) {
            const std::size_t size = _parent->_size;
            // mirror samples below/above the buffer's wrap-around point
            const size_t nFirstHalf = std::min(size - _parent->_index, nSlotsToPublish);
            const size_t nSecondHalf = nSlotsToPublish - nFirstHalf;

            auto &data = _parent->_buffer->_data;
            std::copy(&data[_parent->_index], &data[_parent->_index + nFirstHalf], &data[_parent->_index + size]);
            std::copy(&data[size], &data[size + nSecondHalf], &data[0]);
        }
        _parent->_claimStrategy->publish(_parent->_offset, nSlotsToPublish);
        _parent->_offset += static_cast<signed_index_type>(nSlotsToPublish);
        _parent->_nSlotsPublished += nSlotsToPublish;
        _parent->_isRangePublished = true;
    }
    }; // class PublishableOutputRange

    static_assert(PublishableSpan<PublishableOutputRange<T>>);

    template <typename U>
    class buffer_writer {
        friend class PublishableOutputRange<U, SpanReleasePolicy::Terminate>;
        friend class PublishableOutputRange<U, SpanReleasePolicy::ProcessAll>;
        friend class PublishableOutputRange<U, SpanReleasePolicy::ProcessNone>;

        using BufferTypeLocal = std::shared_ptr<buffer_impl>;

        BufferTypeLocal _buffer; // controls buffer life-cycle, the rest are cache optimisations
        bool            _isMmapAllocated;
        std::size_t     _size;
        ClaimType*      _claimStrategy;

        // doesn't have to be atomic because this writer is accessed (by design) always by the same thread.
        // These are the parameters for PublishableOutputRange, only one PublishableOutputRange can be reserved per writer
        std::size_t       _nSlotsPublished {0UZ}; // controls how many slots wre already published, multiple publish() calls are allowed,
        bool              _isRangePublished {true};// controls if publish() was invoked
        std::size_t       _index {0UZ};
        signed_index_type _offset {0};
        std::span<T> _internalSpan{}; // internal span is managed by buffer_writer and is shared across all PublishableSpans reserved by this buffer_writer

#ifndef NDEBUG
        std::size_t _rangesCounter{0}; // this counter is used only in debug mode to check if publish() was invoked correctly
#endif

    public:
        buffer_writer() = delete;
        explicit buffer_writer(std::shared_ptr<buffer_impl> buffer) noexcept :
            _buffer(std::move(buffer)), _isMmapAllocated(_buffer->_isMmapAllocated),
            _size(_buffer->_size), _claimStrategy(std::addressof(_buffer->_claimStrategy)) { };
        buffer_writer(buffer_writer&& other) noexcept
            : _buffer(std::move(other._buffer))
            , _isMmapAllocated(_buffer->_isMmapAllocated)
            , _size(_buffer->_size)
            , _claimStrategy(std::addressof(_buffer->_claimStrategy))
            , _nSlotsPublished(std::exchange(other._nSlotsPublished, 0UZ))
            , _isRangePublished(std::exchange(other._isRangePublished, true))
            , _index(std::exchange(other._index, 0UZ))
            , _offset(std::exchange(other._offset, 0))
            , _internalSpan(std::exchange(other._internalSpan, std::span<T>{})) { };

        buffer_writer& operator=(buffer_writer tmp) noexcept {
            std::swap(_buffer, tmp._buffer);
            _isMmapAllocated = _buffer->_isMmapAllocated;
            _size = _buffer->_size;
            std::swap(_nSlotsPublished, tmp._nSlotsPublished);
            std::swap(_isRangePublished, tmp._isRangePublished);
            _claimStrategy = std::addressof(_buffer->_claimStrategy);
            std::swap(_index, tmp._index);
            std::swap(_offset, tmp._offset);
            std::swap(_internalSpan, tmp._internalSpan);

            return *this;
        }

        [[nodiscard]] constexpr BufferType buffer() const noexcept { return CircularBuffer(_buffer); };

        template<SpanReleasePolicy policy = SpanReleasePolicy::Terminate>
        [[nodiscard]] constexpr auto reserve(std::size_t nSlotsToClaim) noexcept -> PublishableOutputRange<U, policy> {
            checkIfCanReserveAndAbortIfNeeded();
            _isRangePublished = false;
            _nSlotsPublished = 0UZ;

            if (nSlotsToClaim == 0) {
                return PublishableOutputRange<U, policy>(this);
            }

            try {
                const auto sequence = _claimStrategy->next(*_buffer->_read_indices, nSlotsToClaim); // alt: try_next
                const std::size_t index = (static_cast<std::size_t>(sequence) + _size - nSlotsToClaim) % _size;
                return PublishableOutputRange<U, policy>(this, index, sequence, nSlotsToClaim);
            } catch (const NoCapacityException &) {
                return PublishableOutputRange<U, policy>(this);
            }
        }

        template <typename... Args, WriterCallback<U, Args...> Translator>
        constexpr void publish(Translator&& translator, std::size_t nSlotsToClaim = 1, Args&&... args) {
            _isRangePublished = true;
            _nSlotsPublished += nSlotsToClaim;
            if (nSlotsToClaim <= 0 || _buffer->_read_indices->empty()) {
                return;
            }
            const auto sequence = _claimStrategy->next(*_buffer->_read_indices, nSlotsToClaim);
            translate_and_publish(std::forward<Translator>(translator), nSlotsToClaim, sequence, std::forward<Args>(args)...);
        } // blocks until elements are available

        template <typename... Args, WriterCallback<U, Args...> Translator>
        constexpr bool try_publish(Translator&& translator, std::size_t nSlotsToClaim = 1, Args&&... args) {
            _isRangePublished = true;
            _nSlotsPublished += nSlotsToClaim;
            if (nSlotsToClaim <= 0 || _buffer->_read_indices->empty()) {
                return true;
            }
            try {
                const auto sequence = _claimStrategy->tryNext(*_buffer->_read_indices, nSlotsToClaim);
                translate_and_publish(std::forward<Translator>(translator), nSlotsToClaim, sequence, std::forward<Args>(args)...);
                return true;
            } catch (const NoCapacityException &) {
                return false;
            }
        }

        [[nodiscard]] constexpr signed_index_type position() const noexcept { return _buffer->_cursor.value(); }

        [[nodiscard]] constexpr std::size_t available() const noexcept {
            return static_cast<std::size_t>(_claimStrategy->getRemainingCapacity(*_buffer->_read_indices));
        }

        private:
        template <typename... Args, WriterCallback<U, Args...> Translator>
        constexpr void translate_and_publish(Translator&& translator, const std::size_t n_slots_to_claim, const signed_index_type publishSequence, const Args&... args) {
            try {
                auto& data = _buffer->_data;
                const std::size_t index = (static_cast<std::size_t>(publishSequence) + _size - n_slots_to_claim) % _size;
                std::span<U> writable_data(&data[index], n_slots_to_claim);
                if constexpr (std::is_invocable<Translator, std::span<T>&, signed_index_type, Args...>::value) {
                    std::invoke(std::forward<Translator>(translator), writable_data, publishSequence - static_cast<signed_index_type>(n_slots_to_claim), args...);
                } else if constexpr (std::is_invocable<Translator, std::span<T>&, Args...>::value) {
                    std::invoke(std::forward<Translator>(translator), writable_data, args...);
                } else {
                    static_assert(gr::meta::always_false<Translator>, "Translator does not provide a matching signature");
                }

                if (!_isMmapAllocated) {
                    // mirror samples below/above the buffer's wrap-around point
                    const size_t nFirstHalf = std::min(_size - index, n_slots_to_claim);
                    const size_t nSecondHalf = n_slots_to_claim  - nFirstHalf;

                    std::copy(&data[index], &data[index + nFirstHalf], &data[index+ _size]);
                    std::copy(&data[_size],  &data[_size + nSecondHalf], &data[0]);
                }
                _claimStrategy->publish(publishSequence - static_cast<signed_index_type>(n_slots_to_claim), n_slots_to_claim);
            } catch (const std::exception&) {
                throw;
            } catch (...) {
                throw std::runtime_error("CircularBuffer::translate_and_publish() - unknown user exception thrown");
            }
        }

        constexpr void checkIfCanReserveAndAbortIfNeeded() const noexcept {
            if constexpr (std::is_base_of_v<MultiThreadedStrategy<SIZE, WAIT_STRATEGY>, ClaimType>) {
                if (_internalSpan.size() - _nSlotsPublished != 0) {
                    fmt::print(stderr, "An error occurred: The method CircularBuffer::multiple_writer::reserve() was invoked for the second time in succession, "
                                    "a previous PublishableOutputRange was not fully published, {} samples remain unpublished.", _internalSpan.size() - _nSlotsPublished);
                    std::abort();
                }

            } else {
                if (!_internalSpan.empty() && not _isRangePublished) {
                    fmt::print(stderr, "An error occurred: The method CircularBuffer::single_writer::reserve() was invoked for the second time in succession "
                                    "without calling publish() for a previous PublishableOutputRange, {} samples was reserved.", _internalSpan.size());
                    std::abort();
                }
            }
        }
    }; // class buffer_writer
    //static_assert(BufferWriter<buffer_writer<T>>);

    template<typename U = T>
    class buffer_reader;

    template<typename U = T, SpanReleasePolicy policy = SpanReleasePolicy::Terminate>
    class ConsumableInputRange {
        const buffer_reader<U>* _parent = nullptr;
        std::span<const T>      _internalSpan{};

    public:
    using element_type = T;
    using value_type = typename std::remove_cv_t<T>;
    using iterator = typename std::span<const T>::iterator;
    using reverse_iterator = typename std::span<const T>::reverse_iterator;
    using pointer = typename std::span<const T>::reverse_iterator;

    explicit ConsumableInputRange(const buffer_reader<U>* parent) noexcept : _parent(parent) {};
    explicit constexpr ConsumableInputRange(const buffer_reader<U>* parent, std::size_t index, std::size_t nRequested) noexcept :
        _parent(parent), _internalSpan({ &_parent->_buffer->_data.data()[index], nRequested }) { }

    ConsumableInputRange(const ConsumableInputRange& other)
        : _parent(other._parent),
          _internalSpan(other._internalSpan) {
    }

    ConsumableInputRange& operator=(const ConsumableInputRange& other) {
        if (this != &other) {
            _parent = other._parent;
            _internalSpan = other._internalSpan;
        }
        return *this;
    }

    ConsumableInputRange(ConsumableInputRange&& other) noexcept
        : _parent(std::exchange(other._parent, nullptr))
        , _internalSpan(std::exchange(other._internalSpan, std::span<T>{})) {
    }
    ConsumableInputRange& operator=(ConsumableInputRange&& other) noexcept {
        if (this != &other) {
            std::swap(_parent, other._parent);
            std::swap(_internalSpan, other._internalSpan);
        }
        return *this;
    }
    ~ConsumableInputRange() = default;

    [[nodiscard]] constexpr static SpanReleasePolicy
    spanReleasePolicy() noexcept {
        return policy;
    }

    [[nodiscard]] constexpr bool
     isConsumed() const noexcept {
         return _parent->_isRangeConsumed;
     }

    [[nodiscard]] constexpr std::size_t size() const noexcept { return _internalSpan.size(); }
    [[nodiscard]] constexpr std::size_t size_bytes() const noexcept { return size() * sizeof(T); }
    [[nodiscard]] constexpr bool empty() const noexcept { return _internalSpan.empty(); }
    [[nodiscard]] constexpr iterator cbegin() const noexcept { return _internalSpan.cbegin(); }
    [[nodiscard]] constexpr iterator begin() const noexcept { return _internalSpan.begin(); }
    [[nodiscard]] constexpr iterator cend() const noexcept { return _internalSpan.cend(); }
    [[nodiscard]] constexpr iterator end() const noexcept { return _internalSpan.end(); }
    [[nodiscard]] constexpr const T& front() const noexcept { return _internalSpan.front(); }
    [[nodiscard]] constexpr const T& back() const noexcept { return _internalSpan.back(); }
    [[nodiscard]] constexpr auto first(std::size_t count) const noexcept { return _internalSpan.first(count); }
    [[nodiscard]] constexpr auto last(std::size_t count) const noexcept { return _internalSpan.last(count); }
    [[nodiscard]] constexpr reverse_iterator rbegin() const noexcept { return _internalSpan.rbegin(); }
    [[nodiscard]] constexpr reverse_iterator rend() const noexcept { return _internalSpan.rend(); }
    [[nodiscard]] constexpr const T* data() const noexcept { return _internalSpan.data(); }
    const T& operator [](std::size_t i) const noexcept  {return _internalSpan[i]; }
    const T& operator [](std::size_t i) noexcept { return _internalSpan[i]; }
    operator const std::span<const T>&() const noexcept { return _internalSpan; }
    operator std::span<const T>&() noexcept { return _internalSpan; }
    operator std::span<const T>&&() = delete;

    template <bool strict_check = true>
    [[nodiscard]] bool consume(std::size_t nSamples) const noexcept {
        if (isConsumed()) {
            fmt::println("An error occurred: The method CircularBuffer::buffer_reader::ConsumableInputRange::consume() was invoked for the second time in succession, a corresponding ConsumableInputRange was already consumed.");
            std::abort();
        }
        return tryConsume<strict_check>(nSamples);
    }

    template <bool strict_check = true>
    [[nodiscard]] bool tryConsume(std::size_t nSamples) const noexcept {
        if (isConsumed()) {
            return false;
        }
        _parent->_isRangeConsumed = true;
        if constexpr (strict_check) {
            if (nSamples <= 0) {
                return true;
            }

            if (nSamples > std::min(_internalSpan.size(), _parent->available())) {
                return false;
            }
        }
        _parent->_readIndexCached = _parent->_readIndex->addAndGet(static_cast<signed_index_type>(nSamples));
        return true;
    }

    }; // class ConsumableInputRange
    static_assert(ConsumableSpan<ConsumableInputRange<T>>);

    template<typename U>
    class buffer_reader
    {
        friend class ConsumableInputRange<U, SpanReleasePolicy::Terminate>;
        friend class ConsumableInputRange<U, SpanReleasePolicy::ProcessAll>;
        friend class ConsumableInputRange<U, SpanReleasePolicy::ProcessNone>;

        using BufferTypeLocal = std::shared_ptr<buffer_impl>;

        std::shared_ptr<Sequence>    _readIndex = std::make_shared<Sequence>();
        mutable signed_index_type    _readIndexCached;
        BufferTypeLocal              _buffer; // controls buffer life-cycle, the rest are cache optimisations
        std::size_t                  _size; // pre-condition: std::has_single_bit(_size)
        mutable bool                 _isRangeConsumed {true}; // controls if consume() was invoked, doesn't have to be atomic because this reader is accessed (by design) always by the same thread.

        std::size_t
        buffer_index() const noexcept {
            const auto bitmask = _size - 1;
            return static_cast<std::size_t>(_readIndexCached) & bitmask;
        }

    public:
        buffer_reader() = delete;
        explicit buffer_reader(std::shared_ptr<buffer_impl> buffer) noexcept :
            _buffer(buffer), _size(buffer->_size){
            gr::detail::addSequences(_buffer->_read_indices, _buffer->_cursor, {_readIndex});
            _readIndexCached = _readIndex->value();
        }
        buffer_reader(buffer_reader&& other) noexcept
            : _readIndex(std::move(other._readIndex))
            , _readIndexCached(std::exchange(other._readIndexCached, _readIndex->value()))
            , _buffer(other._buffer)
            , _size(_buffer->_size)
            , _isRangeConsumed(std::move(other._isRangeConsumed)) {
        }
        buffer_reader& operator=(buffer_reader tmp) noexcept {
            std::swap(_readIndex, tmp._readIndex);
            std::swap(_readIndexCached, tmp._readIndexCached);
            std::swap(_buffer, tmp._buffer);
            std::swap(_isRangeConsumed, tmp._isRangeConsumed);
            _size = _buffer->_size;
            return *this;
        };
        ~buffer_reader() { gr::detail::removeSequence( _buffer->_read_indices, _readIndex); }

        [[nodiscard]] constexpr BufferType buffer() const noexcept { return CircularBuffer(_buffer); };

        [[nodiscard]] constexpr bool isConsumed() const noexcept {
            return _isRangeConsumed;
        }

        template<SpanReleasePolicy policy = SpanReleasePolicy::Terminate>
        [[nodiscard]] constexpr auto get(const std::size_t nRequested) const noexcept -> ConsumableInputRange<U, policy> {
            _isRangeConsumed = false;
            return ConsumableInputRange<U, policy>(this, buffer_index(), nRequested);
        }

        template <bool strict_check = true>
        [[nodiscard]] constexpr bool consume(const std::size_t nSamples = 1) noexcept {
            if (isConsumed()) {
                fmt::println("An error occurred: The method CircularBuffer::buffer_reader::consume() was invoked for the second time in succession, a corresponding ConsumableInputRange was already consumed.");
                std::abort();
            }

            if constexpr (strict_check) {
                if (nSamples <= 0) {
                    _isRangeConsumed = true;
                    return true;
                }
                if (nSamples > available()) {
                    _isRangeConsumed = true;
                    return false;
                }
            }
            _readIndexCached = _readIndex->addAndGet(static_cast<signed_index_type>(nSamples));
            _isRangeConsumed = true;
            return true;
        }

        [[nodiscard]] constexpr signed_index_type position() const noexcept { return _readIndexCached; }

        [[nodiscard]] constexpr std::size_t available() const noexcept {
            const auto last = _buffer->_claimStrategy.getHighestPublishedSequence(_readIndexCached + 1, _buffer->_cursor.value());
            return static_cast<std::size_t>(last - _readIndexCached);
        }
    }; // class buffer_reader

    //static_assert(BufferReader<buffer_reader<T>>);

    [[nodiscard]] constexpr static Allocator DefaultAllocator() {
        if constexpr (has_posix_mmap_interface && std::is_trivially_copyable_v<T>) {
            return double_mapped_memory_resource::allocator<T>();
        } else {
            return Allocator();
        }
    }

    std::shared_ptr<buffer_impl> _shared_buffer_ptr;
    explicit CircularBuffer(std::shared_ptr<buffer_impl> shared_buffer_ptr) : _shared_buffer_ptr(shared_buffer_ptr) {}

public:
    CircularBuffer() = delete;
    explicit CircularBuffer(std::size_t min_size, Allocator allocator = DefaultAllocator())
        : _shared_buffer_ptr(std::make_shared<buffer_impl>(min_size, allocator)) { }
    ~CircularBuffer() = default;

    [[nodiscard]] std::size_t       size() const noexcept { return _shared_buffer_ptr->_size; }
    [[nodiscard]] BufferWriter auto new_writer() { return buffer_writer<T>(_shared_buffer_ptr); }
    [[nodiscard]] BufferReader auto new_reader() { return buffer_reader<T>(_shared_buffer_ptr); }

    // implementation specific interface -- not part of public Buffer / production-code API
    [[nodiscard]] auto n_readers()              { return _shared_buffer_ptr->_read_indices->size(); }
    [[nodiscard]] const auto &claim_strategy()  { return _shared_buffer_ptr->_claimStrategy; }
    [[nodiscard]] const auto &wait_strategy()   { return _shared_buffer_ptr->_wait_strategy; }
    [[nodiscard]] const auto &cursor_sequence() { return _shared_buffer_ptr->_cursor; }

};
static_assert(Buffer<CircularBuffer<int32_t>>);
// clang-format on

} // namespace gr
#endif // GNURADIO_CIRCULARBUFFER_HPP

// #include "DataSet.hpp"
#ifndef GNURADIO_DATASET_HPP
#define GNURADIO_DATASET_HPP

// #include "reflection.hpp"
#ifndef GNURADIO_REFLECTION_HPP
#define GNURADIO_REFLECTION_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wsign-conversion"
// #include <refl.hpp>


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

#pragma GCC diagnostic pop

#ifdef __GNUC__
#pragma GCC diagnostic push // ignore warning of external libraries that from this lib-context we do not have any control over
#ifndef __clang__
#pragma GCC diagnostic ignored "-Wuseless-cast"
#endif
#pragma GCC diagnostic ignored "-Wsign-conversion"
#endif
// #include <magic_enum.hpp>
//  __  __             _        ______                          _____
// |  \/  |           (_)      |  ____|                        / ____|_     _
// | \  / | __ _  __ _ _  ___  | |__   _ __  _   _ _ __ ___   | |   _| |_ _| |_
// | |\/| |/ _` |/ _` | |/ __| |  __| | '_ \| | | | '_ ` _ \  | |  |_   _|_   _|
// | |  | | (_| | (_| | | (__  | |____| | | | |_| | | | | | | | |____|_|   |_|
// |_|  |_|\__,_|\__, |_|\___| |______|_| |_|\__,_|_| |_| |_|  \_____|
//                __/ | https://github.com/Neargye/magic_enum
//               |___/  version 0.9.3
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 - 2023 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef NEARGYE_MAGIC_ENUM_HPP
#define NEARGYE_MAGIC_ENUM_HPP

#define MAGIC_ENUM_VERSION_MAJOR 0
#define MAGIC_ENUM_VERSION_MINOR 9
#define MAGIC_ENUM_VERSION_PATCH 3

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <type_traits>
#include <utility>

#if defined(MAGIC_ENUM_CONFIG_FILE)
#  include MAGIC_ENUM_CONFIG_FILE
#endif

#if !defined(MAGIC_ENUM_USING_ALIAS_OPTIONAL)
#  include <optional>
#endif
#if !defined(MAGIC_ENUM_USING_ALIAS_STRING)
#  include <string>
#endif
#if !defined(MAGIC_ENUM_USING_ALIAS_STRING_VIEW)
#  include <string_view>
#endif

#if defined(MAGIC_ENUM_NO_ASSERT)
#  define MAGIC_ENUM_ASSERT(...) static_cast<void>(0)
#else
#  include <cassert>
#  define MAGIC_ENUM_ASSERT(...) assert((__VA_ARGS__))
#endif

#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunknown-warning-option"
#  pragma clang diagnostic ignored "-Wenum-constexpr-conversion"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wmaybe-uninitialized" // May be used uninitialized 'return {};'.
#elif defined(_MSC_VER)
#  pragma warning(push)
#  pragma warning(disable : 26495) // Variable 'static_str<N>::chars_' is uninitialized.
#  pragma warning(disable : 28020) // Arithmetic overflow: Using operator '-' on a 4 byte value and then casting the result to a 8 byte value.
#  pragma warning(disable : 26451) // The expression '0<=_Param_(1)&&_Param_(1)<=1-1' is not true at this call.
#  pragma warning(disable : 4514) // Unreferenced inline function has been removed.
#endif

// Checks magic_enum compiler compatibility.
#if defined(__clang__) && __clang_major__ >= 5 || defined(__GNUC__) && __GNUC__ >= 9 || defined(_MSC_VER) && _MSC_VER >= 1910 || defined(__RESHARPER__)
#  undef  MAGIC_ENUM_SUPPORTED
#  define MAGIC_ENUM_SUPPORTED 1
#endif

// Checks magic_enum compiler aliases compatibility.
#if defined(__clang__) && __clang_major__ >= 5 || defined(__GNUC__) && __GNUC__ >= 9 || defined(_MSC_VER) && _MSC_VER >= 1920
#  undef  MAGIC_ENUM_SUPPORTED_ALIASES
#  define MAGIC_ENUM_SUPPORTED_ALIASES 1
#endif

// Enum value must be greater or equals than MAGIC_ENUM_RANGE_MIN. By default MAGIC_ENUM_RANGE_MIN = -128.
// If need another min range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MIN.
#if !defined(MAGIC_ENUM_RANGE_MIN)
#  define MAGIC_ENUM_RANGE_MIN -128
#endif

// Enum value must be less or equals than MAGIC_ENUM_RANGE_MAX. By default MAGIC_ENUM_RANGE_MAX = 128.
// If need another max range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MAX.
#if !defined(MAGIC_ENUM_RANGE_MAX)
#  define MAGIC_ENUM_RANGE_MAX 127
#endif

// Improve ReSharper C++ intellisense performance with builtins, avoiding unnecessary template instantiations.
#if defined(__RESHARPER__)
#  undef MAGIC_ENUM_GET_ENUM_NAME_BUILTIN
#  undef MAGIC_ENUM_GET_TYPE_NAME_BUILTIN
#  if __RESHARPER__ >= 20230100
#    define MAGIC_ENUM_GET_ENUM_NAME_BUILTIN(V) __rscpp_enumerator_name(V)
#    define MAGIC_ENUM_GET_TYPE_NAME_BUILTIN(T) __rscpp_type_name<T>()
#  else
#    define MAGIC_ENUM_GET_ENUM_NAME_BUILTIN(V) nullptr
#    define MAGIC_ENUM_GET_TYPE_NAME_BUILTIN(T) nullptr
#  endif
#endif

namespace magic_enum {

// If need another optional type, define the macro MAGIC_ENUM_USING_ALIAS_OPTIONAL.
#if defined(MAGIC_ENUM_USING_ALIAS_OPTIONAL)
MAGIC_ENUM_USING_ALIAS_OPTIONAL
#else
using std::optional;
#endif

// If need another string_view type, define the macro MAGIC_ENUM_USING_ALIAS_STRING_VIEW.
#if defined(MAGIC_ENUM_USING_ALIAS_STRING_VIEW)
MAGIC_ENUM_USING_ALIAS_STRING_VIEW
#else
using std::string_view;
#endif

// If need another string type, define the macro MAGIC_ENUM_USING_ALIAS_STRING.
#if defined(MAGIC_ENUM_USING_ALIAS_STRING)
MAGIC_ENUM_USING_ALIAS_STRING
#else
using std::string;
#endif

using char_type = string_view::value_type;
static_assert(std::is_same_v<string_view::value_type, string::value_type>, "magic_enum::customize requires same string_view::value_type and string::value_type");
static_assert([] {
  if constexpr (std::is_same_v<char_type, wchar_t>) {
    constexpr const char     c[] =  "abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|";
    constexpr const wchar_t wc[] = L"abcdefghijklmnopqrstuvwxyz_ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|";
    static_assert(std::size(c) == std::size(wc), "magic_enum::customize identifier characters are multichars in wchar_t.");

    for (std::size_t i = 0; i < std::size(c); ++i) {
      if (c[i] != wc[i]) {
        return false;
      }
    }
  }
  return true;
} (), "magic_enum::customize wchar_t is not compatible with ASCII.");

namespace customize {

// Enum value must be in range [MAGIC_ENUM_RANGE_MIN, MAGIC_ENUM_RANGE_MAX]. By default MAGIC_ENUM_RANGE_MIN = -128, MAGIC_ENUM_RANGE_MAX = 128.
// If need another range for all enum types by default, redefine the macro MAGIC_ENUM_RANGE_MIN and MAGIC_ENUM_RANGE_MAX.
// If need another range for specific enum type, add specialization enum_range for necessary enum type.
template <typename E>
struct enum_range {
  static_assert(std::is_enum_v<E>, "magic_enum::customize::enum_range requires enum type.");
  static constexpr int min = MAGIC_ENUM_RANGE_MIN;
  static constexpr int max = MAGIC_ENUM_RANGE_MAX;
  static_assert(max > min, "magic_enum::customize::enum_range requires max > min.");
};

static_assert(MAGIC_ENUM_RANGE_MAX > MAGIC_ENUM_RANGE_MIN, "MAGIC_ENUM_RANGE_MAX must be greater than MAGIC_ENUM_RANGE_MIN.");
static_assert((MAGIC_ENUM_RANGE_MAX - MAGIC_ENUM_RANGE_MIN) < (std::numeric_limits<std::uint16_t>::max)(), "MAGIC_ENUM_RANGE must be less than UINT16_MAX.");

namespace detail {

enum class customize_tag {
  default_tag,
  invalid_tag,
  custom_tag
};

} // namespace magic_enum::customize::detail

class customize_t : public std::pair<detail::customize_tag, string_view> {
 public:
  constexpr customize_t(string_view srt) : std::pair<detail::customize_tag, string_view>{detail::customize_tag::custom_tag, srt} {}
  constexpr customize_t(const char_type* srt) : customize_t{string_view{srt}} {}
  constexpr customize_t(detail::customize_tag tag) : std::pair<detail::customize_tag, string_view>{tag, string_view{}} {
    MAGIC_ENUM_ASSERT(tag != detail::customize_tag::custom_tag);
  }
};

// Default customize.
inline constexpr auto default_tag = customize_t{detail::customize_tag::default_tag};
// Invalid customize.
inline constexpr auto invalid_tag = customize_t{detail::customize_tag::invalid_tag};

// If need custom names for enum, add specialization enum_name for necessary enum type.
template <typename E>
constexpr customize_t enum_name(E) noexcept {
  return default_tag;
}

// If need custom type name for enum, add specialization enum_type_name for necessary enum type.
template <typename E>
constexpr customize_t enum_type_name() noexcept {
  return default_tag;
}

} // namespace magic_enum::customize

namespace detail {

template <typename T>
struct supported
#if defined(MAGIC_ENUM_SUPPORTED) && MAGIC_ENUM_SUPPORTED || defined(MAGIC_ENUM_NO_CHECK_SUPPORT)
    : std::true_type {};
#else
    : std::false_type {};
#endif

template <auto V, typename E = std::decay_t<decltype(V)>, std::enable_if_t<std::is_enum_v<E>, int> = 0>
using enum_constant = std::integral_constant<E, V>;

template <typename... T>
inline constexpr bool always_false_v = false;

template <typename T, typename = void>
struct has_is_flags : std::false_type {};

template <typename T>
struct has_is_flags<T, std::void_t<decltype(customize::enum_range<T>::is_flags)>> : std::bool_constant<std::is_same_v<bool, std::decay_t<decltype(customize::enum_range<T>::is_flags)>>> {};

template <typename T, typename = void>
struct range_min : std::integral_constant<int, MAGIC_ENUM_RANGE_MIN> {};

template <typename T>
struct range_min<T, std::void_t<decltype(customize::enum_range<T>::min)>> : std::integral_constant<decltype(customize::enum_range<T>::min), customize::enum_range<T>::min> {};

template <typename T, typename = void>
struct range_max : std::integral_constant<int, MAGIC_ENUM_RANGE_MAX> {};

template <typename T>
struct range_max<T, std::void_t<decltype(customize::enum_range<T>::max)>> : std::integral_constant<decltype(customize::enum_range<T>::max), customize::enum_range<T>::max> {};

struct str_view {
  const char* str_ = nullptr;
  std::size_t size_ = 0;
};

template <std::uint16_t N>
class static_str {
 public:
  constexpr explicit static_str(str_view str) noexcept : static_str{str.str_, std::make_integer_sequence<std::uint16_t, N>{}} {
    MAGIC_ENUM_ASSERT(str.size_ == N);
  }

  constexpr explicit static_str(string_view str) noexcept : static_str{str.data(), std::make_integer_sequence<std::uint16_t, N>{}} {
    MAGIC_ENUM_ASSERT(str.size() == N);
  }

  constexpr const char_type* data() const noexcept { return chars_; }

  constexpr std::uint16_t size() const noexcept { return N; }

  constexpr operator string_view() const noexcept { return {data(), size()}; }

 private:
  template <std::uint16_t... I>
  constexpr static_str(const char* str, std::integer_sequence<std::uint16_t, I...>) noexcept : chars_{static_cast<char_type>(str[I])..., static_cast<char_type>('\0')} {}

  template <std::uint16_t... I>
  constexpr static_str(string_view str, std::integer_sequence<std::uint16_t, I...>) noexcept : chars_{str[I]..., static_cast<char_type>('\0')} {}

  char_type chars_[static_cast<std::size_t>(N) + 1];
};

template <>
class static_str<0> {
 public:
  constexpr explicit static_str() = default;

  constexpr explicit static_str(str_view) noexcept {}

  constexpr explicit static_str(string_view) noexcept {}

  constexpr const char_type* data() const noexcept { return nullptr; }

  constexpr std::uint16_t size() const noexcept { return 0; }

  constexpr operator string_view() const noexcept { return {}; }
};

template <typename Op = std::equal_to<>>
class case_insensitive {
  static constexpr char_type to_lower(char_type c) noexcept {
    return (c >= static_cast<char_type>('A') && c <= static_cast<char_type>('Z')) ? static_cast<char_type>(c + (static_cast<char_type>('a') - static_cast<char_type>('A'))) : c;
  }

 public:
  template <typename L, typename R>
  constexpr auto operator()(L lhs,R rhs) const noexcept -> std::enable_if_t<std::is_same_v<std::decay_t<L>, char_type> && std::is_same_v<std::decay_t<R>, char_type>, bool> {
    return Op{}(to_lower(lhs), to_lower(rhs));
  }
};

constexpr std::size_t find(string_view str, char_type c) noexcept {
#if defined(__clang__) && __clang_major__ < 9 && defined(__GLIBCXX__) || defined(_MSC_VER) && _MSC_VER < 1920 && !defined(__clang__)
// https://stackoverflow.com/questions/56484834/constexpr-stdstring-viewfind-last-of-doesnt-work-on-clang-8-with-libstdc
// https://developercommunity.visualstudio.com/content/problem/360432/vs20178-regression-c-failed-in-test.html
  constexpr bool workaround = true;
#else
  constexpr bool workaround = false;
#endif

  if constexpr (workaround) {
    for (std::size_t i = 0; i < str.size(); ++i) {
      if (str[i] == c) {
        return i;
      }
    }

    return string_view::npos;
  } else {
    return str.find(c);
  }
}

template <typename BinaryPredicate>
constexpr bool is_default_predicate() noexcept {
  return std::is_same_v<std::decay_t<BinaryPredicate>, std::equal_to<string_view::value_type>> ||
         std::is_same_v<std::decay_t<BinaryPredicate>, std::equal_to<>>;
}

template <typename BinaryPredicate>
constexpr bool is_nothrow_invocable() {
  return is_default_predicate<BinaryPredicate>() ||
         std::is_nothrow_invocable_r_v<bool, BinaryPredicate, char_type, char_type>;
}

template <typename BinaryPredicate>
constexpr bool cmp_equal(string_view lhs, string_view rhs, [[maybe_unused]] BinaryPredicate&& p) noexcept(is_nothrow_invocable<BinaryPredicate>()) {
#if defined(_MSC_VER) && _MSC_VER < 1920 && !defined(__clang__)
  // https://developercommunity.visualstudio.com/content/problem/360432/vs20178-regression-c-failed-in-test.html
  // https://developercommunity.visualstudio.com/content/problem/232218/c-constexpr-string-view.html
  constexpr bool workaround = true;
#else
  constexpr bool workaround = false;
#endif

  if constexpr (!is_default_predicate<BinaryPredicate>() || workaround) {
    if (lhs.size() != rhs.size()) {
      return false;
    }

    const auto size = lhs.size();
    for (std::size_t i = 0; i < size; ++i) {
      if (!p(lhs[i], rhs[i])) {
        return false;
      }
    }

    return true;
  } else {
    return lhs == rhs;
  }
}

template <typename L, typename R>
constexpr bool cmp_less(L lhs, R rhs) noexcept {
  static_assert(std::is_integral_v<L> && std::is_integral_v<R>, "magic_enum::detail::cmp_less requires integral type.");

  if constexpr (std::is_signed_v<L> == std::is_signed_v<R>) {
    // If same signedness (both signed or both unsigned).
    return lhs < rhs;
  } else if constexpr (std::is_same_v<L, bool>) { // bool special case
      return static_cast<R>(lhs) < rhs;
  } else if constexpr (std::is_same_v<R, bool>) { // bool special case
      return lhs < static_cast<L>(rhs);
  } else if constexpr (std::is_signed_v<R>) {
    // If 'right' is negative, then result is 'false', otherwise cast & compare.
    return rhs > 0 && lhs < static_cast<std::make_unsigned_t<R>>(rhs);
  } else {
    // If 'left' is negative, then result is 'true', otherwise cast & compare.
    return lhs < 0 || static_cast<std::make_unsigned_t<L>>(lhs) < rhs;
  }
}

template <typename I>
constexpr I log2(I value) noexcept {
  static_assert(std::is_integral_v<I>, "magic_enum::detail::log2 requires integral type.");

  if constexpr (std::is_same_v<I, bool>) { // bool special case
    return MAGIC_ENUM_ASSERT(false), value;
  } else {
    auto ret = I{0};
    for (; value > I{1}; value >>= I{1}, ++ret) {}

    return ret;
  }
}

#if defined(__cpp_lib_array_constexpr) && __cpp_lib_array_constexpr >= 201603L
#  define MAGIC_ENUM_ARRAY_CONSTEXPR 1
#else
template <typename T, std::size_t N, std::size_t... I>
constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N], std::index_sequence<I...>) noexcept {
  return {{a[I]...}};
}
#endif

template <typename T>
inline constexpr bool is_enum_v = std::is_enum_v<T> && std::is_same_v<T, std::decay_t<T>>;

template <typename E>
constexpr auto n() noexcept {
  static_assert(is_enum_v<E>, "magic_enum::detail::n requires enum type.");

  if constexpr (supported<E>::value) {
#if defined(MAGIC_ENUM_GET_TYPE_NAME_BUILTIN)
    constexpr auto name_ptr = MAGIC_ENUM_GET_TYPE_NAME_BUILTIN(E);
    constexpr auto name = name_ptr ? str_view{name_ptr, std::char_traits<char>::length(name_ptr)} : str_view{};
#elif defined(__clang__)
    auto name = str_view{__PRETTY_FUNCTION__ + 34, sizeof(__PRETTY_FUNCTION__) - 36};
#elif defined(__GNUC__)
    auto name = str_view{__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 1};
    if (name.str_[name.size_ - 1] == ']') {
      name.size_ -= 50;
      name.str_ += 49;
    } else {
      name.size_ -= 40;
      name.str_ += 37;
    }
#elif defined(_MSC_VER)
    auto name = str_view{__FUNCSIG__ + 40, sizeof(__FUNCSIG__) - 57};
#else
    auto name = str_view{};
#endif
    std::size_t p = 0;
    for (std::size_t i = name.size_; i > 0; --i) {
      if (name.str_[i] == ':') {
        p = i + 1;
        break;
      }
    }
    if (p > 0) {
      name.size_ -= p;
      name.str_ += p;
    }
    return name;
  } else {
    return str_view{}; // Unsupported compiler or Invalid customize.
  }
}

template <typename E>
constexpr auto type_name() noexcept {
  [[maybe_unused]] constexpr auto custom = customize::enum_type_name<E>();
  static_assert(std::is_same_v<std::decay_t<decltype(custom)>, customize::customize_t>, "magic_enum::customize requires customize_t type.");
  if constexpr (custom.first == customize::detail::customize_tag::custom_tag) {
    constexpr auto name = custom.second;
    static_assert(!name.empty(), "magic_enum::customize requires not empty string.");
    return static_str<name.size()>{name};
  } else if constexpr (custom.first == customize::detail::customize_tag::invalid_tag) {
    return static_str<0>{};
  } else if constexpr (custom.first == customize::detail::customize_tag::default_tag) {
    constexpr auto name = n<E>();
    return static_str<name.size_>{name};
  } else {
    static_assert(always_false_v<E>, "magic_enum::customize invalid.");
  }
}

template <typename E>
inline constexpr auto type_name_v = type_name<E>();

template <auto V>
constexpr auto n() noexcept {
  static_assert(is_enum_v<decltype(V)>, "magic_enum::detail::n requires enum type.");

  if constexpr (supported<decltype(V)>::value) {
#if defined(MAGIC_ENUM_GET_ENUM_NAME_BUILTIN)
    constexpr auto name_ptr = MAGIC_ENUM_GET_ENUM_NAME_BUILTIN(V);
    auto name = name_ptr ? str_view{name_ptr, std::char_traits<char>::length(name_ptr)} : str_view{};
#elif defined(__clang__)
    auto name = str_view{__PRETTY_FUNCTION__ + 34, sizeof(__PRETTY_FUNCTION__) - 36};
    if (name.size_ > 22 && name.str_[0] == '(' && name.str_[1] == 'a' && name.str_[10] == ' ' && name.str_[22] == ':') {
      name.size_ -= 23;
      name.str_ += 23;
    }
    if (name.str_[0] == '(' || name.str_[0] == '-' || (name.str_[0] >= '0' && name.str_[0] <= '9')) {
      name = str_view{};
    }
#elif defined(__GNUC__)
    auto name = str_view{__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 1};
    if (name.str_[name.size_ - 1] == ']') {
      name.size_ -= 55;
      name.str_ += 54;
    } else {
      name.size_ -= 40;
      name.str_ += 37;
    }
    if (name.str_[0] == '(') {
      name = str_view{};
    }
#elif defined(_MSC_VER)
    str_view name;
    if ((__FUNCSIG__[5] == '_' && __FUNCSIG__[35] != '(') || (__FUNCSIG__[5] == 'c' && __FUNCSIG__[41] != '(')) {
      name = str_view{__FUNCSIG__ + 35, sizeof(__FUNCSIG__) - 52};
    }
#else
    auto name = str_view{};
#endif
    std::size_t p = 0;
    for (std::size_t i = name.size_; i > 0; --i) {
      if (name.str_[i] == ':') {
        p = i + 1;
        break;
      }
    }
    if (p > 0) {
      name.size_ -= p;
      name.str_ += p;
    }
    return name;
  } else {
    return str_view{}; // Unsupported compiler or Invalid customize.
  }
}

#if defined(_MSC_VER) && !defined(__clang__) && _MSC_VER < 1920
#  define MAGIC_ENUM_VS_2017_WORKAROUND 1
#endif

#if defined(MAGIC_ENUM_VS_2017_WORKAROUND)
template <typename E, E V>
constexpr auto n() noexcept {
  static_assert(is_enum_v<E>, "magic_enum::detail::n requires enum type.");

#  if defined(MAGIC_ENUM_GET_ENUM_NAME_BUILTIN)
  constexpr auto name_ptr = MAGIC_ENUM_GET_ENUM_NAME_BUILTIN(V);
  auto name = name_ptr ? str_view{name_ptr, std::char_traits<char>::length(name_ptr)} : str_view{};
#  else
  str_view name = str_view{__FUNCSIG__, sizeof(__FUNCSIG__) - 17};
  std::size_t p = 0;
  for (std::size_t i = name.size_; i > 0; --i) {
    if (name.str_[i] == ',' || name.str_[i] == ':') {
      p = i + 1;
      break;
    }
  }
  if (p > 0) {
    name.size_ -= p;
    name.str_ += p;
  }
  if (name.str_[0] == '(' || name.str_[0] == '-' || (name.str_[0] >= '0' && name.str_[0] <= '9')) {
    name = str_view{};
  }
  return name;
#  endif
}
#endif

template <typename E, E V>
constexpr auto enum_name() noexcept {
  [[maybe_unused]] constexpr auto custom = customize::enum_name<E>(V);
  static_assert(std::is_same_v<std::decay_t<decltype(custom)>, customize::customize_t>, "magic_enum::customize requires customize_t type.");
  if constexpr (custom.first == customize::detail::customize_tag::custom_tag) {
    constexpr auto name = custom.second;
    static_assert(!name.empty(), "magic_enum::customize requires not empty string.");
    return static_str<name.size()>{name};
  } else if constexpr (custom.first == customize::detail::customize_tag::invalid_tag) {
    return static_str<0>{};
  } else if constexpr (custom.first == customize::detail::customize_tag::default_tag) {
#if defined(MAGIC_ENUM_VS_2017_WORKAROUND)
    constexpr auto name = n<E, V>();
#else
    constexpr auto name = n<V>();
#endif
    return static_str<name.size_>{name};
  } else {
    static_assert(always_false_v<E>, "magic_enum::customize invalid.");
  }
}

template <typename E, E V>
inline constexpr auto enum_name_v = enum_name<E, V>();

template <typename E, auto V>
constexpr bool is_valid() noexcept {
#if defined(__clang__) && __clang_major__ >= 16
  // https://reviews.llvm.org/D130058, https://reviews.llvm.org/D131307
  constexpr E v = __builtin_bit_cast(E, V);
#else
  constexpr E v = static_cast<E>(V);
#endif
  [[maybe_unused]] constexpr auto custom = customize::enum_name<E>(v);
  static_assert(std::is_same_v<std::decay_t<decltype(custom)>, customize::customize_t>, "magic_enum::customize requires customize_t type.");
  if constexpr (custom.first == customize::detail::customize_tag::custom_tag) {
    constexpr auto name = custom.second;
    static_assert(!name.empty(), "magic_enum::customize requires not empty string.");
    return name.size() != 0;
  } else if constexpr (custom.first == customize::detail::customize_tag::default_tag) {
#if defined(MAGIC_ENUM_VS_2017_WORKAROUND)
    return n<E, v>().size_ != 0;
#else
    return n<v>().size_ != 0;
#endif
  } else {
    return false;
  }
}

enum class enum_subtype {
  common,
  flags
};

template <typename E, int O, enum_subtype S, typename U = std::underlying_type_t<E>>
constexpr U ualue(std::size_t i) noexcept {
  if constexpr (std::is_same_v<U, bool>) { // bool special case
    static_assert(O == 0, "magic_enum::detail::ualue requires valid offset.");

    return static_cast<U>(i);
  } else if constexpr (S == enum_subtype::flags) {
    return static_cast<U>(U{1} << static_cast<U>(static_cast<int>(i) + O));
  } else {
    return static_cast<U>(static_cast<int>(i) + O);
  }
}

template <typename E, int O, enum_subtype S, typename U = std::underlying_type_t<E>>
constexpr E value(std::size_t i) noexcept {
  return static_cast<E>(ualue<E, O, S>(i));
}

template <typename E, enum_subtype S, typename U = std::underlying_type_t<E>>
constexpr int reflected_min() noexcept {
  if constexpr (S == enum_subtype::flags) {
    return 0;
  } else {
    constexpr auto lhs = range_min<E>::value;
    constexpr auto rhs = (std::numeric_limits<U>::min)();

    if constexpr (cmp_less(rhs, lhs)) {
      return lhs;
    } else {
      return rhs;
    }
  }
}

template <typename E, enum_subtype S, typename U = std::underlying_type_t<E>>
constexpr int reflected_max() noexcept {
  if constexpr (S == enum_subtype::flags) {
    return std::numeric_limits<U>::digits - 1;
  } else {
    constexpr auto lhs = range_max<E>::value;
    constexpr auto rhs = (std::numeric_limits<U>::max)();

    if constexpr (cmp_less(lhs, rhs)) {
      return lhs;
    } else {
      return rhs;
    }
  }
}

#define MAGIC_ENUM_FOR_EACH_256(T)                                                                                                                                                                 \
  T(  0)T(  1)T(  2)T(  3)T(  4)T(  5)T(  6)T(  7)T(  8)T(  9)T( 10)T( 11)T( 12)T( 13)T( 14)T( 15)T( 16)T( 17)T( 18)T( 19)T( 20)T( 21)T( 22)T( 23)T( 24)T( 25)T( 26)T( 27)T( 28)T( 29)T( 30)T( 31) \
  T( 32)T( 33)T( 34)T( 35)T( 36)T( 37)T( 38)T( 39)T( 40)T( 41)T( 42)T( 43)T( 44)T( 45)T( 46)T( 47)T( 48)T( 49)T( 50)T( 51)T( 52)T( 53)T( 54)T( 55)T( 56)T( 57)T( 58)T( 59)T( 60)T( 61)T( 62)T( 63) \
  T( 64)T( 65)T( 66)T( 67)T( 68)T( 69)T( 70)T( 71)T( 72)T( 73)T( 74)T( 75)T( 76)T( 77)T( 78)T( 79)T( 80)T( 81)T( 82)T( 83)T( 84)T( 85)T( 86)T( 87)T( 88)T( 89)T( 90)T( 91)T( 92)T( 93)T( 94)T( 95) \
  T( 96)T( 97)T( 98)T( 99)T(100)T(101)T(102)T(103)T(104)T(105)T(106)T(107)T(108)T(109)T(110)T(111)T(112)T(113)T(114)T(115)T(116)T(117)T(118)T(119)T(120)T(121)T(122)T(123)T(124)T(125)T(126)T(127) \
  T(128)T(129)T(130)T(131)T(132)T(133)T(134)T(135)T(136)T(137)T(138)T(139)T(140)T(141)T(142)T(143)T(144)T(145)T(146)T(147)T(148)T(149)T(150)T(151)T(152)T(153)T(154)T(155)T(156)T(157)T(158)T(159) \
  T(160)T(161)T(162)T(163)T(164)T(165)T(166)T(167)T(168)T(169)T(170)T(171)T(172)T(173)T(174)T(175)T(176)T(177)T(178)T(179)T(180)T(181)T(182)T(183)T(184)T(185)T(186)T(187)T(188)T(189)T(190)T(191) \
  T(192)T(193)T(194)T(195)T(196)T(197)T(198)T(199)T(200)T(201)T(202)T(203)T(204)T(205)T(206)T(207)T(208)T(209)T(210)T(211)T(212)T(213)T(214)T(215)T(216)T(217)T(218)T(219)T(220)T(221)T(222)T(223) \
  T(224)T(225)T(226)T(227)T(228)T(229)T(230)T(231)T(232)T(233)T(234)T(235)T(236)T(237)T(238)T(239)T(240)T(241)T(242)T(243)T(244)T(245)T(246)T(247)T(248)T(249)T(250)T(251)T(252)T(253)T(254)T(255)

template <typename E, enum_subtype S, std::size_t Size, int Min, std::size_t I>
constexpr void valid_count(bool* valid, std::size_t& count) noexcept {
#define MAGIC_ENUM_V(O)                                     \
  if constexpr ((I + O) < Size) {                           \
    if constexpr (is_valid<E, ualue<E, Min, S>(I + O)>()) { \
      valid[I + O] = true;                                  \
      ++count;                                              \
    }                                                       \
  }

  MAGIC_ENUM_FOR_EACH_256(MAGIC_ENUM_V);

  if constexpr ((I + 256) < Size) {
    valid_count<E, S, Size, Min, I + 256>(valid, count);
  }
#undef MAGIC_ENUM_V
}

template <std::size_t N>
struct valid_count_t {
  std::size_t count = 0;
  bool valid[N] = {};
};

template <typename E, enum_subtype S, std::size_t Size, int Min>
constexpr auto valid_count() noexcept {
  valid_count_t<Size> vc;
  valid_count<E, S, Size, Min, 0>(vc.valid, vc.count);
  return vc;
}

template <typename E, enum_subtype S, std::size_t Size, int Min>
constexpr auto values() noexcept {
  constexpr auto vc = valid_count<E, S, Size, Min>();

  if constexpr (vc.count > 0) {
#if defined(MAGIC_ENUM_ARRAY_CONSTEXPR)
    std::array<E, vc.count> values = {};
#else
    E values[vc.count] = {};
#endif
    for (std::size_t i = 0, v = 0; v < vc.count; ++i) {
      if (vc.valid[i]) {
        values[v++] = value<E, Min, S>(i);
      }
    }
#if defined(MAGIC_ENUM_ARRAY_CONSTEXPR)
    return values;
#else
    return to_array(values, std::make_index_sequence<vc.count>{});
#endif
  } else {
    return std::array<E, 0>{};
  }
}

template <typename E, enum_subtype S, typename U = std::underlying_type_t<E>>
constexpr auto values() noexcept {
  constexpr auto min = reflected_min<E, S>();
  constexpr auto max = reflected_max<E, S>();
  constexpr auto range_size = max - min + 1;
  static_assert(range_size > 0, "magic_enum::enum_range requires valid size.");
  static_assert(range_size < (std::numeric_limits<std::uint16_t>::max)(), "magic_enum::enum_range requires valid size.");

  return values<E, S, range_size, min>();
}

template <typename E, typename U = std::underlying_type_t<E>>
constexpr enum_subtype subtype(std::true_type) noexcept {
  if constexpr (std::is_same_v<U, bool>) { // bool special case
    return enum_subtype::common;
  } else if constexpr (has_is_flags<E>::value) {
    return customize::enum_range<E>::is_flags ? enum_subtype::flags : enum_subtype::common;
  } else {
#if defined(MAGIC_ENUM_AUTO_IS_FLAGS)
    constexpr auto flags_values = values<E, enum_subtype::flags>();
    constexpr auto default_values = values<E, enum_subtype::common>();
    if (flags_values.size() == 0 || default_values.size() > flags_values.size()) {
      return enum_subtype::common;
    }
    for (std::size_t i = 0; i < default_values.size(); ++i) {
      const auto v = static_cast<U>(default_values[i]);
      if (v != 0 && (v & (v - 1)) != 0) {
        return enum_subtype::common;
      }
    }
    return enum_subtype::flags;
#else
    return enum_subtype::common;
#endif
  }
}

template <typename T>
constexpr enum_subtype subtype(std::false_type) noexcept {
  // For non-enum type return default common subtype.
  return enum_subtype::common;
}

template <typename E, typename D = std::decay_t<E>>
inline constexpr auto subtype_v = subtype<D>(std::is_enum<D>{});

template <typename E, enum_subtype S>
inline constexpr auto values_v = values<E, S>();

template <typename E, enum_subtype S, typename D = std::decay_t<E>>
using values_t = decltype((values_v<D, S>));

template <typename E, enum_subtype S>
inline constexpr auto count_v = values_v<E, S>.size();

template <typename E, enum_subtype S, typename U = std::underlying_type_t<E>>
inline constexpr auto min_v = (count_v<E, S> > 0) ? static_cast<U>(values_v<E, S>.front()) : U{0};

template <typename E, enum_subtype S, typename U = std::underlying_type_t<E>>
inline constexpr auto max_v = (count_v<E, S> > 0) ? static_cast<U>(values_v<E, S>.back()) : U{0};

template <typename E, enum_subtype S, std::size_t... I>
constexpr auto names(std::index_sequence<I...>) noexcept {
  return std::array<string_view, sizeof...(I)>{{enum_name_v<E, values_v<E, S>[I]>...}};
}

template <typename E, enum_subtype S>
inline constexpr auto names_v = names<E, S>(std::make_index_sequence<count_v<E, S>>{});

template <typename E, enum_subtype S, typename D = std::decay_t<E>>
using names_t = decltype((names_v<D, S>));

template <typename E, enum_subtype S, std::size_t... I>
constexpr auto entries(std::index_sequence<I...>) noexcept {
  return std::array<std::pair<E, string_view>, sizeof...(I)>{{{values_v<E, S>[I], enum_name_v<E, values_v<E, S>[I]>}...}};
}

template <typename E, enum_subtype S>
inline constexpr auto entries_v = entries<E, S>(std::make_index_sequence<count_v<E, S>>{});

template <typename E, enum_subtype S, typename D = std::decay_t<E>>
using entries_t = decltype((entries_v<D, S>));

template <typename E, enum_subtype S, typename U = std::underlying_type_t<E>>
constexpr bool is_sparse() noexcept {
  if constexpr (count_v<E, S> == 0) {
    return false;
  } else if constexpr (std::is_same_v<U, bool>) { // bool special case
    return false;
  } else {
    constexpr auto max = (S == enum_subtype::flags) ? log2(max_v<E, S>) : max_v<E, S>;
    constexpr auto min = (S == enum_subtype::flags) ? log2(min_v<E, S>) : min_v<E, S>;
    constexpr auto range_size = max - min + 1;

    return range_size != count_v<E, S>;
  }
}

template <typename E, enum_subtype S = subtype_v<E>>
inline constexpr bool is_sparse_v = is_sparse<E, S>();

template <typename E, enum_subtype S, typename U = std::underlying_type_t<E>>
constexpr U values_ors() noexcept {
  static_assert(S == enum_subtype::flags, "magic_enum::detail::values_ors requires valid subtype.");

  auto ors = U{0};
  for (std::size_t i = 0; i < count_v<E, S>; ++i) {
    ors |= static_cast<U>(values_v<E, S>[i]);
  }

  return ors;
}

template <bool, typename R>
struct enable_if_enum {};

template <typename R>
struct enable_if_enum<true, R> {
  using type = R;
  static_assert(supported<R>::value, "magic_enum unsupported compiler (https://github.com/Neargye/magic_enum#compiler-compatibility).");
};

template <typename T, typename R, typename BinaryPredicate = std::equal_to<>, typename D = std::decay_t<T>>
using enable_if_t = typename enable_if_enum<std::is_enum_v<D> && std::is_invocable_r_v<bool, BinaryPredicate, char_type, char_type>, R>::type;

template <typename T, std::enable_if_t<std::is_enum_v<std::decay_t<T>>, int> = 0>
using enum_concept = T;

template <typename T, bool = std::is_enum_v<T>>
struct is_scoped_enum : std::false_type {};

template <typename T>
struct is_scoped_enum<T, true> : std::bool_constant<!std::is_convertible_v<T, std::underlying_type_t<T>>> {};

template <typename T, bool = std::is_enum_v<T>>
struct is_unscoped_enum : std::false_type {};

template <typename T>
struct is_unscoped_enum<T, true> : std::bool_constant<std::is_convertible_v<T, std::underlying_type_t<T>>> {};

template <typename T, bool = std::is_enum_v<std::decay_t<T>>>
struct underlying_type {};

template <typename T>
struct underlying_type<T, true> : std::underlying_type<std::decay_t<T>> {};

#if defined(MAGIC_ENUM_ENABLE_HASH) || defined(MAGIC_ENUM_ENABLE_HASH_SWITCH)

template <typename Value, typename = void>
struct constexpr_hash_t;

template <typename Value>
struct constexpr_hash_t<Value, std::enable_if_t<is_enum_v<Value>>> {
  constexpr auto operator()(Value value) const noexcept {
    using U = typename underlying_type<Value>::type;
    if constexpr (std::is_same_v<U, bool>) { // bool special case
      return static_cast<std::size_t>(value);
    } else {
      return static_cast<U>(value);
    }
  }
  using secondary_hash = constexpr_hash_t;
};

template <typename Value>
struct constexpr_hash_t<Value, std::enable_if_t<std::is_same_v<Value, string_view>>> {
  static constexpr std::uint32_t crc_table[256] {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
    0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
    0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL, 0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
    0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
    0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
    0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
    0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
    0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L, 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
    0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
    0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
    0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
    0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
    0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
    0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
    0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
    0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
    0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
    0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L, 0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
    0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
    0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
    0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
    0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
    0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L, 0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
    0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
    0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
    0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
    0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
    0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL, 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
    0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
    0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
    0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
    0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
  };
  constexpr std::uint32_t operator()(string_view value) const noexcept {
    auto crc = static_cast<std::uint32_t>(0xffffffffL);
    for (const auto c : value) {
      crc = (crc >> 8) ^ crc_table[(crc ^ static_cast<std::uint32_t>(c)) & 0xff];
    }
    return crc ^ 0xffffffffL;
  }

  struct secondary_hash {
    constexpr std::uint32_t operator()(string_view value) const noexcept {
      auto acc = static_cast<std::uint64_t>(2166136261ULL);
      for (const auto c : value) {
        acc = ((acc ^ static_cast<std::uint64_t>(c)) * static_cast<std::uint64_t>(16777619ULL)) & (std::numeric_limits<std::uint32_t>::max)();
      }
      return static_cast<std::uint32_t>(acc);
    }
  };
};

template <typename Hash>
inline constexpr Hash hash_v{};

template <auto* GlobValues, typename Hash>
constexpr auto calculate_cases(std::size_t Page) noexcept {
  constexpr std::array values = *GlobValues;
  constexpr std::size_t size = values.size();

  using switch_t = std::invoke_result_t<Hash, typename decltype(values)::value_type>;
  static_assert(std::is_integral_v<switch_t> && !std::is_same_v<switch_t, bool>);
  const std::size_t values_to = (std::min)(static_cast<std::size_t>(256), size - Page);

  std::array<switch_t, 256> result{};
  auto fill = result.begin();
  {
    auto first = values.begin() + static_cast<std::ptrdiff_t>(Page);
    auto last = values.begin() + static_cast<std::ptrdiff_t>(Page + values_to);
    while (first != last) {
      *fill++ = hash_v<Hash>(*first++);
    }
  }

  // dead cases, try to avoid case collisions
  for (switch_t last_value = result[values_to - 1]; fill != result.end() && last_value != (std::numeric_limits<switch_t>::max)(); *fill++ = ++last_value) {
  }

  {
    auto it = result.begin();
    auto last_value = (std::numeric_limits<switch_t>::min)();
    for (; fill != result.end(); *fill++ = last_value++) {
      while (last_value == *it) {
        ++last_value, ++it;
      }
    }
  }

  return result;
}

template <typename R, typename F, typename... Args>
constexpr R invoke_r(F&& f, Args&&... args) noexcept(std::is_nothrow_invocable_r_v<R, F, Args...>) {
  if constexpr (std::is_void_v<R>) {
    std::forward<F>(f)(std::forward<Args>(args)...);
  } else {
    return static_cast<R>(std::forward<F>(f)(std::forward<Args>(args)...));
  }
}

enum class case_call_t {
  index,
  value
};

template <typename T = void>
inline constexpr auto default_result_type_lambda = []() noexcept(std::is_nothrow_default_constructible_v<T>) { return T{}; };

template <>
inline constexpr auto default_result_type_lambda<void> = []() noexcept {};

template <auto* Arr, typename Hash>
constexpr bool has_duplicate() noexcept {
  using value_t = std::decay_t<decltype((*Arr)[0])>;
  using hash_value_t = std::invoke_result_t<Hash, value_t>;
  std::array<hash_value_t, Arr->size()> hashes{};
  std::size_t size = 0;
  for (auto elem : *Arr) {
    hashes[size] = hash_v<Hash>(elem);
    for (auto i = size++; i > 0; --i) {
      if (hashes[i] < hashes[i - 1]) {
        auto tmp = hashes[i];
        hashes[i] = hashes[i - 1];
        hashes[i - 1] = tmp;
      } else if (hashes[i] == hashes[i - 1]) {
        return false;
      } else {
        break;
      }
    }
  }
  return true;
}

#define MAGIC_ENUM_CASE(val)                                                                                                  \
  case cases[val]:                                                                                                            \
    if constexpr ((val) + Page < size) {                                                                                      \
      if (!pred(values[val + Page], searched)) {                                                                              \
        break;                                                                                                                \
      }                                                                                                                       \
      if constexpr (CallValue == case_call_t::index) {                                                                        \
        if constexpr (std::is_invocable_r_v<result_t, Lambda, std::integral_constant<std::size_t, val + Page>>) {             \
          return detail::invoke_r<result_t>(std::forward<Lambda>(lambda), std::integral_constant<std::size_t, val + Page>{}); \
        } else if constexpr (std::is_invocable_v<Lambda, std::integral_constant<std::size_t, val + Page>>) {                  \
          MAGIC_ENUM_ASSERT(false && "magic_enum::detail::constexpr_switch wrong result type.");                                         \
        }                                                                                                                     \
      } else if constexpr (CallValue == case_call_t::value) {                                                                 \
        if constexpr (std::is_invocable_r_v<result_t, Lambda, enum_constant<values[val + Page]>>) {                           \
          return detail::invoke_r<result_t>(std::forward<Lambda>(lambda), enum_constant<values[val + Page]>{});               \
        } else if constexpr (std::is_invocable_r_v<result_t, Lambda, enum_constant<values[val + Page]>>) {                    \
          MAGIC_ENUM_ASSERT(false && "magic_enum::detail::constexpr_switch wrong result type.");                                         \
        }                                                                                                                     \
      }                                                                                                                       \
      break;                                                                                                                  \
    } else [[fallthrough]];

template <auto* GlobValues,
          case_call_t CallValue,
          std::size_t Page = 0,
          typename Hash = constexpr_hash_t<typename std::decay_t<decltype(*GlobValues)>::value_type>,
          typename BinaryPredicate = std::equal_to<>,
          typename Lambda,
          typename ResultGetterType>
constexpr decltype(auto) constexpr_switch(
    Lambda&& lambda,
    typename std::decay_t<decltype(*GlobValues)>::value_type searched,
    ResultGetterType&& def,
    BinaryPredicate&& pred = {}) {
  using result_t = std::invoke_result_t<ResultGetterType>;
  using hash_t = std::conditional_t<has_duplicate<GlobValues, Hash>(), Hash, typename Hash::secondary_hash>;
  static_assert(has_duplicate<GlobValues, hash_t>(), "magic_enum::detail::constexpr_switch duplicated hash found, please report it: https://github.com/Neargye/magic_enum/issues.");
  constexpr std::array values = *GlobValues;
  constexpr std::size_t size = values.size();
  constexpr std::array cases = calculate_cases<GlobValues, hash_t>(Page);

  switch (hash_v<hash_t>(searched)) {
    MAGIC_ENUM_FOR_EACH_256(MAGIC_ENUM_CASE)
    default:
      if constexpr (size > 256 + Page) {
        return constexpr_switch<GlobValues, CallValue, Page + 256, Hash>(std::forward<Lambda>(lambda), searched, std::forward<ResultGetterType>(def));
      }
      break;
  }
  return def();
}

#undef MAGIC_ENUM_CASE

#endif

} // namespace magic_enum::detail

// Checks is magic_enum supported compiler.
inline constexpr bool is_magic_enum_supported = detail::supported<void>::value;

template <typename T>
using Enum = detail::enum_concept<T>;

// Checks whether T is an Unscoped enumeration type.
// Provides the member constant value which is equal to true, if T is an [Unscoped enumeration](https://en.cppreference.com/w/cpp/language/enum#Unscoped_enumeration) type. Otherwise, value is equal to false.
template <typename T>
struct is_unscoped_enum : detail::is_unscoped_enum<T> {};

template <typename T>
inline constexpr bool is_unscoped_enum_v = is_unscoped_enum<T>::value;

// Checks whether T is an Scoped enumeration type.
// Provides the member constant value which is equal to true, if T is an [Scoped enumeration](https://en.cppreference.com/w/cpp/language/enum#Scoped_enumerations) type. Otherwise, value is equal to false.
template <typename T>
struct is_scoped_enum : detail::is_scoped_enum<T> {};

template <typename T>
inline constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;

// If T is a complete enumeration type, provides a member typedef type that names the underlying type of T.
// Otherwise, if T is not an enumeration type, there is no member type. Otherwise (T is an incomplete enumeration type), the program is ill-formed.
template <typename T>
struct underlying_type : detail::underlying_type<T> {};

template <typename T>
using underlying_type_t = typename underlying_type<T>::type;

template <auto V>
using enum_constant = detail::enum_constant<V>;

// Returns type name of enum.
template <typename E>
[[nodiscard]] constexpr auto enum_type_name() noexcept -> detail::enable_if_t<E, string_view> {
  constexpr string_view name = detail::type_name_v<std::decay_t<E>>;
  static_assert(!name.empty(), "magic_enum::enum_type_name enum type does not have a name.");

  return name;
}

// Returns number of enum values.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_count() noexcept -> detail::enable_if_t<E, std::size_t> {
  return detail::count_v<std::decay_t<E>, S>;
}

// Returns enum value at specified index.
// No bounds checking is performed: the behavior is undefined if index >= number of enum values.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_value(std::size_t index) noexcept -> detail::enable_if_t<E, std::decay_t<E>> {
  using D = std::decay_t<E>;

  if constexpr (detail::is_sparse_v<D, S>) {
    return MAGIC_ENUM_ASSERT(index < detail::count_v<D, S>), detail::values_v<D, S>[index];
  } else {
    constexpr auto min = (S == detail::enum_subtype::flags) ? detail::log2(detail::min_v<D, S>) : detail::min_v<D, S>;

    return MAGIC_ENUM_ASSERT(index < detail::count_v<D, S>), detail::value<D, min, S>(index);
  }
}

// Returns enum value at specified index.
template <typename E, std::size_t I, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_value() noexcept -> detail::enable_if_t<E, std::decay_t<E>> {
  using D = std::decay_t<E>;
  static_assert(I < detail::count_v<D, S>, "magic_enum::enum_value out of range.");

  return enum_value<D, S>(I);
}

// Returns std::array with enum values, sorted by enum value.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_values() noexcept -> detail::enable_if_t<E, detail::values_t<E, S>> {
  return detail::values_v<std::decay_t<E>, S>;
}

// Returns integer value from enum value.
template <typename E>
[[nodiscard]] constexpr auto enum_integer(E value) noexcept -> detail::enable_if_t<E, underlying_type_t<E>> {
  return static_cast<underlying_type_t<E>>(value);
}

// Returns underlying value from enum value.
template <typename E>
[[nodiscard]] constexpr auto enum_underlying(E value) noexcept -> detail::enable_if_t<E, underlying_type_t<E>> {
  return static_cast<underlying_type_t<E>>(value);
}

// Obtains index in enum values from enum value.
// Returns optional with index.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_index(E value) noexcept -> detail::enable_if_t<E, optional<std::size_t>> {
  using D = std::decay_t<E>;
  using U = underlying_type_t<D>;

  if constexpr (detail::count_v<D, S> == 0) {
    static_cast<void>(value);
    return {}; // Empty enum.
  } else if constexpr (detail::is_sparse_v<D, S> || (S == detail::enum_subtype::flags)) {
#if defined(MAGIC_ENUM_ENABLE_HASH)
    return detail::constexpr_switch<&detail::values_v<D, S>, detail::case_call_t::index>(
        [](std::size_t i) { return optional<std::size_t>{i}; },
        value,
        detail::default_result_type_lambda<optional<std::size_t>>);
#else
    for (std::size_t i = 0; i < detail::count_v<D, S>; ++i) {
      if (enum_value<D, S>(i) == value) {
        return i;
      }
    }
    return {}; // Invalid value or out of range.
#endif
  } else {
    const auto v = static_cast<U>(value);
    if (v >= detail::min_v<D, S> && v <= detail::max_v<D, S>) {
      return static_cast<std::size_t>(v - detail::min_v<D, S>);
    }
    return {}; // Invalid value or out of range.
  }
}

// Obtains index in enum values from enum value.
// Returns optional with index.
template <detail::enum_subtype S, typename E>
[[nodiscard]] constexpr auto enum_index(E value) noexcept -> detail::enable_if_t<E, optional<std::size_t>> {
  using D = std::decay_t<E>;

  return enum_index<D, S>(value);
}

// Obtains index in enum values from static storage enum variable.
template <auto V, detail::enum_subtype S = detail::subtype_v<std::decay_t<decltype(V)>>>
[[nodiscard]] constexpr auto enum_index() noexcept -> detail::enable_if_t<decltype(V), std::size_t> {
  constexpr auto index = enum_index<std::decay_t<decltype(V)>, S>(V);
  static_assert(index, "magic_enum::enum_index enum value does not have a index.");

  return *index;
}

// Returns name from static storage enum variable.
// This version is much lighter on the compile times and is not restricted to the enum_range limitation.
template <auto V>
[[nodiscard]] constexpr auto enum_name() noexcept -> detail::enable_if_t<decltype(V), string_view> {
  constexpr string_view name = detail::enum_name_v<std::decay_t<decltype(V)>, V>;
  static_assert(!name.empty(), "magic_enum::enum_name enum value does not have a name.");

  return name;
}

// Returns name from enum value.
// If enum value does not have name or value out of range, returns empty string.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_name(E value) noexcept -> detail::enable_if_t<E, string_view> {
  using D = std::decay_t<E>;

  if (const auto i = enum_index<D, S>(value)) {
    return detail::names_v<D, S>[*i];
  }
  return {};
}

// Returns name from enum value.
// If enum value does not have name or value out of range, returns empty string.
template <detail::enum_subtype S, typename E>
[[nodiscard]] constexpr auto enum_name(E value) -> detail::enable_if_t<E, string_view> {
  using D = std::decay_t<E>;

  return enum_name<D, S>(value);
}

// Returns std::array with names, sorted by enum value.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_names() noexcept -> detail::enable_if_t<E, detail::names_t<E, S>> {
  return detail::names_v<std::decay_t<E>, S>;
}

// Returns std::array with pairs (value, name), sorted by enum value.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_entries() noexcept -> detail::enable_if_t<E, detail::entries_t<E, S>> {
  return detail::entries_v<std::decay_t<E>, S>;
}

// Allows you to write magic_enum::enum_cast<foo>("bar", magic_enum::case_insensitive);
inline constexpr auto case_insensitive = detail::case_insensitive<>{};

// Obtains enum value from integer value.
// Returns optional with enum value.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_cast(underlying_type_t<E> value) noexcept -> detail::enable_if_t<E, optional<std::decay_t<E>>> {
  using D = std::decay_t<E>;

  if constexpr (detail::count_v<D, S> == 0) {
    static_cast<void>(value);
    return {}; // Empty enum.
  } else {
    if constexpr (detail::is_sparse_v<D, S> || (S == detail::enum_subtype::flags)) {
#if defined(MAGIC_ENUM_ENABLE_HASH)
      return detail::constexpr_switch<&detail::values_v<D, S>, detail::case_call_t::value>(
          [](D v) { return optional<D>{v}; },
          static_cast<D>(value),
          detail::default_result_type_lambda<optional<D>>);
#else
      for (std::size_t i = 0; i < detail::count_v<D, S>; ++i) {
        if (value == static_cast<underlying_type_t<D>>(enum_value<D, S>(i))) {
          return static_cast<D>(value);
        }
      }
      return {}; // Invalid value or out of range.
#endif
    } else {
      if (value >= detail::min_v<D, S> && value <= detail::max_v<D, S>) {
        return static_cast<D>(value);
      }
      return {}; // Invalid value or out of range.
    }
  }
}

// Obtains enum value from name.
// Returns optional with enum value.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>, typename BinaryPredicate = std::equal_to<>>
[[nodiscard]] constexpr auto enum_cast(string_view value, [[maybe_unused]] BinaryPredicate p = {}) noexcept(detail::is_nothrow_invocable<BinaryPredicate>()) -> detail::enable_if_t<E, optional<std::decay_t<E>>, BinaryPredicate> {
  using D = std::decay_t<E>;

  if constexpr (detail::count_v<D, S> == 0) {
    static_cast<void>(value);
    return {}; // Empty enum.
#if defined(MAGIC_ENUM_ENABLE_HASH)
    } else if constexpr (detail::is_default_predicate<BinaryPredicate>()) {
      return detail::constexpr_switch<&detail::names_v<D, S>, detail::case_call_t::index>(
          [](std::size_t i) { return optional<D>{detail::values_v<D, S>[i]}; },
          value,
          detail::default_result_type_lambda<optional<D>>,
          [&p](string_view lhs, string_view rhs) { return detail::cmp_equal(lhs, rhs, p); });
#endif
    } else {
    for (std::size_t i = 0; i < detail::count_v<D, S>; ++i) {
      if (detail::cmp_equal(value, detail::names_v<D, S>[i], p)) {
        return enum_value<D, S>(i);
      }
    }
    return {}; // Invalid value or out of range.
  }
}

// Checks whether enum contains value with such value.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_contains(E value) noexcept -> detail::enable_if_t<E, bool> {
  using D = std::decay_t<E>;
  using U = underlying_type_t<D>;

  return static_cast<bool>(enum_cast<D, S>(static_cast<U>(value)));
}

// Checks whether enum contains value with such value.
template <detail::enum_subtype S, typename E>
[[nodiscard]] constexpr auto enum_contains(E value) noexcept -> detail::enable_if_t<E, bool> {
  using D = std::decay_t<E>;
  using U = underlying_type_t<D>;

  return static_cast<bool>(enum_cast<D, S>(static_cast<U>(value)));
}

// Checks whether enum contains value with such integer value.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_contains(underlying_type_t<E> value) noexcept -> detail::enable_if_t<E, bool> {
  using D = std::decay_t<E>;

  return static_cast<bool>(enum_cast<D, S>(value));
}

// Checks whether enum contains enumerator with such name.
template <typename E, detail::enum_subtype S = detail::subtype_v<E>, typename BinaryPredicate = std::equal_to<>>
[[nodiscard]] constexpr auto enum_contains(string_view value, BinaryPredicate p = {}) noexcept(detail::is_nothrow_invocable<BinaryPredicate>()) -> detail::enable_if_t<E, bool, BinaryPredicate> {
  using D = std::decay_t<E>;

  return static_cast<bool>(enum_cast<D, S>(value, std::move(p)));
}

template <bool AsFlags = true>
inline constexpr auto as_flags = AsFlags ? detail::enum_subtype::flags : detail::enum_subtype::common;

template <bool AsFlags = true>
inline constexpr auto as_common = AsFlags ? detail::enum_subtype::common : detail::enum_subtype::flags;

namespace bitwise_operators {

template <typename E, detail::enable_if_t<E, int> = 0>
constexpr E operator~(E rhs) noexcept {
  return static_cast<E>(~static_cast<underlying_type_t<E>>(rhs));
}

template <typename E, detail::enable_if_t<E, int> = 0>
constexpr E operator|(E lhs, E rhs) noexcept {
  return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) | static_cast<underlying_type_t<E>>(rhs));
}

template <typename E, detail::enable_if_t<E, int> = 0>
constexpr E operator&(E lhs, E rhs) noexcept {
  return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) & static_cast<underlying_type_t<E>>(rhs));
}

template <typename E, detail::enable_if_t<E, int> = 0>
constexpr E operator^(E lhs, E rhs) noexcept {
  return static_cast<E>(static_cast<underlying_type_t<E>>(lhs) ^ static_cast<underlying_type_t<E>>(rhs));
}

template <typename E, detail::enable_if_t<E, int> = 0>
constexpr E& operator|=(E& lhs, E rhs) noexcept {
  return lhs = (lhs | rhs);
}

template <typename E, detail::enable_if_t<E, int> = 0>
constexpr E& operator&=(E& lhs, E rhs) noexcept {
  return lhs = (lhs & rhs);
}

template <typename E, detail::enable_if_t<E, int> = 0>
constexpr E& operator^=(E& lhs, E rhs) noexcept {
  return lhs = (lhs ^ rhs);
}

} // namespace magic_enum::bitwise_operators

} // namespace magic_enum

#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  pragma GCC diagnostic pop
#elif defined(_MSC_VER)
#  pragma warning(pop)
#endif

#undef MAGIC_ENUM_GET_ENUM_NAME_BUILTIN
#undef MAGIC_ENUM_GET_TYPE_NAME_BUILTIN
#undef MAGIC_ENUM_VS_2017_WORKAROUND
#undef MAGIC_ENUM_ARRAY_CONSTEXPR
#undef MAGIC_ENUM_FOR_EACH_256

#endif // NEARGYE_MAGIC_ENUM_HPP

// #include <magic_enum_utility.hpp>
//  __  __             _        ______                          _____
// |  \/  |           (_)      |  ____|                        / ____|_     _
// | \  / | __ _  __ _ _  ___  | |__   _ __  _   _ _ __ ___   | |   _| |_ _| |_
// | |\/| |/ _` |/ _` | |/ __| |  __| | '_ \| | | | '_ ` _ \  | |  |_   _|_   _|
// | |  | | (_| | (_| | | (__  | |____| | | | |_| | | | | | | | |____|_|   |_|
// |_|  |_|\__,_|\__, |_|\___| |______|_| |_|\__,_|_| |_| |_|  \_____|
//                __/ | https://github.com/Neargye/magic_enum
//               |___/  version 0.9.3
//
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 - 2023 Daniil Goncharov <neargye@gmail.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef NEARGYE_MAGIC_ENUM_UTILITY_HPP
#define NEARGYE_MAGIC_ENUM_UTILITY_HPP

// #include "magic_enum.hpp"


namespace magic_enum {

namespace detail {

template <typename E, enum_subtype S, typename F, std::size_t... I>
constexpr auto for_each(F&& f, std::index_sequence<I...>) {
  constexpr bool has_void_return = (std::is_void_v<std::invoke_result_t<F, enum_constant<values_v<E, S>[I]>>> || ...);
  constexpr bool all_same_return = (std::is_same_v<std::invoke_result_t<F, enum_constant<values_v<E, S>[0]>>, std::invoke_result_t<F, enum_constant<values_v<E, S>[I]>>> && ...);

  if constexpr (has_void_return) {
    (f(enum_constant<values_v<E, S>[I]>{}), ...);
  } else if constexpr (all_same_return) {
    return std::array{f(enum_constant<values_v<E, S>[I]>{})...};
  } else {
    return std::tuple{f(enum_constant<values_v<E, S>[I]>{})...};
  }
}

template <typename E, enum_subtype S, typename F,std::size_t... I>
constexpr bool all_invocable(std::index_sequence<I...>) {
  if constexpr (count_v<E, S> == 0) {
    return false;
  } else {
    return (std::is_invocable_v<F, enum_constant<values_v<E, S>[I]>> && ...);
  }
}

} // namespace magic_enum::detail

template <typename E, detail::enum_subtype S = detail::subtype_v<E>, typename F, detail::enable_if_t<E, int> = 0>
constexpr auto enum_for_each(F&& f) {
  using D = std::decay_t<E>;
  static_assert(std::is_enum_v<D>, "magic_enum::enum_for_each requires enum type.");
  constexpr auto sep = std::make_index_sequence<detail::count_v<D, S>>{};

  if constexpr (detail::all_invocable<D, S, F>(sep)) {
    return detail::for_each<D, S>(std::forward<F>(f), sep);
  } else {
    static_assert(detail::always_false_v<D>, "magic_enum::enum_for_each requires invocable of all enum value.");
  }
}

template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_next_value(E value, std::ptrdiff_t n = 1) noexcept -> detail::enable_if_t<E, optional<std::decay_t<E>>> {
  using D = std::decay_t<E>;
  constexpr std::ptrdiff_t count = detail::count_v<D, S>;

  if (const auto i = enum_index<D, S>(value)) {
    const std::ptrdiff_t index = (static_cast<std::ptrdiff_t>(*i) + n);
    if (index >= 0 && index < count) {
      return enum_value<D, S>(index);
    }
  }
  return {};
}

template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_next_value_circular(E value, std::ptrdiff_t n = 1) noexcept -> detail::enable_if_t<E, std::decay_t<E>> {
  using D = std::decay_t<E>;
  constexpr std::ptrdiff_t count = detail::count_v<D, S>;

  if (const auto i = enum_index<D, S>(value)) {
    const std::ptrdiff_t index = ((((static_cast<std::ptrdiff_t>(*i) + n) % count) + count) % count);
    if (index >= 0 && index < count) {
      return enum_value<D, S>(index);
    }
  }
  return MAGIC_ENUM_ASSERT(false), value;
}

template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_prev_value(E value, std::ptrdiff_t n = 1) noexcept -> detail::enable_if_t<E, optional<std::decay_t<E>>> {
  using D = std::decay_t<E>;
  constexpr std::ptrdiff_t count = detail::count_v<D, S>;

  if (const auto i = enum_index<D, S>(value)) {
    const std::ptrdiff_t index = (static_cast<std::ptrdiff_t>(*i) - n);
    if (index >= 0 && index < count) {
      return enum_value<D, S>(index);
    }
  }
  return {};
}

template <typename E, detail::enum_subtype S = detail::subtype_v<E>>
[[nodiscard]] constexpr auto enum_prev_value_circular(E value, std::ptrdiff_t n = 1) noexcept -> detail::enable_if_t<E, std::decay_t<E>> {
  using D = std::decay_t<E>;
  constexpr std::ptrdiff_t count = detail::count_v<D, S>;

  if (const auto i = enum_index<D, S>(value)) {
    const std::ptrdiff_t index = ((((static_cast<std::ptrdiff_t>(*i) - n) % count) + count) % count);
    if (index >= 0 && index < count) {
      return enum_value<D, S>(index);
    }
  }
  return MAGIC_ENUM_ASSERT(false), value;
}

} // namespace magic_enum

#endif // NEARGYE_MAGIC_ENUM_UTILITY_HPP

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#endif // GNURADIO_REFLECTION_HPP

// #include "Tag.hpp"
#ifndef GNURADIO_TAG_HPP
#define GNURADIO_TAG_HPP

#include <map>

// #include <pmtv/pmt.hpp>


// #include <gnuradio-4.0/meta/utils.hpp>


// #include "reflection.hpp"


#ifdef __cpp_lib_hardware_interference_size
using std::hardware_constructive_interference_size;
using std::hardware_destructive_interference_size;
#else
inline constexpr std::size_t hardware_destructive_interference_size  = 64;
inline constexpr std::size_t hardware_constructive_interference_size = 64;
#endif

#ifdef __EMSCRIPTEN__
// constexpr for cases where emscripten does not yet support constexpr and has to fall back to static const or nothing
#define EM_CONSTEXPR
#define EM_CONSTEXPR_STATIC static const
#else
#define EM_CONSTEXPR constexpr
#define EM_CONSTEXPR_STATIC constexpr
#endif

namespace gr {

/***
 * Controls automatic propagation of stream tags on sync ports.
 *       ```
 *     ┌───────┐      ┌───────┐     ┌───────┐      ┌───────┐
 *    ┌┤       ├┐    ┌┤       ├┐   ┌┤       ├┐    ┌┤       ├┐
 *    ││       ││    ││ ────► ││   ││ ────► ││    ││       ││
 *    └┤       ├┘    └┤  \ /  ├┘   └┤       ├┘    └┤work(){├┘
 *     │       │      │   X   │     │       │      │ get();│
 *    ┌┤       ├┐    ┌┤  / \  ├┐   ┌┤       ├┐    ┌┤ pub();├┐
 *    ││       ││    ││ ────► ││   ││ ────► ││    ││}      ││
 *    └┤       ├┘    └┤       ├┘   └┤       ├┘    └┤       ├┘
 *     └───────┘      └───────┘     └───────┘      └───────┘
 *       `DONT`      `ALL_TO_ALL   `ONE_TO_ONE`   `TPP_CUSTOM`
 * ```
 */
enum class TagPropagationPolicy {
    TPP_DONT = 0,       /*!< Scheduler doesn't propagate tags from in- to output. The block itself is free to insert tags. */
    TPP_ALL_TO_ALL = 1, /*!< Propagate tags from all in- to all outputs. The scheduler takes care of that. */
    TPP_ONE_TO_ONE = 2, /*!< Propagate tags from n. input to n. output. Requires same number of in- and outputs */
    TPP_CUSTOM = 3      /*!< Like TPP_DONT, but signals the block it should implement application-specific forwarding behaviour. */
};

using property_map = pmtv::map_t;

template<typename T>
concept PropertyMapType = std::same_as<std::decay_t<T>, property_map>;

/**
 * @brief 'Tag' is a metadata structure that can be attached to a stream of data to carry extra information about that data.
 * A tag can describe a specific time, parameter or meta-information (e.g. sampling frequency, gains, ...), provide annotations,
 * or indicate events that blocks may trigger actions in downstream blocks. Tags can be inserted or consumed by blocks at
 * any point in the signal processing flow, allowing for flexible and customisable data processing.
 *
 * Tags contain the index ID of the sending/receiving stream sample <T> they are attached to. Block implementations
 * may choose to chunk the data based on the MIN_SAMPLES/MAX_SAMPLES criteria only, or in addition break-up the stream
 * so that there is only one tag per scheduler iteration. Multiple tags on the same sample shall be merged to one.
 */
struct alignas(hardware_constructive_interference_size) Tag {
    using signed_index_type = std::make_signed_t<std::size_t>;
    signed_index_type index{ 0 };
    property_map      map{};

    Tag() = default; // TODO: remove -- needed only for Clang <=15

    Tag(signed_index_type index_, property_map map_) noexcept : index(index_), map(std::move(map_)) {} // TODO: remove -- needed only for Clang <=15

    bool
    operator==(const Tag &other) const
            = default;

    // TODO: do we need the convenience methods below?
    void
    reset() noexcept {
        index = 0;
        map.clear();
    }

    [[nodiscard]] pmtv::pmt &
    at(const std::string &key) {
        return map.at(key);
    }

    [[nodiscard]] const pmtv::pmt &
    at(const std::string &key) const {
        return map.at(key);
    }

    [[nodiscard]] std::optional<std::reference_wrapper<const pmtv::pmt>>
    get(const std::string &key) const noexcept {
        try {
            return map.at(key);
        } catch (std::out_of_range &e) {
            return std::nullopt;
        }
    }

    [[nodiscard]] std::optional<std::reference_wrapper<pmtv::pmt>>
    get(const std::string &key) noexcept {
        try {
            return map.at(key);
        } catch (std::out_of_range &) {
            return std::nullopt;
        }
    }

    void
    insert_or_assign(const std::pair<std::string, pmtv::pmt> &value) {
        map[value.first] = value.second;
    }

    void
    insert_or_assign(const std::string &key, const pmtv::pmt &value) {
        map[key] = value;
    }
};

} // namespace gr

ENABLE_REFLECTION(gr::Tag, index, map);

namespace gr {
using meta::fixed_string;

inline void
updateMaps(const property_map &src, property_map &dest) {
    for (const auto &[key, value] : src) {
        if (auto nested_map = std::get_if<pmtv::map_t>(&value)) {
            // If it's a nested map
            if (auto it = dest.find(key); it != dest.end()) {
                // If the key exists in the destination map
                auto dest_nested_map = std::get_if<pmtv::map_t>(&(it->second));
                if (dest_nested_map) {
                    // Merge the nested maps recursively
                    updateMaps(*nested_map, *dest_nested_map);
                } else {
                    // Key exists but not a map, replace it
                    dest[key] = value;
                }
            } else {
                // If the key doesn't exist, just insert
                dest.insert({ key, value });
            }
        } else {
            // If it's not a nested map, insert/replace the value
            dest[key] = value;
        }
    }
}

constexpr fixed_string GR_TAG_PREFIX = "gr:";

template<fixed_string Key, typename PMT_TYPE, fixed_string Unit = "", fixed_string Description = "">
class DefaultTag {
    constexpr static fixed_string _key = GR_TAG_PREFIX + Key;

public:
    using value_type = PMT_TYPE;

    [[nodiscard]] constexpr std::string_view
    key() const noexcept {
        return std::string_view{ _key };
    }

    [[nodiscard]] constexpr std::string_view
    shortKey() const noexcept {
        return std::string_view(Key);
    }

    [[nodiscard]] constexpr std::string_view
    unit() const noexcept {
        return std::string_view(Unit);
    }

    [[nodiscard]] constexpr std::string_view
    description() const noexcept {
        return std::string_view(Description);
    }

    [[nodiscard]] EM_CONSTEXPR explicit(false) operator std::string() const noexcept { return std::string(_key); }

    template<typename T>
        requires std::is_same_v<value_type, T>
    [[nodiscard]] std::pair<std::string, pmtv::pmt>
    operator()(const T &newValue) const noexcept {
        return { std::string(_key), static_cast<pmtv::pmt>(PMT_TYPE(newValue)) };
    }
};

template<fixed_string Key, typename PMT_TYPE, fixed_string Unit, fixed_string Description, gr::meta::string_like TOtherString>
inline constexpr std::strong_ordering
operator<=>(const DefaultTag<Key, PMT_TYPE, Unit, Description> &dt, const TOtherString &str) noexcept {
    if ((dt.shortKey() <=> str) == 0) {
        return std::strong_ordering::equal; // shortKeys are equal
    } else {
        return dt.key() <=> str; // compare key()
    }
}

template<fixed_string Key, typename PMT_TYPE, fixed_string Unit, fixed_string Description, gr::meta::string_like TOtherString>
inline constexpr std::strong_ordering
operator<=>(const TOtherString &str, const DefaultTag<Key, PMT_TYPE, Unit, Description> &dt) noexcept {
    if ((str <=> dt.shortKey()) == std::strong_ordering::equal) {
        return std::strong_ordering::equal; // shortKeys are equal
    } else {
        return str <=> dt.key(); // compare key()
    }
}

template<fixed_string Key, typename PMT_TYPE, fixed_string Unit, fixed_string Description, gr::meta::string_like TOtherString>
inline constexpr bool
operator==(const DefaultTag<Key, PMT_TYPE, Unit, Description> &dt, const TOtherString &str) noexcept {
    return (dt <=> std::string_view(str)) == 0;
}

template<fixed_string Key, typename PMT_TYPE, fixed_string Unit, fixed_string Description, gr::meta::string_like TOtherString>
inline constexpr bool
operator==(const TOtherString &str, const DefaultTag<Key, PMT_TYPE, Unit, Description> &dt) noexcept {
    return (std::string_view(str) <=> dt) == 0;
}

namespace tag { // definition of default tags and names
inline EM_CONSTEXPR_STATIC DefaultTag<"sample_rate", float, "Hz", "signal sample rate"> SAMPLE_RATE;
inline EM_CONSTEXPR_STATIC DefaultTag<"sample_rate", float, "Hz", "signal sample rate"> SIGNAL_RATE;
inline EM_CONSTEXPR_STATIC DefaultTag<"signal_name", std::string, "", "signal name"> SIGNAL_NAME;
inline EM_CONSTEXPR_STATIC DefaultTag<"signal_unit", std::string, "", "signal's physical SI unit"> SIGNAL_UNIT;
inline EM_CONSTEXPR_STATIC DefaultTag<"signal_min", float, "a.u.", "signal physical max. (e.g. DAQ) limit"> SIGNAL_MIN;
inline EM_CONSTEXPR_STATIC DefaultTag<"signal_max", float, "a.u.", "signal physical max. (e.g. DAQ) limit"> SIGNAL_MAX;
inline EM_CONSTEXPR_STATIC DefaultTag<"trigger_name", std::string> TRIGGER_NAME;
inline EM_CONSTEXPR_STATIC DefaultTag<"trigger_time", uint64_t, "ns", "UTC-based time-stamp"> TRIGGER_TIME;
inline EM_CONSTEXPR_STATIC DefaultTag<"trigger_offset", float, "s", "sample delay w.r.t. the trigger (e.g.compensating analog group delays)"> TRIGGER_OFFSET;
inline EM_CONSTEXPR_STATIC DefaultTag<"trigger_meta_info", property_map, "", "maps containing additional trigger information"> TRIGGER_META_INFO;
inline EM_CONSTEXPR_STATIC DefaultTag<"context", std::string, "", "multiplexing key to orchestrate node settings/behavioural changes"> CONTEXT;
inline EM_CONSTEXPR_STATIC DefaultTag<"reset_default", bool, "", "reset block state to stored default"> RESET_DEFAULTS;
inline EM_CONSTEXPR_STATIC DefaultTag<"store_default", bool, "", "store block settings as default"> STORE_DEFAULTS;
inline EM_CONSTEXPR_STATIC DefaultTag<"end_of_stream", bool, "", "end of stream, receiver should change to DONE state"> END_OF_STREAM;

inline constexpr std::tuple DEFAULT_TAGS = { SAMPLE_RATE,    SIGNAL_NAME,       SIGNAL_UNIT, SIGNAL_MIN,     SIGNAL_MAX,     TRIGGER_NAME, TRIGGER_TIME,
                                             TRIGGER_OFFSET, TRIGGER_META_INFO, CONTEXT,     RESET_DEFAULTS, STORE_DEFAULTS, END_OF_STREAM };
} // namespace tag

} // namespace gr

#endif // GNURADIO_TAG_HPP

#include <chrono>
#include <cstdint>
#include <map>
// #include <pmtv/pmt.hpp>

#include <variant>
#include <vector>

namespace gr {

struct LayoutRight {};

struct LayoutLeft {};

/**
 * @brief a concept that describes a Packet, which is a subset of the DataSet struct.
 */
template<typename T>
concept PacketLike = requires(T t) {
    typename T::value_type;
    typename T::pmt_map;
    requires std::is_same_v<decltype(t.timestamp), int64_t>;
    requires std::is_same_v<decltype(t.signal_values), std::vector<typename T::value_type>>;
    requires std::is_same_v<decltype(t.meta_information), std::vector<typename T::pmt_map>>;
};

/**
 * @brief A concept that describes a Tensor, which is a subset of the DataSet struct.
 */
template<typename T>
concept TensorLike = PacketLike<T> && requires(T t, const std::size_t n_items) {
    typename T::value_type;
    typename T::pmt_map;
    typename T::tensor_layout_type;
    requires std::is_same_v<decltype(t.extents), std::vector<std::int32_t>>;
    requires std::is_same_v<decltype(t.layout), typename T::tensor_layout_type>;
    requires std::is_same_v<decltype(t.signal_values), std::vector<typename T::value_type>>;
    requires std::is_same_v<decltype(t.signal_errors), std::vector<typename T::value_type>>;
    requires std::is_same_v<decltype(t.meta_information), std::vector<typename T::pmt_map>>;
};

/**
 * @brief: a DataSet consists of signal data, metadata, and associated axis information.
 *
 * The DataSet can be used to store and manipulate data in a structured way, and supports various types of axes,
 * layouts, and signal data. The dataset contains information such as timestamp, axis names and units, signal names,
 * values, and ranges, as well as metadata and timing events. This struct provides a flexible way to store and organize
 * data with associated metadata, and can be customized for different types of data and applications.
 */
template<typename T>
concept DataSetLike = TensorLike<T> && requires(T t, const std::size_t n_items) {
    typename T::value_type;
    typename T::pmt_map;
    typename T::tensor_layout_type;
    requires std::is_same_v<decltype(t.timestamp), int64_t>;

    // axis layout:
    requires std::is_same_v<decltype(t.axis_names), std::vector<std::string>>;
    requires std::is_same_v<decltype(t.axis_units), std::vector<std::string>>;
    requires std::is_same_v<decltype(t.axis_values), std::vector<std::vector<typename T::value_type>>>;

    // signal data storage
    requires std::is_same_v<decltype(t.signal_names), std::vector<std::string>>;
    requires std::is_same_v<decltype(t.signal_units), std::vector<std::string>>;
    requires std::is_same_v<decltype(t.signal_values), std::vector<typename T::value_type>>;
    requires std::is_same_v<decltype(t.signal_errors), std::vector<typename T::value_type>>;
    requires std::is_same_v<decltype(t.signal_ranges), std::vector<std::vector<typename T::value_type>>>;

    // meta data
    requires std::is_same_v<decltype(t.meta_information), std::vector<typename T::pmt_map>>;
    requires std::is_same_v<decltype(t.timing_events), std::vector<std::vector<Tag>>>;
};

template<typename T>
struct DataSet {
    using value_type         = T;
    using tensor_layout_type = std::variant<LayoutRight, LayoutLeft, std::string>;
    using pmt_map            = std::map<std::string, pmtv::pmt>;
    std::int64_t timestamp   = 0; // UTC timestamp [ns]

    // axis layout:
    std::vector<std::string>    axis_names{};  // e.g. time, frequency, …
    std::vector<std::string>    axis_units{};  // axis base SI-unit
    std::vector<std::vector<T>> axis_values{}; // explicit axis values

    // signal data layout:
    std::vector<std::int32_t> extents{}; // extents[dim0_size, dim1_size, …]
    tensor_layout_type        layout{};  // row-major, column-major, “special”

    // signal data storage:
    std::vector<std::string>    signal_names{};  // size = extents[0]
    std::vector<std::string>    signal_units{};  // size = extents[0]
    std::vector<T>              signal_values{}; // size = \PI_i extents[i]
    std::vector<T>              signal_errors{}; // size = \PI_i extents[i] or '0' if not applicable
    std::vector<std::vector<T>> signal_ranges{}; // [[min_0, max_0], [min_1, max_1], …] used for communicating, for example, HW limits

    // meta data
    std::vector<pmt_map>          meta_information{};
    std::vector<std::vector<Tag>> timing_events{};
};

static_assert(DataSetLike<DataSet<std::byte>>, "DataSet<std::byte> concept conformity");
static_assert(DataSetLike<DataSet<float>>, "DataSet<float> concept conformity");
static_assert(DataSetLike<DataSet<double>>, "DataSet<double> concept conformity");

// public type definitions to allow simple reflection
using DataSet_float  = DataSet<double>;
using DataSet_double = DataSet<float>;

template<typename T>
struct Tensor {
    using value_type         = T;
    using tensor_layout_type = std::variant<LayoutRight, LayoutLeft, std::string>;
    using pmt_map            = std::map<std::string, pmtv::pmt>;
    std::int64_t timestamp   = 0; // UTC timestamp [ns]

    std::vector<std::int32_t> extents{}; // extents[dim0_size, dim1_size, …]
    tensor_layout_type        layout{};  // row-major, column-major, “special”

    std::vector<T> signal_values{}; // size = \PI_i extents[i]
    std::vector<T> signal_errors{}; // size = \PI_i extents[i] or '0' if not applicable

    // meta data
    std::vector<pmt_map> meta_information{};
};

static_assert(TensorLike<Tensor<std::byte>>, "Tensor<std::byte> concept conformity");
static_assert(TensorLike<Tensor<float>>, "Tensor<std::byte> concept conformity");
static_assert(TensorLike<Tensor<double>>, "Tensor<std::byte> concept conformity");

template<typename T>
struct Packet {
    using value_type = T;
    using pmt_map    = std::map<std::string, pmtv::pmt>;

    std::int64_t         timestamp = 0; // UTC timestamp [ns]
    std::vector<T>       signal_values{}; // size = \PI_i extents[i
    std::vector<pmt_map> meta_information{};
};

static_assert(PacketLike<Packet<std::byte>>, "Packet<std::byte> concept conformity");
static_assert(PacketLike<Packet<float>>, "Packet<std::byte> concept conformity");
static_assert(PacketLike<Packet<double>>, "Packet<std::byte> concept conformity");

} // namespace gr

ENABLE_REFLECTION(gr::DataSet_double, timestamp, axis_names, axis_units, axis_values, extents, layout, signal_names, signal_units, signal_values, signal_errors, signal_ranges, meta_information,
                  timing_events)
ENABLE_REFLECTION(gr::DataSet_float, timestamp, axis_names, axis_units, axis_values, extents, layout, signal_names, signal_units, signal_values, signal_errors, signal_ranges, meta_information,
                  timing_events)
#endif // GNURADIO_DATASET_HPP

// #include "Message.hpp"
#ifndef GNURADIO_MESSAGE_HPP
#define GNURADIO_MESSAGE_HPP

// #include <gnuradio-4.0/meta/formatter.hpp>
#ifndef GNURADIO_FORMATTER_HPP
#define GNURADIO_FORMATTER_HPP

#include <complex>
#include <expected>
#include <fmt/format.h>
// #include <gnuradio-4.0/meta/UncertainValue.hpp>
#ifndef GNURADIO_UNCERTAINVALUE_HPP
#define GNURADIO_UNCERTAINVALUE_HPP

#include <atomic>
#include <complex>
#include <concepts>
#include <cstdint>
#include <numbers>
#include <optional>
#include <type_traits>

// #include <gnuradio-4.0/meta/utils.hpp>


namespace gr {

/**
 *
 * @brief Propagation of Uncertainties
 *
 * original idea by: Evan Manning, "Uncertainty Propagation in C++", NASA Jet Propulsion Laboratory,
 * C/C++ Users Journal Volume 14, Number 3, March, 1996
 * http://www.pennelynn.com/Documents/CUJ/HTML/14.03/MANNING/MANNING.HTM
 *
 * implements +,-,*,/ operators for basic arithmetic and complex types, for details see:
 * https://en.wikipedia.org/wiki/Propagation_of_uncertainty#Example_formulae
 * This implements only propagation of uncorrelated symmetric errors (i.e. gaussian-type standard deviations).
 * A more rigorous treatment would require the calculation and propagation of the
 * corresponding covariance matrix which is out of scope of this implementation.
 */

template<typename T>
concept arithmetic_or_complex_like = std::is_arithmetic_v<T> || meta::complex_like<T>;

template<arithmetic_or_complex_like T>
struct UncertainValue {
    using value_type = T;

    T value       = static_cast<T>(0); /// mean value
    T uncertainty = static_cast<T>(0); /// uncorrelated standard deviation

    // Default constructor
    constexpr UncertainValue() noexcept = default;

    constexpr UncertainValue(T value_, T uncertainty_) noexcept : value(value_), uncertainty(uncertainty_) {}

    explicit(false) constexpr UncertainValue(T value_) noexcept : value(value_), uncertainty(static_cast<T>(0)) {}

    constexpr UncertainValue(const UncertainValue &) noexcept = default;
    constexpr UncertainValue(UncertainValue &&) noexcept      = default;
    constexpr UncertainValue &
    operator=(const UncertainValue &) noexcept
            = default;
    ~UncertainValue() = default;

    constexpr UncertainValue &
    operator=(const T &other) noexcept {
        value       = other;
        uncertainty = static_cast<T>(0);
        return *this;
    }

    auto
    operator<=>(UncertainValue const &) const
            = default;
};

template<typename T>
UncertainValue(T, T) -> UncertainValue<T>;

template<typename T>
concept UncertainValueLike = gr::meta::is_instantiation_of<T, UncertainValue>;

template<typename T>
    requires arithmetic_or_complex_like<meta::fundamental_base_value_type_t<T>>
[[nodiscard]] inline constexpr auto
value(const T &val) noexcept {
    if constexpr (UncertainValueLike<T>) {
        return val.value;
    } else {
        val;
    }
}

template<typename T>
    requires arithmetic_or_complex_like<meta::fundamental_base_value_type_t<T>>
[[nodiscard]] inline constexpr auto
uncertainty(const T &val) noexcept {
    if constexpr (UncertainValueLike<T>) {
        return val.uncertainty;
    } else {
        return T();
    }
}

namespace detail {
template<typename T>
struct UncertainValueValueType {
    using type = T;
};

template<typename T>
struct UncertainValueValueType<UncertainValue<T>> {
    using type = T;
};
} // namespace detail

template<typename T>
using UncertainValueType_t = detail::UncertainValueValueType<T>::type;

/********************** some basic math operation definitions *********************************/

template<typename T, typename U, typename ValueTypeT = UncertainValueType_t<T>, typename ValueTypeU = UncertainValueType_t<U>>
    requires(UncertainValueLike<T> || UncertainValueLike<U>) && std::is_same_v<meta::fundamental_base_value_type_t<ValueTypeT>, meta::fundamental_base_value_type_t<ValueTypeU>>
[[nodiscard]] inline constexpr auto
operator+(const T &lhs, const U &rhs) noexcept {
    if constexpr (UncertainValueLike<T> && UncertainValueLike<U>) {
        using ResultType = decltype(lhs.value + rhs.value);
        if constexpr (meta::complex_like<ValueTypeT> || meta::complex_like<ValueTypeU>) {
            // we are dealing with complex numbers -> use the standard uncorrelated calculation.
            ResultType newUncertainty = { std::hypot(std::real(lhs.uncertainty), std::real(rhs.uncertainty)), std::hypot(std::imag(lhs.uncertainty), std::imag(rhs.uncertainty)) };
            return UncertainValue<ResultType>{ lhs.value + rhs.value, newUncertainty };
        } else {
            // both ValueType[T,U] are arithmetic uncertainties
            return UncertainValue<ResultType>{ lhs.value + rhs.value, std::hypot(lhs.uncertainty, rhs.uncertainty) };
        }
    } else if constexpr (UncertainValueLike<T> && arithmetic_or_complex_like<ValueTypeU>) {
        return T{ lhs.value + rhs, lhs.uncertainty };
    } else if constexpr (arithmetic_or_complex_like<ValueTypeT> && UncertainValueLike<U>) {
        return U{ lhs + rhs.value, rhs.uncertainty };
    } else {
        static_assert(gr::meta::always_false<T>, "branch should never reach here due to default '+' definition");
        return lhs + rhs; // unlikely to be called due to default '+' definition
    }
}

template<UncertainValueLike T, typename U>
inline constexpr T &
operator+=(T &lhs, const U &rhs) noexcept {
    lhs = lhs + rhs;
    return lhs;
}

template<UncertainValueLike T, typename ValueTypeT = UncertainValueType_t<T>>
inline constexpr T
operator+(const T &val) {
    if constexpr (meta::complex_like<ValueTypeT>) {
        return val;
    } else {
        return { std::abs(val.value), std::abs(val.uncertainty) };
    }
}

template<typename T, typename U, typename ValueTypeT = UncertainValueType_t<T>, typename ValueTypeU = UncertainValueType_t<U>>
    requires(UncertainValueLike<T> || UncertainValueLike<U>) && std::is_same_v<meta::fundamental_base_value_type_t<ValueTypeT>, meta::fundamental_base_value_type_t<ValueTypeU>>
[[nodiscard]] inline constexpr auto
operator-(const T &lhs, const U &rhs) noexcept {
    if constexpr (UncertainValueLike<T> && UncertainValueLike<U>) {
        using ResultType = decltype(lhs.value - rhs.value);
        if constexpr (meta::complex_like<ValueTypeT> || meta::complex_like<ValueTypeU>) {
            // we are dealing with complex numbers -> use the standard uncorrelated calculation.
            ResultType newUncertainty = { std::hypot(std::real(lhs.uncertainty), std::real(rhs.uncertainty)), std::hypot(std::imag(lhs.uncertainty), std::imag(rhs.uncertainty)) };
            return UncertainValue<ResultType>{ lhs.value - rhs.value, newUncertainty };
        } else {
            // both ValueType[T,U] are arithmetic uncertainties
            return UncertainValue<ResultType>{ lhs.value - rhs.value, std::hypot(lhs.uncertainty, rhs.uncertainty) };
        }
    } else if constexpr (UncertainValueLike<T> && arithmetic_or_complex_like<ValueTypeU>) {
        return T{ lhs.value - rhs, lhs.uncertainty };
    } else if constexpr (arithmetic_or_complex_like<ValueTypeT> && UncertainValueLike<U>) {
        return U{ lhs - rhs.value, rhs.uncertainty };
    } else {
        static_assert(gr::meta::always_false<T>, "branch should never reach here due to default '-' definition");
    }
}

template<UncertainValueLike T, typename U>
inline constexpr T &
operator-=(T &lhs, const U &rhs) noexcept {
    lhs = lhs - rhs;
    return lhs;
}

template<UncertainValueLike T>
inline constexpr T
operator-(const T &val) {
    return { -val.value, val.uncertainty };
}

template<typename T, typename U, typename ValueTypeT = UncertainValueType_t<T>, typename ValueTypeU = UncertainValueType_t<U>>
    requires(UncertainValueLike<T> || UncertainValueLike<U>) && std::is_same_v<meta::fundamental_base_value_type_t<ValueTypeT>, meta::fundamental_base_value_type_t<ValueTypeU>>
[[nodiscard]] inline constexpr auto
operator*(const T &lhs, const U &rhs) noexcept {
    if constexpr (UncertainValueLike<T> && UncertainValueLike<U>) {
        using ResultType = decltype(lhs.value * rhs.value);
        if constexpr (meta::complex_like<ValueTypeT> || meta::complex_like<ValueTypeU>) {
            // we are dealing with complex numbers -> use standard uncorrelated calculation
            ResultType newUncertainty = { std::hypot(std::real(lhs.value) * std::real(rhs.uncertainty), std::real(rhs.value) * std::real(lhs.uncertainty)),
                                          std::hypot(std::imag(lhs.value) * std::imag(rhs.uncertainty), std::imag(rhs.value) * std::imag(lhs.uncertainty)) };
            return UncertainValue<ResultType>{ lhs.value * rhs.value, newUncertainty };
        } else {
            // both ValueType[T,U] are arithmetic uncertainties
            auto combinedUncertainty = std::hypot(lhs.value * rhs.uncertainty, rhs.value * lhs.uncertainty);
            return UncertainValue<ResultType>{ lhs.value * rhs.value, combinedUncertainty };
        }
    } else if constexpr (UncertainValueLike<T> && arithmetic_or_complex_like<ValueTypeU>) {
        return T{ lhs.value * rhs, lhs.uncertainty * rhs };
    } else if constexpr (arithmetic_or_complex_like<ValueTypeT> && UncertainValueLike<U>) {
        return U{ lhs * rhs.value, lhs * rhs.uncertainty };
    } else {
        static_assert(gr::meta::always_false<T>, "branch should never reach here due to default '*' definition");
    }
}

template<UncertainValueLike T, typename U>
inline constexpr T &
operator*=(T &lhs, const U &rhs) noexcept {
    lhs = lhs * rhs;
    return lhs;
}

template<typename T, typename U, typename ValueTypeT = UncertainValueType_t<T>, typename ValueTypeU = UncertainValueType_t<U>>
    requires(UncertainValueLike<T> || UncertainValueLike<U>) && std::is_same_v<meta::fundamental_base_value_type_t<ValueTypeT>, meta::fundamental_base_value_type_t<ValueTypeU>>
[[nodiscard]] inline constexpr auto
operator/(const T &lhs, const U &rhs) noexcept {
    if constexpr (UncertainValueLike<T> && UncertainValueLike<U>) {
        using ResultType = decltype(lhs.value * rhs.value);
        if constexpr (meta::complex_like<ValueTypeT> || meta::complex_like<ValueTypeU>) {
            // we are dealing with complex numbers -> use standard uncorrelated calculation
            ResultType newUncertainty;
            if constexpr (std::is_arithmetic_v<ValueTypeT> && meta::complex_like<ValueTypeU>) {
                // LHS is real, RHS is complex
                newUncertainty = { std::sqrt(std::pow(lhs.uncertainty / std::real(rhs.value), 2)), std::sqrt(std::pow(std::imag(rhs.uncertainty) * lhs.value / std::norm(rhs.value), 2)) };
            } else if constexpr (meta::complex_like<ValueTypeT> && std::is_arithmetic_v<ValueTypeU>) {
                // LHS is complex, RHS is real
                newUncertainty = { std::hypot(std::real(lhs.uncertainty) / rhs.value, rhs.uncertainty * std::real(lhs.value) / std::pow(rhs.value, 2)),
                                   std::sqrt(std::pow(std::imag(lhs.uncertainty) / rhs.value, 2)) };
            } else {
                newUncertainty = { std::hypot(std::real(lhs.uncertainty) / std::real(rhs.value), std::real(rhs.uncertainty) * std::real(lhs.value) / std::norm(rhs.value)),
                                   std::hypot(std::imag(lhs.uncertainty) / std::imag(rhs.value), std::imag(rhs.uncertainty) * std::imag(lhs.value) / std::norm(rhs.value)) };
            }

            return UncertainValue<ResultType>{ lhs.value / rhs.value, newUncertainty };
        } else {
            // both ValueType[T,U] are arithmetic uncertainties
            auto combinedUncertainty = std::hypot(lhs.uncertainty / rhs.value, rhs.uncertainty * lhs.value / std::pow(rhs.value, 2));
            return UncertainValue<ResultType>{ lhs.value / rhs.value, combinedUncertainty };
        }
    } else if constexpr (UncertainValueLike<T> && arithmetic_or_complex_like<ValueTypeU>) {
        return T{ lhs.value / rhs, lhs.uncertainty / std::abs(rhs) };
    } else if constexpr (arithmetic_or_complex_like<ValueTypeT> && UncertainValueLike<U>) {
        auto rhsMagSquared = std::norm(rhs.value);
        return U{ lhs / rhs.value, rhs.uncertainty * std::abs(lhs) / rhsMagSquared };
    } else {
        static_assert(gr::meta::always_false<T>, "branch should never reach here due to default '/' definition");
    }
}

template<UncertainValueLike T, typename U>
inline constexpr T &
operator/=(T &lhs, const U &rhs) noexcept {
    lhs = lhs / rhs;
    return lhs;
}

} // namespace gr

namespace gr::math {

template<gr::UncertainValueLike T, std::floating_point U, typename ValueTypeT = gr::UncertainValueType_t<T>>
    requires std::is_same_v<gr::meta::fundamental_base_value_type_t<ValueTypeT>, U> || std::integral<U>
[[nodiscard]] inline constexpr T
pow(const T &base, U exponent) noexcept {
    if (base.value == 0.0) [[unlikely]] {
        if (exponent == 0) [[unlikely]] {
            return T{ 1, 0 };
        } else {
            return T{ 0, 0 };
        }
    }

    ValueTypeT newValue = std::pow(base.value, exponent);
    if constexpr (gr::meta::complex_like<ValueTypeT>) {
        auto val = exponent / base.value * newValue;
        return T{ newValue, std::sqrt(val * std::conj(val)) * base.uncertainty };
    } else {
        return T{ newValue, std::abs(newValue * exponent * base.uncertainty / base.value) };
    }
}

template<gr::UncertainValueLike T, gr::UncertainValueLike U, typename ValueTypeT = gr::UncertainValueType_t<T>, typename ValueTypeU = gr::UncertainValueType_t<T>>
    requires std::is_same_v<gr::meta::fundamental_base_value_type_t<ValueTypeT>, gr::meta::fundamental_base_value_type_t<ValueTypeU>>
[[nodiscard]] inline constexpr T
pow(const T &base, const U &exponent) noexcept {
    if (base.value == 0.0) [[unlikely]] {
        if (exponent.value == static_cast<ValueTypeU>(0)) [[unlikely]] {
            return T{ 1, 0 };
        } else {
            return T{ 0, 0 };
        }
    }

    ValueTypeT newValue = std::pow(base.value, exponent.value);
    if constexpr (gr::meta::complex_like<ValueTypeT>) {
        auto hypot = [](auto a, auto b) { return std::sqrt(std::real(a * std::conj(a) + b * std::conj(b))); }; // c*c⃰ == is always real valued
        return T{ newValue, hypot(exponent.value / base.value * newValue * base.uncertainty, std::log(base.value) * newValue * exponent.uncertainty) };
    } else {
        return T{ newValue, std::abs(newValue) * std::hypot(exponent.value / base.value * base.uncertainty, std::log(base.value) * exponent.uncertainty) };
    }
}

template<gr::UncertainValueLike T>
[[nodiscard]] inline constexpr T
sqrt(const T &value) noexcept {
    return gr::math::pow(value, 0.5);
}

template<gr::UncertainValueLike T, typename ValueTypeT = gr::UncertainValueType_t<T>>
[[nodiscard]] inline constexpr T
sin(const T &x) noexcept {
    return T{ std::sin(x.value), std::abs(std::cos(x.value) * x.uncertainty) };
}

template<gr::UncertainValueLike T, typename ValueTypeT = gr::UncertainValueType_t<T>>
[[nodiscard]] inline constexpr T
cos(const T &x) noexcept {
    return T{ std::cos(x.value), std::abs(std::sin(x.value) * x.uncertainty) };
}

template<gr::UncertainValueLike T, typename ValueTypeT = gr::UncertainValueType_t<T>>
[[nodiscard]] inline constexpr T
exp(const T &x) noexcept {
    if constexpr (gr::meta::complex_like<ValueTypeT>) {
        return gr::math::pow(gr::UncertainValue<ValueTypeT>{ std::numbers::e_v<typename ValueTypeT::value_type>, static_cast<ValueTypeT>(0) }, x);
    } else {
        return gr::math::pow(gr::UncertainValue<ValueTypeT>{ std::numbers::e_v<ValueTypeT>, static_cast<ValueTypeT>(0) }, x);
    }
}

} // namespace gr::math

#endif // GNURADIO_UNCERTAINVALUE_HPP
// #include <gnuradio-4.0/Tag.hpp>

#include <source_location>
#include <vector>

template<typename T>
struct fmt::formatter<std::complex<T>> {
    char presentation = 'g'; // default format

    template<typename ParseContext>
    constexpr auto
    parse(ParseContext &ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 'F' || *it == 'e' || *it == 'E' || *it == 'g' || *it == 'G')) {
            presentation = *it++;
        }
        if (it != end && *it != '}') {
            throw fmt::format_error("invalid format");
        }
        return it;
    }

    template<typename FormatContext>
    constexpr auto
    format(const std::complex<T> &value, FormatContext &ctx) const {
        // format according to: https://fmt.dev/papers/p2197r0.html#examples
        const auto imag = value.imag();
        switch (presentation) {
        case 'e':
            if (imag == 0) {
                return fmt::format_to(ctx.out(), "{:e}", value.real());
            }
            return fmt::format_to(ctx.out(), "({:e}{:+e}i)", value.real(), imag);
        case 'E':
            if (imag == 0) {
                return fmt::format_to(ctx.out(), "{:E}", value.real());
            }
            return fmt::format_to(ctx.out(), "({:E}{:+E}i)", value.real(), imag);
        case 'f':
            if (imag == 0) {
                return fmt::format_to(ctx.out(), "{:f}", value.real());
            }
            return fmt::format_to(ctx.out(), "({:f}{:+f}i)", value.real(), imag);
        case 'F':
            if (imag == 0) {
                return fmt::format_to(ctx.out(), "{:F}", value.real());
            }
            return fmt::format_to(ctx.out(), "({:F}{:+F}i)", value.real(), imag);
        case 'G':
            if (imag == 0) {
                return fmt::format_to(ctx.out(), "{:G}", value.real());
            }
            return fmt::format_to(ctx.out(), "({:G}{:+G}i)", value.real(), imag);
        case 'g':
        default:
            if (imag == 0) {
                return fmt::format_to(ctx.out(), "{:g}", value.real());
            }
            return fmt::format_to(ctx.out(), "({:g}{:+g}i)", value.real(), imag);
        }
    }
};

// simplified formatter for UncertainValue
template<gr::arithmetic_or_complex_like T>
struct fmt::formatter<gr::UncertainValue<T>> {
    template<typename ParseContext>
    constexpr auto
    parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    constexpr auto
    format(const gr::UncertainValue<T> &value, FormatContext &ctx) const {
        if constexpr (gr::meta::complex_like<T>) {
            return fmt::format_to(ctx.out(), "({} ± {})", value.value, value.uncertainty);
        } else {
            return fmt::format_to(ctx.out(), "({:G} ± {:G})", value.value, value.uncertainty);
        }
    }
};

template<>
struct fmt::formatter<gr::property_map> {
    template<typename ParseContext>
    constexpr auto
    parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    constexpr auto
    format(const gr::property_map &value, FormatContext &ctx) const {
        return fmt::format_to(ctx.out(), "{{ {} }}", fmt::join(value, ", "));
    }
};

template<>
struct fmt::formatter<std::vector<bool>> {
    char presentation = 'c';

    constexpr auto
    parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 's' || *it == 'c')) presentation = *it++;
        if (it != end && *it != '}') throw fmt::format_error("invalid format");
        return it;
    }

    template<typename FormatContext>
    auto
    format(const std::vector<bool> &v, FormatContext &ctx) const -> decltype(ctx.out()) {
        auto   sep = (presentation == 'c' ? ", " : " ");
        size_t len = v.size();
        fmt::format_to(ctx.out(), "[");
        for (size_t i = 0; i < len; ++i) {
            if (i > 0) {
                fmt::format_to(ctx.out(), "{}", sep);
            }
            fmt::format_to(ctx.out(), "{}", v[i] ? "true" : "false");
        }
        fmt::format_to(ctx.out(), "]");
        return ctx.out();
    }
};

template<>
struct fmt::formatter<std::source_location> {
    constexpr auto
    parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    // Formats the source_location, using 'f' for file and 'l' for line
    template<typename FormatContext>
    auto
    format(const std::source_location &loc, FormatContext &ctx) const -> decltype(ctx.out()) {
        // Example format: "file:line"
        return fmt::format_to(ctx.out(), "{}:{}", loc.file_name(), loc.line());
    }
};

template<typename Value, typename Error>
struct fmt::formatter<std::expected<Value, Error>> {
    constexpr auto
    parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    // Formats the source_location, using 'f' for file and 'l' for line
    template<typename FormatContext>
    auto
    format(const std::expected<Value, Error> &ret, FormatContext &ctx) const -> decltype(ctx.out()) {
        if (ret.has_value()) {
            return fmt::format_to(ctx.out(), "<std::expected-value: {}>", ret.value());
        } else {
            return fmt::format_to(ctx.out(), "<std::unexpected: {}>", ret.error());
        }
    }
};

#endif // GNURADIO_FORMATTER_HPP

// #include <gnuradio-4.0/meta/utils.hpp>

// #include <gnuradio-4.0/reflection.hpp>


// #include <pmtv/pmt.hpp>


#include <expected>
#include <source_location>
#include <string_view>

#include <fmt/chrono.h>
#include <fmt/format.h>

namespace gr {

struct exception : public std::exception {
    std::string                           message;
    std::source_location                  sourceLocation;
    std::chrono::system_clock::time_point errorTime = std::chrono::system_clock::now();

    exception(std::string_view msg = "unknown exception", std::source_location location = std::source_location::current()) noexcept : message(msg), sourceLocation(location) {}

    [[nodiscard]] const char *
    what() const noexcept override {
        if (formattedMessage.empty()) {
            formattedMessage = fmt::format("{} at {}:{}", message, sourceLocation.file_name(), sourceLocation.line());
        }
        return formattedMessage.c_str();
    }

private:
    mutable std::string formattedMessage; // Now storing the formatted message
};

struct Error {
    std::string                           message;
    std::source_location                  sourceLocation;
    std::chrono::system_clock::time_point errorTime = std::chrono::system_clock::now();

    Error(std::string_view msg = "unknown error", std::source_location location = std::source_location::current(),
          std::chrono::system_clock::time_point time = std::chrono::system_clock::now()) noexcept
        : message(msg), sourceLocation(location), errorTime(time) {}

    explicit Error(const std::exception &ex, std::source_location location = std::source_location::current()) noexcept : Error(ex.what(), location) {}

    explicit Error(const gr::exception &ex) noexcept : message(ex.message), sourceLocation(ex.sourceLocation), errorTime(ex.errorTime) {}

    [[nodiscard]] std::string
    srcLoc() const noexcept {
        return fmt::format("{}", sourceLocation);
    }

    [[nodiscard]] std::string
    methodName() const noexcept {
        return sourceLocation.function_name();
    }

    [[nodiscard]] std::string
    isoTime() const noexcept {
        return fmt::format("{:%Y-%m-%dT%H:%M:%S}.{:03}",                                    // ms-precision ISO time-format
                           fmt::localtime(std::chrono::system_clock::to_time_t(errorTime)), //
                           std::chrono::duration_cast<std::chrono::milliseconds>(errorTime.time_since_epoch()).count() % 1000);
    }
};

static_assert(std::is_default_constructible_v<Error>);
static_assert(!std::is_trivially_copyable_v<Error>); // because of the usage of std::string

namespace message {
/**
 * @brief Follows the OpenCMW command structure.
 * https://github.com/fair-acc/opencmw-cpp/blob/main/docs/Majordomo_protocol_comparison.pdf
 * derived from: https://rfc.zeromq.org/spec/7/ and https://rfc.zeromq.org/spec/18/
 */
enum class Command : unsigned char {
    Invalid     = 0x00,
    Get         = 0x01,
    Set         = 0x02,
    Partial     = 0x03,
    Final       = 0x04,
    Ready       = 0x05, ///< optional for client
    Disconnect  = 0x06, ///< optional for client
    Subscribe   = 0x07, ///< client-only
    Unsubscribe = 0x08, ///< client-only
    Notify      = 0x09, ///< worker-only
    Heartbeat   = 0x0a  ///< optional for client
};

template<Command command>
std::string
commandName() noexcept {
    return std::string(magic_enum::enum_name<command>());
}

inline static std::string defaultBlockProtocol  = "MDPW03";
inline static std::string defaultClientProtocol = "MDPC03";

} // namespace message

/**
 * @brief Follows OpenCMW's Majordomo protocol frame structure.
 * https://github.com/fair-acc/opencmw-cpp/blob/main/docs/Majordomo_protocol_comparison.pdf
 * derived from: https://rfc.zeromq.org/spec/7/ and https://rfc.zeromq.org/spec/18/
 */
struct Message {
    using enum gr::message::Command;
    using Error = gr::Error;

    std::string                        protocol = message::defaultBlockProtocol; ///< unique protocol name including version (e.g. 'MDPC03' or 'MDPW03')
    message::Command                   cmd      = Notify;                        ///< command type (GET, SET, SUBSCRIBE, UNSUBSCRIBE, PARTIAL, FINAL, NOTIFY, READY, DISCONNECT, HEARTBEAT)
    std::string                        serviceName; ///< service/block name (normally the URI path only), or client source ID (for broker/scheduler <-> worker messages) N.B empty string is wildcard
    std::string                        clientRequestID = ""; ///< stateful: worker mirrors clientRequestID; stateless: worker generates unique increasing IDs (to detect packet loss)
    std::string                        endpoint;             ///< URI containing at least <path> and optionally <query> parameters (e.g. property name)
    std::expected<property_map, Error> data;                 ///< request/reply body and/or Error containing stack-trace
    std::string                        rbac = "";            ///< optional RBAC meta-info -- may contain token, role, signed message hash (implementation dependent)
};

static_assert(std::is_default_constructible_v<Message>);
static_assert(!std::is_trivially_copyable_v<Message>); // because of the usage of std::string
static_assert(std::is_move_assignable_v<Message>);

namespace detail {
template<message::Command cmd, typename T>
    requires(std::is_same_v<T, property_map> || std::is_same_v<T, Error>)
void
sendMessage(auto &port, std::string_view serviceName, std::string_view endpoint, T userMessage, std::string_view clientRequestID = "") {
    using namespace gr::message;
    using enum gr::message::Command;

    Message message;
    message.cmd             = cmd;
    message.serviceName     = serviceName;
    message.clientRequestID = clientRequestID;
    message.endpoint        = endpoint;
    message.rbac            = "";

    if constexpr (std::is_same_v<T, property_map>) {
        message.data = std::move(userMessage);
    } else {
        message.data = std::unexpected(userMessage);
    }
    port.streamWriter().publish([&](auto &out) { out[0] = std::move(message); }, 1UZ);
}
} // namespace detail

template<auto cmd>
void
sendMessage(auto &port, std::string_view serviceName, std::string_view endpoint, property_map userMessage, std::string_view clientRequestID = "") {
    detail::sendMessage<cmd>(port, serviceName, endpoint, std::move(userMessage), clientRequestID);
}

template<auto cmd>
void
sendMessage(auto &port, std::string_view serviceName, std::string_view endpoint, std::initializer_list<std::pair<const std::string, pmtv::pmt>> userMessage, std::string_view clientRequestID = "") {
    detail::sendMessage<cmd, property_map>(port, serviceName, endpoint, property_map(userMessage), clientRequestID);
}

template<auto cmd>
void
sendMessage(auto &port, std::string_view serviceName, std::string_view endpoint, Error userMessage, std::string_view clientRequestID = "") {
    detail::sendMessage<cmd, Error>(port, serviceName, endpoint, std::move(userMessage), clientRequestID);
}

} // namespace gr

template<>
struct fmt::formatter<gr::Error> {
    char presentation = 's';

    constexpr auto
    parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && (*it == 'f' || *it == 't' || *it == 's')) presentation = *it++;
        if (it != end && *it != '}') throw fmt::format_error("invalid format");
        return it;
    }

    // Formats the source_location, using 'f' for file and 'l' for line
    template<typename FormatContext>
    auto
    format(const gr::Error &err, FormatContext &ctx) const -> decltype(ctx.out()) {
        switch (presentation) {
        case 't': return fmt::format_to(ctx.out(), "{}: {}: {} in method: {}", err.isoTime(), err.srcLoc(), err.message, err.methodName());
        case 'f': return fmt::format_to(ctx.out(), "{}: {} in method: {}", err.srcLoc(), err.message, err.methodName());
        case 's':
        default: return fmt::format_to(ctx.out(), "{}: {}", err.srcLoc(), err.message);
        }
    }
};

template<>
struct fmt::formatter<gr::message::Command> {
    constexpr auto
    parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    // Formats the source_location, using 'f' for file and 'l' for line
    template<typename FormatContext>
    auto
    format(const gr::message::Command &command, FormatContext &ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{}", magic_enum::enum_name(command));
    }
};

inline std::ostream &
operator<<(std::ostream &os, const gr::message::Command &command) {
    return os << magic_enum::enum_name(command);
}

template<>
struct fmt::formatter<gr::Message> {
    constexpr auto
    parse(format_parse_context &ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    // Formats the source_location, using 'f' for file and 'l' for line
    template<typename FormatContext>
    auto
    format(const gr::Message &msg, FormatContext &ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{{ protocol: '{}', cmd: {}, serviceName: '{}', clientRequestID: '{}', endpoint: '{}', {}, RBAC: '{}' }}", //
                              msg.protocol, msg.cmd, msg.serviceName, msg.clientRequestID, msg.endpoint,                                            //
                              msg.data.has_value() ? fmt::format("data: {}", msg.data.value()) : fmt::format("error: {}", msg.data.error()), msg.rbac);
    }
};

inline std::ostream &
operator<<(std::ostream &os, const gr::Message &msg) {
    return os << fmt::format("{}", msg);
}

#endif // include guard

// #include "Tag.hpp"


namespace gr {

using gr::meta::fixed_string;

enum class PortDirection { INPUT, OUTPUT, ANY }; // 'ANY' only for query and not to be used for port declarations

enum class ConnectionResult { SUCCESS, FAILED };

enum class PortType {
    STREAM,  /*!< used for single-producer-only ond usually synchronous one-to-one or one-to-many communications */
    MESSAGE, /*!< used for multiple-producer one-to-one, one-to-many, many-to-one, or many-to-many communications */
    ANY      // 'ANY' only for querying and not to be used for port declarations
};

/**
 * @brief optional port annotation argument to described whether the port can be handled within the same scheduling domain.
 *
 * @tparam PortDomainName the unique name of the domain, name shouldn't clash with other existing definitions (e.g. 'CPU' and 'GPU')
 */
template<fixed_string PortDomainName>
struct PortDomain {
    static constexpr fixed_string Name = PortDomainName;
};

template<typename T>
concept PortDomainLike = requires { T::Name; } && std::is_base_of_v<PortDomain<T::Name>, T>;

template<typename T>
using is_port_domain = std::bool_constant<PortDomainLike<T>>;

struct CPU : public PortDomain<"CPU"> {};

struct GPU : public PortDomain<"GPU"> {};

static_assert(is_port_domain<CPU>::value);
static_assert(is_port_domain<GPU>::value);
static_assert(!is_port_domain<int>::value);

template<class T>
concept PortLike = requires(T t, const std::size_t n_items, const std::any &newDefault) { // dynamic definitions
    typename T::value_type;
    { t.defaultValue() } -> std::same_as<std::any>;
    { t.setDefaultValue(newDefault) } -> std::same_as<bool>;
    { t.name } -> std::convertible_to<std::string_view>;
    { t.priority } -> std::convertible_to<std::int32_t>;
    { t.min_samples } -> std::convertible_to<std::size_t>;
    { t.max_samples } -> std::convertible_to<std::size_t>;
    { t.type() } -> std::same_as<PortType>;
    { t.direction() } -> std::same_as<PortDirection>;
    { t.domain() } -> std::same_as<std::string_view>;
    { t.resizeBuffer(n_items) } -> std::same_as<ConnectionResult>;
    { t.disconnect() } -> std::same_as<ConnectionResult>;
    { t.isSynchronous() } -> std::same_as<bool>;
    { t.isOptional() } -> std::same_as<bool>;
};

/**
 * @brief internal port buffer handler
 *
 * N.B. void* needed for type-erasure/Python compatibility/wrapping
 */
struct InternalPortBuffers {
    void *streamHandler;
    void *tagHandler;
};

/**
 * @brief optional port annotation argument to describe the min/max number of samples required from this port before invoking the blocks work function.
 *
 * @tparam minSamples (>0) specifies the minimum number of samples the port/block requires for processing in one scheduler iteration
 * @tparam maxSamples specifies the maximum number of samples the port/block can process in one scheduler iteration
 * @tparam isConst specifies if the range is constant or can be modified during run-time.
 */
template<std::size_t minSamples = std::dynamic_extent, std::size_t maxSamples = std::dynamic_extent, bool isConst = false>
struct RequiredSamples {
    static_assert(minSamples > 0, "Port<T, ..., RequiredSamples::MIN_SAMPLES, ...>, ..> must be >= 0");
    static constexpr std::size_t kMinSamples = minSamples == std::dynamic_extent ? 1UZ : minSamples;
    static constexpr std::size_t kMaxSamples = maxSamples == std::dynamic_extent ? std::numeric_limits<std::size_t>::max() : maxSamples;
    static constexpr bool        kIsConst    = isConst;
};

template<typename T>
concept IsRequiredSamples = requires {
    T::kMinSamples;
    T::kMaxSamples;
    T::kIsConst;
} && std::is_base_of_v<RequiredSamples<T::kMinSamples, T::kMaxSamples, T::kIsConst>, T>;

template<typename T>
using is_required_samples = std::bool_constant<IsRequiredSamples<T>>;

static_assert(is_required_samples<RequiredSamples<1, 1024>>::value);
static_assert(!is_required_samples<int>::value);

/**
 * @brief optional port annotation argument informing the graph/scheduler that a given port does not require to be connected
 */
struct Optional {};

/**
 * @brief optional port annotation argument to define the buffer implementation to be used for streaming data
 *
 * @tparam BufferType user-extendable buffer implementation for the streaming data
 */
template<gr::Buffer BufferType>
struct StreamBufferType {
    using type = BufferType;
};

/**
 * @brief optional port annotation argument to define the buffer implementation to be used for tag data
 *
 * @tparam BufferType user-extendable buffer implementation for the tag data
 */
template<gr::Buffer BufferType>
struct TagBufferType {
    using type = BufferType;
};

template<typename T>
concept IsStreamBufferAttribute = requires { typename T::type; } && gr::Buffer<typename T::type> && std::is_base_of_v<StreamBufferType<typename T::type>, T>;

template<typename T>
concept IsTagBufferAttribute = requires { typename T::type; } && gr::Buffer<typename T::type> && std::is_base_of_v<TagBufferType<typename T::type>, T>;

template<typename T>
using is_stream_buffer_attribute = std::bool_constant<IsStreamBufferAttribute<T>>;

template<typename T>
using is_tag_buffer_attribute = std::bool_constant<IsTagBufferAttribute<T>>;

template<typename T>
struct DefaultStreamBuffer : StreamBufferType<gr::CircularBuffer<T>> {};

struct DefaultMessageBuffer : StreamBufferType<gr::CircularBuffer<Message, std::dynamic_extent, gr::ProducerType::Multi>> {};

struct DefaultTagBuffer : TagBufferType<gr::CircularBuffer<Tag>> {};

static_assert(is_stream_buffer_attribute<DefaultStreamBuffer<int>>::value);
static_assert(is_stream_buffer_attribute<DefaultMessageBuffer>::value);
static_assert(!is_stream_buffer_attribute<DefaultTagBuffer>::value);
static_assert(!is_tag_buffer_attribute<DefaultStreamBuffer<int>>::value);
static_assert(is_tag_buffer_attribute<DefaultTagBuffer>::value);

struct PortMetaInfo {
    using description = Doc<R"*(@brief Port meta-information for increased type and physical-unit safety. Uses ISO 80000-1:2022 conventions.

**Some example usages:**
  * prevents to accidentally connect ports with incompatible sampling rates, quantity- and unit-types.
  * used to condition graphs/charts (notably the min/max range),
  * detect saturation/LNA non-linearities,
  * detect computation errors
  * ...

Follows the ISO 80000-1:2022 Quantities and Units conventions:
  * https://www.iso.org/standard/76921.html
  * https://en.wikipedia.org/wiki/ISO/IEC_80000
  * https://blog.ansi.org/iso-80000-1-2022-quantities-and-units/
)*">; // long-term goal: enable compile-time checks based on https://github.com/mpusz/mp-units (N.B. will become part of C++26)

    Annotated<float, "sample rate", Visible, Doc<"sampling rate in samples per second (Hz)">>                        sample_rate = 1.f;
    Annotated<std::string, "signal name", Doc<"name of the signal">>                                                 signal_name = "<unnamed>";
    Annotated<std::string, "signal quantity", Doc<"physical quantity (e.g., 'voltage'). Follows ISO 80000-1:2022.">> signal_quantity{};
    Annotated<std::string, "signal unit", Doc<"unit of measurement (e.g., '[V]', '[m]'). Follows ISO 80000-1:2022">> signal_unit{};
    Annotated<float, "signal min,", Doc<"minimum expected signal value">>                                            signal_min = std::numeric_limits<float>::lowest();
    Annotated<float, "signal max,", Doc<"maximum expected signal value">>                                            signal_max = std::numeric_limits<float>::max();

    // controls automatic (if set) or manual update of above parameters
    std::set<std::string, std::less<>> auto_update{ "sample_rate", "signal_name", "signal_quantity", "signal_unit", "signal_min", "signal_max" };

    PortMetaInfo() noexcept(true) : PortMetaInfo({}) {}

    explicit PortMetaInfo(std::initializer_list<std::pair<const std::string, pmtv::pmt>> initMetaInfo) noexcept(true) : PortMetaInfo(property_map{ initMetaInfo.begin(), initMetaInfo.end() }) {}

    explicit PortMetaInfo(const property_map &metaInfo) noexcept(true) { update<true>(metaInfo); }

    void
    reset() {
        auto_update = { "sample_rate", "signal_name", "signal_quantity", "signal_unit", "signal_min", "signal_max" };
    }

    template<bool isNoexcept = false>
    void
    update(const property_map &metaInfo) noexcept(isNoexcept) {
        if (metaInfo.empty()) {
            return;
        }

        auto updateValue = [&metaInfo](const std::string &key, auto &member) {
            if (!metaInfo.contains(key)) {
                return;
            }
            const auto &value = metaInfo.at(key);
            using T           = std::decay_t<decltype(member.value)>;
            if (std::holds_alternative<T>(value)) {
                member = std::get<T>(value);
            } else {
                throw gr::exception("invalid-argument: incorrect type for " + key);
            }
        };

        for (const auto &key : auto_update) {
            if (key == "sample_rate") {
                updateValue(key, sample_rate);
            } else if (key == "signal_name") {
                updateValue(key, signal_name);
            } else if (key == "signal_quantity") {
                updateValue(key, signal_quantity);
            } else if (key == "signal_unit") {
                updateValue(key, signal_unit);
            } else if (key == "signal_min") {
                updateValue(key, signal_min);
            } else if (key == "signal_max") {
                updateValue(key, signal_max);
            }
        }
    }

    [[nodiscard]] property_map
    get() const noexcept {
        property_map metaInfo;
        metaInfo["sample_rate"]     = sample_rate;
        metaInfo["signal_name"]     = signal_name;
        metaInfo["signal_quantity"] = signal_quantity;
        metaInfo["signal_unit"]     = signal_unit;
        metaInfo["signal_min"]      = signal_min;
        metaInfo["signal_max"]      = signal_max;

        return metaInfo;
    }
};

}
ENABLE_REFLECTION(gr::PortMetaInfo, sample_rate, signal_name, signal_quantity,signal_unit, signal_min, signal_max)

namespace gr {

/**
 * @brief Annotation for making a port asynchronous in a signal flow-graph block.
 *
 * In a standard block, the processing function is invoked based on the least common number of samples
 * available across all input and output ports. When a port is annotated with `Async`, it is excluded from this
 * least common number calculation.
 *
 * Applying `Async` as an optional template argument of the Port class essentially marks the port as "optional" for the
 * synchronization mechanism. The block's processing function will be invoked regardless of the number of samples
 * available at this specific port, relying solely on the state of other ports that are not marked as asynchronous.
 *
 * Use this annotation to create ports that do not constrain the block's ability to process data, making it
 * asynchronous relative to the other ports in the block.
 */
struct Async {};

/**
 * @brief 'ports' are interfaces that allows data to flow between blocks in a graph, similar to RF connectors.
 * Each block can have zero or more input/output ports. When connecting ports, either a single-step or a two-step
 * connection method can be used. Ports belong to a computing domain, such as CPU, GPU, or FPGA, and transitions
 * between domains require explicit data conversion.
 * Each port consists of a synchronous performance-optimised streaming and asynchronous tag communication component:
 *                                                                                      ┌───────────────────────
 *         ───────────────────┐                                       ┌─────────────────┤  <node/block definition>
 *             output-port    │                                       │    input-port   │  ...
 *          stream-buffer<T>  │>───────┬─────────────────┬───────────>│                 │
 *          tag-buffer<Tag>   │      tag#0             tag#1          │                 │
 *                            │                                       │                 │
 *         ───────────────────┘                                       └─────────────────┤
 *
 * Tags contain the index ID of the sending/receiving stream sample <T> they are attached to. Block implementations
 * may choose to chunk the data based on the MIN_SAMPLES/MAX_SAMPLES criteria only, or in addition break-up the stream
 * so that there is only one tag per scheduler iteration. Multiple tags on the same sample shall be merged to one.
 *
 * @tparam T the data type of the port. It can be any copyable preferably cache-aligned (i.e. 64 byte-sized) type.
 * @tparam portName a string to identify the port, notably to be used in an UI- and hand-written explicit code context.
 * @tparam portType STREAM  or MESSAGE
 * @tparam portDirection either input or output
 * @tparam Attributes optional: default to 'DefaultStreamBuffer' and DefaultTagBuffer' based on 'gr::circular_buffer', and CPU domain
 */
template<typename T, fixed_string portName, PortType portType, PortDirection portDirection, typename... Attributes>
struct Port {
    template<fixed_string newName, typename ReflDescriptor>
    using with_name_and_descriptor = Port<T, newName, portType, portDirection, ReflDescriptor, Attributes...>;

    static_assert(portDirection != PortDirection::ANY, "ANY reserved for queries and not port direction declarations");
    static_assert(portType != PortType::ANY, "ANY reserved for queries and not port type declarations");
    static_assert(portType == PortType::STREAM || std::is_same_v<T, gr::Message>, "If a port type is MESSAGE, the value type needs to be gr::Message");

    using value_type        = T;
    using AttributeTypeList = typename gr::meta::typelist<Attributes...>;
    using Domain            = AttributeTypeList::template find_or_default<is_port_domain, CPU>;
    using Required          = AttributeTypeList::template find_or_default<is_required_samples, RequiredSamples<std::dynamic_extent, std::dynamic_extent>>;
    using BufferType        = AttributeTypeList::template find_or_default<is_stream_buffer_attribute, DefaultStreamBuffer<T>>::type;
    using TagBufferType     = AttributeTypeList::template find_or_default<is_tag_buffer_attribute, DefaultTagBuffer>::type;
    using ReflDescriptor    = AttributeTypeList::template find_or_default<refl::trait::is_descriptor, std::false_type>;

    // constexpr members:
    static constexpr PortDirection kDirection = portDirection;
    static constexpr PortType      kPortType  = portType;
    static constexpr bool          kIsInput   = portDirection == PortDirection::INPUT;
    static constexpr bool          kIsOutput  = portDirection == PortDirection::OUTPUT;
    static constexpr fixed_string  Name       = portName;

    // dependent types
    using ReaderType    = decltype(std::declval<BufferType>().new_reader());
    using WriterType    = decltype(std::declval<BufferType>().new_writer());
    using IoType        = std::conditional_t<kIsInput, ReaderType, WriterType>;
    using TagReaderType = decltype(std::declval<TagBufferType>().new_reader());
    using TagWriterType = decltype(std::declval<TagBufferType>().new_writer());
    using TagIoType     = std::conditional_t<kIsInput, TagReaderType, TagWriterType>;

    // public properties
    constexpr static bool kIsSynch      = !std::disjunction_v<std::is_same<Async, Attributes>...>;
    constexpr static bool kIsOptional   = std::disjunction_v<std::is_same<Optional, Attributes>...>;
    std::string           name          = static_cast<std::string>(portName);
    std::int16_t          priority      = 0; // → dependents of a higher-prio port should be scheduled first (Q: make this by order of ports?)
    T                     default_value = T{};

    //
    std::conditional_t<Required::kIsConst, const std::size_t, std::size_t> min_samples = Required::kMinSamples;
    std::conditional_t<Required::kIsConst, const std::size_t, std::size_t> max_samples = Required::kMaxSamples;

    // Port meta-information for increased type and physical-unit safety. Uses ISO 80000-1:2022 conventions.
    PortMetaInfo metaInfo{};

private:
    bool      _connected    = false;
    IoType    _ioHandler    = newIoHandler();
    TagIoType _tagIoHandler = newTagIoHandler();
    Tag       _cachedTag{};

public:
    [[nodiscard]] constexpr bool
    initBuffer(std::size_t nSamples = 0) noexcept {
        if constexpr (kIsOutput) {
            // write one default value into output -- needed for cyclic graph initialisation
            return _ioHandler.try_publish([val = default_value](std::span<T> &out) { std::ranges::fill(out, val); }, nSamples);
        }
        return true;
    }

    [[nodiscard]] constexpr auto
    newIoHandler(std::size_t buffer_size = 65536) const noexcept {
        if constexpr (kIsInput) {
            return BufferType(buffer_size).new_reader();
        } else {
            return BufferType(buffer_size).new_writer();
        }
    }

    [[nodiscard]] constexpr auto
    newTagIoHandler(std::size_t buffer_size = 65536) const noexcept {
        if constexpr (kIsInput) {
            return TagBufferType(buffer_size).new_reader();
        } else {
            return TagBufferType(buffer_size).new_writer();
        }
    }

    [[nodiscard]] InternalPortBuffers
    writerHandlerInternal() noexcept {
        static_assert(kIsOutput, "only to be used with output ports");
        return { static_cast<void *>(std::addressof(_ioHandler)), static_cast<void *>(std::addressof(_tagIoHandler)) };
    }

    [[nodiscard]] bool
    updateReaderInternal(InternalPortBuffers buffer_writer_handler_other) noexcept {
        static_assert(kIsInput, "only to be used with input ports");

        if (buffer_writer_handler_other.streamHandler == nullptr) {
            return false;
        }
        if (buffer_writer_handler_other.tagHandler == nullptr) {
            return false;
        }

        // TODO: If we want to allow ports with different buffer types to be mixed
        //       this will fail. We need to add a check that two ports that
        //       connect to each other use the same buffer type
        //       (std::any could be a viable approach)
        auto typed_buffer_writer     = static_cast<WriterType *>(buffer_writer_handler_other.streamHandler);
        auto typed_tag_buffer_writer = static_cast<TagWriterType *>(buffer_writer_handler_other.tagHandler);
        setBuffer(typed_buffer_writer->buffer(), typed_tag_buffer_writer->buffer());
        return true;
    }

    constexpr Port()   = default;
    Port(const Port &) = delete;
    auto
    operator=(const Port &)
            = delete;

    Port(std::string port_name, std::int16_t priority_ = 0, std::size_t min_samples_ = 0UZ, std::size_t max_samples_ = SIZE_MAX) noexcept
        : name(std::move(port_name)), priority{ priority_ }, min_samples(min_samples_), max_samples(max_samples_) {
        static_assert(portName.empty(), "port name must be exclusively declared via NTTP or constructor parameter");
    }

    constexpr Port(Port &&other) noexcept
        : name(std::move(other.name))
        , priority{ other.priority }
        , min_samples(other.min_samples)
        , max_samples(other.max_samples)
        , _connected(other._connected)
        , _ioHandler(std::move(other._ioHandler))
        , _tagIoHandler(std::move(other._tagIoHandler)) {}

    constexpr Port &
    operator=(Port &&other)
            = delete;

    ~Port() = default;

    [[nodiscard]] constexpr bool
    isConnected() const noexcept {
        // TODO: check if this is correct for output ports, since there _connected is always false, return `readerCount > 0?`?
        return _connected;
    }

    [[nodiscard]] constexpr static PortType
    type() noexcept {
        return portType;
    }

    [[nodiscard]] constexpr static PortDirection
    direction() noexcept {
        return portDirection;
    }

    [[nodiscard]] constexpr static std::string_view
    domain() noexcept {
        return std::string_view(Domain::Name);
    }

    [[nodiscard]] constexpr static bool
    isSynchronous() noexcept {
        return kIsSynch;
    }

    [[nodiscard]] constexpr static bool
    isOptional() noexcept {
        return kIsOptional;
    }

    [[nodiscard]] constexpr static decltype(portName)
    static_name() noexcept
        requires(!portName.empty())
    {
        return portName;
    }

    [[nodiscard]] std::any
    defaultValue() const noexcept {
        return default_value;
    }

    [[nodiscard]] bool
    setDefaultValue(const std::any &newDefault) {
        if (newDefault.type() == typeid(T)) {
            default_value = std::any_cast<T>(newDefault);
            return true;
        }
        return false;
    }

    [[nodiscard]] constexpr static std::size_t
    available() noexcept {
        return 0;
    } //  ↔ maps to Buffer::Buffer[Reader, Writer].available()

    [[nodiscard]] constexpr std::size_t
    min_buffer_size() const noexcept {
        if constexpr (Required::kIsConst) {
            return Required::kMinSamples;
        } else {
            return min_samples;
        }
    }

    [[nodiscard]] constexpr std::size_t
    max_buffer_size() const noexcept {
        if constexpr (Required::kIsConst) {
            return Required::kMaxSamples;
        } else {
            return max_samples;
        }
    }

    [[nodiscard]] constexpr ConnectionResult
    resizeBuffer(std::size_t min_size) noexcept {
        using enum gr::ConnectionResult;
        if constexpr (kIsInput) {
            return SUCCESS;
        } else {
            try {
                _ioHandler    = BufferType(min_size).new_writer();
                _tagIoHandler = TagBufferType(min_size).new_writer();
            } catch (...) {
                return FAILED;
            }
        }
        return SUCCESS;
    }

    [[nodiscard]] auto
    buffer() {
        struct port_buffers {
            BufferType    streamBuffer;
            TagBufferType tagBuffer;
        };

        return port_buffers{ _ioHandler.buffer(), _tagIoHandler.buffer() };
    }

    void
    setBuffer(gr::Buffer auto streamBuffer, gr::Buffer auto tagBuffer) noexcept {
        if constexpr (kIsInput) {
            _ioHandler    = streamBuffer.new_reader();
            _tagIoHandler = tagBuffer.new_reader();
            _connected    = true;
        } else {
            _ioHandler    = streamBuffer.new_writer();
            _tagIoHandler = tagBuffer.new_writer();
        }
    }

    [[nodiscard]] constexpr const ReaderType &
    streamReader() const noexcept {
        static_assert(!kIsOutput, "streamReader() not applicable for outputs (yet)");
        return _ioHandler;
    }

    [[nodiscard]] constexpr ReaderType &
    streamReader() noexcept {
        static_assert(!kIsOutput, "streamReader() not applicable for outputs (yet)");
        return _ioHandler;
    }

    [[nodiscard]] constexpr const WriterType &
    streamWriter() const noexcept {
        static_assert(!kIsInput, "streamWriter() not applicable for inputs (yet)");
        return _ioHandler;
    }

    [[nodiscard]] constexpr WriterType &
    streamWriter() noexcept {
        static_assert(!kIsInput, "streamWriter() not applicable for inputs (yet)");
        return _ioHandler;
    }

    [[nodiscard]] constexpr const TagReaderType &
    tagReader() const noexcept {
        static_assert(!kIsOutput, "tagReader() not applicable for outputs (yet)");
        return _tagIoHandler;
    }

    [[nodiscard]] constexpr TagReaderType &
    tagReader() noexcept {
        static_assert(!kIsOutput, "tagReader() not applicable for outputs (yet)");
        return _tagIoHandler;
    }

    [[nodiscard]] constexpr const TagWriterType &
    tagWriter() const noexcept {
        static_assert(!kIsInput, "tagWriter() not applicable for inputs (yet)");
        return _tagIoHandler;
    }

    [[nodiscard]] constexpr TagWriterType &
    tagWriter() noexcept {
        static_assert(!kIsInput, "tagWriter() not applicable for inputs (yet)");
        return _tagIoHandler;
    }

    [[nodiscard]] ConnectionResult
    disconnect() noexcept {
        if (_connected == false) {
            return ConnectionResult::FAILED;
        }
        _ioHandler    = newIoHandler();
        _tagIoHandler = newTagIoHandler();
        _connected    = false;
        return ConnectionResult::SUCCESS;
    }

    template<typename Other>
    [[nodiscard]] ConnectionResult
    connect(Other &&other) {
        static_assert(kIsOutput && std::remove_cvref_t<Other>::kIsInput);
        auto src_buffer = writerHandlerInternal();
        return std::forward<Other>(other).updateReaderInternal(src_buffer) ? ConnectionResult::SUCCESS : ConnectionResult::FAILED;
    }

    /**
     * @return get all (incl. past unconsumed) tags () until the read-position + optional offset
     */
    inline constexpr std::span<const Tag>
    getTags(Tag::signed_index_type untilOffset = 0) noexcept
        requires(kIsInput)
    {
        const auto  readPos           = streamReader().position();
        const auto  tags              = tagReader().get(tagReader().available()); // N.B. returns all old/available/pending tags
        std::size_t nTagsProcessed    = 0UZ;
        bool        properTagDistance = false;

        for (const Tag &tag : tags) {
            const auto relativeTagPosition = (tag.index - readPos); // w.r.t. present stream reader position
            const bool tagIsWithinRange    = (tag.index != -1) && relativeTagPosition <= untilOffset;
            if ((!properTagDistance && tag.index < 0) || tagIsWithinRange) { // 'index == -1' wildcard Tag index -> process unconditionally
                nTagsProcessed++;
                if (tagIsWithinRange) { // detected regular Tag position, ignore and stop at further wildcard Tags
                    properTagDistance = true;
                }
            } else {
                break; // Tag is wildcard (index == -1) after a regular or newer than the present reading position (+ offset)
            }
        }
        return tags.first(nTagsProcessed);
    }

    inline const Tag
    getTag(Tag::signed_index_type untilOffset = 0)
        requires(kIsInput)
    {
        const auto readPos = streamReader().position();
        if (_cachedTag.index == readPos && readPos >= 0) {
            return _cachedTag;
        }
        _cachedTag.reset();

        auto mergeSrcMapInto = [](const property_map &sourceMap, property_map &destinationMap) {
            assert(&sourceMap != &destinationMap);
            for (const auto &[key, value] : sourceMap) {
                destinationMap.insert_or_assign(key, value);
            }
        };

        const auto tags  = getTags(untilOffset);
        _cachedTag.index = readPos;
        std::ranges::for_each(tags, [&mergeSrcMapInto, this](const Tag &tag) { mergeSrcMapInto(tag.map, _cachedTag.map); });
        std::ignore = tagReader().consume(tags.size());

        return _cachedTag;
    }

    inline constexpr void
    publishTag(property_map &&tag_data, Tag::signed_index_type tagOffset = -1) noexcept
        requires(kIsOutput)
    {
        processPublishTag(std::move(tag_data), tagOffset);
    }

    inline constexpr void
    publishTag(const property_map &tag_data, Tag::signed_index_type tagOffset = -1) noexcept
        requires(kIsOutput)
    {
        processPublishTag(tag_data, tagOffset);
    }

    [[maybe_unused]] inline constexpr bool
    publishPendingTags() noexcept
        requires(kIsOutput)
    {
        if (_cachedTag.map.empty() /*|| streamWriter().buffer().n_readers() == 0UZ*/) {
            return false;
        }
        auto outTags     = tagWriter().reserve(1UZ);
        outTags[0].index = _cachedTag.index;
        outTags[0].map   = _cachedTag.map;
        outTags.publish(1UZ);

        _cachedTag.reset();
        return true;
    }

private:
    template<PropertyMapType PropertyMap>
    inline constexpr void
    processPublishTag(PropertyMap &&tag_data, Tag::signed_index_type tagOffset) noexcept {
        const auto newTagIndex = tagOffset < 0 ? tagOffset : streamWriter().position() + tagOffset;

        if (tagOffset >= 0 && (_cachedTag.index != newTagIndex && _cachedTag.index != -1)) { // do not cache tags that have an explicit index
            publishPendingTags();
        }
        _cachedTag.index = newTagIndex;
        if constexpr (std::is_rvalue_reference_v<PropertyMap &&>) { // -> move semantics
            for (auto &[key, value] : tag_data) {
                _cachedTag.map.insert_or_assign(std::move(key), std::move(value));
            }
        } else { // -> copy semantics
            for (const auto &[key, value] : tag_data) {
                _cachedTag.map.insert_or_assign(key, value);
            }
        }

        if (tagOffset != -1L || _cachedTag.map.contains(gr::tag::END_OF_STREAM)) { // force tag publishing for explicitly published tags or EOS
            publishPendingTags();
        }
    }

    friend class DynamicPort;
};

namespace detail {
template<typename T, auto>
using just_t = T;

template<typename T, fixed_string baseName, PortType portType, PortDirection portDirection, typename... Attributes, std::size_t... Is>
consteval gr::meta::typelist<just_t<Port<T, baseName + meta::make_fixed_string<Is>(), portType, portDirection, Attributes...>, Is>...>
repeated_ports_impl(std::index_sequence<Is...>) {
    return {};
}
} // namespace detail

template<std::size_t count, typename T, fixed_string baseName, PortType portType, PortDirection portDirection, typename... Attributes>
using repeated_ports = decltype(detail::repeated_ports_impl<T, baseName, portType, portDirection, Attributes...>(std::make_index_sequence<count>()));

static_assert(repeated_ports<3, float, "out", PortType::STREAM, PortDirection::OUTPUT, Optional>::at<0>::Name == fixed_string("out0"));
static_assert(repeated_ports<3, float, "out", PortType::STREAM, PortDirection::OUTPUT, Optional>::at<1>::Name == fixed_string("out1"));
static_assert(repeated_ports<3, float, "out", PortType::STREAM, PortDirection::OUTPUT, Optional>::at<2>::Name == fixed_string("out2"));

template<typename T, typename... Attributes>
using PortIn = Port<T, "", PortType::STREAM, PortDirection::INPUT, Attributes...>;
template<typename T, typename... Attributes>
using PortOut = Port<T, "", PortType::STREAM, PortDirection::OUTPUT, Attributes...>;
template<typename T, fixed_string PortName, typename... Attributes>
using PortInNamed = Port<T, PortName, PortType::STREAM, PortDirection::INPUT, Attributes...>;
template<typename T, fixed_string PortName, typename... Attributes>
using PortOutNamed = Port<T, PortName, PortType::STREAM, PortDirection::OUTPUT, Attributes...>;

using MsgPortIn  = Port<Message, "", PortType::MESSAGE, PortDirection::INPUT, DefaultMessageBuffer>;
using MsgPortOut = Port<Message, "", PortType::MESSAGE, PortDirection::OUTPUT, DefaultMessageBuffer>;
template<fixed_string PortName, typename... Attributes>
using MsgPortInNamed = Port<Message, PortName, PortType::MESSAGE, PortDirection::INPUT, DefaultMessageBuffer, Attributes...>;
template<fixed_string PortName, typename... Attributes>
using MsgPortOutNamed = Port<Message, PortName, PortType::MESSAGE, PortDirection::OUTPUT, DefaultMessageBuffer, Attributes...>;

static_assert(PortLike<PortIn<float>>);
static_assert(PortLike<decltype(PortIn<float>())>);
static_assert(PortLike<PortOut<float>>);
static_assert(PortLike<MsgPortIn>);
static_assert(PortLike<MsgPortOut>);
static_assert(PortLike<PortInNamed<float, "test">>);
static_assert(PortLike<PortOutNamed<float, "test">>);

static_assert(std::is_same_v<MsgPortIn::BufferType, gr::CircularBuffer<Message, std::dynamic_extent, gr::ProducerType::Multi>>);

static_assert(PortIn<float, RequiredSamples<1, 2>>::Required::kMinSamples == 1);
static_assert(PortIn<float, RequiredSamples<1, 2>>::Required::kMaxSamples == 2);
static_assert(std::same_as<PortIn<float, RequiredSamples<1, 2>>::Domain, CPU>);
static_assert(std::same_as<PortIn<float, RequiredSamples<1, 2>, GPU>::Domain, GPU>);

static_assert(MsgPortOutNamed<"out_msg">::static_name() == fixed_string("out_msg"));
static_assert(!(MsgPortOutNamed<"out_msg">::with_name_and_descriptor<"out_message", std::false_type>::static_name() == fixed_string("out_msg")));
static_assert(MsgPortOutNamed<"out_msg">::with_name_and_descriptor<"out_message", std::false_type>::static_name() == fixed_string("out_message"));

static_assert(PortIn<float>::kPortType == PortType::STREAM);
static_assert(PortIn<Message>::kPortType == PortType::STREAM);
static_assert(MsgPortIn::kPortType == PortType::MESSAGE);

/**
 *  Runtime capable wrapper to be used within a block. It's primary purpose is to allow the runtime
 *  initialisation/connections between blocks that are not in the same compilation unit.
 *  Ownership is defined by if the strongly-typed port P is either passed
 *  a) as an lvalue (i.e. P& -> keep reference), or
 *  b) as an rvalue (P&& -> being moved into dyn_port).
 *
 *  N.B. the intended use is within the node/block interface where there is -- once initialised --
 *  always a strong-reference between the strongly-typed port and it's dyn_port wrapper. I.e no ports
 *  are added or removed after the initialisation and the port life-time is coupled to that of it's
 *  parent block/node.
 */
class DynamicPort {
public:
    const std::string &name;
    std::int16_t      &priority; // → dependents of a higher-prio port should be scheduled first (Q: make this by order of ports?)
    std::size_t       &min_samples;
    std::size_t       &max_samples;

private:
    struct model { // intentionally class-private definition to limit interface exposure and enhance composition
        virtual ~model() = default;

        [[nodiscard]] virtual std::any
        defaultValue() const noexcept
                = 0;

        [[nodiscard]] virtual bool
        setDefaultValue(const std::any &val) noexcept
                = 0;

        [[nodiscard]] virtual PortType
        type() const noexcept
                = 0;

        [[nodiscard]] virtual PortDirection
        direction() const noexcept
                = 0;

        [[nodiscard]] virtual std::string_view
        domain() const noexcept
                = 0;

        [[nodiscard]] virtual bool
        isSynchronous() noexcept
                = 0;

        [[nodiscard]] virtual bool
        isOptional() noexcept
                = 0;

        [[nodiscard]] virtual ConnectionResult
        resizeBuffer(std::size_t min_size) noexcept
                = 0;

        [[nodiscard]] virtual ConnectionResult
        disconnect() noexcept
                = 0;

        [[nodiscard]] virtual ConnectionResult
        connect(DynamicPort &dst_port)
                = 0;

        // internal runtime polymorphism access
        [[nodiscard]] virtual bool
        updateReaderInternal(InternalPortBuffers buffer_other) noexcept
                = 0;
    };

    std::unique_ptr<model> _accessor;

    template<PortLike T, bool owning>
    class wrapper final : public model {
        using TPortType = std::decay_t<T>;
        std::conditional_t<owning, TPortType, TPortType &> _value;

        [[nodiscard]] InternalPortBuffers
        writerHandlerInternal() noexcept {
            return _value.writerHandlerInternal();
        };

        [[nodiscard]] bool
        updateReaderInternal(InternalPortBuffers buffer_other) noexcept override {
            if constexpr (T::kIsInput) {
                return _value.updateReaderInternal(buffer_other);
            } else {
                assert(false && "This works only on input ports");
                return false;
            }
        }

    public:
        wrapper() = delete;

        wrapper(const wrapper &) = delete;

        auto &
        operator=(const wrapper &)
                = delete;

        auto &
        operator=(wrapper &&)
                = delete;

        explicit constexpr wrapper(T &arg) noexcept : _value{ arg } {
            if constexpr (T::kIsInput) {
                static_assert(requires { arg.writerHandlerInternal(); }, "'private void* writerHandlerInternal()' not implemented");
            } else {
                static_assert(requires { arg.updateReaderInternal(std::declval<InternalPortBuffers>()); }, "'private bool updateReaderInternal(void* buffer)' not implemented");
            }
        }

        explicit constexpr wrapper(T &&arg) noexcept : _value{ std::move(arg) } {
            if constexpr (T::kIsInput) {
                static_assert(requires { arg.writerHandlerInternal(); }, "'private void* writerHandlerInternal()' not implemented");
            } else {
                static_assert(requires { arg.updateReaderInternal(std::declval<InternalPortBuffers>()); }, "'private bool updateReaderInternal(void* buffer)' not implemented");
            }
        }

        ~wrapper() override = default;

        [[nodiscard]] std::any
        defaultValue() const noexcept override {
            return _value.defaultValue();
        }

        [[nodiscard]] bool
        setDefaultValue(const std::any &val) noexcept override {
            return _value.setDefaultValue(val);
        }

        [[nodiscard]] constexpr PortType
        type() const noexcept override {
            return _value.type();
        }

        [[nodiscard]] constexpr PortDirection
        direction() const noexcept override {
            return _value.direction();
        }

        [[nodiscard]] constexpr std::string_view
        domain() const noexcept override {
            return _value.domain();
        }

        [[nodiscard]] bool
        isSynchronous() noexcept override {
            return _value.isSynchronous();
        }

        [[nodiscard]] bool
        isOptional() noexcept override {
            return _value.isOptional();
        }

        [[nodiscard]] ConnectionResult
        resizeBuffer(std::size_t min_size) noexcept override {
            return _value.resizeBuffer(min_size);
        }

        [[nodiscard]] ConnectionResult
        disconnect() noexcept override {
            return _value.disconnect();
        }

        [[nodiscard]] ConnectionResult
        connect(DynamicPort &dst_port) override {
            using enum gr::ConnectionResult;
            if constexpr (T::kIsOutput) {
                auto src_buffer = _value.writerHandlerInternal();
                return dst_port.updateReaderInternal(src_buffer) ? SUCCESS : FAILED;
            } else {
                assert(false && "This works only on input ports");
                return FAILED;
            }
        }
    };

    bool
    updateReaderInternal(InternalPortBuffers buffer_other) noexcept {
        return _accessor->updateReaderInternal(buffer_other);
    }

public:
    using value_type = void; // a sterile port

    struct owned_value_tag {};

    struct non_owned_reference_tag {};

    constexpr DynamicPort() = delete;

    DynamicPort(const DynamicPort &arg) = delete;
    DynamicPort &
    operator=(const DynamicPort &arg)
            = delete;

    DynamicPort(DynamicPort &&arg) = default;
    DynamicPort &
    operator=(DynamicPort &&arg)
            = delete;

    // TODO: The lifetime of ports is a problem here, if we keep
    // a reference to the port in DynamicPort, the port object
    // can not be reallocated
    template<PortLike T>
    explicit constexpr DynamicPort(T &arg, non_owned_reference_tag) noexcept
        : name(arg.name), priority(arg.priority), min_samples(arg.min_samples), max_samples(arg.max_samples), _accessor{ std::make_unique<wrapper<T, false>>(arg) } {}

    template<PortLike T>
    explicit constexpr DynamicPort(T &&arg, owned_value_tag) noexcept
        : name(arg.name), priority(arg.priority), min_samples(arg.min_samples), max_samples(arg.max_samples), _accessor{ std::make_unique<wrapper<T, true>>(std::forward<T>(arg)) } {}

    [[nodiscard]] std::any
    defaultValue() const noexcept {
        return _accessor->defaultValue();
    }

    [[nodiscard]] bool
    setDefaultValue(const std::any &val) noexcept {
        return _accessor->setDefaultValue(val);
    }

    [[nodiscard]] PortType
    type() const noexcept {
        return _accessor->type();
    }

    [[nodiscard]] PortDirection
    direction() const noexcept {
        return _accessor->direction();
    }

    [[nodiscard]] std::string_view
    domain() const noexcept {
        return _accessor->domain();
    }

    [[nodiscard]] bool
    isSynchronous() noexcept {
        return _accessor->isSynchronous();
    }

    [[nodiscard]] bool
    isOptional() noexcept {
        return _accessor->isOptional();
    }

    [[nodiscard]] ConnectionResult
    resizeBuffer(std::size_t min_size) {
        if (direction() == PortDirection::OUTPUT) {
            return _accessor->resizeBuffer(min_size);
        }
        return ConnectionResult::FAILED;
    }

    [[nodiscard]] ConnectionResult
    disconnect() noexcept {
        return _accessor->disconnect();
    }

    [[nodiscard]] ConnectionResult
    connect(DynamicPort &dst_port) {
        return _accessor->connect(dst_port);
    }
};

static_assert(PortLike<DynamicPort>);

namespace detail {
template<typename T>
concept TagPredicate = requires(const T &t, const Tag &tag, Tag::signed_index_type readPosition) {
    { t(tag, readPosition) } -> std::convertible_to<bool>;
};
inline constexpr TagPredicate auto defaultTagMatcher    = [](const Tag &tag, Tag::signed_index_type readPosition) noexcept { return tag.index >= readPosition; };
inline constexpr TagPredicate auto defaultEOSTagMatcher = [](const Tag &tag, Tag::signed_index_type readPosition) noexcept {
    auto eosTagIter = tag.map.find(gr::tag::END_OF_STREAM);
    if (eosTagIter != tag.map.end() && eosTagIter->second == true) {
        if (tag.index >= readPosition || tag.index < 0) {
            return true;
        }
    }
    return false;
};
} // namespace detail

inline constexpr std::optional<std::size_t>
nSamplesToNextTagConditional(const PortLike auto &port, detail::TagPredicate auto &predicate, Tag::signed_index_type readOffset) {
    const auto                    available = port.tagReader().available();
    const gr::ConsumableSpan auto tagData   = port.tagReader().get(available);
    if (!port.isConnected() || tagData.empty()) [[likely]] {
        return std::nullopt; // default: no tags in sight
    }
    const Tag::signed_index_type readPosition = port.streamReader().position();

    // at least one tag is present -> if tag is not on the first tag position read up to the tag position, or if the tag has a special 'index = -1'
    const auto firstMatchingTag = std::ranges::find_if(tagData, [&](const auto &tag) { return predicate(tag, readPosition + readOffset); });
    if (firstMatchingTag != tagData.end()) {
        return static_cast<std::size_t>(std::max(firstMatchingTag->index - readPosition, Tag::signed_index_type(0))); // Tags in the past will have a negative distance -> deliberately map them to '0'
    } else {
        return std::nullopt;
    }
}

inline constexpr std::optional<std::size_t>
nSamplesUntilNextTag(const PortLike auto &port, Tag::signed_index_type offset = 0) {
    return nSamplesToNextTagConditional(port, detail::defaultTagMatcher, offset);
}

inline constexpr std::optional<std::size_t>
samples_to_eos_tag(const PortLike auto &port, Tag::signed_index_type offset = 0) {
    return nSamplesToNextTagConditional(port, detail::defaultEOSTagMatcher, offset);
}

} // namespace gr
ENABLE_REFLECTION_FOR_TEMPLATE_FULL((typename T, gr::fixed_string portName, gr::PortType portType, gr::PortDirection portDirection, typename... Attributes), (gr::Port<T, portName, portType, portDirection, Attributes...>), kDirection, kPortType, kIsInput, kIsOutput, kIsSynch, kIsOptional, name, priority, min_samples, max_samples, metaInfo)

#endif // include guard

// #include "PortTraits.hpp"
#ifndef GNURADIO_NODE_PORT_TRAITS_HPP
#define GNURADIO_NODE_PORT_TRAITS_HPP

// #include <gnuradio-4.0/meta/utils.hpp>


// #include "Port.hpp"


namespace gr::traits::port {

template<typename T>
concept HasFixedInfo = requires {
    typename T::value_type;
    { T::static_name() };
    { T::direction() } -> std::same_as<PortDirection>;
    { T::type() } -> std::same_as<PortType>;
};

template<typename T>
using has_fixed_info = std::integral_constant<bool, HasFixedInfo<T>>;

template<typename T>
struct has_fixed_info_or_is_typelist : std::false_type {};

template<typename T>
    requires HasFixedInfo<T>
struct has_fixed_info_or_is_typelist<T> : std::true_type {};

template<typename T>
    requires(meta::is_typelist_v<T> and T::template all_of<has_fixed_info>)
struct has_fixed_info_or_is_typelist<T> : std::true_type {};

template<typename Port>
using is_input = std::integral_constant<bool, Port::direction() == PortDirection::INPUT>;

template<typename Port>
concept is_input_v = is_input<Port>::value;

template<typename Port>
using is_output = std::integral_constant<bool, Port::direction() == PortDirection::OUTPUT>;

template<typename Port>
concept is_output_v = is_output<Port>::value;

template<typename Type>
concept is_port_v = is_output_v<Type> || is_input_v<Type>;

template<typename Type>
using is_port = std::integral_constant<bool, is_port_v<Type>>;

template<typename Collection>
concept is_port_collection_v = is_port_v<typename Collection::value_type>;

template<typename T>
auto
unwrap_port_helper() {
    if constexpr (port::is_port_v<T>) {
        return static_cast<T *>(nullptr);
    } else if constexpr (port::is_port_collection_v<T>) {
        return static_cast<typename T::value_type *>(nullptr);
    } else {
        meta::print_types<meta::message_type<"Is not a port or a collection of ports">, T>{};
    }
}

template<typename T>
using unwrap_port = std::remove_pointer_t<decltype(unwrap_port_helper<T>())>;

struct kind {
    template<PortType matcherPortType>
    struct tester_for {
        template<typename Port>
        static constexpr bool matches_kind = matcherPortType == PortType::ANY || matcherPortType == Port::kPortType;

        template<typename T>
        constexpr static bool
        is_port_or_collection_helper() {
            if constexpr (port::is_port_v<T> || port::is_port_collection_v<T>) {
                return matches_kind<unwrap_port<T>>;
            } else {
                return false;
            }
        }

        template<typename T>
        using is_port_or_collection = std::integral_constant<bool, is_port_or_collection_helper<T>()>;

        template<typename T>
        using is_input_port_or_collection = std::integral_constant<bool, is_port_or_collection<T>() && port::is_input_v<unwrap_port<T>>>;

        template<typename T>
        using is_output_port_or_collection = std::integral_constant<bool, is_port_or_collection<T>() && port::is_output_v<unwrap_port<T>>>;
    };
};

template<typename PortOrCollection>
auto
type_helper() {
    if constexpr (is_port_v<PortOrCollection>) {
        return static_cast<typename PortOrCollection::value_type *>(nullptr);
    } else {
        return static_cast<std::vector<typename PortOrCollection::value_type::value_type> *>(nullptr);
    }
}

template<typename PortOrCollection>
using type = std::remove_pointer_t<decltype(type_helper<PortOrCollection>())>;

template<typename... Ports>
struct min_samples : std::integral_constant<std::size_t, std::max({ Ports::Required::kMinSamples... })> {};

template<typename... Ports>
struct max_samples : std::integral_constant<std::size_t, std::max({ Ports::Required::kMaxSamples... })> {};

template<typename Type>
constexpr bool is_not_any_port_or_collection = !gr::traits::port::kind::tester_for<PortType::ANY>::is_port_or_collection<Type>();

} // namespace gr::traits::port

#endif // include guard

// #include "reflection.hpp"


#include <algorithm> // TODO: simd misses the algorithm dependency for std::clamp(...) -> add to simd
// #include <vir/simd.h>


namespace gr::work {
enum class Status;
}

namespace gr::traits::block {

namespace detail {

template<typename FieldDescriptor>
using member_type = typename FieldDescriptor::value_type;

template<typename Port>
constexpr bool is_port_descriptor_v = port::is_port_v<member_type<Port>>;

template<typename Collection>
constexpr bool is_port_collection_descriptor_v = port::is_port_collection_v<member_type<Collection>>;

template<typename Descriptor>
using is_port_or_collection_descriptor = std::integral_constant<bool, is_port_descriptor_v<Descriptor> || is_port_collection_descriptor_v<Descriptor>>;

template<typename Descriptor>
constexpr auto
member_to_named_port_helper() {
    // Collections of ports don't get names inside the type as
    // the ports inside are dynamically created
    if constexpr (is_port_descriptor_v<Descriptor>) {
        return static_cast<typename Descriptor::value_type::template with_name_and_descriptor<fixed_string(refl::descriptor::get_name(Descriptor()).data), Descriptor> *>(nullptr);
    } else if constexpr (is_port_collection_descriptor_v<Descriptor>) {
        if constexpr (gr::meta::is_std_array_type<typename Descriptor::value_type>()) {
            auto value_type_updater = []<template<typename, auto> typename Template, typename Arg, auto Size>(Template<Arg, Size> *) {
                return static_cast< //
                        Template<typename Arg::template with_name_and_descriptor<fixed_string(refl::descriptor::get_name(Descriptor()).data), Descriptor>, Size> *>(nullptr);
            };
            return value_type_updater(static_cast<typename Descriptor::value_type *>(nullptr));
        } else {
            auto value_type_updater = []<template<typename...> typename Template, typename Arg, typename... Args>(Template<Arg, Args...> *) {
                // This type is not going to be used for a variable, it is just meant to be
                // a compile-time hint of what the port collection looks like.
                // We're ignoring the Args... because they might depend on the
                // main type (for example, allocator in a vector)
                return static_cast<Template<typename Arg::template with_name_and_descriptor<fixed_string(refl::descriptor::get_name(Descriptor()).data), Descriptor>> *>(nullptr);
            };
            return value_type_updater(static_cast<typename Descriptor::value_type *>(nullptr));
        }
    } else {
        return static_cast<void *>(nullptr);
    }
}

template<typename Descriptor>
using member_to_named_port = std::remove_pointer_t<decltype(member_to_named_port_helper<Descriptor>())>;

template<typename TBlock>
struct member_ports_detector {
    static constexpr bool value = false;
};

template<class T, typename ValueType = std::remove_cvref_t<T>>
concept Reflectable = refl::is_reflectable<ValueType>();

template<Reflectable TBlock>
struct member_ports_detector<TBlock> {
    using member_ports = typename meta::to_typelist<refl::descriptor::member_list<TBlock>>::template filter<is_port_or_collection_descriptor>::template transform<member_to_named_port>;

    static constexpr bool value = member_ports::size != 0;
};

template<typename TBlock>
using port_name = typename TBlock::static_name();

template<typename RequestedType>
struct member_descriptor_has_type {
    template<typename Descriptor>
    using matches = std::is_same<RequestedType, member_to_named_port<Descriptor>>;
};

} // namespace detail

template<typename...>
struct fixedBlock_ports_data_helper;

// This specialization defines block attributes when the block is created
// with two type lists - one list for input and one for output ports
template<typename TBlock, meta::is_typelist_v InputPorts, meta::is_typelist_v OutputPorts>
    requires(InputPorts::template all_of<port::has_fixed_info> && OutputPorts::template all_of<port::has_fixed_info>)
struct fixedBlock_ports_data_helper<TBlock, InputPorts, OutputPorts> {
    using member_ports_detector = std::false_type;

    using defined_input_ports  = InputPorts;
    using defined_output_ports = OutputPorts;

    template<gr::PortType portType>
    struct for_type {
        using input_ports  = typename defined_input_ports ::template filter<traits::port::kind::tester_for<portType>::template is_input_port_or_collection>;
        using output_ports = typename defined_output_ports ::template filter<traits::port::kind::tester_for<portType>::template is_output_port_or_collection>;
        using all_ports    = meta::concat<input_ports, output_ports>;

        using input_port_types  = typename input_ports ::template transform<port::type>;
        using output_port_types = typename output_ports ::template transform<port::type>;
    };

    using all     = for_type<PortType::ANY>;
    using stream  = for_type<PortType::STREAM>;
    using message = for_type<PortType::MESSAGE>;
};

// This specialization defines block attributes when the block is created
// with a list of ports as template arguments
template<typename TBlock, port::HasFixedInfo... Ports>
struct fixedBlock_ports_data_helper<TBlock, Ports...> {
    using member_ports_detector = detail::member_ports_detector<TBlock>;

    using all_ports = std::remove_pointer_t<decltype([] {
        if constexpr (member_ports_detector::value) {
            return static_cast<typename member_ports_detector::member_ports *>(nullptr);
        } else {
            return static_cast<typename meta::concat<std::conditional_t<gr::meta::is_typelist_v<Ports>, Ports, meta::typelist<Ports>>...> *>(nullptr);
        }
    }())>;

    template<PortType portType>
    struct for_type {
        using input_ports  = typename all_ports ::template filter<traits::port::kind::tester_for<portType>::template is_input_port_or_collection>;
        using output_ports = typename all_ports ::template filter<traits::port::kind::tester_for<portType>::template is_output_port_or_collection>;

        using input_port_types  = typename input_ports ::template transform<port::type>;
        using output_port_types = typename output_ports ::template transform<port::type>;
    };

    using all     = for_type<PortType::ANY>;
    using stream  = for_type<PortType::STREAM>;
    using message = for_type<PortType::MESSAGE>;
};

// clang-format off
template<typename TBlock,
         typename TDerived = typename TBlock::derived_t,
         typename ArgumentList = typename TBlock::block_template_parameters>
using fixedBlock_ports_data =
    typename ArgumentList::template filter<port::has_fixed_info_or_is_typelist>
                         ::template prepend<TBlock>
                         ::template apply<fixedBlock_ports_data_helper>;
// clang-format on

template<typename TBlock>
using ports_data = fixedBlock_ports_data<TBlock>;

template<typename TBlock>
using all_input_ports = typename fixedBlock_ports_data<TBlock>::all::input_ports;

template<typename TBlock>
using all_output_ports = typename fixedBlock_ports_data<TBlock>::all::output_ports;

template<typename TBlock>
using all_input_port_types = typename fixedBlock_ports_data<TBlock>::all::input_port_types;

template<typename TBlock>
using all_output_port_types = typename fixedBlock_ports_data<TBlock>::all::output_port_types;

template<typename TBlock>
using all_input_port_types_tuple = typename all_input_port_types<TBlock>::tuple_type;

template<typename TBlock>
using stream_input_ports = typename fixedBlock_ports_data<TBlock>::stream::input_ports;

template<typename TBlock>
using stream_output_ports = typename fixedBlock_ports_data<TBlock>::stream::output_ports;

template<typename TBlock>
using stream_input_port_types = typename fixedBlock_ports_data<TBlock>::stream::input_port_types;

template<typename TBlock>
using stream_output_port_types = typename fixedBlock_ports_data<TBlock>::stream::output_port_types;

template<typename TBlock>
using stream_input_port_types_tuple = typename stream_input_port_types<TBlock>::tuple_type;

template<typename TBlock>
using stream_return_type = typename fixedBlock_ports_data<TBlock>::stream::output_port_types::tuple_or_type;

template<typename TBlock>
using all_input_port_names = typename all_input_ports<TBlock>::template transform<detail::port_name>;

template<typename TBlock>
using all_output_port_names = typename all_output_ports<TBlock>::template transform<detail::port_name>;

template<typename TBlock>
constexpr bool block_defines_ports_as_member_variables = fixedBlock_ports_data<TBlock>::member_ports_detector::value;

template<typename TBlock, typename TPortType>
using get_port_member_descriptor = typename meta::to_typelist<refl::descriptor::member_list<TBlock>>::template filter<detail::is_port_or_collection_descriptor>::template filter<
        detail::member_descriptor_has_type<TPortType>::template matches>::template at<0>;

// TODO: Why is this not done with requires?
namespace detail {
template<std::size_t... Is>
auto
can_processOne_invoke_test(auto &block, const auto &input, std::index_sequence<Is...>) -> decltype(block.processOne(std::get<Is>(input)...));

template<typename T>
struct exact_argument_type {
    template<std::same_as<T> U>
    constexpr
    operator U() const noexcept;
};

template<std::size_t... Is>
auto
can_processOne_with_offset_invoke_test(auto &block, const auto &input, std::index_sequence<Is...>) -> decltype(block.processOne(exact_argument_type<std::size_t>(), std::get<Is>(input)...));

template<typename TBlock>
using simd_return_type_of_can_processOne = meta::simdize<stream_return_type<TBlock>, meta::simdize_size_v<meta::simdize<stream_input_port_types_tuple<TBlock>>>>;
} // namespace detail

/* A block "can process simd" if its `processOne` function takes at least one argument and all
 * arguments can be simdized types of the actual port data types.
 *
 * The block can be a sink (no output ports).
 * The requirement of at least one function argument disallows sources.
 *
 * There is another (unnamed) concept for source nodes: Source nodes can implement
 * `processOne_simd(integral_constant)`, which returns SIMD object(s) of width N.
 */
template<typename TBlock>
concept can_processOne_simd =
#if DISABLE_SIMD
        false;
#else
        traits::block::stream_input_ports<TBlock>::template all_of<port::is_port> and // checks we don't have port collections inside
        traits::block::stream_input_port_types<TBlock>::size() > 0 and requires(TBlock &block, const meta::simdize<stream_input_port_types_tuple<TBlock>> &input_simds) {
            {
                detail::can_processOne_invoke_test(block, input_simds, std::make_index_sequence<traits::block::stream_input_ports<TBlock>::size()>())
            } -> std::same_as<detail::simd_return_type_of_can_processOne<TBlock>>;
        };
#endif

template<typename TBlock>
concept can_processOne_simd_with_offset =
#if DISABLE_SIMD
        false;
#else
        traits::block::stream_input_ports<TBlock>::template all_of<port::is_port> and // checks we don't have port collections inside
        traits::block::stream_input_port_types<TBlock>::size() > 0 && requires(TBlock &block, const meta::simdize<stream_input_port_types_tuple<TBlock>> &input_simds) {
            {
                detail::can_processOne_with_offset_invoke_test(block, input_simds, std::make_index_sequence<traits::block::stream_input_ports<TBlock>::size()>())
            } -> std::same_as<detail::simd_return_type_of_can_processOne<TBlock>>;
        };
#endif

template<typename TBlock>
concept can_processOne_scalar = requires(TBlock &block, const stream_input_port_types_tuple<TBlock> &inputs) {
    { detail::can_processOne_invoke_test(block, inputs, std::make_index_sequence<traits::block::stream_input_ports<TBlock>::size()>()) } -> std::same_as<stream_return_type<TBlock>>;
};

template<typename TBlock>
concept can_processOne_scalar_with_offset = requires(TBlock &block, const stream_input_port_types_tuple<TBlock> &inputs) {
    { detail::can_processOne_with_offset_invoke_test(block, inputs, std::make_index_sequence<traits::block::stream_input_ports<TBlock>::size()>()) } -> std::same_as<stream_return_type<TBlock>>;
};

template<typename TBlock>
concept can_processOne = can_processOne_scalar<TBlock> or can_processOne_simd<TBlock> or can_processOne_scalar_with_offset<TBlock> or can_processOne_simd_with_offset<TBlock>;

template<typename TBlock>
concept can_processOne_with_offset = can_processOne_scalar_with_offset<TBlock> or can_processOne_simd_with_offset<TBlock>;

template<typename TBlock, typename TPort>
concept can_processMessagesForPortConsumableSpan = requires(TBlock &block, TPort &inPort) { block.processMessages(inPort, inPort.streamReader().get(1UZ)); };

template<typename TBlock, typename TPort>
concept can_processMessagesForPortStdSpan = requires(TBlock &block, TPort &inPort, std::span<const Message> msgSpan) { block.processMessages(inPort, msgSpan); };

// clang-format off
namespace detail {

template<typename T>
struct DummyConsumableSpan {
    using value_type = typename std::remove_cv_t<T>;
    using iterator = typename std::span<const T>::iterator;

private:
    std::span<const T> internalSpan; // Internal span, used for fake implementation

public:
    DummyConsumableSpan() = default;
    DummyConsumableSpan(const DummyConsumableSpan& other) = default;
    DummyConsumableSpan& operator=(const DummyConsumableSpan& other) = default;
    DummyConsumableSpan(DummyConsumableSpan&& other) noexcept = default;
    DummyConsumableSpan& operator=(DummyConsumableSpan&& other) noexcept = default;
    ~DummyConsumableSpan() = default;

    [[nodiscard]] constexpr iterator begin() const noexcept { return internalSpan.begin(); }
    [[nodiscard]] constexpr iterator end() const noexcept { return internalSpan.end(); }
    [[nodiscard]] constexpr std::size_t size() const noexcept { return internalSpan.size(); }
    operator const std::span<const T>&() const noexcept { return internalSpan; }
    operator std::span<const T>&() noexcept  { return internalSpan; }
    operator std::span<const T>&&() = delete;

    [[nodiscard]] bool consume(std::size_t /* nSamples */) const noexcept { return true; }
};
static_assert(ConsumableSpan<DummyConsumableSpan<int>>);

template<typename T>
struct DummyPublishableSpan {
    using value_type = typename std::remove_cv_t<T>;
    using iterator = typename std::span<T>::iterator;

private:
    std::span<T> internalSpan; // Internal span, used for fake implementation

public:
    DummyPublishableSpan() = default;
    DummyPublishableSpan(const DummyPublishableSpan& other) = delete;
    DummyPublishableSpan& operator=(const DummyPublishableSpan& other) = delete;
    DummyPublishableSpan(DummyPublishableSpan&& other) noexcept = default;
    DummyPublishableSpan& operator=(DummyPublishableSpan&& other) noexcept = default;
    ~DummyPublishableSpan() = default;

    [[nodiscard]] constexpr iterator begin() const noexcept { return internalSpan.begin(); }
    [[nodiscard]] constexpr iterator end() const noexcept { return internalSpan.end(); }
    [[nodiscard]] constexpr std::size_t size() const noexcept { return internalSpan.size(); }
    operator const std::span<T>&() const noexcept { return internalSpan; }
    operator std::span<T>&() noexcept  { return internalSpan; }

    constexpr void publish(std::size_t) noexcept {}
};
static_assert(PublishableSpan<DummyPublishableSpan<int>>);

// clang-format on

struct to_any_vector {
    template<typename Any>
    operator std::vector<Any>() const {
        return {};
    } // NOSONAR

    template<typename Any>
    operator std::vector<Any> &() const {
        return {};
    } // NOSONAR
};

struct to_any_pointer {
    template<typename Any>
    operator Any *() const {
        return {};
    } // NOSONAR
};

template<typename T>
struct dummy_reader {
    using type = to_any_pointer;
};

template<typename T>
struct dummy_writer {
    using type = to_any_pointer;
};

template<typename Port, bool isVectorOfSpansReturned>
constexpr auto *
port_to_processBulk_argument_helper() {
    if constexpr (requires(Port p) { // array of ports
                      typename Port::value_type;
                      p.cbegin() != p.cend();
                  }) {
        if constexpr (Port::value_type::kIsInput) {
            if constexpr (isVectorOfSpansReturned) {
                return static_cast<std::span<std::span<const typename Port::value_type::value_type>> *>(nullptr);
            } else {
                return static_cast<std::span<DummyConsumableSpan<typename Port::value_type::value_type>> *>(nullptr);
            }
        } else if constexpr (Port::value_type::kIsOutput) {
            if constexpr (isVectorOfSpansReturned) {
                return static_cast<std::span<std::span<typename Port::value_type::value_type>> *>(nullptr);
            } else {
                return static_cast<std::span<DummyPublishableSpan<typename Port::value_type::value_type>> *>(nullptr);
            }
        }

    } else { // single port
        if constexpr (Port::kIsInput) {
            return static_cast<DummyConsumableSpan<typename Port::value_type> *>(nullptr);
        } else if constexpr (Port::kIsOutput) {
            return static_cast<DummyPublishableSpan<typename Port::value_type> *>(nullptr);
        }
    }
}

template<typename Port>
struct port_to_processBulk_argument_consumable_publishable {
    using type = std::remove_pointer_t<decltype(port_to_processBulk_argument_helper<Port, false>())>;
};

template<typename Port>
struct port_to_processBulk_argument_std_span {
    using type = std::remove_pointer_t<decltype(port_to_processBulk_argument_helper<Port, true>())>;
};

template<typename>
struct nothing_you_ever_wanted {};

// This alias template is only necessary as a workaround for a bug in Clang. Instead of passing dynamic_span to transform_conditional below, C++ allows passing std::span directly.
template<typename T>
using dynamic_span = std::span<T>;

template<std::size_t... InIdx, std::size_t... OutIdx>
auto
can_processBulk_invoke_test(auto &block, const auto &inputs, auto &outputs, std::index_sequence<InIdx...>, std::index_sequence<OutIdx...>)
        -> decltype(block.processBulk(std::get<InIdx>(inputs)..., std::get<OutIdx>(outputs)...));
} // namespace detail

template<typename TBlock, template<typename> typename TArguments>
concept can_processBulk_helper = requires(TBlock &n, typename meta::transform_types_nested<TArguments, traits::block::stream_input_ports<TBlock>>::tuple_type inputs,
                                          typename meta::transform_types_nested<TArguments, traits::block::stream_output_ports<TBlock>>::tuple_type outputs) {
    {
        detail::can_processBulk_invoke_test(n, inputs, outputs, std::make_index_sequence<stream_input_port_types<TBlock>::size>(), std::make_index_sequence<stream_output_port_types<TBlock>::size>())
    } -> std::same_as<work::Status>;
};

template<typename TBlock>
concept can_processBulk = can_processBulk_helper<TBlock, detail::port_to_processBulk_argument_consumable_publishable> || can_processBulk_helper<TBlock, detail::port_to_processBulk_argument_std_span>;

/**
 * Satisfied if `TDerived` has a member function `processBulk` which can be invoked with a number of arguments matching the number of input and output ports. Input arguments must accept either a
 * std::span<const T> or any type satisfying ConsumableSpan<T>. Output arguments must accept either a std::span<T> or any type satisfying PublishableSpan<T>, except for the I-th output argument, which
 * must be std::span<T> and *not* a type satisfying PublishableSpan<T>.
 */
template<typename TDerived, std::size_t I>
concept processBulk_requires_ith_output_as_span
        = can_processBulk<TDerived> && (I < traits::block::stream_output_port_types<TDerived>::size) && (I >= 0)
       && requires(TDerived &d, typename meta::transform_types<detail::DummyConsumableSpan, traits::block::stream_input_port_types<TDerived>>::template apply<std::tuple> inputs,
                   typename meta::transform_conditional<decltype([](auto j) { return j == I; }), detail::dynamic_span, detail::DummyPublishableSpan,
                                                        traits::block::stream_output_port_types<TDerived>>::template apply<std::tuple>
                           outputs,
                   typename meta::transform_conditional<decltype([](auto j) { return j == I; }), detail::nothing_you_ever_wanted, detail::DummyPublishableSpan,
                                                        traits::block::stream_output_port_types<TDerived>>::template apply<std::tuple>
                           bad_outputs) {
              {
                  detail::can_processBulk_invoke_test(d, inputs, outputs, std::make_index_sequence<stream_input_port_types<TDerived>::size>(),
                                                      std::make_index_sequence<stream_output_port_types<TDerived>::size>())
              } -> std::same_as<work::Status>;
              // TODO: Is this check redundant?
              not requires {
                  []<std::size_t... InIdx, std::size_t... OutIdx>(std::index_sequence<InIdx...>,
                                                                  std::index_sequence<OutIdx...>) -> decltype(d.processBulk(std::get<InIdx>(inputs)..., std::get<OutIdx>(bad_outputs)...)) {
                      return {};
                  }(std::make_index_sequence<traits::block::stream_input_port_types<TDerived>::size>(), std::make_index_sequence<traits::block::stream_output_port_types<TDerived>::size>());
              };
          };

} // namespace gr::traits::block

#endif // include guard

// #include <gnuradio-4.0/Port.hpp>

// #include <gnuradio-4.0/Sequence.hpp>

// #include <gnuradio-4.0/Tag.hpp>

// #include <gnuradio-4.0/thread/thread_pool.hpp>
#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <mutex>
#include <span>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>

#include <fmt/format.h>
#include <fmt/ranges.h>

// #include "../WaitStrategy.hpp"
#ifndef GNURADIO_WAITSTRATEGY_HPP
#define GNURADIO_WAITSTRATEGY_HPP

#include <condition_variable>
#include <atomic>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// #include "Sequence.hpp"
#ifndef GNURADIO_SEQUENCE_HPP
#define GNURADIO_SEQUENCE_HPP

#include <algorithm>
#include <atomic>
#include <cstdint>
#include <limits>
#include <memory>
#include <ranges>
#include <vector>

#include <fmt/format.h>

namespace gr {

#ifndef forceinline
// use this for hot-spots only <-> may bloat code size, not fit into cache and
// consequently slow down execution
#define forceinline inline __attribute__((always_inline))
#endif

#ifdef __cpp_lib_hardware_interference_size
using std::hardware_constructive_interference_size;
using std::hardware_destructive_interference_size;
#else
inline constexpr std::size_t hardware_destructive_interference_size  = 64;
inline constexpr std::size_t hardware_constructive_interference_size = 64;
#endif
static constexpr const std::make_signed_t<std::size_t> kInitialCursorValue = -1L;

/**
 * Concurrent sequence class used for tracking the progress of the ring buffer and event
 * processors. Support a number of concurrent operations including CAS and order writes.
 * Also attempts to be more efficient with regards to false sharing by adding padding
 * around the volatile field.
 */
class Sequence {
public:
    using signed_index_type = std::make_signed_t<std::size_t>;

private:
    alignas(hardware_destructive_interference_size) std::atomic<signed_index_type> _fieldsValue{};

public:
    Sequence(const Sequence &)  = delete;
    Sequence(const Sequence &&) = delete;
    void
    operator=(const Sequence &)
            = delete;

    explicit Sequence(signed_index_type initialValue = kInitialCursorValue) noexcept : _fieldsValue(initialValue) {}

    [[nodiscard]] forceinline signed_index_type
    value() const noexcept {
        return std::atomic_load_explicit(&_fieldsValue, std::memory_order_acquire);
    }

    forceinline void
    setValue(const signed_index_type value) noexcept {
        std::atomic_store_explicit(&_fieldsValue, value, std::memory_order_release);
    }

    [[nodiscard]] forceinline bool
    compareAndSet(signed_index_type expectedSequence, signed_index_type nextSequence) noexcept {
        // atomically set the value to the given updated value if the current value == the
        // expected value (true, otherwise folse).
        return std::atomic_compare_exchange_strong(&_fieldsValue, &expectedSequence, nextSequence);
    }

    [[nodiscard]] forceinline signed_index_type
    incrementAndGet() noexcept {
        return std::atomic_fetch_add(&_fieldsValue, 1L) + 1L;
    }

    [[nodiscard]] forceinline signed_index_type
    addAndGet(signed_index_type value) noexcept {
        return std::atomic_fetch_add(&_fieldsValue, value) + value;
    }

    void
    wait(signed_index_type oldValue) const noexcept {
        atomic_wait_explicit(&_fieldsValue, oldValue, std::memory_order_acquire);
    }

    void
    notify_all() noexcept {
        _fieldsValue.notify_all();
    }
};

namespace detail {

using signed_index_type = Sequence::signed_index_type;

/**
 * Get the minimum sequence from an array of Sequences.
 *
 * \param sequences sequences to compare.
 * \param minimum an initial default minimum.  If the array is empty this value will
 * returned. \returns the minimum sequence found or lon.MaxValue if the array is empty.
 */
inline signed_index_type
getMinimumSequence(const std::vector<std::shared_ptr<Sequence>> &sequences, signed_index_type minimum = std::numeric_limits<signed_index_type>::max()) noexcept {
    // Note that calls to getMinimumSequence get rather expensive with sequences.size() because
    // each Sequence lives on its own cache line. Also, this is no reasonable loop for vectorization.
    for (const auto &s : sequences) {
        const signed_index_type v = s->value();
        if (v < minimum) {
            minimum = v;
        }
    }
    return minimum;
}

inline void
addSequences(std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> &sequences, const Sequence &cursor, const std::vector<std::shared_ptr<Sequence>> &sequencesToAdd) {
    signed_index_type                                       cursorSequence;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> updatedSequences;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> currentSequences;

    do {
        currentSequences = std::atomic_load_explicit(&sequences, std::memory_order_acquire);
        updatedSequences = std::make_shared<std::vector<std::shared_ptr<Sequence>>>(currentSequences->size() + sequencesToAdd.size());

#if not defined(_LIBCPP_VERSION)
        std::ranges::copy(currentSequences->begin(), currentSequences->end(), updatedSequences->begin());
#else
        std::copy(currentSequences->begin(), currentSequences->end(), updatedSequences->begin());
#endif

        cursorSequence = cursor.value();

        auto index     = currentSequences->size();
        for (auto &&sequence : sequencesToAdd) {
            sequence->setValue(cursorSequence);
            (*updatedSequences)[index] = sequence;
            index++;
        }
    } while (!std::atomic_compare_exchange_weak(&sequences, &currentSequences, updatedSequences)); // xTODO: explicit memory order

    cursorSequence = cursor.value();

    for (auto &&sequence : sequencesToAdd) {
        sequence->setValue(cursorSequence);
    }
}

inline bool
removeSequence(std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> &sequences, const std::shared_ptr<Sequence> &sequence) {
    std::uint32_t                                           numToRemove;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> oldSequences;
    std::shared_ptr<std::vector<std::shared_ptr<Sequence>>> newSequences;

    do {
        oldSequences = std::atomic_load_explicit(&sequences, std::memory_order_acquire);
#if not defined(_LIBCPP_VERSION)
        numToRemove = static_cast<std::uint32_t>(std::ranges::count(*oldSequences, sequence)); // specifically uses identity
#else
        numToRemove = static_cast<std::uint32_t>(std::count((*oldSequences).begin(), (*oldSequences).end(), sequence)); // specifically uses identity
#endif
        if (numToRemove == 0) {
            break;
        }

        auto oldSize = static_cast<std::uint32_t>(oldSequences->size());
        newSequences = std::make_shared<std::vector<std::shared_ptr<Sequence>>>(oldSize - numToRemove);

        for (auto i = 0U, pos = 0U; i < oldSize; ++i) {
            const auto &testSequence = (*oldSequences)[i];
            if (sequence != testSequence) {
                (*newSequences)[pos] = testSequence;
                pos++;
            }
        }
    } while (!std::atomic_compare_exchange_weak(&sequences, &oldSequences, newSequences));

    return numToRemove != 0;
}

} // namespace detail

} // namespace gr

#include <fmt/core.h>
#include <fmt/ostream.h>

template<>
struct fmt::formatter<gr::Sequence> {
    template<typename ParseContext>
    constexpr auto
    parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto
    format(gr::Sequence const &value, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "{}", value.value());
    }
};

namespace gr {
inline std::ostream &
operator<<(std::ostream &os, const Sequence &v) {
    return os << fmt::format("{}", v.value());
}
} // namespace gr

#endif // GNURADIO_SEQUENCE_HPP


namespace gr {
// clang-format off
/**
 * Wait for the given sequence to be available.  It is possible for this method to return a value less than the sequence number supplied depending on the implementation of the WaitStrategy.
 * A common use for this is to signal a timeout.Any EventProcessor that is using a WaitStrategy to get notifications about message becoming available should remember to handle this case.
 * The BatchEventProcessor<T> explicitly handles this case and will signal a timeout if required.
 *
 * \param sequence sequence to be waited on.
 * \param cursor Ring buffer cursor on which to wait.
 * \param dependentSequence on which to wait.
 * \param barrier barrier the IEventProcessor is waiting on.
 * \returns the sequence that is available which may be greater than the requested sequence.
 */
template<typename T>
inline constexpr bool isWaitStrategy = requires(T /*const*/ t, const std::int64_t sequence, const Sequence &cursor, std::vector<std::shared_ptr<Sequence>> &dependentSequences) {
    { t.waitFor(sequence, cursor, dependentSequences) } -> std::same_as<std::int64_t>;
};
static_assert(!isWaitStrategy<int>);

/**
 * signal those waiting that the cursor has advanced.
 */
template<typename T>
inline constexpr bool hasSignalAllWhenBlocking = requires(T /*const*/ t) {
    { t.signalAllWhenBlocking() } -> std::same_as<void>;
};
static_assert(!hasSignalAllWhenBlocking<int>);

template<typename T>
concept WaitStrategy = isWaitStrategy<T>;



/**
 * Blocking strategy that uses a lock and condition variable for IEventProcessor's waiting on a barrier.
 * This strategy should be used when performance and low-latency are not as important as CPU resource.
 */
class BlockingWaitStrategy {
    std::recursive_mutex        _gate;
    std::condition_variable_any _conditionVariable;

public:
    std::int64_t waitFor(const std::int64_t sequence, const Sequence &cursor, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) {
        if (cursor.value() < sequence) {
            std::unique_lock uniqueLock(_gate);

            while (cursor.value() < sequence) {
                // optional: barrier check alert
                _conditionVariable.wait(uniqueLock);
            }
        }

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            // optional: barrier check alert
        }

        return availableSequence;
    }

    void signalAllWhenBlocking() {
        std::unique_lock uniqueLock(_gate);
        _conditionVariable.notify_all();
    }
};
static_assert(WaitStrategy<BlockingWaitStrategy>);

/**
 * Busy Spin strategy that uses a busy spin loop for IEventProcessor's waiting on a barrier.
 * This strategy will use CPU resource to avoid syscalls which can introduce latency jitter.
 * It is best used when threads can be bound to specific CPU cores.
 */
struct BusySpinWaitStrategy {
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) const {
        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            // optional: barrier check alert
        }
        return availableSequence;
    }
};
static_assert(WaitStrategy<BusySpinWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<BusySpinWaitStrategy>);

/**
 * Sleeping strategy that initially spins, then uses a std::this_thread::yield(), and eventually sleep. T
 * his strategy is a good compromise between performance and CPU resource.
 * Latency spikes can occur after quiet periods.
 */
class SleepingWaitStrategy {
    static const std::int32_t _defaultRetries = 200;
    std::int32_t              _retries        = 0;

public:
    explicit SleepingWaitStrategy(std::int32_t retries = _defaultRetries)
        : _retries(retries) {
    }

    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) const {
        auto       counter    = _retries;
        const auto waitMethod = [&counter]() {
            // optional: barrier check alert

            if (counter > 100) {
                --counter;
            } else if (counter > 0) {
                --counter;
                std::this_thread::yield();
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));
            }
        };

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            waitMethod();
        }

        return availableSequence;
    }
};
static_assert(WaitStrategy<SleepingWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<SleepingWaitStrategy>);

struct TimeoutException : public std::runtime_error {
    TimeoutException() : std::runtime_error("TimeoutException") {}
};

class TimeoutBlockingWaitStrategy {
    using Clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>;
    Clock::duration             _timeout;
    std::recursive_mutex        _gate;
    std::condition_variable_any _conditionVariable;

public:
    explicit TimeoutBlockingWaitStrategy(Clock::duration timeout)
        : _timeout(timeout) {}

    std::int64_t waitFor(const std::int64_t sequence, const Sequence &cursor, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) {
        auto timeSpan = std::chrono::duration_cast<std::chrono::microseconds>(_timeout);

        if (cursor.value() < sequence) {
            std::unique_lock uniqueLock(_gate);

            while (cursor.value() < sequence) {
                // optional: barrier check alert

                if (_conditionVariable.wait_for(uniqueLock, timeSpan) == std::cv_status::timeout) {
                    throw TimeoutException();
                }
            }
        }

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            // optional: barrier check alert
        }

        return availableSequence;
    }

    void signalAllWhenBlocking() {
        std::unique_lock uniqueLock(_gate);
        _conditionVariable.notify_all();
    }
};
static_assert(WaitStrategy<TimeoutBlockingWaitStrategy>);
static_assert(hasSignalAllWhenBlocking<TimeoutBlockingWaitStrategy>);

/**
 * Yielding strategy that uses a Thread.Yield() for IEventProcessors waiting on a barrier after an initially spinning.
 * This strategy is a good compromise between performance and CPU resource without incurring significant latency spikes.
 */
class YieldingWaitStrategy {
    const std::size_t _spinTries = 100;

public:
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequences) const {
        auto       counter    = _spinTries;
        const auto waitMethod = [&counter]() {
            // optional: barrier check alert

            if (counter == 0) {
                std::this_thread::yield();
            } else {
                --counter;
            }
        };

        std::int64_t availableSequence;
        while ((availableSequence = detail::getMinimumSequence(dependentSequences)) < sequence) {
            waitMethod();
        }

        return availableSequence;
    }
};
static_assert(WaitStrategy<YieldingWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<YieldingWaitStrategy>);

struct NoWaitStrategy {
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> & /*dependentSequences*/) const {
        // wait for nothing
        return sequence;
    }
};
static_assert(WaitStrategy<NoWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<NoWaitStrategy>);


/**
 *
 * SpinWait is meant to be used as a tool for waiting in situations where the thread is not allowed to block.
 *
 * In order to get the maximum performance, the implementation first spins for `YIELD_THRESHOLD` times, and then
 * alternates between yielding, spinning and putting the thread to sleep, to allow other threads to be scheduled
 * by the kernel to avoid potential CPU contention.
 *
 * The number of spins, yielding, and sleeping for either '0 ms' or '1 ms' is controlled by the NTTP constants
 * @tparam YIELD_THRESHOLD
 * @tparam SLEEP_0_EVERY_HOW_MANY_TIMES
 * @tparam SLEEP_1_EVERY_HOW_MANY_TIMES
 */
template<std::int32_t YIELD_THRESHOLD = 10, std::int32_t SLEEP_0_EVERY_HOW_MANY_TIMES = 5, std::int32_t SLEEP_1_EVERY_HOW_MANY_TIMES = 20>
class SpinWait {
    using Clock         = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>;
    std::int32_t _count = 0;
    static void  spinWaitInternal(std::int32_t iterationCount) noexcept {
        for (auto i = 0; i < iterationCount; i++) {
            yieldProcessor();
        }
    }
#ifndef __EMSCRIPTEN__
    static void yieldProcessor() noexcept { asm volatile("rep\nnop"); }
#else
    static void yieldProcessor() noexcept { std::this_thread::sleep_for(std::chrono::milliseconds(1)); }
#endif

public:
    SpinWait() = default;

    [[nodiscard]] std::int32_t count() const noexcept { return _count; }
    [[nodiscard]] bool         nextSpinWillYield() const noexcept { return _count > YIELD_THRESHOLD; }

    void                       spinOnce() {
        if (nextSpinWillYield()) {
            auto num = _count >= YIELD_THRESHOLD ? _count - 10 : _count;
            if (num % SLEEP_1_EVERY_HOW_MANY_TIMES == SLEEP_1_EVERY_HOW_MANY_TIMES - 1) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            } else {
                if (num % SLEEP_0_EVERY_HOW_MANY_TIMES == SLEEP_0_EVERY_HOW_MANY_TIMES - 1) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(0));
                } else {
                    std::this_thread::yield();
                }
            }
        } else {
            spinWaitInternal(4 << _count);
        }

        if (_count == std::numeric_limits<std::int32_t>::max()) {
            _count = YIELD_THRESHOLD;
        } else {
            ++_count;
        }
    }

    void reset() noexcept { _count = 0; }

    template<typename T>
    requires std::is_nothrow_invocable_r_v<bool, T>
    bool
    spinUntil(const T &condition) const { return spinUntil(condition, -1); }

    template<typename T>
    requires std::is_nothrow_invocable_r_v<bool, T>
    bool
    spinUntil(const T &condition, std::int64_t millisecondsTimeout) const {
        if (millisecondsTimeout < -1) {
            throw std::out_of_range("Timeout value is out of range");
        }

        std::int64_t num = 0;
        if (millisecondsTimeout != 0 && millisecondsTimeout != -1) {
            num = getTickCount();
        }

        SpinWait spinWait;
        while (!condition()) {
            if (millisecondsTimeout == 0) {
                return false;
            }

            spinWait.spinOnce();

            if (millisecondsTimeout != 1 && spinWait.nextSpinWillYield() && millisecondsTimeout <= (getTickCount() - num)) {
                return false;
            }
        }

        return true;
    }

    [[nodiscard]] static std::int64_t getTickCount() { return std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now().time_since_epoch()).count(); }
};

/**
 * Spin strategy that uses a SpinWait for IEventProcessors waiting on a barrier.
 * This strategy is a good compromise between performance and CPU resource.
 * Latency spikes can occur after quiet periods.
 */
struct SpinWaitWaitStrategy {
    std::int64_t waitFor(const std::int64_t sequence, const Sequence & /*cursor*/, const std::vector<std::shared_ptr<Sequence>> &dependentSequence) const {
        std::int64_t availableSequence;

        SpinWait     spinWait;
        while ((availableSequence = detail::getMinimumSequence(dependentSequence)) < sequence) {
            // optional: barrier check alert
            spinWait.spinOnce();
        }

        return availableSequence;
    }
};
static_assert(WaitStrategy<SpinWaitWaitStrategy>);
static_assert(!hasSignalAllWhenBlocking<SpinWaitWaitStrategy>);

struct NO_SPIN_WAIT {};

template<typename SPIN_WAIT = NO_SPIN_WAIT>
class AtomicMutex {
    std::atomic_flag _lock{};
    SPIN_WAIT        _spin_wait;

public:
    AtomicMutex()                    = default;
    AtomicMutex(const AtomicMutex &) = delete;
    AtomicMutex &operator=(const AtomicMutex &) = delete;

    //
    void lock() {
        while (_lock.test_and_set(std::memory_order_acquire)) {
            if constexpr (requires { _spin_wait.spin_once(); }) {
                _spin_wait.spin_once();
            }
        }
        if constexpr (requires { _spin_wait.spin_once(); }) {
            _spin_wait.reset();
        }
    }
    void unlock() { _lock.clear(std::memory_order::release); }
};


// clang-format on
} // namespace gr


#endif // GNURADIO_WAITSTRATEGY_HPP

// #include "thread_affinity.hpp"
#ifndef THREADAFFINITY_HPP
#define THREADAFFINITY_HPP

#include <algorithm>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <mutex>
#include <optional>
#include <sstream>
#include <system_error>
#include <thread>
#include <vector>

#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))) // UNIX-style OS
#include <unistd.h>
#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
#include <pthread.h>
#include <sched.h>
#endif
#endif

namespace gr::thread_pool::thread {

constexpr size_t THREAD_MAX_NAME_LENGTH  = 16;
constexpr int    THREAD_UNINITIALISED    = 1;
constexpr int    THREAD_ERROR_UNKNOWN    = 2;
constexpr int    THREAD_VALUE_RANGE      = 3;
constexpr int    THREAD_INVALID_ARGUMENT = 22;
constexpr int    THREAD_ERANGE           = 34;

class thread_exception : public std::error_category {
    using std::error_category::error_category;

public:
    constexpr thread_exception() : std::error_category(){};

    const char *
    name() const noexcept override {
        return "thread_exception";
    };

    std::string
    message(int errorCode) const override {
        switch (errorCode) {
        case THREAD_UNINITIALISED: return "thread uninitialised or user does not have the appropriate rights (ie. CAP_SYS_NICE capability)";
        case THREAD_ERROR_UNKNOWN: return "thread error code 2";
        case THREAD_INVALID_ARGUMENT: return "invalid argument";
        case THREAD_ERANGE: return fmt::format("length of the string specified pointed to by name exceeds the allowed limit THREAD_MAX_NAME_LENGTH = '{}'", THREAD_MAX_NAME_LENGTH);
        case THREAD_VALUE_RANGE: return fmt::format("priority out of valid range for scheduling policy", THREAD_MAX_NAME_LENGTH);
        default: return fmt::format("unknown threading error code {}", errorCode);
        }
    };
};

template<class type>
#if __cpp_lib_jthread >= 201911L
concept thread_type = std::is_same_v<type, std::thread> || std::is_same_v<type, std::jthread>;
#else
concept thread_type = std::is_same_v<type, std::thread>;
#endif

namespace detail {
#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
template<typename Tp, typename... Us>
constexpr decltype(auto)
firstElement(Tp &&t, Us &&...) noexcept {
    return std::forward<Tp>(t);
}

inline constexpr pthread_t
getPosixHandler(thread_type auto &...t) noexcept {
    if constexpr (sizeof...(t) > 0) {
        return firstElement(t...).native_handle();
    } else {
        return pthread_self();
    }
}

inline std::string
getThreadName(const pthread_t &handle) {
    if (handle == 0U) {
        return "uninitialised thread";
    }
    char threadName[THREAD_MAX_NAME_LENGTH];
    if (int rc = pthread_getname_np(handle, threadName, THREAD_MAX_NAME_LENGTH); rc != 0) {
        throw std::system_error(rc, thread_exception(), "getThreadName(thread_type)");
    }
    return std::string{ threadName, strnlen(threadName, THREAD_MAX_NAME_LENGTH) };
}

inline int
getPid() {
    return getpid();
}
#else
inline int
getPid() {
    return 0;
}
#endif
} // namespace detail

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline std::string
getProcessName(const int pid = detail::getPid()) {
    if (std::ifstream in(fmt::format("/proc/{}/comm", pid), std::ios::in); in.is_open()) {
        std::string fileContent;
        std::getline(in, fileContent, '\n');
        return fileContent;
    }
    return "unknown_process";
}
#else
inline std::string
getProcessName(const int /*pid*/ = -1) {
    return "unknown_process";
}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline std::string
getThreadName(thread_type auto &...thread) {
    const pthread_t handle = detail::getPosixHandler(thread...);
    if (handle == 0U) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), "getThreadName(thread_type)");
    }
    return detail::getThreadName(handle);
}
#else
inline std::string
getThreadName(thread_type auto &.../*thread*/) {
    return "unknown thread name";
}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline void
setProcessName(const std::string_view &processName, int pid = detail::getPid()) {
    std::ofstream out(fmt::format("/proc/{}/comm", pid), std::ios::out);
    if (!out.is_open()) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("setProcessName({},{})", processName, pid));
    }
    out << std::string{ processName.cbegin(), std::min(15LU, processName.size()) };
    out.close();
}
#else
inline void
setProcessName(const std::string_view & /*processName*/, int /*pid*/ = -1) {}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline void
setThreadName(const std::string_view &threadName, thread_type auto &...thread) {
    const pthread_t handle = detail::getPosixHandler(thread...);
    if (handle == 0U) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("setThreadName({}, thread_type)", threadName, detail::getThreadName(handle)));
    }
    if (int rc = pthread_setname_np(handle, threadName.data()); rc < 0) {
        throw std::system_error(rc, thread_exception(), fmt::format("setThreadName({},{}) - error code '{}'", threadName, detail::getThreadName(handle), rc));
    }
}
#else
inline void
setThreadName(const std::string_view & /*threadName*/, thread_type auto &.../*thread*/) {}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
namespace detail {
inline std::vector<bool>
getAffinityMask(const cpu_set_t &cpuSet) {
    std::vector<bool> bitMask(std::min(sizeof(cpu_set_t), static_cast<size_t>(std::thread::hardware_concurrency())));
    for (size_t i = 0; i < bitMask.size(); i++) {
        bitMask[i] = CPU_ISSET(i, &cpuSet);
    }
    return bitMask;
}

template<class T>
    requires requires(T value) { value[0]; }
inline constexpr cpu_set_t
getAffinityMask(const T &threadMap) {
    cpu_set_t cpuSet;
    CPU_ZERO(&cpuSet);
    size_t nMax = std::min(threadMap.size(), static_cast<size_t>(std::thread::hardware_concurrency()));
    for (size_t i = 0; i < nMax; i++) {
        if (threadMap[i]) {
            CPU_SET(i, &cpuSet);
        } else {
            CPU_CLR(i, &cpuSet);
        }
    }
    return cpuSet;
}
} // namespace detail
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline std::vector<bool>
getThreadAffinity(thread_type auto &...thread) {
    const pthread_t handle = detail::getPosixHandler(thread...);
    if (handle == 0U) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("getThreadAffinity(thread_type)"));
    }
    cpu_set_t cpuSet;
    if (int rc = pthread_getaffinity_np(handle, sizeof(cpu_set_t), &cpuSet); rc != 0) {
        throw std::system_error(rc, thread_exception(), fmt::format("getThreadAffinity({})", detail::getThreadName(handle)));
    }
    return detail::getAffinityMask(cpuSet);
}
#else
std::vector<bool>
getThreadAffinity(thread_type auto &...) {
    return std::vector<bool>(std::thread::hardware_concurrency()); // cannot set affinity for non-posix threads
}
#endif

template<class T>
    requires requires(T value) { value[0]; }
#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline constexpr void
setThreadAffinity(const T &threadMap, thread_type auto &...thread) {
    const pthread_t handle = detail::getPosixHandler(thread...);
    if (handle == 0U) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(),
                                fmt::format("setThreadAffinity(std::vector<bool, {}> = {{{}}}, thread_type)", threadMap.size(), fmt::join(threadMap.begin(), threadMap.end(), ", ")));
    }
    cpu_set_t cpuSet = detail::getAffinityMask(threadMap);
    if (int rc = pthread_setaffinity_np(handle, sizeof(cpu_set_t), &cpuSet); rc != 0) {
        throw std::system_error(rc, thread_exception(),
                                fmt::format("setThreadAffinity(std::vector<bool, {}> = {{{}}}, {})", threadMap.size(), fmt::join(threadMap.begin(), threadMap.end(), ", "),
                                            detail::getThreadName(handle)));
    }
}
#else
constexpr bool
setThreadAffinity(const T & /*threadMap*/, thread_type auto &...) {
    return false; // cannot set affinity for non-posix threads
}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline std::vector<bool>
getProcessAffinity(const int pid = detail::getPid()) {
    if (pid <= 0) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("getProcessAffinity({}) -- invalid pid", pid));
    }
    cpu_set_t cpuSet;
    if (int rc = sched_getaffinity(pid, sizeof(cpu_set_t), &cpuSet); rc != 0) {
        throw std::system_error(rc, thread_exception(), fmt::format("getProcessAffinity(std::bitset<{{}}> = {{}}, thread_type)")); // todo: fix format string
    }
    return detail::getAffinityMask(cpuSet);
}
#else
inline std::vector<bool>
getProcessAffinity(const int /*pid*/ = -1) {
    return std::vector<bool>(std::thread::hardware_concurrency()); // cannot set affinity for non-posix threads
}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
template<class T>
    requires requires(T value) { std::get<0>(value); }
inline constexpr bool
setProcessAffinity(const T &threadMap, const int pid = detail::getPid()) {
    if (pid <= 0) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(),
                                fmt::format("setProcessAffinity(std::vector<bool, {}> = {{{}}}, {})", threadMap.size(), fmt::join(threadMap.begin(), threadMap.end(), ", "), pid));
    }
    cpu_set_t cpuSet = detail::getAffinityMask(threadMap);
    if (int rc = sched_setaffinity(pid, sizeof(cpu_set_t), &cpuSet); rc != 0) {
        throw std::system_error(rc, thread_exception(),
                                fmt::format("setProcessAffinity(std::vector<bool, {}> = {{{}}}, {})", threadMap.size(), fmt::join(threadMap.begin(), threadMap.end(), ", "), pid));
    }

    return true;
}
#else
template<class T>
    requires requires(T value) { std::get<0>(value); }
inline constexpr bool
setProcessAffinity(const T & /*threadMap*/, const int /*pid*/ = -1) {
    return false; // cannot set affinity for non-posix threads
}
#endif
enum Policy { UNKNOWN = -1, OTHER = 0, FIFO = 1, ROUND_ROBIN = 2 };
} // namespace gr::thread_pool::thread

template<>
struct fmt::formatter<gr::thread_pool::thread::Policy> {
    using Policy = gr::thread_pool::thread::Policy;

    template<typename ParseContext>
    constexpr auto
    parse(ParseContext &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto
    format(Policy policy, FormatContext &ctx) {
        std::string policy_name;
        switch (policy) {
        case Policy::UNKNOWN: policy_name = "UNKNOWN"; break;
        case Policy::OTHER: policy_name = "OTHER"; break;
        case Policy::FIFO: policy_name = "FIFO"; break;
        case Policy::ROUND_ROBIN: policy_name = "ROUND_ROBIN"; break;
        default: policy_name = "INVALID_POLICY"; break;
        }
        return fmt::format_to(ctx.out(), "{}", policy_name);
    }
};

namespace gr::thread_pool::thread {

struct SchedulingParameter {
    Policy policy; // e.g. SCHED_OTHER, SCHED_RR, FSCHED_FIFO
    int    priority;
};

namespace detail {
inline Policy
getEnumPolicy(const int policy) {
    switch (policy) {
#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
    case SCHED_FIFO: return Policy::FIFO;
    case SCHED_RR: return Policy::ROUND_ROBIN;
    case SCHED_OTHER: return Policy::OTHER;
#endif
    default: return Policy::UNKNOWN;
    }
}
} // namespace detail

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline struct SchedulingParameter
getProcessSchedulingParameter(const int pid = detail::getPid()) {
    if (pid <= 0) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("getProcessSchedulingParameter({}) -- invalid pid", pid));
    }
    struct sched_param param;
    const int          policy = sched_getscheduler(pid);
    if (int rc = sched_getparam(pid, &param); rc != 0) {
        throw std::system_error(rc, thread_exception(), fmt::format("getProcessSchedulingParameter({}) - sched_getparam error", pid));
    }
    return SchedulingParameter{ .policy = detail::getEnumPolicy(policy), .priority = param.sched_priority };
}
#else
inline struct SchedulingParameter
getProcessSchedulingParameter(const int /*pid*/ = -1) {
    return {};
}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline void
setProcessSchedulingParameter(Policy scheduler, int priority, const int pid = detail::getPid()) {
    if (pid <= 0) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("setProcessSchedulingParameter({}, {}, {}) -- invalid pid", scheduler, priority, pid));
    }
    const int minPriority = sched_get_priority_min(scheduler);
    const int maxPriority = sched_get_priority_max(scheduler);
    if (priority < minPriority || priority > maxPriority) {
        throw std::system_error(THREAD_VALUE_RANGE, thread_exception(),
                                fmt::format("setProcessSchedulingParameter({}, {}, {}) -- requested priority out-of-range [{}, {}]", scheduler, priority, pid, minPriority, maxPriority));
    }

    struct sched_param param {
        .sched_priority = priority
    };

    if (int rc = sched_setscheduler(pid, scheduler, &param); rc != 0) {
        throw std::system_error(rc, thread_exception(), fmt::format("setProcessSchedulingParameter({}, {}, {}) - sched_setscheduler return code: {}", scheduler, priority, pid, rc));
    }
}
#else
inline void
setProcessSchedulingParameter(Policy /*scheduler*/, int /*priority*/, const int /*pid*/ = -1) {}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline struct SchedulingParameter
getThreadSchedulingParameter(thread_type auto &...thread) {
    const pthread_t handle = detail::getPosixHandler(thread...);
    if (handle == 0U) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("getThreadSchedulingParameter(thread_type) -- invalid thread"));
    }
    struct sched_param param;
    int                policy;
    if (int rc = pthread_getschedparam(handle, &policy, &param); rc != 0) {
        throw std::system_error(rc, thread_exception(), fmt::format("getThreadSchedulingParameter({}) - sched_getparam error", detail::getThreadName(handle)));
    }
    return { .policy = detail::getEnumPolicy(policy), .priority = param.sched_priority };
}
#else
inline struct SchedulingParameter
getThreadSchedulingParameter(thread_type auto &.../*thread*/) {
    return {};
}
#endif

#if defined(_POSIX_VERSION) && not defined(__EMSCRIPTEN__)
inline void
setThreadSchedulingParameter(Policy scheduler, int priority, thread_type auto &...thread) {
    const pthread_t handle = detail::getPosixHandler(thread...);
    if (handle == 0U) {
        throw std::system_error(THREAD_UNINITIALISED, thread_exception(), fmt::format("setThreadSchedulingParameter({}, {}, thread_type) -- invalid thread", scheduler, priority));
    }
    const int minPriority = sched_get_priority_min(scheduler);
    const int maxPriority = sched_get_priority_max(scheduler);
    if (priority < minPriority || priority > maxPriority) {
        throw std::system_error(THREAD_VALUE_RANGE, thread_exception(),
                                fmt::format("setThreadSchedulingParameter({}, {}, {}) -- requested priority out-of-range [{}, {}]", scheduler, priority, detail::getThreadName(handle), minPriority,
                                            maxPriority));
    }

    struct sched_param param {
        .sched_priority = priority
    };

    if (int rc = pthread_setschedparam(handle, scheduler, &param); rc != 0) {
        throw std::system_error(rc, thread_exception(),
                                fmt::format("setThreadSchedulingParameter({}, {}, {}) - pthread_setschedparam return code: {}", scheduler, priority, detail::getThreadName(handle), rc));
    }
}
#else
inline void
setThreadSchedulingParameter(Policy /*scheduler*/, int /*priority*/, thread_type auto &.../*thread*/) {}
#endif

} // namespace gr::thread_pool::thread

#endif // THREADAFFINITY_HPP


namespace gr::thread_pool {
namespace detail {

// TODO remove all the below and use std when moved to modules // support code from mpunits for basic_fixed_string
template<class InputIt1, class InputIt2>
constexpr bool
equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

template<class I1, class I2, class Cmp>
constexpr auto
lexicographical_compare_three_way(I1 f1, I1 l1, I2 f2, I2 l2, Cmp comp) -> decltype(comp(*f1, *f2)) {
    using ret_t = decltype(comp(*f1, *f2));
    static_assert(std::disjunction_v<std::is_same<ret_t, std::strong_ordering>, std::is_same<ret_t, std::weak_ordering>, std::is_same<ret_t, std::partial_ordering>>,
                  "The return type must be a comparison category type.");

    bool exhaust1 = (f1 == l1);
    bool exhaust2 = (f2 == l2);
    for (; !exhaust1 && !exhaust2; exhaust1 = (++f1 == l1), exhaust2 = (++f2 == l2))
        if (auto c = comp(*f1, *f2); c != 0) return c;

    return !exhaust1 ? std::strong_ordering::greater : !exhaust2 ? std::strong_ordering::less : std::strong_ordering::equal;
}

template<class I1, class I2>
constexpr auto
lexicographical_compare_three_way(I1 f1, I1 l1, I2 f2, I2 l2) {
    return lexicographical_compare_three_way(f1, l1, f2, l2, std::compare_three_way());
}

/**
 * @brief A compile-time fixed string
 * taken from https://github.com/mpusz/units/blob/master/src/core/include/units/bits/external/fixed_string.h
 *
 * @tparam CharT Character type to be used by the string
 * @tparam N The size of the string
 */
template<typename CharT, std::size_t N>
struct basic_fixed_string {
    CharT data_[N + 1]   = {};

    using iterator       = CharT *;
    using const_iterator = const CharT *;

    constexpr explicit(false) basic_fixed_string(CharT ch) noexcept { data_[0] = ch; }

    constexpr explicit(false) basic_fixed_string(const CharT (&txt)[N + 1]) noexcept {
        if constexpr (N != 0)
            for (std::size_t i = 0; i < N; ++i) data_[i] = txt[i];
    }

    [[nodiscard]] constexpr bool
    empty() const noexcept {
        return N == 0;
    }

    [[nodiscard]] constexpr std::size_t
    size() const noexcept {
        return N;
    }

    [[nodiscard]] constexpr const CharT *
    data() const noexcept {
        return data_;
    }

    [[nodiscard]] constexpr const CharT *
    c_str() const noexcept {
        return data();
    }

    [[nodiscard]] constexpr const CharT &
    operator[](std::size_t index) const noexcept {
        return data()[index];
    }

    [[nodiscard]] constexpr CharT
    operator[](std::size_t index) noexcept {
        return data()[index];
    }

    [[nodiscard]] constexpr iterator
    begin() noexcept {
        return data();
    }

    [[nodiscard]] constexpr const_iterator
    begin() const noexcept {
        return data();
    }

    [[nodiscard]] constexpr iterator
    end() noexcept {
        return data() + size();
    }

    [[nodiscard]] constexpr const_iterator
    end() const noexcept {
        return data() + size();
    }

    template<std::size_t N2>
    [[nodiscard]] constexpr friend basic_fixed_string<CharT, N + N2>
    operator+(const basic_fixed_string &lhs, const basic_fixed_string<CharT, N2> &rhs) noexcept {
        CharT txt[N + N2 + 1] = {};

        for (size_t i = 0; i != N; ++i) txt[i] = lhs[i];
        for (size_t i = 0; i != N2; ++i) txt[N + i] = rhs[i];

        return basic_fixed_string<CharT, N + N2>(txt);
    }

    [[nodiscard]] constexpr bool
    operator==(const basic_fixed_string &other) const {
        if (size() != other.size()) return false;
        return detail::equal(begin(), end(), other.begin()); // TODO std::ranges::equal(*this, other)
    }

    template<std::size_t N2>
    [[nodiscard]] friend constexpr bool
    operator==(const basic_fixed_string &, const basic_fixed_string<CharT, N2> &) {
        return false;
    }

    template<std::size_t N2>
    [[nodiscard]] friend constexpr auto
    operator<=>(const basic_fixed_string &lhs, const basic_fixed_string<CharT, N2> &rhs) {
        // TODO std::lexicographical_compare_three_way(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        return detail::lexicographical_compare_three_way(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
};

template<typename CharT, std::size_t N>
basic_fixed_string(const CharT (&str)[N]) -> basic_fixed_string<CharT, N - 1>;

template<typename CharT>
basic_fixed_string(CharT) -> basic_fixed_string<CharT, 1>;

template<std::size_t N>
using fixed_string = basic_fixed_string<char, N>;

/**
 * @brief a move-only implementation of std::function by Matthias Kretz, GSI
 * TODO(C++23): to be replaced once C++23's STL version is out/available:
 * https://en.cppreference.com/w/cpp/utility/functional/move_only_function/move_only_function
 */
class move_only_function {
    using FunPtr            = std::unique_ptr<void, void (*)(void *)>;
    FunPtr _erased_fun      = { nullptr, [](void *) {} };
    void   (*_call)(void *) = nullptr;

public:
    constexpr move_only_function() = default;

    template<typename F>
        requires(!std::same_as<move_only_function, std::remove_cvref<F>> && !std::is_reference_v<F>)
    constexpr move_only_function(F &&fun) : _erased_fun(new F(std::forward<F>(fun)), [](void *ptr) { delete static_cast<F *>(ptr); }), _call([](void *ptr) { (*static_cast<F *>(ptr))(); }) {}

    template<typename F>
        requires(!std::is_reference_v<F>)
    constexpr move_only_function &
    operator=(F &&fun) {
        _erased_fun = FunPtr(new F(std::forward<F>(fun)), [](void *ptr) { delete static_cast<F *>(ptr); });
        _call       = [](void *ptr) { (*static_cast<F *>(ptr))(); };
        return *this;
    }

    constexpr void
    operator()() {
        if (_call) {
            _call(_erased_fun.get());
        }
    }

    constexpr void
    operator()() const {
        if (_call) {
            _call(_erased_fun.get());
        }
    }
};

struct Task {
    uint64_t           id;
    move_only_function func;
    std::string        name{}; // Default value provided to avoid warnings on construction with {.id = ..., .func = ...}
    int32_t            priority = 0;
    int32_t            cpuID    = -1;

    std::weak_ordering
    operator<=>(const Task &other) const noexcept {
        return priority <=> other.priority;
    }

    // We want to reuse objects to avoid reallocations
    void
    reset() noexcept {
        *this = Task();
    }
};

template<bool lock, typename... Args>
struct conditional_lock : public std::scoped_lock<Args...> {
    using std::scoped_lock<Args...>::scoped_lock;
};

template<typename... Args>
struct conditional_lock<false, Args...> {
    conditional_lock(const Args &...){};
};

class TaskQueue {
public:
    using TaskContainer = std::list<Task>;

private:
    mutable gr::AtomicMutex<> _mutex;

    TaskContainer             _tasks;

    template<bool shouldLock>
    using conditional_lock = conditional_lock<shouldLock, gr::AtomicMutex<>>;

public:
    TaskQueue()                       = default;
    TaskQueue(const TaskQueue &queue) = delete;
    TaskQueue &
    operator=(const TaskQueue &queue)
            = delete;

    ~TaskQueue() { clear(); }

    template<bool shouldLock = true>
    void
    clear() {
        conditional_lock<shouldLock> lock(_mutex);
        _tasks.clear();
    }

    template<bool shouldLock = true>
    std::size_t
    size() const {
        conditional_lock<shouldLock> lock(_mutex);
        return _tasks.size();
    }

    template<bool shouldLock = true>
    void
    push(TaskContainer jobContainer) {
        conditional_lock<shouldLock> lock(_mutex);
        assert(!jobContainer.empty());
        auto      &job                = jobContainer.front();
        const auto currentJobPriority = job.priority;

        const auto insertPosition     = [&] {
            if (currentJobPriority == 0) {
                return _tasks.end();
            } else {
                return std::find_if(_tasks.begin(), _tasks.end(), [currentJobPriority](const auto &task) { return task.priority < currentJobPriority; });
            }
        }();

        _tasks.splice(insertPosition, jobContainer, jobContainer.begin(), jobContainer.end());
    }

    template<bool shouldLock = true>
    TaskContainer
    pop() {
        conditional_lock<shouldLock> lock(_mutex);
        TaskContainer                result;
        if (!_tasks.empty()) {
            result.splice(result.begin(), _tasks, _tasks.begin(), std::next(_tasks.begin()));
        }
        return result;
    }
};

} // namespace detail

class TaskQueue;

enum TaskType { IO_BOUND = 0, CPU_BOUND = 1 };

template<typename T>
concept ThreadPool = requires(T t, std::function<void()> &&func) {
    { t.execute(std::move(func)) } -> std::same_as<void>;
};

/**
 * <h2>Basic thread pool that uses a fixed-number or optionally grow/shrink between a [min, max] number of threads.</h2>
 * The growth policy is controlled by the TaskType template parameter:
 * <ol type="A">
 *   <li> <code>TaskType::IO_BOUND</code> if the task is IO bound, i.e. it is likely to block the thread for a long time, or
 *   <li> <code>TaskType::CPU_BOUND</code> if the task is CPU bound, i.e. it is primarily limited by the CPU and memory bandwidth.
 * </ol>
 * <br>
 * For the IO_BOUND policy, unused threads are kept alive for a pre-defined amount of time to be reused and gracefully
 * shut down to the minimum number of threads when unused.
 * <br>
 * For the CPU_BOUND policy, the threads are equally spread and pinned across the set CPU affinity.
 * <br>
 * The CPU affinity and OS scheduling policy and priorities are controlled by:
 * <ul>
 *  <li> <code>setAffinityMask(std::vector&lt;bool&gt; threadAffinityMask);</code> </li>
 *  <li> <code>setThreadSchedulingPolicy(const thread::Policy schedulingPolicy, const int schedulingPriority)</code> </li>
 * </ul>
 * Some user-level examples: <br>
 * @code
 *
 * // pool for CPU-bound tasks with exactly 1 thread
 * opencmw::BasicThreadPool&lt;opencmw::CPU_BOUND&gt; poolWork("CustomCpuPool", 1, 1);
 * // enqueue and add task to list -- w/o return type
 * poolWork.execute([] { fmt::print("Hello World from thread '{}'!\n", getThreadName()); }); // here: caller thread-name
 * poolWork.execute([](const auto &...args) { fmt::print(fmt::runtime("Hello World from thread '{}'!\n"), args...); }, getThreadName()); // here: executor thread-name
 * // [..]
 *
 * // pool for IO-bound (potentially blocking) tasks with at least 1 and a max of 1000 threads
 * opencmw::BasicThreadPool&lt;opencmw::IO_BOUND&gt;  poolIO("CustomIOPool", 1, 1000);
 * poolIO.keepAliveDuration = seconds(10);              // keeps idling threads alive for 10 seconds (optional)
 * poolIO.waitUntilInitialised();                       // wait until the pool is initialised (optional)
 * poolIO.setAffinityMask({ true, true, true, false }); // allows executor threads to run on the first four CPU cores
 *
 * constexpr auto           func1  = [](const auto &...args) { return fmt::format(fmt::runtime("thread '{1}' scheduled task '{0}'!\n"), getThreadName(), args...); };
 * std::future&lt;std::string&gt; result = poolIO.execute&lt;"customTaskName"&gt;(func1, getThreadName()); // N.B. the calling thread is owner of the std::future
 *
 * // execute a task with a name, a priority and single-core affinity (here: 2)
 * poolIO.execute&lt;"task name", 20U, 2&gt;([]() { fmt::print("Hello World from custom thread '{}'!\n", getThreadName()); });
 *
 * try {
 *     poolIO.execute&lt;"customName", 20U, 3&gt;([]() {  [..] this potentially long-running task is trackable via it's 'customName' thread name [..] });
 * } catch (const std::invalid_argument &e) {
 *     fmt::print("caught exception: {}\n", e.what());
 * }
 * @endcode
 */
class BasicThreadPool {
    using Task      = thread_pool::detail::Task;
    using TaskQueue = thread_pool::detail::TaskQueue;
    static std::atomic<uint64_t> _globalPoolId;
    static std::atomic<uint64_t> _taskID;

    static std::string
    generateName() {
        return fmt::format("BasicThreadPool#{}", _globalPoolId.fetch_add(1));
    }

    std::atomic_bool        _initialised = ATOMIC_FLAG_INIT;
    std::atomic_bool        _shutdown    = false;

    std::condition_variable _condition;
    std::atomic_size_t      _numTaskedQueued = 0U; // cache for _taskQueue.size()
    std::atomic_size_t      _numTasksRunning = 0U;
    TaskQueue               _taskQueue;
    TaskQueue               _recycledTasks;

    std::mutex              _threadListMutex;
    std::atomic_size_t      _numThreads = 0U;
    std::list<std::thread>  _threads;

    std::vector<bool>       _affinityMask;
    thread::Policy          _schedulingPolicy   = thread::Policy::OTHER;
    int                     _schedulingPriority = 0;

    const std::string       _poolName;
    const TaskType          _taskType;
    const uint32_t          _minThreads;
    const uint32_t          _maxThreads;

public:
    std::chrono::microseconds sleepDuration     = std::chrono::milliseconds(1);
    std::chrono::milliseconds keepAliveDuration = std::chrono::seconds(10);

    BasicThreadPool(const std::string_view &name = generateName(), const TaskType taskType = TaskType::CPU_BOUND, uint32_t min = std::thread::hardware_concurrency(),
                    uint32_t max = std::thread::hardware_concurrency())
        : _poolName(name), _taskType(taskType), _minThreads(std::min(min, max)), _maxThreads(max) {
        assert(min > 0 && "minimum number of threads must be > 0");
        for (uint32_t i = 0; i < _minThreads; ++i) {
            createWorkerThread();
        }
    }

    ~BasicThreadPool() {
        _shutdown = true;
        _condition.notify_all();
        for (auto &t : _threads) {
            t.join();
        }
    }

    BasicThreadPool(const BasicThreadPool &) = delete;
    BasicThreadPool(BasicThreadPool &&)      = delete;
    BasicThreadPool &
    operator=(const BasicThreadPool &)
            = delete;
    BasicThreadPool &
    operator=(BasicThreadPool &&)
            = delete;

    [[nodiscard]] std::string
    poolName() const noexcept {
        return _poolName;
    }

    [[nodiscard]] uint32_t
    minThreads() const noexcept {
        return _minThreads;
    };

    [[nodiscard]] uint32_t
    maxThreads() const noexcept {
        return _maxThreads;
    };

    [[nodiscard]] std::size_t
    numThreads() const noexcept {
        return std::atomic_load_explicit(&_numThreads, std::memory_order_acquire);
    }

    [[nodiscard]] std::size_t
    numTasksRunning() const noexcept {
        return std::atomic_load_explicit(&_numTasksRunning, std::memory_order_acquire);
    }

    [[nodiscard]] std::size_t
    numTasksQueued() const {
        return std::atomic_load_explicit(&_numTaskedQueued, std::memory_order_acquire);
    }

    [[nodiscard]] std::size_t
    numTasksRecycled() const {
        return _recycledTasks.size();
    }

    [[nodiscard]] bool
    isInitialised() const {
        return _initialised.load(std::memory_order::acquire);
    }

    void
    waitUntilInitialised() const {
        _initialised.wait(false);
    }

    void
    requestShutdown() {
        _shutdown = true;
        _condition.notify_all();
        for (auto &t : _threads) {
            t.join();
        }
    }

    [[nodiscard]] bool
    isShutdown() const {
        return _shutdown;
    }

    //

    [[nodiscard]] std::vector<bool>
    getAffinityMask() const {
        return _affinityMask;
    }

    void
    setAffinityMask(const std::vector<bool> &threadAffinityMask) {
        _affinityMask.clear();
        std::copy(threadAffinityMask.begin(), threadAffinityMask.end(), std::back_inserter(_affinityMask));
        cleanupFinishedThreads();
        updateThreadConstraints();
    }

    [[nodiscard]] auto
    getSchedulingPolicy() const {
        return _schedulingPolicy;
    }

    [[nodiscard]] auto
    getSchedulingPriority() const {
        return _schedulingPriority;
    }

    void
    setThreadSchedulingPolicy(const thread::Policy schedulingPolicy = thread::Policy::OTHER, const int schedulingPriority = 0) {
        _schedulingPolicy   = schedulingPolicy;
        _schedulingPriority = schedulingPriority;
        cleanupFinishedThreads();
        updateThreadConstraints();
    }

    // TODO: Do we need support for cancellation?
    template<const detail::basic_fixed_string taskName = "", uint32_t priority = 0, int32_t cpuID = -1, std::invocable Callable, typename... Args, typename R = std::invoke_result_t<Callable, Args...>>
        requires(std::is_same_v<R, void>)
    void
    execute(Callable &&func, Args &&...args) {
        static thread_local gr::SpinWait spinWait;
        if constexpr (cpuID >= 0) {
            if (cpuID >= _affinityMask.size() || (cpuID >= 0 && !_affinityMask[cpuID])) {
                throw std::invalid_argument(
                        fmt::format("requested cpuID {} incompatible with set affinity mask({}): [{}]", cpuID, _affinityMask.size(), fmt::join(_affinityMask.begin(), _affinityMask.end(), ", ")));
            }
        }
        _numTaskedQueued.fetch_add(1U);

        _taskQueue.push(createTask<taskName, priority, cpuID>(std::forward<decltype(func)>(func), std::forward<decltype(func)>(args)...));
        _condition.notify_one();
        if (_taskType == TaskType::IO_BOUND) {
            spinWait.spinOnce();
            spinWait.spinOnce();
            while (_taskQueue.size() > 0) {
                if (const auto nThreads = numThreads(); nThreads <= numTasksRunning() && nThreads <= _maxThreads) {
                    createWorkerThread();
                }
                _condition.notify_one();
                spinWait.spinOnce();
                spinWait.spinOnce();
            }
            spinWait.reset();
        }
    }

    template<const detail::basic_fixed_string taskName = "", uint32_t priority = 0, int32_t cpuID = -1, std::invocable Callable, typename... Args, typename R = std::invoke_result_t<Callable, Args...>>
        requires(!std::is_same_v<R, void>)
    [[nodiscard]] std::future<R>
    execute(Callable &&func, Args &&...funcArgs) {
        if constexpr (cpuID >= 0) {
            if (cpuID >= _affinityMask.size() || (cpuID >= 0 && !_affinityMask[cpuID])) {
#ifdef _LIBCPP_VERSION
                throw std::invalid_argument(fmt::format("cpuID {} is out of range [0,{}] or incompatible with set affinity mask", cpuID, _affinityMask.size()));
#else
                throw std::invalid_argument(fmt::format("cpuID {} is out of range [0,{}] or incompatible with set affinity mask [{}]", cpuID, _affinityMask.size(), _affinityMask));
#endif
            }
        }
        std::promise<R> promise;
        auto            result = promise.get_future();
        auto            lambda = [promise = std::move(promise), func = std::forward<decltype(func)>(func), ... args = std::forward<decltype(func)>(funcArgs)]() mutable {
            try {
                promise.set_value(func(args...));
            } catch (...) {
                promise.set_exception(std::current_exception());
            }
        };
        execute<taskName, priority, cpuID>(std::move(lambda));
        return result;
    }

private:
    void
    cleanupFinishedThreads() {
        std::scoped_lock lock(_threadListMutex);
        // TODO:
        // (C++Ref) A thread that has finished executing code, but has not yet been
        // joined is still considered an active thread of execution and is
        // therefore joinable.
        // std::erase_if(_threads, [](auto &thread) { return !thread.joinable(); });
    }

    void
    updateThreadConstraints() {
        std::scoped_lock lock(_threadListMutex);
        // std::erase_if(_threads, [](auto &thread) { return !thread.joinable(); });

        std::for_each(_threads.begin(), _threads.end(), [this, threadID = std::size_t{ 0 }](auto &thread) mutable { this->updateThreadConstraints(threadID++, thread); });
    }

    void
    updateThreadConstraints(const std::size_t threadID, std::thread &thread) const {
        thread::setThreadName(fmt::format("{}#{}", _poolName, threadID), thread);
        thread::setThreadSchedulingParameter(_schedulingPolicy, _schedulingPriority, thread);
        if (!_affinityMask.empty()) {
            if (_taskType == TaskType::IO_BOUND) {
                thread::setThreadAffinity(_affinityMask);
                return;
            }
            const std::vector<bool> affinityMask = distributeThreadAffinityAcrossCores(_affinityMask, threadID);
            std::cout << fmt::format("{}#{} affinity mask: {}", _poolName, threadID, fmt::join(affinityMask.begin(), affinityMask.end(), ",")) << std::endl;
            thread::setThreadAffinity(affinityMask);
        }
    }

    std::vector<bool>
    distributeThreadAffinityAcrossCores(const std::vector<bool> &globalAffinityMask, const std::size_t threadID) const {
        if (globalAffinityMask.empty()) {
            return {};
        }
        std::vector<bool> affinityMask;
        std::size_t       coreCount = 0;
        for (bool value : globalAffinityMask) {
            if (value) {
                affinityMask.push_back(coreCount++ % _minThreads == threadID);
            } else {
                affinityMask.push_back(false);
            }
        }
        return affinityMask;
    }

    void
    createWorkerThread() {
        std::scoped_lock  lock(_threadListMutex);
        const std::size_t nThreads = numThreads();
        std::thread      &thread   = _threads.emplace_back(&BasicThreadPool::worker, this);
        updateThreadConstraints(nThreads + 1, thread);
    }

    template<const detail::basic_fixed_string taskName = "", uint32_t priority = 0, int32_t cpuID = -1, std::invocable Callable, typename... Args>
    auto
    createTask(Callable &&func, Args &&...funcArgs) {
        const auto getTask = [&recycledTasks = _recycledTasks](Callable &&f, Args &&...args) {
            auto extracted = recycledTasks.pop();
            if (extracted.empty()) {
                if constexpr (sizeof...(Args) == 0) {
                    extracted.push_front(Task{ .id = _taskID.fetch_add(1U) + 1U, .func = std::move(f) });
                } else {
                    extracted.push_front(Task{ .id = _taskID.fetch_add(1U) + 1U, .func = std::move(std::bind_front(std::forward<decltype(func)>(f), std::forward<decltype(func)>(args)...)) });
                }
            } else {
                auto &task = extracted.front();
                task.id    = _taskID.fetch_add(1U) + 1U;
                if constexpr (sizeof...(Args) == 0) {
                    task.func = std::move(f);
                } else {
                    task.func = std::move(std::bind_front(std::forward<decltype(func)>(f), std::forward<decltype(func)>(args)...));
                }
            }
            return extracted;
        };

        auto  taskContainer = getTask(std::forward<decltype(func)>(func), std::forward<decltype(func)>(funcArgs)...);
        auto &task          = taskContainer.front();

        if constexpr (!taskName.empty()) {
            task.name = taskName.c_str();
        }
        task.priority = priority;
        task.cpuID    = cpuID;

        return taskContainer;
    }

    TaskQueue::TaskContainer
    popTask() {
        auto result = _taskQueue.pop();
        if (!result.empty()) {
            _numTaskedQueued.fetch_sub(1U);
        }
        return result;
    }

    void
    worker() {
        constexpr uint32_t N_SPIN       = 1 << 8;
        uint32_t           noop_counter = 0;
        const auto         threadID     = _numThreads.fetch_add(1);
        std::mutex         mutex;
        std::unique_lock   lock(mutex);
        auto               lastUsed              = std::chrono::steady_clock::now();
        auto               timeDiffSinceLastUsed = std::chrono::steady_clock::now() - lastUsed;
        if (numThreads() >= _minThreads) {
            std::atomic_store_explicit(&_initialised, true, std::memory_order_release);
            _initialised.notify_all();
        }
        _numThreads.notify_one();
        bool running = true;
        do {
            if (TaskQueue::TaskContainer currentTaskContainer = popTask(); !currentTaskContainer.empty()) {
                assert(!currentTaskContainer.empty());
                auto &currentTask = currentTaskContainer.front();
                _numTasksRunning.fetch_add(1);
                bool nameSet = !(currentTask.name.empty());
                if (nameSet) {
                    thread::setThreadName(currentTask.name);
                }
                currentTask.func();
                // execute dependent children
                currentTask.reset();
                _recycledTasks.push(std::move(currentTaskContainer));
                _numTasksRunning.fetch_sub(1);
                if (nameSet) {
                    thread::setThreadName(fmt::format("{}#{}", _poolName, threadID));
                }
                lastUsed     = std::chrono::steady_clock::now();
                noop_counter = 0;
            } else if (++noop_counter > N_SPIN) [[unlikely]] {
                // perform some thread maintenance tasks before going to sleep
                noop_counter = noop_counter / 2;
                cleanupFinishedThreads();

                _condition.wait_for(lock, keepAliveDuration, [this] { return numTasksQueued() > 0 || isShutdown(); });
            }
            // check if this thread is to be kept
            timeDiffSinceLastUsed = std::chrono::steady_clock::now() - lastUsed;
            if (isShutdown()) {
                auto nThread = _numThreads.fetch_sub(1);
                _numThreads.notify_all();
                if (nThread == 1) { // cleanup last thread
                    _recycledTasks.clear();
                    _taskQueue.clear();
                }
                running = false;
            } else if (timeDiffSinceLastUsed > keepAliveDuration) { // decrease to the minimum of _minThreads in a thread safe way
                unsigned long nThreads = numThreads();
                while (nThreads > minThreads()) { // compare and swap loop
                    if (_numThreads.compare_exchange_weak(nThreads, nThreads - 1, std::memory_order_acq_rel)) {
                        _numThreads.notify_all();
                        if (nThreads == 1) { // cleanup last thread
                            _recycledTasks.clear();
                            _taskQueue.clear();
                        }
                        running = false;
                        break;
                    }
                }
            }
        } while (running);
    }
};

inline std::atomic<uint64_t> BasicThreadPool::_globalPoolId = 0U;
inline std::atomic<uint64_t> BasicThreadPool::_taskID       = 0U;
static_assert(ThreadPool<BasicThreadPool>);

} // namespace gr::thread_pool

#endif // THREADPOOL_HPP


// #include <gnuradio-4.0/annotated.hpp>
 // This needs to be included after fmt/format.h, as it defines formatters only if FMT_FORMAT_H_ is defined
// #include <gnuradio-4.0/reflection.hpp>

// #include <gnuradio-4.0/Settings.hpp>
#ifndef GNURADIO_SETTINGS_HPP
#define GNURADIO_SETTINGS_HPP

#include <atomic>
#include <chrono>
#include <concepts>
#include <mutex>
#include <optional>
#include <set>
#include <variant>

#include <fmt/format.h>
#include <fmt/ranges.h>

// #include <gnuradio-4.0/annotated.hpp>

// #include <gnuradio-4.0/BlockTraits.hpp>

// #include <gnuradio-4.0/meta/formatter.hpp>

// #include <gnuradio-4.0/reflection.hpp>

// #include <gnuradio-4.0/Tag.hpp>


namespace gr {

namespace settings {
template<typename T>
inline constexpr static bool
isSupportedType() {
    return std::is_arithmetic_v<T> || std::is_same_v<T, std::string> || gr::meta::vector_type<T> || std::is_same_v<T, property_map>;
}
} // namespace settings

struct ApplyStagedParametersResult {
    property_map forwardParameters; // parameters that should be forwarded to dependent child blocks
    property_map appliedParameters;
};

namespace detail {
template<class T>
inline constexpr void
hash_combine(std::size_t &seed, const T &v) noexcept {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
} // namespace detail

struct SettingsCtx {
    // using TimePoint = std::chrono::time_point<std::chrono::utc_clock>; // TODO: change once the C++20 support is ubiquitous
    using TimePoint               = std::chrono::time_point<std::chrono::system_clock>;
    std::optional<TimePoint> time = std::nullopt; /// UTC time-stamp from which the setting is valid
    property_map             context;             /// user-defined multiplexing context for which the setting is valid

    SettingsCtx() {}

    explicit SettingsCtx(const TimePoint &t, const property_map &ctx = {}) {
        time    = t;
        context = ctx;
    }

    bool
    operator==(const SettingsCtx &) const
            = default;

    bool
    operator<(const SettingsCtx &other) {
        // order by time
        return !time || (other.time && *time < *other.time);
    }

    [[nodiscard]] std::size_t
    hash() const noexcept {
        std::size_t seed = 0;
        if (time) {
            detail::hash_combine(seed, time.value().time_since_epoch().count());
        }
        for (const auto &[key, val] : context) {
            detail::hash_combine(seed, key);
            detail::hash_combine(seed, pmtv::to_base64(val));
        }
        return seed;
    }
};

/**
 * @brief a concept verifying whether a processing block optionally provides a `settingsChanged` callback to react to
 * block configuration changes and/or to influence forwarded downstream parameters.
 *
 * Implementers may have:
 * 1. `settingsChanged(oldSettings, newSettings)`
 * 2. `settingsChanged(oldSettings, newSettings, forwardSettings)`
 *    - where `forwardSettings` is for influencing subsequent blocks. E.g., a decimating block might adjust the `sample_rate` for downstream blocks.
 */
template<typename BlockType>
concept HasSettingsChangedCallback = requires(BlockType *block, const property_map &oldSettings, property_map &newSettings) {
    { block->settingsChanged(oldSettings, newSettings) };
} or requires(BlockType *block, const property_map &oldSettings, property_map &newSettings, property_map &forwardSettings) {
    { block->settingsChanged(oldSettings, newSettings, forwardSettings) };
};

/**
 * @brief a concept verifying whether a processing block optionally provides a `reset` callback to react to
 * block reset requests (being called after the settings have been reverted(.
 */
template<typename TBlock>
concept HasSettingsResetCallback = requires(TBlock *block) {
    { block->reset() };
};

template<typename T>
concept SettingsLike = requires(T t, std::span<const std::string> parameter_keys, const std::string &parameter_key, const property_map &parameters, SettingsCtx ctx) {
    /**
     * @brief returns if there are stages settings that haven't been applied yet.
     */
    { t.changed() } -> std::same_as<bool>;

    /**
     * @brief stages new key-value pairs that shall replace the block field-based settings.
     * N.B. settings become only active after executing 'applyStagedParameters()' (usually done early on in the 'Block::work()' function)
     * @return key-value pairs that could not be set
     */
    { t.set(parameters, ctx) } -> std::same_as<property_map>;
    { t.set(parameters) } -> std::same_as<property_map>;

    /**
     * @brief updates parameters based on block input tags for those with keys stored in `autoUpdateParameters()`
     * Parameter changes to down-stream blocks is controlled via `autoForwardParameters()`
     */
    { t.autoUpdate(parameters, ctx) } -> std::same_as<void>;
    { t.autoUpdate(parameters) } -> std::same_as<void>;

    /**
     * @brief return all available block settings as key-value pairs
     */
    { t.get() } -> std::same_as<property_map>;

    /**
     * @brief return key-pmt values map for multiple keys
     */
    { t.get(parameter_keys, ctx) } -> std::same_as<property_map>;
    { t.get(parameter_keys) } -> std::same_as<property_map>;

    /**
     * @brief return pmt value for a single key
     */
    { t.get(parameter_key, ctx) } -> std::same_as<std::optional<pmtv::pmt>>;
    { t.get(parameter_key) } -> std::same_as<std::optional<pmtv::pmt>>;

    /**
     * @brief returns the staged/not-yet-applied new parameters
     */
    { t.stagedParameters() } -> std::same_as<const property_map>;

    /**
     * @brief synchronise map-based with actual block field-based settings
     */
    { t.applyStagedParameters() } -> std::same_as<ApplyStagedParametersResult>;

    /**
     * @brief synchronises the map-based with the block's field-based parameters
     * (N.B. usually called after the staged parameters have been synchronised)
     */
    { t.updateActiveParameters() } -> std::same_as<void>;
};

struct SettingsBase {
    std::atomic_bool _changed{ false };

    virtual ~SettingsBase() = default;

    void
    swap(SettingsBase &other) noexcept {
        if (this == &other) {
            return;
        }
        bool temp = _changed;
        // avoid CAS-loop since this called only during initialisation where there is no concurrent access possible.
        std::atomic_store_explicit(&_changed, std::atomic_load_explicit(&other._changed, std::memory_order_acquire), std::memory_order_release);
        other._changed = temp;
    }

    /**
     * @brief returns if there are stages settings that haven't been applied yet.
     */
    [[nodiscard]] bool
    changed() const noexcept {
        return _changed;
    }

    /**
     * @brief stages new key-value pairs that shall replace the block field-based settings.
     * N.B. settings become only active after executing 'applyStagedParameters()' (usually done early on in the 'Block::work()' function)
     * @return key-value pairs that could not be set
     */
    [[nodiscard]] virtual property_map
    set(const property_map &parameters, SettingsCtx ctx = {})
            = 0;

    virtual void
    storeDefaults()
            = 0;
    virtual void
    resetDefaults()
            = 0;

    /**
     * @brief updates parameters based on block input tags for those with keys stored in `autoUpdateParameters()`
     * Parameter changes to down-stream blocks is controlled via `autoForwardParameters()`
     */
    virtual void
    autoUpdate(const property_map &parameters, SettingsCtx = {})
            = 0;

    /**
     * @brief return all (or for selected multiple keys) available block settings as key-value pairs
     */
    [[nodiscard]] virtual property_map
    get(std::span<const std::string> parameter_keys = {}, SettingsCtx = {}) const noexcept
            = 0;

    [[nodiscard]] virtual std::optional<pmtv::pmt>
    get(const std::string &parameter_key, SettingsCtx = {}) const noexcept = 0;

    /**
     * @brief returns the staged/not-yet-applied new parameters
     */
    [[nodiscard]] virtual const property_map
    stagedParameters() const
            = 0;

    [[nodiscard]] virtual std::set<std::string, std::less<>> &
    autoUpdateParameters() noexcept
            = 0;

    [[nodiscard]] virtual std::set<std::string, std::less<>> &
    autoForwardParameters() noexcept
            = 0;

    /**
     * @brief synchronise map-based with actual block field-based settings
     * returns map with key-value tags that should be forwarded
     * to dependent/child blocks.
     */
    [[nodiscard]] virtual ApplyStagedParametersResult
    applyStagedParameters() noexcept
            = 0;

    /**
     * @brief synchronises the map-based with the block's field-based parameters
     * (N.B. usually called after the staged parameters have been synchronised)
     */
    virtual void
    updateActiveParameters() noexcept
            = 0;
};

namespace detail {
template<typename T>
concept HasBaseType = requires { typename std::remove_cvref_t<T>::base_t; };
}; // namespace detail

template<typename TBlock>
class BasicSettings : public SettingsBase {
    TBlock                            *_block = nullptr;
    mutable std::mutex                 _lock{};
    property_map                       _active{}; // copy of class field settings as pmt-style map
    property_map                       _staged{}; // parameters to become active before the next work() call
    std::set<std::string, std::less<>> _auto_update{};
    std::set<std::string, std::less<>> _auto_forward{};
    property_map                       _default_settings{};

public:
    BasicSettings()  = delete;
    ~BasicSettings() = default;

    explicit constexpr BasicSettings(TBlock &block) noexcept : SettingsBase(), _block(&block) {
        if constexpr (requires { &TBlock::settingsChanged; }) { // if settingsChanged is defined
            static_assert(HasSettingsChangedCallback<TBlock>, "if provided, settingsChanged must have either a `(const property_map& old, property_map& new, property_map& fwd)`"
                                                              "or `(const property_map& old, property_map& new)` parameter signatures.");
        }

        if constexpr (requires { &TBlock::reset; }) { // if reset is defined
            static_assert(HasSettingsResetCallback<TBlock>, "if provided, reset() may have no function parameters");
        }

        if constexpr (refl::is_reflectable<TBlock>()) {
            // register block-global description
            constexpr bool hasMetaInfo = requires(TBlock t) {
                {
                    unwrap_if_wrapped_t<decltype(t.meta_information)> {}
                } -> std::same_as<property_map>;
            };

            if constexpr (hasMetaInfo && requires(TBlock t) { t.description; }) {
                static_assert(std::is_same_v<std::remove_cvref_t<unwrap_if_wrapped_t<decltype(TBlock::description)>>, std::string_view>);
                _block->meta_information.value["description"] = std::string(_block->description);
            }

            // handle meta-information for UI and other non-processing-related purposes
            auto iterate_over_member = [this]<typename Member>(Member member) {
                using RawType         = std::remove_cvref_t<decltype(member(*_block))>;
                using Type            = unwrap_if_wrapped_t<RawType>;
                const auto memberName = std::string(get_display_name(member));

                if constexpr (hasMetaInfo && AnnotatedType<RawType>) {
                    _block->meta_information.value[memberName + "::description"]   = std::string(RawType::description());
                    _block->meta_information.value[memberName + "::documentation"] = std::string(RawType::documentation());
                    _block->meta_information.value[memberName + "::unit"]          = std::string(RawType::unit());
                    _block->meta_information.value[memberName + "::visible"]       = RawType::visible();
                }

                // detect whether field has one of the DEFAULT_TAGS signature
                if constexpr (traits::port::is_not_any_port_or_collection<Type> && !std::is_const_v<Type> && is_writable(member) && settings::isSupportedType<Type>()) {
                    meta::tuple_for_each(
                            [&memberName, this](auto &&default_tag) {
                                if (default_tag == memberName) {
                                    _auto_forward.emplace(memberName);
                                }
                                _auto_update.emplace(memberName);
                            },
                            gr::tag::DEFAULT_TAGS);
                }
            };

            if constexpr (detail::HasBaseType<TBlock>) {
                refl::util::for_each(refl::reflect<typename std::remove_cvref_t<TBlock>::base_t>().members, iterate_over_member);
            }
            refl::util::for_each(refl::reflect<TBlock>().members, iterate_over_member);
        }
    }

    constexpr BasicSettings(const BasicSettings &other) noexcept : SettingsBase(other) {
        BasicSettings temp(other);
        swap(temp);
    }

    constexpr BasicSettings(BasicSettings &&other) noexcept : SettingsBase(std::move(other)) {
        BasicSettings temp(std::move(other));
        swap(temp);
    }

    BasicSettings &
    operator=(const BasicSettings &other) noexcept {
        swap(other);
        return *this;
    }

    BasicSettings &
    operator=(BasicSettings &&other) noexcept {
        BasicSettings temp(std::move(other));
        swap(temp);
        return *this;
    }

    void
    swap(BasicSettings &other) noexcept {
        if (this == &other) {
            return;
        }
        SettingsBase::swap(other);
        std::swap(_block, other._block);
        std::scoped_lock lock(_lock, other._lock);
        std::swap(_active, other._active);
        std::swap(_staged, other._staged);
        std::swap(_auto_update, other._auto_update);
        std::swap(_auto_forward, other._auto_forward);
    }

    [[nodiscard]] property_map
    set(const property_map &parameters, SettingsCtx = {}) override {
        property_map ret;
        if constexpr (refl::is_reflectable<TBlock>()) {
            std::lock_guard lg(_lock);
            for (const auto &[localKey, localValue] : parameters) {
                const auto &key                 = localKey;
                const auto &value               = localValue;
                bool        is_set              = false;
                auto        iterate_over_member = [&, this](auto member) {
                    using Type = unwrap_if_wrapped_t<std::remove_cvref_t<decltype(member(*_block))>>;
                    if constexpr (traits::port::is_not_any_port_or_collection<Type> && !std::is_const_v<Type> && is_writable(member) && settings::isSupportedType<Type>()) {
                        const auto fieldName = std::string_view(get_display_name(member));
                        if (fieldName == key && std::holds_alternative<Type>(value)) {
                            if (_auto_update.contains(key)) {
                                _auto_update.erase(key);
                            }
                            _staged.insert_or_assign(key, value);
                            SettingsBase::_changed.store(true);
                            is_set = true;
                        }
                        if (fieldName == key && !std::holds_alternative<Type>(value)) {
                            throw std::invalid_argument([&key, &value] { // lazy evaluation
                                const std::size_t actual_index   = value.index();
                                const std::size_t required_index = meta::to_typelist<pmtv::pmt>::index_of<Type>(); // This too, as per your implementation.
                                return fmt::format("value for key '{}' has a wrong type. Index of actual type: {} ({}), Index of expected type: {} ({})", key, actual_index, "<missing pmt type>",
                                                          required_index, gr::meta::type_name<Type>());
                            }());
                        }
                    }
                };
                if constexpr (detail::HasBaseType<TBlock>) {
                    refl::util::for_each(refl::reflect<typename std::remove_cvref_t<TBlock>::base_t>().members, iterate_over_member);
                }
                refl::util::for_each(refl::reflect<TBlock>().members, iterate_over_member);
                if (!is_set) {
                    ret.insert_or_assign(key, pmtv::pmt(value));
                }
            }
        }

        // copy items that could not be matched to the block's meta_information map (if available)
        if constexpr (requires(TBlock t) {
                          {
                              unwrap_if_wrapped_t<decltype(t.meta_information)> {}
                          } -> std::same_as<property_map>;
                      }) {
            updateMaps(ret, _block->meta_information);
        }

        return ret; // N.B. returns those <key:value> parameters that could not be set
    }

    void
    storeDefaults() override {
        this->storeDefaultSettings(_default_settings);
    }

    void
    resetDefaults() override {
        _staged     = _default_settings;
        std::ignore = applyStagedParameters();
        if constexpr (HasSettingsResetCallback<TBlock>) {
            _block->reset();
        }
    }

    void
    autoUpdate(const property_map &parameters, SettingsCtx = {}) override {
        if constexpr (refl::is_reflectable<TBlock>()) {
            for (const auto &[localKey, localValue] : parameters) {
                const auto &key                 = localKey;
                const auto &value               = localValue;
                auto        iterate_over_member = [&](auto member) {
                    using Type = unwrap_if_wrapped_t<std::remove_cvref_t<decltype(member(*_block))>>;
                    if constexpr (traits::port::is_not_any_port_or_collection<Type> && !std::is_const_v<Type> && is_writable(member) && settings::isSupportedType<Type>()) {
                        if (std::string(get_display_name(member)) == key && std::holds_alternative<Type>(value)) {
                            _staged.insert_or_assign(key, value);
                            SettingsBase::_changed.store(true);
                        }
                    }
                };
                if constexpr (detail::HasBaseType<TBlock>) {
                    refl::util::for_each(refl::reflect<typename std::remove_cvref_t<TBlock>::base_t>().members, iterate_over_member);
                }
                refl::util::for_each(refl::reflect<TBlock>().members, iterate_over_member);
            }
        }
    }

    [[nodiscard]] const property_map
    stagedParameters() const noexcept override {
        std::lock_guard lg(_lock);
        return _staged;
    }

    [[nodiscard]] property_map
    get(std::span<const std::string> parameter_keys = {}, SettingsCtx = {}) const noexcept override {
        std::lock_guard lg(_lock);
        if (parameter_keys.empty()) {
            return _active;
        }
        property_map ret;
        for (const auto &key : parameter_keys) {
            if (_active.contains(key)) {
                ret.insert_or_assign(key, _active.at(key));
            }
        }
        return ret;
    }

    [[nodiscard]] std::optional<pmtv::pmt>
    get(const std::string &parameter_key, SettingsCtx = {}) const noexcept override {
        if constexpr (refl::is_reflectable<TBlock>()) {
            std::lock_guard lg(_lock);

            if (_active.contains(parameter_key)) {
                return { _active.at(parameter_key) };
            }
        }

        return std::nullopt;
    }

    [[nodiscard]] std::set<std::string, std::less<>> &
    autoUpdateParameters() noexcept override {
        return _auto_update;
    }

    [[nodiscard]] std::set<std::string, std::less<>> &
    autoForwardParameters() noexcept override {
        return _auto_forward;
    }

    /**
     * @brief synchronise map-based with actual block field-based settings
     * returns a structure containing three maps:
     *  - forwardParameters -- map with key-value tags that should be forwarded
     *    to dependent/child blocks.
     *  - appliedParameters -- map with peoperties that were successfully set
     */
    [[nodiscard]] ApplyStagedParametersResult
    applyStagedParameters() noexcept override {
        ApplyStagedParametersResult result;
        if constexpr (refl::is_reflectable<TBlock>()) {
            std::lock_guard lg(_lock);

            // prepare old settings if required
            property_map oldSettings;
            if constexpr (HasSettingsChangedCallback<TBlock>) {
                storeDefaultSettings(oldSettings);
            }

            // check if reset of settings should be performed
            if (_staged.contains(gr::tag::RESET_DEFAULTS)) {
                _staged.clear();
                resetDefaults();
            }

            // update staged and forward parameters based on member properties
            property_map staged;
            for (const auto &[localKey, localStaged_value] : _staged) {
                const auto &key                  = localKey;
                const auto &staged_value         = localStaged_value;
                auto        apply_member_changes = [&key, &staged, &result, &staged_value, this](auto member) {
                    using RawType = std::remove_cvref_t<decltype(member(*_block))>;
                    using Type    = unwrap_if_wrapped_t<RawType>;
                    if constexpr (traits::port::is_not_any_port_or_collection<Type> && !std::is_const_v<Type> && is_writable(member) && settings::isSupportedType<Type>()) {
                        if (std::string(get_display_name(member)) == key && std::holds_alternative<Type>(staged_value)) {
                            if constexpr (is_annotated<RawType>()) {
                                if (member(*_block).validate_and_set(std::get<Type>(staged_value))) {
                                    result.appliedParameters.insert_or_assign(key, staged_value);
                                    if constexpr (HasSettingsChangedCallback<TBlock>) {
                                        staged.insert_or_assign(key, staged_value);
                                    } else {
                                        std::ignore = staged; // help clang to see why staged is not unused
                                    }
                                } else {
                                    // TODO: replace with pmt error message on msgOut port (to note: clang compiler bug/issue)
#if !defined(__EMSCRIPTEN__) && !defined(__clang__)
                                    fmt::print(stderr, " cannot set field {}({})::{} = {} to {} due to limit constraints [{}, {}] validate func is {} defined\n", //
                                               _block->unique_name, _block->name, member(*_block), std::get<Type>(staged_value),                                  //
                                               std::string(get_display_name(member)), RawType::LimitType::MinRange,
                                               RawType::LimitType::MaxRange, //
                                               RawType::LimitType::ValidatorFunc == nullptr ? "not" : "");
#else
                                    fmt::print(stderr, " cannot set field {}({})::{} = {} to {} due to limit constraints [{}, {}] validate func is {} defined\n", //
                                               "_block->unique_name", "_block->name", "member(*_block)", std::get<Type>(staged_value),                            //
                                               std::string(get_display_name(member)), RawType::LimitType::MinRange,
                                               RawType::LimitType::MaxRange, //
                                               RawType::LimitType::ValidatorFunc == nullptr ? "not" : "");
#endif
                                }
                            } else {
                                member(*_block) = std::get<Type>(staged_value);
                                result.appliedParameters.insert_or_assign(key, staged_value);
                                if constexpr (HasSettingsChangedCallback<TBlock>) {
                                    staged.insert_or_assign(key, staged_value);
                                } else {
                                    std::ignore = staged; // help clang to see why staged is not unused
                                }
                            }
                        }
                        if (_auto_forward.contains(key)) {
                            result.forwardParameters.insert_or_assign(key, staged_value);
                        }
                    }
                };
                processMembers<TBlock>(apply_member_changes);
            }

            // update active parameters
            auto update_active = [this](auto member) {
                using Type = unwrap_if_wrapped_t<std::remove_cvref_t<decltype(member(*_block))>>;
                if constexpr (traits::port::is_not_any_port_or_collection<Type> && is_readable(member) && settings::isSupportedType<Type>()) {
                    _active.insert_or_assign(get_display_name(member), static_cast<Type>(member(*_block)));
                }
            };
            processMembers<TBlock>(update_active);

            // invoke user-callback function if staged is not empty
            if (!staged.empty()) {
                if constexpr (requires { _block->settingsChanged(/* old settings */ _active, /* new settings */ staged); }) {
                    _block->settingsChanged(/* old settings */ oldSettings, /* new settings */ staged);
                } else if constexpr (requires { _block->settingsChanged(/* old settings */ _active, /* new settings */ staged, /* new forward settings */ result.forwardParameters); }) {
                    _block->settingsChanged(/* old settings */ oldSettings, /* new settings */ staged, /* new forward settings */ result.forwardParameters);
                }
            }

            if (_staged.contains(gr::tag::STORE_DEFAULTS)) {
                storeDefaults();
            }

            if constexpr (HasSettingsResetCallback<TBlock>) {
                if (_staged.contains(gr::tag::RESET_DEFAULTS)) {
                    _block->reset();
                }
            }

            _staged.clear();
        }

        SettingsBase::_changed.store(false);
        return result;
    }

    void
    updateActiveParameters() noexcept override {
        if constexpr (refl::is_reflectable<TBlock>()) {
            std::lock_guard lg(_lock);
            auto            iterate_over_member = [&, this](auto member) {
                using Type = unwrap_if_wrapped_t<std::remove_cvref_t<decltype(member(*_block))>>;
                if constexpr (traits::port::is_not_any_port_or_collection<Type> && is_readable(member) && settings::isSupportedType<Type>()) {
                    _active.insert_or_assign(get_display_name(member), static_cast<Type>(member(*_block)));
                }
            };
            if constexpr (detail::HasBaseType<TBlock>) {
                refl::util::for_each(refl::reflect<typename std::remove_cvref_t<TBlock>::base_t>().members, iterate_over_member);
            }
            refl::util::for_each(refl::reflect<TBlock>().members, iterate_over_member);
        }
    }

private:
    void
    storeDefaultSettings(property_map &oldSettings) {
        // take a copy of the field -> map value of the old settings
        if constexpr (refl::is_reflectable<TBlock>()) {
            auto iterate_over_member = [&, this](auto member) {
                using Type = unwrap_if_wrapped_t<std::remove_cvref_t<decltype(member(*_block))>>;

                if constexpr (traits::port::is_not_any_port_or_collection<Type> && is_readable(member) && settings::isSupportedType<Type>()) {
                    oldSettings.insert_or_assign(get_display_name(member), pmtv::pmt(member(*_block)));
                }
            };
            if constexpr (detail::HasBaseType<TBlock>) {
                refl::util::for_each(refl::reflect<typename std::remove_cvref_t<TBlock>::base_t>().members, iterate_over_member);
            }
            refl::util::for_each(refl::reflect<TBlock>().members, iterate_over_member);
        }
    }

    template<typename T, typename Func>
    inline constexpr static void
    processMembers(Func func) {
        if constexpr (detail::HasBaseType<T>) {
            refl::util::for_each(refl::reflect<typename std::remove_cvref_t<T>::base_t>().members, func);
        }
        refl::util::for_each(refl::reflect<T>().members, func);
    }
};

static_assert(SettingsLike<BasicSettings<int>>);

} // namespace gr

namespace std {
template<>
struct hash<gr::SettingsCtx> {
    [[nodiscard]] size_t
    operator()(const gr::SettingsCtx &ctx) const noexcept {
        return ctx.hash();
    }
};
} // namespace std

#endif // GNURADIO_SETTINGS_HPP


// #include <gnuradio-4.0/LifeCycle.hpp>
#ifndef GNURADIO_LIFECYCLE_HPP
#define GNURADIO_LIFECYCLE_HPP

// #include <gnuradio-4.0/Message.hpp>

// #include <gnuradio-4.0/meta/formatter.hpp>

// #include <gnuradio-4.0/meta/utils.hpp>

// #include <gnuradio-4.0/reflection.hpp>


#include <atomic>
#include <expected>
#include <source_location>
#include <string>

namespace gr ::lifecycle {
/**
 * @enum lifecycle::State enumerates the possible states of a `Scheduler` lifecycle.
 *
 * Transition between the following states is triggered by specific actions or events:
 * - `IDLE`: The initial state before the scheduler has been initialized.
 * - `INITIALISED`: The scheduler has been initialized and is ready to start running.
 * - `RUNNING`: The scheduler is actively running.
 * - `REQUESTED_PAUSE`: A pause has been requested, and the scheduler is in the process of pausing.
 * - `PAUSED`: The scheduler is paused and can be resumed or stopped.
 * - `REQUESTED_STOP`: A stop has been requested, and the scheduler is in the process of stopping.
 * - `STOPPED`: The scheduler has been stopped and can be reset or re-initialized.
 * - `ERROR`: An error state that can be reached from any state at any time, requiring a reset.
 *
 * @note All `Block<T>`-derived classes can optionally implement any subset of the lifecycle methods
 * (`start()`, `stop()`, `reset()`, `pause()`, `resume()`) to handle state changes of the `Scheduler`.
 *
 * State diagram:
 *
 *                 Block<T>()              can be reached from
 *                    │                   anywhere and anytime.
 *              ┌─────┴────┐                   ┌────┴────┐
 * ┌────────────┤   IDLE   │                   │  ERROR  │
 * │            └────┬─────┘                   └────┬────┘
 * │                 │ init()                       │ reset()
 * │                 v                              │
 * │         ┌───────┴───────┐                      │
 * ├<────────┤  INITIALISED  ├<─────────────────────┤
 * │         └───────┬───────┘                      │
 * │                 │ start()                      │
 * │                 v                              │
 * │   stop() ┌──────┴──────┐                       │  ╓
 * │ ┌────────┤   RUNNING   ├<──────────┐           │  ║
 * │ │        └─────┬───────┘           │           │  ║
 * │ │              │ pause()           │           │  ║  isActive(lifecycle::State) ─> true
 * │ │              v                   │ resume()  │  ║
 * │ │    ┌─────────┴─────────┐   ┌─────┴─────┐     │  ║
 * │ │    │  REQUESTED_PAUSE  ├──>┤  PAUSED   │     │  ║
 * │ │    └──────────┬────────┘   └─────┬─────┘     │  ╙
 * │ │               │ stop()           │ stop()    │
 * │ │               v                  │           │
 * │ │     ┌─────────┴────────┐         │           │  ╓
 * │ └────>┤  REQUESTED_STOP  ├<────────┘           │  ║
 * │       └────────┬─────────┘                     │  ║
 * │                │                               │  ║  isShuttingDown(lifecycle::State) ─> true
 * │                v                               │  ║
 * │          ┌─────┴─────┐ reset()                 │  ║
 * └─────────>│  STOPPED  ├─────────────────────────┘  ║
 *            └─────┬─────┘                            ╙
 *                  │
 *                  v
 *              ~Block<T>()
 */
enum class State : char { IDLE, INITIALISED, RUNNING, REQUESTED_PAUSE, PAUSED, REQUESTED_STOP, STOPPED, ERROR };
using enum State;

inline constexpr bool
isActive(lifecycle::State state) noexcept {
    return state == RUNNING || state == REQUESTED_PAUSE || state == PAUSED;
}

inline constexpr bool
isShuttingDown(lifecycle::State state) noexcept {
    return state == REQUESTED_STOP || state == STOPPED;
}

constexpr bool
isValidTransition(const State from, const State to) noexcept {
    if (to == State::ERROR || from == to) {
        // can transit to ERROR from any state
        return true;
    }
    switch (from) {
    case State::IDLE: return to == State::INITIALISED || to == State::REQUESTED_STOP || to == State::STOPPED;
    case State::INITIALISED: return to == State::RUNNING || to == State::REQUESTED_STOP || to == State::STOPPED;
    case State::RUNNING: return to == State::REQUESTED_PAUSE || to == State::REQUESTED_STOP;
    case State::REQUESTED_PAUSE: return to == State::PAUSED;
    case State::PAUSED: return to == State::RUNNING || to == State::REQUESTED_STOP;
    case State::REQUESTED_STOP: return to == State::STOPPED;
    case State::STOPPED: return to == State::INITIALISED;
    case State::ERROR: return to == State::INITIALISED;
    default: return false;
    }
}

enum class StorageType { ATOMIC, NON_ATOMIC };

/**
 * @brief StateMachine class template that manages the lifecycle states of a Scheduler or Block.
 * It is designed to be inherited by blocks (TDerived) to safely and effectively manage their lifecycle state transitions.
 *
 * If implemented in TDerived, the following specific lifecycle methods are called:
 * - `init()`   when transitioning from IDLE to INITIALISED
 * - `start()`  when transitioning from INITIALISED to RUNNING
 * - `stop()`   when transitioning from any `isActive(State)` to REQUESTED_STOP
 * - `pause()`  when transitioning from RUNNING to REQUESTED_PAUSE
 * - `resume()` when transitioning from PAUSED to RUNNING
 * - `reset()`  when transitioning from any state (typically ERROR or STOPPED) to INITIALISED.
 * If any of these methods throw an exception, the StateMachine transitions to the ERROR state, captures,
 * and forward the exception details.
 *
 * To react to state changes, TDerived can implement the `stateChanged(State newState)` method.
 *
 * @tparam TDerived The derived class type implementing specific lifecycle methods.
 * @tparam storageType Specifies the storage type for the state, allowing for atomic operations
 *         for thread-safe state changes. Defaults to ATOMIC.
 */
template<typename TDerived, StorageType storageType = StorageType::ATOMIC>
class StateMachine {
protected:
    using StateStorage  = std::conditional_t<storageType == StorageType::ATOMIC, std::atomic<State>, State>;
    StateStorage _state = lifecycle::State::IDLE;

    void
    setAndNotifyState(State newState) {
        if constexpr (requires(TDerived d) { d.stateChanged(newState); }) {
            static_cast<TDerived *>(this)->stateChanged(newState);
        }
        if constexpr (storageType == StorageType::ATOMIC) {
            _state.store(newState, std::memory_order_release);
            _state.notify_all();
        } else {
            _state = newState;
        }
    }

    std::string
    getBlockName() {
        if constexpr (requires(TDerived d) { d.uniqueName(); }) {
            return std::string{ static_cast<TDerived *>(this)->uniqueName() };
        } else if constexpr (requires(TDerived d) { d.unique_name; }) {
            return std::string{ static_cast<TDerived *>(this)->unique_name };
        } else {
            return "unknown block/item";
        }
    }

    template<typename TMethod>
    std::expected<void, Error>
    invokeLifecycleMethod(TMethod method, const std::source_location &location) {
        try {
            (static_cast<TDerived *>(this)->*method)();
            return {};
        } catch (const std::exception &e) {
            setAndNotifyState(State::ERROR);
            return std::unexpected(Error{ fmt::format("Block '{}' throws: {}", getBlockName(), e.what()), location });
        } catch (...) {
            setAndNotifyState(State::ERROR);
            return std::unexpected(Error{ fmt::format("Block '{}' throws: {}", getBlockName(), "unknown unnamed error"), location });
        }
    }

public:
    StateMachine() noexcept = default;

    StateMachine(StateMachine &&other) noexcept
        requires(storageType == StorageType::ATOMIC)
        : _state(other._state.load()) {} // atomic, not moving

    StateMachine(StateMachine &&other) noexcept
        requires(storageType != StorageType::ATOMIC)
        : _state(other._state) {} // plain enum

    [[nodiscard]] std::expected<void, Error>
    changeStateTo(State newState, const std::source_location location = std::source_location::current()) {
        State oldState = _state;
        if (oldState == newState || (oldState == STOPPED && newState == REQUESTED_STOP) || (oldState == PAUSED && newState == REQUESTED_PAUSE)) {
            return {};
        }

        if (!isValidTransition(oldState, newState)) {
            return std::unexpected(Error{ fmt::format("Block '{}' invalid state transition in {} from {} -> to {}", //
                                                                   getBlockName(), gr::meta::type_name<TDerived>(),              //
                                                                   magic_enum::enum_name(state()), magic_enum::enum_name(newState)),
                                                       location });
            ;
        }

        setAndNotifyState(newState);

        if constexpr (std::is_same_v<TDerived, void>) {
            return {};
        } else {
            // Call specific methods in TDerived based on the state
            if constexpr (requires(TDerived &d) { d.init(); }) {
                if (oldState == State::IDLE && newState == State::INITIALISED) {
                    return invokeLifecycleMethod(&TDerived::init, location);
                }
            }
            if constexpr (requires(TDerived &d) { d.start(); }) {
                if (oldState == State::INITIALISED && newState == State::RUNNING) {
                    return invokeLifecycleMethod(&TDerived::start, location);
                }
            }
            if constexpr (requires(TDerived &d) { d.stop(); }) {
                if (newState == State::REQUESTED_STOP) {
                    return invokeLifecycleMethod(&TDerived::stop, location);
                }
            }
            if constexpr (requires(TDerived &d) { d.pause(); }) {
                if (newState == State::REQUESTED_PAUSE) {
                    return invokeLifecycleMethod(&TDerived::pause, location);
                }
            }
            if constexpr (requires(TDerived &d) { d.resume(); }) {
                if ((oldState == State::REQUESTED_PAUSE || oldState == State::PAUSED) && newState == State::RUNNING) {
                    return invokeLifecycleMethod(&TDerived::resume, location);
                }
            }
            if constexpr (requires(TDerived &d) { d.reset(); }) {
                if (oldState != State::IDLE && newState == State::INITIALISED) {
                    return invokeLifecycleMethod(&TDerived::reset, location);
                }
            }

            return {};
        }
    }

    [[nodiscard]] State
    state() const noexcept {
        if constexpr (storageType == StorageType::ATOMIC) {
            return _state.load();
        } else {
            return _state;
        }
    }

    void
    waitOnState(State oldState)
        requires(storageType == StorageType::ATOMIC)
    {
        _state.wait(oldState);
    }
};

} // namespace gr::lifecycle

#endif // GNURADIO_LIFECYCLE_HPP


namespace gr {

namespace stdx = vir::stdx;
using gr::meta::fixed_string;

template<typename F>
constexpr void
simd_epilogue(auto width, F &&fun) {
    static_assert(std::has_single_bit(+width));
    auto w2 = std::integral_constant<std::size_t, width / 2>{};
    if constexpr (w2 > 0) {
        fun(w2);
        simd_epilogue(w2, std::forward<F>(fun));
    }
}

template<std::ranges::contiguous_range... Ts, typename Flag = stdx::element_aligned_tag>
constexpr auto
simdize_tuple_load_and_apply(auto width, const std::tuple<Ts...> &rngs, auto offset, auto &&fun, Flag f = {}) {
    using Tup = meta::simdize<std::tuple<std::ranges::range_value_t<Ts>...>, width>;
    return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
        return fun(std::tuple_element_t<Is, Tup>(std::ranges::data(std::get<Is>(rngs)) + offset, f)...);
    }(std::make_index_sequence<sizeof...(Ts)>());
}

template<typename T, typename... Us>
auto
invokeProcessOneWithOrWithoutOffset(T &node, std::size_t offset, const Us &...inputs) {
    if constexpr (traits::block::can_processOne_with_offset<T>) return node.processOne(offset, inputs...);
    else
        return node.processOne(inputs...);
}

template<std::size_t Index, PortType portType, typename Self>
[[nodiscard]] constexpr auto &
inputPort(Self *self) noexcept {
    using TRequestedPortType = typename traits::block::ports_data<Self>::template for_type<portType>::input_ports::template at<Index>;
    if constexpr (traits::block::block_defines_ports_as_member_variables<Self>) {
        using member_descriptor = traits::block::get_port_member_descriptor<Self, TRequestedPortType>;
        return member_descriptor()(*self);
    } else {
        return self->template getArgument<TRequestedPortType>();
    }
}

template<std::size_t Index, PortType portType, typename Self>
[[nodiscard]] constexpr auto &
outputPort(Self *self) noexcept {
    using TRequestedPortType = typename traits::block::ports_data<Self>::template for_type<portType>::output_ports::template at<Index>;
    if constexpr (traits::block::block_defines_ports_as_member_variables<Self>) {
        using member_descriptor = traits::block::get_port_member_descriptor<Self, TRequestedPortType>;
        return member_descriptor()(*self);
    } else {
        return self->template getArgument<TRequestedPortType>();
    }
}

template<fixed_string Name, typename Self>
[[nodiscard]] constexpr auto &
inputPort(Self *self) noexcept {
    constexpr int Index = meta::indexForName<Name, traits::block::all_input_ports<Self>>();
    if constexpr (Index == meta::default_message_port_index) {
        return self->msgIn;
    }
    return inputPort<Index, PortType::ANY, Self>(self);
}

template<fixed_string Name, typename Self>
[[nodiscard]] constexpr auto &
outputPort(Self *self) noexcept {
    constexpr int Index = meta::indexForName<Name, traits::block::all_output_ports<Self>>();
    if constexpr (Index == meta::default_message_port_index) {
        return self->msgOut;
    }
    return outputPort<Index, PortType::ANY, Self>(self);
}

template<PortType portType, typename Self>
[[nodiscard]] constexpr auto
inputPorts(Self *self) noexcept {
    return [self]<std::size_t... Idx>(std::index_sequence<Idx...>) {
        return std::tie(inputPort<Idx, portType>(self)...);
    }(std::make_index_sequence<traits::block::ports_data<Self>::template for_type<portType>::input_ports::size()>());
}

template<PortType portType, typename Self>
[[nodiscard]] constexpr auto
outputPorts(Self *self) noexcept {
    return [self]<std::size_t... Idx>(std::index_sequence<Idx...>) {
        return std::tie(outputPort<Idx, portType>(self)...);
    }(std::make_index_sequence<traits::block::ports_data<Self>::template for_type<portType>::output_ports::size>());
}

namespace work {

class Counter {
    std::atomic_uint64_t encodedCounter{ static_cast<uint64_t>(std::numeric_limits<gr::Size_t>::max()) << 32 };

public:
    void
    increment(std::size_t workRequestedInc, std::size_t workDoneInc) {
        uint64_t oldCounter;
        uint64_t newCounter;
        do {
            oldCounter         = encodedCounter;
            auto workRequested = static_cast<gr::Size_t>(oldCounter >> 32);
            auto workDone      = static_cast<gr::Size_t>(oldCounter & 0xFFFFFFFF);
            if (workRequested != std::numeric_limits<gr::Size_t>::max()) {
                workRequested = static_cast<uint32_t>(std::min(static_cast<std::uint64_t>(workRequested) + workRequestedInc, static_cast<std::uint64_t>(std::numeric_limits<gr::Size_t>::max())));
            }
            workDone += static_cast<gr::Size_t>(workDoneInc);
            newCounter = (static_cast<uint64_t>(workRequested) << 32) | workDone;
        } while (!encodedCounter.compare_exchange_weak(oldCounter, newCounter));
    }

    std::pair<std::size_t, std::size_t>
    getAndReset() {
        uint64_t oldCounter    = encodedCounter.exchange(0);
        auto     workRequested = static_cast<gr::Size_t>(oldCounter >> 32);
        auto     workDone      = static_cast<gr::Size_t>(oldCounter & 0xFFFFFFFF);
        if (workRequested == std::numeric_limits<gr::Size_t>::max()) {
            return { std::numeric_limits<std::size_t>::max(), static_cast<std::size_t>(workDone) };
        }
        return { static_cast<std::size_t>(workRequested), static_cast<std::size_t>(workDone) };
    }

    std::pair<std::size_t, std::size_t>
    get() {
        uint64_t oldCounter    = std::atomic_load_explicit(&encodedCounter, std::memory_order_acquire);
        auto     workRequested = static_cast<gr::Size_t>(oldCounter >> 32);
        auto     workDone      = static_cast<gr::Size_t>(oldCounter & 0xFFFFFFFF);
        if (workRequested == std::numeric_limits<std::uint32_t>::max()) {
            return { std::numeric_limits<std::size_t>::max(), static_cast<std::size_t>(workDone) };
        }
        return { static_cast<std::size_t>(workRequested), static_cast<std::size_t>(workDone) };
    }
};

enum class Status {
    ERROR                     = -100, /// error occurred in the work function
    INSUFFICIENT_OUTPUT_ITEMS = -3,   /// work requires a larger output buffer to produce output
    INSUFFICIENT_INPUT_ITEMS  = -2,   /// work requires a larger input buffer to produce output
    DONE                      = -1,   /// this block has completed its processing and the flowgraph should be done
    OK                        = 0,    /// work call was successful and return values in i/o structs are valid
};

struct Result {
    std::size_t requested_work = std::numeric_limits<std::size_t>::max();
    std::size_t performed_work = 0;
    Status      status         = Status::OK;
};
} // namespace work

template<typename T>
concept HasWork = requires(T t, std::size_t requested_work) {
    { t.work(requested_work) } -> std::same_as<work::Result>;
};

template<typename T>
concept BlockLike = requires(T t, std::size_t requested_work) {
    { t.unique_name } -> std::same_as<const std::string &>;
    { unwrap_if_wrapped_t<decltype(t.name)>{} } -> std::same_as<std::string>;
    { unwrap_if_wrapped_t<decltype(t.meta_information)>{} } -> std::same_as<property_map>;
    { t.description } noexcept -> std::same_as<const std::string_view &>;

    { t.isBlocking() } noexcept -> std::same_as<bool>;

    { t.settings() } -> std::same_as<SettingsBase &>;

    // N.B. TODO discuss these requirements
    requires !std::is_copy_constructible_v<T>;
    requires !std::is_copy_assignable_v<T>;
} && HasWork<T>;

template<typename Derived>
concept HasProcessOneFunction = traits::block::can_processOne<Derived>;

template<typename Derived>
concept HasConstProcessOneFunction = traits::block::can_processOne<Derived> && gr::meta::is_const_member_function(&Derived::processOne);

template<typename Derived>
concept HasProcessBulkFunction = traits::block::can_processBulk<Derived>;

template<typename Derived>
concept HasRequiredProcessFunction = (HasProcessBulkFunction<Derived> or HasProcessOneFunction<Derived>) and(HasProcessOneFunction<Derived> + HasProcessBulkFunction<Derived>) == 1;

template<typename TBlock, typename TDecayedBlock = std::remove_cvref_t<TBlock>>
inline void
checkBlockContracts();

template<typename T>
struct isBlockDependent {
    static constexpr bool value = PortLike<T> || BlockLike<T>;
};

namespace block::property {
inline static const char *kHeartbeat      = "Heartbeat";      ///< heartbeat property - the canary in the coal mine (supports block-specific subscribe/unsubscribe)
inline static const char *kEcho           = "Echo";           ///< basic property that receives any matching message and sends a mirror with it's serviceName/unique_name
inline static const char *kLifeCycleState = "LifecycleState"; ///< basic property that sets the block's @see lifecycle::StateMachine
inline static const char *kSetting        = "Settings";       ///< asynchronous message-based setting handling,
                                                              // N.B. 'Set' Settings are first staged before being applied within the work(...) function (real-time/non-real-time decoupling)
inline static const char *kStagedSetting = "StagedSettings";  ///< asynchronous message-based staging of settings

inline static const char *kStoreDefaults = "StoreDefaults"; ///< store present settings as default, for counterpart @see kResetDefaults
inline static const char *kResetDefaults = "ResetDefaults"; ///< retrieve and reset to default setting, for counterpart @see kStoreDefaults
} // namespace block::property

/**
 * @brief The 'Block<Derived>' is a base class for blocks that perform specific signal processing operations. It stores
 * references to its input and output 'ports' that can be zero, one, or many, depending on the use case.
 * As the base class for all user-defined blocks, it implements common convenience functions and a default public API
 * through the Curiously-Recurring-Template-Pattern (CRTP). For example:
 * @code
 * struct user_defined_block : Block<user_defined_block> {
 *   IN<float> in;
 *   OUT<float> out;
 *   // implement one of the possible work or abstracted functions
 * };
 * ENABLE_REFLECTION(user_defined_block, in, out);
 * @endcode
 * The macro `ENABLE_REFLECTION` since it relies on a template specialisation needs to be declared on the global scope.
 *
 * As an alternative definition that does not require the 'ENABLE_REFLECTION' macro and that also supports arbitrary
 * types for input 'T' and for the return 'R':
 * @code
 * template<typename T, typename R>
 * struct user_defined_block : Block<user_defined_block, IN<T, 0, N_MAX, "in">, OUT<R, 0, N_MAX, "out">> {
 *   // implement one of the possible work or abstracted functions
 * };
 * @endcode
 * This implementation provides efficient compile-time static polymorphism (i.e. access to the ports, settings, etc. does
 * not require virtual functions or inheritance, which can have performance penalties in high-performance computing contexts).
 * Note: The template parameter '<Derived>' can be dropped once C++23's 'deducing this' is widely supported by compilers.
 *
 * The 'Block<Derived>' implementation provides simple defaults for users who want to focus on generic signal-processing
 * algorithms and don't need full flexibility (and complexity) of using the generic `work_return_t work() {...}`.
 * The following defaults are defined for one of the two 'user_defined_block' block definitions (WIP):
 * <ul>
 * <li> <b>case 1a</b> - non-decimating N-in->N-out mechanic and automatic handling of streaming tags and settings changes:
 * @code
 *  gr::IN<T> in;
 *  gr::OUT<R> out;
 *  T _factor = T{1.0};
 *
 *  [[nodiscard]] constexpr auto processOne(T a) const noexcept {
 *      return static_cast<R>(a * _factor);
 *  }
 * @endcode
 * The number, type, and ordering of input and arguments of `processOne(..)` are defined by the port definitions.
 * <li> <b>case 1b</b> - non-decimating N-in->N-out mechanic providing bulk access to the input/output data and automatic
 * handling of streaming tags and settings changes:
 * @code
 *  [[nodiscard]] constexpr auto processBulk(std::span<const T> input, std::span<R> output) const noexcept {
 *      std::ranges::copy(input, output | std::views::transform([a = this->_factor](T x) { return static_cast<R>(x * a); }));
 *  }
 * @endcode
 * <li> <b>case 2a</b>: N-in->M-out -> processBulk(<ins...>, <outs...>) N,M fixed -> aka. interpolator (M>N) or decimator (M<N) (to-be-done)
 * <li> <b>case 2b</b>: N-in->M-out -> processBulk(<{ins,tag-IO}...>, <{outs,tag-IO}...>) user-level tag handling (to-be-done)
 * <li> <b>case 3</b> -- generic `work()` providing full access/logic capable of handling any N-in->M-out tag-handling case:
 * @code
 * [[nodiscard]] constexpr work_return_t work() const noexcept {
 *     auto &out_port = outputPort<"out">(this);
 *     auto &in_port = inputPort<"in">(this);
 *
 *     auto &reader = in_port.streamReader();
 *     auto &writer = out_port.streamWriter();
 *     const auto n_readable = std::min(reader.available(), in_port.max_buffer_size());
 *     const auto n_writable = std::min(writer.available(), out_port.max_buffer_size());
 *     if (n_readable == 0) {
 *         return { 0, gr::work::Status::INSUFFICIENT_INPUT_ITEMS };
 *     } else if (n_writable == 0) {
 *         return { 0, gr::work::Status::INSUFFICIENT_OUTPUT_ITEMS };
 *     }
 *     const std::size_t n_to_publish = std::min(n_readable, n_writable); // N.B. here enforcing N_input == N_output
 *
 *     writer.publish([&reader, n_to_publish, this](std::span<T> output) {
 *         const auto input = reader.get(n_to_publish);
 *         for (; i < n_to_publish; i++) {
 *             output[i] = input[i] * value;
 *         }
 *     }, n_to_publish);
 *
 *     if (!reader.consume(n_to_publish)) {
 *         return { n_to_publish, gr::work::Status::ERROR };
 *     }
 *     return { n_to_publish, gr::work::Status::OK };
 * }
 * @endcode
 * <li> <b>case 4</b>:  Python -> map to cases 1-3 and/or dedicated callback (to-be-implemented)
 * <li> <b>special cases<b>: (to-be-implemented)
 *     * case sources: HW triggered vs. generating data per invocation (generators via Port::MIN)
 *     * case sinks: HW triggered vs. fixed-size consumer (may block/never finish for insufficient input data and fixed Port::MIN>0)
 * <ul>
 *
 * In addition derived classes can optionally implement any subset of the lifecycle methods ( `start()`, `stop()`, `reset()`, `pause()`, `resume()`).
 * The Scheduler invokes these methods on each Block instance, if they are implemented, just before invoking its corresponding method of the same name.
 * @code
 * struct userBlock : public Block<userBlock> {
 * void start() {...} // Implement any startup logic required for the block within this method.
 * void stop() {...} // Use this method for handling any clean-up procedures.
 * void pause() {...} // Implement logic to temporarily halt the block's operation, maintaining its current state.
 * void resume() {...} // This method should contain logic to restart operations after a pause, continuing from the same state as when it was paused.
 * void reset() {...} // Reset the block's state to defaults in this method.
 * };
 * @endcode
 *
 * Properties System:
 * Properties offer a standardized way to manage runtime configuration and state. This system is built upon a message-passing model, allowing blocks
 * to dynamically adjust their behavior, respond to queries, and notify about state changes. Defined under the `block::property` namespace,
 * these properties leverage the Majordomo Protocol (MDP) pattern for structured and efficient communication.
 *
 * Predefined properties include:
 * - `kHeartbeat`: Monitors and reports the block's operational state.
 * - `kEcho`: Responds to messages by echoing them back, aiding in communication testing.
 * - `kLifeCycleState`: Manages and reports the block's lifecycle state.
 * - `kSetting` & `kStagedSetting`: Handle real-time and non-real-time configuration adjustments.
 * - `kStoreDefaults` & `kResetDefaults`: Facilitate storing and reverting to default settings.
 *
 * These properties can be interacted with through messages, supporting operations like setting values, querying states, and subscribing to updates.
 * This model provides a flexible interface for blocks to adapt their processing based on runtime conditions and external inputs.
 *
 * Implementing a Property:
 * Blocks can implement custom properties by registering them in the `propertyCallbacks` map within the `start()` method.
 * This allows the block to handle `SET`, `GET`, `SUBSCRIBE`, and `UNSUBSCRIBE` commands targeted at the property, enabling dynamic interaction with the block's functionality and configuration.
 *
 * @code
 * struct MyBlock : public Block<MyBlock> {
 *     static inline const char* kMyCustomProperty = "MyCustomProperty";
 *     std::optional<Message> propertyCallbackMyCustom(std::string_view propertyName, Message message) {
 *         using enum gr::message::Command;
 *         assert(kMyCustomProperty  == propertyName); // internal check that the property-name to callback is correct
 *
 *         switch (message.cmd) {
 *           case Set: // handle property setting
 *             break;
 *           case Get: // handle property querying
 *             return Message{ populate reply message };
 *           case Subscribe: // handle subscription
 *             break;
 *           case Unsubscribe: // handle unsubscription
 *             break;
 *           default: throw gr::exception(fmt::format("unsupported command {} for property {}", message.cmd, propertyName));
 *         }
 *       return std::nullopt; // no reply needed for Set, Subscribe, Unsubscribe
 *     }
 *
 *     void start() override {
 *         propertyCallbacks.emplace(kMyCustomProperty, &MyBlock::propertyCallbackMyCustom);
 *     }
 * };
 * @endcode
 *
 * @tparam Derived the user-defined block CRTP: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
 * @tparam Arguments NTTP list containing the compile-time defined port instances, setting structs, or other constraints.
 */
template<typename Derived, typename... Arguments>
class Block : public lifecycle::StateMachine<Derived>, //
              protected std::tuple<Arguments...>       // all arguments -> may cause code binary size bloat
//              protected std::tuple<typename gr::meta::typelist<Arguments...>::template filter<gr::isBlockDependent>> // only add port types to the tuple, the other info are kept in the using
//              statements below
{
    static std::atomic_size_t _uniqueIdCounter;
    template<typename T, gr::meta::fixed_string description = "", typename... Args>
    using A = Annotated<T, description, Args...>;

public:
    using base_t                     = Block<Derived, Arguments...>;
    using derived_t                  = Derived;
    using ArgumentsTypeList          = typename gr::meta::typelist<Arguments...>;
    using block_template_parameters  = meta::typelist<Arguments...>;
    using Resampling                 = ArgumentsTypeList::template find_or_default<is_resampling_ratio, ResamplingRatio<1UL, 1UL, true>>;
    using StrideControl              = ArgumentsTypeList::template find_or_default<is_stride, Stride<0UL, true>>;
    using AllowIncompleteFinalUpdate = ArgumentsTypeList::template find_or_default<is_incompleteFinalUpdatePolicy, IncompleteFinalUpdatePolicy<IncompleteFinalUpdateEnum::DROP>>;
    using DrawableControl            = ArgumentsTypeList::template find_or_default<is_drawable, Drawable<UICategory::None, "">>;
    constexpr static bool blockingIO = std::disjunction_v<std::is_same<BlockingIO<true>, Arguments>...> || std::disjunction_v<std::is_same<BlockingIO<false>, Arguments>...>;

    template<typename T>
    auto &
    getArgument() {
        return std::get<T>(*this);
    }

    template<typename T>
    const auto &
    getArgument() const {
        return std::get<T>(*this);
    }

    // TODO: These are not involved in move operations, might be a problem later
    alignas(hardware_destructive_interference_size) std::atomic<std::size_t> ioRequestedWork{ std::numeric_limits<std::size_t>::max() };
    alignas(hardware_destructive_interference_size) work::Counter ioWorkDone{};
    alignas(hardware_destructive_interference_size) std::atomic<work::Status> ioLastWorkStatus{ work::Status::OK };
    alignas(hardware_destructive_interference_size) std::shared_ptr<gr::Sequence> progress                         = std::make_shared<gr::Sequence>();
    alignas(hardware_destructive_interference_size) std::shared_ptr<gr::thread_pool::BasicThreadPool> ioThreadPool = std::make_shared<gr::thread_pool::BasicThreadPool>(
            "block_thread_pool", gr::thread_pool::TaskType::IO_BOUND, 2UZ, std::numeric_limits<uint32_t>::max());
    alignas(hardware_destructive_interference_size) std::atomic<bool> ioThreadRunning{ false };

    constexpr static TagPropagationPolicy tag_policy = TagPropagationPolicy::TPP_ALL_TO_ALL;

    using RatioValue = std::conditional_t<Resampling::kIsConst, const gr::Size_t, gr::Size_t>;
    A<RatioValue, "numerator", Doc<"Top of resampling ratio (<1: Decimate, >1: Interpolate, =1: No change)">, Limits<1UL, std::numeric_limits<RatioValue>::max()>> numerator = Resampling::kNumerator;
    A<RatioValue, "denominator", Doc<"Bottom of resampling ratio (<1: Decimate, >1: Interpolate, =1: No change)">, Limits<1UL, std::numeric_limits<RatioValue>::max()>> denominator
            = Resampling::kDenominator;
    using StrideValue = std::conditional_t<StrideControl::kIsConst, const gr::Size_t, gr::Size_t>;
    A<StrideValue, "stride", Doc<"samples between data processing. <N for overlap, >N for skip, =0 for back-to-back.">> stride = StrideControl::kStride;

    gr::Size_t strideCounter = 0UL; // leftover stride from previous calls

    // TODO: These are not involved in move operations, might be a problem later
    const std::size_t unique_id   = _uniqueIdCounter++;
    const std::string unique_name = fmt::format("{}#{}", gr::meta::type_name<Derived>(), unique_id);

    //
    A<std::string, "user-defined name", Doc<"N.B. may not be unique -> ::unique_name">> name = gr::meta::type_name<Derived>();
    //
    constexpr static std::string_view description = [] {
        if constexpr (requires { typename Derived::Description; }) {
            return static_cast<std::string_view>(Derived::Description::value);
        } else {
            return "please add a public 'using Description = Doc<\"...\">' documentation annotation to your block definition";
        }
    }();
    static_assert(std::atomic<lifecycle::State>::is_always_lock_free, "std::atomic<lifecycle::State> is not lock-free");

    //
    static property_map
    initMetaInfo() {
        using namespace std::string_literals;
        property_map ret;
        if constexpr (!std::is_same_v<NotDrawable, DrawableControl>) {
            property_map info;
            info.insert_or_assign("Category"s, std::string(magic_enum::enum_name(DrawableControl::kCategorgy)));
            info.insert_or_assign("Toolkit"s, std::string(DrawableControl::kToolkit));

            ret.insert_or_assign("Drawable"s, info);
        }
        return ret;
    }

    A<property_map, "meta-information", Doc<"store non-graph-processing information like UI block position etc.">> meta_information = initMetaInfo();

    // TODO: C++26 make sure these are not reflected
    // We support ports that are template parameters or reflected member variables,
    // so these are handled in a special way
    MsgPortInNamed<"__Builtin">  msgIn;
    MsgPortOutNamed<"__Builtin"> msgOut;

    using PropertyCallback = std::optional<Message> (Derived::*)(std::string_view, Message);
    std::map<std::string, PropertyCallback>         propertyCallbacks{
                { block::property::kHeartbeat, &Block::propertyCallbackHeartbeat },           //
                { block::property::kEcho, &Block::propertyCallbackEcho },                     //
                { block::property::kLifeCycleState, &Block::propertyCallbackLifecycleState }, //
                { block::property::kSetting, &Block::propertyCallbackSettings },              //
                { block::property::kStagedSetting, &Block::propertyCallbackStagedSettings },  //
                { block::property::kStoreDefaults, &Block::propertyCallbackStoreDefaults },   //
                { block::property::kResetDefaults, &Block::propertyCallbackResetDefaults },   //
    };
    std::map<std::string, std::set<std::string>> propertySubscriptions;

protected:
    bool _outputTagsChanged = false;
    Tag  _mergedInputTag{};

    // intermediate non-real-time<->real-time setting states
    std::unique_ptr<SettingsBase> _settings = std::make_unique<BasicSettings<Derived>>(self());

    [[nodiscard]] constexpr auto &
    self() noexcept {
        return *static_cast<Derived *>(this);
    }

    [[nodiscard]] constexpr const auto &
    self() const noexcept {
        return *static_cast<const Derived *>(this);
    }

public:
    Block() noexcept(false) : Block({}) {} // N.B. throws in case of on contract violations

    Block(std::initializer_list<std::pair<const std::string, pmtv::pmt>> init_parameter) noexcept(false) // N.B. throws in case of on contract violations
        : _settings(std::make_unique<BasicSettings<Derived>>(*static_cast<Derived *>(this))) {           // N.B. safe delegated use of this (i.e. not used during construction)

        // check Block<T> contracts
        checkBlockContracts<decltype(*static_cast<Derived *>(this))>();

        if (init_parameter.size() != 0) {
            const auto failed = settings().set(init_parameter);
            if (!failed.empty()) {
                throw std::invalid_argument("Settings not applied successfully");
            }
        }
    }

    Block(Block &&other) noexcept
        : lifecycle::StateMachine<Derived>(std::move(other))
        , std::tuple<Arguments...>(std::move(other))
        , numerator(std::move(other.numerator))
        , denominator(std::move(other.denominator))
        , stride(std::move(other.stride))
        , strideCounter(std::move(other.strideCounter))
        , msgIn(std::move(other.msgIn))
        , msgOut(std::move(other.msgOut))
        , _outputTagsChanged(std::move(other._outputTagsChanged))
        , _mergedInputTag(std::move(other._mergedInputTag))
        , _settings(std::move(other._settings)) {}

    // There are a few const or conditionally const member variables,
    // we can not have a move-assignment that is equivalent to
    // the move constructor
    Block &
    operator=(Block &&other)
            = delete;

    ~Block() { // NOSONAR -- need to request the (potentially) running ioThread to stop
        if (lifecycle::isActive(this->state())) {
            if (auto e = this->changeStateTo(lifecycle::State::REQUESTED_STOP); !e) {
                emitErrorMessage("~Block()", e.error());
            }
        }
        if (isBlocking()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        // wait for done
        for (auto actualState = this->state(); lifecycle::isActive(actualState); actualState = this->state()) {
            this->waitOnState(actualState);
        }

        if (auto e = this->changeStateTo(lifecycle::State::STOPPED); !e) {
            emitErrorMessage("~Block()", e.error());
        }
    }

    void
    init(std::shared_ptr<gr::Sequence> progress_, std::shared_ptr<gr::thread_pool::BasicThreadPool> ioThreadPool_) {
        progress     = std::move(progress_);
        ioThreadPool = std::move(ioThreadPool_);

        // Set names of port member variables
        // TODO: Refactor the library not to assign names to ports. The
        // block and the graph are the only things that need the port name
        auto setPortName = [&]([[maybe_unused]] std::size_t index, auto &&t) {
            using CurrentPortType = std::remove_cvref_t<decltype(t)>;
            if constexpr (traits::port::is_port_v<CurrentPortType>) {
                using PortDescriptor = typename CurrentPortType::ReflDescriptor;
                if constexpr (refl::trait::is_descriptor_v<PortDescriptor>) {
                    auto &port = (self().*(PortDescriptor::pointer));
                    port.name  = CurrentPortType::Name;
                }
            } else {
                using PortCollectionDescriptor = typename CurrentPortType::value_type::ReflDescriptor;
                if constexpr (refl::trait::is_descriptor_v<PortCollectionDescriptor>) {
                    auto       &collection     = (self().*(PortCollectionDescriptor::pointer));
                    std::string collectionName = refl::descriptor::get_name(PortCollectionDescriptor()).data;
                    for (auto &port : collection) {
                        port.name = collectionName;
                    }
                }
            }
        };
        traits::block::all_input_ports<Derived>::for_each(setPortName);
        traits::block::all_output_ports<Derived>::for_each(setPortName);

        // Handle settings
        // important: these tags need to be queued because at this stage the block is not yet connected to other downstream blocks
        if (const auto applyResult = settings().applyStagedParameters(); !applyResult.forwardParameters.empty()) {
            if constexpr (Derived::tag_policy == TagPropagationPolicy::TPP_ALL_TO_ALL) {
                publishTag(applyResult.forwardParameters);
            }
            notifyListeners(block::property::kSetting, settings().get());
        }
        checkParametersAndThrowIfNeeded();

        // store default settings -> can be recovered with 'resetDefaults()'
        settings().storeDefaults();
        if (auto e = this->changeStateTo(lifecycle::State::INITIALISED); !e) {
            emitErrorMessage("init(..) -> INITIALISED", e.error());
        }
    }

    template<gr::meta::array_or_vector_type Container>
    [[nodiscard]] constexpr std::size_t
    availableInputSamples(Container &data) const noexcept {
        if constexpr (gr::meta::vector_type<Container>) {
            data.resize(traits::block::stream_input_port_types<Derived>::size);
        } else if constexpr (gr::meta::array_type<Container>) {
            static_assert(std::tuple_size<Container>::value >= traits::block::stream_input_port_types<Derived>::size);
        } else {
            static_assert(gr::meta::always_false<Container>, "type not supported");
        }
        meta::tuple_for_each_enumerate(
                [&data]<typename Port>(auto index, Port &input_port) {
                    if constexpr (traits::port::is_port_v<Port>) {
                        data[index] = input_port.streamReader().available();
                    } else {
                        data[index] = 0;
                        for (auto &port : input_port) {
                            data[index] += port.streamReader().available();
                        }
                    }
                },
                inputPorts<PortType::STREAM>(&self()));
        return traits::block::stream_input_port_types<Derived>::size;
    }

    template<gr::meta::array_or_vector_type Container>
    [[nodiscard]] constexpr std::size_t
    availableOutputSamples(Container &data) const noexcept {
        if constexpr (gr::meta::vector_type<Container>) {
            data.resize(traits::block::stream_output_port_types<Derived>::size);
        } else if constexpr (gr::meta::array_type<Container>) {
            static_assert(std::tuple_size<Container>::value >= traits::block::stream_output_port_types<Derived>::size);
        } else {
            static_assert(gr::meta::always_false<Container>, "type not supported");
        }
        meta::tuple_for_each_enumerate(
                [&data]<typename Port>(auto index, Port &output_port) {
                    if constexpr (traits::port::is_port_v<Port>) {
                        data[index] = output_port.streamWriter().available();
                    } else {
                        data[index] = 0;
                        for (auto &port : output_port) {
                            data[index] += port.streamWriter().available();
                        }
                    }
                },
                outputPorts<PortType::STREAM>(&self()));
        return traits::block::stream_output_port_types<Derived>::size;
    }

    [[nodiscard]] constexpr bool
    isBlocking() const noexcept {
        return blockingIO;
    }

    [[nodiscard]] constexpr bool
    input_tags_present() const noexcept {
        return !_mergedInputTag.map.empty();
    };

    [[nodiscard]] Tag
    mergedInputTag() const noexcept {
        return _mergedInputTag;
    }

    [[nodiscard]] constexpr SettingsBase &
    settings() const noexcept {
        return *_settings;
    }

    [[nodiscard]] constexpr SettingsBase &
    settings() noexcept {
        return *_settings;
    }

    template<typename T>
    void
    setSettings(std::unique_ptr<T> &settings) {
        _settings = std::move(settings);
    }

    template<std::size_t Index, typename Self>
    friend constexpr auto &
    inputPort(Self *self) noexcept;

    template<std::size_t Index, typename Self>
    friend constexpr auto &
    outputPort(Self *self) noexcept;

    template<fixed_string Name, typename Self>
    friend constexpr auto &
    inputPort(Self *self) noexcept;

    template<fixed_string Name, typename Self>
    friend constexpr auto &
    outputPort(Self *self) noexcept;

    constexpr void
    checkParametersAndThrowIfNeeded() {
        constexpr bool kIsSourceBlock = traits::block::stream_input_port_types<Derived>::size == 0;
        constexpr bool kIsSinkBlock   = traits::block::stream_output_port_types<Derived>::size == 0;

        if constexpr (Resampling::kEnabled) {
            static_assert(!kIsSinkBlock, "Decimation/interpolation is not available for sink blocks. Remove 'ResamplingRatio<>' from the block definition.");
            static_assert(!kIsSourceBlock, "Decimation/interpolation is not available for source blocks. Remove 'ResamplingRatio<>' from the block definition.");
            static_assert(HasProcessBulkFunction<Derived>, "Blocks which allow decimation/interpolation must implement processBulk(...) method. Remove 'ResamplingRatio<>' from the block definition.");
        } else {
            if (numerator != 1ULL || denominator != 1ULL) {
                auto e = gr::Error(fmt::format("Block is not defined as `ResamplingRatio<>`, but numerator = {}, denominator = {}, they both must equal to 1.", numerator, denominator));
                emitErrorMessage("Block::checkParametersAndThrowIfNeeded:", e);
                requestStop();
                return;
            }
        }

        if constexpr (StrideControl::kEnabled) {
            static_assert(!kIsSourceBlock, "Stride is not available for source blocks. Remove 'Stride<>' from the block definition.");
        } else {
            if (stride != 0ULL) {
                auto e = gr::Error(fmt::format("Block is not defined as `Stride<>`, but stride = {}, it must equal to 0.", stride));
                emitErrorMessage("Block::checkParametersAndThrowIfNeeded:", e);
                requestStop();
                return;
            }
        }

        const auto [minSyncIn, maxSyncIn, _, _1]    = getPortLimits(inputPorts<PortType::STREAM>(&self()));
        const auto [minSyncOut, maxSyncOut, _2, _3] = getPortLimits(outputPorts<PortType::STREAM>(&self()));
        if (minSyncIn > maxSyncIn) {
            auto e = gr::Error(fmt::format("Min samples for input ports ({}) is larger then max samples for input ports ({})", minSyncIn, maxSyncIn));
            emitErrorMessage("Block::checkParametersAndThrowIfNeeded:", e);
            requestStop();
            return;
        }
        if (minSyncOut > maxSyncOut) {
            auto e = gr::Error(fmt::format("Min samples for output ports ({}) is larger then max samples for output ports ({})", minSyncOut, maxSyncOut));
            emitErrorMessage("Block::checkParametersAndThrowIfNeeded:", e);
            requestStop();
            return;
        }
        if (denominator > maxSyncIn) {
            auto e = gr::Error(fmt::format("resampling denominator ({}) is larger then max samples for input ports ({})", denominator, maxSyncIn));
            emitErrorMessage("Block::checkParametersAndThrowIfNeeded:", e);
            requestStop();
            return;
        }
        if (numerator > maxSyncOut) {
            auto e = gr::Error(fmt::format("resampling numerator ({}) is larger then max samples for output ports ({})", numerator, maxSyncOut));
            emitErrorMessage("Block::checkParametersAndThrowIfNeeded:", e);
            requestStop();
            return;
        }
    }

    void
    publishSamples(std::size_t nSamples, auto &publishableSpanTuple) noexcept {
        if constexpr (traits::block::stream_output_ports<Derived>::size > 0) {
            meta::tuple_for_each_enumerate(
                    [nSamples]<typename OutputRange>(auto, OutputRange &outputRange) {
                        auto processOneRange = [nSamples]<typename Out>(Out &out) {
                            if constexpr (Out::isMultiThreadedStrategy()) {
                                if (!out.isFullyPublished()) {
                                    fmt::print(stderr, "Block::publishSamples - did not publish all samples for MultiThreadedStrategy\n");
                                    std::abort();
                                }
                            }
                            if (!out.isPublished()) {
                                using enum gr::SpanReleasePolicy;
                                if constexpr (Out::spanReleasePolicy() == Terminate) {
                                    fmt::print(stderr, "Block::publishSamples - samples were not published, default SpanReleasePolicy is {}\n", magic_enum::enum_name(Terminate));
                                    std::abort();
                                } else if constexpr (Out::spanReleasePolicy() == ProcessAll) {
                                    out.publish(nSamples);
                                } else if constexpr (Out::spanReleasePolicy() == ProcessNone) {
                                    out.publish(0U);
                                }
                            }
                        };
                        if constexpr (refl::trait::is_instance_of_v<std::vector, std::remove_cvref_t<OutputRange>>) {
                            for (auto &out : outputRange) {
                                processOneRange(out);
                            }
                        } else {
                            processOneRange(outputRange);
                        }
                    },
                    publishableSpanTuple);
        }
    }

    bool
    consumeReaders(std::size_t nSamples, auto &consumableSpanTuple) {
        bool success = true;
        if constexpr (traits::block::stream_input_ports<Derived>::size > 0) {
            meta::tuple_for_each_enumerate(
                    [nSamples, &success]<typename InputRange>(auto, InputRange &inputRange) {
                        auto processOneRange = [nSamples, &success]<typename In>(In &in) {
                            if (!in.isConsumed()) {
                                using enum gr::SpanReleasePolicy;
                                if constexpr (In::spanReleasePolicy() == Terminate) {
                                    fmt::print(stderr, "Block::consumeReaders - samples were not consumed, default SpanReleasePolicy is {}\n", magic_enum::enum_name(Terminate));
                                    std::abort();
                                } else if constexpr (In::spanReleasePolicy() == ProcessAll) {
                                    success = success && in.consume(nSamples);
                                } else if constexpr (In::spanReleasePolicy() == ProcessNone) {
                                    success = success && in.consume(0U);
                                }
                            }
                        };
                        if constexpr (refl::trait::is_instance_of_v<std::vector, std::remove_cvref_t<InputRange>>) {
                            for (auto &in : inputRange) {
                                processOneRange(in);
                            }
                        } else {
                            processOneRange(inputRange);
                        }
                    },
                    consumableSpanTuple);
        }
        return success;
    }

    template<typename... Ts>
    constexpr auto
    invoke_processOne(std::size_t offset, Ts &&...inputs) {
        if constexpr (traits::block::stream_output_ports<Derived>::size == 0) {
            invokeProcessOneWithOrWithoutOffset(self(), offset, std::forward<Ts>(inputs)...);
            return std::tuple{};
        } else if constexpr (traits::block::stream_output_ports<Derived>::size == 1) {
            return std::tuple{ invokeProcessOneWithOrWithoutOffset(self(), offset, std::forward<Ts>(inputs)...) };
        } else {
            return invokeProcessOneWithOrWithoutOffset(self(), offset, std::forward<Ts>(inputs)...);
        }
    }

    template<typename... Ts>
    constexpr auto
    invoke_processOne_simd(std::size_t offset, auto width, Ts &&...input_simds) {
        if constexpr (sizeof...(Ts) == 0) {
            if constexpr (traits::block::stream_output_ports<Derived>::size == 0) {
                self().processOne_simd(offset, width);
                return std::tuple{};
            } else if constexpr (traits::block::stream_output_ports<Derived>::size == 1) {
                return std::tuple{ self().processOne_simd(offset, width) };
            } else {
                return self().processOne_simd(offset, width);
            }
        } else {
            return invoke_processOne(offset, std::forward<Ts>(input_simds)...);
        }
    }

    constexpr void
    forwardTags() noexcept {
        if (input_tags_present()) {
            // clear temporary cached input tags after processing - won't be needed after this
            _mergedInputTag.map.clear();
        }

        for_each_port([](PortLike auto &outPort) noexcept { outPort.publishPendingTags(); }, outputPorts<PortType::STREAM>(&self()));
        _outputTagsChanged = false;
    }

    /**
     * Collects tags from each input port, merges them into a single map, applies settings and if requested propagates
     * them to the output ports.
     * @param untilOffset defaults to 0, if bigger merges all tags from samples 0...untilOffset for each port before merging
     *                    them
     */
    constexpr void
    updateInputAndOutputTags(std::size_t untilOffset = 0) noexcept {
        for_each_port(
                [untilOffset, this]<typename Port>(Port &input_port) noexcept {
                    auto mergeSrcMapInto = [](const property_map &sourceMap, property_map &destinationMap) {
                        assert(&sourceMap != &destinationMap);
                        for (const auto &[key, value] : sourceMap) {
                            destinationMap.insert_or_assign(key, value);
                        }
                    };

                    const Tag mergedPortTags = input_port.getTag(static_cast<gr::Tag::signed_index_type>(untilOffset));
                    mergeSrcMapInto(mergedPortTags.map, _mergedInputTag.map);
                },
                inputPorts<PortType::STREAM>(&self()));

        if (!mergedInputTag().map.empty()) {
            settings().autoUpdate(mergedInputTag().map); // apply tags as new settings if matching
            if constexpr (Derived::tag_policy == TagPropagationPolicy::TPP_ALL_TO_ALL) {
                for_each_port([this](PortLike auto &outPort) noexcept { outPort.publishTag(mergedInputTag().map, 0); }, outputPorts<PortType::STREAM>(&self()));
            }
            if (mergedInputTag().map.contains(gr::tag::END_OF_STREAM)) {
                requestStop();
            }
        }
    }

    void
    applyChangedSettings() {
        if (settings().changed()) {
            auto applyResult = settings().applyStagedParameters();
            checkParametersAndThrowIfNeeded();

            if (!applyResult.forwardParameters.empty()) {
                publishTag(applyResult.forwardParameters, 0);
            }

            settings()._changed.store(false);

            if (!applyResult.appliedParameters.empty()) {
                notifyListeners(block::property::kStagedSetting, applyResult.appliedParameters);
            }
            notifyListeners(block::property::kSetting, settings().get());
        }
    }

    constexpr static auto
    prepareStreams(auto ports, std::size_t sync_samples) {
        return meta::tuple_transform(
                [sync_samples]<typename PortOrCollection>(PortOrCollection &output_port_or_collection) noexcept {
                    auto process_single_port = [&sync_samples]<typename Port>(Port &&port) {
                        using enum gr::SpanReleasePolicy;
                        if constexpr (std::remove_cvref_t<Port>::kIsSynch) {
                            if constexpr (std::remove_cvref_t<Port>::kIsInput) {
                                return std::forward<Port>(port).streamReader().template get<ProcessAll>(sync_samples);
                            } else if constexpr (std::remove_cvref_t<Port>::kIsOutput) {
                                return std::forward<Port>(port).streamWriter().template reserve<ProcessAll>(sync_samples);
                            }
                        } else {
                            // for the Async port get/reserve all available samples
                            if constexpr (std::remove_cvref_t<Port>::kIsInput) {
                                return std::forward<Port>(port).streamReader().template get<ProcessNone>(port.streamReader().available());
                            } else if constexpr (std::remove_cvref_t<Port>::kIsOutput) {
                                return std::forward<Port>(port).streamWriter().template reserve<ProcessNone>(port.streamWriter().available());
                            }
                        }
                    };
                    if constexpr (traits::port::is_port_v<PortOrCollection>) {
                        return process_single_port(output_port_or_collection);
                    } else {
                        using value_span = decltype(process_single_port(std::declval<typename PortOrCollection::value_type>()));
                        std::vector<value_span> result{};
                        std::transform(output_port_or_collection.begin(), output_port_or_collection.end(), std::back_inserter(result), process_single_port);
                        return result;
                    }
                },
                ports);
    }

    inline constexpr void
    publishTag(property_map &&tag_data, Tag::signed_index_type tagOffset = -1) noexcept {
        for_each_port([tag_data = std::move(tag_data), tagOffset](PortLike auto &outPort) { outPort.publishTag(tag_data, tagOffset); }, outputPorts<PortType::STREAM>(&self()));
    }

    inline constexpr void
    publishTag(const property_map &tag_data, Tag::signed_index_type tagOffset = -1) noexcept {
        for_each_port([&tag_data, tagOffset](PortLike auto &outPort) { outPort.publishTag(tag_data, tagOffset); }, outputPorts<PortType::STREAM>(&self()));
    }

    constexpr void
    requestStop() noexcept {
        if (auto e = this->changeStateTo(lifecycle::State::REQUESTED_STOP); !e) {
            emitErrorMessage("requestStop()", e.error());
        }
    }

    constexpr void
    processScheduledMessages() {
        using namespace std::chrono;
        const std::uint64_t nanoseconds_count = static_cast<uint64_t>(duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count());
        notifyListeners(block::property::kHeartbeat, { { "heartbeat", nanoseconds_count } });

        auto processPort = [this]<PortLike TPort>(TPort &inPort) {
            const auto available = inPort.streamReader().available();
            if (available == 0UZ) {
                return;
            }
            ConsumableSpan auto inSpan = inPort.streamReader().get(available);
            if constexpr (traits::block::can_processMessagesForPortConsumableSpan<Derived, TPort>) {
                self().processMessages(inPort, inSpan);
                // User could have consumed the span in the custom processMessages handler
                std::ignore = inSpan.tryConsume(inSpan.size());
            } else if constexpr (traits::block::can_processMessagesForPortStdSpan<Derived, TPort>) {
                self().processMessages(inPort, static_cast<std::span<const Message>>(inSpan));
                if (auto consumed = inSpan.tryConsume(inSpan.size()); !consumed) {
                    throw gr::exception(fmt::format("Block {}::processScheduledMessages() could not consume the messages from the message port", unique_name));
                }
            }
        };
        processPort(msgIn);
        for_each_port(processPort, inputPorts<PortType::MESSAGE>(&self()));
    }

protected:
    std::optional<Message>
    propertyCallbackHeartbeat(std::string_view propertyName, Message message) {
        using enum gr::message::Command;
        assert(propertyName == block::property::kHeartbeat);

        if (message.cmd == Set || message.cmd == Get) {
            std::uint64_t nanoseconds_count = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
            message.data                    = { { "heartbeat", nanoseconds_count } };
            return message;
        } else if (message.cmd == Subscribe) {
            if (!message.clientRequestID.empty()) {
                propertySubscriptions[std::string(propertyName)].insert(message.clientRequestID);
            }
            return std::nullopt;
        } else if (message.cmd == Unsubscribe) {
            propertySubscriptions[std::string(propertyName)].erase(message.clientRequestID);
            return std::nullopt;
        }

        throw gr::exception(fmt::format("block {} property {} does not implement command {}, msg: {}", unique_name, propertyName, message.cmd, message));
    }

    std::optional<Message>
    propertyCallbackEcho(std::string_view propertyName, Message message) {
        using enum gr::message::Command;
        assert(propertyName == block::property::kEcho);

        if (message.cmd == Set) {
            return message; // mirror message as is
        }

        throw gr::exception(fmt::format("block {} property {} does not implement command {}, msg: {}", unique_name, propertyName, message.cmd, message));
    }

    std::optional<Message>
    propertyCallbackLifecycleState(std::string_view propertyName, Message message) {
        using enum gr::message::Command;
        assert(propertyName == block::property::kLifeCycleState);

        if (message.cmd == Set) {
            if (!message.data.has_value() && !message.data.value().contains("state")) {
                throw gr::exception(fmt::format("block {} (aka. {}) cannot set block state w/o 'state' data msg: {}", unique_name, name, message));
            }

            std::string stateStr;
            try {
                stateStr = std::get<std::string>(message.data.value().at("state"));
            } catch (const std::exception &e) {
                throw gr::exception(fmt::format("block {} property {} state conversion throws {}, msg: {}", unique_name, propertyName, e.what(), message));
            } catch (...) {
                throw gr::exception(fmt::format("block {} property {} state conversion throws unknown exception, msg: {}", unique_name, propertyName, message));
            }
            auto state = magic_enum::enum_cast<lifecycle::State>(stateStr);
            if (!state.has_value()) {
                throw gr::exception(fmt::format("block {} property {} invalid lifecycle::State conversion from {}, msg: {}", unique_name, propertyName, stateStr, message));
            }
            if (auto e = this->changeStateTo(state.value()); !e) {
                throw gr::exception(fmt::format("error in state transition block {} property {} - what: {}", //
                                                unique_name, propertyName, e.error().message, e.error().sourceLocation, e.error().errorTime));
            }
            return std::nullopt;
        } else if (message.cmd == Get) {
            message.data = { { "state", std::string(magic_enum::enum_name(this->state())) } };
            return message;
        } else if (message.cmd == Subscribe) {
            if (!message.clientRequestID.empty()) {
                propertySubscriptions[std::string(propertyName)].insert(message.clientRequestID);
            }
            return std::nullopt;
        } else if (message.cmd == Unsubscribe) {
            propertySubscriptions[std::string(propertyName)].erase(message.clientRequestID);
            return std::nullopt;
        }

        throw gr::exception(fmt::format("block {} property {} does not implement command {}, msg: {}", unique_name, propertyName, message.cmd, message));
    }

    std::optional<Message>
    propertyCallbackSettings(std::string_view propertyName, Message message) {
        using enum gr::message::Command;
        assert(propertyName == block::property::kSetting);

        if (message.cmd == Set) {
            if (!message.data.has_value()) {
                throw gr::exception(fmt::format("block {} (aka. {}) cannot set {} w/o data msg: {}", unique_name, name, propertyName, message));
            }
            // delegate to 'propertyCallbackStagedSettings' since we cannot set but only stage new settings due to mandatory real-time/non-real-time decoupling
            // settings are applied during the next work(...) invocation.
            propertyCallbackStagedSettings(block::property::kStagedSetting, message);
            return std::nullopt;
        } else if (message.cmd == Get) {
            message.data = self().settings().get();
            return message;
        } else if (message.cmd == Subscribe) {
            if (!message.clientRequestID.empty()) {
                propertySubscriptions[std::string(propertyName)].insert(message.clientRequestID);
            }
            return std::nullopt;
        } else if (message.cmd == Unsubscribe) {
            propertySubscriptions[std::string(propertyName)].erase(message.clientRequestID);
            return std::nullopt;
        }

        throw gr::exception(fmt::format("block {} property {} does not implement command {}, msg: {}", unique_name, propertyName, message.cmd, message));
    }

    std::optional<Message>
    propertyCallbackStagedSettings(std::string_view propertyName, Message message) {
        using enum gr::message::Command;
        assert(propertyName == block::property::kStagedSetting);

        if (message.cmd == Set) {
            if (!message.data.has_value()) {
                throw gr::exception(fmt::format("block {} (aka. {}) cannot set {} w/o data msg: {}", unique_name, name, propertyName, message));
            }

            property_map stagedParameter = self().settings().stagedParameters();
            property_map notSet          = self().settings().set(*message.data);

            if (notSet.empty()) {
                if (!message.clientRequestID.empty()) {
                    message.cmd  = Final;
                    message.data = stagedParameter;
                    return message;
                }
                return std::nullopt;
            }

            const auto keys = [](const auto &map) { return fmt::join(map | std::views::transform([](const auto &pair) { return pair.first; }), ", "); };
            throw gr::exception(fmt::format("block {} (aka. {}) could not set fields: {}\nvs. available: {}", unique_name, name, keys(notSet), keys(settings().get())));
        } else if (message.cmd == Get) {
            message.data = self().settings().stagedParameters();
            return message;
        } else if (message.cmd == Subscribe) {
            if (!message.clientRequestID.empty()) {
                propertySubscriptions[std::string(propertyName)].insert(message.clientRequestID);
            }
            return std::nullopt;
        } else if (message.cmd == Unsubscribe) {
            propertySubscriptions[std::string(propertyName)].erase(message.clientRequestID);
            return std::nullopt;
        }

        throw gr::exception(fmt::format("block {} property {} does not implement command {}, msg: {}", unique_name, propertyName, message.cmd, message));
    }

    std::optional<Message>
    propertyCallbackStoreDefaults(std::string_view propertyName, Message message) {
        using enum gr::message::Command;
        assert(propertyName == block::property::kStoreDefaults);

        if (message.cmd == Set) {
            settings().storeDefaults();
            return std::nullopt;
        }

        throw gr::exception(fmt::format("block {} property {} does not implement command {}, msg: {}", unique_name, propertyName, message.cmd, message));
    }

    std::optional<Message>
    propertyCallbackResetDefaults(std::string_view propertyName, Message message) {
        using enum gr::message::Command;
        assert(propertyName == block::property::kResetDefaults);

        if (message.cmd == Set) {
            settings().resetDefaults();
            return std::nullopt;
        }

        throw gr::exception(fmt::format("block {} property {} does not implement command {}, msg: {}", unique_name, propertyName, message.cmd, message));
    }

protected:
    /***
     * Aggregate the amount of samples that can be consumed/produced from a range of ports.
     * @param ports a typelist of input or output ports
     * @return an anonymous struct representing the amount of available data on the ports
     */
    template<typename P>
    auto
    getPortLimits(P &&ports) {
        struct {
            std::size_t minSync = 0UL;                                          // the minimum amount of samples that the block needs for processing on the sync ports
            std::size_t maxSync = std::numeric_limits<std::size_t>::max();      // the maximum amount of that can be consumed on all sync ports
            std::size_t maxAvailable = std::numeric_limits<std::size_t>::max(); // the maximum amount of that are available on all sync ports
            bool hasAsync = false;                                              // true if there is at least one async input/output that has available samples/remaining capacity
        } result;
        auto        adjustForInputPort  = [&result]<PortLike Port>(Port &port) {
            const std::size_t available = [&port]() {
                if constexpr (gr::traits::port::is_input_v<Port>) {
                    return port.streamReader().available();
                } else {
                    return port.streamWriter().available();
                }
            }();
            if constexpr (std::remove_cvref_t<Port>::kIsSynch) {
                result.minSync      = std::max(result.minSync, port.min_samples);
                result.maxSync      = std::min(result.maxSync, port.max_samples);
                result.maxAvailable = std::min(result.maxAvailable, available);
            } else {                                 // async port
                if (available >= port.min_samples) { // ensure that process function is called if at least one async port has data available
                    result.hasAsync = true;
                }
            }
        };
        for_each_port([&adjustForInputPort](PortLike auto &port) { adjustForInputPort(port); }, std::forward<P>(ports));
        return result;
    }

    /***
     * Check the input ports for available samples
     */
    auto
    getNextTagAndEosPosition() {
        struct {
            bool hasTag = false;
            std::size_t nextTag = std::numeric_limits<std::size_t>::max();
            std::size_t nextEosTag = std::numeric_limits<std::size_t>::max();
            bool asyncEoS = false;
        } result;
        auto        adjustForInputPort = [&result]<PortLike Port>(Port &port) {
            if (port.isConnected()) {
                if constexpr (std::remove_cvref_t<Port>::kIsSynch) {
                    // get the tag after the one at position 0 that will be evaluated for this chunk.
                    // nextTag limits the size of the chunk except if this would violate port constraints
                    result.nextTag                        = std::min(result.nextTag, nSamplesUntilNextTag(port, 1).value_or(std::numeric_limits<std::size_t>::max()));
                    result.nextEosTag                     = std::min(result.nextEosTag, samples_to_eos_tag(port).value_or(std::numeric_limits<std::size_t>::max()));
                    const gr::ConsumableSpan auto tagData = port.tagReader().get(port.tagReader().available());
                    result.hasTag =  result.hasTag || (!tagData.empty() && tagData[0].index == port.streamReader().position() && !tagData[0].map.empty());
                } else { // async port
                    if (samples_to_eos_tag(port).transform([&port](auto n) { return n <= port.min_samples; }).value_or(false)) {
                        result.asyncEoS = true;
                    }
                }
            }
        };
        for_each_port([&adjustForInputPort](PortLike auto &port) { adjustForInputPort(port); }, inputPorts<PortType::STREAM>(&self()));
        return result;
    }

    /***
     * skip leftover stride
     * @param available number of samples that can be consumed from each sync port
     * @return inputSamples to skip before the chunk
     */
    std::size_t
    inputSamplesToSkipBeforeNextChunk(std::size_t availableSamples) {
        if constexpr (StrideControl::kEnabled) {                    // check if stride was removed at compile time
            const bool isStrideActiveAndNotDefault = stride.value != 0 && stride.value != denominator;
            std::size_t toSkip = 0;
            if (isStrideActiveAndNotDefault && strideCounter > 0) {
                toSkip = std::min(static_cast<std::size_t>(strideCounter), availableSamples);
                strideCounter -= static_cast<gr::Size_t>(toSkip);
            }
            return toSkip;
        }
        return 0Z;
    }

    /***
     * calculate how many samples to skip after processing
     * @return inputSamples to skip before the chunk
     */
    std::size_t
    inputSamplesToSkipAfterChunk(std::size_t remainingSamples) {
        if constexpr (StrideControl::kEnabled) {
            const bool isStrideActiveAndNotDefault = stride.value != 0 && stride.value != denominator;
            std::size_t toSkip = 0;
            if (isStrideActiveAndNotDefault && strideCounter == 0 && remainingSamples > 0) {
                toSkip = std::min(static_cast<std::size_t>(stride.value), remainingSamples);
                strideCounter = stride.value - static_cast<gr::Size_t>(toSkip);
            }
            return toSkip;
        }
        return 0UZ;
    }

    auto
    computeResampling(std::size_t minSyncIn, std::size_t maxSyncIn, std::size_t minSyncOut, std::size_t maxSyncOut) {
        struct ResamplingResult {
            std::size_t decimatedIn;
            std::size_t decimatedOut;
        };
        if constexpr (!Resampling::kEnabled) { // no resampling
            std::size_t n = std::min(maxSyncIn, maxSyncOut);
            return ResamplingResult{.decimatedIn = n, .decimatedOut = n};
        }
        if (denominator == 1UL && numerator == 1UL) { // no resampling
            std::size_t n = std::min(maxSyncIn, maxSyncOut);
            return ResamplingResult{.decimatedIn = n, .decimatedOut = n};
        }
        std::size_t nResamplingChunks;
        if constexpr (StrideControl::kEnabled) { // with stride, we cannot process more than one chunk
            if (stride.value != 0 && stride.value != denominator) {
                nResamplingChunks = denominator <= maxSyncIn && numerator <= maxSyncOut ? 1 : 0;
            } else {
                nResamplingChunks = std::min(maxSyncIn / denominator, maxSyncOut / numerator);
            }
        } else {
            nResamplingChunks = std::min(maxSyncIn / denominator, maxSyncOut / numerator);
        }
        if (nResamplingChunks * denominator < minSyncIn || nResamplingChunks * numerator < minSyncOut) {
            return ResamplingResult{.decimatedIn = 0UZ, .decimatedOut = 0UZ};
        } else {
            return ResamplingResult{static_cast<std::size_t>(nResamplingChunks * denominator), static_cast<std::size_t>(nResamplingChunks * numerator)};
        }
    }

    auto
    getMergedBlockLimit() {
        if constexpr (requires(const Derived &d) {
                          { available_samples(d) } -> std::same_as<std::size_t>;
                      }) {
            return available_samples(self());
        } else if constexpr (traits::block::stream_input_port_types<Derived>::size == 0
                             && traits::block::stream_output_port_types<Derived>::size
                                        == 0) { // allow blocks that have neither input nor output ports (by merging source to sink block) -> use internal buffer size
            constexpr gr::Size_t chunkSize = Derived::merged_work_chunk_size();
            static_assert(chunkSize != std::dynamic_extent && chunkSize > 0, "At least one internal port must define a maximum number of samples or the non-member/hidden "
                                                                             "friend function `available_samples(const BlockType&)` must be defined.");
            return chunkSize;
        }
        return std::numeric_limits<std::size_t>::max();
    }

    template<typename TIn, typename TOut>
    gr::work::Status invokeProcessBulk(TIn &inputReaderTuple, TOut &outputReaderTuple) {
        auto tempInputSpanStorage = std::apply([]<typename... PortReader>(PortReader&... args) {
            return std::tuple{(gr::meta::array_or_vector_type<PortReader> ? std::span{args.data(), args.size()} : args)...};
        }, inputReaderTuple);

        auto tempOutputSpanStorage = std::apply([]<typename... PortReader>(PortReader&... args)  {
            return std::tuple{(gr::meta::array_or_vector_type<PortReader> ? std::span{args.data(), args.size()} : args)...};
        }, outputReaderTuple);

        auto refToSpan = []<typename T, typename U>(T&& original, U&& temporary) -> decltype(auto) {
            if constexpr (gr::meta::array_or_vector_type<std::decay_t<T>>) {
                return std::forward<U>(temporary);
            } else {
                return std::forward<T>(original);
            }
        };

        return [&]<std::size_t... InIdx, std::size_t... OutIdx>(std::index_sequence<InIdx...>, std::index_sequence<OutIdx...>) {
            return self().processBulk(
                    refToSpan(std::get<InIdx>(inputReaderTuple), std::get<InIdx>(tempInputSpanStorage))...,
                    refToSpan(std::get<OutIdx>(outputReaderTuple), std::get<OutIdx>(tempOutputSpanStorage))...
            );
        }(std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<decltype(inputReaderTuple)>>>(),
               std::make_index_sequence<std::tuple_size_v<std::remove_cvref_t<decltype(outputReaderTuple)>>>());
    }


    work::Status
    invokeProcessOneSimd(auto &inputSpans, auto &outputSpans, auto width, std::size_t nSamplesToProcess) {
        std::size_t i = 0;
        for (; i + width <= nSamplesToProcess; i += width) {
            const auto &results = simdize_tuple_load_and_apply(width, inputSpans, i, [&](const auto &...input_simds) { return invoke_processOne_simd(i, width, input_simds...); });
            meta::tuple_for_each([i](auto &output_range, const auto &result) { result.copy_to(output_range.data() + i, stdx::element_aligned); }, outputSpans, results);
        }
        simd_epilogue(width, [&](auto w) {
            if (i + w <= nSamplesToProcess) {
                const auto results = simdize_tuple_load_and_apply(w, inputSpans, i, [&](auto &&...input_simds) { return invoke_processOne_simd(i, w, input_simds...); });
                meta::tuple_for_each([i](auto &output_range, auto &result) { result.copy_to(output_range.data() + i, stdx::element_aligned); }, outputSpans, results);
                i += w;
            }
        });
        return work::Status::OK;
    }

    work::Status
    invokeProcessOnePure(auto &inputSpans, auto &outputSpans, std::size_t nSamplesToProcess) {
        for (std::size_t i = 0; i < nSamplesToProcess; ++i) {
            auto results = std::apply([this, i](auto &...inputs) { return this->invoke_processOne(i, inputs[i]...); }, inputSpans);
            meta::tuple_for_each([i]<typename R>(auto &output_range, R &&result) { output_range[i] = std::forward<R>(result); }, outputSpans, results);
        }
        return work::Status::OK;
    }

    auto
    invokeProcessOneNonConst(auto &inputSpans, auto &outputSpans, std::size_t nSamplesToProcess) {
        using enum work::Status;
        struct ProcessOneResult {
            work::Status status;
            std::size_t processedIn;
            std::size_t processedOut;
        };
        std::size_t nOutSamplesBeforeRequestedStop = 0;
        for (std::size_t i = 0; i < nSamplesToProcess; ++i) {
            auto results = std::apply([this, i](auto &...inputs) { return this->invoke_processOne(i, inputs[i]...); }, inputSpans);
            meta::tuple_for_each(
                    [i]<typename R>(auto &output_range, R &&result) {
                        if constexpr (meta::array_or_vector_type<std::remove_cvref<decltype(result)>>) {
                            for (int j = 0; j < result.size(); j++) {
                                output_range[i][j] = std::move(result[j]);
                            }
                        } else {
                            output_range[i] = std::forward<R>(result);
                        }
                    },
                    outputSpans, results);
            nOutSamplesBeforeRequestedStop++;
            // the block implementer can set `_outputTagsChanged` to true in `processOne` to prematurely leave the loop and apply his changes
            if (_outputTagsChanged || lifecycle::isShuttingDown(this->state())) [[unlikely]] { // emitted tag and/or requested to stop
                break;
            }
        }
        if (nOutSamplesBeforeRequestedStop > 0) {
            return ProcessOneResult{OK, nOutSamplesBeforeRequestedStop, nOutSamplesBeforeRequestedStop};
        }
        return ProcessOneResult{OK, nSamplesToProcess, nSamplesToProcess};
    }

    void
    emitMessage(std::string_view endpoint, property_map message, std::string_view clientRequestID = "") noexcept {
        sendMessage<message::Command::Notify>(msgOut, unique_name /* serviceName */, endpoint, std::move(message), clientRequestID);
    }

    void
    notifyListeners(std::string_view endpoint, property_map message) noexcept {
        const auto it = propertySubscriptions.find(std::string(endpoint));
        if (it != propertySubscriptions.end()) {
            for (const auto &clientID : it->second) {
                emitMessage(endpoint, message, clientID);
            }
        }
    }

    void
    emitErrorMessage(std::string_view endpoint, Error e, std::string_view clientRequestID = "") noexcept {
        sendMessage<message::Command::Notify>(msgOut, unique_name /* serviceName */, endpoint, std::move(e), clientRequestID);
    }

    /**
     * Central function managing the dispatch of work to the block implementation provided work implementation
     * @brief
     * This function performs a series of steps to handle common block mechanics and determine the amount of work to be
     * dispatched to the block-provided work implementation. It can be sub-structured into the following steps:
     * - input validation and processing
     *   - apply settings
     *   - stream tags
     *     - settings
     *     - chunk by tags or realign tags to chunks
     *       - DEFAULT: chunk s.th. that tags are always on the first sample of a chunk
     *       - MOVE_FW/MOVE_BW: move the tags to the first sample of the current/next chunk
     *       - special case EOS tag: send incomplete chunk even if it violates work/block constraints -> implementations choose to drop/pad/...
     *     - propagate tags:
     *       - in the generic case the only tag in the current chunk is on the first sample
     *       - different strategies, see TagPropagation
     *   - settings
     *      - apply and reset cached/merged tag
     *   - get available samples count
     *     - syncIn: min/max/available samples to consume on SYNC ports
     *     - syncOut: min/max/available samples to produce on SYNC ports
     *     - check whether there are available samples for any ASYNC port
     *     - limit to requestedWork
     *     - correctly consider Resampling and Stride
     *     - deprecated: available_samples limits the amount of work to produce for source blocks
     * - perform work: processBulk/One/SIMD
     * - publishing
     *   - publish tags (done first so tags are guaranteed to be fully published for all available samples)
     *   - publish out samples
     *   - consume in samples (has to be last to correctly propagate back-pressure)
     * @return struct { std::size_t produced_work, work_return_t}
     */
    work::Result
    workInternal(std::size_t requested_work) {
        using enum gr::work::Status;
        using TInputTypes  = traits::block::stream_input_port_types<Derived>;
        using TOutputTypes = traits::block::stream_output_port_types<Derived>;

        applyChangedSettings(); // apply settings even if the block is already stopped

        if constexpr (!blockingIO) { // N.B. no other thread/constraint to consider before shutting down
            if (this->state() == lifecycle::State::REQUESTED_STOP) {
                if (auto e = this->changeStateTo(lifecycle::State::STOPPED); !e) {
                    using namespace gr::message;
                    emitErrorMessage("workInternal(): REQUESTED_STOP -> STOPPED", e.error());
                }
            }
        }

        if (this->state() == lifecycle::State::STOPPED) {
            return { requested_work, 0UZ, work::Status::DONE };
        }

        // evaluate number of available and processable samples
        const auto [minSyncIn, maxSyncIn, maxSyncAvailableIn, hasAsyncIn]     = getPortLimits(inputPorts<PortType::STREAM>(&self()));
        const auto [minSyncOut, maxSyncOut, maxSyncAvailableOut, hasAsyncOut] = getPortLimits(outputPorts<PortType::STREAM>(&self()));
        auto [hasTag, nextTag, nextEosTag, asyncEoS]                          = getNextTagAndEosPosition();
        auto       maxChunk                                                   = getMergedBlockLimit(); // handle special cases for merged blocks. TODO: evaluate if/how we can get rid of these
        const auto inputSkipBefore                                            = inputSamplesToSkipBeforeNextChunk(std::min({ maxSyncAvailableIn, nextTag, nextEosTag }));
        const auto availableToProcess          = std::min({ maxSyncIn, maxChunk, (maxSyncAvailableIn - inputSkipBefore), (nextTag - inputSkipBefore), (nextEosTag - inputSkipBefore) });
        const auto availableToPublish          = std::min({ maxSyncOut, maxSyncAvailableOut });
        const auto [resampledIn, resampledOut] = computeResampling(minSyncIn, availableToProcess, minSyncOut, availableToPublish);

        if (inputSkipBefore > 0) {                                                                          // consume samples on sync ports that need to be consumed due to the stride
            updateInputAndOutputTags(inputSkipBefore);                                                      // apply all tags in the skipped data range
            const auto inputSpans = prepareStreams(inputPorts<PortType::STREAM>(&self()), inputSkipBefore); // only way to consume is via the ConsumableSpan now
            consumeReaders(inputSkipBefore, inputSpans);
        }
        // return if there is no work to be performed // todo: add eos policy
        if (asyncEoS || (resampledIn == 0 && resampledOut == 0 && !hasAsyncIn && !hasAsyncOut)) {
            if (asyncEoS || (nextEosTag - inputSkipBefore <= minSyncIn) || (nextEosTag - inputSkipBefore <= denominator) || (nextEosTag - inputSkipBefore) / denominator <= minSyncOut / numerator) {
                if (auto e = this->changeStateTo(lifecycle::State::REQUESTED_STOP); !e) {
                    emitErrorMessage("workInternal(): EOS tag arrived -> REQUESTED_STOP", e.error());
                }
                publishTag({ { gr::tag::END_OF_STREAM, true } }, 0);
                updateInputAndOutputTags();
                forwardTags();
                this->setAndNotifyState(lifecycle::State::STOPPED);
                return { requested_work, 0UZ, work::Status::DONE };
            }
            if (nextEosTag <= 0 || lifecycle::isShuttingDown(this->state())) {
                if (auto e = this->changeStateTo(lifecycle::State::REQUESTED_STOP); !e) {
                    emitErrorMessage("workInternal(): REQUESTED_STOP", e.error());
                }
                updateInputAndOutputTags();
                applyChangedSettings();
                forwardTags();
                return { requested_work, 0UZ, DONE };
            }
            return {requested_work, 0UZ, resampledOut == 0 ? INSUFFICIENT_OUTPUT_ITEMS : INSUFFICIENT_INPUT_ITEMS };
        }
        // process stream tags
        updateInputAndOutputTags();
        applyChangedSettings();
        // TODO: handle tag propagation to next or previous chunk if there are multiple tags inside min samples, special case EOS -> additional parameter for kAllowIncompleteFinalUpdate

        // for non-bulk processing, the processed span has to be limited to the first sample if it contains a tag s.t. the tag is not applied to every sample
        const bool limitByFirstTag = (!HasProcessBulkFunction<Derived> && HasProcessOneFunction<Derived>) && hasTag;

        // call the block implementation's work function
        const auto   inputSpans  = prepareStreams(inputPorts<PortType::STREAM>(&self()), limitByFirstTag ? 1 : resampledIn);
        auto         outputSpans = prepareStreams(outputPorts<PortType::STREAM>(&self()), limitByFirstTag ? 1 : resampledOut);
        work::Status ret;
        std::size_t  processedIn  = limitByFirstTag ? 1 : resampledIn;
        std::size_t  processedOut = limitByFirstTag ? 1 : resampledOut;
        if constexpr (HasProcessBulkFunction<Derived>) {
            ret = invokeProcessBulk(inputSpans, outputSpans); // todo: evaluate how many were really produced...
        } else if constexpr (HasProcessOneFunction<Derived>) {
            if (processedIn != processedOut) {
                auto e = gr::Error(fmt::format("N input samples ({}) does not equal to N output samples ({}) for processOne() method.", resampledIn, resampledOut));
                emitErrorMessage("Block::workInternal:", e);
                requestStop();
                processedIn = 0;
                processedOut = 0;
            } else {
                using input_simd_types  = meta::simdize<typename TInputTypes::template apply<std::tuple>>;
                using output_simd_types = meta::simdize<typename TOutputTypes::template apply<std::tuple>>;

                constexpr auto                                 input_types_simd_size = meta::simdize_size_v<input_simd_types>;
                constexpr std::size_t                          max_simd_double_size  = stdx::simd_abi::max_fixed_size<double>;
                constexpr std::size_t                          simd_size             = input_types_simd_size == 0 ? max_simd_double_size : std::min(max_simd_double_size, input_types_simd_size * 4);
                std::integral_constant<std::size_t, simd_size> width{};

                if constexpr ((meta::simdize_size_v<output_simd_types> != 0) and ((requires(Derived &d) {
                    { d.processOne_simd(simd_size) };
                }) or (meta::simdize_size_v<input_simd_types> != 0 and traits::block::can_processOne_simd<Derived>))) { // SIMD loop
                    ret = invokeProcessOneSimd(inputSpans, outputSpans, width, processedIn);
                } else {                                                 // Non-SIMD loop
                    if constexpr (HasConstProcessOneFunction<Derived>) { // processOne is const -> can process whole batch similar to SIMD-ised call
                        ret = invokeProcessOnePure(inputSpans, outputSpans);
                    } else { // processOne isn't const i.e. not a pure function w/o side effects -> need to evaluate state after each sample
                        const auto result = invokeProcessOneNonConst(inputSpans, outputSpans, processedIn);
                        ret = result.status;
                        processedIn = result.processedIn;
                        processedOut = result.processedOut;
                    }
                }
            }
        } else { // block does not define any valid processing function
            static_assert(gr::meta::always_false<gr::traits::block::stream_input_port_types_tuple<Derived>>, "neither processBulk(...) nor processOne(...) implemented");
        }
        forwardTags();
        if (lifecycle::isShuttingDown(this->state())) {
            if (auto e = this->changeStateTo(lifecycle::State::REQUESTED_STOP); !e) {
                emitErrorMessage("isShuttingDown -> STOPPED", e.error());
            }
            updateInputAndOutputTags(processedIn);
            applyChangedSettings();
            ret       = work::Status::DONE;
            processedIn = 0UZ;
        }
        // publish/consume
        publishSamples(processedOut, outputSpans);
        const auto inputSamplesToSkipAfter = resampledIn > 0 ? inputSamplesToSkipAfterChunk(maxSyncAvailableIn - inputSkipBefore) : 0UZ;
        bool       success;
        if (inputSamplesToSkipAfter > 0 && inputSamplesToSkipAfter <= resampledIn) {
            updateInputAndOutputTags(inputSamplesToSkipAfter); // apply all tags in the skipped data range
            success = consumeReaders(inputSamplesToSkipAfter, inputSpans);
        } else if (inputSamplesToSkipAfter > 0) {
            updateInputAndOutputTags(inputSamplesToSkipAfter); // apply all tags in the skipped data range
            success                          = consumeReaders(resampledIn, inputSpans);
            const auto inputSpansForSkipping = prepareStreams(inputPorts<PortType::STREAM>(&self()), inputSamplesToSkipAfter - resampledIn); // only way to consume is via the ConsumableSpan now
            consumeReaders(inputSamplesToSkipAfter - resampledIn, inputSpansForSkipping);
        } else {
            success = consumeReaders(processedIn, inputSpans);
        }
        // if the block state changed to DONE, publish EOS tag on the next sample
        if (ret == work::Status::DONE) {
            this->setAndNotifyState(lifecycle::State::STOPPED);
            publishTag({ { gr::tag::END_OF_STREAM, true } }, 0);
        }
        return { requested_work, processedIn, success ? ret : work::Status::ERROR };
    } // end: work_return_t workInternal() noexcept { ..}

public:
    work::Status
    invokeWork()
        requires(blockingIO)
    {
        auto [work_requested, work_done, last_status] = workInternal(std::atomic_load_explicit(&ioRequestedWork, std::memory_order_acquire));
        ioWorkDone.increment(work_requested, work_done);
        ioLastWorkStatus.exchange(last_status, std::memory_order_relaxed);

        std::ignore = progress->incrementAndGet();
        progress->notify_all();
        return last_status;
    }

    /**
     * @brief Process as many samples as available and compatible with the internal boundary requirements or limited by 'requested_work`
     *
     * @param requested_work: usually the processed number of input samples, but could be any other metric as long as
     * requested_work limit as an affine relation with the returned performed_work.
     * @return { requested_work, performed_work, status}
     */
    template<typename = void>
    work::Result
    work(std::size_t requested_work = std::numeric_limits<std::size_t>::max()) noexcept {
        if constexpr (blockingIO) {
            constexpr bool useIoThread = std::disjunction_v<std::is_same<BlockingIO<true>, Arguments>...>;
            std::atomic_store_explicit(&ioRequestedWork, requested_work, std::memory_order_release);

            bool expectedThreadState = false;
            if (lifecycle::isActive(this->state()) && this->ioThreadRunning.compare_exchange_strong(expectedThreadState, true, std::memory_order_acq_rel)) {
                if constexpr (useIoThread) { // use graph-provided ioThreadPool
                    ioThreadPool->execute([this]() {
                        assert(lifecycle::isActive(this->state()));

                        lifecycle::State actualThreadState = this->state();
                        while (lifecycle::isActive(actualThreadState)) {
                            // execute ten times before testing actual state -- minimises overhead atomic load to work execution if the latter is a noop or very fast to execute
                            for (std::size_t testState = 0UZ; testState < 10UZ; ++testState) {
                                if (invokeWork() == work::Status::DONE) {
                                    actualThreadState = lifecycle::State::REQUESTED_STOP;
                                    if (auto e = this->changeStateTo(lifecycle::State::REQUESTED_STOP); !e) {
                                        emitErrorMessage("REQUESTED_STOP -> REQUESTED_STOP", e.error());
                                    }
                                    break;
                                }
                            }
                            actualThreadState = this->state();
                        }
                        if (auto e = this->changeStateTo(lifecycle::State::STOPPED); !e) {
                            emitErrorMessage("-> STOPPED", e.error());
                        }
                        ioThreadRunning.store(false);
                    });
                } else { // use user-provided ioThreadPool
                    // let user call 'work' explicitly and set both 'ioWorkDone' and 'ioLastWorkStatus'
                }
            }
            if constexpr (!useIoThread) {
                const bool blockIsActive = lifecycle::isActive(this->state());
                if (!blockIsActive) {
                    publishTag({ { gr::tag::END_OF_STREAM, true } }, 0);
                    ioLastWorkStatus.exchange(work::Status::DONE, std::memory_order_relaxed);
                }
            }

            const auto &[accumulatedRequestedWork, performedWork] = ioWorkDone.getAndReset();
            // TODO: this is just "working" solution for deadlock with emscripten, need to be investigated further
#if defined(__EMSCRIPTEN__)
            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
#endif
            return { accumulatedRequestedWork, performedWork, ioLastWorkStatus.load() };
        } else {
            return workInternal(requested_work);
        }
    }

    void
    processMessages([[maybe_unused]] const MsgPortInNamed<"__Builtin"> &port, std::span<const Message> messages) {
        using enum gr::message::Command;
        assert(std::addressof(port) == std::addressof(msgIn) && "got a message on wrong port");

        for (const auto &message : messages) {
            if (!message.serviceName.empty() && message.serviceName != unique_name && message.serviceName != name) {
                // Skip if target does not match the block's (unique) name and is not empty.
                continue;
            }

            PropertyCallback callback = nullptr;
            // Attempt to find a matching property callback or use the unmatchedPropertyHandler.
            if (auto it = propertyCallbacks.find(message.endpoint); it != propertyCallbacks.end()) {
                callback = it->second;
            } else {
                if constexpr (requires(std::string_view sv, Message m) {
                                  { self().unmatchedPropertyHandler(sv, m) } -> std::same_as<std::optional<Message>>;
                              }) {
                    callback = &Derived::unmatchedPropertyHandler;
                }
            }

            if (callback == nullptr) {
                continue; // did not find matching property callback
            }

            std::optional<Message> retMessage;
            try {
                retMessage = (self().*callback)(message.endpoint, message); // N.B. life-time: message is copied
            } catch (const gr::exception &e) {
                retMessage       = Message{ message };
                retMessage->data = std::unexpected(Error(e));
            } catch (const std::exception &e) {
                retMessage       = Message{ message };
                retMessage->data = std::unexpected(Error(e));
            } catch (...) {
                retMessage       = Message{ message };
                retMessage->data = std::unexpected(Error(fmt::format("unknown exception in Block {} property '{}'\n request message: {} ", unique_name, message.endpoint, message)));
            }

            if (!retMessage.has_value()) {
                continue; // function does not produce any return message
            }

            retMessage->cmd         = Final; // N.B. could enable/allow for partial if we return multiple messages (e.g. using coroutines?)
            retMessage->serviceName = unique_name;
            msgOut.streamWriter().publish([&](auto &out) { out[0] = *retMessage; }, 1UZ);
        } // - end - for (const auto &message : messages) { ..
    }

}; // template<typename Derived, typename... Arguments> class Block : ...

namespace detail {
template<typename List, std::size_t Index = 0, typename StringFunction>
inline constexpr auto
for_each_type_to_string(StringFunction func) -> std::string {
    if constexpr (Index < List::size) {
        using T = typename List::template at<Index>;
        return std::string(Index > 0 ? ", " : "") + func(Index, T()) + for_each_type_to_string<List, Index + 1>(func);
    } else {
        return "";
    }
}

template<typename T>
inline constexpr std::string
container_type_name() {
    if constexpr (requires { typename T::allocator_type; }) {
        return fmt::format("std::vector<{}>", gr::meta::type_name<typename T::value_type>());
    } else if constexpr (requires { std::tuple_size<T>::value; }) {
        return fmt::format("std::array<{}, {}>", gr::meta::type_name<typename T::value_type>(), std::tuple_size<T>::value);
    } else if constexpr (requires(T a) {
                             { std::real(a) } -> std::convertible_to<typename T::value_type>;
                             { std::imag(a) } -> std::convertible_to<typename T::value_type>;
                         }) {
        return fmt::format("std::complex<{}>", gr::meta::type_name<typename T::value_type>());
    } else { // fallback
        return gr::meta::type_name<T>();
    }
}
} // namespace detail

template<typename TBlock, typename TDecayedBlock>
inline void
checkBlockContracts() {
    // N.B. some checks could be evaluated during compile time but the expressed intent is to do this during runtime to allow
    // for more verbose feedback on method signatures etc.
    constexpr static auto processMembers = []<typename Func>(Func func) {
        if constexpr (detail::HasBaseType<TDecayedBlock>) {
            using BaseType = typename TDecayedBlock::base_t;
            if constexpr (refl::is_reflectable<BaseType>()) {
                refl::util::for_each(refl::reflect<BaseType>().members, func);
            }
        }
        if constexpr (refl::is_reflectable<TDecayedBlock>()) {
            refl::util::for_each(refl::reflect<TDecayedBlock>().members, func);
        }
    };

    constexpr static auto shortTypeName = []<typename T>() {
        if constexpr (std::is_same_v<T, gr::property_map>) {
            return "gr::property_map";
        } else if constexpr (std::is_same_v<T, std::string>) {
            return "std::string";
        } else if constexpr (requires { typename T::value_type; }) {
            return detail::container_type_name<T>();
        } else {
            return gr::meta::type_name<T>();
        }
    };

    constexpr static auto checkSettingsTypes = [](auto member) {
        using MemberType           = decltype(member)::value_type;
        using RawType              = std::remove_cvref_t<MemberType>;
        using Type                 = std::remove_cvref_t<unwrap_if_wrapped_t<RawType>>;
        constexpr bool isAnnotated = !std::is_same_v<RawType, Type>;
        // N.B. this function is compile-time ready but static_assert does not allow for configurable error messages
        if constexpr (!gr::settings::isSupportedType<Type>() && !(traits::port::is_port_v<Type> || traits::port::is_port_collection_v<Type>) ) {
            throw std::invalid_argument(fmt::format("block {} {}member '{}' has unsupported setting type '{}'", //
                                                    gr::meta::type_name<TDecayedBlock>(), isAnnotated ? "" : "annotated ", get_display_name(member), shortTypeName.template operator()<Type>()));
        }
    };
    processMembers(checkSettingsTypes);

    using TDerived = typename TDecayedBlock::derived_t;
    if constexpr (requires { &TDerived::work; }) {
        // N.B. implementing this is still allowed for workaround but should be discouraged as default API since this often leads to
        // important variants not being implemented such as lifecycle::State handling, Tag forwarding, etc.
        fmt::println(stderr, "DEPRECATION WARNING: block {} implements a raw 'gr::work::Result work(std::size_t requested_work)' ", shortTypeName.template operator()<TDecayedBlock>());
        return;
    }

    using TInputTypes  = traits::block::stream_input_port_types<TDerived>;
    using TOutputTypes = traits::block::stream_output_port_types<TDerived>;

    if constexpr (((TInputTypes::size.value + TOutputTypes::size.value) > 0UZ) && !gr::HasRequiredProcessFunction<TDecayedBlock>) {
        const auto b1 = (TOutputTypes::size.value == 1UZ) ? "" : "{ "; // optional opening brackets
        const auto b2 = (TOutputTypes::size.value == 1UZ) ? "" : " }"; // optional closing brackets
                                                                       // clang-format off
        std::string signatureProcessOne = fmt::format("* Option Ia (pure function):\n\n{}\n\n* Option Ib (allows modifications: settings, Tags, state, errors,...):\n\n{}\n\n* Option Ic (explicit return types):\n\n{}\n\n", //
fmt::format(R"(auto processOne({}) const noexcept {{
    /* add code here */
    return {}{}{};
}})",
    detail::for_each_type_to_string<TInputTypes>([]<typename T>(auto index, T) { return fmt::format("{} in{}", shortTypeName.template operator()<T>(), index); }),
    b1, detail::for_each_type_to_string<TOutputTypes>([]<typename T>(auto, T) { return fmt::format("{}()", shortTypeName.template operator()<T>()); }), b2),
fmt::format(R"(auto processOne({}) {{
    /* add code here */
    return {}{}{};
}})",
    detail::for_each_type_to_string<TInputTypes>([]<typename T>(auto index, T) { return fmt::format("{} in{}", shortTypeName.template operator()<T>(), index); }),
    b1, detail::for_each_type_to_string<TOutputTypes>([]<typename T>(auto, T) { return fmt::format("{}()", shortTypeName.template operator()<T>()); }), b2),
fmt::format(R"(std::tuple<{}> processOne({}) {{
    /* add code here */
    return {}{}{};
}})",
   detail::for_each_type_to_string<TOutputTypes>([]<typename T>(auto, T) { return fmt::format("{}", shortTypeName.template operator()<T>()); }), //
   detail::for_each_type_to_string<TInputTypes>([]<typename T>(auto index, T) { return fmt::format("{} in{}", shortTypeName.template operator()<T>(), index); }), //
   b1, detail::for_each_type_to_string<TOutputTypes>([]<typename T>(auto, T) { return fmt::format("{}()", shortTypeName.template operator()<T>()); }), b2)
);

std::string signaturesProcessBulk = fmt::format("* Option II:\n\n{}\n\nadvanced:* Option III:\n\n{}\n\n\n",
fmt::format(R"(gr::work::Status processBulk({}{}{}) {{
    /* add code here */
    return gr::work::Status::OK;
}})", //
    detail::for_each_type_to_string<TInputTypes>([]<typename T>(auto index, T) { return fmt::format("std::span<const {}> in{}", shortTypeName.template operator()<T>(), index); }), //
    (TInputTypes::size == 0UZ || TOutputTypes::size == 0UZ ? "" : ", "),                                                                             //
    detail::for_each_type_to_string<TOutputTypes>([]<typename T>(auto index, T) { return fmt::format("std::span<{}> out{}", shortTypeName.template operator()<T>(), index); })),
fmt::format(R"(gr::work::Status processBulk({}{}{}) {{
    /* add code here */
    return gr::work::Status::OK;
}})", //
    detail::for_each_type_to_string<TInputTypes>([]<typename T>(auto index, T) { return fmt::format("std::span<const {}> in{}", shortTypeName.template operator()<T>(), index); }), //
    (TInputTypes::size == 0UZ || TOutputTypes::size == 0UZ ? "" : ", "),                                                                             //
    detail::for_each_type_to_string<TOutputTypes>([]<typename T>(auto index, T) { return fmt::format("PublishableSpan auto out{}", shortTypeName.template operator()<T>(), index); })));
        // clang-format on

        bool has_port_collection = false;
        TInputTypes::for_each([&has_port_collection]<typename T>(auto, T) { has_port_collection |= requires { typename T::value_type; }; });
        TOutputTypes::for_each([&has_port_collection]<typename T>(auto, T) { has_port_collection |= requires { typename T::value_type; }; });
        const std::string signatures = (has_port_collection ? "" : signatureProcessOne) + signaturesProcessBulk;
        throw std::invalid_argument(fmt::format("block {} has neither a valid processOne(...) nor valid processBulk(...) method\nPossible valid signatures (copy-paste):\n\n{}",
                                                shortTypeName.template operator()<TDecayedBlock>(), signatures));
    }

    // test for optional Drawable interface
    if constexpr (!std::is_same_v<NotDrawable, typename TDecayedBlock::DrawableControl> && !requires(TDecayedBlock t) {
                      { t.draw() } -> std::same_as<work::Status>;
                  }) {
        static_assert(gr::meta::always_false<TDecayedBlock>, "annotated Block<Derived, Drawable<...>, ...> must implement 'work::Status draw() {}'");
    }
}

template<typename Derived, typename... Arguments>
inline std::atomic_size_t Block<Derived, Arguments...>::_uniqueIdCounter{ 0UZ };
} // namespace gr

ENABLE_REFLECTION_FOR_TEMPLATE_FULL((typename T, typename... Arguments), (gr::Block<T, Arguments...>), numerator, denominator, stride, unique_name, name, meta_information);

namespace gr {

/**
 * @brief a short human-readable/markdown description of the node -- content is not contractual and subject to change
 */
template<BlockLike TBlock>
[[nodiscard]] /*constexpr*/ std::string
blockDescription() noexcept {
    using DerivedBlock         = typename TBlock::derived_t;
    using ArgumentList         = typename TBlock::block_template_parameters;
    using SupportedTypes       = typename ArgumentList::template find_or_default<is_supported_types, DefaultSupportedTypes>;
    constexpr bool kIsBlocking = ArgumentList::template contains<BlockingIO<true>> || ArgumentList::template contains<BlockingIO<false>>;

    // re-enable once string and constexpr static is supported by all compilers
    /*constexpr*/ std::string ret = fmt::format("# {}\n{}\n{}\n**supported data types:**", //
                                                gr::meta::type_name<DerivedBlock>(), TBlock::description,
                                                kIsBlocking ? "**BlockingIO**\n_i.e. potentially non-deterministic/non-real-time behaviour_\n" : "");
    gr::meta::typelist<SupportedTypes>::for_each([&](std::size_t index, auto &&t) {
        std::string type_name = gr::meta::type_name<decltype(t)>();
        ret += fmt::format("{}:{} ", index, type_name);
    });
    ret += fmt::format("\n**Parameters:**\n");
    if constexpr (refl::is_reflectable<DerivedBlock>()) {
        for_each(refl::reflect<DerivedBlock>().members, [&](auto member) {
            using RawType = std::remove_cvref_t<typename decltype(member)::value_type>;
            using Type    = unwrap_if_wrapped_t<RawType>;

            if constexpr (is_readable(member) && (std::integral<Type> || std::floating_point<Type> || std::is_same_v<Type, std::string>) ) {
                if constexpr (is_annotated<RawType>()) {
                    const std::string type_name   = refl::detail::get_type_name<Type>().str();
                    const std::string member_name = get_display_name_const(member).str();
                    ret += fmt::format("{}{:10} {:<20} - annotated info: {} unit: [{}] documentation: {}{}\n",
                                       RawType::visible() ? "" : "_", //
                                       type_name,
                                       member_name, //
                                       RawType::description(), RawType::unit(),
                                       RawType::documentation(), //
                                       RawType::visible() ? "" : "_");
                } else {
                    const std::string type_name   = refl::detail::get_type_name<Type>().str();
                    const std::string member_name = get_display_name_const(member).str();
                    ret += fmt::format("_{:10} {}_\n", type_name, member_name);
                }
            }
        });
    }
    ret += fmt::format("\n~~Ports:~~\ntbd.");
    return ret;
}

namespace detail {
using namespace std::string_literals;

template<typename Type>
std::string
reflFirstTypeName() {
    if constexpr (refl::is_reflectable<Type>()) {
        return refl::reflect<Type>().name.str();

    } else {
        return meta::type_name<Type>;
    }
}

template<typename... Types>
std::string
encodeListOfTypes() {
    struct accumulator {
        std::string value;

        accumulator &
        operator%(const std::string &type) {
            if (value.empty()) value = type;
            else
                value += ","s + type;

            return *this;
        }
    };

    return (accumulator{} % ... % reflFirstTypeName<Types>()).value;
}

template<typename TBlock>
std::string
blockBaseName() {
    auto blockName = reflFirstTypeName<TBlock>();
    auto it        = std::ranges::find(blockName, '<');
    return std::string(blockName.begin(), it);
}

template<auto Value>
std::string
nttpToString() {
    if constexpr (magic_enum::is_scoped_enum_v<decltype(Value)> || magic_enum::is_unscoped_enum_v<decltype(Value)>) {
        return std::string(magic_enum::enum_name(Value));
    } else {
        return std::to_string(Value);
    }
}
} // namespace detail

template<typename... Types>
struct BlockParameters : meta::typelist<Types...> {
    static std::string
    toString() {
        return detail::encodeListOfTypes<Types...>();
    }
};

/**
 * This function (and overloads) can be used to register a block with
 * the block registry to be used for runtime instantiation of blocks
 * based on their stringified types.
 *
 * The arguments are:
 *  - registerInstance -- a reference to the registry (common to use gr::globalBlockRegistry)
 *  - TBlock -- the block class template
 *  - Value0 and Value1 -- if the block has non-template-type parameters,
 *    set these to the values of NTTPs you want to register
 *  - TBlockParameters -- types that the block can be instantiated with
 */
template<template<typename> typename TBlock, typename... TBlockParameters, typename TRegisterInstance>
inline constexpr int
registerBlock(TRegisterInstance &registerInstance) {
    auto addBlockType = [&]<typename Type> {
        using ThisBlock = TBlock<Type>;
        static_assert(!meta::is_instantiation_of<Type, BlockParameters>);
        registerInstance.template addBlockType<ThisBlock>(detail::blockBaseName<TBlock<Type>>(), //
                                                          detail::reflFirstTypeName<Type>());
    };
    ((addBlockType.template operator()<TBlockParameters>()), ...);
    return {};
}

template<template<typename, typename> typename TBlock, typename... TBlockParameters, typename TRegisterInstance>
inline constexpr int
registerBlock(TRegisterInstance &registerInstance) {
    auto addBlockType = [&]<typename Type> {
        using ThisBlock = TBlock<typename Type::template at<0>, typename Type::template at<1>>;
        static_assert(meta::is_instantiation_of<Type, BlockParameters>);
        static_assert(Type::size == 2);
        registerInstance.template addBlockType<ThisBlock>(detail::blockBaseName<ThisBlock>(), //
                                                          Type::toString());
    };
    ((addBlockType.template operator()<TBlockParameters>()), ...);
    return {};
}

template<template<typename, auto> typename TBlock, auto Value0, typename... TBlockParameters, typename TRegisterInstance>
inline constexpr int
registerBlock(TRegisterInstance &registerInstance) {
    auto addBlockType = [&]<typename Type> {
        static_assert(!meta::is_instantiation_of<Type, BlockParameters>);
        using ThisBlock = TBlock<Type, Value0>;
        registerInstance.template addBlockType<ThisBlock>(detail::blockBaseName<ThisBlock>(), //
                                                          detail::reflFirstTypeName<Type>() + "," + detail::nttpToString<Value0>());
    };
    ((addBlockType.template operator()<TBlockParameters>()), ...);
    return {};
}

template<template<typename, typename, auto> typename TBlock, auto Value0, typename... TBlockParameters, typename TRegisterInstance>
inline constexpr int
registerBlock(TRegisterInstance &registerInstance) {
    auto addBlockType = [&]<typename Type> {
        static_assert(meta::is_instantiation_of<Type, BlockParameters>);
        static_assert(Type::size == 2);
        using ThisBlock = TBlock<typename Type::template at<0>, typename Type::template at<1>, Value0>;
        registerInstance.template addBlockType<ThisBlock>(detail::blockBaseName<ThisBlock>(), //
                                                          Type::toString() + "," + detail::nttpToString<Value0>());
    };
    ((addBlockType.template operator()<TBlockParameters>()), ...);
    return {};
}

template<template<typename, auto, auto> typename TBlock, auto Value0, auto Value1, typename... TBlockParameters, typename TRegisterInstance>
inline constexpr int
registerBlock(TRegisterInstance &registerInstance) {
    auto addBlockType = [&]<typename Type> {
        static_assert(!meta::is_instantiation_of<Type, BlockParameters>);
        using ThisBlock = TBlock<Type, Value0, Value1>;
        registerInstance.template addBlockType<ThisBlock>(detail::blockBaseName<ThisBlock>(), //
                                                          detail::reflFirstTypeName<Type>() + "," + detail::nttpToString<Value0>() + "," + detail::nttpToString<Value1>());
    };
    ((addBlockType.template operator()<TBlockParameters>()), ...);
    return {};
}

template<template<typename, typename, auto, auto> typename TBlock, auto Value0, auto Value1, typename... TBlockParameters, typename TRegisterInstance>
inline constexpr int
registerBlock(TRegisterInstance &registerInstance) {
    auto addBlockType = [&]<typename Type> {
        static_assert(meta::is_instantiation_of<Type, BlockParameters>);
        static_assert(Type::size == 2);
        using ThisBlock = TBlock<typename Type::template at<0>, typename Type::template at<1>, Value0, Value1>;
        registerInstance.template addBlockType<ThisBlock>(detail::blockBaseName<ThisBlock>(), //
                                                          Type::toString() + "," + detail::nttpToString<Value0>() + "," + detail::nttpToString<Value1>());
    };
    ((addBlockType.template operator()<TBlockParameters>()), ...);
    return {};
}

template<typename Function, typename Tuple, typename... Tuples>
inline constexpr auto
for_each_port(Function &&function, Tuple &&tuple, Tuples &&...tuples) {
    return gr::meta::tuple_for_each(
            [&function](auto &&...args) {
                (..., ([&function](auto &&arg) {
                     using ArgType = std::decay_t<decltype(arg)>;
                     if constexpr (traits::port::is_port_v<ArgType>) {
                         function(arg); // arg is a port, apply function directly
                     } else if constexpr (traits::port::is_port_collection_v<ArgType>) {
                         for (auto &port : arg) { // arg is a collection of ports, apply function to each port
                             function(port);
                         }
                     } else {
                         static_assert(gr::meta::always_false<Tuple>, "not a port or collection of ports");
                     }
                 }(args)));
            },
            std::forward<Tuple>(tuple), std::forward<Tuples>(tuples)...);
}

} // namespace gr

template<>
struct fmt::formatter<gr::work::Result> {
    static constexpr auto
    parse(const format_parse_context &ctx) {
        const auto it = ctx.begin();
        if (it != ctx.end() && *it != '}') throw format_error("invalid format");
        return it;
    }

    template<typename FormatContext>
    auto
    format(const gr::work::Result &work_return, FormatContext &ctx) {
        return fmt::format_to(ctx.out(), "requested_work: {}, performed_work: {}, status: {}", work_return.requested_work, work_return.performed_work, magic_enum::enum_name(work_return.status));
    }
};

#endif // include guard

// #include <gnuradio-4.0/Buffer.hpp>

// #include <gnuradio-4.0/CircularBuffer.hpp>

// #include <gnuradio-4.0/meta/typelist.hpp>

// #include <gnuradio-4.0/Port.hpp>

// #include <gnuradio-4.0/reflection.hpp>

// #include <gnuradio-4.0/Sequence.hpp>

// #include <gnuradio-4.0/thread/thread_pool.hpp>


#include <algorithm>
#include <complex>
#include <iostream>
#include <map>
#include <ranges>
#include <tuple>
#include <variant>

#if !__has_include(<source_location>)
#define HAVE_SOURCE_LOCATION 0
#else

#include <source_location>

#if defined __cpp_lib_source_location && __cpp_lib_source_location >= 201907L
#define HAVE_SOURCE_LOCATION 1
#else
#define HAVE_SOURCE_LOCATION 0
#endif
#endif

namespace gr {

class BlockModel {
protected:
    struct NamedPortCollection {
        std::string                  name;
        std::vector<gr::DynamicPort> ports;
    };

    using DynamicPortOrCollection             = std::variant<gr::DynamicPort, NamedPortCollection>;
    using DynamicPorts                        = std::vector<DynamicPortOrCollection>;
    bool                  _dynamicPortsLoaded = false;
    std::function<void()> _dynamicPortsLoader;
    DynamicPorts          _dynamicInputPorts;
    DynamicPorts          _dynamicOutputPorts;

    BlockModel() = default;

public:
    BlockModel(const BlockModel &) = delete;
    BlockModel &
    operator=(const BlockModel &)
            = delete;
    BlockModel(BlockModel &&other) = delete;
    BlockModel &
    operator=(BlockModel &&other)
            = delete;

    void
    initDynamicPorts() const {
        if (!_dynamicPortsLoaded) _dynamicPortsLoader();
    }

    MsgPortInNamed<"__Builtin">  *msgIn;
    MsgPortOutNamed<"__Builtin"> *msgOut;

    [[nodiscard]] gr::DynamicPort &
    dynamicInputPort(std::size_t index, std::size_t subIndex = meta::invalid_index) {
        initDynamicPorts();
        if (auto *portCollection = std::get_if<NamedPortCollection>(&_dynamicInputPorts.at(index))) {
            if (subIndex == meta::invalid_index) {
                throw std::invalid_argument("Need to specify the index in the port collection");
            } else {
                return portCollection->ports[subIndex];
            }

        } else if (auto *port = std::get_if<gr::DynamicPort>(&_dynamicInputPorts.at(index))) {
            if (subIndex == meta::invalid_index) {
                return *port;
            } else {
                throw std::invalid_argument("Specified sub-index for a normal port");
            }
        }

        throw std::logic_error("Variant construction failed");
    }

    [[nodiscard]] gr::DynamicPort &
    dynamicOutputPort(std::size_t index, std::size_t subIndex = meta::invalid_index) {
        initDynamicPorts();
        if (auto *portCollection = std::get_if<NamedPortCollection>(&_dynamicOutputPorts.at(index))) {
            if (subIndex == meta::invalid_index) {
                throw std::invalid_argument("Need to specify the index in the port collection");
            } else {
                return portCollection->ports[subIndex];
            }

        } else if (auto *port = std::get_if<gr::DynamicPort>(&_dynamicOutputPorts.at(index))) {
            if (subIndex == meta::invalid_index) {
                return *port;
            } else {
                throw std::invalid_argument("Specified sub-index for a normal port");
            }
        }

        throw std::logic_error("Variant construction failed");
    }

    [[nodiscard]] std::size_t
    dynamicInputPortsSize(std::size_t parentIndex = meta::invalid_index) const {
        initDynamicPorts();
        if (parentIndex == meta::invalid_index) {
            return _dynamicInputPorts.size();
        } else {
            if (auto *portCollection = std::get_if<NamedPortCollection>(&_dynamicInputPorts.at(parentIndex))) {
                return portCollection->ports.size();
            } else {
                return meta::invalid_index;
            }
        }
    }

    [[nodiscard]] std::size_t
    dynamicOutputPortsSize(std::size_t parentIndex = meta::invalid_index) const {
        initDynamicPorts();
        if (parentIndex == meta::invalid_index) {
            return _dynamicOutputPorts.size();
        } else {
            if (auto *portCollection = std::get_if<NamedPortCollection>(&_dynamicOutputPorts.at(parentIndex))) {
                return portCollection->ports.size();
            } else {
                return meta::invalid_index;
            }
        }
    }

    std::size_t
    dynamicInputPortIndex(std::string_view name) const {
        initDynamicPorts();
        for (std::size_t i = 0; i < _dynamicInputPorts.size(); ++i) {
            if (auto *portCollection = std::get_if<NamedPortCollection>(&_dynamicInputPorts.at(i))) {
                if (portCollection->name == name) {
                    return i;
                }
            } else if (auto *port = std::get_if<gr::DynamicPort>(&_dynamicInputPorts.at(i))) {
                if (port->name == name) {
                    return i;
                }
            }
        }

        throw std::invalid_argument(fmt::format("Port {} does not exist", name));
    }

    std::size_t
    dynamicOutputPortIndex(std::string_view name) const {
        initDynamicPorts();
        for (std::size_t i = 0; i < _dynamicOutputPorts.size(); ++i) {
            if (auto *portCollection = std::get_if<NamedPortCollection>(&_dynamicOutputPorts.at(i))) {
                if (portCollection->name == name) {
                    return i;
                }
            } else if (auto *port = std::get_if<gr::DynamicPort>(&_dynamicOutputPorts.at(i))) {
                if (port->name == name) {
                    return i;
                }
            }
        }

        throw std::invalid_argument(fmt::format("Port {} does not exist", name));
    }

    virtual ~BlockModel() = default;

    /**
     * @brief to be called by scheduler->graph to initialise block
     */
    virtual void
    init(std::shared_ptr<gr::Sequence> progress, std::shared_ptr<gr::thread_pool::BasicThreadPool> ioThreadPool)
            = 0;

    /**
     * @brief returns scheduling hint that invoking the work(...) function may block on IO or system-calls
     */
    [[nodiscard]] virtual constexpr bool
    isBlocking() const noexcept
            = 0;

    /**
     * @brief change Block state (N.B. IDLE, INITIALISED, RUNNING, REQUESTED_STOP, REQUESTED_PAUSE, STOPPED, PAUSED, ERROR)
     * See enum description for details.
     */
    [[nodiscard]] virtual std::expected<void, Error>
    changeState(lifecycle::State newState) noexcept = 0;

    /**
     * @brief Block state (N.B. IDLE, INITIALISED, RUNNING, REQUESTED_STOP, REQUESTED_PAUSE, STOPPED, PAUSED, ERROR)
     * See enum description for details.
     */
    [[nodiscard]] virtual lifecycle::State
    state() const noexcept
            = 0;

    /**
     * @brief number of available readable samples at the block's input ports
     */
    [[nodiscard]] virtual constexpr std::size_t
    availableInputSamples(std::vector<std::size_t> &) const noexcept
            = 0;

    /**
     * @brief number of available writable samples at the block's output ports
     */
    [[nodiscard]] virtual constexpr std::size_t
    availableOutputSamples(std::vector<std::size_t> &) const noexcept
            = 0;

    /**
     * @brief user defined name
     */
    [[nodiscard]] virtual std::string_view
    name() const
            = 0;

    /**
     * @brief the type of the node as a string
     */
    [[nodiscard]] virtual std::string_view
    typeName() const
            = 0;

    /**
     * @brief user-defined name
     * N.B. may not be unique -> ::uniqueName
     */
    virtual void
    setName(std::string name) noexcept
            = 0;

    /**
     * @brief used to store non-graph-processing information like UI block position etc.
     */
    [[nodiscard]] virtual property_map &
    metaInformation() noexcept
            = 0;

    [[nodiscard]] virtual const property_map &
    metaInformation() const
            = 0;

    /**
     * @brief process-wide unique name
     * N.B. can be used to disambiguate in case user provided the same 'name()' for several blocks.
     */
    [[nodiscard]] virtual std::string_view
    uniqueName() const
            = 0;

    [[nodiscard]] virtual SettingsBase &
    settings() const
            = 0;

    [[nodiscard]] virtual work::Result
    work(std::size_t requested_work)
            = 0;

    [[nodiscard]] virtual work::Status
    draw() = 0;

    virtual void
    processScheduledMessages()
            = 0;

    [[nodiscard]] virtual void *
    raw() = 0;
};

namespace detail {
template<typename T, typename... Ts>
constexpr bool contains_type = (std::is_same_v<T, Ts> || ...);
}

template<BlockLike T>
class BlockWrapper : public BlockModel {
private:
    static_assert(std::is_same_v<T, std::remove_reference_t<T>>);
    T           _block;
    std::string _type_name = gr::meta::type_name<T>();

    [[nodiscard]] constexpr const auto &
    blockRef() const noexcept {
        if constexpr (requires { *_block; }) {
            return *_block;
        } else {
            return _block;
        }
    }

    [[nodiscard]] constexpr auto &
    blockRef() noexcept {
        if constexpr (requires { *_block; }) {
            return *_block;
        } else {
            return _block;
        }
    }

    void
    initMessagePorts() {
        msgIn  = std::addressof(_block.msgIn);
        msgOut = std::addressof(_block.msgOut);
    }

    void
    createDynamicPortsLoader() {
        _dynamicPortsLoader = [this] {
            if (_dynamicPortsLoaded) return;

            using Node = std::remove_cvref_t<decltype(blockRef())>;

            auto registerPort = [&](auto &where, [[maybe_unused]] auto direction, [[maybe_unused]] auto index, auto &&t) {
                auto processPort = []<typename Port>(auto &where_, Port &port) -> auto & {
                    where_.push_back(gr::DynamicPort(port, DynamicPort::non_owned_reference_tag{}));
                    return where_.back();
                };

                using CurrentPortType = std::remove_cvref_t<decltype(t)>;
                if constexpr (traits::port::is_port_v<CurrentPortType>) {
                    using PortDescriptor = typename CurrentPortType::ReflDescriptor;
                    if constexpr (refl::trait::is_descriptor_v<PortDescriptor>) {
                        auto &port = (blockRef().*(PortDescriptor::pointer));
                        processPort(where, port);
                    } else {
                        // We can also have ports defined as template parameters
                        if constexpr (decltype(direction)::value == PortDirection::INPUT) {
                            processPort(where, gr::inputPort<decltype(index)::value, PortType::ANY>(&blockRef()));
                        } else {
                            processPort(where, gr::outputPort<decltype(index)::value, PortType::ANY>(&blockRef()));
                        }
                    }
                } else {
                    using PortCollectionDescriptor = typename CurrentPortType::value_type::ReflDescriptor;
                    if constexpr (refl::trait::is_descriptor_v<PortCollectionDescriptor>) {
                        auto               &collection = (blockRef().*(PortCollectionDescriptor::pointer));
                        NamedPortCollection result;
                        result.name = refl::descriptor::get_name(PortCollectionDescriptor()).data;
                        for (auto &port : collection) {
                            processPort(result.ports, port);
                        }
                        where.push_back(std::move(result));
                    } else {
                        static_assert(meta::always_false<PortCollectionDescriptor>, "Port collections are only supported for member variables");
                    }
                }
            };
            traits::block::all_input_ports<Node>::for_each(registerPort, _dynamicInputPorts, std::integral_constant<PortDirection, PortDirection::INPUT>{});
            traits::block::all_output_ports<Node>::for_each(registerPort, _dynamicOutputPorts, std::integral_constant<PortDirection, PortDirection::OUTPUT>{});

            constexpr std::size_t input_port_count  = gr::traits::block::all_input_port_types<Node>::size;
            constexpr std::size_t output_port_count = gr::traits::block::all_output_port_types<Node>::size;
            static_assert(input_port_count + output_port_count > 0);
            _dynamicPortsLoaded = true;
        };
    }

public:
    BlockWrapper(const BlockWrapper &other) = delete;
    BlockWrapper(BlockWrapper &&other)      = delete;
    BlockWrapper &
    operator=(const BlockWrapper &other)
            = delete;
    BlockWrapper &
    operator=(BlockWrapper &&other)
            = delete;

    ~BlockWrapper() override = default;

    BlockWrapper() {
        initMessagePorts();
        createDynamicPortsLoader();
    }

    template<typename Arg>
        requires(!std::is_same_v<std::remove_cvref_t<Arg>, T>)
    explicit BlockWrapper(Arg &&arg) : _block(std::forward<Arg>(arg)) {
        initMessagePorts();
        createDynamicPortsLoader();
    }

    template<typename... Args>
        requires(!detail::contains_type<BlockWrapper, std::decay_t<Args>...> && sizeof...(Args) > 1)
    explicit BlockWrapper(Args &&...args) : _block{ std::forward<Args>(args)... } {
        initMessagePorts();
        createDynamicPortsLoader();
    }

    explicit BlockWrapper(std::initializer_list<std::pair<const std::string, pmtv::pmt>> init_parameter) : _block{ std::move(init_parameter) } {
        initMessagePorts();
        createDynamicPortsLoader();
    }

    void
    init(std::shared_ptr<gr::Sequence> progress, std::shared_ptr<gr::thread_pool::BasicThreadPool> ioThreadPool) override {
        return blockRef().init(progress, ioThreadPool);
    }

    [[nodiscard]] constexpr work::Result
    work(std::size_t requested_work = std::numeric_limits<std::size_t>::max()) override {
        return blockRef().work(requested_work);
    }

    constexpr work::Status
    draw() override {
        if constexpr (requires { blockRef().draw(); }) {
            return blockRef().draw();
        }
        return work::Status::ERROR;
    }

    void
    processScheduledMessages() override {
        return blockRef().processScheduledMessages();
    }

    [[nodiscard]] constexpr bool
    isBlocking() const noexcept override {
        return blockRef().isBlocking();
    }

    [[nodiscard]] std::expected<void, Error>
    changeState(lifecycle::State newState) noexcept override {
        return blockRef().changeStateTo(newState);
    }

    [[nodiscard]] lifecycle::State
    state() const noexcept override {
        return blockRef().state();
    }

    [[nodiscard]] constexpr std::size_t
    availableInputSamples(std::vector<std::size_t> &data) const noexcept override {
        return blockRef().availableInputSamples(data);
    }

    [[nodiscard]] constexpr std::size_t
    availableOutputSamples(std::vector<std::size_t> &data) const noexcept override {
        return blockRef().availableOutputSamples(data);
    }

    [[nodiscard]] std::string_view
    name() const override {
        return blockRef().name;
    }

    void
    setName(std::string name) noexcept override {
        blockRef().name = std::move(name);
    }

    [[nodiscard]] std::string_view
    typeName() const override {
        return _type_name;
    }

    [[nodiscard]] property_map &
    metaInformation() noexcept override {
        return blockRef().meta_information;
    }

    [[nodiscard]] const property_map &
    metaInformation() const override {
        return blockRef().meta_information;
    }

    [[nodiscard]] std::string_view
    uniqueName() const override {
        return blockRef().unique_name;
    }

    [[nodiscard]] SettingsBase &
    settings() const override {
        return blockRef().settings();
    }

    [[nodiscard]] void *
    raw() override {
        return std::addressof(blockRef());
    }
};

template<typename T>
struct PortIndexDefinition {
    T           topLevel;
    std::size_t subIndex;

    constexpr PortIndexDefinition(T _topLevel, std::size_t _subIndex = meta::invalid_index) : topLevel(std::move(_topLevel)), subIndex(_subIndex) {}
};

class Edge {
public: // TODO: consider making this private and to use accessors (that can be safely used by users)
    using PortDirection::INPUT;
    using PortDirection::OUTPUT;
    BlockModel                      *_sourceBlock;
    BlockModel                      *_destinationBlock;
    PortIndexDefinition<std::size_t> _sourcePortDefinition;
    PortIndexDefinition<std::size_t> _destinationPortDefinition;
    std::size_t                      _minBufferSize;
    std::int32_t                     _weight;
    std::string                      _name; // custom edge name
    bool                             _connected;

public:
    Edge() = delete;

    Edge(const Edge &) = delete;

    Edge &
    operator=(const Edge &)
            = delete;

    Edge(Edge &&) noexcept = default;

    Edge &
    operator=(Edge &&) noexcept
            = default;

    Edge(BlockModel *sourceBlock, PortIndexDefinition<std::size_t> sourcePortDefinition, BlockModel *destinationBlock, PortIndexDefinition<std::size_t> destinationPortDefinition,
         std::size_t minBufferSize, std::int32_t weight, std::string_view name)
        : _sourceBlock(sourceBlock)
        , _destinationBlock(destinationBlock)
        , _sourcePortDefinition(sourcePortDefinition)
        , _destinationPortDefinition(destinationPortDefinition)
        , _minBufferSize(minBufferSize)
        , _weight(weight)
        , _name(name) {}

    [[nodiscard]] constexpr const BlockModel &
    sourceBlock() const noexcept {
        return *_sourceBlock;
    }

    [[nodiscard]] constexpr const BlockModel &
    destinationBlock() const noexcept {
        return *_destinationBlock;
    }

    [[nodiscard]] constexpr PortIndexDefinition<std::size_t>
    sourcePortDefinition() const noexcept {
        return _sourcePortDefinition;
    }

    [[nodiscard]] constexpr PortIndexDefinition<std::size_t>
    destinationPortDefinition() const noexcept {
        return _destinationPortDefinition;
    }

    [[nodiscard]] constexpr std::string_view
    name() const noexcept {
        return _name;
    }

    [[nodiscard]] constexpr std::size_t
    minBufferSize() const noexcept {
        return _minBufferSize;
    }

    [[nodiscard]] constexpr std::int32_t
    weight() const noexcept {
        return _weight;
    }

    [[nodiscard]] constexpr bool
    is_connected() const noexcept {
        return _connected;
    }
};

class Graph : public gr::Block<Graph> {
    alignas(hardware_destructive_interference_size) std::shared_ptr<gr::Sequence> progress                         = std::make_shared<gr::Sequence>();
    alignas(hardware_destructive_interference_size) std::shared_ptr<gr::thread_pool::BasicThreadPool> ioThreadPool = std::make_shared<gr::thread_pool::BasicThreadPool>(
            "graph_thread_pool", gr::thread_pool::TaskType::IO_BOUND, 2UZ, std::numeric_limits<uint32_t>::max());

private:
    std::vector<std::function<ConnectionResult(Graph &)>> _connectionDefinitions;
    std::vector<Edge>                                     _edges;

    std::vector<std::unique_ptr<BlockModel>> _blocks;

    template<typename TBlock>
    std::unique_ptr<BlockModel> &
    findBlock(TBlock &what) {
        static_assert(!std::is_pointer_v<std::remove_cvref_t<TBlock>>);
        auto it = [&, this] {
            if constexpr (std::is_same_v<TBlock, BlockModel>) {
                return std::find_if(_blocks.begin(), _blocks.end(), [&](const auto &block) { return block.get() == &what; });
            } else {
                return std::find_if(_blocks.begin(), _blocks.end(), [&](const auto &block) { return block->raw() == &what; });
            }
        }();

        if (it == _blocks.end()) throw std::runtime_error(fmt::format("No such block in this graph"));
        return *it;
    }

    template<std::size_t sourcePortIndex, std::size_t sourcePortSubIndex, std::size_t destinationPortIndex, std::size_t destinationPortSubIndex, typename Source, typename SourcePort,
             typename Destination, typename DestinationPort>
    [[nodiscard]] ConnectionResult
    connectImpl(Source &sourceNodeRaw, SourcePort &source_port_or_collection, Destination &destinationNodeRaw, DestinationPort &destinationPort_or_collection, std::size_t minBufferSize = 65536,
                std::int32_t weight = 0, std::string_view edgeName = "unnamed edge") {
        if (!std::any_of(_blocks.begin(), _blocks.end(), [&](const auto &registeredNode) { return registeredNode->raw() == std::addressof(sourceNodeRaw); })
            || !std::any_of(_blocks.begin(), _blocks.end(), [&](const auto &registeredNode) { return registeredNode->raw() == std::addressof(destinationNodeRaw); })) {
            throw std::runtime_error(
                    fmt::format("Can not connect nodes that are not registered first:\n {}:{} -> {}:{}\n", sourceNodeRaw.name, sourcePortIndex, destinationNodeRaw.name, destinationPortIndex));
        }

        auto *sourcePort = [&] {
            if constexpr (traits::port::is_port_v<SourcePort>) {
                return &source_port_or_collection;
            } else {
                return &source_port_or_collection[sourcePortSubIndex];
            }
        }();

        auto *destinationPort = [&] {
            if constexpr (traits::port::is_port_v<DestinationPort>) {
                return &destinationPort_or_collection;
            } else {
                return &destinationPort_or_collection[destinationPortSubIndex];
            }
        }();

        if constexpr (!std::is_same_v<typename std::remove_pointer_t<decltype(destinationPort)>::value_type, typename std::remove_pointer_t<decltype(sourcePort)>::value_type>) {
            meta::print_types<meta::message_type<"The source port type needs to match the sink port type">, typename std::remove_pointer_t<decltype(destinationPort)>::value_type,
                              typename std::remove_pointer_t<decltype(sourcePort)>::value_type>{};
        }

        auto result = sourcePort->connect(*destinationPort);
        if (result == ConnectionResult::SUCCESS) {
            auto *sourceNode      = findBlock(sourceNodeRaw).get();
            auto *destinationNode = findBlock(destinationNodeRaw).get();
            // TODO: Rethink edge definition, indices, message port -1 etc.
            _edges.emplace_back(sourceNode, PortIndexDefinition<std::size_t>{ sourcePortIndex, sourcePortSubIndex }, destinationNode,
                                PortIndexDefinition<std::size_t>{ destinationPortIndex, destinationPortSubIndex }, minBufferSize, weight, edgeName);
        }

        return result;
    }

    // Just a dummy class that stores the graph and the source block and port
    // to be able to split the connection into two separate calls
    // connect(source) and .to(destination)
    template<typename Source, typename Port, std::size_t sourcePortIndex = 1UZ, std::size_t sourcePortSubIndex = meta::invalid_index>
    struct SourceConnector {
        Graph  &self;
        Source &source;
        Port   &port;

        SourceConnector(Graph &_self, Source &_source, Port &_port) : self(_self), source(_source), port(_port) {}

        static_assert(std::is_same_v<Port, gr::Message> || traits::port::is_port_v<Port> || (sourcePortSubIndex != meta::invalid_index),
                      "When we have a collection of ports, we need to have an index to access the desired port in the collection");

    private:
        template<typename Destination, typename DestinationPort, std::size_t destinationPortIndex = meta::invalid_index, std::size_t destinationPortSubIndex = meta::invalid_index>
        [[nodiscard]] constexpr ConnectionResult
        to(Destination &destination, DestinationPort &destinationPort) {
            // Not overly efficient as the block doesn't know the graph it belongs to,
            // but this is not a frequent operation and the check is important.
            auto is_block_known = [this](const auto &query_block) {
                return std::any_of(self._blocks.cbegin(), self._blocks.cend(), [&query_block](const auto &known_block) { return known_block->raw() == std::addressof(query_block); });
            };
            if (!is_block_known(source) || !is_block_known(destination)) {
                fmt::print("Source {} and/or destination {} do not belong to this graph\n", source.name, destination.name);
                return ConnectionResult::FAILED;
            }
            self._connectionDefinitions.push_back([src = &source, source_port = &port, destination = &destination, destinationPort = &destinationPort](Graph &graph) {
                return graph.connectImpl<sourcePortIndex, sourcePortSubIndex, destinationPortIndex, destinationPortSubIndex>(*src, *source_port, *destination, *destinationPort);
            });
            return ConnectionResult::SUCCESS;
        }

    public:
        // connect using the port index

        template<std::size_t destinationPortIndex, std::size_t destinationPortSubIndex, typename Destination>
        [[nodiscard]] auto
        to_internal(Destination &destination) {
            auto &destinationPort = inputPort<destinationPortIndex, PortType::ANY>(&destination);
            return to<Destination, std::remove_cvref_t<decltype(destinationPort)>, destinationPortIndex, destinationPortSubIndex>(destination, destinationPort);
        }

        template<std::size_t destinationPortIndex, std::size_t destinationPortSubIndex, typename Destination>
        [[nodiscard, deprecated("For internal use only, the one with the port name should be used")]] auto
        to(Destination &destination) {
            return to_internal<destinationPortIndex, destinationPortSubIndex, Destination>(destination);
        }

        template<std::size_t destinationPortIndex, typename Destination>
        [[nodiscard]] auto
        to(Destination &destination) {
            if constexpr (destinationPortIndex == gr::meta::default_message_port_index) {
                return to<Destination, decltype(destination.msgIn)>(destination, destination.msgIn);

            } else {
                return to<destinationPortIndex, meta::invalid_index, Destination>(destination);
            }
        }

        // connect using the port name

        template<fixed_string destinationPortName, std::size_t destinationPortSubIndex, typename Destination>
        [[nodiscard]] constexpr auto
        to(Destination &destination) {
            using destination_input_ports              = typename traits::block::all_input_ports<Destination>;
            constexpr std::size_t destinationPortIndex = meta::indexForName<destinationPortName, destination_input_ports>();
            if constexpr (destinationPortIndex == meta::invalid_index) {
                meta::print_types<meta::message_type<"There is no input port with the specified name in this destination block">, Destination, meta::message_type<destinationPortName>,
                                  meta::message_type<"These are the known names:">, traits::block::all_input_port_names<Destination>, meta::message_type<"Full ports info:">, destination_input_ports>
                        port_not_found_error{};
            }
            return to_internal<destinationPortIndex, destinationPortSubIndex, Destination>(destination);
        }

        template<fixed_string destinationPortName, typename Destination>
        [[nodiscard]] constexpr auto
        to(Destination &destination) {
            return to<destinationPortName, meta::invalid_index, Destination>(destination);
        }

        SourceConnector(const SourceConnector &) = delete;
        SourceConnector(SourceConnector &&)      = delete;
        SourceConnector &
        operator=(const SourceConnector &)
                = delete;
        SourceConnector &
        operator=(SourceConnector &&)
                = delete;
    };

public:
    Graph(Graph &)  = delete;
    Graph(Graph &&) = default;
    Graph()         = default;
    Graph &
    operator=(Graph &)
            = delete;
    Graph &
    operator=(Graph &&)
            = delete;

    /**
     * @return a list of all blocks contained in this graph
     * N.B. some 'blocks' may be (sub-)graphs themselves
     */
    [[nodiscard]] std::span<std::unique_ptr<BlockModel>>
    blocks() noexcept {
        return { _blocks };
    }

    /**
     * @return a list of all edges in this graph connecting blocks
     */
    [[nodiscard]] std::span<Edge>
    edges() noexcept {
        return { _edges };
    }

    BlockModel &
    addBlock(std::unique_ptr<BlockModel> block) {
        auto &new_block_ref = _blocks.emplace_back(std::move(block));
        new_block_ref->init(progress, ioThreadPool);
        // TODO: Should we connectChildMessagePorts for these blocks as well?
        return *new_block_ref.get();
    }

    template<BlockLike TBlock, typename... Args>
    auto &
    emplaceBlock(Args &&...args) { // TODO for review: do we still need this factory method or allow only pmt-map-type constructors (see below)
        static_assert(std::is_same_v<TBlock, std::remove_reference_t<TBlock>>);
        auto &new_block_ref = _blocks.emplace_back(std::make_unique<BlockWrapper<TBlock>>(std::forward<Args>(args)...));
        auto  raw_ref       = static_cast<TBlock *>(new_block_ref->raw());
        raw_ref->init(progress, ioThreadPool);
        return *raw_ref;
    }

    template<BlockLike TBlock>
    auto &
    emplaceBlock(const property_map &initialSettings) {
        static_assert(std::is_same_v<TBlock, std::remove_reference_t<TBlock>>);
        auto      &new_block_ref = _blocks.emplace_back(std::make_unique<BlockWrapper<TBlock>>());
        auto       raw_ref       = static_cast<TBlock *>(new_block_ref->raw());
        const auto failed        = raw_ref->settings().set(initialSettings);
        if (!failed.empty()) {
            std::vector<std::string> keys;
            for (const auto &pair : failed) {
                keys.push_back(pair.first);
            }
            throw std::invalid_argument(fmt::format("initial Block settings could not be applied successfully - mismatched keys or value-type: {}\n", fmt::join(keys, ", ")));
        }
        raw_ref->init(progress, ioThreadPool);
        return *raw_ref;
    }

    // connect using the port index

    template<std::size_t sourcePortIndex, std::size_t sourcePortSubIndex, typename Source>
    [[nodiscard]] auto
    connect_internal(Source &source) {
        auto &port_or_collection = outputPort<sourcePortIndex, PortType::ANY>(&source);
        return SourceConnector<Source, std::remove_cvref_t<decltype(port_or_collection)>, sourcePortIndex, sourcePortSubIndex>(*this, source, port_or_collection);
    }

    template<std::size_t sourcePortIndex, std::size_t sourcePortSubIndex, typename Source>
    [[nodiscard, deprecated("The connect with the port name should be used")]] auto
    connect(Source &source) {
        return connect_internal<sourcePortIndex, sourcePortSubIndex, Source>(source);
    }

    template<std::size_t sourcePortIndex, typename Source>
    [[nodiscard]] auto
    connect(Source &source) {
        if constexpr (sourcePortIndex == meta::default_message_port_index) {
            return SourceConnector<Source, decltype(source.msgOut), meta::invalid_index, meta::invalid_index>(*this, source, source.msgOut);
        } else {
            return connect<sourcePortIndex, meta::invalid_index, Source>(source);
        }
    }

    // connect using the port name

    template<fixed_string sourcePortName, std::size_t sourcePortSubIndex, typename Source>
    [[nodiscard]] auto
    connect(Source &source) {
        using source_output_ports             = typename traits::block::all_output_ports<Source>;
        constexpr std::size_t sourcePortIndex = meta::indexForName<sourcePortName, source_output_ports>();
        if constexpr (sourcePortIndex == meta::invalid_index) {
            meta::print_types<meta::message_type<"There is no output port with the specified name in this source block">, Source, meta::message_type<sourcePortName>,
                              meta::message_type<"These are the known names:">, traits::block::all_output_port_names<Source>, meta::message_type<"Full ports info:">, source_output_ports>
                    port_not_found_error{};
        }
        return connect_internal<sourcePortIndex, sourcePortSubIndex, Source>(source);
    }

    template<fixed_string sourcePortName, typename Source>
    [[nodiscard]] auto
    connect(Source &source) {
        return connect<sourcePortName, meta::invalid_index, Source>(source);
    }

    // dynamic/runtime connections

    template<typename Source, typename Destination>
        requires(!std::is_pointer_v<std::remove_cvref_t<Source>> && !std::is_pointer_v<std::remove_cvref_t<Destination>>)
    ConnectionResult
    connect(Source &sourceBlockRaw, PortIndexDefinition<std::size_t> sourcePortDefinition, Destination &destinationBlockRaw, PortIndexDefinition<std::size_t> destinationPortDefinition,
            std::size_t minBufferSize = 65536, std::int32_t weight = 0, std::string_view edgeName = "unnamed edge") {
        auto result = findBlock(sourceBlockRaw)
                              ->dynamicOutputPort(sourcePortDefinition.topLevel, sourcePortDefinition.subIndex)
                              .connect(findBlock(destinationBlockRaw)->dynamicInputPort(destinationPortDefinition.topLevel, destinationPortDefinition.subIndex));
        if (result == ConnectionResult::SUCCESS) {
            auto *sourceBlock      = findBlock(sourceBlockRaw).get();
            auto *destinationBlock = findBlock(destinationBlockRaw).get();
            _edges.emplace_back(sourceBlock, sourcePortDefinition, destinationBlock, destinationPortDefinition, minBufferSize, weight, edgeName);
        }
        return result;
    }

    template<typename Source, typename Destination>
        requires(!std::is_pointer_v<std::remove_cvref_t<Source>> && !std::is_pointer_v<std::remove_cvref_t<Destination>>)
    ConnectionResult
    connect(Source &sourceBlockRaw, PortIndexDefinition<std::string> sourcePortDefinition, Destination &destinationBlockRaw, PortIndexDefinition<std::string> destinationPortDefinition,
            std::size_t minBufferSize = 65536, std::int32_t weight = 0, std::string_view edgeName = "unnamed edge") {
        auto sourcePortIndex      = this->findBlock(sourceBlockRaw)->dynamicOutputPortIndex(sourcePortDefinition.topLevel);
        auto destinationPortIndex = this->findBlock(destinationBlockRaw)->dynamicInputPortIndex(destinationPortDefinition.topLevel);
        return connect(sourceBlockRaw, { sourcePortIndex, sourcePortDefinition.subIndex }, destinationBlockRaw, { destinationPortIndex, destinationPortDefinition.subIndex }, minBufferSize, weight,
                       edgeName);
    }

    template<typename Anything>
    void
    processMessages(MsgPortInNamed<"__FromChildren"> & /*port*/, std::span<const Anything> /*input*/) {
        static_assert(meta::always_false<Anything>, "This is not called, children are processed in processScheduledMessages");
    }

    bool
    performConnections() {
        auto result = std::all_of(_connectionDefinitions.begin(), _connectionDefinitions.end(),
                                  [this](auto &connection_definition) { return connection_definition(*this) == ConnectionResult::SUCCESS; });
        if (result) {
            _connectionDefinitions.clear();
        }
        return result;
    }

    template<typename F> // TODO: F must be constraint by a descriptive concept
    void
    forEachBlock(F &&f) const {
        std::ranges::for_each(_blocks, [f](const auto &block_ptr) { std::invoke(f, *block_ptr.get()); });
    }

    template<typename F> // TODO: F must be constraint by a descriptive concept
    void
    forEachEdge(F &&f) const {
        std::ranges::for_each(_edges, [f](const auto &edge) { std::invoke(f, edge); });
    }
};

static_assert(BlockLike<Graph>);

/*******************************************************************************************************/
/**************************** begin of SIMD-Merged Graph Implementation ********************************/
/*******************************************************************************************************/

/**
 * Concepts and class for Merging Blocks to Sub-Graph Functionality
 *
 * This code provides a way to merge blocks of processing units in a flow-graph for efficient computation.
 * The merging occurs at compile-time, enabling the execution performance to be much better than running
 * each constituent block individually.
 *
 * Concepts:
 *  - `SourceBlockLike`: Represents a source block with processing capability and at least one output port.
 *  - `SinkBlockLike`: Represents a sink block with processing capability and at least one input port.
 *
 * Key Features:
 *  - `MergedGraph` class: Combines a source and sink block into a new unit, connecting them via specified
 *    output and input port indices.
 *  - The merged block can be efficiently optimized at compile-time.
 *  - Each `MergedGraph` instance has a unique ID and name, aiding in debugging and identification.
 *  - The merging works seamlessly for blocks that have single or multiple output ports.
 *  - It allows for SIMD optimizations if the constituent blocks support it.
 *
 * Utility Functions:
 *  - `mergeByIndex()`: A utility function to merge two blocks based on specified port indices.
 *    It checks if the output port of the source block and the input port of the sink block have matching types.
 *
 * Examples:
 *  This enables you to create a flow-graph where you merge blocks to create optimized processing paths.
 *  Example usage can be found in the documentation of `mergeByIndex()`.
 *
 * Dependencies:
 *  - Relies on various traits and meta-programming utilities for type introspection and compile-time checks.
 *
 * Note:
 *  - The implementation of the actual processing logic (e.g., `processOne()`, `processOne_simd()`, etc.)
 *    and their SIMD variants is specific to the logic and capabilities of the blocks being merged.
 *
 * Limitations:
 *  - Currently, SIMD support for multiple output ports is not implemented.
 */

template<typename TBlock>
concept SourceBlockLike = traits::block::can_processOne<TBlock> and traits::block::template stream_output_port_types<TBlock>::size > 0;

static_assert(not SourceBlockLike<int>);

template<typename TBlock>
concept SinkBlockLike = traits::block::can_processOne<TBlock> and traits::block::template stream_input_port_types<TBlock>::size > 0;

static_assert(not SinkBlockLike<int>);

template<SourceBlockLike Left, SinkBlockLike Right, std::size_t OutId, std::size_t InId>
class MergedGraph
    : public Block<MergedGraph<Left, Right, OutId, InId>, meta::concat<typename traits::block::stream_input_ports<Left>, meta::remove_at<InId, typename traits::block::stream_input_ports<Right>>>,
                   meta::concat<meta::remove_at<OutId, typename traits::block::stream_output_ports<Left>>, typename traits::block::stream_output_ports<Right>>> {
    static std::atomic_size_t _unique_id_counter;

public:
    const std::size_t unique_id   = _unique_id_counter++;
    const std::string unique_name = fmt::format("MergedGraph<{}:{},{}:{}>#{}", gr::meta::type_name<Left>(), OutId, gr::meta::type_name<Right>(), InId, unique_id);

private:
    // copy-paste from above, keep in sync
    using base = Block<MergedGraph<Left, Right, OutId, InId>, meta::concat<typename traits::block::stream_input_ports<Left>, meta::remove_at<InId, typename traits::block::stream_input_ports<Right>>>,
                       meta::concat<meta::remove_at<OutId, typename traits::block::stream_output_ports<Left>>, typename traits::block::stream_output_ports<Right>>>;

    Left  left;
    Right right;

    // merged_work_chunk_size, that's what friends are for
    friend base;

    template<SourceBlockLike, SinkBlockLike, std::size_t, std::size_t>
    friend class MergedGraph;

    // returns the minimum of all internal max_samples port template parameters
    static constexpr std::size_t
    merged_work_chunk_size() noexcept {
        constexpr std::size_t left_size = []() {
            if constexpr (requires {
                              { Left::merged_work_chunk_size() } -> std::same_as<std::size_t>;
                          }) {
                return Left::merged_work_chunk_size();
            } else {
                return std::dynamic_extent;
            }
        }();
        constexpr std::size_t right_size = []() {
            if constexpr (requires {
                              { Right::merged_work_chunk_size() } -> std::same_as<std::size_t>;
                          }) {
                return Right::merged_work_chunk_size();
            } else {
                return std::dynamic_extent;
            }
        }();
        return std::min({ traits::block::stream_input_ports<Right>::template apply<traits::port::max_samples>::value,
                          traits::block::stream_output_ports<Left>::template apply<traits::port::max_samples>::value, left_size, right_size });
    }

    template<std::size_t I>
    constexpr auto
    apply_left(std::size_t offset, auto &&input_tuple) noexcept {
        return [&]<std::size_t... Is>(std::index_sequence<Is...>) {
            return invokeProcessOneWithOrWithoutOffset(left, offset, std::get<Is>(std::forward<decltype(input_tuple)>(input_tuple))...);
        }(std::make_index_sequence<I>());
    }

    template<std::size_t I, std::size_t J>
    constexpr auto
    apply_right(std::size_t offset, auto &&input_tuple, auto &&tmp) noexcept {
        return [&]<std::size_t... Is, std::size_t... Js>(std::index_sequence<Is...>, std::index_sequence<Js...>) {
            constexpr std::size_t first_offset  = traits::block::stream_input_port_types<Left>::size;
            constexpr std::size_t second_offset = traits::block::stream_input_port_types<Left>::size + sizeof...(Is);
            static_assert(second_offset + sizeof...(Js) == std::tuple_size_v<std::remove_cvref_t<decltype(input_tuple)>>);
            return invokeProcessOneWithOrWithoutOffset(right, offset, std::get<first_offset + Is>(std::forward<decltype(input_tuple)>(input_tuple))..., std::forward<decltype(tmp)>(tmp),
                                                       std::get<second_offset + Js>(input_tuple)...);
        }(std::make_index_sequence<I>(), std::make_index_sequence<J>());
    }

public:
    using TInputPortTypes  = typename traits::block::stream_input_port_types<base>;
    using TOutputPortTypes = typename traits::block::stream_output_port_types<base>;
    using TReturnType      = typename traits::block::stream_return_type<base>;

    constexpr MergedGraph(Left l, Right r) : left(std::move(l)), right(std::move(r)) {}

    // if the left block (source) implements available_samples (a customization point), then pass the call through
    friend constexpr std::size_t
    available_samples(const MergedGraph &self) noexcept
        requires requires(const Left &l) {
            { available_samples(l) } -> std::same_as<std::size_t>;
        }
    {
        return available_samples(self.left);
    }

    template<meta::any_simd... Ts>
        requires traits::block::can_processOne_simd<Left> and traits::block::can_processOne_simd<Right>
    constexpr meta::simdize<TReturnType, meta::simdize_size_v<std::tuple<Ts...>>>
    processOne(std::size_t offset, const Ts &...inputs) {
        static_assert(traits::block::stream_output_port_types<Left>::size == 1, "TODO: SIMD for multiple output ports not implemented yet");
        return apply_right<InId, traits::block::stream_input_port_types<Right>::size() - InId - 1>(offset, std::tie(inputs...),
                                                                                                   apply_left<traits::block::stream_input_port_types<Left>::size()>(offset, std::tie(inputs...)));
    }

    constexpr auto
    processOne_simd(std::size_t offset, auto N)
        requires traits::block::can_processOne_simd<Right>
    {
        if constexpr (requires(Left &l) {
                          { l.processOne_simd(offset, N) };
                      }) {
            return invokeProcessOneWithOrWithoutOffset(right, offset, left.processOne_simd(offset, N));
        } else if constexpr (requires(Left &l) {
                                 { l.processOne_simd(N) };
                             }) {
            return invokeProcessOneWithOrWithoutOffset(right, offset, left.processOne_simd(N));
        } else {
            using LeftResult = typename traits::block::stream_return_type<Left>;
            using V          = meta::simdize<LeftResult, N>;
            alignas(stdx::memory_alignment_v<V>) LeftResult tmp[V::size()];
            for (std::size_t i = 0UZ; i < V::size(); ++i) {
                tmp[i] = invokeProcessOneWithOrWithoutOffset(left, offset + i);
            }
            return invokeProcessOneWithOrWithoutOffset(right, offset, V(tmp, stdx::vector_aligned));
        }
    }

    template<typename... Ts>
    // Nicer error messages for the following would be good, but not at the expense of breaking can_processOne_simd.
        requires(TInputPortTypes::template are_equal<std::remove_cvref_t<Ts>...>)
    constexpr TReturnType
    processOne(std::size_t offset, Ts &&...inputs) {
        // if (sizeof...(Ts) == 0) we could call `return processOne_simd(integral_constant<size_t, width>)`. But if
        // the caller expects to process *one* sample (no inputs for the caller to explicitly
        // request simd), and we process more, we risk inconsistencies.
        if constexpr (traits::block::stream_output_port_types<Left>::size == 1) {
            // only the result from the right block needs to be returned
            return apply_right<InId, traits::block::stream_input_port_types<Right>::size() - InId
                                             - 1>(offset, std::forward_as_tuple(std::forward<Ts>(inputs)...),
                                                  apply_left<traits::block::stream_input_port_types<Left>::size()>(offset, std::forward_as_tuple(std::forward<Ts>(inputs)...)));

        } else {
            // left produces a tuple
            auto left_out  = apply_left<traits::block::stream_input_port_types<Left>::size()>(offset, std::forward_as_tuple(std::forward<Ts>(inputs)...));
            auto right_out = apply_right<InId, traits::block::stream_input_port_types<Right>::size() - InId - 1>(offset, std::forward_as_tuple(std::forward<Ts>(inputs)...),
                                                                                                                 std::move(std::get<OutId>(left_out)));

            if constexpr (traits::block::stream_output_port_types<Left>::size == 2 && traits::block::stream_output_port_types<Right>::size == 1) {
                return std::make_tuple(std::move(std::get<OutId ^ 1>(left_out)), std::move(right_out));

            } else if constexpr (traits::block::stream_output_port_types<Left>::size == 2) {
                return std::tuple_cat(std::make_tuple(std::move(std::get<OutId ^ 1>(left_out))), std::move(right_out));

            } else if constexpr (traits::block::stream_output_port_types<Right>::size == 1) {
                return [&]<std::size_t... Is, std::size_t... Js>(std::index_sequence<Is...>, std::index_sequence<Js...>) {
                    return std::make_tuple(std::move(std::get<Is>(left_out))..., std::move(std::get<OutId + 1 + Js>(left_out))..., std::move(right_out));
                }(std::make_index_sequence<OutId>(), std::make_index_sequence<traits::block::stream_output_port_types<Left>::size - OutId - 1>());

            } else {
                return [&]<std::size_t... Is, std::size_t... Js, std::size_t... Ks>(std::index_sequence<Is...>, std::index_sequence<Js...>, std::index_sequence<Ks...>) {
                    return std::make_tuple(std::move(std::get<Is>(left_out))..., std::move(std::get<OutId + 1 + Js>(left_out))..., std::move(std::get<Ks>(right_out)...));
                }(std::make_index_sequence<OutId>(), std::make_index_sequence<traits::block::stream_output_port_types<Left>::size - OutId - 1>(),
                       std::make_index_sequence<Right::output_port_types::size>());
            }
        }
    } // end:: processOne

    work::Result
    work(std::size_t requested_work) noexcept {
        return base::work(requested_work);
    }
};

template<SourceBlockLike Left, SinkBlockLike Right, std::size_t OutId, std::size_t InId>
inline std::atomic_size_t MergedGraph<Left, Right, OutId, InId>::_unique_id_counter{ 0UZ };

/**
 * This methods can merge simple blocks that are defined via a single `auto processOne(..)` producing a
 * new `merged` node, bypassing the dynamic run-time buffers.
 * Since the merged node can be highly optimised during compile-time, it's execution performance is usually orders
 * of magnitude more efficient than executing a cascade of the same constituent blocks. See the benchmarks for details.
 * This function uses the connect-by-port-ID API.
 *
 * Example:
 * @code
 * // declare flow-graph: 2 x in -> adder -> scale-by-2 -> scale-by-minus1 -> output
 * auto merged = merge_by_index<0, 0>(scale<int, -1>(), merge_by_index<0, 0>(scale<int, 2>(), adder<int>()));
 *
 * // execute graph
 * std::array<int, 4> a = { 1, 2, 3, 4 };
 * std::array<int, 4> b = { 10, 10, 10, 10 };
 *
 * int                r = 0;
 * for (std::size_t i = 0; i < 4; ++i) {
 *     r += merged.processOne(a[i], b[i]);
 * }
 * @endcode
 */
template<std::size_t OutId, std::size_t InId, SourceBlockLike A, SinkBlockLike B>
constexpr auto
mergeByIndex(A &&a, B &&b) -> MergedGraph<std::remove_cvref_t<A>, std::remove_cvref_t<B>, OutId, InId> {
    if constexpr (!std::is_same_v<typename traits::block::stream_output_port_types<std::remove_cvref_t<A>>::template at<OutId>,
                                  typename traits::block::stream_input_port_types<std::remove_cvref_t<B>>::template at<InId>>) {
        gr::meta::print_types<gr::meta::message_type<"OUTPUT_PORTS_ARE:">, typename traits::block::stream_output_port_types<std::remove_cvref_t<A>>, std::integral_constant<int, OutId>,
                              typename traits::block::stream_output_port_types<std::remove_cvref_t<A>>::template at<OutId>,

                              gr::meta::message_type<"INPUT_PORTS_ARE:">, typename traits::block::stream_input_port_types<std::remove_cvref_t<A>>, std::integral_constant<int, InId>,
                              typename traits::block::stream_input_port_types<std::remove_cvref_t<A>>::template at<InId>>{};
    }
    return { std::forward<A>(a), std::forward<B>(b) };
}

/**
 * This methods can merge simple blocks that are defined via a single `auto processOne(..)` producing a
 * new `merged` node, bypassing the dynamic run-time buffers.
 * Since the merged node can be highly optimised during compile-time, it's execution performance is usually orders
 * of magnitude more efficient than executing a cascade of the same constituent blocks. See the benchmarks for details.
 * This function uses the connect-by-port-name API.
 *
 * Example:
 * @code
 * // declare flow-graph: 2 x in -> adder -> scale-by-2 -> output
 * auto merged = merge<"scaled", "addend1">(scale<int, 2>(), adder<int>());
 *
 * // execute graph
 * std::array<int, 4> a = { 1, 2, 3, 4 };
 * std::array<int, 4> b = { 10, 10, 10, 10 };
 *
 * int                r = 0;
 * for (std::size_t i = 0; i < 4; ++i) {
 *     r += merged.processOne(a[i], b[i]);
 * }
 * @endcode
 */
template<fixed_string OutName, fixed_string InName, SourceBlockLike A, SinkBlockLike B>
constexpr auto
merge(A &&a, B &&b) {
    constexpr int OutIdUnchecked = meta::indexForName<OutName, typename traits::block::stream_output_ports<A>>();
    constexpr int InIdUnchecked  = meta::indexForName<InName, typename traits::block::stream_input_ports<B>>();
    static_assert(OutIdUnchecked != -1);
    static_assert(InIdUnchecked != -1);
    constexpr auto OutId = static_cast<std::size_t>(OutIdUnchecked);
    constexpr auto InId  = static_cast<std::size_t>(InIdUnchecked);
    static_assert(std::same_as<typename traits::block::stream_output_port_types<std::remove_cvref_t<A>>::template at<OutId>,
                               typename traits::block::stream_input_port_types<std::remove_cvref_t<B>>::template at<InId>>,
                  "Port types do not match");
    return MergedGraph<std::remove_cvref_t<A>, std::remove_cvref_t<B>, OutId, InId>{ std::forward<A>(a), std::forward<B>(b) };
}

/*******************************************************************************************************/
/**************************** end of SIMD-Merged Graph Implementation **********************************/
/*******************************************************************************************************/

// TODO: add nicer enum formatter
inline std::ostream &
operator<<(std::ostream &os, const ConnectionResult &value) {
    return os << static_cast<int>(value);
}

inline std::ostream &
operator<<(std::ostream &os, const PortType &value) {
    return os << static_cast<int>(value);
}

inline std::ostream &
operator<<(std::ostream &os, const PortDirection &value) {
    return os << static_cast<int>(value);
}

template<PortDomainLike T>
inline std::ostream &
operator<<(std::ostream &os, const T &value) {
    return os << value.Name;
}

#if HAVE_SOURCE_LOCATION
inline auto
this_source_location(std::source_location l = std::source_location::current()) {
    return fmt::format("{}:{},{}", l.file_name(), l.line(), l.column());
}
#else
inline auto
this_source_location() {
    return "not yet implemented";
}
#endif // HAVE_SOURCE_LOCATION

} // namespace gr

REFL_TYPE(gr::Graph) REFL_END // minimal reflection declaration

#endif // include guard