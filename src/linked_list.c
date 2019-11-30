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

struct al_linked_list {
	struct al_ll_iterator head;
	uint32_t elem_size;
};

struct al_linked_list* al_ll_new(uint32_t elem_size) {
    struct al_linked_list *llist;

    llist = calloc(1, sizeof(*llist));
    CHECK_NOMEM_RT(llist, NULL);

    llist->elem_size = elem_size;
    llist->head.next = &llist->head;
    llist->head.prev = &llist->head;

	return llist;
}

void al_ll_destroy(struct al_linked_list *llist) {
    al_ll_clear(llist);
    free(llist);
}

void al_ll_clear(struct al_linked_list *llist) {
    if (!llist) {
        return;
    }

    while (llist->head.next != &llist->head) {
        al_ll_remove(llist->head.next);
    }
}

int al_ll_is_empty(const struct al_linked_list *llist) {
	return !llist || llist->head.next == llist->head.prev;
}

static int insert_after(struct al_linked_list *llist, struct al_ll_iterator *iter, al_ll_const_data_ptr element) {
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

int al_ll_insert_front(struct al_linked_list *llist, al_ll_const_data_ptr element) {
    CHECK_NULLARG_RT(llist, -1);
    return insert_after(llist, &llist->head, element);
}

int al_ll_insert_back(struct al_linked_list *llist, al_ll_const_data_ptr element) {
    CHECK_NULLARG_RT(llist, -1);
    return insert_after(llist, llist->head.prev, element);
}

void al_ll_remove(struct al_ll_iterator *iter) {
    if (!iter) {
        return;
    }
    iter->next->prev = iter->prev;
    iter->prev->next = iter->next;
    free(iter);
}

struct al_ll_iterator* al_ll_get_next(struct al_linked_list *llist, struct al_ll_iterator *iter) {
    if (al_ll_is_empty(llist)) {
        return NULL;
    }

    if (!iter) {
        iter = llist->head.next;
    } else {
        iter = iter->next;
    }

    return iter->next == &llist->head ? NULL : iter;
}

struct al_ll_iterator* al_ll_get_prev(struct al_linked_list *llist, struct al_ll_iterator *iter) {
    if (al_ll_is_empty(llist)) {
        return NULL;
    }

    if (!iter) {
        iter = llist->head.prev;
    } else {
        iter = iter->prev;
    }

    return iter == &llist->head ? NULL : iter;
}

#endif /* LINKEDLIST_C_ */
