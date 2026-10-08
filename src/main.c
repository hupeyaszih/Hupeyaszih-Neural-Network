#include "core/brain.h"
#include "utils/vector.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello from hupeyaszih-neural-network (C)!\n");

    struct brain_region_info default_region;
    brain_init_brain_region_info(&default_region, 0, "default region", BRAIN_REGION_TYPE_DEFAULT, 16, 4, 20);

    struct brain_region_info vta;
    brain_init_brain_region_info(&vta, 1, "VTA", BRAIN_REGION_TYPE_DOPAMINERGIC, 4, 4, 10);


    struct brain_region_wiring_info vta_def;
    brain_init_brain_region_wiring_info(&vta_def, 0, 1, 10, 22);

    struct brain_region_wiring_info def_vta;
    brain_init_brain_region_wiring_info(&def_vta, 1, 0, 10, 22);


    struct vector *region_list = vector_create_vector(2, sizeof(struct brain_region_info));
    vector_add_element(region_list, &default_region);
    vector_add_element(region_list, &vta);


    struct vector *wiring_config = vector_create_vector(2, sizeof(struct brain_region_wiring_info));
    vector_add_element(wiring_config, &vta_def);
    vector_add_element(wiring_config, &def_vta);


    struct brain_map brain_map = brain_init_brain_map(region_list, wiring_config);

    brain_start(brain_map);

    return 0;
}
