#!/bin/bash

make $@
avr-size ctor.elf
avr-size ctor_adhoc.elf
