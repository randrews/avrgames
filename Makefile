CHIP=atmega32u4
MHZ=16
UTILS=lib/spi lib/sd lib/pff/diskio lib/pff/pff lib/usb_serial # lib/uart
APP=columns
CABLE=usbasp
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

.c: lib/*.h lib/pff/*.h

${APP}.elf: ${APP}.o ${UTILS:=.o}
	avr-gcc ${GCC_ARGS} -o $@ *.o lib/*.o lib/pff/*.o

clean:
	rm -f lib/*.o *.o *.elf *.hex *.bin lib/pff/*.o

flash:
	avrdude -p ${CHIP} -c ${CABLE} -Uflash:w:${APP}.hex

