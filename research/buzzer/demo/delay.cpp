
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

inline void hi_sig()
{ PORTB |= (1 << PB3); }

inline void lo_sig()
{ PORTB &= ~(1 << PB3); }

int main() {
    //sets the PB3 pin as output
    //(positive pin of the buzzer connected to PB3)
    DDRB |= (1 << PB3);

    hi_sig();
    _delay_ms(5);
    lo_sig();
    _delay_ms(10);
    hi_sig();
    _delay_ms(5);
    lo_sig();
    
    while(1){}
}
