#!/bin/bash

make $@
avr-size beep.elf
avr-size beep_pause_beep.elf
avr-size beep_pause_beep_noclock.elf
avr-size beep_pause_beep_custom_hilosig.elf
avr-size beep_pause_beep_custom_hilosig_noclock.elf
