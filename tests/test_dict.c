/**
 * Copyright (c) 2015 - 2021 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#include <libal/dict.h>
#include <stddef.h>
#include <string.h>

#include "unity/unity.h"

void setUp(void) {
    TEST_ASSERT_EQUAL_INT(0, al_dict_init(0));
}

void tearDown(void) {
    al_dict_destroy();
}

void test_dict_add_remove() {
    const char *str1, *str2, *str3, *str4, *str5;

    str1 = al_dict_add("abc");
    TEST_ASSERT_EQUAL_STRING("abc", str1);
    str2 = al_dict_add("def");
    TEST_ASSERT_EQUAL_STRING("def", str2);

    str3 = al_dict_add("abc");
    TEST_ASSERT_EQUAL_STRING("abc", str3);
    TEST_ASSERT_EQUAL_PTR(str1, str3);

    str4 = al_dict_add_n("abcd", 3);
    TEST_ASSERT_EQUAL_STRING("abc", str4);
    TEST_ASSERT_EQUAL_PTR(str1, str4);

    str5 = al_dict_add_ds(strdup("abc"));
    TEST_ASSERT_EQUAL_STRING("abc", str5);
    TEST_ASSERT_EQUAL_PTR(str1, str5);

    al_dict_remove(str1);
    al_dict_remove(str2);
    al_dict_remove(str3);
    al_dict_remove(str4);
    al_dict_remove(str5);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_dict_add_remove);
    return UNITY_END();
}
