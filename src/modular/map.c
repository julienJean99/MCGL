/* // */
/* // This document created by Julien JEAN */
/* // For project : MCGL */
/* // */
/* // Wed 22 May 12:34:03 CEST 2019 */
/* // map definition */
/* // */

#include <string.h>
#include "modular/new.h"
#include "internal/modular/mapPr.h"

static void mapCtor(
    map_pr *this,
    va_list *args)
{
    size_t max_len = va_arg(*args, size_t);
    size_t nb_args = va_arg(*args, size_t);

    this->_mapSize = ((max_len / ALLOCSIZE) * ALLOCSIZE);
    this->_map = malloc(sizeof(void *) * this->_mapSize);
    if (!this->_map) {
        raise("out of memory");
    }
    this->_map = memset(this->_map, 0, sizeof(void *) * this->_mapSize);
    while (nb_args) {
        --nb_args;
        this->base.emplace(this, va_arg(*args, size_t), va_arg(*args, void*));
    }
}

static void mapDtor(
    map_pr *this,
    __attribute__((unused))va_list *args)
{
    while (this->_mapSize) {
        --this->_mapSize;
        delete(this->_map[this->_mapSize]);
    }
    free(this->_map);
}

static void *findMap(
    Object *_this,
    unsigned int key)
{
    map_pr *this = _this;

    if (key >= this->_mapSize) {
        return (NULL);
    }
    return (this->_map[key]);
}

static void swapMap(
    Object *_this,
    unsigned int key1,
    unsigned int key2)
{
    map_pr *this = _this;
    void *tmp = NULL;

    if (this->_mapSize <= key1 ||
        this->_mapSize <= key2 ) {
        return;
    }

    tmp = this->_map[key1];
    this->_map[key1] = this->_map[key2];
    this->_map[key2] = tmp;
    return;
}

static char emplaceMap(
    Object *_this,
    unsigned int key,
    void *object)
{
    map_pr *this = _this;
    void *tmp = NULL;

    if (key >= this->_mapSize) {
        tmp = realloc(
            this->_map,
            sizeof(void *) * (this->_mapSize + ALLOCSIZE));
        if (!tmp) {
            raise("Out of memory");
        }
        this->_map = tmp;
    }
    if (this->_map[key]) {
        delete(this->_map[key]);
    }
    this->_map[key] = object;
    return (1);
}

static void *removeMap(
    Object *_this,
    unsigned int key)
{
    map_pr *this = _this;
    void *tmp = NULL;

    if (key >= this->_mapSize) {
        return (NULL);
    }
    tmp = this->_map[key];
    this->_map[key] = NULL;
    return (tmp);
}


static map_pr _description = {
    {
        {
            .__size__ = sizeof(map_pr),
            .__name__ = "Map_t",
            .__ctor__ = (ctor_t)&mapCtor,
            .__dtor__ = (dtor_t)&mapDtor,
            .__str__ = NULL,
            .__add__ = NULL,
            .__sub__ = NULL,
            .__mul__ = NULL,
            .__div__ = NULL,
            .__eq__ = NULL,
            .__gt__ = NULL,
            .__lt__ = NULL
        },
        .find = &findMap,
        .swap = &swapMap,
        .emplace = &emplaceMap,
        .remove = &removeMap
    },
    ._map = NULL,
    ._mapSize = 0
};

Class   *Map_t= (Class *)&_description;
