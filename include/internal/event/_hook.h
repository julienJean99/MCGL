/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Sun 30 Jun 19:08:13 CEST 2019 */
/* // hook private */
/* // */

#ifndef __HOOK_H_
#define __HOOK_H_

#include "class/event/hook.h"

typedef struct {
    mc_hook base;
    Object *_arg;
    hookFunc _func;
} _mc_hook;

#endif //__HOOK_H_
