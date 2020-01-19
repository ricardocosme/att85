
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits/integral_constant.hpp>
#include <att85/type_traits/is_destructible.hpp>

namespace att85 {

//Only for avr-gcc
template<typename T>
struct is_trivially_destructible
    : integral_constant<bool, is_destructible<T>::value
                        && __has_trivial_destructor(T)>
{};

}
