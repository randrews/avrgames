#include "uart.h"

void initUSART(){
    UBRR1H = UBRRH_VALUE; /* defined in setbaud.h */
    UBRR1L = UBRRL_VALUE;

#if USE_2X
    UCSR1A |= (1 << U2X1);
#else
    UCSR1A &= ~(1 << U2X1);
#endif

    UCSR1B = (1 << TXEN1) | (1 << RXEN1); /* Enable USART transmitter/receiver */
    UCSR1C = (1 << UCSZ11) | (1 << UCSZ10); /* 8 data bits, 1 stop bit */
}

void transmitByte(uint8_t data) {
    /* Wait for empty transmit buffer */
    loop_until_bit_is_set(UCSR1A, UDRE1);
    UDR1 = data; /* send data */
}

uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR1A, RXC1); /* Wait for incoming data */
  return UDR1; /* return register value */
}

void printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    transmitByte(myString[i]);
    i++;
  }
}

void printInt(int a){
    char str[10];
    itoa(a, str, 10);
    printString(str);
}

void printHex(unsigned char a){
    int n1 = (a >> 4);
    int n2 = (a & 0x0f);

    if(n1 >= 10) transmitByte('A' + n1 - 10);
    else transmitByte('0' + n1);

    if(n2 >= 10) transmitByte('A' + n2 - 10);
    else transmitByte('0' + n2);
}

void printStringHex(const char myString[], unsigned char c) {
    printString(myString);
    printHex(c);
    printString("\r\n");
}

void printStringInt(const char myString[], int c) {
    printString(myString);
    printInt(c);
    printString("\r\n");
}
