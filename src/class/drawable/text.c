/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Tue  5 Mar 19:31:21 CET 2019 */
/* // text */
/* // */

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <X11/Xlib.h>
#include "modular/raise.h"
#include "internal/interface/drawable.h"
#include "internal/drawable/textpr.h"
#include "internal/server_connection.h"

static void textCtor(
    mc_textPr *this,
    va_list *list)
{
    char *str = va_arg(*list, char *);
    char *fontPath = va_arg(*list, char *);
    Display *dys = getDisplay();
    int scr = XDefaultScreen(dys);
    Window win= XDefaultRootWindow(dys);

    this->_text.setText(this, str);
    this->_text.setFont(this, fontPath);
    this->text.delta = 100;
    this->_text.base._gc = XCreateGC(
        dys,
        win,
        0,
        NULL);
    XSetForeground(
        dys,
        this->_text.base._gc,
        WhitePixel(
            dys,
            scr));
}

static void textDtor(
    mc_textPr *this)
{
    Display *display = getDisplay();

    XUnloadFont(display, this->text.font);
    free(this->text.chars);
}

static int drawText(
    Object *_this,
    Display *display,
    Drawable *screen)
{
    mc_textPr *this = _this;

    XDrawText(display,
              *screen,
              ((mc_drawable *)this)->_gc,
              this->_y, this->_x,
              &this->text,
              1);
    return (0);
}

static const char *getText(
    const Object *_this)
{
    const mc_textPr *this = _this;

    return (this->text.chars);
}

static int length(
    const Object *_this)
{
    const mc_textPr *this = _this;

    return (this->text.nchars);
}

static void setText(
    Object *_this,
    char *text)
{
    mc_textPr *this = _this;

    this->text.chars = text;
    this->text.nchars = strlen(text);
}

static void unloadFont(
    Font font,
    Display *display)
{
    if (font)
        XUnloadFont(display, font);
}

static void setFont(
    Object *_this,
    const char *path)
{
    mc_textPr *this = _this;
    Display *display = getDisplay();
    Font tmp = XLoadFont(display, path);

    if (!tmp) {
        raise("Invalid path to font\n");
        return;
    }
    unloadFont(this->text.font, display);
    this->text.font = tmp;
}

static mc_textPr _description = {
    {{{
                .__size__ = sizeof(mc_textPr),
                .__name__ = "Text",
                .__ctor__ = (ctor_t)&textCtor,
                .__dtor__ = (dtor_t)&textDtor,
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
      ._draw = &drawText,
      ._gc = 0,
        },
     .getText = &getText,
     .setText = &setText,
     .setFont = &setFont,
     .length = &length,
     .x = 0,
     .y = 0,
    },
    .text = {
        .chars = NULL,
        .nchars = 0,
        .delta = 0,
        .font = None,
    },
};

Class *mc_Text = (Class *)&_description;
