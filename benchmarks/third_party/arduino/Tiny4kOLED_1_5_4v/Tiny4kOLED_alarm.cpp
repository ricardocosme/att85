#include <Tiny4kOLED.h>

uint8_t width = 128;
uint8_t height = 64;

void setup() {
  oled.begin(width, height, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.setFont(FONT6X8);
  oled.clear();
  oled.print("alarm");
  oled.on();
}

void loop() {}
//Compilation using Arduino IDE 1.8.13 with std=c++17:
//   text	   data	    bss	    dec	    hex	filename
//   2572	     22	     68	   2662	    a66	/tmp/arduino_build_706826/sketch_oct20b.ino.elf
