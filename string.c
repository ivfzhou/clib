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
#include <stdlib.h>
#include <stdio.h>

#include "string.h"

static void _generate_kmp_next(const char *p, int next[], size_t len) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < len - 1) {
        if (j == -1 || p[i] == p[j]) {
            ++i, ++j;
            //next[i] = j;
            if (p[i] != p[j]) next[i] = j;
            else next[i] = next[j];
        } else j = next[j];
    }
}

String *string_alloc(const char *c) {
    String *s = malloc(sizeof(String));
    s->_length = strlen(c);
    if (s->_length) s->_chars = malloc(sizeof(char) * s->_length);
    else s->_chars = NULL;
    // for (int i = 0; i < s->_length; i++) s->_chars[i] = c[i];
    if (s->_chars != NULL)
        memcpy(s->_chars, c, sizeof(char) * s->_length);
    return s;
}

String *string_concat(const String *s1, const String *s2) {
    String *s = malloc(sizeof(String));
    s->_length = s1->_length + s2->_length;
    if (s->_length) {
        s->_chars = malloc(sizeof(char) * s->_length);
    } else {
        s->_chars = NULL;
    }
    if (s1->_length)
        memcpy(s->_chars, s1->_chars, s1->_length * sizeof(char));
    if (s2->_length)
        memcpy(s->_chars + s1->_length, s2->_chars, s2->_length * sizeof(char));
    return s;
}

size_t string_len(const String *s) {
    return s->_length;
}

size_t string_index(const String *s, const String *sub) {
    int next[sub->_length];
    _generate_kmp_next(sub->_chars, next, sub->_length);
    long long i = 0, j = 0;
    while (i < s->_length && j < (long long) sub->_length) {
        if (j < 0 || s->_chars[i] == sub->_chars[j]) {
            i++, j++;
        } else j = next[j];
    }
    if (j >= sub->_length) return i - sub->_length;
    return -1;
}

String *string_sub(const String *s, long long begin, long long end) {
    if (begin > (long long) s->_length - 1 || end > (long long) s->_length)
        return NULL;
    if (begin < -(long long) s->_length)
        return NULL;
    if (end < -(long long) s->_length)
        return NULL;
    if (begin < 0) {
        begin += s->_length + 1;
    }
    if (end < 0) {
        end += s->_length + 1;
    }

    if (end < begin) return NULL;

    String *sub = malloc(sizeof(String));
    sub->_length = end - begin ? end - begin : 1;
    if (sub->_length > 0) {
        sub->_chars = malloc(sizeof(char) * sub->_length);
        memcpy(sub->_chars, s->_chars + begin, sub->_length * sizeof(char));
    } else sub->_chars = NULL;
    return sub;
}

void string_free(String *s) {
    free(s->_chars);
    free(s);
}

int string_compare(const String *s1, const String *s2) {
    for (int i = 0; i < s1->_length && i < s2->_length; i++) {
        if (s1->_chars[i] != s2->_chars[i]) return s1->_chars[i] - s2->_chars[i];
    }
    return s1->_length > s2->_length ? 1 : s1->_length == s2->_length ? 0 : -1;
}

int string_fprint(const String *s, FILE *f) {
    for (int i = 0; i < s->_length; i++) fputc(s->_chars[i], f);
    return 0;
}
