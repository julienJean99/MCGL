/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 27 May 17:07:30 CEST 2019 */
/* // thread ancapsulation */
/* // */

#include "internal/modular/threadPr.h"

static void threadCtor(
    _thread *this,
    va_list args)
{
    void *(*func)(void *) = va_arg(args, void *(*)(void *));
    void *arg = va_arg(args, void *);

    if ((pthread_create(
        &this->_thread,
        NULL,
        func,
        arg)) != 0) {
        raise("HAHHHAH");
    }
}

static void threadDtor(
    __attribute__((unused))_thread *this,
    __attribute__((unused))va_list args)
{
}

static void *join(struct thread *this)
{
    void *ret = NULL;

    pthread_join(
        ((_thread *)this)->_thread,
        &ret);
    return (ret);
}

static _thread _description =
{
    {
        {
            .__size__ = sizeof(_thread),
            .__name__ = "thread",
            .__ctor__ = (ctor_t)&threadCtor,
            .__dtor__ = (dtor_t)&threadDtor,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL
        },
        .join = &join,
    },
    ._thread = 0,
};

Class *Thread = (Class *) &_description;
