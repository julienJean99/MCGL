/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sun 24 Feb 16:46:02 CET 2019 */
/* // line */
/* // */

#include <X11/Xlib.h>
#include <stdarg.h>
#include "internal/interface/drawable.h"
#include "class/drawable/line.h"

void lineCtor(
    mc_line *this,
    va_list *list)
{
    this->ax = va_arg(*list, int);
    this->ay = va_arg(*list, int);
    this->bx = va_arg(*list, int);
    this->by = va_arg(*list, int);
}

int drawLine(
    Object *_this,
    Display *display,
    Drawable *screen,
    GC *gc)
{
    mc_line *this = _this;

    return (XDrawLine(
                display,
                *screen,
                *gc,
                this->ax, this->ay,
                this->bx, this->by));
}

static mc_line _description = {
    {{
            .__size__ = sizeof(mc_line),
            .__name__ = "Point",
            .__ctor__ = (ctor_t)&lineCtor,
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
     ._draw = &drawLine,
    },
    .ax = 0,
    .ay = 0,
    .bx = 0,
    .by = 0
};

Class   *mc_Line = (Class *)&_description;
