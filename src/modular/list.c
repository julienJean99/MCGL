/* // */
/* // This document created by Julien JEAN */
/* // For project : mcgl */
/* // */
/* // Mon 13 May 08:47:28 CEST 2019 */
/* // list.const */
/* // */

#include <string.h>
#include "modular/new.h"
#include "modular/thread.h"
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
        this->base.pushBack((list_t *)this, va_arg(*args, void *));
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

static bool pushBack(
    list_t *_this,
    Class *object)
{
    list_pr *this = (list_pr *)_this;
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
    const list_t *_this)
{
    const list_pr *this = (list_pr *)_this;

    return this->_len;
}

static Class *at(
    const list_t *_this,
    size_t idx)
{
    const list_pr *this = (list_pr *)_this;

    if (this->_len < (idx + 1)) {
        raise("index out of bound");
    }
    return (this->_tab[idx]);
}

static Class *listRemove(
    list_t *_this,
    size_t idx)
{
    list_pr *this = (list_pr *)_this;
    void *ptr = NULL;

    if (this->_len < (idx + 1)) {
        raise("index out of bound");
    }
    ptr = this->_tab[idx];
    memmove(&this->_tab[idx + 1], &this->_tab[idx], (sizeof(void *) * (this->_len - idx)));
    return (ptr);
}

static list_t *map(
    const list_t *_this,
    mapFunc *func,
    ...)
{
    const list_pr *this = (list_pr *)_this;
    list_pr *ret = new(List_t, this->_len, 0);
    va_list args;
    thread *tmp = NULL;
    list_t *threadList = new(List_t, this->_len, 0);
    listArgs *argsList = malloc(sizeof(listArgs) * this->_len);
    size_t index = 0;

    if (!func) {
        return NULL;
    }
    va_start(args, func);


    if (!argsList || !threadList) {
        return (NULL);
    }
    while (this->_len > index) {
        va_copy(argsList[index].args, args);
        argsList[index].obj = this->_tab[index];
        argsList[index].index = index;
        threadList->pushBack(
            threadList,
            new(Thread, func, &argsList[index]));
        ++index;
    }
    va_end(args);
    while (index) {
        --index;
        tmp = (thread *)threadList->at(threadList, index);
        ret->base.pushBack((list_t *)ret, tmp->join(tmp));
    }
    delete(threadList);
    free(argsList);
    return ((list_t *)ret);
}

static void loop(
    const list_t *_this,
    loopFunc *func,
    ...)
{
    const list_pr *this = (list_pr *)_this;
    va_list args;
    thread *tmp = NULL;
    list_t *threadList = new(List_t, this->_len, 0);
    listArgs *argsList = malloc(sizeof(listArgs) * this->_len);
    size_t index = 0;

    if (!func || !argsList) {
        return;
    }
    va_start(args, func);
    while (this->_len > index) {
        va_copy(argsList[index].args, args);
        argsList[index].obj = this->_tab[index];
        argsList[index].index = index;
        threadList->pushBack(
            threadList,
            new(Thread, func, &argsList[index]));
        ++index;
    }
    va_end(args);
    while (index) {
        --index;
        tmp = (thread *)threadList->at(threadList, index);
        tmp->join(tmp);
    }
    delete(threadList);
    free(argsList);
    return;
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
        .map = &map,
        .loop = &loop
    },
    ._tab = NULL,
    ._len = 0,
    ._lenMax = 0
};

Class   *List_t= (Class *)&_description;
