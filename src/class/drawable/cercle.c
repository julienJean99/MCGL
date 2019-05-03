/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sun 24 Feb 23:18:42 CET 2019 */
/* // cercle */
/* // */

#include <stdarg.h>
#include <X11/Xlib.h>
#include "internal/server_connection.h"
#include "internal/interface/drawable.h"
#include "class/drawable/cercle.h"

void cercleCtor(
    mc_cercle *this,
    va_list *list)
{
    Display *dys = getDisplay();
    int scr = XDefaultScreen(dys);
    Window win= XDefaultRootWindow(dys);

    this->x = va_arg(*list, int);
    this->y = va_arg(*list, int);
    this->rad = va_arg(*list, int);
    this->base._gc = XCreateGC(
        dys,
        win,
        0,
        NULL);
    XSetForeground(
        dys,
        this->base._gc,
        WhitePixel(
            dys,
            scr));
}

int drawCercle(
    Object *_this,
    Display *display,
    Drawable *screen)
{
    mc_cercle *this = _this;

    return (XDrawArc(
                display,
                *screen,
                this->base._gc,
                this->x - this->rad, this->y - this->rad,
                this->rad * 2, this->rad * 2,
                0, 360 * 64));
}

static mc_cercle _description = {
    {{
            .__size__ = sizeof(mc_cercle),
            .__name__ = "Point",
            .__ctor__ = (ctor_t)&cercleCtor,
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
     ._gc = NULL,
     ._usrDraw = NULL,
     ._draw = &drawCercle,
    },
    .x = 0,
    .y = 0,
    .rad = 0
};

Class   *mc_Cercle = (Class *)&_description;
