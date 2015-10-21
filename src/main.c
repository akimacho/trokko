/*
 ============================================================================
    Name        : main.c
    Description : main function
 ============================================================================
*/

#include "defines.h"
#include "serial.h"
#include "lib.h"
#include "assert.h"

int main(void)
{
    serial_init(SERIAL_DEFAULT_DEVICE);

    puts("Hello World!\n");
    
    ASSERT(0x10);
    ASSERT(0x0);
    ASSERT(0x10 < 0xffff);
    ASSERT(0x10 > 0xffff);

    while (1)
        ;

    return 0;
}

