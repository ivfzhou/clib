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

#include "array_list.c"

#define TEST_LENGTH 500000

static int _intCmp(const void *o1, const void *o2);

static void _intVisitor(void *p);

static size_t _intToString(void *elem, char *s);

int main(void) {
    printf("begin test array list\n");

    ArrayList *list = arrayList_alloc(sizeof(int));
    assert(list);

    int elem = 2;
    int index = 0;
    assert(!arrayList_insert(list, index, &elem));
    arrayList_fprint(list, stdout, _intToString, 1); // [2]
    puts("");

    elem = 1;
    assert(!arrayList_lpush(list, &elem));
    arrayList_fprint(list, stdout, _intToString, 1); // [1, 2]
    puts("");

    elem = 3;
    assert(!arrayList_rpush(list, &elem));
    arrayList_fprint(list, stdout, _intToString, 1); // [1, 2, 3]
    puts("");

    assert(!arrayList_travel(list, _intVisitor));

    size_t length = arrayList_len(list);
    assert(length == 3);

    elem = 4;
    assert(!arrayList_set(list, index, &elem));
    arrayList_fprint(list, stdout, _intToString, 1); // [4, 2, 3]
    puts("");

    assert(!arrayList_get(list, index, &elem));
    assert(elem == 4);

    elem = 3;
    assert(!arrayList_locate(list, _intCmp, &elem, &index));
    assert(index == 2);

    elem = 4;
    assert(!arrayList_getSet(list, index, &elem));
    assert(elem == 3);
    arrayList_fprint(list, stdout, _intToString, 1); // [4, 2, 4]
    puts("");

    assert(!arrayList_getDel(list, index, &elem));
    assert(elem == 4);
    arrayList_fprint(list, stdout, _intToString, 1); // [4, 2]
    puts("");

    assert(!arrayList_lpop(list, &elem));
    assert(elem == 4);
    arrayList_fprint(list, stdout, _intToString, 1); // [2]
    puts("");

    assert(!arrayList_rpop(list, &elem));
    assert(elem == 2);
    arrayList_fprint(list, stdout, _intToString, 1); // []
    puts("");

    srand(time(NULL) + 100);
    int res = 0;
    for (int i = 0; i < TEST_LENGTH; i++) {
        elem = i + 1;
        length = arrayList_len(list);
        index = rand() % (length + 1u);
        assert(!arrayList_insert(list, index, &elem));
        assert(!arrayList_get(list, index, &res));
        assert(res == elem);
    }
    for (int i = 0; i < TEST_LENGTH; i++) {
        length = arrayList_len(list);
        index = rand() % length;
        assert(!arrayList_del(list, index));
    }

    assert(!arrayList_clear(list));
    assert(!arrayList_free(list));

    printf("array list test passed\n");
}

static int _intCmp(const void *o1, const void *o2) {
    int *n1 = (int *) o1;
    int *n2 = (int *) o2;
    if (*n1 == *n2)
        return 0;
    return o1 > o2 ? 1 : -1;
}

static void _intVisitor(void *p) {
    static int prev = 1;
    int i = *(int *) p;
    assert(i == prev);
    prev = i + 1;
}

static size_t _intToString(void *elem, char *s) {
    int x = *(int *) elem;
    char buf[12];
    int len = snprintf(buf, 12, "%d", x);
    strncpy(s, buf, len);
    return len;
}