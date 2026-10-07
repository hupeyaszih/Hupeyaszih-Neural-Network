#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
///< @brief A vector struct to help brain mapping infos to hold and create. Currently, only planned for using to hold brain infos.
struct vector {
    void *data;
    uint64_t element_count;
    uint64_t capacity;
    uint64_t type_size;
};

struct vector *vector_create_vector(uint64_t capacity, uint64_t type_size);
void vector_delete_vector(struct vector *vector);

void *vector_get_element(struct vector *vector, uint64_t element_id);
void vector_add_element(struct vector *vector, void *data);

#endif
