/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 13 May 08:47:28 CEST 2019 */
/* // list.const */
/* // */

#include <string.h>
#include "modular/new.h"
#include "internal/modular/listPr.h"

static void listCtor(
    list_pr *this,
    va_list *args)
{
    size_t max_len = va_arg(*args, size_t);
    size_t nb_args = va_arg(*args, size_t);

    this->_lenMax = ((max_len / PRELOAD) * PRELOAD);
    this->_len = 0;
    this->_tab= malloc(sizeof(void *) * this->_lenMax);
    if (!this->_tab) {
        raise("out of memory");
    }
    this->_tab = memset(this->_tab, 0, sizeof(void *) * this->_lenMax);
    while (nb_args) {
        --nb_args;
        this->base.pushBack(this, va_arg(*args, void *));
    }
}

static void listDtor(
    list_pr *this,
    __attribute__((unused))va_list *args)
{
    while (this->_len) {
        --this->_len;
        delete(this->_tab[this->_len]);
    }
    free(this->_tab);
}

static list_t *listAdd(
    const list_t *_this,
    const list_t *_other)
{
    const list_pr *this = (const list_pr *)_this;
    const list_pr *other = (const list_pr *)_other;
    list_pr *ret = new(List_t, other->_len + this->_len, 0);
    memcpy(ret->_tab, this->_tab, sizeof(void *) * this->_len);
    memcpy(&ret->_tab[this->_len], other->_tab, sizeof(void *) * other->_len);
    ret->_len = this->_len + other->_len;
    return ((list_t *)ret);
}

static char pushBack(
    void *_this,
    Object *object)
{
    list_pr *this = _this;
    void *ptr = NULL;

    if (this->_len == this->_lenMax) {
        ptr = realloc(
            this->_tab,
            sizeof(void *) * (this->_len + PRELOAD));
        if (!ptr) {
            return (0);
        }
        this->_lenMax += PRELOAD;
        this->_tab = ptr;
    }
    this->_tab[this->_len] = object;
    this->_len += 1;
    return (1);
}

static size_t length(
    const void *_this)
{
    const list_pr *this = _this;

    return this->_len;
}

static void *at(
    const Object *_this,
    size_t idx)
{
    const list_pr *this = _this;

    if (this->_len < (idx + 1)) {
        raise("index out of bound");
    }
    return (this->_tab[idx]);
}

static void *listRemove(
    Object *_this,
    size_t idx)
{
    list_pr *this = _this;
    void *ptr = NULL;

    if (this->_len < (idx + 1)) {
        raise("index out of bound");
    }
    ptr = this->_tab[idx];
    memmove(&this->_tab[idx + 1], &this->_tab[idx], (sizeof(void *) * (this->_len - idx)));
    return (ptr);
}

static list_t *map(
    const Object *_this,
    mapFunc *func,
    ...)
{
    const list_pr *this = _this;
    va_list args;
    va_list cp;
    list_pr *ret = new(List_t, this->_len, 0);
    size_t index = 0;


    if (!func || !ret) {
        return (NULL);
    }
    va_start(args, func);
    while (this->_len > index) {
        va_copy(cp, args);
        ret->base.pushBack(ret, func(this->_tab[index], &cp));
        ++index;
    }
    va_end(args);
    return ((list_t *)ret);
}

static list_pr _description = {
    {
        {
            .__size__ = sizeof(list_pr),
            .__name__ = "List_t",
            .__ctor__ = (ctor_t)&listCtor,
            .__dtor__ = (dtor_t)&listDtor,
            .__str__ = NULL,
            .__add__ = (operator_t)&listAdd,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL
        },
        .pushBack = &pushBack,
        .length = &length,
        .remove = &listRemove,
        .at = &at,
        .map = &map
    },
    ._tab = NULL,
    ._len = 0,
    ._lenMax = 0
};

Class   *List_t= (Class *)&_description;
