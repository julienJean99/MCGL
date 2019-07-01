/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon  1 Jul 11:01:01 CEST 2019 */
/* // button handler */
/* // */

#ifndef _BUTTONHANDLER_H_
#define _BUTTONHANDLER_H_

# include "modular/object.h"
# include "_hook.h"

enum keyState{
    press = 0,
    hold = 1,
    release = 2
};

typedef struct {
    Class _base;
    void (*push)(Object *this);
    void (*relise)(Object *this);
    void (*setHook)(Object *this, enum keyState state);
    _mc_hook states[3];
} mc_key;

#endif //_BUTTONHANDLER_H_
