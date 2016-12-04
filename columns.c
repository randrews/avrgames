#include <avr/io.h>

#include "pins.h"
#include "lib/uart.h"
#include "lib/spi.h"
#include "lib/pff/pff.h"

int streq(const char* str1, const char* str2);

int main(){
    SD_DDR |= (1 << SD_CS);
    initUSART();

    printString("ATmega32u4 Initialized\r\n");

    initSPI();

    FATFS fs;
    DIR dir;
    FILINFO file;
    FRESULT res;

    printStringHex("Mount: ", pf_mount(&fs));

    res = pf_opendir(&dir, "");
    printStringHex("opendir: ", res);

    int found_foo = 0;
    while(!res){
        FRESULT read = pf_readdir(&dir, &file);
        if(file.fname[0] == 0) break;
        printString("File: ");
        printString(file.fname);
        printString("\r\n");
        if(!found_foo) found_foo = streq(file.fname, "FOO.TXT");
    }

    printStringHex("Found foo: ", found_foo);

    res = pf_open("FOO.TXT");
    printStringHex("Open file: ", res);

    printString("File contents: ");

    byte buf[16]; UINT count;
    while(1){
        res = pf_read(buf, 16, &count);
        if(res || !count) break;

        for(int n=0; n<count; n++)
            transmitByte(buf[n]);
    }

    printString("\r\n");
    return 0;
}

int streq(const char* str1, const char* str2){
    while(1){
        if(*str1 != *str2) return 0;
        if(!*str1) return 1;
        str1++; str2++;
    }
}
