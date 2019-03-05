/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sat 23 Feb 11:54:27 CET 2019 */
/* // Point */
/* // */

#ifndef _POINT_H_
#define _POINT_H_

#include "class/drawable/drawable.h"

typedef struct {
    mc_drawable base;
    int x;
    int y;
} mc_point;

extern Class *mc_Point;

#endif //_POINT_H_
