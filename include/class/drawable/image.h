/*
** EPITECH PROJECT, 2019
** MCGL
** File description:
** image definition
*/

#ifndef _IMAGE_H_
#define _IMAGE_H_

# include "class/drawable/drawable.h"

typedef struct {
    mc_drawable base;
    /*! set the image */
    char (*setImage)(Object *, char *);
    /*! returns the raw data of the image*/
    const char *(*getRawData)(Object *);
    /*! returns the dimention of the image */
    const int *(*getDimation)(const Object *);
    int x;
    int y;
} mc_image;

extern Class *mc_Image;

#endif //_TEXT_H_
