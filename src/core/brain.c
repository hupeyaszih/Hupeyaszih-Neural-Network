#include "core/brain.h"
#include "utils/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum neuron_type {
    NEURON_TYPE_DEFAULT,
    NEURON_TYPE_DOPAMINERGIC,
    NEURON_TYPE_INHIBITORY
};

struct neurons_data { ///< @brief SoA
    uint16_t *last_spike_time;

    uint8_t *threshold;
    uint8_t *voltage;

    enum neuron_type *type;
};

struct synapses_data {
    uint16_t *target_brain_part;
    uint16_t *target_neuron_id;
    uint8_t *weight;
    uint8_t *latency;
};

struct brain_part {
    struct neurons_data  neurons;
    struct synapses_data synapses;

    uint32_t brain_region_id;
    uint8_t dopamine_level;
};

struct brain {
    struct brain_map map;
    struct brain_part *brain_parts;
    uint64_t brain_part_count;
};

struct brain *brain_create_brain(struct brain_map brain_map) {
    struct brain *brain = calloc(1, sizeof(struct brain));
    brain->map = brain_map;

    brain->brain_part_count = 0;
    brain->brain_parts = NULL;

    // calculate brain part count
    for(uint64_t i = 0;i < brain_map.brain_region_infos->element_count; ++i) {
        const struct brain_region_info *info = (struct brain_region_info *) vector_get_element(brain_map.brain_region_infos, i);
        uint64_t brain_part_count = info->neuron_count / info->neuron_count_per_brain_part;

        brain->brain_part_count += brain_part_count;
    }

    brain->brain_parts = calloc(brain->brain_part_count, sizeof(struct brain_part)); // allocating

    // initialize allocated brain parts
    uint64_t initialized_brain_part_count = 0;
    for(uint64_t i = 0;i < brain_map.brain_region_infos->element_count; ++i) {
        const struct brain_region_info *info = (struct brain_region_info *) vector_get_element(brain_map.brain_region_infos, i);
        uint64_t brain_part_count = info->neuron_count / info->neuron_count_per_brain_part;

        for(uint64_t j = 0;j < brain_part_count; ++j) {
            struct brain_part *part = brain->brain_parts + initialized_brain_part_count;
            part->brain_region_id = info->region_id;
            part->dopamine_level = 0;

            // TODO: initialize synapses and neurons

            ++initialized_brain_part_count;
        }
    }

    return brain;
}

void brain_delete_brain(struct brain *brain) {
    if(NULL == brain) return;

    vector_delete_vector(brain->map.brain_region_infos);
    vector_delete_vector(brain->map.brain_region_wiring_info);

    free(brain->brain_parts);
    free(brain);
}

void brain_init_brain_region_info(struct brain_region_info *info, const uint32_t region_id, const char *name, const enum brain_region_type type, const uint32_t neuron_count, const uint32_t neuron_count_per_brain_part, const uint8_t inhibitory_percentage) {
    if(NULL == info) return;
    if(NULL == name) return;

    strncpy(info->name, name, sizeof(info->name) - 1);
    info->name[sizeof(info->name)-1] = '\0';

    info->region_type = type;
    info->neuron_count = neuron_count;
    info->neuron_count_per_brain_part = neuron_count_per_brain_part;
    info->inhibitory_percentage = inhibitory_percentage;
    info->region_id = region_id;
}

void brain_init_brain_region_wiring_info(struct brain_region_wiring_info *info, uint32_t src_region_id, uint32_t dest_region_id, uint8_t connectivity_density, uint32_t synaptic_latency_between_regions) {
    if(NULL == info) return;

    info->src_region_id = src_region_id;
    info->dest_region_id = dest_region_id;
    info->connectivity_density = connectivity_density;
    info->synaptic_latency_between_regions = synaptic_latency_between_regions;
}

struct brain_map brain_init_brain_map(struct vector *brain_region_info_list, struct vector *brain_region_wiring_info_list) {
    if(NULL == brain_region_info_list || NULL == brain_region_wiring_info_list) return (struct brain_map) {.brain_region_infos = NULL, .brain_region_wiring_info = NULL};

    return (struct brain_map) {.brain_region_infos = brain_region_info_list, .brain_region_wiring_info = brain_region_wiring_info_list};
}

void brain_start(struct brain_map map) {
    struct brain *brain = brain_create_brain(map);

    brain_delete_brain(brain);
}
