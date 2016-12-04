#include "spi.h"
#include "uart.h"

void initSPI() {
    SPI_DDR |= (1 << SPI_MOSI) | (1 << SPI_CLK); // MOSI and CLK are outputs
    SPI_PORT |= (1 << SPI_MISO); // MISO gets a pullup resistor
    SPI_PORT &= ~(1 << SPI_CLK);    
}

byte spi(byte b) {
    byte result = 0;
    for(int n=0; n<8; n++){
        // Copy bit into MOSI
        if(b & 0x80)
            SPI_PORT |= (1 << SPI_MOSI);
        else
            SPI_PORT &= ~(1 << SPI_MOSI);

        // Pulse CLK
        SPI_PORT |= (1 << SPI_CLK);

        // Copy bit into result
        result <<= 1;
        if(SPI_PIN & (1 << SPI_MISO)) result |= 1;

        // Shift b down 1
        b <<= 1;

        SPI_PORT &= ~(1 << SPI_CLK);
    }
    return result;
}
