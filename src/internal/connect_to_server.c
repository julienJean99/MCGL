/* // */
/* // This document created by Julien JEAN */
/* // For project : creat window  */
/* // */
/* // Sat Nov 17 19:42:24 CET 2018 */
/* // connect to the server */
/* // */

#include <X11/Xlib.h>
#include "modular/raise.h"

Display *display = NULL;

// connect to the Xserver
__attribute__((constructor)) static void connectToServer(void)
{
    display = XOpenDisplay(NULL);

    if (display == NULL){
        raise("A Problem acured while connecting to the server X\
please check your DISPLAY env variable");
    }
}

// return the display
Display *getDisplay(void)
{
    if (!display) {
        connectToServer();
    }
    return (display);
}

// disconnect to the Xserver
__attribute__((destructor))static void disconnectToServer(void)
{
    if (display == NULL || XCloseDisplay(display) == -1) {
        raise("Invalide display");
    }
}
