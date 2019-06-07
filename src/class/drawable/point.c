/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sat 23 Feb 12:46:21 CET 2019 */
/* // Point definition */
/* // */

#include <stdarg.h>
#include <X11/Xlib.h>
#include <string.h>
#include "internal/server_connection.h"
#include "internal/interface/drawable.h"
#include "internal/window.h"
#include "class/drawable/point.h"
#include "modular/new.h"

void pointCtor(
    mc_point *this,
    va_list *list)
{
    Display *dys = getDisplay();
    int scr = XDefaultScreen(dys);
    Window win= XDefaultRootWindow(dys);

    this->x = va_arg(*list, int);
    this->y = va_arg(*list, int);
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

int drawPoint(
    const Object *_this,
    Display *dys,
    Drawable *screen)
{
    const mc_point *this = _this;
    XDrawPoint(dys,
               *screen,
               this->base._gc,
               this->x, this->y);
    return (0);
}

mc_point *_add_(
    const mc_point *this,
    const mc_point *other)
{
    return (new(mc_Point,
                this->x + other->x,
                this->y + other->y));
}

mc_point *_sub_(
    const mc_point *this,
    const mc_point *other)
{
    return (new(mc_Point,
                this->x - other->x,
                this->y - other->y));
}

mc_point *_mul_(
    const mc_point *this,
    const mc_point *other)
{
    return (new(mc_Point,
                this->x * other->x,
                this->y * other->y));
}

mc_point *_div_(
    const mc_point *this,
    const mc_point *other)
{
    return (new(mc_Point,
                this->x / other->x,
                this->y / other->y));
}

bool _eq_(
    const mc_point *this,
    const mc_point *other)
{
    if (this->x == other->x &&
        this->y == other->y) {
        return (true);
    }
    return (false);
}

static mc_point _description = {
    {{
            .__size__ = sizeof(mc_point),
            .__name__ = "Point",
            .__ctor__ = (ctor_t)&pointCtor,
            .__dtor__ = NULL,
            .__str__ = NULL,
            .__add__ = (operator_t)&_add_,
            .__sub__ = (operator_t)&_sub_,
            .__mul__ = (operator_t)&_mul_,
            .__div__ = (operator_t)&_div_,
            .__eq__ = (comparator_t)&_eq_,
            .__gt__ = NULL,
            .__lt__ = NULL,
        },
     .setDrawFunc = NULL,
     ._gc = NULL,
     ._usrDraw = NULL,
     ._draw = &drawPoint,
    },
    .x = 0,
    .y = 0,
};

Class   *mc_Point = (Class *)&_description;
