/* // */
/* // This document created by Julien JEAN */
/* // For project : CMGL */
/* // */
/* // Tue  5 Mar 19:16:09 CET 2019 */
/* // private text */
/* // */

#ifndef _TEXTPR_H_
#define _TEXTPR_H_

# include <X11/Xlib.h>
#include <stdint.h>
#include "class/drawable/image.h"

typedef struct {
    mc_image _image;
    XImage *image;
    int _bitDepth;
} mc_imagePr;

char readPng(const char *path, mc_imagePr *image);

#endif //_TEXTPR_H_
