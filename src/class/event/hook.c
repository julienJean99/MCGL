/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Sun 30 Jun 19:12:58 CEST 2019 */
/* // hook */
/* // */

#include "internal/event/_hook.h"
#include "modular/new.h"

static void hookCtor(
    _mc_hook *this,
    va_list *args)
{
    this->_func = va_arg(*args, hookFunc);
    this->_arg= va_arg(*args, void *);
}

static void hookDtor(_mc_hook *this)
{
    delete(this->_arg);
}

static void setFunc(
    _mc_hook *this,
    hookFunc func)
{
    this->_func = func;
}

static void setArg(
    _mc_hook *this,
    Object *arg)
{
    this->_arg = arg;
}

void *trigger(_mc_hook *this)
{
    if (this->_func) {
        return (this->_func(this->_arg));
    }
    return (NULL);
}


static _mc_hook _description = {
    {{
            .__size__ = sizeof(_mc_hook),
            .__name__ = "mc_Hook",
            .__ctor__ = (ctor_t)&hookCtor,
            .__dtor__ = (dtor_t)&hookDtor,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL,
        },
     .setFunc = &setFunc,
     .setArg = &setArg,
     .trigger = &trigger,
    },
    ._func = NULL,
    ._arg = NULL,
};

Class *mc_Hook = (Class *)&_description;
