/**
 * Copyright (c) 2015 - 2017 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef AL_LINKED_LIST_H_
#define AL_LINKED_LIST_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct al_ll_iterator;
struct al_linked_list;
typedef void* al_ll_data_ptr;
typedef const void* al_ll_const_data_ptr;

struct al_linked_list* al_ll_new();
void al_ll_destroy(struct al_linked_list *llist);
void al_ll_clear(struct al_linked_list *llist);
int al_ll_is_empty(const struct al_linked_list *llist);

int al_ll_insert_front(struct al_linked_list *llist, al_ll_const_data_ptr element, uint32_t elem_size);
int al_ll_insert_back(struct al_linked_list *llist, al_ll_const_data_ptr element, uint32_t elem_size);
void al_ll_remove(struct al_ll_iterator *iter);

struct al_ll_iterator* al_ll_get_next(struct al_linked_list *llist, struct al_ll_iterator *iter);
struct al_ll_iterator* al_ll_get_prev(struct al_linked_list *llist, struct al_ll_iterator *iter);

#define al_ll_get_data(iter, TYPE) ((TYPE*)((al_ll_data_ptr)((void**)(iter) + 2)))

#define AL_LL_FOR(llist, iter) \
	for(iter = al_ll_get_next(llist, NULL); iter; iter = al_ll_get_next(llist, iter))

#define AL_LL_FOR_SAFE(llist, iter, iter_next) \
	for(iter = al_ll_get_next(llist, NULL); \
			iter ? (iter_next = al_ll_get_next(llist, iter), 1) : 0; \
			iter = iter_next)

#define AL_LL_INV_FOR(llist, iter) \
	for(iter = al_ll_get_prev(llist, NULL); iter; iter = al_ll_get_prev(llist, iter))

#define AL_LL_INV_FOR_SAFE(llist, iter, iter_next) \
	for(iter = al_ll_get_prev(llist, NULL); \
			iter ? (iter_next = al_ll_get_prev(llist, iter), 1) : 0; \
			iter = iter_next)

inline static int al_ll_insert_int_front(struct al_linked_list *llist, int element) {
    return al_ll_insert_front(llist, &element, sizeof(int));
}

inline static int al_ll_insert_int_back(struct al_linked_list *llist, int element) {
    return al_ll_insert_back(llist, &element, sizeof(int));
}

#ifdef __cplusplus
}
#endif

#endif /* AL_LINKED_LIST_H_ */
