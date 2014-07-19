#include <avr/io.h>

#include "uart.h"
#include "spi.h"
#include "lcd.h"
#include "pff/pff.h"

int main(){
    SD_DDR |= (1 << SD_CS);
    LCD_DDR |= (1 << LCD_CS) | (1 << LCD_RESET) | (1 << LCD_DC);

    initUSART();
    initSPI(FAST_SPI);
    initLCD(&LCD_PORT, LCD_CS,
            &LCD_PORT, LCD_DC,
            &LCD_PORT, LCD_RESET);

    lcd_hline(0, 160, 50, 0);

    FATFS fs;
    DIR dir;
    FILINFO file;
    FRESULT res;

    while(1){
        byte a = receiveByte();

        printString("==========\r\n");

        printStringHex("Mount: ", pf_mount(&fs));

        res = pf_opendir(&dir, "");
        printStringHex("Open dir: ", res);

        printString("----------\r\n");

        while(!res){ // If the dir succeeded in opening
            FRESULT read = pf_readdir(&dir, &file);
            if(res || file.fname[0] == 0) break;
            transmitByte('.');
            /* printString("File: "); */
            /* printString(file.fname); */
            /* printString("\r\n"); */
        }

        /* res = pf_open("FOO.TXT"); */
        /* printStringHex("Open file: ", res); */

        /* printString("File contents: "); */

        /* byte buf[16]; UINT count; */
        /* while(1){ */
        /*     res = pf_read(buf, 16, &count); */
        /*     if(res || !count) break; */

        /*     for(int n=0; n<count; n++) */
        /*         transmitByte(buf[n]); */
        /* } */

        /* printString("\r\n"); */

        printString("==========\r\n\r\n");
    }

    return 0;
}
