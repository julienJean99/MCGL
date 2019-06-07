/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Fri 24 May 16:10:24 CEST 2019 */
/* // string */
/* // */

#ifndef _STRINGPR_H_
#define _STRINGPR_H_

#include "modular/string.h"

typedef struct {
    string base;
    char *_str;
    size_t _len;
} stringPr;

#endif //_STRINGPR_H_
