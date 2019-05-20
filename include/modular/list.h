/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 13 May 08:52:26 CEST 2019 */
/* // list */
/* // */

#ifndef _LIST_H_
#define _LIST_H_

#include "object.h"

typedef struct list_t list_t;

/* type for fuction exeutable by map */
typedef void *(mapFunc)(void *, va_list *);

struct list_t {
    Class base;
    /*! add the element at the end of the list */
    char (*pushBack)(void *this, void *);
    /*! return the length of the list */
    size_t (*length)(const Object *this);
    /*! remove item at index and return it */
    void *(*remove)(Object *this, size_t);
    /*! return the item at index */
    void *(*at)(const Object *this, size_t);
    /*! run a function on every item in the list */
    struct list_t *(*map)(const Object *this, mapFunc *, ...);
};

extern Class *List_t;

#endif //_LIST_H_
