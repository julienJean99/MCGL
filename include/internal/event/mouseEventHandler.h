/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl  */
/* // */
/* // Mon  1 Jul 11:20:11 CEST 2019 */
/* // mouse event handler */
/* // */


#ifndef _MOUSEEVENTHANDLER_H_
#define _MOUSEEVENTHANDLER_H_

# include <X11/Xlib.h>
# include "event/hook.h"
# include "buttonHandler.h"
# include "modular/object.h"

typedef struct {
    Class _base;
    void (*pointerMouvment)(Object *this, XPointerMovedEvent *event);
    void (*buttonEvent)(Object *this, XButtonEvent *event);
    void (*setHook)(Object *this, va_list *args);
    mc_key *left;
    mc_key *right;
    mc_hook *mouvment;
    mc_mouseMouvment mouveArg;
} _mouseEventHandler;

extern Class *MouseEventHandler;

#endif //_MOUSEEVENTHANDLER_H_
