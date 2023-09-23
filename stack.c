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
#include <signal.h>

#include "stack.h"

void stack_push(Stack *s, const void *elem) {
    if (s->_top - s->_bottom + s->_sizeOfElem > STACK_SIZE) raise(SIGABRT);
    memcpy(s->_top, elem, s->_sizeOfElem);
    s->_top += s->_sizeOfElem;
}

void stack_pop(Stack *s, void *elem) {
    if (stack_isEmpty(s)) raise(SIGABRT);
    memcpy(elem, s->_top - s->_sizeOfElem, s->_sizeOfElem);
    s->_top -= s->_sizeOfElem;
}

_Bool stack_isEmpty(const Stack *s) {
    return s->_bottom == s->_top;
}

Stack *stack_alloc(size_t sizeOfElem) {
    Stack *s = malloc(sizeof(Stack));
    s->_sizeOfElem = sizeOfElem;
    s->_bottom = s->_top = malloc(STACK_SIZE);
    return s;
}

void stack_free(Stack *s) {
    free(s->_bottom);
    free(s);
}

int stack_peekTop(const Stack *s, void *elem) {
    if (stack_isEmpty(s)) return 1;
    memcpy(elem, s->_top - s->_sizeOfElem, s->_sizeOfElem);
    return 0;
}
