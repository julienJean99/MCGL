/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Tue 19 Feb 15:21:03 CET 2019 */
/* // window class */
/* // */

#include <stdarg.h>
#include <X11/Xlib.h>
#include "class/mc_window.h"
#include "internal/server_connection.h"

typedef struct
{
    mc_window window;
    XEvent _event;
    Window _window;
    GC _gc;
    Display *_display;
    loop _loop;
    int _bcColor;
    int _frColor;
} mc_windowPr;

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
    free(this->_gc);
    disconnectToServer(this->_display);
}

static int start_update(
    mc_windowPr *this)
{
    int ret = 0;
    long eventM = ExposureMask | KeyPressMask | KeyReleaseMask |
        PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
        StructureNotifyMask;

    while (1) {
        while (XCheckMaskEvent(this->_display, eventM, &this->_event))
            if (this->_event.type == DestroyNotify)
                break;
        XClearWindow(this->_display, this->_window);
        ret = this->_loop(this);
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
    this->_gc = XCreateGC(this->_display, this->_window, 0, 0);
    XSetForeground(this->_display, this->_gc, this->_frColor);
    XSetBackground(this->_display, this->_gc, this->_bcColor);
    XSelectInput(this->_display, this->_window, eventM);
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

static mc_windowPr _description = {
    {{
        .__size__ = sizeof(mc_windowPr),
        .__name__ = "Player",
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
};

Class   *mc_Window = (Class *)&_description;
