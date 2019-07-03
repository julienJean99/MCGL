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
#include "internal/window.h"

static void eventCtor(
    _event *this,
    __attribute__((unused)) va_list *ap)
{
    this->_mouse = new(MouseEventHandler);
    this->_text = new(_TextEventHandler);
}

static void eventDtor(
    _event *this)
{
    delete(this->_mouse);
    delete(this->_text);
}

static void newEvent(
    Object *_this,
    mc_windowPr *win,
    XEvent *event)
{
    _event *this = (_event *)_this;

    if (event->type == ButtonPress ||
        event->type == ButtonRelease) {
        this->_mouse->buttonEvent(this->_mouse, &event->xbutton);
    } else if (event->type == MotionNotify) {
        this->_mouse->pointerMouvment(this->_mouse, &event->xmotion);
    } else if (event->type == KeyPress ||
               event->type == KeyRelease) {
        this->_text->newEvent(this->_text, &event->xkey);
    } else if (event->type == ConfigureNotify) {
        win->_height = event->xconfigure.height;
        win->_width = event->xconfigure.width;
    }
}

static void setHook(
    Object *_this,
    enum eventCategory category,
    va_list *ap)
{
    _event *this = _this;

    if (category == mouse) {
        this->_mouse->setHook(this->_mouse, ap);
    } else if (category == keyBoard) {
        this->_text->setHook(this->_text, ap);
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
