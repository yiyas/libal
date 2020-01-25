/**
 * Copyright (c) 2015 - 2017 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef AL_HASH_TABLE_H_
#define AL_HASH_TABLE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AL_HT_ITER_INVALID      ((uint32_t)-1)

struct al_hash_table;
typedef void* al_hash_key_ptr;
typedef void* al_hash_val_ptr;
typedef const void* al_hash_const_key_ptr;
typedef const void* al_hash_const_val_ptr;
typedef uint32_t al_hash_iter;

typedef uint32_t (*al_hash_calc_function)(al_hash_const_key_ptr key);
typedef int (*al_hash_cmp_function)(al_hash_const_key_ptr key1, al_hash_const_key_ptr key2);
typedef void (*al_hash_free)(al_hash_key_ptr key, al_hash_val_ptr val);

struct al_hash_table* al_ht_new(uint32_t key_size, uint32_t val_size, al_hash_calc_function calc_func,
        al_hash_cmp_function eq_func, uint32_t init_capacity);
void al_ht_destroy(struct al_hash_table *ht);
void al_ht_clear(struct al_hash_table *ht);
uint32_t al_ht_size(struct al_hash_table *ht);

void al_ht_set_destructor(struct al_hash_table *ht, al_hash_free destructor);

int al_ht_put(struct al_hash_table *ht, al_hash_const_key_ptr key, al_hash_const_val_ptr val, al_hash_iter *iter);
int al_ht_remove(struct al_hash_table *ht, al_hash_const_key_ptr key);

al_hash_iter al_ht_get(struct al_hash_table *ht, al_hash_const_key_ptr key);
al_hash_key_ptr al_ht_getkey(struct al_hash_table *ht, al_hash_const_key_ptr key);
al_hash_val_ptr al_ht_getval(struct al_hash_table *ht, al_hash_const_key_ptr key);
al_hash_key_ptr al_ht_iterkey(struct al_hash_table *ht, al_hash_iter iter);
al_hash_val_ptr al_ht_iterval(struct al_hash_table *ht, al_hash_iter iter);
int al_ht_iterremove(struct al_hash_table *ht, al_hash_iter iter);

struct al_hash_table* al_ht_str_new(uint32_t val_size, uint32_t init_capacity, int ds);

#ifdef __cplusplus
}
#endif

#endif /* AL_HASH_TABLE_H_ */
