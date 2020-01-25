MCU_TARGET=attiny85
STD_CXX=c++17
OPTIMIZE=-Os

CXX=avr-g++
CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump

CXXFLAGS=-std=$(STD_CXX) -g -mmcu=$(MCU_TARGET) -Wall $(OPTIMIZE) -I ../../include -I ../../include/att85

demos = init_display char_8x8 two_char_8x8 commands 8x8 16x32 runtime_sequence_16x32 number_16x32 lowest_freq_display alarm alphabet

all: $(demos:%=%.elf) $(demos:%=%.lst) $(demos:%=%.s)

%.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(demos:%=%.d)

%.s: %.cpp
	$(CXX) $(CXXFLAGS) -S $^

%.elf: %.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

.PHONY: flash_%
flash-%: %.hex
	avrdude -p t85 -c usbasp -P usb  -U flash:w:$<

.PHONY: clean
clean:
	rm -f *.hex *.lst *.elf *.o *.d *.s

