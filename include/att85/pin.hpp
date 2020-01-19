
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <avr/sfr_defs.h>

#include <inttypes.h>

namespace att85 {

struct portB { static const uint8_t addr = 0x18; };

template<typename Reg>
struct ddr;

template<>
struct ddr<portB> { constexpr static uint8_t addr = 0x17; };

struct pb0 : portB {
    using port = portB;
    static const uint8_t num = 0;
};
using mosi = pb0;
using di = pb0;
using sda = pb0;
using ain0 = pb0;
using oc0a = pb0;
using comp_oc1a = pb0;
using aref = pb0;
using pcint0 = pb0;

struct pb1 : portB {
    using port = portB;
    static const uint8_t num = 1;
};
using miso = pb1;
using ain1 = pb1;
using oc0b = pb1;
using oc1a = pb1;
using pcint1 = pb1;

struct pb2 : portB {
    using port = portB;
    static const uint8_t num = 2;
};
using sck = pb2;
using usck = pb2;
using scl = pb2;
using adc1 = pb2;
using t0 = pb2;
using int0 = pb2;
using pcint2 = pb2;

struct pb3 : portB {
    using port = portB;
    static const uint8_t num = 3;
};

struct pb4 : portB {
    using port = portB;
    static const uint8_t num = 4;
};

struct pb5 : portB {
    using port = portB;
    static const uint8_t num = 5;
};

template<typename Pin>
[[gnu::always_inline]]
constexpr inline void high()
{ _SFR_IO8(Pin::port::addr) |= (1 << Pin::num); }

template<typename Pin>
inline void hi()
{ high<Pin>(); }

template<typename Pin>
[[gnu::always_inline]]
constexpr inline void low()
{ _SFR_IO8(Pin::port::addr) &= ~(1 << Pin::num); }

template<typename Pin>
inline void lo()
{ low<Pin>(); }

}
