
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits/integral_constant.hpp>
#include <att85/type_traits/is_reference.hpp>
#include <att85/type_traits/is_void.hpp>

namespace att85 {

template<typename T, bool = !is_void<T>::value && !is_reference<T>::value>
struct add_rvalue_reference;

template<typename T>
struct add_rvalue_reference<T, true> { using type = T&&; };

template<typename T>
struct add_rvalue_reference<T, false> { using type = T; };

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

}
