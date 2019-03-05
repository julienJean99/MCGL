/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sat 23 Feb 10:52:45 CET 2019 */
/* // drawable def */
/* // */

#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "modular/object.h"
#include "class/mc_window.h"

struct mc_drawable {
    Class base;
    /* set the function when drawing the object */
    void (*setDrawFunc)(Object *, drawFunc *);
    char pad[16];
};


typedef struct mc_drawable mc_drawable;

extern Class *mc_Drawable;

#endif //_DRAWABLE_H_
