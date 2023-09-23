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

#ifndef CLIB_STACK_H
#define CLIB_STACK_H

#include <stdlib.h>

#define STACK_SIZE (2*1024*1024)

typedef struct {
    void *_bottom;
    void *_top;
    size_t _sizeOfElem;
} Stack;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_push(Stack *s, const void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_pop(Stack *s, void *elem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
_Bool stack_isEmpty(const Stack *s);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
Stack *stack_alloc(size_t sizeOfElem);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
void stack_free(Stack *s);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
int stack_peekTop(const Stack *s, void *elem);

#endif //CLIB_STACK_H
