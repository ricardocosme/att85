
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/pulse/pulse.hpp>

namespace att85 { namespace pulse { namespace detail {

template<typename TimerFor, typename Pulse, typename... Pulses>
struct out_pulses_impl;

template<typename TimerFor, typename Pulse, typename Timers>
inline void assign_timer(Timers& timers, uint8_t idx)
{
    //the previous timer must emit the signal that is relative to this
    //timer when it expires
    timers[idx+1].onexpire().high = Pulse::value;

    //constructs a new timer moving the onexpire function to preserve
    //the assignment located above
    timers[idx] = TimerFor{}(Pulse{}, timers[idx].onexpire());
}

template<typename TimerFor, typename Pulse>
struct out_pulses_impl<TimerFor, Pulse> {
    template<typename Timers>
    out_pulses_impl(Timers& timers) 
    { assign_timer<TimerFor, Pulse>(timers, 0); }
};
    
template<typename TimerFor, typename Pulse, typename... Pulses>
struct out_pulses_impl : out_pulses_impl<TimerFor, Pulses...> {
    template<typename Timers>
    out_pulses_impl(Timers& timers) : out_pulses_impl<TimerFor, Pulses...>(timers)
    { assign_timer<TimerFor, Pulse>(timers, sizeof...(Pulses)); }
};
    
template<typename TimeFor, typename... Pulses>
struct out_pulses;

// sizeof...(Pulses) == 0
template<typename TimerFor>
struct out_pulses<TimerFor> {
    template<typename Timers>
    out_pulses(Timers&) {}
};

template<typename TimerFor, typename... Pulses>
struct out_pulses : out_pulses_impl<TimerFor, Pulses...> {
    template<typename Timers>
    out_pulses(Timers& timers) : out_pulses_impl<TimerFor, Pulses...>{timers} {}
};

template<typename HighPulse, typename LowPulse>
struct out_pulse {
    template<typename Duration>
    void operator()(high_t<Duration>)
    { HighPulse{}(); }
    
    template<typename Duration>
    void operator()(low_t<Duration>)
    { LowPulse{}(); }
};

}}}
