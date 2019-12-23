/**
 * Copyright (c) 2015 - 2017 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef FLEXIBLE_ARRAY_H_
#define FLEXIBLE_ARRAY_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AL_FA_INVALID_INDEX   ((uint32_t)-1)

struct al_flexible_array;
typedef void* al_fa_data_ptr;
typedef const void* al_fa_const_data_ptr;

struct al_flexible_array* al_fa_new(uint32_t elem_size, uint32_t init_len, uint32_t inc_len);
void al_fa_destroy(struct al_flexible_array *array);
void al_fa_clear(struct al_flexible_array *array);

int al_fa_add(struct al_flexible_array *array, uint32_t index, al_fa_const_data_ptr element);
int al_fa_remove(struct al_flexible_array *array, uint32_t index);

uint32_t al_fa_get_count(struct al_flexible_array *array);
al_fa_data_ptr al_fa_get_data(struct al_flexible_array *array, uint32_t index);

#ifdef __cplusplus
}
#endif

#endif /* FLEXIBLE_ARRAY_H_ */
