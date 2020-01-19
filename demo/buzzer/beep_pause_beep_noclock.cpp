
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <avr/interrupt.h>
#include <avr/io.h>

#include <att85/buzzer/buzzer_at.hpp>
#include <att85/chrono/duration.hpp>

using namespace att85;
using namespace att85::buzzer;

//clock_time_factor = 10
//clock_time = 1ms * clock_time_factor
const auto clock_time = 10_ms;

//represents a buzzer connected to pin PB3 that is clocked at 100Hz
auto bz = clk_buzzer_at<pb3>(10_ms);

//interrupt handler for each 10ms(clock_time)
ISR(TIM1_COMPA_vect) {
    //buzzer polling
    bz.poll();
}

int main() {
    //sets the PB3 pin as output
    //(positive pin of the buzzer connected to PB3)
    bz.init();
    
    //setup a CTC timer for each 10ms.
    //this will be act as a clock to bz with a clock time equals to 10ms
    TCCR1 |= (1 << CTC1) | (1 << CS13) | (1 << CS11) | (1 << CS10);
    OCR1C = clock_time.value; 
    TIMSK |= (1 << OCIE1A);
    sei();

    //outputs a sequence of three pulses: one beep for 50ms, after a
    //pause for 100ms and last a beep for 50ms.
    bz.out(beep(50_ms), pause(100_ms), beep(50_ms));
    
    while(true);
}
