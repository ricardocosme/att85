
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 { namespace pulse {

//see att85/chrono/duration.hpp
template<typename Duration>
struct pulse_base { using duration = Duration; };

//Represents a positive(high) pulse with a duration(width) of Duration
template<typename Duration>
struct high_t : pulse_base<Duration> {
    static constexpr bool value{true};
};
    
//Represents a negative(low) pulse with a duration(width) of Duration
template<typename Duration>
struct low_t : pulse_base<Duration> {
    static constexpr bool value{false};
};

template<typename Duration>
constexpr auto high(Duration)
{ return high_t<Duration>{}; }

template<typename Duration>
constexpr auto low(Duration)
{ return low_t<Duration>{}; }

}}
