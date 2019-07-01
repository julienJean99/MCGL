/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Tue 18 Jun 15:00:03 CEST 2019 */
/* // event */
/* // */

#ifndef _EVENT_H_
#define _EVENT_H_

# include "class/event/hook.h"
# include "modular/object.h"
# include "textEventHandler.h"
# include "mouseEventHandler.h"

typedef struct {
    Class _base;
    void (*newEvent)(Object *this, XEvent *event);
    void (*setHook)(Object *this, enum eventCategory, va_list *);
    _textEventHandler *_text;
    _mouseEventHandler *_mouse;
} _event;

extern Class *_Event;

#endif //_EVENT_H_
