/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 27 May 16:56:01 CEST 2019 */
/* // thread encapsulation */
/* // */

#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include "object.h"

typedef struct thread {
    Class base;
    void *(*join)(struct thread *this);
} thread;

extern Class *Thread;

#endif //_THREAD_H_
