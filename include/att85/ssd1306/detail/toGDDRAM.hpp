
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <avr/io.h>
#include <avr/pgmspace.h>

namespace att85 { namespace ssd1306 { namespace detail {

constexpr inline uint8_t toGDDRAM(const uint8_t* seq, uint8_t col) {
    uint8_t byte{0x00};
    for(int8_t r{7}; r >= 0; --r)
        byte |= (((seq[r] & (0x80 >> col)) << col) >> (7 - r));
    return byte;
}

constexpr inline uint8_t toGDDRAM(const uint8_t* seq, uint8_t page, uint8_t col) {
    uint8_t _byte{0x00};
    uint8_t pg = page * 8;
    for(int8_t r{7}; r >= 0; --r)
        _byte |= (((seq[pg + r] & (0x80 >> col)) << col) >> (7 - r));
    return _byte;
}

constexpr inline uint8_t toGDDRAM(const uint16_t* seq, uint8_t page, uint8_t col) {
    uint8_t byte{0x00};
    uint8_t pg = page * 8;
    for(int8_t r{7}; r >= 0; --r) {
        uint8_t seq_b = ((seq[pg + r] & (0x8000 >> col)) << col) >> 8;
        byte |= (seq_b >> (7 - r));
    }
    return byte;
}

}}}
