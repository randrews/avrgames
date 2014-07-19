#include "ram.h"
#include "spi.h"

volatile uint8_t *ram_cs_port;
int ram_cs_bit;

void cselect(int selected);

int initRAM(volatile uint8_t *port, int bit){
    ram_cs_port = port;
    ram_cs_bit = bit;
    byte mode;

    cselect(1);
    spi(0x05); // read mode register

    mode = spi(0); // First 3 bytes are junk

    cselect(0);

    return mode == 0x40; // default mode, sequential read / write
}

void cselect(int selected){
    if(!selected) (*ram_cs_port) |= (1 << ram_cs_bit);
    else (*ram_cs_port) &= ~(1 << ram_cs_bit);
}

/****************************************/

int readRAM(uint32_t start, unsigned char *buf, uint32_t len){
    cselect(1);
    spi(0x03); // read

    // Send address, high byte first
    spi(start >> 16);
    spi(start >> 8);
    spi(start);

    for(int n=0; n<len; n++){
        buf[n] = spi(0);
    };

    cselect(0);
    return len;
}

int writeRAM(uint32_t start, unsigned char *buf, uint32_t len){
    cselect(1);
    spi(0x02); // write

    // Send address, high byte first
    spi(start >> 16);
    spi(start >> 8);
    spi(start);

    for(int n=0; n<len; n++){
        spi(buf[n]);
    };

    cselect(0);
    return len;
}
