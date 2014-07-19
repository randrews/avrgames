#ifndef PINS_H
#define PINS_H

#define BAUD 9600
#define FAST_SPI 1

// SPI (these can't be changed, they're chip-dependent.
// These are the values for the 1284p, the 328's are
// different)
#define SPI_PORT  PORTB
#define SPI_DDR   DDRB
#define SPI_SS    4
#define SPI_MOSI  5
#define SPI_MISO  6
#define SPI_CLK   7

// A green LED, for basic status
#define LED_PORT  PORTA
#define LED_DDR   DDRA
#define LED_CS    0

// SD card reader CS
#define SD_PORT   PORTB
#define SD_DDR    DDRB
#define SD_CS     0

// SD card reader CS
#define LCD_PORT  PORTB
#define LCD_DDR   DDRB
#define LCD_CS    1
#define LCD_RESET 2
#define LCD_DC    3

// SRAM CS
#define RAM_PORT  PORTB
#define RAM_DDR   DDRB
#define RAM_CS    4

#endif
