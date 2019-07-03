/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Sun 30 Jun 18:57:44 CEST 2019 */
/* // hook */
/* // */

#ifndef _HOOK_H_
#define _HOOK_H_

#include "modular/object.h"

typedef void *(*hookFunc)(Object *);

typedef struct {
    Class _base;
    /*! set the fuction to call */
    void (*setFunc)(Object *this, hookFunc);
    /*! set the argument to pass to the function */
    void (*setArg)(Object *this, Object *);
    /*! trigger the hook */
    void *(*trigger)(Object *this);
} mc_hook;

extern Class *mc_Hook;

#ifndef _KEYSTATE_
# define _KEYSTATE_

/* for each button you can chouse between 3 state */

enum keyState{
    press ,
    hold,
    release
};

# endif  /* _KEYSTATE_ */

/* Event Hook */

enum eventCategory {
    mouse,
    keyBoard,
    window
};

/* MOUSE HOOK */

enum mouseEvent {
    mouvment,
    clickR,
    clickL,
};

/*! parameter given to the mouse moovment hool on trigger */
typedef struct {
    int x;
    int y;
    Object *param;
} mc_mouseMouvment;

/*! type for the mouse mouvment */
typedef void (*MouseMouvmentHook)(mc_mouseMouvment *arg);
#endif //_HOOK_H_
