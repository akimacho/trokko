/*
 ============================================================================
    Name        : vector.c
    Description : Interrupt vector
 ============================================================================
*/

#include "defines.h"

extern void start(void);    /* routine for start-up */

/*
 * Interrupt vector table
 * placed at the leading address by definition of linker script
 */
void (*vectors[])(void) = {
    start, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
};

