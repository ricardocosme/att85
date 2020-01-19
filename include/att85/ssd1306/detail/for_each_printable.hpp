
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "att85/ssd1306/detail/out_number.hpp"
#include "att85/ssd1306/detail/out_c_str.hpp"
#include "att85/ssd1306/detail/out_dynamic_c_str.hpp"

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Display, typename Font, typename T>
constexpr void for_each_printable(T& o)
{ out<Display, Font>(o); }
    
template<typename Display,
         typename Font,
         typename T,
         typename... Printables>
constexpr void for_each_printable(T& o, Printables... ps) {
    out<Display, Font>(o);
    for_each_printable<Display, Font>(ps...);
}

}}}
