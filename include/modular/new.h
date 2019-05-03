/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Mon 18 Feb 22:52:35 CET 2019 */
/* // new delete header */
/* // */


#ifndef NEW_H
# define NEW_H

# include <stdarg.h>
# include "object.h"

/*! Create an object CLASS using parameters */
Object  *new(Class *class, ...);
/*! Create an object CLASS using a VA_LIST */
Object  *va_new(Class *class, va_list* ap);
/*! Call the destructor if not NULL and free the pointer */
void    delete(Object *ptr);

#endif
