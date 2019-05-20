/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Mon 18 Feb 22:52:00 CET 2019 */
/* // new and delete */
/* // */

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "modular/object.h"
#include "modular/raise.h"

Object *new(
    Class *class,
    ...)
{
    Class *ret = malloc(class->__size__);
    va_list ap;

    if (ret == NULL) {
        raise("Out of memory");
    }
    memcpy((Class *)ret, class, class->__size__);
    if (class->__ctor__) {
        va_start(ap, class);
        class->__ctor__(ret, &ap);
        va_end(ap);
    } else {
        free(ret);
        return (NULL);
    }
    return (ret);
}

Object *va_new(
    Class *class,
    va_list *ap)
{
    Class *ret = malloc(class->__size__);

    if (ret == NULL) {
        raise("Out of memory");
    }
        memcpy((Class *)ret, class, class->__size__);
    if (class->__ctor__) {
        class->__ctor__(ret, ap);
    }
    return (ret);
}

void delete(
    Object *ptr)
{
    if (!ptr) {
        return;
    } else if (((Class *)ptr)->__dtor__) {
        ((Class *)ptr)->__dtor__(ptr);
    }
    free(ptr);
}
