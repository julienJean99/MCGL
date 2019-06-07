/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Fri 24 May 16:26:24 CEST 2019 */
/* // string */
/* // */

#include <string.h>
#include "internal/modular/stringPr.h"

static void strCtor(
    stringPr *this,
    va_list *ap)
{
    this->base.setPointer((string *)this, va_arg(*ap, char *));
}

static void strDtor(
    stringPr *this,
    __attribute__((unused))va_list *ap)
{
    free(this->_str);
}

static string *strAdd(
    stringPr *this,
    stringPr *other)
{
    char *tmp = malloc(sizeof(char) * (this->_len + other->_len));

    if (!tmp) {
        raise("out of memory");
    }
    memcpy(tmp, this->_str, this->_len);
    memcpy(&tmp[this->_len], other->_str, other->_len);
    return (new(String, tmp));
}

static string *to_string(
    string *this)
{
    return (this);
}

static bool strEq(
    const stringPr *this,
    const stringPr *other)
{
    return (strcmp(this->_str, other->_str) == 0);
}

static bool strGt(
    const stringPr *this,
    const stringPr *other)
{
    return (strcmp(this->_str, other->_str) > 0);
}

static bool strLt(
    const stringPr *this,
    const stringPr *other)
{
    return (strcmp(this->_str, other->_str) < 0);
}

static void setPointer(
    string *_this,
    char *str)
{
    stringPr *this = (stringPr *) _this;

    this->_len = strlen(str);
    this->_str = str;
}

static const char *getPointer(
    const string *_this)
{
    return (((stringPr *)_this)->_str);
}

static size_t length(
    const string *_this)
{
    return (((stringPr *)_this)->_len);
}

static bool resize(
    string *_this,
    size_t newLen,
    char c)
{
    stringPr *this = (stringPr *) _this;
    char *tmp = realloc(this->_str, newLen);

    if (!tmp) {
        return (false);
    } else if (this->_len < newLen) {
        memset(tmp + this->_len, c, newLen - this->_len);
    }
    this->_str = tmp;
    this->_len = newLen;
    return (true);
}

static stringPr _description = {
    {
        {
            .__size__ = sizeof(stringPr),
            .__name__ = "String",
            .__ctor__ = (ctor_t)&strCtor,
            .__dtor__ = (dtor_t)&strDtor,
            .__str__ = (to_string_t)&to_string,
            .__add__ = (operator_t)&strAdd,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = (comparator_t)&strEq,
            .__gt__ = (comparator_t)&strGt,
            .__lt__ = (comparator_t)&strLt
        },
        .setPointer = &setPointer,
        .getPointer = &getPointer,
        .length = &length,
        .resize = &resize
    },
    ._str = NULL,
    ._len = 0
};

Class *String = (Class *)&_description;
