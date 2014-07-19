#include "spi.h"

void initSPI(int fast) {
    SPI_DDR |= (1 << SPI_SS); /* set SS output */
    SPI_PORT |= (1 << SPI_SS); /* start off not selected (high) */

    SPI_DDR |= (1 << SPI_MOSI) | (1 << SPI_CLK);
    SPI_PORT |= (1 << SPI_MISO); /* pullup on MISO */

    if(!fast){ /* Speed flags, safer for breadboards */
        SPCR |= (1 << SPR0) | (1 << SPR1);
    }

    SPCR |= (1 << MSTR) | (1 << SPE); /* clockmaster, and enable */
}

byte spi(byte b) {
    SPDR = b; /* SPI starts sending immediately */
    loop_until_bit_is_set(SPSR, SPIF); /* wait until done */
    return SPDR; /* SPDR now contains the received byte */
}
