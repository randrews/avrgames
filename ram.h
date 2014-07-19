#ifndef RAM_H
#define RAM_H

#include <avr/io.h>

int initRAM(volatile uint8_t *port, int bit);
int readRAM(uint32_t start, unsigned char *buf, uint32_t len);
int writeRAM(uint32_t start, unsigned char *buf, uint32_t len);

#endif
