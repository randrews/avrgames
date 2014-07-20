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

    lcd_blit(10, 10, 12, 12, Pieces, 0, lcd_color(255, 0, 0), 1);
    lcd_blit(22, 10, 12, 12, Pieces+24, 0, lcd_color(0, 255, 0), 1);
    lcd_blit(34, 10, 12, 12, Pieces+48, 0, lcd_color(0, 0, 255), 1);
    lcd_blit(46, 10, 12, 12, Pieces+72, 0, lcd_color(255, 255, 0), 1);
    lcd_blit(58, 10, 12, 12, Pieces+96, 0, lcd_color(0, 255, 255), 1);
    lcd_blit(70, 10, 12, 12, Pieces+120, 0, lcd_color(255, 255, 255), 1);
}
