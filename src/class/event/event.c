/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Tue 18 Jun 14:45:01 CEST 2019 */
/* // event */
/* // */

#include <stdio.h>

#include "X11/X.h"
#include "internal/event/event.h"
#include "modular/new.h"

static void eventCtor(
    _event *this,
    __attribute__((unused)) va_list *ap)
{
    this->_mouse = new(MouseEventHandler);
}

static void eventDtor(
    _event *this)
{
    delete(this->_mouse);
}

static void newEvent(
    Object *_this,
    XEvent *event)
{
    _event *this = (_event *)_this;

    printf("newEvent %d %d\n", MotionNotify, event->type);
    if (event->type == MotionNotify) {
        this->_mouse->pointerMouvment(this->_mouse, &event->xmotion);
    }
}

static void setHook(
    Object *_this,
    enum eventCategory category,
    va_list *ap)
{
    _event *this = _this;

    printf("event Handler\n");
    if (category == mouse) {
        this->_mouse->setHook(this->_mouse, ap);
    }
}

static _event _description = {
    {
        .__size__ = sizeof(_event),
        .__name__ = "_even",
        .__ctor__ = (ctor_t)&eventCtor,
        .__dtor__ = (dtor_t)&eventDtor,
        .__str__ = NULL,
        .__add__ = NULL,
        .__sub__ = NULL,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL,
    },
    .newEvent = &newEvent,
    .setHook = &setHook,
    ._text = NULL,
    ._mouse = NULL
};

Class *_Event = (Class *)&_description;
