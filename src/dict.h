/**
 * Copyright (c) 2015 - 2017 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef AL_DICT_H_
#define AL_DICT_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int al_dict_init(uint32_t init_size);
void al_dict_destroy(void);

const char* al_dict_add(const char *str);
const char* al_dict_add_n(const char *str, uint32_t size);
const char* al_dict_add_ds(char *str);

void al_dict_remove(const char *str);

#ifdef __cplusplus
}
#endif

#endif /* AL_DICT_H_ */
