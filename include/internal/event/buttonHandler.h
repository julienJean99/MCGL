/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon  1 Jul 11:01:01 CEST 2019 */
/* // button handler */
/* // */

#ifndef _BUTTONHANDLER_H_
#define _BUTTONHANDLER_H_

# include <X11/Xlib.h>
# include "modular/object.h"
# include "_hook.h"

typedef struct {
    Class _base;
    void (*keyEvent)(Object *this, XKeyEvent *);
    void (*setHook)(Object *this, int, mc_hook *);
    void (*frame)(Object *this);
    mc_hook *press;
    mc_hook *hold;
    mc_hook *release;
    Time lastEvent;
    bool isPress;
} mc_key;

extern Class *mc_Key;
#endif //_BUTTONHANDLER_H_

#ifndef _KEYSTATE_
# define _KEYSTATE_

enum keyState{
    press = 0,
    hold = 1,
    release = 2
};

# endif  /* _KEYSTATE_ */
