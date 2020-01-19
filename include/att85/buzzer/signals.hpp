
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <att85/buzzer/detail/signals.hpp>

#pragma once

namespace att85 { namespace buzzer { 

//Returns a beep with a duration of Duration
template<typename Duration>
constexpr auto beep(Duration)
{ return detail::beep_impl<Duration>{}; }

//Returns a pause with a duration of Duration
template<typename Duration>
constexpr auto pause(Duration)
{ return detail::pause_impl<Duration>{}; }

}}
