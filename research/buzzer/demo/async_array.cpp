
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <avr/io.h>
#include <avr/interrupt.h>

inline void hi_sig()
{ PORTB |= (1 << PB3); }

inline void lo_sig()
{ PORTB &= ~(1 << PB3); }

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

uint8_t t[] = {0, 10,
               1, 5,
               0, 0};

void handle() {
    if(state < 3) {
        wait([]{
                 auto p = &t[state*2];
                 sig(p[0]);
                 cnt = p[1];
                 ++state;
             });
    }
}

//handler for each 10ms
ISR(TIM1_COMPA_vect) {
    handle();
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

    hi_sig();
    state = 0;
    cnt = 5;
    
    while(1){}
}
