
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "att85/utility.hpp"

namespace att85 { namespace ssd1306 { 

//You can specialize this class template to a specific Font and `char
//c` to offer a new printable char. Take a look at `font/*/chars.hpp`
//to see an example of usage.
template<typename Display, typename Font, char c>
struct send_char;

//We should do nothing to a null char('\0')
template<typename Display, typename Font>
struct send_char<Display, Font, '\0'>
{ constexpr static void send() { /*do nothing*/ } };

}}
