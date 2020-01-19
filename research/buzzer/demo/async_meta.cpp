
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

template<uint8_t... tail>
struct handle;

template<uint8_t _state, uint8_t s, uint8_t cnt>
struct handle<_state, s, cnt> {
    void operator()() {
        wait([]{ sig(s); });
    }
};

template<uint8_t _state, uint8_t _sig, uint8_t _cnt, uint8_t... tail>
struct handle<_state, _sig, _cnt, tail...> : handle<tail...> {
    using base = handle<tail...>;
    void operator()() {
        if(state == _state)
            wait([]{
                     sig(_sig);
                     state = _state + 1;
                     cnt = _cnt;
                 });
        else base()();
    }
};

handle<0, 0, 10,
       1, 1, 5,
       2, 0, 0> h;

//handler for each 10ms
ISR(TIM1_COMPA_vect) {
    h();
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

    sig(1);
    state = 0;
    cnt = 5;
    
    while(1){}
}
