
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <avr/io.h>
#include <avr/interrupt.h>

#include <att85/buzzer/buzzer.hpp>

using namespace att85;

struct HiSig { void operator()() { PORTB |= (1 << PB3); } };
struct LoSig { void operator()() { PORTB &= ~(1 << PB3); } };
buzzer<HiSig, LoSig> bz;

//handler for each 10ms
ISR(TIM1_COMPA_vect) {
    //buzzer polling
    bz.poll();
}

int main() {
    //sets the PB3 pin as output
    //(positive pin of the buzzer connected to PB3)
    DDRB |= (1 << PB3);

    //setup a CTC timer for each 10ms
    TCCR1 |= (1 << CTC1);
    TCCR1 |= (1 << CS13) | (1 << CS11) | (1 << CS10);
    OCR1C = 10; 
    TIMSK |= (1 << OCIE1A);
    sei();

    //emits a beep for (5 * 10)ms, after this it emits a pause for (10
    //* 10) ms and for last it emits another beep for (6 * 10)ms
    bz.out<beep<5>, pause<10>, beep<6>>();
    
    while(1){}
}
