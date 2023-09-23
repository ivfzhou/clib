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

#include "list.h"
#include "array_list.h"
#include "circle_linked_list.h"
#include "double_linked_list.h"
#include "linked_list.h"
#include "static_linked_list.h"

List *list_alloc(size_t elemSize, ListImplType type) {
    List *list = malloc(sizeof(List));
    switch (type) {
        case ListImplType_Array:
            list->_impl = arrayList_alloc(elemSize);
            break;
        case ListImplType_Linked:
            list->_impl = linkedList_alloc(elemSize);
            break;
        case ListImplType_DoubleLinked:
            list->_impl = doubleLinkedList_alloc(elemSize);
            break;
        case ListImplType_StaticLinked:
            list->_impl = staticLinkedList_alloc(elemSize);
            break;
        case ListImplType_CircleLinked:
            list->_impl = circleLinkedList_alloc(elemSize);
            break;
        default:
            return NULL;
    }
    list->_type = type;
    if (!list->_impl) {
        free(list);
        return NULL;
    }
    return list;
}

int list_free(List *list) {
    int st;
    switch (list->_type) {
        case ListImplType_Array:
            st = arrayList_free(list->_impl);
            break;
        case ListImplType_Linked:
            st = linkedList_free(list->_impl);
            break;
        case ListImplType_DoubleLinked:
            st = doubleLinkedList_free(list->_impl);
            break;
        case ListImplType_StaticLinked:
            st = staticLinkedList_free(list->_impl);
            break;
        case ListImplType_CircleLinked:
            st = circleLinkedList_free(list->_impl);
            break;
        default:
            return 1;
    }
    if (!st) free(list);

    return st;
}

size_t list_len(const List *list) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_len(list->_impl);
        case ListImplType_Linked:
            return linkedList_len(list->_impl);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_len(list->_impl);
        case ListImplType_StaticLinked:
            return staticLinkedList_len(list->_impl);
        case ListImplType_CircleLinked:
            return circleLinkedList_len(list->_impl);
        default:
            return 0;
    }
}

int list_get(const List *list, int index, void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_get(list->_impl, index, elem);
        case ListImplType_Linked:
            return linkedList_get(list->_impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_get(list->_impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_get(list->_impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_get(list->_impl, index, elem);
        default:
            return 1;
    }
}

int list_insert(List *list, int index, const void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_insert(list->_impl, index, elem);
        case ListImplType_Linked:
            return linkedList_insert(list->_impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_insert(list->_impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_insert(list->_impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_insert(list->_impl, index, elem);
        default:
            return 1;
    }
}

int list_del(List *list, int index) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_del(list->_impl, index);
        case ListImplType_Linked:
            return linkedList_del(list->_impl, index);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_del(list->_impl, index);
        case ListImplType_StaticLinked:
            return staticLinkedList_del(list->_impl, index);
        case ListImplType_CircleLinked:
            return circleLinkedList_del(list->_impl, index);
        default:
            return 1;
    }
}

int list_locate(const List *list, ListElemComparer cmp, const void *elem, int *index) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_locate(list->_impl, cmp, elem, index);
        case ListImplType_Linked:
            return linkedList_locate(list->_impl, cmp, elem, index);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_locate(list->_impl, cmp, elem, index);
        case ListImplType_StaticLinked:
            return staticLinkedList_locate(list->_impl, cmp, elem, index);
        case ListImplType_CircleLinked:
            return circleLinkedList_locate(list->_impl, cmp, elem, index);
        default:
            return 1;
    }
}

int list_travel(const List *list, ListElemVisitor visit) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_travel(list->_impl, visit);
        case ListImplType_Linked:
            return linkedList_travel(list->_impl, visit);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_travel(list->_impl, visit);
        case ListImplType_StaticLinked:
            return staticLinkedList_travel(list->_impl, visit);
        case ListImplType_CircleLinked:
            return circleLinkedList_travel(list->_impl, visit);
        default:
            return 1;
    }
}

int list_clear(List *list) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_clear(list->_impl);
        case ListImplType_Linked:
            return linkedList_clear(list->_impl);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_clear(list->_impl);
        case ListImplType_StaticLinked:
            return staticLinkedList_clear(list->_impl);
        case ListImplType_CircleLinked:
            return circleLinkedList_clear(list->_impl);
        default:
            return 1;
    }
}

int list_rpop(List *list, void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_rpop(list->_impl, elem);
        case ListImplType_Linked:
            return linkedList_rpop(list->_impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_rpop(list->_impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_rpop(list->_impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_rpop(list->_impl, elem);
        default:
            return 1;
    }
}

int list_lpush(List *list, const void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_lpush(list->_impl, elem);
        case ListImplType_Linked:
            return linkedList_lpush(list->_impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_lpush(list->_impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_lpush(list->_impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_lpush(list->_impl, elem);
        default:
            return 1;
    }
}

int list_rpush(List *list, const void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_rpush(list->_impl, elem);
        case ListImplType_Linked:
            return linkedList_rpush(list->_impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_rpush(list->_impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_rpush(list->_impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_rpush(list->_impl, elem);
        default:
            return 1;
    }
}

int list_lpop(List *list, void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_lpop(list->_impl, elem);
        case ListImplType_Linked:
            return linkedList_lpop(list->_impl, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_lpop(list->_impl, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_lpop(list->_impl, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_lpop(list->_impl, elem);
        default:
            return 1;
    }
}

int list_set(const List *list, int index, const void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_set(list->_impl, index, elem);
        case ListImplType_Linked:
            return linkedList_set(list->_impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_set(list->_impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_set(list->_impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_set(list->_impl, index, elem);
        default:
            return 1;
    }
}

int list_getDel(List *list, int index, void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_getDel(list->_impl, index, elem);
        case ListImplType_Linked:
            return linkedList_getDel(list->_impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_getDel(list->_impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_getDel(list->_impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_getDel(list->_impl, index, elem);
        default:
            return 1;
    }
}

int list_getSet(const List *list, int index, void *elem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_getSet(list->_impl, index, elem);
        case ListImplType_Linked:
            return linkedList_getSet(list->_impl, index, elem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_getSet(list->_impl, index, elem);
        case ListImplType_StaticLinked:
            return staticLinkedList_getSet(list->_impl, index, elem);
        case ListImplType_CircleLinked:
            return circleLinkedList_getSet(list->_impl, index, elem);
        default:
            return 1;
    }
}

int list_fprint(const List *list, FILE *f, ListElemToString str, size_t sizeOfElem) {
    switch (list->_type) {
        case ListImplType_Array:
            return arrayList_fprint(list->_impl, f, str, sizeOfElem);
        case ListImplType_Linked:
            return linkedList_fprint(list->_impl, f, str, sizeOfElem);
        case ListImplType_DoubleLinked:
            return doubleLinkedList_fprint(list->_impl, f, str, sizeOfElem);
        case ListImplType_StaticLinked:
            return staticLinkedList_fprint(list->_impl, f, str, sizeOfElem);
        case ListImplType_CircleLinked:
            return circleLinkedList_fprint(list->_impl, f, str, sizeOfElem);
        default:
            return 1;
    }
}
