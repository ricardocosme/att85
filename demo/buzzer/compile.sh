avr-g++ -std=c++14 -mmcu=attiny85 \
        -Wall -Os \
        -I ../../include \
        beep_pause_beep.cpp -I. $@
        
