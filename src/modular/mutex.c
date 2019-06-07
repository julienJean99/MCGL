/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Fri  7 Jun 16:32:04 CEST 2019 */
/* // mutex */
/* // */

#include <errno.h>
#include "internal/modular/mutexPr.h"

void mutexCtor(
    _mutex_t *this,
    va_list * args)
{
    const pthread_mutexattr_t *attr = va_arg(*args, pthread_mutexattr_t *);
    if (pthread_mutex_init(&this->_mutex, attr) != 0){
        perror(NULL);
    }
}

void mutexDtor(
    _mutex_t *this)
{
    if (pthread_mutex_destroy(&this->_mutex) != 0){
        perror(NULL);
    }
}

void lock(
    Object *_this)
{
    _mutex_t *this = _this;

    if (pthread_mutex_lock(&this->_mutex) != 0) {
        perror(NULL);
    }
}

void unlock(
    Object *_this)
{
    _mutex_t *this = _this;

    if (pthread_mutex_unlock(&this->_mutex) != 0) {
        perror(NULL);
    }
}

bool tryLock(
    Object *_this)
{
    _mutex_t *this = _this;
    int tmp = pthread_mutex_trylock(&this->_mutex);

    if (tmp == 0) {
        return (true);
    }
    return (false);
}

static _mutex_t _description =
{
    {
        {
            .__size__ = sizeof(_mutex_t),
            .__name__ = "Mutex_t",
            .__ctor__ = (ctor_t)&mutexCtor,
            .__dtor__ = (dtor_t)&mutexDtor,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL
        },
        .lock = &lock,
        .tryLock = &tryLock,
        .unlock = &unlock,
    },
    ._mutex = {},
};

Class *Mutex_t = (Class *) &_description;
