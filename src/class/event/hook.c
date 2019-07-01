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

static void setFunc(
    Object *_this,
    hookFunc func)
{
    _mc_hook *this = _this;

    this->_func = func;
}

static void setArg(
    Object *_this,
    Object *arg)
{
    _mc_hook *this = _this;

    this->_arg = arg;
}

static void *trigger(Object *_this)
{
    _mc_hook *this = _this;

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
            .__dtor__ = NULL,
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
