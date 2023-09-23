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

#ifndef CLIB_STATIC_LINKED_LIST_H
#define CLIB_STATIC_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

// 线性表之静态链实现。
typedef struct {
    int _length, _capacity;
    size_t _elemSize;
    unsigned *_indexes;
    void *_elems;
} StaticLinkedList;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
StaticLinkedList *staticLinkedList_alloc(size_t elemSize);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int staticLinkedList_free(StaticLinkedList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t staticLinkedList_len(const StaticLinkedList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int staticLinkedList_get(const StaticLinkedList *list, int index, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 1: 越界。
int staticLinkedList_insert(StaticLinkedList *list, int index, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 1: 越界。
int staticLinkedList_del(StaticLinkedList *list, int index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// -1: 未找到。
int staticLinkedList_locate(const StaticLinkedList *list, ListElemComparer cmp, const void *elem, int *index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int staticLinkedList_travel(const StaticLinkedList *list, ListElemVisitor visit);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int staticLinkedList_clear(StaticLinkedList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 1: 越界。
int staticLinkedList_rpop(StaticLinkedList *list, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(n)
int staticLinkedList_lpush(StaticLinkedList *list, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(n)
int staticLinkedList_rpush(StaticLinkedList *list, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 1: 越界。
int staticLinkedList_lpop(StaticLinkedList *list, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int staticLinkedList_set(const StaticLinkedList *list, int index, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(n)
// 1: 越界。
int staticLinkedList_getDel(StaticLinkedList *list, int index, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int staticLinkedList_getSet(const StaticLinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(n)
int staticLinkedList_fprint(const StaticLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_STATIC_LINKED_LIST_H
