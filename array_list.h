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

#ifndef CLIB_ARRAY_LIST_H
#define CLIB_ARRAY_LIST_H

#include <stdlib.h>

#include "list.h"

// 线性表之顺序实现。
typedef struct {
    int _length;
    int _capacity;
    size_t _elemSize;
    void *_elems;
} ArrayList;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
ArrayList *arrayList_alloc(size_t elemSize);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int arrayList_free(ArrayList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t arrayList_len(const ArrayList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_get(const ArrayList *list, int index, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_insert(ArrayList *list, int index, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_del(ArrayList *list, int index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// -1: 未找到。
int arrayList_locate(const ArrayList *list, ListElemComparer cmp, const void *elem, int *index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int arrayList_travel(const ArrayList *list, ListElemVisitor visit);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int arrayList_clear(ArrayList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_rpop(ArrayList *list, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int arrayList_lpush(ArrayList *list, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int arrayList_rpush(ArrayList *list, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_lpop(ArrayList *list, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_set(const ArrayList *list, int index, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_getDel(ArrayList *list, int index, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int arrayList_getSet(const ArrayList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int arrayList_fprint(const ArrayList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_ARRAY_LIST_H
