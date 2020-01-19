MCU_TARGET=attiny85
STD_CXX=c++14

CXX=avr-g++
CXXFLAGS=-std=$(STD_CXX) -mmcu=$(MCU_TARGET) -Wall -I ../../include

bins = add_rvalue_reference remove_cv is_destructible is_trivially_destructible is_void
all: $(bins)

.PHONY: clean
clean:
	rm -f $(bins)
