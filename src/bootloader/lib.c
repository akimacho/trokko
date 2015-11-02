/*
 ============================================================================
    Name        : lib.c
    Description : common utils
 ============================================================================
*/

#include "defines.h"
#include "serial.h"
#include "lib.h"

/***************************************************************************
 * I/O
 ***************************************************************************/
/*** INPUT ***/
/* get a single character */
unsigned char getc(void)
{
    unsigned char c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    c = (c == '\r') ? '\n' : c; /* convert a new line code */
    putc(c); /* echo-back */
    return c;
}

/* get a string */
int gets(unsigned char *buf)
{
    int i = 0;
    unsigned char c;
    do {
        c = getc();
        if (c == '\n') {
            c = '\0';
        }
        buf[i++] = c;
    } while (c);
    return i - 1;
}

/*** OUTPUT ***/
/* send single charactor */
int putc(unsigned char c)
{
    /* convert a new line code */
    if (c == '\n') {
        serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    }
    return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

/* send string */
int puts(unsigned char *str)
{
    while (*str) {
        putc(*(str++));
    }
    return 0;
}

/* display a number in hexadecimal*/
int putxval(unsigned long value, int column)
{
    char buf[9];
    char *p;

    /* process from the least significant digit */
    p = buf + sizeof(buf) - 1;
    *(p--) = '\0';

    if (!value && !column) {
        column++;
    }

    while (value || column) {
        *(p--) = "0123456789abcdef"[value & 0xf];/* 0xf:0b1111 */
        value >>= 4;/* move to the next digit */
        if (column)
            column--;
    }

    puts(p + 1);

    return 0;
}

/***************************************************************************
 * Utilities
 ***************************************************************************/
/* fill a memory in a particular data */
void *memset(void *b, int c, long len)
{
    char *p;

    for (p = b; len > 0; len--) {
        *(p++) = c;
    }
    return b;
}

/* copy the memory */
void *memcpy(void *dst, const void *src, long len)
{
    char *d = dst;
    const char *s = src;
    
    for (; len > 0; len--) {
        *(d++) = *(s++);
    }
    return dst;
}

/* compare the memory */
int memcmp(const void *b1, const void *b2, long len)
{
    const char *p1 = b1;
    const char *p2 = b2;
    
    for (; len > 0; len--) {
        if (*p1 != *p2) {
            return (*p1 > *p2) ? 1 : -1;
        }
        p1++;
        p2++;
    }
    return 0;
}

/* get the length of the string */
int strlen(const char *s)
{
    int len;

    for (len = 0; *s; s++, len++) {
        ;
    }
    return len;
}

/* copy the string */
char *strcpy(char *dst, const char *src)
{
    char *d = dst;

    for (;; dst++, src++) {
        *dst = *src;
        if (!(*src)) {
            break;
        }
    }
    return d;
}

/* compare strings */
int strcmp(const char *s1, const char *s2)
{
    while (*s1 || *s2) {
        if (*s1 != *s2) {
            return (*s1 > *s2) ? 1 : -1;
        }
        s1++;
        s2++;
    }
    return 0;
}

/* compare the string by specifying the length */
int strncmp(const char *s1, const char *s2, int len)
{
    while ((*s1 || *s2) && (len > 0)) {
        if (*s1 != *s2) {
            return (*s1 > *s2) ? 1 : -1;
        }
        s1++;
        s2++;
        len--;
    }
    return 0;
}

/* convert string to integer */
int atoi(const char *s)
{
    int integer = 0;
    
    do {
        if ('0' <= *s && *s <= '9') {
            integer = integer * 10 + (*s - '0');
        }
    } while(*s++);
    return integer;
}

/* concat two strings */
char *strcat(char *dst, const char *src)
{
    char *d = dst;

    while (*dst) {
        dst++;
    }
    strcpy(dst, src);
    return d;
}

/* concat two strings up to length */
char *strncat(char *dst, const char *src, int len)
{
    char *d = dst;

    while (*dst) {
        dst++;
    }
    strncmp(dst, src, len);
    return d;
}

