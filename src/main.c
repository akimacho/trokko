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

/* initialize memory and serial device */
static int init(void)
{
    /*** symbols in linker script ***/
    extern int erodata;
    extern int data_start, edata;
    extern int bss_start,  ebss;

    /*** initialize DATA section and BSS section ***/
    /* copy .data section */
    memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
    /* clear .bss section */
    memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

    /* initialize serial device */
    serial_init(SERIAL_DEFAULT_DEVICE);

    return 0;
}

int global_data = 0x10; /* .data section */
int global_bss; /* bss section */

int main(void)
{
    init();
    puts("Hello world!\n");

    ASSERT(global_data == 0x10);
    global_data = 0x20;
    ASSERT(global_data == 0x20);

    global_bss = 0x10;
    ASSERT(global_bss == 0x10);
    global_bss = 0x20;
    ASSERT(global_bss == 0x20);

    while (1)
        ;

    return 0;
}

