#include <stddef.h>

#include "../src/linked_list.h"
#include "unity/unity.h"

static const int ARR[] = { 1, 2, 3, 4, 5 };

struct al_linked_list *llist = NULL;

void setUp(void) {
	llist = al_ll_new(sizeof(ARR[0]));
}

void tearDown(void) {
	al_ll_destroy(llist);
}

static void build_list_with_inert_back() {
    int i;

    for (i = 0; i < (int) (sizeof(ARR) / sizeof(ARR[0])); i++) {
        al_ll_insert_back(llist, &ARR[i]);
    }
}

static void build_list_with_inert_front() {
    int i;

    for (i = 4; i >= 0; i--) {
        al_ll_insert_front(llist, &ARR[i]);
    }
}

static void iter_list_with_for() {
    int i;
    struct al_ll_iterator *iter;
    int *ptr;

    i = 1;
    AL_LL_FOR(llist, iter)
    {
        ptr = al_ll_get_data(iter);
        TEST_ASSERT_EQUAL_INT(i, *(int* )ptr);
        i++;
    }
}

static void iter_list_with_inv_for() {
    int i;
    struct al_ll_iterator *iter;
    int *ptr;

    i = 5;
    AL_LL_INV_FOR(llist, iter)
    {
        ptr = al_ll_get_data(iter);
        TEST_ASSERT_EQUAL_INT(i, *(int* )ptr);
        i--;
    }
}

static void iter_list_with_for_safe_then_remove() {
    int i;
    struct al_ll_iterator *iter, *next;
    int *ptr;

    i = 1;
    AL_LL_FOR_SAFE(llist, iter, next)
    {
        ptr = al_ll_get_data(iter);
        TEST_ASSERT_EQUAL_INT(i, *(int* )ptr);
        i++;
        al_ll_remove(iter);
    }

    TEST_ASSERT_TRUE(al_ll_is_empty(llist));
}

static void iter_list_with_inv_for_safe_then_remove() {
    int i;
    struct al_ll_iterator *iter, *next;
    int *ptr;

    i = 5;
    AL_LL_INV_FOR_SAFE(llist, iter, next)
    {
        ptr = al_ll_get_data(iter);
        TEST_ASSERT_EQUAL_INT(i, *(int* )ptr);
        i--;
        al_ll_remove(iter);
    }

    TEST_ASSERT_TRUE(al_ll_is_empty(llist));
}

typedef void (*FUNCTION)();

static void test11() {
    build_list_with_inert_back();
    iter_list_with_for();
}

static void test12() {
    build_list_with_inert_back();
    iter_list_with_inv_for();
}

static void test13() {
    build_list_with_inert_back();
    iter_list_with_for_safe_then_remove();
}

static void test14() {
    build_list_with_inert_back();
    iter_list_with_inv_for_safe_then_remove();
}

static void test21() {
    build_list_with_inert_front();
    iter_list_with_for();
}

static void test22() {
    build_list_with_inert_front();
    iter_list_with_inv_for();
}

static void test23() {
    build_list_with_inert_front();
    iter_list_with_for_safe_then_remove();
}

static void test24() {
    build_list_with_inert_front();
    iter_list_with_inv_for_safe_then_remove();
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(test11);
	RUN_TEST(test12);
	RUN_TEST(test13);
	RUN_TEST(test14);
	RUN_TEST(test21);
	RUN_TEST(test22);
	RUN_TEST(test23);
	RUN_TEST(test24);
	return UNITY_END();
}
