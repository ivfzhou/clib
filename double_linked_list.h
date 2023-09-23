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

#ifndef CLIB_DOUBLE_LINKED_LIST_H
#define CLIB_DOUBLE_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

typedef struct DoubleLinkNode {
    void *_elem;
    struct DoubleLinkNode *_next;
    struct DoubleLinkNode *_prev;
} DoubleLinkNode;

// 线性表之双链式实现。
typedef struct {
    size_t _elemSize;
    int _length;
    DoubleLinkNode *_head;
    DoubleLinkNode *_tail;
} DoubleLinkedList;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
DoubleLinkedList *doubleLinkedList_alloc(size_t elemSize);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_free(DoubleLinkedList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t doubleLinkedList_len(const DoubleLinkedList *list);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_get(const DoubleLinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_insert(DoubleLinkedList *list, int index, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_del(DoubleLinkedList *list, int index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// -1: 未找到。
int doubleLinkedList_locate(const DoubleLinkedList *list, ListElemComparer cmp, const void *elem, int *index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_travel(const DoubleLinkedList *list, ListElemVisitor visit);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_clear(DoubleLinkedList *list);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_rpop(DoubleLinkedList *list, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_lpush(DoubleLinkedList *list, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_rpush(DoubleLinkedList *list, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_lpop(DoubleLinkedList *list, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_set(const DoubleLinkedList *list, int index, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_getDel(DoubleLinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int doubleLinkedList_getSet(const DoubleLinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int doubleLinkedList_fprint(const DoubleLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_DOUBLE_LINKED_LIST_H
