/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 20 May 20:05:50 CEST 2019 */
/* // map class */
/* // */

#ifndef _MAP_H_
#define _MAP_H_

# include "object.h"
# include "string.h"

typedef struct {
    Class base;
    /*! return the object represented by KEY.
        if key is not found return NULL */
    void *(*find)(Object *this, string *key);
    /*! swap the content of to the to *key */
    void (*swap)(Object *this, string *key1, string *key2);
    /*! emplace an object for the key.
        return a boolean signifing the succes */
    bool (*emplace)(Object *this, string *key, void *);
    /*! remove the key and return the object*/
    void *(*remove)(Object *this, string *key);
} map_t;


extern Class *Map_t;

#endif //_MAP_H_
