CHIP=atmega1284p
MHZ=20
UTILS=spi sd pff/diskio pff/pff uart ram lcd
APP=tinysd
##########

GCC_ARGS=-mmcu=${CHIP} -Os -DF_CPU=${MHZ}000000 -std=gnu99 -Ipff/

.SUFFIXES: .elf .hex .bin

all: ${APP}.hex ${APP}.bin

.elf.hex: ${APP}.elf
	avr-objcopy -O ihex $< $@

.elf.bin: ${APP}.elf
	avr-objcopy -O binary $< $@

.c.o:
	avr-gcc ${GCC_ARGS} -c $< -o $@

.c: *.h pff/*.h

${APP}.elf: ${APP}.o ${UTILS:=.o}
	avr-gcc ${GCC_ARGS} -o $@ *.o pff/*.o

clean:
	rm -f *.o *.elf *.hex *.bin pff/*.o

flash:
	avrdude -p ${CHIP} -c usbasp -Uflash:w:${APP}.hex

