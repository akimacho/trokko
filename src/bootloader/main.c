/*
 ============================================================================
    Name        : main.c
    Description : main function
 ============================================================================
*/

#include "defines.h"
#include "serial.h"
#include "lib.h"
#include "elf.h"
#include "xmodem.h"

/*** initialize memory and serial device ***/
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

/*** memory dump ***/
static int dump(char *buf, long size)
{
    long i;

    if (size < 0) {
        puts("no data.\n");
        return -1;
    }
    for (i = 0; i < size; i++) {
        putxval(buf[i], 2);
        if ((i & 0xf) == 15) {
            puts("\n");
        } else {
            if ((i & 0xf) == 7) {
                puts(" ");
            }
            puts(" ");
        }
    }
    puts("\n");

    return 0;
}

static void wait()
{
    volatile long i;
    puts("now waiting ... \n");
    for (i = 0; i < 300000; i++) {
        ;
    }
}

/*** main function ***/
int main(void)
{
    static char buf[16]; /* 128byte buffer */
    static long size = -1; /* received buffer-size */
    static unsigned char *loadbuf = NULL; /* buffuer to load a file-data */
    extern int buffer_start; /* buffer defined by linker script */
    char *entry_point; /* entry point */
    void (*entry_proc)(void); /* function-pointer for execute function from entry point */

    init();

    puts("trokko_loader started. \n");

    while (1) {
        puts("trokko_loader > "); /* display a prompt */
        gets(buf); /* get command from serial communication */

        if (!strcmp(buf, "load")) { /* download a file on XMODEM */
            loadbuf = (char *)(&buffer_start);
            size = xmodem_recv(loadbuf);
            wait();

            if (size < 0) {
                puts("\n*** XMODEM receive error! ***\n");
            } else {
                puts("\n*** XMODEM receive succeeded. ***\n");
            }
        } else if (!strcmp(buf, "dump")) { /* memory dump */
            puts("size : ");
            putxval(size, 0);
            puts("\n");
            dump(loadbuf, size);
        } else if (!strcmp(buf, "run")) { /* execute ELF-format-file */
            entry_point = elf_load(loadbuf); /* load file on memory */
            if (!entry_point) {
                puts("run error!\n");
            } else {
                puts("*** starting from entry point ***");
                putxval((unsigned long)entry_point, 0);
                puts("\n");

                entry_proc = (void (*)(void))entry_point;
                entry_proc(); /* start process */
            }
        } else if (!strcmp(buf, "hello")) { 
            puts("Hello, I'm trokko!\n");
        } else { /* otherwise */
            puts("*** unknown. ***\n");
        }
    }

    while (1) {
        ;
    }

    return 0;
}

