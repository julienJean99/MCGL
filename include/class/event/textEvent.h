/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Tue 18 Jun 15:15:14 CEST 2019 */
/* // textEvent */
/* // */

#ifndef _TEXTEVENT_H_
#define _TEXTEVENT_H_

# include "modular/object.h"

typedef struct {
    Class base;
    char key[255];
    Object *param;
} mc_keyEvent;

typedef mc_keyEvent mc_keyRelease;
typedef mc_keyEvent mc_keyPress;

#endif //_TEXTEVENT_H_
