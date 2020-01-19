
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 { namespace ssd1306 {

//ChargePumpPolicy
//
//Disable the Charge Pump Regulator.
struct DisableChargePump {};

struct DefDisplayClock {};

//ClearOnInitPolicy
//
//Policy to choose if the display will be clear on the
//initialization. The default is to clear the entire display with a
//blank char because the GDDRAM is a SRAM memory and when the device
//is power off the data stored in the memory is eventually lost. This
//means that the user can obtain garbage in the display when he powers
//on the circuit. It is possible that the programmer can achieve an
//optimization filling the spaces that are not used with information
//to be put on the display when the program is showing the first
//screen, this approach will fill the entire screen eventually. The
//argument NoClearOnInit can be used in this scenario.
struct ClearOnInit{};
struct NoClearOnInit{};

}}
