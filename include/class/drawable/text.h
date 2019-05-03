/*
** EPITECH PROJECT, 2019
** MCGL
** File description:
** text definition
*/

#ifndef _TEXT_H_
#define _TEXT_H_

# include <X11/Xlib.h>
# include "class/drawable/drawable.h"

typedef struct {
    mc_drawable base;
    /*! return the text */
    const char *(*getText)(const Object *);
    /*! set the text */
    void (*setText)(Object *, char *);
    /*! set the Font */
    void (*setFont)(Object *, const char *);
    /*! return the length of the text */
    int (*length)(const Object *);
    int x;
    int y;
} mc_text;

extern Class *mc_Text;

#endif //_TEXT_H_
