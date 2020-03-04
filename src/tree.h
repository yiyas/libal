/**
 * Copyright (c) 2015 - 2017 YIYAS
 *
 * This source code is licensed under BSD 3-Clause License (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://opensource.org/licenses/BSD-3-Clause
 */
#ifndef AL_TREE_H_
#define AL_TREE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct al_tree;
struct al_tree_node;
struct al_tree_iterator;

typedef void* al_tree_data_ptr;
typedef const void* al_tree_const_data_ptr;

struct al_tree_node* al_tree_new(al_tree_const_data_ptr data, uint32_t size);
void al_tree_destroy(struct al_tree_node *node, int with_sibling);

int al_tree_add_p(struct al_tree *tree, struct al_tree_iterator *parent,
        al_tree_const_data_ptr data, uint32_t size);
int al_tree_add_s(struct al_tree *tree, struct al_tree_iterator *prev,
        al_tree_const_data_ptr data, uint32_t size);
int al_tree_free(struct al_tree *tree, struct al_tree_iterator *node);


#ifdef __cplusplus
}
#endif

#endif /* AL_TREE_H_ */
