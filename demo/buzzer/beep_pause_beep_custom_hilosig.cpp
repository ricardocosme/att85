
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <att85/pulse/generator.hpp>
#include <att85/clock/clock.hpp>

using namespace att85;
using namespace att85::pulse;

struct HighPulse { void operator()() { PORTB |= (1 << PB3); } };
struct LowPulse { void operator()() { PORTB &= ~(1 << PB3); } };
struct Init  { void operator()() { DDRB |= (1 << PB3); } };

//defines a clock of 100Hz and a buzzer connected to pin PB3 that is
//clocked at this frequency.
auto clk = clock::clock<
    generator<HighPulse, LowPulse, Init> //device clocked by this clock. It is polled at
                                  //each 10ms to process sequences of beeps and
                                 //pauses in an asynchronous approach.
>(10_ms, //clock time of 10ms (100Hz)
  1_MHz); //defines the hardware clock. BTW, 1_MHz is the default
          //value. For example, if your uC is running at 8MHz, then
          //you must pass the value 8_MHz.
  

//registers the clock as an ISR(Interrupt Service Routine)
ATT85_CLOCK_ISR(clk)

int main() {
    //setup the clock using a timer of ATtiny85
    clk.init();

    //outputs a sequence of three pulses: one beep for 50ms, after a
    //pause for 100ms and last a beep for 50ms.
    clk.devices.obj.out(high(50_ms), low(100_ms), high(50_ms));
    
    while(true);
}
