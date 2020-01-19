
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "att85/ssd1306/detail/toGDDRAM.hpp"

#define ATT85_SSD1306_GDDRAM_8_BYTES(HumanSeq) \
    detail::toGDDRAM(HumanSeq, 0), \
    detail::toGDDRAM(HumanSeq, 1), \
    detail::toGDDRAM(HumanSeq, 2), \
    detail::toGDDRAM(HumanSeq, 3), \
    detail::toGDDRAM(HumanSeq, 4), \
    detail::toGDDRAM(HumanSeq, 5), \
    detail::toGDDRAM(HumanSeq, 6), \
    detail::toGDDRAM(HumanSeq, 7),
    
#define ATT85_SSD1306_GDDRAM_ARRAY_8_BYTES(HumanSeq) \
constexpr static uint8_t HumanSeq ##_## gddram [] PROGMEM = {  \
    ATT85_SSD1306_GDDRAM_8_BYTES(HumanSeq) \
};

#define ATT85_SSD1306_GDDRAM_64_BYTES(HumanSeq) \
    detail::toGDDRAM(HumanSeq, 0, 0), \
    detail::toGDDRAM(HumanSeq, 1, 0), \
    detail::toGDDRAM(HumanSeq, 2, 0), \
    detail::toGDDRAM(HumanSeq, 3, 0), \
    detail::toGDDRAM(HumanSeq, 0, 1), \
    detail::toGDDRAM(HumanSeq, 1, 1), \
    detail::toGDDRAM(HumanSeq, 2, 1), \
    detail::toGDDRAM(HumanSeq, 3, 1), \
    detail::toGDDRAM(HumanSeq, 0, 2), \
    detail::toGDDRAM(HumanSeq, 1, 2), \
    detail::toGDDRAM(HumanSeq, 2, 2), \
    detail::toGDDRAM(HumanSeq, 3, 2), \
    detail::toGDDRAM(HumanSeq, 0, 3), \
    detail::toGDDRAM(HumanSeq, 1, 3), \
    detail::toGDDRAM(HumanSeq, 2, 3), \
    detail::toGDDRAM(HumanSeq, 3, 3), \
    detail::toGDDRAM(HumanSeq, 0, 4), \
    detail::toGDDRAM(HumanSeq, 1, 4), \
    detail::toGDDRAM(HumanSeq, 2, 4), \
    detail::toGDDRAM(HumanSeq, 3, 4), \
    detail::toGDDRAM(HumanSeq, 0, 5), \
    detail::toGDDRAM(HumanSeq, 1, 5), \
    detail::toGDDRAM(HumanSeq, 2, 5), \
    detail::toGDDRAM(HumanSeq, 3, 5), \
    detail::toGDDRAM(HumanSeq, 0, 6), \
    detail::toGDDRAM(HumanSeq, 1, 6), \
    detail::toGDDRAM(HumanSeq, 2, 6), \
    detail::toGDDRAM(HumanSeq, 3, 6), \
    detail::toGDDRAM(HumanSeq, 0, 7), \
    detail::toGDDRAM(HumanSeq, 1, 7), \
    detail::toGDDRAM(HumanSeq, 2, 7), \
    detail::toGDDRAM(HumanSeq, 3, 7), \
    detail::toGDDRAM(HumanSeq, 0, 8), \
    detail::toGDDRAM(HumanSeq, 1, 8), \
    detail::toGDDRAM(HumanSeq, 2, 8), \
    detail::toGDDRAM(HumanSeq, 3, 8), \
    detail::toGDDRAM(HumanSeq, 0, 9), \
    detail::toGDDRAM(HumanSeq, 1, 9), \
    detail::toGDDRAM(HumanSeq, 2, 9), \
    detail::toGDDRAM(HumanSeq, 3, 9), \
    detail::toGDDRAM(HumanSeq, 0, 10), \
    detail::toGDDRAM(HumanSeq, 1, 10), \
    detail::toGDDRAM(HumanSeq, 2, 10), \
    detail::toGDDRAM(HumanSeq, 3, 10), \
    detail::toGDDRAM(HumanSeq, 0, 11), \
    detail::toGDDRAM(HumanSeq, 1, 11), \
    detail::toGDDRAM(HumanSeq, 2, 11), \
    detail::toGDDRAM(HumanSeq, 3, 11), \
    detail::toGDDRAM(HumanSeq, 0, 12), \
    detail::toGDDRAM(HumanSeq, 1, 12), \
    detail::toGDDRAM(HumanSeq, 2, 12), \
    detail::toGDDRAM(HumanSeq, 3, 12), \
    detail::toGDDRAM(HumanSeq, 0, 13), \
    detail::toGDDRAM(HumanSeq, 1, 13), \
    detail::toGDDRAM(HumanSeq, 2, 13), \
    detail::toGDDRAM(HumanSeq, 3, 13), \
    detail::toGDDRAM(HumanSeq, 0, 14), \
    detail::toGDDRAM(HumanSeq, 1, 14), \
    detail::toGDDRAM(HumanSeq, 2, 14), \
    detail::toGDDRAM(HumanSeq, 3, 14), \
    detail::toGDDRAM(HumanSeq, 0, 15), \
    detail::toGDDRAM(HumanSeq, 1, 15), \
    detail::toGDDRAM(HumanSeq, 2, 15), \
    detail::toGDDRAM(HumanSeq, 3, 15), \

#define ATT85_SSD1306_GDDRAM_ARRAY_64_BYTES(HumanSeq) \
constexpr static uint8_t HumanSeq ##_## gddram [] PROGMEM = { \
    ATT85_SSD1306_GDDRAM_64_BYTES(HumanSeq) \
};
