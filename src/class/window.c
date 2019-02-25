/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Tue 19 Feb 15:21:03 CET 2019 */
/* // window class */
/* // */

#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#include "internal/window.h"
#include "internal/server_connection.h"
#include "internal/interface/drawable.h"

static void windowCtor(
    mc_windowPr *this,
    va_list *args)
{
    this->window.height = va_arg(*args, unsigned int);
    this->window.width = va_arg(*args, unsigned int);
}

static void windowDtor(
    mc_windowPr *this)
{
    XUnmapWindow(this->_display, this->_window);
    XDestroyWindow(this->_display, this->_window);
    XFreePixmap(this->_display, this->_screen);
    free(this->_gc);
    disconnectToServer(this->_display);
}

static int start_update(
    mc_windowPr *this)
{
    int ret = 0;
    struct timespec ts = {0, 999999999L / 60};

    while (1) {
        while (XPending(this->_display)) {
            XNextEvent(this->_display, &this->_event);
            if (this->_event.type == DestroyNotify ||
                (this->_event.type == ClientMessage && this->_event.xclient.data.l[0] == (long)this->_delWin))
                return (ret);
        }
        nanosleep(&ts, NULL);
        XSetForeground(this->_display, this->_gc, this->_bcColor);
        XFillRectangle(
            this->_display,
            this->_window,
            this->_gc,
            0, 0,
            this->window.width,
            this->window.height);
        XSetForeground(this->_display, this->_gc, this->_frColor);
        ret = this->_loop(this);
        XFlush(this->_display);
    }
    return (ret);
}

static int open(
    Object *_this)
{
    mc_windowPr *this = _this;
    long eventM = ExposureMask | KeyPressMask | KeyReleaseMask |
        PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
        StructureNotifyMask;
    XSetWindowAttributes attribute = {};

    this->_display = connectToServer();
    if (!this->_display){
        free(this->_display);
        return (-1);
    }
    this->_bcColor = BlackPixel(
        this->_display,
        DefaultScreen(this->_display));
    this->_frColor =  WhitePixel(
        this->_display,
        DefaultScreen(this->_display));
    this->_window = XCreateWindow(
        this->_display,
        XDefaultRootWindow(this->_display),
        0, 0,
        this->window.width, this->window.height,
        0,
        CopyFromParent,
        CopyFromParent,
        CopyFromParent,
        0,
        &attribute);
    this->_delWin = XInternAtom(this->_display, "WM_DELETE_WINDOW", True);
    this->_screen = XCreatePixmap(
        this->_display,
        this->_window,
        this->window.width, this->window.height,
        32);
    this->_gc = XCreateGC(this->_display, this->_window, 0, 0);
    XSetForeground(this->_display, this->_gc, this->_frColor);
    XSetBackground(this->_display, this->_gc, this->_bcColor);
    XSelectInput(this->_display, this->_window, eventM);
    XSetWMProtocols(this->_display, this->_window, &this->_delWin, 1);
    XMapWindow(this->_display, this->_window);
    while (1) {
        XNextEvent(this->_display, &this->_event);
        if (this->_event.type == MapNotify)
            break;
    }
    if (this->_loop) {
        return (start_update(this));
    }
    return (-1);
}

static void setLoop(
    Object *_this,
    loop func)
{
    mc_windowPr *this = _this;

    this->_loop = func;
}

int draw(
    Object *_this,
    struct mc_drawable *obj)
{
    mc_windowPr *this = _this;

    if (obj->_usrDraw) {
        return (obj->_usrDraw(obj, (mc_window *)this));
    } else if (obj->_draw) {
        return (obj->_draw(obj, this->_display, &this->_window, &this->_gc));
    }
    return (-1);
}

static mc_windowPr _description = {
    {{
        .__size__ = sizeof(mc_windowPr),
        .__name__ = "Window",
        .__ctor__ = (ctor_t)&windowCtor,
        .__dtor__ = (dtor_t)&windowDtor,
        .__str__ = NULL,
        .__add__ = NULL,
        .__sub__ = NULL,
        .__mul__ = NULL,
        .__div__ = NULL,
        .__eq__ = NULL,
        .__gt__ = NULL,
        .__lt__ = NULL,
        },
     .open = &open,
     .setLoop = &setLoop,
     .draw = &draw,
     .width = 0,
     .height = 0,
    },
    ._event = {},
    ._window = 0,
    ._gc = 0,
    ._display = NULL,
    ._loop = NULL,
    ._bcColor = 0,
    ._frColor = 0,
    ._delWin = 0,
    ._screen = 0,
};

Class   *mc_Window = (Class *)&_description;
