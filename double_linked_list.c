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

#include "double_linked_list.h"

static DoubleLinkNode *_newNode(size_t size, const void *elem) {
    DoubleLinkNode *newNode = malloc(sizeof(DoubleLinkNode));
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

static DoubleLinkNode *_getNode(const DoubleLinkedList *list, int index) {
    DoubleLinkNode *node;
    if (index <= (list->_length - 1) / 2) {
        node = list->_head;
        for (int i = 0; i < index; i++)
            node = node->_next;
    } else {
        node = list->_tail;
        for (int i = list->_length - 1; i > index; i--)
            node = node->_prev;
    }
    return node;
}

static DoubleLinkNode *_popNode(DoubleLinkedList *list, int index) {
    DoubleLinkNode *node;
    if (!index) {
        node = list->_head;
        list->_head = list->_head->_next;
        if (list->_length == 2)
            list->_tail = list->_head->_next = NULL;
    } else if (index == (list->_length - 1)) {
        node = list->_tail;
        list->_tail = list->_tail->_prev;
        list->_tail->_next = NULL;
        if (list->_length == 2)
            list->_tail = NULL;
    } else {
        node = _getNode(list, index);
        node->_prev->_next = node->_next;
        node->_next->_prev = node->_prev;
    }
    node->_prev = node->_next = NULL;
    list->_length--;
    return node;
}

DoubleLinkedList *doubleLinkedList_alloc(size_t elemSize) {
    DoubleLinkedList *list = malloc(sizeof(DoubleLinkedList));
    list->_elemSize = elemSize;
    list->_length = 0;
    list->_head = list->_tail = NULL;
    return list;
}

int doubleLinkedList_free(DoubleLinkedList *list) {
    DoubleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        DoubleLinkNode *tmp = node->_next;
        free(node->_elem);
        free(node);
        node = tmp;
    }
    list->_length = 0;
    list->_elemSize = 0;
    list->_head = list->_tail = NULL;
    free(list);
    return 0;
}

size_t doubleLinkedList_len(const DoubleLinkedList *list) {
    return list->_length;
}

int doubleLinkedList_get(const DoubleLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    DoubleLinkNode *node = _getNode(list, index);
    memcpy(elem, node->_elem, list->_elemSize);
    return 0;
}

int doubleLinkedList_insert(DoubleLinkedList *list, int index, const void *elem) {
    if (index > list->_length || index < 0)
        return 1;
    DoubleLinkNode *newNode = _newNode(list->_elemSize, elem);
    if (newNode == NULL)
        return 2;

    if (!list->_length) { // 第一次插入
        list->_head = newNode;
    } else if (list->_length == 1) { // 第二次插入
        if (index) {
            newNode->_prev = list->_head;
            list->_head->_next = newNode;
            list->_tail = newNode;
        } else {
            newNode->_next = list->_head;
            list->_head->_prev = newNode;
            list->_tail = list->_head;
            list->_head = newNode;
        }
    } else if (index == list->_length) { // 尾部追加
        newNode->_prev = list->_tail;
        list->_tail->_next = newNode;
        list->_tail = newNode;
    } else if (!index) { // 头部追加
        newNode->_next = list->_head;
        list->_head->_prev = newNode;
        list->_head = newNode;
    } else {
        DoubleLinkNode *node = _getNode(list, index);
        newNode->_next = node;
        newNode->_prev = node->_prev;
        node->_prev->_next = newNode;
        node->_prev = newNode;
    }

    list->_length++;
    return 0;
}

int doubleLinkedList_del(DoubleLinkedList *list, int index) {
    if (index > list->_length || index < 0)
        return 1;
    DoubleLinkNode *node = _popNode(list, index);
    free(node->_elem);
    free(node);
    return 0;
}

int
doubleLinkedList_locate(const DoubleLinkedList *list, ListElemComparer cmp, const void *elem, int *index) {
    DoubleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        if (!cmp(node->_elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->_next;
    }
    return -1;
}

int doubleLinkedList_travel(const DoubleLinkedList *list, ListElemVisitor visit) {
    DoubleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        visit(node->_elem);
        node = node->_next;
    }
    return 0;
}

int doubleLinkedList_clear(DoubleLinkedList *list) {
    DoubleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        DoubleLinkNode *tmp = node->_next;
        free(node->_elem);
        free(node);
        node = tmp;
    }
    list->_length = 0;
    list->_head = list->_tail = NULL;
    return 0;
}

int doubleLinkedList_rpop(DoubleLinkedList *list, void *elem) {
    return doubleLinkedList_getDel(list, list->_length - 1, elem);
}

int doubleLinkedList_lpush(DoubleLinkedList *list, const void *elem) {
    return doubleLinkedList_insert(list, 0, elem);
}

int doubleLinkedList_rpush(DoubleLinkedList *list, const void *elem) {
    return doubleLinkedList_insert(list, list->_length, elem);
}

int doubleLinkedList_lpop(DoubleLinkedList *list, void *elem) {
    return doubleLinkedList_getDel(list, 0, elem);
}

int doubleLinkedList_set(const DoubleLinkedList *list, int index, const void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    DoubleLinkNode *node = _getNode(list, index);
    memcpy(node->_elem, elem, list->_elemSize);
    return 0;
}

int doubleLinkedList_getDel(DoubleLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    DoubleLinkNode *node = _popNode(list, index);
    memcpy(elem, node->_elem, list->_elemSize);
    free(node->_elem);
    free(node);
    return 0;
}

int doubleLinkedList_getSet(const DoubleLinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    DoubleLinkNode *node = _getNode(list, index);
    void *tmp = malloc(list->_elemSize);
    if (tmp == NULL)
        return 2;
    memcpy(tmp, node->_elem, list->_elemSize);
    memcpy(node->_elem, elem, list->_elemSize);
    memcpy(elem, tmp, list->_elemSize);
    free(tmp);
    return 0;
}

int doubleLinkedList_fprint(const DoubleLinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    DoubleLinkNode *node = list->_head;
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
