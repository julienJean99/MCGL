/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon  1 Jul 13:56:28 CEST 2019 */
/* // mouse event handler */
/* // */

#include <stdio.h>
#include "internal/event/mouseEventHandler.h"
#include "class/event/hook.h"
#include "modular/new.h"

static void mouseHandlerCtor(
    _mouseEventHandler *this,
    __attribute__((unused)) va_list *args)
{
    this->mouvment = new(mc_Hook, NULL, NULL);
}

static void mouseHandlerDtor(
    _mouseEventHandler *this)
{
    delete(this->mouvment);
}

static void pointerMouvment(
    Object *_this,
    XPointerMovedEvent *event)
{
    _mouseEventHandler *this = _this;
    mc_mouseMouvment *arg = &this->mouveArg;

    printf("mouse mouvment\n");
    arg->x = event->x;
    arg->y = event->y;
    this->mouvment->base.trigger(this->mouvment);
}

static void buttonEvent(
    Object *this,
    XButtonEvent *event)
{

}

static void setHook(
    Object *_this,
    va_list *args)
{
    _mouseEventHandler *this = _this;
    int event = va_arg(*args, int);

    printf("mouse Handler\n");
    if (event == mouvment) {
        this->mouvment->_func = va_arg(*args, hookFunc);
        this->mouveArg.param = va_arg(*args, Object *);
        this->mouvment->_arg = &this->mouveArg;
    }
}

static _mouseEventHandler _description ={
    {
        .__size__ = sizeof(_mouseEventHandler),
        .__name__ = "mouseEventHandler",
        .__ctor__ = (ctor_t)&mouseHandlerCtor,
        .__dtor__ = (dtor_t)&mouseHandlerDtor,
        .__str__ = NULL,
        .__add__ = NULL,
        .__sub__ = NULL,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL,
    },
    .pointerMouvment = &pointerMouvment,
    .buttonEvent = &buttonEvent,
    .setHook = &setHook,
    .left = NULL,
    .right = NULL,
    .mouvment = NULL,
    .mouveArg = {
        .x = 0,
        .y = 0,
        .param = NULL
    }
};

Class *MouseEventHandler = (Class *) &_description;
