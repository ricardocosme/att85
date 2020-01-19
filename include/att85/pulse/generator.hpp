
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/chrono/duration.hpp>
#include <att85/pulse/detail/out_pulse.hpp>
#include <att85/pulse/detail/timer_for.hpp>
#include <att85/pulse/pulse.hpp>
#include <att85/timer/deadline.hpp>

#include <util/atomic.h>

namespace att85 { namespace pulse {

using namespace ::att85::chrono::literals;

//pulse generator
//
//Generates a sequence of positive(High) and negative(Low) pulses. A
//high pulse is is emitted by a HighPulseOut function and a low pulse by a
//LowPulseOut function. The generator must be clocked at ClockTime and
//polled at each clock time period through the method poll(). The
//ClockTime determines the minimum duration(width) of a pulse. This
//abstractions is intendend to be used with a hardware timer(see
//att85/clock/clock.hpp to abstract a clock) to achieve an asynchronous
//approach to process sequences of pulses emitted through the method
//out(), which is a non-blocking call. The limit of pulses to be
//processed at one call to out() is determined by the parameter
//Capacity. Tip: the capacity can be the length of the maximum
//sequence emitted by the program.
//
// HighPulseOut: function that emits a high pulse. It must have the
// following signature: void()
//
// LowPulseOut: function that emits a low pulse. It must have the
// following signature: void()
//
// Init: function that initializes the generator. It must have the
// following signature: void()
//
// ClockTime: clock time period represented by a model of Duration(see
// att85/chrono/duration.hpp). The generator must be polled through a
// call to poll() at each clock time period.
//
// Capacity: the maximum length of a sequence of pulses to be emitted
// through one call to out(). 
//
// Example:
//   HighPulseOut can put 5V in PB3 and LowPulseOut can put 0V in
//   PB3. We could have the following:
//
//     struct HighPulseOut { void operator()() { PORTB |= (1 << PB3); } };
//     struct LowPulseOut { void operator()() { PORTB &= ~(1 << PB3); } };
//
//   Init can set the pin PB3 as an output pin:
//
//     struct Init  { void operator()() { DDRB |= (1 << PB3); } };
//
//   The generator can be clocked at 100Hz, or in another words, with
//   a clock time period of 10ms. This can be implemented as an
//   ISR(TIM1_COMPA_vect) that polls the generator at each 10ms. Note,
//   the timer must be configured by the programmer. See generator()
//   and clock/clock.hpp to abstract the clock.
//
//     auto gen = clk_generator<HighPulseOut, LowPulseOut>(10_ms);
//   
//     ISR(TIM1_COMPA_vect)
//     { gen.poll(); }
//
//   We can emit the rectangular wave below with the following call:
//
//     gen.out(hi(50_ms), low(100_ms), hi(50_ms));
//
// v(V)
//     ^  hi            hi
//  5V | -----         -----
//     | |   |         |   |
//     | |   |  low    |   |
//  0V |--   -----------   -----
//     ----------------------------> t(ms)
//      <50ms> <100ms> <50ms>
//
template<typename HighPulseOut,
         typename LowPulseOut,
         typename Init,
         typename ClockTime,
         uint8_t  Capacity = 3>
class generator_impl {
public:
    using high_pulse_out = HighPulseOut;
    using low_pulse_out = LowPulseOut;
    using clock_time = ClockTime;
    static const uint8_t capacity = Capacity;
private:
    using timer_t = timer::deadline<
        detail::out_pulse_on_expire<high_pulse_out, low_pulse_out>>;
    timer_t _timers[capacity]; //FIFO

    //we don't use 255 here to hint the compiler to use the bss
    //section for a global or static instance of a generator. See the
    //assignment at init().
    uint8_t _idx{0};
public:
    void init() {
        Init{}();
        
        //we don't have to do anything during the polling before a
        //call to out().
        _idx = 255;
    }
    
    void poll() { if(_idx < 255) _timers[_idx].down([&]{--_idx;}); }

    template<typename Pulse, typename... Pulses>
    void out(Pulse, Pulses...) {
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            _idx = sizeof...(Pulses);
            detail::out_pulse<high_pulse_out, low_pulse_out>{}(Pulse{});
            using timer_for_t = detail::timer_for<timer_t, clock_time>;
            _timers[_idx] = timer_for_t{}(Pulse{});
            detail::out_pulses<timer_for_t, Pulses...>{_timers};
        }
    }
};

//pulse generator
//
//Specialization for Capacity equals to 1. See above.
//
template<typename HighPulseOut,
         typename LowPulseOut,
         typename Init,
         typename ClockTime>
class generator_impl<HighPulseOut, LowPulseOut, Init, ClockTime, 1> {
public:    
    using high_pulse_out = HighPulseOut;
    using low_pulse_out = LowPulseOut;
    using clock_time = ClockTime;
    static const uint8_t capacity = 1;
private:    
    using timer_t = timer::deadline<low_pulse_out>;
    timer_t _timer;
public:
    void init() const { Init{}(); }
    
    void poll()
    { if(!_timer.expired()) _timer.down(); }

    template<typename Pulse>
    void out(Pulse) {
        //TODO For 16bits timers I have to answer if I need to protect
        //this block because the ISR can(?) be executed after the
        //assignment of the low/high part of the timer value(ticks).
        detail::out_pulse<high_pulse_out, low_pulse_out>{}(Pulse{});
        _timer = timer_t(Pulse::duration::value / ClockTime::value);
    }
};

//Builds a generator without the clock abstraction
template<typename HighPulseOut,
         typename LowPulseOut,
         typename Init,
         uint8_t  Capacity = 3,
         typename ClockTime>
constexpr auto clk_generator(ClockTime)
{
    return generator_impl<
        HighPulseOut,
        LowPulseOut,
        Init,
        ClockTime,
        Capacity>{};
}

//Adaptor to be used with the clock abstraction (see att85/clock/clock.hpp)
template<typename HighPulseOut,
         typename LowPulseOut,
         typename Init,
         uint8_t  Capacity = 3>
struct generator {
    template<typename ClockTime>
    using clocked_at = generator_impl<
        HighPulseOut, LowPulseOut, Init, ClockTime, Capacity>;
};

}}

