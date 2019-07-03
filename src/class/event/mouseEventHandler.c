/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon  1 Jul 13:56:28 CEST 2019 */
/* // mouse event handler */
/* // */

#include <stdio.h>
#include "internal/event/mouseEventHandler.h"
#include "event/hook.h"
#include "modular/new.h"
#include "internal/event/buttonHandler.h"

static void mouseHandlerCtor(
    _mouseEventHandler *this,
    __attribute__((unused)) va_list *args)
{
    this->mouvment = new(mc_Hook, NULL, NULL);
    this->left = new(mc_Key);
    this->right = new(mc_Key);
}

static void mouseHandlerDtor(
    _mouseEventHandler *this)
{
    delete(this->mouvment);
    delete(this->left);
    delete(this->right);
}

static void pointerMouvment(
    Object *_this,
    XPointerMovedEvent *event)
{
    _mouseEventHandler *this = _this;
    mc_mouseMouvment *arg = &this->mouveArg;

    arg->x = event->x;
    arg->y = event->y;
    this->mouvment->trigger(this->mouvment);
}

static void buttonEvent(
    Object *_this,
    XButtonEvent *event)
{
    _mouseEventHandler *this = _this;

    if (event->button == Button1) {
        this->left->keyEvent(this->left, (XKeyEvent*)event);
    } else if (event->button == Button3) {
        this->right->keyEvent(this->right, (XKeyEvent*)event);
    }
}

static void setHook(
    Object *_this,
    va_list *args)
{
    _mouseEventHandler *this = _this;
    int event = va_arg(*args, int);
    int state = -1;
    hookFunc func = NULL;

    if (event == mouvment) {
        this->mouvment->setFunc(this->mouvment, va_arg(*args, hookFunc));
        this->mouveArg.param = va_arg(*args, Object *);
        this->mouvment->setArg(this->mouvment, &this->mouveArg);
    } else if (event == clickR) {
        state = va_arg(*args, int);
        func = va_arg(*args, hookFunc);
        this->right->setHook(this->right,
                             state,
                             new(mc_Hook,
                                 func,
                                 va_arg(*args, Object *)));
    } else if (event == clickL) {
        state = va_arg(*args, int);
        func = va_arg(*args, hookFunc);
        this->left->setHook(this->left,
                            state,
                            new(mc_Hook,
                                func,
                                va_arg(*args, Object *)));
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
