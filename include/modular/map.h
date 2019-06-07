/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 20 May 20:05:50 CEST 2019 */
/* // map class */
/* // */

#ifndef _MAP_H_
#define _MAP_H_

#include "object.h"

typedef struct {
    Class base;
    /*! return the object represented by KEY.
        if key is not found return NULL */
    void *(*find)(Object *this, unsigned int);
    /*! swap the content of to the to key */
    void (*swap)(Object *this, unsigned int, unsigned int);
    /*! emplace an object for the key.
        return a boolean signifing the succes */
    char (*emplace)(Object *this, unsigned int, void *);
    /*! remove the key and return the object*/
    void *(*remove)(Object *this, unsigned int);
} map_t;


extern Class *Map_t;

#endif //_MAP_H_
