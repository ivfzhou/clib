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

#include<stdlib.h>
#include<string.h>

#include "linked_queue.h"

LinkedQueue *linkedQueue_alloc(size_t elemSize) {
    LinkedQueue *q = malloc(sizeof(LinkedQueue));
    q->_length = 0;
    q->_front = q->_rear = NULL;
    q->_elemSize = elemSize;
    return q;
}

void linkedQueue_free(LinkedQueue *q) {
    LinkQueueNode *node = q->_front;
    for (int i = 0; i < q->_length; i++) {
        free(node->_elem);
        node = node->_next;
    }
    q->_length = q->_elemSize = 0;
    q->_front = q->_rear = NULL;
    free(q);
}

int linkedQueue_into(LinkedQueue *q, const void *elem) {
    LinkQueueNode *node = malloc(sizeof(LinkQueueNode));
    node->_elem = malloc(q->_elemSize);
    node->_next = NULL;
    memcpy(node->_elem, elem, q->_elemSize);

    if (!q->_length) {
        q->_front = q->_rear = node;
    } else {
        q->_front->_next = node;
        q->_front = node;
    }

    q->_length++;
    return 0;
}

int linkedQueue_exit(LinkedQueue *q, void *elem) {
    if (!q->_length) return 1;
    memcpy(elem, q->_rear->_elem, q->_elemSize);

    if (q->_length == 1) {
        free(q->_front->_elem);
        free(q->_front);
        q->_front = q->_rear = NULL;
    } else {
        LinkQueueNode *node = q->_rear->_next;
        free(q->_rear->_elem);
        free(q->_rear);
        q->_rear = node;
    }

    q->_length--;
    return 0;
}

size_t linkedQueue_len(const LinkedQueue *q) {
    return q->_length;
}
