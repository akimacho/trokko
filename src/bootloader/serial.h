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
/* send a single character */
int serial_send_byte(int index, unsigned char b);
/* check whether it is possible to receive a message */
int serial_is_recv_enable(int index);
/* receive a single character */
unsigned char serial_recv_byte(int index);

#endif /* _SERIAL_H_INCLUDED */

