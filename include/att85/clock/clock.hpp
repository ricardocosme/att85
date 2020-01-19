
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/chrono/duration.hpp>
#include <att85/clock/timer_params.hpp>
#include <att85/fusion/for_each.hpp>
#include <att85/fusion/vector.hpp>

extern "C" void __vector_3();
extern "C" void __vector_10();

#include <avr/interrupt.h>

namespace att85 {

template<uint8_t v>
struct MHz
{ static const uint8_t value = v; };

template<char... digits>
constexpr auto operator"" _MHz()
{ return MHz<mpl::chars_to_int<digits...>::value>{}; }

template<uint8_t v>
constexpr unsigned long long to_hz(MHz<v>)
{ return MHz<v>::value * 1000000; }

namespace clock {

struct Timer0 {};
struct Timer1 {};

constexpr void prescaling_src(int clk_divisor) {
    if(clk_divisor == 1)
        TCCR1 |= (1 << CTC1) | (1 << CS10);
    else if(clk_divisor == 2)
        TCCR1 |= (1 << CTC1) | (1 << CS11);
    else if(clk_divisor == 4)
        TCCR1 |= (1 << CTC1) | (1 << CS11) | (1 << CS10);
    else if(clk_divisor == 8)
        TCCR1 |= (1 << CTC1) | (1 << CS12);
    else if(clk_divisor == 16)
        TCCR1 |= (1 << CTC1) | (1 << CS12) | (1 << CS10);
    else if(clk_divisor == 32)
        TCCR1 |= (1 << CTC1) | (1 << CS12) | (1 << CS11);
    else if(clk_divisor == 64)
        TCCR1 |= (1 << CTC1) | (1 << CS12) | (1 << CS11) | (1 << CS10);
    else if(clk_divisor == 128)
        TCCR1 |= (1 << CTC1) | (1 << CS13);
    else if(clk_divisor == 256)
        TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS10);
    else if(clk_divisor == 512)
        TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS11);
    else if(clk_divisor == 1024)
        TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS12) | (1 << CS11);
    else if(clk_divisor == 2048)
        TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS12);
    else if(clk_divisor == 4096)
        TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS12);
    else if(clk_divisor == 8192)
        TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS12) | (1 << CS11);
    else if(clk_divisor == 16384)
        TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10);
}

//TODO Timer0
template<typename HardwareTimer,
         typename HardwareClockFreq,
         typename ClockTime,
         typename... Devices>
struct clock_t {
    using clock_time = ClockTime;
    using hdw_clock_freq = HardwareClockFreq;
    using timer = HardwareTimer;

    //TODO: getter for a specific device
    fusion::vector<Devices...> devices;
    
    static_assert(is_same<typename Devices::clock_time..., ClockTime>::value
                  , "A device must have the same clock time as the clock.");

    void init() {
        fusion::for_each(devices, [](auto&& d){ d.init(); });
        //TODO Compile time tests for timer_params
        // static_assert(timer_params(1E6, 1E-2).timer_cmp == 39,"");
        // static_assert(timer_params(1E6, 1E-2).clk_divisor == 256,"");
        auto [clk_divisor, timer_cmp] =
            timer_params(to_hz(hdw_clock_freq{}), to_seconds(clock_time{}));
        
        prescaling_src(clk_divisor);
        OCR1C = timer_cmp;
        
        TIMSK |= (1 << OCIE1A);
        
        sei();
    }
    
    void tick()
    { fusion::for_each(devices, [](auto&& d){ d.poll(); }); }
};

template<typename HardwareTimer,
         typename HardwareClockFreq,
         typename ClockTime,
         typename... Device>
struct clock_factory
    : clock_t<HardwareTimer,
              HardwareClockFreq,
              ClockTime,
              typename Device::template clocked_at<ClockTime>...>
{
    using base = clock_t<HardwareTimer,
                         HardwareClockFreq,
                         ClockTime,
                         typename Device::template clocked_at<ClockTime>...>;
    using base::base;
};
 
template<typename... Device,
         typename ClockTime,
         typename HardwareClockFreq = MHz<1>,
         typename HardwareTimer = Timer1>
constexpr auto clock(ClockTime ckt,
                     HardwareClockFreq = HardwareClockFreq{},
                     HardwareTimer tm = HardwareTimer{})
{ return clock_factory<HardwareTimer, HardwareClockFreq, ClockTime, Device...>{}; }

}} //namespace att85::clock

#define ATT85_CLOCK_ISR(clk)                                            \
    [[gnu::signal]] inline void __vector_clk_tick(){ clk.tick(); }      \
                                                                        \
    inline void dispatch(att85::true_type)                              \
    { __vector_clk_tick(); }                                            \
                                                                        \
    inline void dispatch(att85::false_type) {                           \
        asm volatile("rjmp __bad_interrupt");                           \
        __builtin_unreachable();                                        \
    }                                                                   \
                                                                        \
    void __vector_3()                                                   \
    { dispatch(att85::is_same<decltype(clk)::timer, att85::clock::Timer1>{}); } \
                                                                        \
    void __vector_10()                                                  \
    { dispatch(att85::is_same<decltype(clk)::timer, att85::clock::Timer0>{}); }

