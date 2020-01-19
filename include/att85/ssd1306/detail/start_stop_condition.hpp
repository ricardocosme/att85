
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/pin.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Sda, typename Scl>
constexpr inline void start_cond() {
    //Sda and Scl lines are low by precondition because these lines
    //are pulled up by external resistors.
    low<Sda>();
    low<Scl>();
}

template<typename Sda, typename Scl>
constexpr inline void stop_cond() {
    //TODO: Check this comment please. I understand that the Sda line
    //should be low by precondition because I should always have an
    //Acknowledge after a byte transmission, and this state implies in
    //Sda low.
    //
    // low<Sda>();
    high<Scl>();
    high<Sda>();
}

}}}
