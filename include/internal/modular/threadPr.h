/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 27 May 17:02:45 CEST 2019 */
/* // thread ancapsulation */
/* // */

#ifndef _THREADPR_H_
#define _THREADPR_H_

#include "modular/thread.h"

typedef struct {
    thread _base;
    pthread_t _thread;
} _thread;

#endif //_THREADPR_H_
