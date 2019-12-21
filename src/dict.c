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
    dict_table = al_ht_str_new(sizeof(uint32_t), init_size, 1);
    return dict_table ? 0 : 1;
}

void al_dict_destroy(void) {
    al_ht_destroy(dict_table);
}

static const char* add_str(const char *str, int ds) {
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
        if(ds) {
            free((char*)str);
        }
    } else {
        if (ds) {
            dup = (char*) str;
        } else {
            dup = strdup(str);
            CHECK_NOMEM_RT(dup, NULL);
        }

        rt = al_ht_put(dict_table, &dup, &one, &iter);
        CHECK_INTERR_DO_RT(rt, free(dup), NULL);
    }

    return *(const char**) al_ht_iterkey(dict_table, iter);
}

const char* al_dict_add(const char *str) {
    return add_str(str, 0);
}

const char* al_dict_add_n(const char *str, uint32_t size) {
    char *dup = NULL;

    dup = strndup(str, size);
    CHECK_NOMEM_RT(dup, NULL);

    return al_dict_add_ds(dup);
}

const char* al_dict_add_ds(char *str) {
    return add_str(str, 1);
}

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
            al_ht_iterremove(dict_table, iter);
        } else {
            (*count)--;
        }
    }
}
