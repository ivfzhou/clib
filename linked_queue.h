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

#ifndef CLIB_LINKED_QUEUE_H
#define CLIB_LINKED_QUEUE_H

#include <stdlib.h>

typedef struct LinkQueueNode {
    void *_elem;
    struct LinkQueueNode *_next;
} LinkQueueNode;

typedef struct {
    LinkQueueNode *_front;
    LinkQueueNode *_rear;
    size_t _elemSize;
    size_t _length;
} LinkedQueue;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
LinkedQueue *linkedQueue_alloc(size_t elemSize);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
void linkedQueue_free(LinkedQueue *);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int linkedQueue_into(LinkedQueue *, const void *);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
// 1: 队列为空
int linkedQueue_exit(LinkedQueue *, void *);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t linkedQueue_len(const LinkedQueue *);

#endif //CLIB_LINKED_QUEUE_H
