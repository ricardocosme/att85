
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits.hpp>

namespace att85 {

template<typename T, typename R = remove_reference_t<T>&&>
constexpr R move(T&& o)
{ return static_cast<R>(o); }

//TODO: Review index_sequence
template<uint8_t... I>
struct index_sequence{};

//TODO: Review make_index_sequence
template<uint8_t N, uint8_t... I>
struct make_index_sequence;

template<uint8_t... I>
struct make_index_sequence<0, I...> {
    using type = index_sequence<I...>;
};

template<uint8_t N, uint8_t... I>
struct make_index_sequence : make_index_sequence<N-1, N-1, I...>{};

}
