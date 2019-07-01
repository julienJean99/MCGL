/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon  1 Jul 10:35:46 CEST 2019 */
/* // key event handler */
/* // */

#ifndef _TEXTEVENTHANDLER_H_
#define _TEXTEVENTHANDLER_H_

# include <X11/Xlib.h>
# include "modular/list.h"
# include "textEvent.h"

typedef struct {
    void (*activate)(XKeyEvent *);
    list_t *keylist;
} _textEventHandler;

#endif //_TEXTEVENTHANDLER_H_
