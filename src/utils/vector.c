#include "utils/vector.h"
#include <stdlib.h>
#include <string.h>

struct vector *vector_create_vector(uint64_t capacity, uint64_t type_size) {
    struct vector *vector = calloc(1, sizeof(struct vector));
    vector->type_size = type_size;
    vector->capacity = capacity;

    vector->element_count = 0;
    vector->data = calloc(capacity, type_size);

    return vector;
}

void vector_delete_vector(struct vector *vector) {
    if(NULL == vector) return;
    free(vector->data);
    free(vector);
}

void *vector_get_element(struct vector *vector, uint64_t element_id) {
    if(NULL == vector) return NULL;

    return vector->data + element_id * vector->type_size;
}

void vector_add_element(struct vector *vector, void *data) {
    if(NULL == vector) return;
    if(vector->element_count >= vector->capacity) return; // TODO: resizing required

    void *target = (char *) vector->data + (vector->element_count * vector->type_size);
    memcpy(target, data, vector->type_size);

    ++vector->element_count;
}
