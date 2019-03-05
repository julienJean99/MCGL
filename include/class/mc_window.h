/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Tue 19 Feb 15:40:32 CET 2019 */
/* // window definition */
/* // */

#ifndef _WINDOW_H_
#define _WINDOW_H_

# include "modular/object.h"

struct mc_drawable;

typedef int (*loop)(Object *);

typedef struct
{
    Class base;

    /* Call the function at every update */
    int (*open)(Object *);
    /* Set the function to call on update */
    void (*setLoop)(Object *, loop func);
    /* draws a drawabel on the window */
    int (*draw)(Object *, Object *);
    unsigned int width;
    unsigned int height;
} mc_window;

extern Class *mc_Window;

typedef int (*drawFunc)(Object *, mc_window *);

#endif //_WINDOW_H_
