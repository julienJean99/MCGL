/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sun 24 Feb 11:53:45 CET 2019 */
/* // internat window */
/* // */

#ifndef _WINDOWPR_H_
#define _WINDOWPR_H_

# include <X11/Xlib.h>
# include <X11/Xatom.h>
# include "class/mc_window.h"

typedef struct
{
    mc_window window;
    unsigned int _width;
    unsigned int _height;
    XEvent _event;
    Window _window;
    GC _gc;
    loop _loop;
    int _bcColor;
    int _frColor;
    Atom _delWin;
    Pixmap _screen;
} mc_windowPr;

#endif //_WINDOW_H_
