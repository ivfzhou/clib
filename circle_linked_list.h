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

#ifndef CLIB_CIRCLE_LINKED_LIST_H
#define CLIB_CIRCLE_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

typedef struct CircleLinkNode {
    void *_elem;
    struct CircleLinkNode *_next;
    struct CircleLinkNode *_prev;
} CircleLinkNode;

typedef struct {
    int _length;
    size_t _elemSize;
    CircleLinkNode *_firstNode;
} CircleLinkedList;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
CircleLinkedList *circleLinkedList_alloc(size_t elemSize);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circleLinkedList_free(CircleLinkedList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t circleLinkedList_len(const CircleLinkedList *list);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int circleLinkedList_get(const CircleLinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int circleLinkedList_insert(CircleLinkedList *list, int index, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int circleLinkedList_del(CircleLinkedList *list, int index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// -1: 未找到
int circleLinkedList_locate(const CircleLinkedList *list, ListElemComparer cmp, const void *elem, int *index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circleLinkedList_travel(const CircleLinkedList *list, ListElemVisitor visit);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circleLinkedList_clear(CircleLinkedList *list);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int circleLinkedList_rpop(CircleLinkedList *list, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circleLinkedList_lpush(CircleLinkedList *list, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circleLinkedList_rpush(CircleLinkedList *list, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int circleLinkedList_lpop(CircleLinkedList *list, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circleLinkedList_set(const CircleLinkedList *list, int index, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int circleLinkedList_getDel(CircleLinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int circleLinkedList_getSet(const CircleLinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int circleLinkedList_fprint(const CircleLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_CIRCLE_LINKED_LIST_H
