
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

//This header is only intended to be used with sketches from Arduino

//It's recommended that you don't use this user friendly header if
//you're not using Arduino. Instead of include this file pick up and
//include the headers that are only necessary to your project.
//
//Important: The att85 is a C++17 library, you should check if your
//Arduino IDE uses an avr-gcc which has support to C++17. You may need
//to enable the C++17 standard editing the file
//`plataform.txt`. Search for `compiler.cpp.flags` and use the flag
//`-std=c++17`.
#include <att85/pin.hpp>
#include <att85/ssd1306/ssd1306.hpp>
#include <att85/type_traits.hpp>
#include <att85/utility.hpp>
