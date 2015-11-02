/*
 ============================================================================
    Name        : assert.h
    Description : utils for testing
 ============================================================================
*/

#ifndef _ASSERT_H_INCLUDED_
#define _ASSERT_H_INCLUDED_

#include "lib.h"

#define ASSERT(expr) do { \
    if (expr) { \
        puts("ok \t"); \
        puts(__FILE__); \
        puts(":"); \
        putxval(__LINE__, 0); \
        puts("\n"); \
    } else { \
        puts("not ok \t"); \
        puts(__FILE__); \
        puts(":"); \
        putxval(__LINE__, 0); \
        puts("\n"); \
    } \
} while (0)

#endif /* _ASSERT_H_INCLUDED_ */

