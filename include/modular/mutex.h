/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Fri  7 Jun 16:26:06 CEST 2019 */
/* // mutex encapsulation */
/* // */

#ifndef _MUTEX_H_
#define _MUTEX_H_

#include "modular/object.h"
#include <pthread.h>

typedef struct {
    Class base;
    void (*lock)(Object *this);
    bool (*tryLock)(Object *this);
    void (*unlock)(Object *this);
} mutex_t;

extern Class *Mutex_t;

#endif //_MUTEX_H_
