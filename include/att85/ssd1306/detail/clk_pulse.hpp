
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/pin.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Scl>
[[gnu::always_inline]]
constexpr inline void clk_pulse() {
    high<Scl>();
    low<Scl>();
}

}}}
