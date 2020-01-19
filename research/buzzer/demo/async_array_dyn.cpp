
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <avr/io.h>
#include <avr/interrupt.h>

inline void sig(bool b) {
    if(b) PORTB |= (1 << PB3);
    else PORTB &= ~(1 << PB3);
}
    
uint8_t cnt, state;

template<typename F>
inline void wait(F&& f) {
    if(cnt == 0) f();
    else --cnt;
}

uint8_t t[6];

//handler for each 10ms
ISR(TIM1_COMPA_vect) {
    if(state < 255) {
        wait([]{
                 auto p = &t[state*2];
                 sig(p[0]);
                 cnt = p[1];
                 --state;
             });
    }
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

    t[0] = 0;
    t[1] = 0;
    t[2] = 1;
    t[3] = 5;
    t[4] = 0;
    t[5] = 10;
    sig(1);
    state = 2;
    cnt = 5;
    
    while(1){}
}
