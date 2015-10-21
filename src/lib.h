/*
 ============================================================================
    Name        : lib.h
    Description : common utils
 ============================================================================
*/

#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

/***************************************************************************
 * I/O
 ***************************************************************************/
/* send single charactor */
int putc(unsigned char c);
/* send string */
int puts(unsigned char *str);
/* display a number in hexadecimal*/
int putxval(unsigned long value, int column);

/***************************************************************************
 * Utilities
 ***************************************************************************/
/* fill a memory in a particular data */
void *memset(void *b, int c, long len);
/* copy the memory */
void *memcpy(void *dst, const void *src, long len);
/* compare the memory */
int memcmp(const void *b1, const void *b2, long len);
/* get the length of the string */
int strlen(const char *s);
/* copy the string */
char *strcpy(char *dst, const char *src);
/* compare strings */
int strcmp(const char *s1, const char *s2);
/* compare the string by specifying the length */
int strncmp(const char *s1, const char *s2, int len);
/* convert string to integer */
int atoi(const char *s);
/* concat two strings */
char *strcat(char *dst, const char *src);
/* concat two strings up to length */
char *strncat(char *dst, const char *src, int len);

#endif /* _LIB_H_INCLUDED_ */

