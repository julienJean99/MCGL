/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Wed  3 Jul 09:27:43 CEST 2019 */
/* // test event handler */
/* // */

#include <X11/Xlib.h>
#include "internal/event/buttonHandler.h"
#include "event/keydef.h"
#include "modular/new.h"
#include "internal/modular/listPr.h"
#include "internal/event/textEventHandler.h"

void textEventHandlerCtor(
    _textEventHandler *this,
    __attribute__((unused)) va_list *ap)
{
    this->keyList = new(List_t, mc_any, 0);
}

void textEventHandlerDtor(
    _textEventHandler *this)
{
    delete(this->keyList);
}

void newEvent(
    Object *_this,
    XKeyEvent *event)
{
    _textEventHandler *this = _this;
    list_t *keylist = this->keyList;
    unsigned int keySym = XLookupKeysym(event, 0);
    mc_key *tmp = (mc_key *)keylist->at(keylist, keySym);

    printf("sym is %u\n", keySym);
    if (tmp == NULL) {
        printf("nope\n");
        return;
    }
    tmp->keyEvent(tmp, event);
}

void setHook(
    Object *_this,
    va_list *ap)
{
    _textEventHandler *this = _this;
    unsigned int  key = va_arg(*ap, unsigned int);
    int state = va_arg(*ap, enum keyState);
    list_t *keylist = this->keyList;
    hookFunc func = va_arg(*ap, hookFunc);
    mc_key *tmp = (mc_key *)this->keyList->at(this->keyList, key);

    printf("new key is %u\n", key);
    if (tmp == NULL) {
        tmp = new(mc_Key);
        tmp->setHook(tmp,
                     state,
                     new(mc_Hook,
                         func,
                         va_arg(*ap, Object *)));
        keylist->emplace(
            keylist,
            key,
            (Class *)tmp);
        return;
    }
    tmp->setHook(tmp,
                 state,
                 new(mc_Hook,
                     func,
                     va_arg(*ap, Object *)));
}

static _textEventHandler _description = {
    {
        .__size__ = sizeof(_textEventHandler),
        .__name__ = "_textEventHandler",
        .__ctor__ = (ctor_t)&textEventHandlerCtor,
        .__dtor__ = (dtor_t)&textEventHandlerDtor,
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
    .keyList = NULL
};

Class *_TextEventHandler = (Class *)&_description;
