/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Sun 24 Feb 23:19:18 CET 2019 */
/* // cercle */
/* // */

#ifndef _CERCLE_H_
#define _CERCLE_H_

#include "class/drawable/drawable.h"

typedef struct {
    struct mc_drawable base;
    int x;
    int y;
    int rad;
} mc_cercle;

extern Class *mc_Cercle;

#endif //_CERCLE_H_
