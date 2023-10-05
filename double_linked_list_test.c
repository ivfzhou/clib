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

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "double_linked_list.c"

#define TEST_LENGTH 50000

static int intCmp(const void *o1, const void *o2);

static void intVisitor(void *p);

static size_t intToString(void *elem, char *s);

int main(void) {
    printf("begin test double linked list\n");

    DoubleLinkedList *list = doubleLinkedList_alloc(sizeof(int));
    assert(list);

    int elem = 2;
    size_t index = 0;
    assert(!doubleLinkedList_insert(list, index, &elem));
    doubleLinkedList_fprint(list, stdout, intToString, 1); // [2]
    puts("");

    elem = 1;
    assert(!doubleLinkedList_lpush(list, &elem));
    doubleLinkedList_fprint(list, stdout, intToString, 1); // [1, 2]
    puts("");

    elem = 3;
    assert(!doubleLinkedList_rpush(list, &elem));
    doubleLinkedList_fprint(list, stdout, intToString, 1); // [1, 2, 3]
    puts("");

    assert(!doubleLinkedList_travel(list, intVisitor));

    size_t length = doubleLinkedList_len(list);
    assert(length == 3);

    elem = 4;
    assert(!doubleLinkedList_set(list, index, &elem));
    doubleLinkedList_fprint(list, stdout, intToString, 1); // [4, 2, 3]
    puts("");

    assert(!doubleLinkedList_get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!doubleLinkedList_locate(list, intCmp, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!doubleLinkedList_getSet(list, index, &elem));
    assert(elem == 3);
    doubleLinkedList_fprint(list, stdout, intToString, 1); // [4, 2, 4]
    puts("");

    assert(!doubleLinkedList_getDel(list, index, &elem));
    assert(elem == 4);
    doubleLinkedList_fprint(list, stdout, intToString, 1); // [4, 2]
    puts("");

    assert(!doubleLinkedList_lpop(list, &elem));
    assert(elem == 4);
    doubleLinkedList_fprint(list, stdout, intToString, 1); // [2]
    puts("");

    assert(!doubleLinkedList_rpop(list, &elem));
    assert(elem == 2);
    doubleLinkedList_fprint(list, stdout, intToString, 1); // []
    puts("");

    srand(time(NULL) + 100);
    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = doubleLinkedList_len(list);
        index = rand() % (length + 1u);
        assert(!doubleLinkedList_insert(list, index, &elem));
        assert(!doubleLinkedList_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = doubleLinkedList_len(list);
        index = rand() % length;
        assert(!doubleLinkedList_del(list, index));
    }

    assert(!doubleLinkedList_clear(list));

    doubleLinkedList_free(list);
    printf("double linked list test passed\n");
}

static int intCmp(const void *o1, const void *o2) {
    int *n1 = (int *) o1;
    int *n2 = (int *) o2;
    if (*n1 == *n2)
        return 0;
    return o1 > o2 ? 1 : -1;
}

static void intVisitor(void *p) {
    static int prev = 1;
    int i = *(int *) p;
    assert(i == prev);
    prev = i + 1;
}

static size_t intToString(void *elem, char *s) {
    int x = *(int *) elem;
    char buf[12];
    int len = snprintf(buf, 12, "%d", x);
    strncpy(s, buf, len);
    return len;
}
