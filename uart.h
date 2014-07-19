#ifndef UART_H
#define UART_H

#include "pins.h"
#include <stdlib.h> 
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>

void initUSART();
uint8_t receiveByte();
void transmitByte(uint8_t data);
void printString(const char myString[]);
void printStringHex(const char myString[], unsigned char a);
void printStringInt(const char myString[], int a);
void printInt(int a);
void printHex(unsigned char a);

#endif

