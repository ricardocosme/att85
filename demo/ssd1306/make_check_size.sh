#!/bin/bash

make $@
avr-size alarm.elf
avr-size demo.elf
avr-size char_8x8.elf
avr-size char_8x8_adhoc.elf
avr-size two_char_8x8.elf
avr-size two_char_8x8_adhoc.elf
avr-size init_display.elf
avr-size init_display_adhoc.elf
avr-size commands.elf
avr-size commands_adhoc.elf
avr-size 16x32.elf
