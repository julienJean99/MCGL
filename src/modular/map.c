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
    _map_t *this,
    va_list *args)
{
    size_t max_len = va_arg(*args, size_t);
    size_t nb_args = va_arg(*args, size_t);

    this->_mapSize = ((max_len / ALLOCSIZE) * ALLOCSIZE);
    this->_map = malloc(sizeof(void *) * this->_mapSize);
    this->_map = malloc(sizeof(void *) * this->_mapSize);
    if (!this->_map) {
        raise("out of memory");
    }
    this->_map = memset(this->_map, 0, sizeof(void *) * this->_mapSize);
    while (nb_args) {
        --nb_args;
        this->base.emplace(this, va_arg(*args, string *), va_arg(*args, void*));
    }
}

static void mapDtor(
    _map_t *this,
    __attribute__((unused))va_list *args)
{
    while (this->_mapSize) {
        --this->_mapSize;
        delete(this->_map[this->_mapSize]);
    }
    free(this->_map);
}

static ssize_t _findIdx(
    string *objKey,
    size_t idxLow,
    size_t idxHigh,
    const string **keyTab)
{
    size_t idxMid = idxLow + (idxHigh - idxLow) * .5;

    if (idxLow == idxHigh) {
        if (eq(objKey, keyTab[idxLow]))
            return (idxLow);
        return (-1);
    } else if (lt(objKey, keyTab[idxMid])) {
        return (_findIdx(objKey, idxLow, idxMid, keyTab));
    } else if (gt(objKey, keyTab[idxMid])) {
        return (_findIdx(objKey, idxMid, idxHigh, keyTab));
    }
    return (-1);
}

static void *findMap(
    Object *_this,
    string *key)
{
    _map_t *this = _this;
    ssize_t index = _findIdx(key,
                             0,
                             this->_mapSize - 1,
                             (const string **)this->_keyMap);

    if (index == -1) {
        return (NULL);
    }
    return (this->_map[index]);
}

static void swapMap(
    Object *_this,
    string *key1,
    string *key2)
{
    _map_t *this = _this;
    void *tmp = NULL;
    ssize_t idx1 = _findIdx(key1,
                            0,
                            this->_mapSize - 1,
                            (const string **)this->_keyMap);
    ssize_t idx2 = _findIdx(key2,
                            0,
                            this->_mapSize - 1,
                            (const string **)this->_keyMap);

    if (idx1 == -1 ||
        idx2 == -1) {
        return;
    }
    tmp = this->_map[idx1];
    this->_map[idx1] = this->_map[idx2];
    this->_map[idx2] = tmp;
    return;
}

static void _shiftMapR(
    Object *_this,
    size_t toFree)
{
    _map_t *this = _this;
    size_t index = this->_mapSize;
    void *tmp = NULL;

    --toFree;
    while (index != toFree) {
        --index;
        tmp = this->_map[index];
        this->_map[index + 1] = tmp;
    }
    ++this->_mapSize;
}

static size_t _findEmplace(
    string *objKey,
    size_t idxLow,
    size_t idxHigh,
    const string **keyTab)
{
    size_t idxMid = idxLow + (idxHigh - idxLow) * .5;

    if (idxLow == idxHigh) {
        if (eq(objKey, keyTab[idxLow]))
            return (idxLow);
        return (-1);
    } else if (lt(objKey, keyTab[idxMid])) {
        return (_findIdx(objKey, idxLow, idxMid, keyTab));
    } else if (gt(objKey, keyTab[idxMid])) {
        return (_findIdx(objKey, idxMid, idxHigh, keyTab));
    }
    return (-1);
}

static bool emplaceMap(
    Object *_this,
    string *key,
    void *object)
{
    _map_t *this = _this;
    void *tmp = NULL;
    ssize_t index = _findIdx(key,
                             0,
                             this->_mapSize - 1,
                             (const string **)this->_keyMap);

    if (index == -1) {
        tmp = realloc(
            this->_map,
            sizeof(void *) * (this->_mapSize + ALLOCSIZE));
        if (!tmp) {
            return (false);
        }
        this->_map = tmp;
        index = _findEmplace(key,
                             0,
                             this->_mapSize - 1,
                             (const string **)this->_keyMap);
        _shiftMapR(this, index);
    }
    if (this->_map[index]) {
        delete(this->_map[index]);
    }
    this->_map[index] = object;
    return (true);
}

static void *removeMap(
    Object *_this,
    string *key)
{
    _map_t *this = _this;
    size_t max = this->_mapSize;
    ssize_t index = _findIdx(key,
                             0,
                             this->_mapSize - 1,
                             (const string **)this->_keyMap);
    void *tmp = NULL;

    if (index == -1) {
        return (NULL);
    }
    tmp = this->_map[index];
    while ((unsigned)index != max) {
        this->_map[index] = this->_map[index + 1];
        ++index;
    }
    --this->_mapSize;
    return (tmp);
}

static _map_t _description = {
    {
        {
            .__size__ = sizeof(_map_t),
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
    ._keyMap = NULL,
    ._mapSize = 0
};

Class   *Map_t= (Class *)&_description;
