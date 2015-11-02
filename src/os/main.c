/*
 ============================================================================
    Name        : os/main.c
    Description : main function for operating system 
 ============================================================================
*/

#include "defines.h"
#include "serial.h"
#include "lib.h"

/*** main function ***/
int main(void)
{
    static char buf[32];

    puts("Hello, world!\n");

    while (1) {
        puts("> ");
        gets(buf);

        if (!strncmp(buf, "echo", 4)) {
            puts(buf + 4);
            puts("\n");
        } else if (!strcmp(buf, "exit")) {
            break;
        } else {
            puts("unkown.\n");
        }
    }

    return 0;
}

