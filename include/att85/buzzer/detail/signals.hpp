
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <att85/pulse/pulse.hpp>

#pragma once

namespace att85 { namespace buzzer { namespace detail {

//Represents a beep with a duration of Duration
template<typename Duration>
struct beep_impl : pulse::high_t<Duration> {};
    
//Represents a pause with a duration of Duration
template<typename Duration>
struct pause_impl : pulse::low_t<Duration> {};

}}}

