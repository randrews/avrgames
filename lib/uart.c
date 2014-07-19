#include "uart.h"

void initUSART(){
    UBRR0H = UBRRH_VALUE; /* defined in setbaud.h */
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    UCSR0B = (1 << TXEN0) | (1 << RXEN0); /* Enable USART transmitter/receiver */
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); /* 8 data bits, 1 stop bit */
}

void transmitByte(uint8_t data) {
    /* Wait for empty transmit buffer */
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data; /* send data */
}

uint8_t receiveByte(void) {
  loop_until_bit_is_set(UCSR0A, RXC0); /* Wait for incoming data */
  return UDR0; /* return register value */
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
