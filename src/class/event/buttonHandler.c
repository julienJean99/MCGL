/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Tue  2 Jul 09:49:39 CEST 2019 */
/* // button handler */
/* // */

#include <time.h>
#include "modular/new.h"
#include "internal/event/buttonHandler.h"

static void keyDtor(
    mc_key *this)
{
    delete(this->press);
    delete(this->hold);
    delete(this->release);
}

static void keyEvent(
    Object *_this,
    XKeyEvent *event)
{
    mc_key *this = _this;

    if (this->lastEvent == event->time &&
        this->hold) {
        this->hold->trigger(this->hold);
    } else if ((event->type == KeyPress ||
                event->type == ButtonPress) &&
               this->press) {
        this->press->trigger(this->press);
    } else if ((event->type == KeyRelease ||
                event->type == ButtonRelease) &&
               this->release) {
        this->release->trigger(this->release);
    }
    if (event->type == KeyRelease ||
        event->type == ButtonRelease) {
        this->isPress = false;
    } else if (event->type == KeyPress ||
               event->type == ButtonPress){
        this->isPress = true;
    }
    this->lastEvent = clock();
}

static void setHook(
    Object *_this,
    int state,
    mc_hook *hook)
{
    mc_key *this = _this;

    if (state == press) {
        if (this->press) {
            delete(this->press);
        }
        this->press = hook;
    } else if (state == hold) {
        if (this->hold) {
            delete(this->hold);
        }
        this->hold = hook;
    } else if (state == release) {
        if (this->release) {
            delete(this->release);
        }
        this->release = hook;
    }
}

void frame(
    Object *_this)
{
    mc_key *this = _this;

    if (this->isPress &&
        (clock() - this->lastEvent) > 20000 &&
        this->hold) {
        this->hold->trigger(this->hold);
    }
}

static mc_key _description = {
    {
        .__size__ = sizeof(mc_key),
        .__name__ = "mc_Key",
        .__ctor__ = NULL,
        .__dtor__ = (dtor_t)&keyDtor,
        .__str__ = NULL,
        .__add__ = NULL,
        .__sub__ = NULL,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL,
    },
    .keyEvent = &keyEvent,
    .setHook = &setHook,
    .frame = &frame,
    .press = NULL,
    .hold = NULL,
    .release = NULL,
    .lastEvent = 0
};

Class *mc_Key = (Class *)&_description;
