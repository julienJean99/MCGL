/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Sun 30 Jun 18:57:44 CEST 2019 */
/* // hook */
/* // */

#ifndef _HOOK_H_
#define _HOOK_H_

#include "modular/object.h"

typedef void *(*hookFunc)(Object *);

typedef struct {
    Class _base;
    /*! set the fuction to call */
    void (*setFunc)(Object *this, hookFunc);
    /*! set the argument to pass to the function */
    void (*setArg)(Object *this, Object *);
    /*! trigger the hook */
    void *(*trigger)(Object *this);
} mc_hook;

extern Class *mc_Hook;

#endif //_HOOK_H_
