/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon  1 Jul 10:35:46 CEST 2019 */
/* // key event handler */
/* // */

#ifndef _TEXTEVENTHANDLER_H_
#define _TEXTEVENTHANDLER_H_

# include <X11/Xlib.h>
# include "modular/list.h"
# include "textEvent.h"
# include "modular/object.h"

typedef struct {
    Class _base;
    void (*newEvent)(Object *this, XKeyEvent *);
    void (*setHook)(Object *this, va_list *);
    list_t *keyList;
} _textEventHandler;

extern Class *_TextEventHandler;

#endif //_TEXTEVENTHANDLER_H_
