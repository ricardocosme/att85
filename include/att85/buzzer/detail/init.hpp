
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/pin.hpp>

#include <avr/sfr_defs.h>

namespace att85 { namespace buzzer { namespace detail {

template<typename Pin>
struct Init {
    //sets Pin as output
    void operator()() const
    { _SFR_IO8(ddr<typename Pin::port>::addr) |= (1 << Pin::num); }
};

}}}
