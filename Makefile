# AVR type
MMCU = atmega16

# Frequency
F_CPU = 16000000

# Programmer
PROGRAMMER = usbasp 
PROGRAMMER_PORT = usb

# Output name
PROJECT = ov7670

# Source files
SOURCES = main.c \
	ov7670.c \
	hardware/atmega16/twi.c \
	hardware/atmega16/uart.c \
	hardware/atmega16/shift.c \
	hardware/atmega16/ssd1289.c

# Compiler utils
CC = avr-gcc
OBJCOPY = avr-objcopy

CDEFS = -DF_CPU=$(F_CPU)UL

CFLAGS = $(CDEFS) 
CFLAGS += -mmcu=$(MMCU) -g -Os -Wall -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wstrict-prototypes -I$(shell pwd)

OBJECTS = $(SOURCES:.c=.o)

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -O ihex -R .eeprom $(PROJECT).out $(PROJECT).hex

$(PROJECT).out:  $(OBJECTS)
	$(CC)  $(CFLAGS) $^ -o $@ -lm

$.o:%.c
	$(CC) $(CFLAGS) $< -o $@

program_flash: $(PROJECT).hex
	avrdude -c $(PROGRAMMER) -P $(PROGRAMMER_PORT) -p $(MMCU) -U flash:w:$(PROJECT).hex 

clean:
	rm -f $(OBJECTS) 
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex

.PHONY: clean program_flash
