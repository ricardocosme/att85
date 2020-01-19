
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/buzzer/detail/hi_lo_sig.hpp>
#include <att85/buzzer/detail/init.hpp>
#include <att85/buzzer/signals.hpp>
#include <att85/pulse/generator.hpp>

namespace att85 { namespace buzzer {

using namespace ::att85::chrono::literals;

//Represents a buzzer connected to a pin defined by Pin (see
//att85/pin.hpp). This component must be polled[poll() see
//buzzer/buzzer.hpp] at a period of time defined by a clock time.
//
//See below buzzer_at to abstract the polling process through a clock
//abstraction.
//
//We must call init() before use the component.
//
//See buzzer for more informations.
template<typename Pin,
         typename ClockTime,
         uint8_t Capacity = 3>
struct clk_buzzer_at_impl : pulse::generator_impl<detail::HiSig<Pin>,
                                                  detail::LoSig<Pin>,
                                                  detail::Init<Pin>,
                                                  ClockTime,
                                                  Capacity>
{
    using base = pulse::generator_impl<detail::HiSig<Pin>,
                                       detail::LoSig<Pin>,
                                       detail::Init<Pin>,
                                       ClockTime,
                                       Capacity>;
    using base::base;
};

template<typename Pin, uint8_t capacity = 3, typename ClockTime>
constexpr auto clk_buzzer_at(ClockTime)
{ return clk_buzzer_at_impl<Pin, ClockTime, capacity>{}; }

//Represents a buzzer connected to a pin defined by Pin (see
//att85/pin.hpp). This component is clocked by a clock with a clock
//time defined by ClockTime.
//
//This abstraction represents a clocked buzzer to be instantiated and
//owned by a clock(see att85/clock/clock.hpp). The clock instantiates the
//buzzer with a clock time that is the period time that the buzzer is
//polled to process an sequence of beeps and pauses in an asynchronous
//approach. The clock time is also the base unit of time that is used
//to represent the duration of beeps and pauses. A signal(beep or
//pause) must have at least a duration greater or equal than the clock
//time.
//
//Pin represents a output pin of ATTiny85 that is connected to the
//positive pin of a buzzer component.
//
//Capacity is the maximum length of a sequence of signals(beeps and
//pauses) to be processed in an asynchronous approach.
//
//See clk_buzzer_at_impl for more informations.
template<typename Pin, uint8_t Capacity = 3>
struct buzzer_at {
    template<typename ClockTime>
    using clocked_at = clk_buzzer_at_impl<Pin, ClockTime, Capacity>;
};

}}
