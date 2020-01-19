
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/mpl/pow.hpp>

#include <stdint.h>

namespace att85 { namespace mpl {

//TODO 16bits
template<char... digits>
struct chars_to_int;
    
template<char digit, char... digits>
struct chars_to_int<digit, digits...> {
    static const uint8_t exp = sizeof...(digits);
    //TODO Can I use 48 as a safe offset? (ASCII table)
    static const uint8_t value =
        ((digit - 48) * mpl::pow<10, exp>::value)
        + chars_to_int<digits...>::value;
};

template<>
struct chars_to_int<>
{ static const uint8_t value = 0; };

}}

