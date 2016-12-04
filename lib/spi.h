#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <util/delay.h>
#include "../pins.h"

typedef unsigned char byte;

void initSPI();
byte spi(byte b);

#endif
