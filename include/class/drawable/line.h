/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sun 24 Feb 16:47:12 CET 2019 */
/* // line def */
/* // */

#ifndef _LINE_H_
#define _LINE_H_

#include "class/drawable/drawable.h"

typedef struct {
    mc_drawable base;
    int ax;
    int ay;
    int bx;
    int by;
} mc_line;

extern Class *mc_Line;

#endif //_LINE_H_
