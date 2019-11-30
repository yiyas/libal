#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct al_ll_iterator;
struct al_linkedlist;
typedef void* al_ll_data_ptr;
typedef const void* al_ll_const_data_ptr;

struct al_linkedlist* al_ll_new(uint32_t elem_size);
void al_ll_destroy(struct al_linkedlist *llist);
void al_ll_clear(struct al_linkedlist *llist);
int al_ll_is_empty(const struct al_linkedlist *llist);

int al_ll_insert_front(struct al_linkedlist *llist, al_ll_const_data_ptr element);
int al_ll_insert_back(struct al_linkedlist *llist, al_ll_const_data_ptr element);
void al_ll_remove(struct al_ll_iterator *iter);

struct al_ll_iterator* al_ll_get_next(struct al_linkedlist *llist, struct al_ll_iterator *iter);
struct al_ll_iterator* al_ll_get_prev(struct al_linkedlist *llist, struct al_ll_iterator *iter);

#define al_ll_get_data(iter) ((al_ll_data_ptr)((void**)(iter) + 2))

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

#ifdef __cplusplus
}
#endif

#endif /* LINKED_LIST_H_ */
