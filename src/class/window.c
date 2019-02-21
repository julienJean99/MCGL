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
    XEvent *_event;
    Window _window;
    GC _gc;
    Display *_display;
    void (*_loop)(Object *, void *ret);
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
    disconnectToServer(this->_display);
    free(this->_event);
}

static void *start_update(
    mc_windowPr *this)
{
    size_t wait = 10000;
    void *ret = NULL;

    if (!this->_loop)
        return (NULL);
    while (wait) {
        --wait;
        XNextEvent(this->_display, this->_event);
        XClearWindow(this->_display, this->_window);
        if (this->_event->type == MapNotify)
            break;
        this->_loop(this, ret);
        XFlush(this->_display);
    }
    return (ret);
}

static void *open(
    Object *_this)
{
    mc_windowPr *this = _this;
    Display *dpy = connectToServer();
    XEvent *event = malloc(sizeof(XEvent));
    XSetWindowAttributes attribute = {
    .event_mask = StructureNotifyMask};

    if (!dpy || !event){
        free(dpy);
        free(event);
        return (NULL);
    }
    printf("looks fine %u %u\n",
        this->window.width, this->window.height);
    this->_window = XCreateWindow(
        dpy,
        XDefaultRootWindow(dpy),
        0, 0,
        this->window.width, this->window.height,
        0,
        CopyFromParent,
        CopyFromParent,
        CopyFromParent,
        0,
        &attribute);
    printf("looks fine\n");
    this->_bcColor = BlackPixel(dpy, DefaultScreen(dpy));
    this->_frColor =  WhitePixel(dpy, DefaultScreen(dpy));
    this->_event = event;
    this->_display = dpy;
    XMapWindow(this->_display, this->_window);
    this->_gc = XCreateGC(this->_display, this->_window, 0, 0);
    XSetForeground(this->_display, this->_gc, this->_frColor);
    XSetBackground(this->_display, this->_gc, this->_bcColor);
    XFlush(this->_display);
    while (1) {
        printf("nope\n");
        XNextEvent(this->_display, this->_event);
        if (this->_event->type == MapNotify)
            break;
    }
    if (this->_loop) {
        return (start_update(this));
    }
    return (NULL);
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
    ._event = NULL,
    ._window = 0,
    ._gc = 0,
    ._display = NULL,
    ._loop = NULL,
    ._bcColor = 0,
    ._frColor = 0,
};

Class   *mc_Window = (Class *)&_description;
