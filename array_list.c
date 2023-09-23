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

#include "array_list.h"

const static int ExpandThreshold = 256;

const static long double ExpandFactor = 1.25L;

const static long double ReduceFactor = 2L;

static _Bool _needReduce(ArrayList *list) {
    return list->_length > ExpandThreshold && (list->_length * ReduceFactor <= list->_capacity);
}

static _Bool _needExpand(ArrayList *list) {
    return list->_length >= list->_capacity;
}

static int _expandAndInsert(ArrayList *list, int index, const void *elem) {
    if (list->_capacity < ExpandThreshold)
        list->_capacity += list->_capacity + 1;
    else
        list->_capacity = (int) ((long double) list->_capacity * ExpandFactor);

    void *newElems = malloc(list->_elemSize * list->_capacity);
    if (newElems == NULL)
        return 2;
    if (index && list->_elems != NULL)
        memcpy(newElems, list->_elems, list->_elemSize * index); // 复制前段
    if ((list->_length - index) && list->_elems != NULL)
        memcpy(newElems + (index + 1) * list->_elemSize, list->_elems + index * list->_elemSize,
               list->_elemSize * (list->_length - index));             // 复制后段
    memcpy(newElems + index * list->_elemSize, elem, list->_elemSize); // 设置新元素

    free(list->_elems);
    list->_elems = newElems;
    list->_length++;
    return 0;
}

static int _deallocAndPop(ArrayList *list, int index, void *elem) {
    if (elem != NULL)
        memcpy(elem, list->_elems + index * list->_elemSize, list->_elemSize);
    void *newElems = malloc(list->_elemSize * (int) (list->_length * ExpandFactor));
    if (newElems == NULL)
        return 2;
    if (index)
        memcpy(newElems, list->_elems, list->_elemSize * index); // 复制前段
    if (list->_length - index)
        memcpy(newElems + (index + 1) * list->_elemSize, list->_elems + index * list->_elemSize,
               list->_elemSize * (list->_length - index)); // 复制后段

    free(list->_elems);
    list->_elems = newElems;
    list->_length--;
    return 0;
}

ArrayList *arrayList_alloc(size_t elemSize) {
    ArrayList *list = malloc(sizeof(ArrayList));
    list->_elemSize = elemSize;
    list->_length = list->_capacity = 0;
    list->_elems = NULL;
    return list;
}

int arrayList_free(ArrayList *list) {
    free(list->_elems);
    list->_length = list->_capacity = 0;
    list->_elemSize = 0;
    list->_elems = NULL;
    free(list);
    return 0;
}

size_t arrayList_len(const ArrayList *list) {
    return list->_length;
}

int arrayList_get(const ArrayList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    memcpy(elem, list->_elems + index * list->_elemSize, list->_elemSize);
    return 0;
}

int arrayList_insert(ArrayList *list, int index, const void *elem) {
    if (index > list->_length || index < 0)
        return 1;
    if (_needExpand(list))
        return _expandAndInsert(list, index, elem);

    if (list->_length - index)
        memmove(list->_elems + (index + 1) * list->_elemSize, list->_elems + index * list->_elemSize,
                list->_elemSize * (list->_length - index));                // 从index往后移动一位
    memcpy(list->_elems + index * list->_elemSize, elem, list->_elemSize); // 复制元素
    list->_length++;
    return 0;
}

int arrayList_del(ArrayList *list, int index) {
    if (index >= list->_length || index < 0)
        return 1;
    if (_needReduce(list))
        return _deallocAndPop(list, index, NULL);
    if (list->_length - index - 1)
        memmove(list->_elems + index * list->_elemSize, list->_elems + (index + 1) * list->_elemSize,
                (list->_length - index - 1) * list->_elemSize); // 从index往前移动一位
    list->_length--;
    return 0;
}

int arrayList_locate(const ArrayList *list, ListElemComparer cmp, const void *elem, int *index) {
    for (int i = 0; i < list->_length; i++) {
        if (!cmp(list->_elems + (i * list->_elemSize), elem)) {
            *index = i;
            return 0;
        }
    }
    return -1;
}

int arrayList_travel(const ArrayList *list, ListElemVisitor visit) {
    for (int i = 0; i < list->_length; i++)
        visit(list->_elems + (i * list->_elemSize));

    return 0;
}

int arrayList_clear(ArrayList *list) {
    free(list->_elems);
    list->_elems = NULL;
    list->_length = list->_capacity = 0;
    return 0;
}

int arrayList_rpop(ArrayList *list, void *elem) {
    return arrayList_getDel(list, list->_length - 1, elem);
}

int arrayList_lpush(ArrayList *list, const void *elem) {
    return arrayList_insert(list, 0, elem);
}

int arrayList_rpush(ArrayList *list, const void *elem) {
    return arrayList_insert(list, list->_length, elem);
}

int arrayList_lpop(ArrayList *list, void *elem) {
    return arrayList_getDel(list, 0, elem);
}

int arrayList_set(const ArrayList *list, int index, const void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    memcpy(list->_elems + index * list->_elemSize, elem, list->_elemSize);
    return 0;
}

int arrayList_getDel(ArrayList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    if (_needReduce(list))
        return _deallocAndPop(list, index, elem);
    memcpy(elem, list->_elems + index * list->_elemSize, list->_elemSize);
    if (list->_length - 1 - index)
        memmove(list->_elems + index * list->_elemSize, list->_elems + (list->_length - 1) * list->_elemSize,
                list->_elemSize); // 从index往前移动一位
    list->_length--;
    return 0;
}

int arrayList_getSet(const ArrayList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    void *tmp = malloc(list->_elemSize);
    memcpy(tmp, list->_elems + index * list->_elemSize, list->_elemSize);  // 复制元素
    memcpy(list->_elems + index * list->_elemSize, elem, list->_elemSize); // 设置元素
    memcpy(elem, tmp, list->_elemSize);
    free(tmp);
    return 0;
}

int arrayList_fprint(const ArrayList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    for (int i = 0; i < list->_length - 1; i++) {
        size_t len = str(list->_elems + i * list->_elemSize, s);
        s[len] = '\000';
        fprintf(f, "%s, ", s);
    }
    if (list->_length > 0) {
        size_t len = str(list->_elems + (list->_length - 1) * list->_elemSize, s);
        s[len] = '\000';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
