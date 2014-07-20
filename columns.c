#include <avr/io.h>

#include "pins.h"
#include "lib/spi.h"
#include "lib/lcd.h"
#include "bmp.h"

void drawFrame();

int main(){
    // Set up the screen's pins
    LCD_DDR |= (1 << LCD_CS) | (1 << LCD_RESET) | (1 << LCD_DC);

    // init subsystems we need
    initSPI(FAST_SPI);
    initLCD(&LCD_PORT, LCD_CS,
            &LCD_PORT, LCD_DC,
            &LCD_PORT, LCD_RESET);

    drawFrame();

    return 0;
}

byte sq[] = {
    0b11111111, 0b11110000,
    0b10000000, 0b00010000,
    0b10111111, 0b11010000,
    0b10100000, 0b01010000,
    0b10101111, 0b01010000,
    0b10101001, 0b01010000,
    0b10101001, 0b01010000,
    0b10101111, 0b01010000,
    0b10100000, 0b01010000,
    0b10111111, 0b11010000,
    0b10000000, 0b00010000,
    0b11111111, 0b11110000,
};

void drawFrame(){
    lcd_rect(0, 0, 319, 239, 0); // Clear the screen to black

    lcd_vline(99, 0, 239, lcd_color(0, 32, 32));
    lcd_vline(98, 0, 239, lcd_color(0, 32, 32));

    lcd_vline(97, 0, 239, lcd_color(0, 64, 64));
    lcd_vline(96, 0, 239, lcd_color(0, 64, 64));

    lcd_vline(95, 0, 239, lcd_color(0, 64, 128));
    lcd_vline(94, 0, 239, lcd_color(0, 64, 128));

    lcd_vline(93, 0, 239, lcd_color(0, 64, 192));
    lcd_vline(92, 0, 239, lcd_color(0, 64, 192));

    lcd_vline(220, 0, 239, lcd_color(0, 32, 32));
    lcd_vline(221, 0, 239, lcd_color(0, 32, 32));

    lcd_vline(222, 0, 239, lcd_color(0, 64, 64));
    lcd_vline(223, 0, 239, lcd_color(0, 64, 64));

    lcd_vline(224, 0, 239, lcd_color(0, 64, 128));
    lcd_vline(225, 0, 239, lcd_color(0, 64, 128));

    lcd_vline(226, 0, 239, lcd_color(0, 64, 192));
    lcd_vline(227, 0, 239, lcd_color(0, 64, 192));

    lcd_blit(10, 10, 12, 12, sq, 0, lcd_color(255, 0, 0), 1);
}
