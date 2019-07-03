/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Tue 19 Feb 15:21:03 CET 2019 */
/* // window class */
/* // */

#include <unistd.h>
#include <stdarg.h>
#include "internal/interface/drawable.h"
#include "internal/window.h"
#include "internal/server_connection.h"
#include "modular/new.h"
#include "internal/event/event.h"

static void windowCtor(
    mc_windowPr *this,
    va_list *args)
{
    this->_height = va_arg(*args, unsigned int);
    this->_width = va_arg(*args, unsigned int);
    this->_drawMut = new(Mutex_t, NULL);
    this->_eventHandler = new(_Event);
}

static void windowDtor(
    mc_windowPr *this)
{
    Display *display = getDisplay();

    XUnmapWindow(display, this->_window);
    XDestroyWindow(display, this->_window);
    XFreePixmap(display, this->_screen);
    delete(this->_drawMut);
    delete(this->_eventHandler);
    free(this->_gc);
}

static int start_update(
    mc_windowPr *this)
{
    int ret = -1;
    struct timespec ts = {0, 999999999L / 60};
    Display *display = getDisplay();

    while (1) {
        while (XPending(display)) {
            XNextEvent(display, &this->_event);
            if (this->_event.type == DestroyNotify ||
                (this->_event.type == ClientMessage &&
                 this->_event.xclient.data.l[0] == (long)this->_delWin))
                return (ret);
            this->_eventHandler->newEvent(
                this->_eventHandler,
                this,
                &this->_event);
        }
        this->_eventHandler->_mouse->left->frame(this->_eventHandler->_mouse->left);
        this->_eventHandler->_mouse->right->frame(this->_eventHandler->_mouse->right);
        nanosleep(&ts, NULL);
        XSetForeground(display, this->_gc, this->_bcColor);
        XFillRectangle(
            display,
            this->_window,
            this->_gc,
            0, 0,
            this->_width,
            this->_height);
        XSetForeground(display, this->_gc, this->_frColor);
        if (!this->_loop) {
            break;
        }
        ret = this->_loop(this);
        XFlush(display);
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
    Display *display = getDisplay();

    if (!display){
        raise("no display");
        return (-1);
    }
    this->_bcColor = BlackPixel(
        display,
        DefaultScreen(display));
    this->_frColor =  WhitePixel(
        display,
        DefaultScreen(display));
    this->_window = XCreateWindow(
        display,
        XDefaultRootWindow(display),
        0, 0,
        this->_width, this->_height,
        0,
        CopyFromParent,
        CopyFromParent,
        CopyFromParent,
        0,
        &attribute);
    this->_delWin = XInternAtom(display, "WM_DELETE_WINDOW", True);
    this->_screen = XCreatePixmap(
        display,
        this->_window,
        this->_width, this->_height,
        32);
    this->_gc = XCreateGC(display, this->_window, 0, 0);
    XSetForeground(display, this->_gc, this->_frColor);
    XSetBackground(display, this->_gc, this->_bcColor);
    XSelectInput(display, this->_window, eventM);
    XSetWMProtocols(display, this->_window, &this->_delWin, 1);
    XMapWindow(display, this->_window);
    while (1) {
        XNextEvent(display, &this->_event);
        if (this->_event.type == MapNotify)
            break;
    }
    return (start_update(this));
}

static void setLoop(
    Object *_this,
    loop func)
{
    mc_windowPr *this = _this;

    this->_loop = func;
}

static int draw(
    Object *_this,
    const Object *_obj)
{
    mc_windowPr *this = _this;
    const mc_drawable *obj = _obj;
    Display *display = getDisplay();
    int tmp = 0;

    this->_drawMut->lock(this->_drawMut);
    if (obj->_usrDraw) {
        tmp = obj->_usrDraw(obj, (mc_window *)this);
    } else if (obj->_draw) {
        tmp = obj->_draw(obj, display, &this->_window);
    }
    this->_drawMut->unlock(this->_drawMut);
    return (tmp);
}

static void setHook(
    Object *_this,
    enum eventCategory category,
    ...)
{
    mc_windowPr *this = _this;
    va_list ap;

    va_start(ap, category);
    this->_eventHandler->setHook(this->_eventHandler, category, &ap);
    va_end(ap);
}

static void winClose(
    Object *_this)
{
    mc_windowPr *this = _this;

    this->_loop = NULL;
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
     .setHook = &setHook,
     .close = &winClose,
    },
    ._width = 0,
    ._height = 0,
    ._event = {},
    ._window = 0,
    ._gc = 0,
    ._loop = NULL,
    ._bcColor = 0,
    ._frColor = 0,
    ._delWin = 0,
    ._screen = 0,
    ._drawMut = NULL,
    ._eventHandler = NULL
};

Class   *mc_Window = (Class *)&_description;
