
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 {

template<bool, typename T1, typename>
struct conditional
{ using type = T1; };

template<typename T1, typename T2>
struct conditional<false, T1, T2>
{ using type = T2; };

template<bool B, typename T1, typename T2>
using conditional_t = typename conditional<B, T1, T2>::type;

}
