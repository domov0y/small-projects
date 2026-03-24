# Настройки проекта
MCU=attiny13
F_CPU=9600000UL
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
PROGRAMMER=usbtiny
TARGET=main

# Флаги компиляции
CFLAGS=-Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)
LDFLAGS=-mmcu=$(MCU)

# Цели
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(TARGET).c
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET).elf $(LDFLAGS)

# Прошивка
flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$(TARGET).hex:i

# Очистка
clean:
	rm -f $(TARGET).elf $(TARGET).hex

.PHONY: all flash clean