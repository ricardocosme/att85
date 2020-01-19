
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <att85/buzzer/buzzer_at.hpp>
#include <att85/clock/clock.hpp>

using namespace att85;
using namespace att85::buzzer;

//defines a clock of 100Hz and a buzzer connected to pin PB3 that is
//clocked at this frequency.
auto clk = clock::clock<
    buzzer_at<pb3, //device clocked by this clock. It is polled at
                    //each 10ms to process sequences of beeps and
                    //pauses in an asynchronous approach.
              
              1 //optimizes when desired an emission of single
                //beeps. In another words, this configuration does not
                //permit an emission of a sequence of beeps and
                //pauses. We can only output a single beep at each
                //call to buzzer::out().
              >    
>(10_ms, //clock time of 10ms (100Hz)
  1_MHz); //defines the hardware clock. BTW, 1_MHz is the default
          //value. For example, if your uC is running at 8MHz, then
          //you must pass the value 8_MHz.
              
//registers the clock as an ISR(Interrupt Service Routine)
ATT85_CLOCK_ISR(clk)

int main() {
    //setup the clock using a timer of ATtiny85
    clk.init();

    //emits a beep for 50ms
    clk.devices.obj.out(beep(50_ms));
    
    while(true);
}
