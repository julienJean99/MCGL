/* // */
/* // This document created by Julien JEAN */
/* // For project : creat window  */
/* // */
/* // Sat Nov 17 19:42:24 CET 2018 */
/* // connect to the server */
/* // */

#include <X11/Xlib.h>
#include "modular/raise.h"

// connect to the Xserver
Display *connectToServer(void)
{
    Display *display = XOpenDisplay(NULL);

    if (display == NULL){
        raise("A Problem acured while connecting to the server X\
please check your DISPLAY env variable");
        return (NULL);
    }
    return (display);
}

// disconnect to the Xserver
char disconnectToServer(Display *display)
{
    if (display == NULL || XCloseDisplay(display) == -1){
        raise("Invalide display");
        return (-1);
    }
    return (0);
}
