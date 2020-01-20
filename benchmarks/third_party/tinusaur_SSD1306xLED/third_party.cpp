#include <avr/io.h>

#include "ssd1306xled/font8x16.h"
#include "ssd1306xled/ssd1306xled.h"
#include "ssd1306xled/ssd1306xledtx.h"

int main() {
    ssd1306_init();
    ssd1306_clear();
    ssd1306tx_stringxy(ssd1306xled_font8x16data, 0, 0, "alarm");
    while(true);
}

//Compilation using avr-gcc 8.2.0 with -Os, SSD1306xLED library at
//commit 067db232d620 and 128x32 display:
//   text	   data	    bss	    dec	    hex	filename
//   2446	     16	      9	   2471	    9a7	a.out
