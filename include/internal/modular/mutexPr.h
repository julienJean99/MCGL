/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Fri  7 Jun 16:29:04 CEST 2019 */
/* // mutex ancapsulation */
/* // */

#ifndef _MUTEXPR_H_
#define _MUTEXPR_H_

#include "modular/mutex.h"

typedef struct {
    mutex_t base;
    pthread_mutex_t _mutex;
} _mutex_t;

#endif //_MUTEXPR_H_
