#ifndef SD_H
#define SD_H

#include "spi.h"
#include <avr/io.h>
#include <util/delay.h>

byte initSD(volatile uint8_t *port, int bit);
int readSD(byte *array, uint32_t sector, unsigned int offset, unsigned int count);

#endif
