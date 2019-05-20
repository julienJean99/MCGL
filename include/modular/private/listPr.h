/* // */
/* // This document created by Julien JEAN */
/* // For project : private */
/* // */
/* // Mon 20 May 10:48:15 CEST 2019 */
/* // list */
/* // */

#ifndef _LISTPR_H_
#define _LISTPR_H_

#include "modular/list.h"

#define PRELOAD 128

typedef struct {
    list_t base;
    void **_tab;
    size_t _len;
    size_t _lenMax;
} list_pr;

#endif //_LISTPR_H_
