
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 {

/// let `Δpolling` be the regular time interval to poll a buzzer
/// let `Δduration` be the signal duration
///
/// Duration = Δduration/Δpolling
///
/// For example, to declare a signal with a duration of 50ms when the
/// buzzer is polled at each 10ms, we can say that the Duration is the
/// factor 5 of 50ms, or using algebra we have the following equation:
///
/// Duration = 50ms / 10ms = 5
///
template<uint8_t Duration>
struct signal { static const uint8_t duration = Duration; };

//Represents a beep with a duration of Duration * Δpolling
template<uint8_t Duration>
struct beep : signal<Duration> {};
    
//Represents a pause with a duration of Duration * Δpolling
template<uint8_t Duration>
struct pause : signal<Duration> {};

}
