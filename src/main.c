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
    char dst[25] = "abc";
    char src[]   = "efg";

    serial_init(SERIAL_DEFAULT_DEVICE);

    puts("Hello World!\n");

    ASSERT(123 == atoi("123"));
    ASSERT(123 == atoi("12a3"));

    strcat(dst, src);
    ASSERT(strcmp(dst, "abcdef"));

    while (1)
        ;

    return 0;
}

