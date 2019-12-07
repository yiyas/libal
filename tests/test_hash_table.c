#include <stddef.h>

#include "../src/hash_table.h"
#include "unity/unity.h"

static const char* STRS[] = { "aa", "bb", "cc", "c1234", "x1", "y12", "112233" };
static const int INTS[] = { 1, 2, 3, 4, 5, 6, 7 };

static struct al_hash_table *ht = NULL;

void setUp(void) {
    ht = al_ht_str_new((uint32_t) sizeof(INTS[0]), 0);
}

void tearDown(void) {
    al_ht_destroy(ht);
}

void test_ht_put_get_remove() {
    TEST_ASSERT_EQUAL_UINT32(0, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], &INTS[0]));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[1], &INTS[1]));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[2], &INTS[2]));
    TEST_ASSERT_EQUAL_UINT32(3, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[3], &INTS[3]));
    TEST_ASSERT_EQUAL_UINT32(4, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[4], &INTS[4]));
    TEST_ASSERT_EQUAL_UINT32(5, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[5], &INTS[5]));
    TEST_ASSERT_EQUAL_UINT32(6, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[6], &INTS[6]));
    TEST_ASSERT_EQUAL_UINT32(7, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(1, *(int* )al_ht_get(ht, &STRS[0]));
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_ht_get(ht, &STRS[1]));
    TEST_ASSERT_EQUAL_INT(3, *(int* )al_ht_get(ht, &STRS[2]));
    TEST_ASSERT_EQUAL_INT(4, *(int* )al_ht_get(ht, &STRS[3]));
    TEST_ASSERT_EQUAL_INT(5, *(int* )al_ht_get(ht, &STRS[4]));
    TEST_ASSERT_EQUAL_INT(6, *(int* )al_ht_get(ht, &STRS[5]));
    TEST_ASSERT_EQUAL_INT(7, *(int* )al_ht_get(ht, &STRS[6]));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[0]));
    TEST_ASSERT_EQUAL_UINT32(6, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[1]));
    TEST_ASSERT_EQUAL_UINT32(5, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[2]));
    TEST_ASSERT_EQUAL_UINT32(4, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[3]));
    TEST_ASSERT_EQUAL_UINT32(3, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[4]));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[5]));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(0, al_ht_remove(ht, &STRS[6]));
    TEST_ASSERT_EQUAL_UINT32(0, al_ht_size(ht));
}

void test_ht_clear() {
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], &INTS[0]));
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[1], &INTS[1]));
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[2], &INTS[2]));
    TEST_ASSERT_EQUAL_UINT32(3, al_ht_size(ht));

    al_ht_clear(ht);

    TEST_ASSERT_NULL(al_ht_get(ht, &STRS[0]));
    TEST_ASSERT_NULL(al_ht_get(ht, &STRS[1]));
    TEST_ASSERT_NULL(al_ht_get(ht, &STRS[2]));

    TEST_ASSERT_EQUAL_UINT32(0, al_ht_size(ht));
}

void test_ht_put_same_key() {
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], &INTS[0]));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));

    TEST_ASSERT_EQUAL_INT(1, *(int* )al_ht_get(ht, &STRS[0]));

    TEST_ASSERT_EQUAL_INT(1, al_ht_put(ht, &STRS[0], &INTS[1]));

    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_ht_get(ht, &STRS[0]));
}

void test_ht_put_null_key() {
    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[0], NULL));
    TEST_ASSERT_EQUAL_UINT32(1, al_ht_size(ht));
    TEST_ASSERT_EQUAL_INT(0, *(int* )al_ht_get(ht, &STRS[0]));

    TEST_ASSERT_EQUAL_INT(0, al_ht_put(ht, &STRS[1], &INTS[1]));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));
    TEST_ASSERT_EQUAL_INT(2, *(int* )al_ht_get(ht, &STRS[1]));

    TEST_ASSERT_EQUAL_INT(1, al_ht_put(ht, &STRS[1], NULL));
    TEST_ASSERT_EQUAL_UINT32(2, al_ht_size(ht));
    TEST_ASSERT_EQUAL_INT(0, *(int* )al_ht_get(ht, &STRS[1]));
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_ht_put_get_remove);
    RUN_TEST(test_ht_clear);
    RUN_TEST(test_ht_put_same_key);
    RUN_TEST(test_ht_put_null_key);
    return UNITY_END();
}
