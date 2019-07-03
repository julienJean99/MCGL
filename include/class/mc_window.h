/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Tue 19 Feb 15:40:32 CET 2019 */
/* // window definition */
/* // */

#ifndef _WINDOW_H_
#define _WINDOW_H_

# include "modular/object.h"
# include "event/hook.h"

struct mc_drawable;

typedef int (*loop)(Object *);

typedef struct
{
    Class base;
    /*! Call the function at every update */
    int (*open)(Object *this);
    /*! Set the function to call on update */
    void (*setLoop)(Object *this, loop func);
    /*! draws a drawabel on the window */
    int (*draw)(Object *this, const Object *);
    /*! used to set hooks: see hook.h for more info */
    void (*setHook)(Object *this, enum eventCategory, ...);
    /*! closes the window */
    void (*close)(Object *this);
} mc_window;

extern Class *mc_Window;

typedef int (*drawFunc)(const Object *, mc_window *);

#endif //_WINDOW_H_
