/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sat 23 Feb 10:47:13 CET 2019 */
/* // drawable class */
/* // */

#include <X11/Xlib.h>
#include "modular/object.h"
#include "internal/interface/drawable.h"

static struct mc_drawable _description = {
    {
        .__size__ = sizeof(struct mc_drawable),
        .__name__ = "Drawable",
        .__ctor__ = NULL,
        .__dtor__ = NULL,
        .__str__ = NULL,
        .__add__ = NULL,
        .__sub__ = NULL,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL,
    },
    .setDrawFunc = NULL,

    ._usrDraw = NULL,
    ._draw = NULL,
};

Class   *mc_Drawable = (Class *)&_description;
