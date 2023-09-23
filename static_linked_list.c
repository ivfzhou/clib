/*
 * Copyright (c) 2023 ivfzhou
 * clib is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

#include <string.h>

#include "static_linked_list.h"

const static int ExpandThreshold = 256;

const static long double ExpandFactor = 1.25L;

const static long double ReduceFactor = 2L;

static _Bool _needReduce(StaticLinkedList *list) {
    return list->_length > ExpandThreshold && (list->_length * ReduceFactor <= list->_capacity);
}

static _Bool _needExpand(StaticLinkedList *list) {
    return list->_length >= list->_capacity;
}

static int _expandAndInsert(StaticLinkedList *list, int index, const void *elem) {
    if (list->_capacity < ExpandThreshold)
        list->_capacity += list->_capacity + 1;
    else
        list->_capacity = (int) (list->_capacity * ExpandFactor);

    void *newElems = malloc(list->_elemSize * list->_capacity);
    if (newElems == NULL)
        return 2;

    unsigned *newIndexed = malloc(sizeof(unsigned) * list->_capacity);
    if (newIndexed == NULL) {
        free(newElems);
        return 2;
    }

    if (list->_length && list->_elems != NULL)
        memcpy(newElems, list->_elems, list->_length * list->_elemSize);
    memcpy(newElems + list->_length * list->_elemSize, elem, list->_elemSize);

    if (index && list->_indexes != NULL)
        memcpy(newIndexed, list->_indexes, index * sizeof(unsigned));
    newIndexed[index] = list->_length;
    if (list->_length - index)
        memcpy(newIndexed + index + 1, list->_indexes + index, (list->_length - index) * sizeof(unsigned));

    free(list->_elems);
    free(list->_indexes);
    list->_elems = newElems;
    list->_indexes = newIndexed;

    list->_length++;
    return 0;
}

static int _reduceAndPop(StaticLinkedList *list, int index, void *elem) {
    unsigned elemIndex = list->_indexes[index];
    if (elem != NULL)
        memcpy(elem, list->_elems + elemIndex * list->_elemSize, list->_elemSize);
    list->_capacity = (int) (list->_length * ExpandFactor);

    void *newElems = malloc(list->_elemSize * (size_t) list->_capacity);
    if (newElems == NULL)
        return 2;

    unsigned *newIndexed = malloc(sizeof(unsigned) * (size_t) list->_capacity);
    if (newIndexed == NULL) {
        free(newElems);
        return 2;
    }

    if (elemIndex - 1)
        memcpy(newElems, list->_elems, list->_elemSize * (elemIndex - 1));
    if (list->_length - index - 1)
        memcpy(
                newElems + elemIndex * list->_elemSize,
                list->_elems + (elemIndex + 1) * list->_elemSize,
                (list->_length - index - 1) * list->_elemSize);

    if (index)
        memcpy(newIndexed, list->_indexes, index * sizeof(unsigned));
    if (list->_length - 1)
        memcpy(newIndexed + index, list->_indexes + index + 1, (list->_length - 1) * sizeof(unsigned));

    free(list->_elems);
    free(list->_indexes);
    list->_indexes = newIndexed;
    list->_elems = newElems;

    list->_length--;
    for (int i = 0; i < list->_length; i++)
        if (list->_indexes[i] > elemIndex)
            list->_indexes[i]--;

    return 0;
}

StaticLinkedList *staticLinkedList_alloc(size_t elemSize) {
    StaticLinkedList *list = malloc(sizeof(StaticLinkedList));
    list->_elemSize = elemSize;
    list->_indexes = list->_elems = NULL;
    list->_length = list->_capacity = 0;
    return list;
}

int staticLinkedList_free(StaticLinkedList *list) {
    free(list->_elems);
    free(list->_indexes);
    list->_indexes = list->_elems = NULL;
    list->_length = list->_capacity = 0;
    free(list);
    return 0;
}

size_t staticLinkedList_len(const StaticLinkedList *list) {
    return list->_length;
}

int staticLinkedList_get(const StaticLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    memcpy(elem, list->_elems + list->_indexes[index] * list->_elemSize, list->_elemSize);
    return 0;
}

int staticLinkedList_insert(StaticLinkedList *list, int index, const void *elem) {
    if (index > list->_length || index < 0)
        return 1;

    // 扩容
    if (_needExpand(list))
        return _expandAndInsert(list, index, elem);

    memcpy(list->_elems + list->_length * list->_elemSize, elem, list->_elemSize);
    if (list->_length - index)
        memmove(list->_indexes + index + 1, list->_indexes + index, (list->_length - index) * sizeof(unsigned));
    list->_indexes[index] = list->_length;
    list->_length++;
    return 0;
}

int staticLinkedList_del(StaticLinkedList *list, int index) {
    if (index >= list->_length || index < 0)
        return 1;
    if (_needReduce(list))
        return _reduceAndPop(list, index, NULL);
    unsigned elemIndex = list->_indexes[index];
    if (list->_length - index - 1)
        memmove(list->_elems + elemIndex * list->_elemSize, list->_elems + (elemIndex + 1) * list->_elemSize,
                (list->_length - index - 1) * list->_elemSize);
    if (list->_length - index - 1)
        memmove(list->_indexes + index, list->_indexes + index + 1, sizeof(unsigned) * (list->_length - index - 1));
    list->_length--;
    for (int i = 0; i < list->_length; i++)
        if (list->_indexes[i] > elemIndex)
            list->_indexes[i]--;
    return 0;
}

int
staticLinkedList_locate(const StaticLinkedList *list, ListElemComparer cmp, const void *elem, int *index) {
    for (int i = 0; i < list->_length; i++) {
        if (!cmp(list->_elems + list->_indexes[i] * list->_elemSize, elem)) {
            *index = (int) i;
            return 0;
        }
    }
    return -1;
}

int staticLinkedList_travel(const StaticLinkedList *list, ListElemVisitor visit) {
    for (int i = 0; i < list->_length - 1; i++)
        visit(list->_elems + list->_indexes[i] * list->_elemSize);

    return 0;
}

int staticLinkedList_clear(StaticLinkedList *list) {
    free(list->_elems);
    free(list->_indexes);
    list->_length = list->_capacity = 0;
    list->_indexes = list->_elems = NULL;
    return 0;
}

int staticLinkedList_rpop(StaticLinkedList *list, void *elem) {
    return staticLinkedList_getDel(list, list->_length - 1, elem);
}

int staticLinkedList_lpush(StaticLinkedList *list, const void *elem) {
    return staticLinkedList_insert(list, 0, elem);
}

int staticLinkedList_rpush(StaticLinkedList *list, const void *elem) {
    return staticLinkedList_insert(list, list->_length, elem);
}

int staticLinkedList_lpop(StaticLinkedList *list, void *elem) {
    return staticLinkedList_getDel(list, 0, elem);
}

int staticLinkedList_set(const StaticLinkedList *list, int index, const void *elem) {
    if (index < 0 || index >= list->_length)
        return 1;
    memcpy(list->_elems + list->_indexes[index] * list->_elemSize, elem, list->_elemSize);
    return 0;
}

int staticLinkedList_getDel(StaticLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    if (_needReduce(list))
        return _reduceAndPop(list, index, elem);
    unsigned elemIndex = list->_indexes[index];
    memcpy(elem, list->_elems + elemIndex * list->_elemSize, list->_elemSize);
    if (list->_length - index - 1)
        memmove(list->_elems + elemIndex * list->_elemSize, list->_elems + (elemIndex + 1) * list->_elemSize,
                (list->_length - index - 1) * list->_elemSize);
    if (list->_length - index - 1)
        memmove(list->_indexes + index, list->_indexes + index + 1, sizeof(unsigned) * (list->_length - index - 1));
    list->_length--;
    for (int i = 0; i < list->_length - 1; i++)
        if (list->_indexes[i] > elemIndex)
            list->_indexes[i]--;
    return 0;
}

int staticLinkedList_getSet(const StaticLinkedList *list, int index, void *elem) {
    void *tmp = malloc(list->_elemSize);
    if (tmp == NULL)
        return 2;
    memcpy(tmp, list->_elems + list->_indexes[index] * list->_elemSize, list->_elemSize);
    memcpy(list->_elems + list->_indexes[index] * list->_elemSize, elem, list->_elemSize);
    memcpy(elem, tmp, list->_elemSize);
    free(tmp);
    return 0;
}

int staticLinkedList_fprint(const StaticLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    for (int i = 0; i < list->_length - 1; i++) {
        size_t len = str(list->_elems + list->_indexes[i] * list->_elemSize, s);
        s[len] = '\000';
        fprintf(f, "%s, ", s);
    }
    if (list->_length > 0) {
        size_t len = str(list->_elems + list->_indexes[list->_length - 1] * list->_elemSize, s);
        s[len] = '\000';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
