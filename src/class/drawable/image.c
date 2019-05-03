/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Tue  5 Mar 19:31:21 CET 2019 */
/* // image */
/* // */

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "modular/raise.h"
#include "internal/interface/drawable.h"
#include "internal/drawable/imagepr.h"
#include "internal/server_connection.h"

static void imageCtor(
    mc_imagePr *this,
    va_list *list)
{
    char *str = va_arg(*list, char *);
    Display *dys = getDisplay();
    int scr = XDefaultScreen(dys);
    Window win= XDefaultRootWindow(dys);

    this->_image.x = va_arg(*list, unsigned int);
    this->_image.y = va_arg(*list, unsigned int);
    this->_image.setImage(this, str);
    this->_image.base._gc = XCreateGC(
        dys,
        win,
        0,
        NULL);
    XSetForeground(
        dys,
        this->_image.base._gc,
        WhitePixel(
            dys,
            scr));

}

static void imageDtor(
    mc_imagePr *this)
{
    XDestroyImage(this->image);
}

static int drawImage(
    Object *_this,
    Display *display,
    Drawable *window)
{
    mc_imagePr *this = _this;

    if (!this->image)
        return -1;
    XPutImage(display,
              *window,
              ((mc_drawable *)this)->_gc,
              this->image,
              0, 0,
              this->_image.y, this->_image.x,
              this->image->width, this->image->height);
    return (0);
}

static char setImage(
    Object *_this,
    __attribute__((unused))char *path)
{
    mc_imagePr *this = _this;

    if (this->image) {
        XDestroyImage(this->image);
    }
    return (readPng(path, this));
}

static mc_imagePr _description = {
    {{{
                .__size__ = sizeof(mc_imagePr),
                .__name__ = "Image",
                .__ctor__ = (ctor_t)&imageCtor,
                .__dtor__ = (dtor_t)&imageDtor,
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
      ._draw = &drawImage,
      ._gc = NULL,
        },
     .setImage = &setImage,
     .getRawData = NULL,
     .getDimation = NULL
    },
    .image = NULL,
    ._bitDepth = 0,
};

Class *mc_Image = (Class *)&_description;
