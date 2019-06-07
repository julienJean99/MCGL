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

typedef struct {
    const Class *obj;
    va_list args;
    size_t index;
} listArgs;

/*! type for fuction exeutable by map */
typedef void *(mapFunc)(listArgs *);
/*! type for fuction exeutable by loop */
typedef void (loopFunc)(listArgs *);

struct list_t {
    Class base;
    /*! add the element at the end of the list */
    bool (*pushBack)(list_t *this, Class *);
    /*! return the length of the list */
    size_t (*length)(const list_t *this);
    /*! remove item at index and return it */
    Class *(*remove)(list_t *this, size_t);
    /*! return the item at index */
    Class *(*at)(const list_t *this, size_t);
    /*! run a function on every item in the list
        return a list of each pointer return by mapFunc*/
    struct list_t *(*map)(const list_t *this, mapFunc *, ...);
    /*! run a function on every item in the list */
    void (*loop)(const list_t *this, loopFunc *, ...);
};

extern Class *List_t;

#endif //_LIST_H_
