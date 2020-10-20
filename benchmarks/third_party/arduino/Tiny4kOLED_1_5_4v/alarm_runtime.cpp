#include <att85.hpp>

using namespace att85::ssd1306;

void setup() {
  display_128x64<> disp;
  disp.out<font::_8x8>(0, 0, runtime::c_str<font::_8x8::alpha>{"alarm"});
  disp.on();
}

void loop() {}

//Compilation using Arduino IDE 1.8.13 with std=c++17:
//   text	   data	    bss	    dec	    hex	filename
//   720	      6	      9	    735	    2df	/tmp/arduino_build_935674/sketch_oct20a.ino.elf
