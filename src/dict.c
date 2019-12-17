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

#include "al_pub.h"
#include "hash_table.h"
#include "dict.h"

static struct al_hash_table *dict_table = NULL;

int al_dict_init(uint32_t init_size) {
    dict_table = al_ht_str_new(sizeof(uint32_t), init_size);
    return dict_table ? 0 : 1;
}

void al_dict_destroy(void) {
    //TODO: free all string in table
    al_ht_destroy(dict_table);
}

const char* al_dict_add(const char *str) {
    al_hash_iter iter;
    uint32_t *count, one = 1;
    char *dup = NULL;
    int rt;

    if (!str) {
        return NULL;
    }

    iter = al_ht_get(dict_table, &str);
    if (iter != AL_HT_ITER_INVALID) {
        count = al_ht_iterval(dict_table, iter);
        (*count)++;
        return *(const char**) al_ht_iterkey(dict_table, iter);
    }

    dup = strdup(str);
    CHECK_NOMEM_RT(dup, NULL);

    rt = al_ht_put(dict_table, &dup, &one, &iter);
    CHECK_INTERR_DO_RT(rt, free(dup), NULL);

    return *(const char**) al_ht_iterkey(dict_table, iter);
}
//
//const char* al_dict_add_n(const char *str, uint32_t size) {
//}
//
//const char* al_dict_add_ds(char *str) {
//}

void al_dict_remove(const char *str) {
    al_hash_iter iter;
    uint32_t *count;

    if(!str) {
        return;
    }

    iter = al_ht_get(dict_table, &str);
    if (iter != AL_HT_ITER_INVALID) {
        count = al_ht_iterval(dict_table, iter);
        if (*count <= 1) {
            //TODO
            free(*(char**)al_ht_iterkey(dict_table, iter));
            al_ht_iterremove(dict_table, iter);
        } else {
            (*count)--;
        }
    }
}
