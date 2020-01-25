/**
 * Copyright (c) 2015 - 2017 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#include "pub.h"

#define DEFAULT_UP_FACTOR       ((uint8_t)75)
#define DEFAULT_INIT_CAPACITY   ((uint32_t)8)
#define DEFAULT_ENLARGE_RATE    (2)

struct hash_node {
    uint32_t hit;
    uint32_t hash_code;

    char data[0];
};

struct al_hash_table {
    uint32_t key_size;
    uint32_t val_size;
    al_hash_calc_function hash_func;
    al_hash_cmp_function cmp_func;
    uint8_t up_factor;
    uint8_t padding[3];
    uint32_t init_capacity;
    uint32_t capacity;
    uint32_t count;
    al_hash_free destructor;

    struct hash_node *data;
};

#define NEXT_POS(ht, i)   ((i + 1) % ht->capacity)
#define NODE_LEN(ht)      (sizeof(struct hash_node) + ht->key_size + ht->val_size)
#define NODE_PTR(ht, i)   ((struct hash_node*)((char*)ht->data + i * NODE_LEN(ht)))
#define KEY_PTR(ht, i)    ((al_hash_key_ptr)((char*)ht->data + i * NODE_LEN(ht) + sizeof(struct hash_node)))
#define VAL_PTR(ht, i)    ((al_hash_val_ptr)((char*)ht->data + i * NODE_LEN(ht) + sizeof(struct hash_node) + ht->key_size))

struct al_hash_table* al_ht_new(uint32_t key_size, uint32_t val_size, al_hash_calc_function hash_func,
        al_hash_cmp_function cmp_func, uint32_t init_capacity) {
    struct al_hash_table *ht;

    if (!key_size || !hash_func || !cmp_func) {
        return NULL;
    }

    ht = calloc(1, sizeof(*ht));
    CHECK_NOMEM_RT(ht, NULL);

    ht->key_size = key_size;
    ht->val_size = val_size;
    ht->hash_func = hash_func;
    ht->cmp_func = cmp_func;
    ht->up_factor = DEFAULT_UP_FACTOR;
    ht->init_capacity = init_capacity < DEFAULT_INIT_CAPACITY ? DEFAULT_INIT_CAPACITY : init_capacity;

    ht->data = calloc(ht->init_capacity, NODE_LEN(ht));
    CHECK_NOMEM_DO_RT(ht->data, free(ht), NULL);

    ht->capacity = ht->init_capacity;
    ht->count = 0;

    return ht;
}

inline static void destroy_by_pos(struct al_hash_table *ht, uint32_t pos) {
    if(ht->destructor) {
        ht->destructor(KEY_PTR(ht, pos), VAL_PTR(ht, pos));
    }
}

void al_ht_set_destructor(struct al_hash_table *ht, al_hash_free destructor) {
    if(!ht) {
        return;
    }

    ht->destructor = destructor;
}

void al_ht_clear(struct al_hash_table *ht) {
    uint32_t i;

    if(!ht) {
        return;
    }

    for (i = 0; i < ht->capacity; i++) {
        if(NODE_PTR(ht, i)->hit) {
            destroy_by_pos(ht, i);
            NODE_PTR(ht, i)->hit = 0;
        }
    }
    ht->count = 0;
}

void al_ht_destroy(struct al_hash_table *ht) {
    if(!ht) {
        return;
    }

    al_ht_clear(ht);

    free(ht->data);
    free(ht);
}

uint32_t al_ht_size(struct al_hash_table *ht) {
    return ht->count;
}

static uint32_t find_next_unused_pos(struct al_hash_table *ht, uint32_t pos) {
    uint32_t i;

    for (i = NEXT_POS(ht, pos); i != pos; i = NEXT_POS(ht, i)) {
        if(!NODE_PTR(ht, i)->hit) {
            return i;
        }
    }

    return AL_HT_ITER_INVALID;
}

static uint32_t next_collision_pos(struct al_hash_table *ht, uint32_t pos, uint32_t primary_pos) {
    uint32_t tmp;

    for(tmp = NEXT_POS(ht, pos); tmp != primary_pos; tmp = NEXT_POS(ht, tmp)) {
        if (NODE_PTR(ht, pos)->hit && NODE_PTR(ht, pos)->hash_code % ht->capacity == primary_pos) {
            return tmp;
        }
    }

    return AL_HT_ITER_INVALID;
}

al_hash_iter al_ht_get(struct al_hash_table *ht, al_hash_const_key_ptr key) {
    uint32_t hash, primary_pos, pos, hit;

    hash = ht->hash_func(key);
    primary_pos = hash % ht->capacity;

    for (pos = primary_pos, hit = NODE_PTR(ht, primary_pos)->hit; pos != AL_HT_ITER_INVALID && hit;
            pos = next_collision_pos(ht, pos, primary_pos), hit--) {
        if (NODE_PTR(ht, pos)->hash_code == hash && !ht->cmp_func(key, KEY_PTR(ht, pos))) {
            return pos;
        }
    }

    return AL_HT_ITER_INVALID;
}

al_hash_key_ptr al_ht_iterkey(struct al_hash_table *ht, al_hash_iter iter) {
    return iter == AL_HT_ITER_INVALID ? NULL : KEY_PTR(ht, iter);
}

al_hash_val_ptr al_ht_iterval(struct al_hash_table *ht, al_hash_iter iter) {
    return iter == AL_HT_ITER_INVALID ? NULL : VAL_PTR(ht, iter);
}

al_hash_key_ptr al_ht_getkey(struct al_hash_table *ht, al_hash_const_key_ptr key) {
    return al_ht_iterkey(ht, al_ht_get(ht, key));
}

al_hash_val_ptr al_ht_getval(struct al_hash_table *ht, al_hash_const_key_ptr key) {
    return al_ht_iterval(ht, al_ht_get(ht, key));
}

static void set_val_to_pos(struct al_hash_table *ht, uint32_t pos, uint32_t hash,
        al_hash_const_key_ptr key, al_hash_const_val_ptr val) {
    NODE_PTR(ht, pos)->hash_code = hash;
    NODE_PTR(ht, pos)->hit = 1;
    ht->count++;
    memcpy(NODE_PTR(ht, pos)->data, key, ht->key_size);
    if (val) {
        memcpy(NODE_PTR(ht, pos)->data + ht->key_size, val, ht->val_size);
    } else {
        memset(NODE_PTR(ht, pos)->data + ht->key_size, 0, ht->val_size);
    }
    printf("add %s, hash: %u, pos: %u, pri_pos: %u\n", *(const char**) key, hash, pos, hash % ht->capacity);
}

static int add_collision_node(struct al_hash_table *ht, al_hash_const_key_ptr key, al_hash_const_val_ptr val,
        uint32_t hash, uint32_t primary_pos, al_hash_iter *iter) {
    al_hash_iter saved_iter;
    uint32_t tmp;

    saved_iter = al_ht_get(ht, key);
    if(saved_iter != AL_HT_ITER_INVALID) {
        if(val) {
            memcpy(VAL_PTR(ht, saved_iter), val, ht->val_size);
        } else {
            memset(VAL_PTR(ht, saved_iter), 0, ht->val_size);
        }
        if(iter) {
            *iter = saved_iter;
        }
        return 1;
    }

    NODE_PTR(ht, primary_pos)->hit++;

    tmp = find_next_unused_pos(ht, primary_pos);
    CHECK_INTERR_RT(tmp == AL_HT_ITER_INVALID, -1);
    set_val_to_pos(ht, tmp, hash, key, val);

    if(iter) {
        *iter = tmp;
    }

    return 0;
}

static int enlarge_table(struct al_hash_table *ht) {
    struct al_hash_table *ht2;
    uint32_t i;
    int rt;

    ht2 = al_ht_new(ht->key_size, ht->val_size, ht->hash_func, ht->cmp_func, ht->capacity * DEFAULT_ENLARGE_RATE);
    CHECK_NOMEM_RT(ht2, -1);

    for (i = 0; i < ht->capacity; i++) {
        if(NODE_PTR(ht, i)->hit) {
            rt = al_ht_put(ht2, KEY_PTR(ht, i), VAL_PTR(ht, i), NULL);
            CHECK_INTERR_DO_RT(rt, al_ht_destroy(ht2), -1);
        }
    }

    free(ht->data);
    memcpy(ht, ht2, sizeof(struct al_hash_table));
    free(ht2);

    return 0;
}

int al_ht_put(struct al_hash_table *ht, al_hash_const_key_ptr key, al_hash_const_val_ptr val, al_hash_iter *iter) {
    uint32_t hash, pos, next;
    int rt;

    CHECK_NULLARG2_RT(ht, key, -1);

    if(ht->count * 100 / ht->capacity >= ht->up_factor) {
        rt = enlarge_table(ht);
        CHECK_INTERR_RT(rt, rt);
    }

    hash = ht->hash_func(key);
    pos = hash % ht->capacity;
    if (!NODE_PTR(ht, pos)->hit) {
        set_val_to_pos(ht, pos, hash, key, val);
    } else {
        if(NODE_PTR(ht, pos)->hash_code % ht->capacity != pos) {
            next = find_next_unused_pos(ht, pos);
            CHECK_INTERR_RT(next == AL_HT_ITER_INVALID, -1);
            memcpy(NODE_PTR(ht, next), NODE_PTR(ht, pos), NODE_LEN(ht));
            set_val_to_pos(ht, pos, hash, key, val);
        } else {
            return add_collision_node(ht, key, val, hash, pos, iter);
        }
    }

    if(iter) {
        *iter = pos;
    }

    return 0;
}

static int remove_by_pos(struct al_hash_table *ht, al_hash_iter pos, uint32_t primary_pos) {
    if (pos == primary_pos && NODE_PTR(ht, primary_pos)->hit > 1) {
        // primary pos will be removed, find next ...
        pos = next_collision_pos(ht, pos, primary_pos);
        CHECK_INTERR_RT(pos == AL_HT_ITER_INVALID, -1);

        destroy_by_pos(ht, primary_pos);

        // move next to primary pos
        NODE_PTR(ht, primary_pos)->hash_code = NODE_PTR(ht, pos)->hash_code;
        memcpy(NODE_PTR(ht, primary_pos)->data, NODE_PTR(ht, pos)->data, ht->key_size + ht->val_size);
    } else {
        destroy_by_pos(ht, pos);
    }

    NODE_PTR(ht, primary_pos)->hit--;
    NODE_PTR(ht, pos)->hit = 0;
    ht->count--;

    return 0;
}

int al_ht_iterremove(struct al_hash_table *ht, al_hash_iter pos) {
    uint32_t primary_pos;

    if (pos >= ht->capacity || !NODE_PTR(ht, pos)->hit) {
        return 1;
    }

    primary_pos = NODE_PTR(ht, pos)->hash_code % ht->capacity;

    return remove_by_pos(ht, pos, primary_pos);
}

int al_ht_remove(struct al_hash_table *ht, al_hash_const_key_ptr key) {
    uint32_t hash, primary_pos, pos, hit;

    CHECK_NULLARG2_RT(ht, key, -1);

    hash = ht->hash_func(key);
    primary_pos = hash % ht->capacity;

    for (pos = primary_pos, hit = NODE_PTR(ht, primary_pos)->hit; pos != AL_HT_ITER_INVALID && hit;
            pos = next_collision_pos(ht, pos, primary_pos), hit--) {
        if (NODE_PTR(ht, pos)->hash_code == hash && !ht->cmp_func(key, KEY_PTR(ht, pos))) {
            break;
        }
    }

    if (pos == AL_HT_ITER_INVALID) {
        return 1;
    }

    return remove_by_pos(ht, pos, primary_pos);
}

/*
 * Bob Jenkin's one-at-a-time hash
 * http://www.burtleburtle.net/bob/hash/doobs.html
 */
static uint32_t str_hash(al_hash_const_key_ptr key) {
    const char *strkey;
    uint32_t hash, i;

    strkey = *(const char**) key;
    for (hash = i = 0; i < strlen(strkey); ++i) {
        hash += strkey[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

static int str_cmp(al_hash_const_key_ptr key1, al_hash_const_key_ptr key2) {
    return strcmp(*(const char**) key1, *(const char**) key2);
}

static void free_dynamic_str(al_hash_key_ptr key, al_hash_val_ptr val) {
    (void) val;
    free(*(char**) key);
}

struct al_hash_table* al_ht_str_new(uint32_t val_size, uint32_t init_capacity, int ds)
{
    struct al_hash_table *ht;

    ht = al_ht_new(sizeof(const char*), val_size, str_hash, str_cmp, init_capacity);
    if(ht && ds) {
        al_ht_set_destructor(ht, free_dynamic_str);
    }

    return ht;
}



