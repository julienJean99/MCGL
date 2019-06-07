/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Wed 22 May 12:23:31 CEST 2019 */
/* // map */
/* // */

#ifndef _MAPPR_H_
#define _MAPPR_H_

#include "modular/map.h"

#define ALLOCSIZE 128

typedef struct {
    map_t base;
    void **_map;
    size_t _mapSize;
} map_pr;

#endif //_MAPPR_H_
