#!/bin/bash

make $@
avr-size ctor.elf
avr-size ctor_adhoc.elf
avr-size commands.elf
avr-size commands_naive.elf
