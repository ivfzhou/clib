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

#include "linked_list.h"

static SingleLinkNode *_getNode(const LinkedList *list, int index) {
    SingleLinkNode *node = list->_head;
    for (int i = 0; i < index; i++)
        node = node->_next;
    return node;
}

static SingleLinkNode *_newNode(size_t elemSize, const void *elem) {
    SingleLinkNode *newNode = malloc(sizeof(SingleLinkNode));
    if (newNode == NULL)
        return NULL;
    newNode->_elem = malloc(elemSize);
    memcpy(newNode->_elem, elem, elemSize);
    newNode->_next = NULL;
    return newNode;
}

static void _popNode(LinkedList *list, int index, void *elem) {
    SingleLinkNode *delNode;
    if (!index) { // 删除首元素
        delNode = list->_head;
        list->_head = delNode->_next;
    } else {
        SingleLinkNode *prevNode = _getNode(list, index - 1);
        delNode = prevNode->_next;
        prevNode->_next = delNode->_next;
    }

    if (elem != NULL)
        memcpy(elem, delNode->_elem, list->_elemSize);
    free(delNode->_elem);
    free(delNode);
    list->_length--;
}

LinkedList *linkedList_alloc(size_t elemSize) {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->_elemSize = elemSize;
    list->_length = 0;
    list->_head = NULL;
    return list;
}

int linkedList_free(LinkedList *list) {
    SingleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        SingleLinkNode *next = node->_next;
        free(node->_elem);
        free(node);
        node = next;
    }
    list->_head = NULL;
    list->_elemSize = list->_length = 0;
    free(list);
    return 0;
}

size_t linkedList_len(const LinkedList *list) {
    return list->_length;
}

int linkedList_get(const LinkedList *list, int index, void *elem) {
    if (index >= list->_length || index < 0)
        return 1;
    SingleLinkNode *node = _getNode(list, index);
    memcpy(elem, node->_elem, list->_elemSize);
    return 0;
}

int linkedList_insert(LinkedList *list, int index, const void *elem) {
    if (index > list->_length || index < 0)
        return 1;
    SingleLinkNode *newNode = _newNode(list->_elemSize, elem);

    if (!index) { // 首部追加元素
        newNode->_next = list->_head;
        list->_head = newNode;
    } else { // 找到插入位置的节点并插入
        SingleLinkNode *prevNode = _getNode(list, index - 1);
        newNode->_next = prevNode->_next;
        prevNode->_next = newNode;
    }

    list->_length++;
    return 0;
}

int linkedList_del(LinkedList *list, int index) {
    _popNode(list, index, NULL);
    return 0;
}

int linkedList_locate(const LinkedList *list, ListElemComparer cmp, const void *elem, int *index) {
    SingleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        if (!cmp(node->_elem, elem)) {
            *index = i;
            return 0;
        }
        node = node->_next;
    }
    return -1;
}

int linkedList_travel(const LinkedList *list, ListElemVisitor visit) {
    SingleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        visit(node->_elem);
        node = node->_next;
    }
    return 0;
}

int linkedList_clear(LinkedList *list) {
    SingleLinkNode *node = list->_head;
    for (int i = 0; i < list->_length; i++) {
        SingleLinkNode *next = node->_next;
        free(node->_elem);
        free(node);
        node = next;
    }
    list->_length = 0;
    list->_head = NULL;
    return 0;
}

int linkedList_rpop(LinkedList *list, void *elem) {
    return linkedList_getDel(list, list->_length - 1, elem);
}

int linkedList_lpush(LinkedList *list, const void *elem) {
    return linkedList_insert(list, 0, elem);
}

int linkedList_rpush(LinkedList *list, const void *elem) {
    return linkedList_insert(list, list->_length, elem);
}

int linkedList_lpop(LinkedList *list, void *elem) {
    return linkedList_getDel(list, 0, elem);
}

int linkedList_set(const LinkedList *list, int index, const void *elem) {
    SingleLinkNode *node = _getNode(list, index);
    memcpy(node->_elem, elem, list->_elemSize);
    return 0;
}

int linkedList_getDel(LinkedList *list, int index, void *elem) {
    _popNode(list, index, elem);
    return 0;
}

int linkedList_getSet(const LinkedList *list, int index, void *elem) {
    SingleLinkNode *node = _getNode(list, index);
    void *tmp = malloc(list->_elemSize);
    memcpy(tmp, node->_elem, list->_elemSize);
    memcpy(node->_elem, elem, list->_elemSize);
    memcpy(elem, tmp, list->_elemSize);
    free(tmp);
    return 0;
}

int linkedList_fprint(const LinkedList *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    fprintf(f, "[");
    char s[sizeOfElem + 1];
    SingleLinkNode *node = list->_head;
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
    return 0;
}
