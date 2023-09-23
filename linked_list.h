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

#ifndef CLIB_LINKED_LIST_H
#define CLIB_LINKED_LIST_H

#include <stdlib.h>

#include "list.h"

typedef struct SingleLinkNode {
    void *_elem;
    struct SingleLinkNode *_next;
} SingleLinkNode;

// 线性表之链式实现。
typedef struct {
    int _length;
    size_t _elemSize;
    SingleLinkNode *_head;
} LinkedList;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
LinkedList *linkedList_alloc(size_t elemSize);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linkedList_free(LinkedList *list);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t linkedList_len(const LinkedList *list);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_get(const LinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_insert(LinkedList *list, int index, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_del(LinkedList *list, int index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// -1: 未找到。
int linkedList_locate(const LinkedList *list, ListElemComparer cmp, const void *elem, int *index);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linkedList_travel(const LinkedList *list, ListElemVisitor visit);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linkedList_clear(LinkedList *list);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_rpop(LinkedList *list, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linkedList_lpush(LinkedList *list, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linkedList_rpush(LinkedList *list, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_lpop(LinkedList *list, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_set(const LinkedList *list, int index, const void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_getDel(LinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
// 1: 越界。
int linkedList_getSet(const LinkedList *list, int index, void *elem);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int linkedList_fprint(const LinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem);

#endif // CLIB_LINKED_LIST_H
