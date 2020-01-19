
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/send_str.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Display, typename Font, char... Cs>
constexpr void out(compiletime::c_str<Cs...>) 
{ send<Display, Font>(compiletime::c_str<Cs...>{}); }

}}}
