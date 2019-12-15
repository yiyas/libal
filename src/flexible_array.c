#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "flexible_array.h"
#include "al_pub.h"

struct al_flexible_array {
    uint32_t elem_size;
    uint32_t inc_len;

    uint32_t alloc_len;
    uint32_t used_len;

    al_fa_data_ptr data;
};

struct al_flexible_array* al_fa_new(uint32_t elem_size, uint32_t init_len, uint32_t inc_len) {
    struct al_flexible_array *array;

    array = calloc(1, sizeof(*array));
    CHECK_NOMEM_RT(array, NULL);

    array->data = calloc(init_len, elem_size);
    CHECK_NOMEM_DO_RT(array->data, free(array->data), NULL);

    array->alloc_len = init_len;
    array->elem_size = elem_size;
    array->inc_len = inc_len;

    return array;
}

void al_fa_destroy(struct al_flexible_array *array) {
    if(!array) {
        return;
    }

    free(array->data);
    free(array);
}

void al_fa_clear(struct al_flexible_array *array) {
    if(!array) {
        return;
    }

    array->used_len = 0;
}

inline static void move_element(struct al_flexible_array *array, uint32_t from, uint32_t to) {
    memmove(array->data + to * array->elem_size, array->data + from * array->elem_size,
            (size_t) (array->used_len - from) * array->elem_size);
}

int al_fa_add(struct al_flexible_array *array, uint32_t index, al_fa_const_data_ptr element) {
    al_fa_data_ptr tmp;

    CHECK_NULLARG_RT(array, -1);

    if (index == AL_FA_INVALID_INDEX) {
        index = array->used_len;
    }

    if (index > array->used_len) {
        return 1;
    }

    if (array->used_len == array->alloc_len) {
        tmp = realloc(array->data, (size_t) (array->alloc_len + array->inc_len) * array->elem_size);
        CHECK_NOMEM_RT(tmp, -1);
        array->data = tmp;
        array->alloc_len += array->inc_len;
    }

    if(index < array->used_len) {
        move_element(array, index, index + 1);
    }
    array->used_len++;

    if(element) {
        memcpy(array->data + index * array->elem_size, element, array->elem_size);
    } else {
        memset(array->data + index * array->elem_size, 0, array->elem_size);
    }

    return 0;
}

int al_fa_remove(struct al_flexible_array *array, uint32_t index) {
    CHECK_NULLARG_RT(array, -1);

    if (index == AL_FA_INVALID_INDEX) {
        index = array->used_len ? array->used_len - 1 : 0;
    }

    if (index >= array->used_len) {
        return 1;
    }

    if (index + 1 < array->used_len) {
        move_element(array, index + 1, index);
    }
    array->used_len--;

    return 0;
}

uint32_t al_fa_get_count(struct al_flexible_array *array) {
    if(!array) {
        return 0;
    }

    return array->used_len;
}

al_fa_data_ptr al_fa_get_data(struct al_flexible_array *array, uint32_t index) {
    if(!array) {
        return NULL;
    }

    if(index >= array->used_len) {
        return NULL;
    }

    return array->data + index * array->elem_size;
}





