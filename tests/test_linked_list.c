#include <stddef.h>

#include "../src/linked_list.h"
#include "unity/unity.h"

static const int ARR[] = { 1, 2, 3, 4, 5 };

struct al_linkedlist *llist = NULL;

void setUp(void) {
	llist = al_ll_new(sizeof(ARR[0]));
}

void tearDown(void) {
	al_ll_destroy(llist);
}

static void insert_back_then_iterate_then_destroy() {
	int i;
	struct al_ll_iterator *iter;
	int *ptr;

	for (i = 0; i < (int)(sizeof(ARR) / sizeof(ARR[0])); i++) {
		al_ll_insert_back(llist, &ARR[i]);
	}

    i = 1;
    AL_LL_FOR(llist, iter)
    {
        ptr = al_ll_get_data(iter);
        TEST_ASSERT_EQUAL_INT(i, *(int* )ptr);
        i++;
    }
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(insert_back_then_iterate_then_destroy);
	return UNITY_END();
}
