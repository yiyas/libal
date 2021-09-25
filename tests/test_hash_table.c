/**
 * Copyright (c) 2015 - 2021 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#include <libal/hash_table.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "unity/unity.h"

static const char *STRS[] = { "aa", "bb", "cc", "c1234", "y12", "x1", "112233" };
static const size_t INTS[] = { 1, 2, 3, 4, 5, 6, 7 };

static struct al_hash_table *ht = NULL;

void setUp(void) {
    ht = al_ht_str_new((uint32_t) sizeof(INTS[0]), 0, 0);
}

void tearDown(void) {
    al_ht_destroy(ht);
}

void test_ht_put_get_remove() {
    TEST_ASSERT_EQUAL_UINT32(0, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], &INTS[0], NULL));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[1], &INTS[1], NULL));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[2], &INTS[2], NULL));
    TEST_ASSERT_EQUAL_UINT32(3, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[3], &INTS[3], NULL));
    TEST_ASSERT_EQUAL_UINT32(4, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[4], &INTS[4], NULL));
    TEST_ASSERT_EQUAL_UINT32(5, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[5], &INTS[5], NULL));
    TEST_ASSERT_EQUAL_UINT32(6, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[6], &INTS[6], NULL));
    TEST_ASSERT_EQUAL_UINT32(7, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(1, *(int* )al_ht_getval(ht, &STRS[0]));
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_ht_getval(ht, &STRS[1]));
    TEST_ASSERT_EQUAL_INT(3, *(int* )al_ht_getval(ht, &STRS[2]));
    TEST_ASSERT_EQUAL_INT(4, *(int* )al_ht_getval(ht, &STRS[3]));
    TEST_ASSERT_EQUAL_INT(5, *(int* )al_ht_getval(ht, &STRS[4]));
    TEST_ASSERT_EQUAL_INT(6, *(int* )al_ht_getval(ht, &STRS[5]));
    TEST_ASSERT_EQUAL_INT(7, *(int* )al_ht_getval(ht, &STRS[6]));

    TEST_ASSERT_EQUAL_STRING(STRS[0], *(char** )al_ht_getkey(ht, &STRS[0]));
    TEST_ASSERT_EQUAL_STRING(STRS[1], *(char** )al_ht_getkey(ht, &STRS[1]));
    TEST_ASSERT_EQUAL_STRING(STRS[2], *(char** )al_ht_getkey(ht, &STRS[2]));
    TEST_ASSERT_EQUAL_STRING(STRS[3], *(char** )al_ht_getkey(ht, &STRS[3]));
    TEST_ASSERT_EQUAL_STRING(STRS[4], *(char** )al_ht_getkey(ht, &STRS[4]));
    TEST_ASSERT_EQUAL_STRING(STRS[5], *(char** )al_ht_getkey(ht, &STRS[5]));
    TEST_ASSERT_EQUAL_STRING(STRS[6], *(char** )al_ht_getkey(ht, &STRS[6]));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[0]));
    TEST_ASSERT_EQUAL_UINT32(6, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[1]));
    TEST_ASSERT_EQUAL_UINT32(5, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[2]));
    TEST_ASSERT_EQUAL_UINT32(4, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[3]));
    TEST_ASSERT_EQUAL_UINT32(3, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[6]));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[5]));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[4]));
    TEST_ASSERT_EQUAL_UINT32(0, al_ht_size(ht));
}

void test_ht_clear() {
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], &INTS[0], NULL));
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[1], &INTS[1], NULL));
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[2], &INTS[2], NULL));
    TEST_ASSERT_EQUAL_UINT32(3, al_ht_size(ht));

    al_ht_clear(ht);

    TEST_ASSERT_NULL(al_ht_getval(ht, &STRS[0]));
    TEST_ASSERT_NULL(al_ht_getval(ht, &STRS[1]));
    TEST_ASSERT_NULL(al_ht_getval(ht, &STRS[2]));

    TEST_ASSERT_EQUAL_UINT32(0, al_ht_size(ht));
}

void test_ht_put_same_key() {
    al_hash_iter iter1, iter2;

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], &INTS[0], &iter1));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));
    TEST_ASSERT_NOT_EQUAL(AL_HT_ITER_INVALID, iter1);
    TEST_ASSERT_EQUAL_INT(1, *(int* )al_ht_getval(ht, &STRS[0]));

    TEST_ASSERT_EQUAL_INT(1, al_ht_put(ht, &STRS[0], &INTS[1], &iter2));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));
    TEST_ASSERT_EQUAL(iter1, iter2);
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_ht_getval(ht, &STRS[0]));
}

void test_ht_put_null_key() {
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], NULL, NULL));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));
    TEST_ASSERT_EQUAL_INT(0, *(int* )al_ht_getval(ht, &STRS[0]));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[1], &INTS[1], NULL));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_ht_getval(ht, &STRS[1]));

    TEST_ASSERT_EQUAL_INT(1, al_ht_put(ht, &STRS[1], NULL, NULL));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));
    TEST_ASSERT_EQUAL_INT(0, *(int* )al_ht_getval(ht, &STRS[1]));
}

void test_ht_iter_remove() {
    al_hash_iter iter1, iter2;

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], &INTS[0], &iter1));
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[1], &INTS[1], &iter2));

    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_iterremove(ht, iter2));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_iterremove(ht, iter1));
    TEST_ASSERT_EQUAL_UINT32(0, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(1, al_ht_iterremove(ht, iter1));

    TEST_ASSERT_EQUAL_INT(1, al_ht_iterremove(ht, AL_HT_ITER_INVALID));
}

void test_ht_with_dynamic_str_key() {
    char *k1, *k2, *v1, *v2;
    struct al_hash_table *ht;

    k1 = strdup("key1");
    k2 = strdup("key2");
    v1 = "value1";
    v2 = "value2";

    ht = al_ht_str_new(sizeof(const char*), 0, 1);

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &k1, &v1, NULL));
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &k2, &v2, NULL));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &k1));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    al_ht_destroy(ht);
}

void test_ht_with_const_ptr_key() {
    char *k1, *k2, *v1, *v2;
    struct al_hash_table *ht;

    k1 = "key1";
    k2 = "key2";
    v1 = "value1";
    v2 = "value2";

    ht = al_ht_ptr_new(sizeof(const char*), 0);

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &k1, &v1, NULL));
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &k2, &v2, NULL));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &k1));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    al_ht_destroy(ht);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_ht_put_get_remove);
    RUN_TEST(test_ht_clear);
    RUN_TEST(test_ht_put_same_key);
    RUN_TEST(test_ht_put_null_key);
    RUN_TEST(test_ht_iter_remove);
    RUN_TEST(test_ht_with_dynamic_str_key);
    RUN_TEST(test_ht_with_const_ptr_key);
    return UNITY_END();
}
