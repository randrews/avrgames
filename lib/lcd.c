#include "ram.h"
#include "spi.h"
#include <avr/pgmspace.h>

volatile uint8_t *lcd_cs_port, *lcd_dc_port, *lcd_rst_port;
int lcd_cs_bit, lcd_dc_bit, lcd_rst_bit;

void lcdselect(int cs, int dc);
void lcdreset(int rst);
byte lcd_command(byte cmd);
byte lcd_data(byte cmd);

/****************************************/

// Array of commands for the init sequence of the LCD
// First entry is 1=command, 2=data
// second entry is command itself
const byte init_commands[] PROGMEM = {
    1, 0xEF,
    2, 0x03,
    2, 0x80,
    2, 0x02,

    1, 0xCF,
    2, 0x00,
    2, 0xC1,
    2, 0x30,

    1, 0xED,
    2, 0x64,
    2, 0x03,
    2, 0x12,
    2, 0x81,

    1, 0xE8,
    2, 0x85,
    2, 0x00,
    2, 0x78,

    1, 0xCB,
    2, 0x39,
    2, 0x2C,
    2, 0x00,
    2, 0x34,
    2, 0x02,

    1, 0xF7,
    2, 0x20,

    1, 0xEA,
    2, 0x00,
    2, 0x00,

    1, 0xC0, // power control
    2, 0x23,

    1, 0xC1, // power control
    2, 0x10,

    1, 0xC5, // vcm control
    2, 0x3E,
    2, 0x28,

    1, 0xC7, // vcm control
    2, 0x86,

    1, 0x36, // memory access control
    2, 0x28,

    1, 0x3A, // pixel format
    2, 0x55,

    1, 0xB1, // frmctr
    2, 0x00,
    2, 0x18,

    1, 0xB6, // Display Function Control
    2, 0x08,
    2, 0x82,
    2, 0x27,

    1, 0xF2, // 3Gamma Function Disable
    2, 0x00,

    1, 0x26, // Gamma curve selected
    2, 0x01,

    1, 0xE0, //Set Gamma 
    2, 0x0F,
    2, 0x31,
    2, 0x2B,
    2, 0x0C,
    2, 0x0E,
    2, 0x08,
    2, 0x4E,
    2, 0xF1,
    2, 0x37,
    2, 0x07,
    2, 0x10,
    2, 0x03,
    2, 0x0E,
    2, 0x09,
    2, 0x00,

    1, 0xE1, //Set Gamma 
    2, 0x00,
    2, 0x0E,
    2, 0x14,
    2, 0x03,
    2, 0x11,
    2, 0x07,
    2, 0x31,
    2, 0xC1,
    2, 0x48,
    2, 0x08,
    2, 0x0F,
    2, 0x0C,
    2, 0x31,
    2, 0x36,
    2, 0x0F,

    /* 1, 0x36, // MADCTL */
    /* 2, 0x28, // MADCTL_MV | MADCTL_BGR */

    0, 0x00 // Stop here!
};

int initLCD(volatile uint8_t *cs_port, int cs_bit,
            volatile uint8_t *dc_port, int dc_bit,
            volatile uint8_t *rst_port, int rst_bit){

    lcd_cs_port = cs_port;
    lcd_dc_port = dc_port;
    lcd_rst_port = rst_port;

    lcd_cs_bit = cs_bit;
    lcd_dc_bit = dc_bit;
    lcd_rst_bit = rst_bit;

    lcdreset(0);
    lcdreset(1);

    int n = 0;
    while(1){
        byte type  = pgm_read_byte( &(init_commands[n])   );
        byte value = pgm_read_byte( &(init_commands[n+1]) );

        if(type == 0) break;

        if(type == 1) lcd_command(value);
        else lcd_data(value);

        n += 2;
    }

    lcd_command(0x11);    // Exit Sleep 
    _delay_ms(120); 		
    lcd_command(0x29);    // Display on 
}

byte lcd_command(byte cmd){
    lcdselect(0, 0);
    byte r = spi(cmd);
    lcdselect(1, 0);
    return r;
}

byte lcd_data(byte cmd){
    lcdselect(0, 1);
    byte r = spi(cmd);
    lcdselect(1, 0);
    return r;
}

void lcdselect(int cs, int dc){
    if(cs) (*lcd_cs_port) |=  (1 << lcd_cs_bit);
    else   (*lcd_cs_port) &= ~(1 << lcd_cs_bit);

    if(dc) (*lcd_dc_port) |=  (1 << lcd_dc_bit);
    else   (*lcd_dc_port) &= ~(1 << lcd_dc_bit);
}

void lcdreset(int rst){
    if(rst) (*lcd_rst_port) |=  (1 << lcd_rst_bit);
    else    (*lcd_rst_port) &= ~(1 << lcd_rst_bit);
}

/****************************************/

void lcd_status(byte *manufacturer, byte *version, byte *driver){
    lcdselect(0, 0);

    spi(0x04);
    spi(0);
    *manufacturer = spi(0);
    *version      = spi(0);
    *driver       = spi(0);

    lcdselect(1, 0);
}

void lcd_window(int x0, int y0, int x1, int y1){
    lcd_command(0x2A); // Column addr set
    lcd_data(x0 >> 8);
    lcd_data(x0 & 0xFF);     // XSTART 
    lcd_data(x1 >> 8);
    lcd_data(x1 & 0xFF);     // XEND

    lcd_command(0x2B); // Row addr set
    lcd_data(y0>>8);
    lcd_data(y0);     // YSTART
    lcd_data(y1>>8);
    lcd_data(y1);     // YEND

    lcd_command(0x2C); // write to RAM
}

uint16_t lcd_color(byte r, byte g, byte b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void lcd_pixel(int x, int y, uint16_t color){
    lcd_window(x, y, x+1, y+1);
    lcdselect(0, 1);
    spi(color >> 8);
    spi(color);
    lcdselect(1, 0);
}

void lcd_hline(int x0, int x1, int y, uint16_t color){
    lcd_window(x0, y, x1, y+1);
    lcdselect(0, 1);
    byte h = color >> 8;

    for(int n=x0; n <= x1; n++){
        spi(h);
        spi(color);
    }

    lcdselect(1, 0);    
}

void lcd_vline(int x, int y0, int y1, uint16_t color){
    lcd_window(x, y0, x, y1);
    lcdselect(0, 1);
    byte h = color >> 8;

    for(int n=y0; n <= y1; n++){
        spi(h);
        spi(color);
    }

    lcdselect(1, 0);    
}

void lcd_rect(int left, int top, int right, int bottom, uint16_t color){
    lcd_window(left, top, right, bottom);
    lcdselect(0, 1);
    byte h = color >> 8;

    for(int y=top; y <= bottom; y++){
        for(int x=left; x <= right; x++){
            spi(h);
            spi(color);
        }
    }
    lcdselect(1, 0);
}

void lcd_blit(int x, int y, int w, int h,
              byte *bitmap,
              uint16_t col0, uint16_t col1, byte drawmode){

    lcd_window(x, y, x+w-1, y+h-1);

    lcdselect(0, 1);

    byte col0_h = col0 >> 8;
    byte col1_h = col1 >> 8;

    int byte_num = 0;
    int bit = 7;
    byte current_byte = *bitmap;
    int current_column = 0;
    int current_row = 0;

    while(1){
        if(current_byte & (1 << bit)){
            spi(col1_h);
            spi(col1);
        } else {
            spi(col0_h);
            spi(col0);
        }

        if(++current_column >= w){
            if(++current_row >= h) break;
            current_column = 0;
            bit = 7;
            current_byte = bitmap[++byte_num];
        } else if(--bit < 0){
            bit = 7;
            current_byte = bitmap[++byte_num];
        }
    }

    lcdselect(1, 0);
}
