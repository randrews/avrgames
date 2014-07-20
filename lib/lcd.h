#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

typedef unsigned char byte;

int initLCD(volatile uint8_t *cs_port, int cs_bit,
            volatile uint8_t *dc_port, int dc_bit,
            volatile uint8_t *rst_port, int rst_bit);

void lcd_status(byte *manufacturer, byte *version, byte *driver);

uint16_t lcd_color(byte r, byte g, byte b);
void lcd_pixel(int x, int y, uint16_t color);

void lcd_hline(int x0, int x1, int y, uint16_t col);
void lcd_vline(int x, int y0, int y1, uint16_t col);
void lcd_rect(int left, int top, int right, int bottom, uint16_t color);

void lcd_blit(int x, int y, int w, int h, const byte *bitmap, uint16_t col0, uint16_t col1, byte progmem);

#endif
