#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <util/delay.h>
#include "../pins.h"

typedef unsigned char byte;

void initSPI(int fast);
byte spi(byte b);

#endif
