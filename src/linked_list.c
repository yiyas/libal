#ifndef LINKEDLIST_C_
#define LINKEDLIST_C_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "al_pub.h"

struct al_ll_iterator {
	struct al_ll_iterator *prev;
	struct al_ll_iterator *next;
	char data[0];
};

struct al_linkedlist {
	struct al_ll_iterator head;
	uint32_t elem_size;
};

struct al_linkedlist* al_ll_new(uint32_t elem_size) {
    struct al_linkedlist *llist;

    llist = calloc(1, sizeof(*llist));
    CHECK_NOMEM_RT(llist, NULL);

    llist->elem_size = elem_size;
    llist->head.next = &llist->head;
    llist->head.prev = &llist->head;

	return llist;
}

void al_ll_destroy(struct al_linkedlist *llist) {
    al_ll_clear(llist);
    free(llist);
}

void al_ll_clear(struct al_linkedlist *llist) {
    if (!llist) {
        return;
    }

    while (llist->head.next != &llist->head) {
        al_ll_remove(llist, llist->head.next);
    }
}

int al_ll_is_empty(const struct al_linkedlist *llist) {
	return !llist || llist->head.next == llist->head.prev;
}

static int insert_after(struct al_linkedlist *llist, struct al_ll_iterator *iter, al_ll_const_data_ptr element) {
    struct al_ll_iterator *tmp;

    tmp = calloc(1, sizeof(*tmp) + llist->elem_size);
    CHECK_NOMEM_RT(tmp, -1);

    if(element) {
        memcpy(tmp->data, element, llist->elem_size);
    }

    tmp->next = iter->next;
    iter->next->prev = tmp;

    tmp->prev = iter;
    iter->next = tmp;

    return 0;
}

int al_ll_insert_front(struct al_linkedlist *llist, al_ll_const_data_ptr element) {
    CHECK_NULLARG_RT(llist, -1);
    return insert_after(llist, &llist->head, element);
}

int al_ll_insert_back(struct al_linkedlist *llist, al_ll_const_data_ptr element) {
    CHECK_NULLARG_RT(llist, -1);
    return insert_after(llist, llist->head.prev, element);
}

int al_ll_remove(struct al_linkedlist *llist, struct al_ll_iterator *iter) {
    CHECK_NULLARG2_RT(llist, iter, -1);

    iter->next->prev = iter->prev;
    iter->prev->next = iter->next;

    free(iter);

    return 0;
}

struct al_ll_iterator* al_ll_get_next(struct al_linkedlist *llist, struct al_ll_iterator *iter) {
    if (al_ll_is_empty(llist)) {
        return NULL;
    }

    if (!iter) {
        iter = &llist->head;
    }

    return iter->next == &llist->head ? NULL : iter->next;
}

struct al_ll_iterator* al_ll_get_prev(struct al_linkedlist *llist, struct al_ll_iterator *iter) {
    if (al_ll_is_empty(llist)) {
        return NULL;
    }

    if (!iter) {
        iter = &llist->head;
    }

    return iter->prev == &llist->head ? NULL : iter->prev;
}

#endif /* LINKEDLIST_C_ */
