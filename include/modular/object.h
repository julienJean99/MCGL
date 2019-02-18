/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Mon 18 Feb 22:59:58 CET 2019 */
/* // modular c base definition */
/* // */

#ifndef CLASS_H
# define CLASS_H

# include <sys/types.h>
# include <stdarg.h>
# include <stdbool.h>
# include "raise.h"

typedef void Object;
typedef void (*ctor_t)(Object *this, va_list *args);
typedef void (*dtor_t)(Object *this);
typedef const char *(*to_string_t)(Object *this);
typedef Object *(*operator_t)(const Object *this, const Object *other);
typedef bool (*comparator_t)(const Object *this, const Object *other);

typedef struct {
    const size_t __size__;
    const char   *__name__;
    ctor_t       __ctor__;
    dtor_t       __dtor__;
    to_string_t  __str__;
    operator_t   __add__;
    operator_t   __sub__;
    operator_t   __mul__;
    operator_t   __div__;
    comparator_t __eq__;
    comparator_t __gt__;
    comparator_t __lt__;
} Class;

# define str(o)    (((Class *)o)->__str__ != NULL ? ((Class *)o)->__str__(o) : ((Class *)o)->__name__)
# define add(a, b) (Class *)a)->__add__(a, b)
# define sub(a, b) ((Class *)a)->__sub__(a, b)
# define mul(a, b) ((Class *)a)->__mul__(a, b)
# define div(a, b) ((Class *)a)->__div__(a, b)
# define eq(a, b)  ((Class *)a)->__eq__(a, b)
# define gt(a, b)  ((Class *)a)->__gt__(a, b)
# define lt(a, b)  ((Class *)a)->__lt__(a, b)

#endif
