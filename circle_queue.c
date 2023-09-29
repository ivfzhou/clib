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

#include <stdlib.h>
#include <string.h>

#include "circle_queue.h"

CircleQueue *circleQueue_alloc(size_t elemSize, size_t queueLength) {
    CircleQueue *queue = malloc(sizeof(CircleQueue));
    queue->_elemSize = elemSize;
    queue->_length = queueLength;
    queue->_array = malloc(elemSize * queueLength);
    queue->_head = queue->_tail = 0;
    return queue;
}

int circleQueue_into(CircleQueue *queue, const void *elem) {
    if (queue == NULL) return 2;
    if ((queue->_head - queue->_tail) >= queue->_length) return 1;
    memcpy(queue->_array + (queue->_head % queue->_length) * queue->_elemSize, elem, queue->_elemSize);
    queue->_head++;
    return 0;
}

int circleQueue_exit(CircleQueue *queue, void *elem) {
    if (queue == NULL) return 2;
    if (queue->_tail == queue->_head) return 1;
    memcpy(elem, queue->_array + (queue->_tail % queue->_length) * queue->_elemSize, queue->_elemSize);
    queue->_tail++;
    return 0;
}

void circleQueue_free(CircleQueue *queue) {
    free(queue->_array);
    free(queue);
}

size_t circleQueue_len(const CircleQueue *queue) {
    if (queue == NULL) return 0;
    return queue->_head - queue->_tail;
}
