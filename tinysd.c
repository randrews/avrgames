#include <avr/io.h>

#include "pins.h"
#include "lib/spi.h"
#include "lib/lcd.h"

int main(){
    SD_DDR |= (1 << SD_CS);
    LCD_DDR |= (1 << LCD_CS) | (1 << LCD_RESET) | (1 << LCD_DC);

    initSPI(FAST_SPI);
    initLCD(&LCD_PORT, LCD_CS,
            &LCD_PORT, LCD_DC,
            &LCD_PORT, LCD_RESET);

    lcd_rect(0, 0, 319, 239, 0);
    lcd_hline(0, 160, 50, lcd_color(0, 0, 255));

    return 0;
}
