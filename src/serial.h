/*
 ============================================================================
    Name        : serial.h
    Description : serial device driver
 ============================================================================
*/

#ifndef _SERIAL_H_INCLUDED_
#define _SERIAL_H_INCLUDED_

/* init serial device */
int serial_init(int index);
/* check whether it is possible to send a message */
int serial_is_send_enable(int index);
/* send single character */
int serial_send_byte(int index, unsigned char b);

#endif /* _SERIAL_H_INCLUDED */

