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

#ifndef CLIB_STRING_H
#define CLIB_STRING_H

#include <stdio.h>

typedef struct {
    char *_chars;
    unsigned long long _length;
} String;

// 时间复杂度：O(1)
// 空间复杂度：O(1)
String *string_alloc(const char *c);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
String *string_concat(const String *s1, const String *s2);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
size_t string_len(const String *s);

// 时间复杂度：O(n)
// 空间复杂度：O(n)
size_t string_index(const String *s, const String *sub);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
String *string_sub(const String *s, long long begin, long long end);

// 时间复杂度：O(1)
// 空间复杂度：O(1)
void string_free(String *s);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int string_compare(const String *s1, const String *s2);

// 时间复杂度：O(n)
// 空间复杂度：O(1)
int string_fprint(const String *s, FILE *f);

#endif //CLIB_STRING_H
