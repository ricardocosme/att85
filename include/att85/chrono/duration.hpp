
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/mpl/chars_to_int.hpp>

#include <stdint.h>

namespace att85 { namespace chrono { namespace literals {

//TODO 16bits
template<uint8_t v>
struct ms
{ static const uint8_t value = v; };

template<char... digits>
constexpr auto operator"" _ms()
{ return ms<mpl::chars_to_int<digits...>::value>{}; }

}}}
