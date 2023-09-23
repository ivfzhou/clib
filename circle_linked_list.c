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

#include "circle_linked_list.h"

static CircleLinkNode *_newNode(size_t size, const void *elem) {
    CircleLinkNode *newNode = malloc(sizeof(CircleLinkNode));
    if (newNode == NULL)
        return NULL;
    newNode->_elem = malloc(size);
    if (newNode->_elem == NULL) {
        free(newNode);
        return NULL;
    }
    memcpy(newNode->_elem, elem, size);
    newNode->_next = newNode->_prev = NULL;
    return newNode;
}

static CircleLinkNode *_getNode(const CircleLinkedList *list, int index) {
    CircleLinkNode *node = list->_firstNode;
    if (index <= list->_length / 2)
        for (int i = 0; i < index; i++)
            node = node->_next;
    else
        for (int i = list->_length - 1; i >= index; i--)
            node = node->_prev;

    return node;
}

static CircleLinkNode *_popNode(CircleLinkedList *list, int index) {
    CircleLinkNode *node;
    if (!index) {
        node = list->_firstNode;
        list->_firstNode = node->_next;
        if (list->_firstNode)
            list->_firstNode->_prev = node->_prev;
        if (node->_prev)
            node->_prev->_next = list->_firstNode;
    } else {
        node = _getNode(list, index);
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
    }
    node->_prev = node->_next = NULL;
    list->_length--;
    return node;
}

CircleLinkedList *circleLinkedList_alloc(size_t elemSize) {
    CircleLinkedList *list = malloc(sizeof(CircleLinkedList));
    list->_elemSize = elemSize;
    list->_length = 0;
    list->_firstNode = NULL;
    return list;
}

int circleLinkedList_free(CircleLinkedList *list) {
    CircleLinkNode *node = list->_firstNode;
    for (int i = 0; i < list->_length; i++) {
        CircleLinkNode *next = node->_next;
        free(node->_elem);
        free(node);
        node = next;
    }
    list->_length = list->_elemSize = 0;
    list->_firstNode = NULL;
    free(list);
    return 0;
}

size_t circleLinkedList_len(const CircleLinkedList *list) {
    return list->_length;
}

int circleLinkedList_get(const CircleLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    CircleLinkNode *node = _getNode(list, index);
    memcpy(elem, node->_elem, list->_elemSize);
    return 0;
}

int circleLinkedList_insert(CircleLinkedList *list, int index, const void *elem) {
    if (index > list->_length || index < 0)
        return 1;
    CircleLinkNode *newNode = _newNode(list->_elemSize, elem);
    if (newNode == NULL)
        return 2;

    if (!index) {
        if (!list->_length) {
            list->_firstNode = newNode;
            list->_firstNode->_next = list->_firstNode->_prev = list->_firstNode;
        } else {
            CircleLinkNode *lastNode = _getNode(list, list->_length - 1);
            list->_firstNode->_prev = newNode;
            newNode->_next = list->_firstNode;
            newNode->_prev = lastNode;
            lastNode->_next = newNode;
            list->_firstNode = newNode;
        }
    } else {
        CircleLinkNode *node = _getNode(list, index);
        newNode->_next = node;
        newNode->_prev = node->_prev;
        if (node->_prev)
            node->_prev->_next = newNode;
        node->_prev = newNode;
    }

    list->_length++;
    return 0;
}

int circleLinkedList_del(CircleLinkedList *list, int index) {
    if (index >= list->_length || index < 0)
        return 1;
    CircleLinkNode *node = _popNode(list, index);
    free(node->_elem);
    free(node);
    return 0;
}

int circleLinkedList_locate(const CircleLinkedList *list, ListElemComparer cmp, const void *elem, int *index) {
    CircleLinkNode *node = list->_firstNode;
    for (int i = 0; i < list->_length; i++) {
        if (!cmp(node->_elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->_next;
    }
    return -1;
}

int circleLinkedList_travel(const CircleLinkedList *list, ListElemVisitor visit) {
    CircleLinkNode *node = list->_firstNode;
    for (int i = 0; i < list->_length; i++) {
        visit(node->_elem);
        node = node->_next;
    }
    return 0;
}

int circleLinkedList_clear(CircleLinkedList *list) {
    CircleLinkNode *node = list->_firstNode;
    for (int i = 0; i < list->_length; i++) {
        CircleLinkNode *next = node->_next;
        free(node->_elem);
        free(node);
        node = next;
    }
    list->_length = 0;
    list->_firstNode = NULL;
    return 0;
}

int circleLinkedList_rpop(CircleLinkedList *list, void *elem) {
    return circleLinkedList_getDel(list, list->_length - 1, elem);
}

int circleLinkedList_lpush(CircleLinkedList *list, const void *elem) {
    return circleLinkedList_insert(list, 0, elem);
}

int circleLinkedList_rpush(CircleLinkedList *list, const void *elem) {
    return circleLinkedList_insert(list, list->_length, elem);
}

int circleLinkedList_lpop(CircleLinkedList *list, void *elem) {
    return circleLinkedList_getDel(list, 0, elem);
}

int circleLinkedList_set(const CircleLinkedList *list, int index, const void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    CircleLinkNode *node = _getNode(list, index);
    memcpy(node->_elem, elem, list->_elemSize);
    return 0;
}

int circleLinkedList_getDel(CircleLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    CircleLinkNode *node = _popNode(list, index);
    memcpy(elem, node->_elem, list->_elemSize);
    free(node->_elem);
    free(node);
    return 0;
}

int circleLinkedList_getSet(const CircleLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    CircleLinkNode *node = _getNode(list, index);
    void *tmp = malloc(list->_elemSize);
    memcpy(tmp, node->_elem, list->_elemSize);
    memcpy(node->_elem, elem, list->_elemSize);
    memcpy(elem, tmp, list->_elemSize);
    free(tmp);
    return 0;
}

int circleLinkedList_fprint(const CircleLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    CircleLinkNode *node = list->_firstNode;
    for (int i = 0; i < list->_length - 1; i++) {
        size_t len = str(node->_elem, s);
        s[len] = '\000';
        fprintf(f, "%s, ", s);
        node = node->_next;
    }
    if (list->_length > 0) {
        size_t len = str(node->_elem, s);
        s[len] = '\000';
        fprintf(f, "%s", s);
    }
    fprintf(f, "]");
    fflush(f);
    return 0;
}
