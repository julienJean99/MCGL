/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Wed 20 Feb 21:17:30 CET 2019 */
/* // connection to the server */
/* // */

#ifndef _SERVER_CONNECTION_H_
#define _SERVER_CONNECTION_H_

#include <X11/Xlib.h>

/* connect_to_server.c */

// connect to the Xserver
Display *connectToServer(void);

// disconnect to the Xserver
char disconnectToServer(Display *);

#endif //_SERVER_CONNECTION_H_
