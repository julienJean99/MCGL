/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Fri 24 May 15:36:56 CEST 2019 */
/* // string */
/* // */

#ifndef _STRING_H_
#define _STRING_H_

#include "object.h"

# define str(o)                                                      \
    do {                                                             \
        if (((Class *)o)->__str__ != NULL) {                         \
            ((Class *)o)->__str__(o);                                \
            break;                                                   \
        }                                                            \
        new(String, ((Class *)o)->__name__);                         \
    } while(0);

typedef struct string {
    Class _base;
    /*! change the contant of the string */
    void (*setPointer)(struct string *this, char *);
    /*! return the pointer to the string */
    const char *(*getPointer)(const struct string *this);
    /*! return the length of the string */
    size_t (*length)(const struct string *this);
    /*! resize the string to the new length.
        if the new length is longer then the original then
        the current content is extended by inserting at the end as many characters as needed*/
    bool (*resize)(struct string *this, size_t, char);
} string;

extern Class *String;

#endif //_STRING_H_
