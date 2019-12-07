#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct al_hash_table;
typedef void* al_hash_key_ptr;
typedef void* al_hash_val_ptr;
typedef const void* al_hash_const_key_ptr;
typedef const void* al_hash_const_val_ptr;

typedef uint32_t (*al_hash_calc_function)(al_hash_const_key_ptr key);
typedef int (*al_hash_cmp_function)(al_hash_const_key_ptr key1, al_hash_const_key_ptr key2);

struct al_hash_table* al_ht_new(uint32_t key_size, uint32_t val_size, al_hash_calc_function calc_func,
        al_hash_cmp_function eq_func, uint32_t init_capacity);
void al_ht_destroy(struct al_hash_table *ht);
void al_ht_clear(struct al_hash_table *ht);

//void al_ht_set_up_factor(struct al_hash_table *ht, uint8_t factor);
//void al_ht_set_down_factor(struct al_hash_table *ht, uint8_t factor);
//
//uint8_t al_ht_get_up_factor(struct al_hash_table *ht);
//uint8_t al_ht_get_down_factor(struct al_hash_table *ht);

uint32_t al_ht_size(struct al_hash_table *ht);
al_hash_val_ptr al_ht_get(struct al_hash_table *ht, al_hash_const_key_ptr key);
int al_ht_put(struct al_hash_table *ht, al_hash_const_key_ptr key, al_hash_const_val_ptr val);
int al_ht_remove(struct al_hash_table *ht, al_hash_const_key_ptr key);

struct al_hash_table* al_ht_str_new(uint32_t val_size, uint32_t init_capacity);

#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_H_ */
