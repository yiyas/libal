/**
 * Copyright (c) 2015 - 2017 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#include <libal/flexible_array.h>
#include <stddef.h>

#include "unity/unity.h"

static const int ARR[] = { 1, 2, 3, 4, 5, 6 };

static int ARR_SIZE = (int) (sizeof(ARR) / sizeof(ARR[0]));

static struct al_flexible_array *array = NULL;

void setUp(void) {
    array = al_fa_new(sizeof(ARR[0]), 3, 2);
}

void tearDown(void) {
    al_fa_destroy(array);
}

void test_add_as_last_then_remove_from_last() {
    int i, rc;

    for (i = 0; i < ARR_SIZE; i++) {
        rc = al_fa_add(array, AL_FA_INVALID_INDEX, &ARR[i]);
        TEST_ASSERT_EQUAL_INT(0, rc);
    }
    TEST_ASSERT_EQUAL_UINT32(6, al_fa_get_count(array));

    TEST_ASSERT_EQUAL_INT(1, *(int* )al_fa_get_data(array, 0));
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_fa_get_data(array, 1));
    TEST_ASSERT_EQUAL_INT(3, *(int* )al_fa_get_data(array, 2));
    TEST_ASSERT_EQUAL_INT(4, *(int* )al_fa_get_data(array, 3));
    TEST_ASSERT_EQUAL_INT(5, *(int* )al_fa_get_data(array, 4));
    TEST_ASSERT_EQUAL_INT(6, *(int* )al_fa_get_data(array, 5));

    for (i = 0; i < ARR_SIZE; i++) {
        rc = al_fa_remove(array, AL_FA_INVALID_INDEX);
        TEST_ASSERT_EQUAL_INT(0, rc);
    }
    TEST_ASSERT_EQUAL_UINT32(0, al_fa_get_count(array));
}

void test_add_as_first_then_remove_from_first() {
    int i, rc;

    for (i = 0; i < ARR_SIZE; i++) {
        rc = al_fa_add(array, 0, &ARR[i]);
        TEST_ASSERT_EQUAL_INT(0, rc);
    }
    TEST_ASSERT_EQUAL_UINT32(6, al_fa_get_count(array));

    TEST_ASSERT_EQUAL_INT(6, *(int* )al_fa_get_data(array, 0));
    TEST_ASSERT_EQUAL_INT(5, *(int* )al_fa_get_data(array, 1));
    TEST_ASSERT_EQUAL_INT(4, *(int* )al_fa_get_data(array, 2));
    TEST_ASSERT_EQUAL_INT(3, *(int* )al_fa_get_data(array, 3));
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_fa_get_data(array, 4));
    TEST_ASSERT_EQUAL_INT(1, *(int* )al_fa_get_data(array, 5));

    for (i = 0; i < ARR_SIZE; i++) {
        rc = al_fa_remove(array, 0);
        TEST_ASSERT_EQUAL_INT(0, rc);
    }
    TEST_ASSERT_EQUAL_UINT32(0, al_fa_get_count(array));
}

void test_random_add_then_random_remove() {
    int i, rc;

    for (i = 0; i < 3; i++) {
        rc = al_fa_add(array, 0, &ARR[i]);
        TEST_ASSERT_EQUAL_INT(0, rc);
    }
    TEST_ASSERT_EQUAL_UINT32(3, al_fa_get_count(array)); // 3,2,1

    rc = al_fa_remove(array, 1);
    TEST_ASSERT_EQUAL_INT(0, rc);
    TEST_ASSERT_EQUAL_UINT32(2, al_fa_get_count(array)); //remove 2 then 3,1
    TEST_ASSERT_EQUAL_INT(3, *(int* )al_fa_get_data(array, 0));
    TEST_ASSERT_EQUAL_INT(1, *(int* )al_fa_get_data(array, 1));

    rc = al_fa_add(array, 1, &ARR[3]);
    TEST_ASSERT_EQUAL_INT(0, rc);
    rc = al_fa_add(array, 1, &ARR[4]);
    TEST_ASSERT_EQUAL_INT(0, rc);
    TEST_ASSERT_EQUAL_UINT32(4, al_fa_get_count(array)); //remove 2 then 3,5,4,1
    TEST_ASSERT_EQUAL_INT(3, *(int* )al_fa_get_data(array, 0));
    TEST_ASSERT_EQUAL_INT(5, *(int* )al_fa_get_data(array, 1));
    TEST_ASSERT_EQUAL_INT(4, *(int* )al_fa_get_data(array, 2));
    TEST_ASSERT_EQUAL_INT(1, *(int* )al_fa_get_data(array, 3));

    al_fa_clear(array);
    TEST_ASSERT_EQUAL_UINT32(0, al_fa_get_count(array));
}

void test_add_null_element_and_index_out_of_range() {
    int rc;

    rc = al_fa_add(array, 0, NULL);
    TEST_ASSERT_EQUAL_INT(0, rc);

    TEST_ASSERT_EQUAL_UINT32(1, al_fa_get_count(array));
    TEST_ASSERT_EQUAL_INT(0, *(int* )al_fa_get_data(array, 0));

    TEST_ASSERT_EQUAL_PTR(NULL, al_fa_get_data(array, 1));

    TEST_ASSERT_EQUAL_INT(1, al_fa_remove(array, 1));

    TEST_ASSERT_EQUAL_INT(1, al_fa_add(array, 2, NULL));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_add_as_last_then_remove_from_last);
    RUN_TEST(test_add_as_first_then_remove_from_first);
    RUN_TEST(test_random_add_then_random_remove);
    RUN_TEST(test_add_null_element_and_index_out_of_range);
    return UNITY_END();
}
