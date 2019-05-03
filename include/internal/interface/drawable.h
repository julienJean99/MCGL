/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sat 23 Feb 12:49:08 CET 2019 */
/* // Drawable interface */
/* // */

#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include <X11/Xlib.h>
#include "modular/object.h"
#include "internal/window.h"

struct mc_drawable {
    Class base;
    void (*setDrawFunc)(Object *, drawFunc *);
    /* private */

    drawFunc _usrDraw;
    int (*_draw)(Object *, Display *, Drawable *);
    GC _gc;
};

typedef struct mc_drawable mc_drawable;

extern Class *mc_Drawable;

#endif //_DRAWABLE_H_
