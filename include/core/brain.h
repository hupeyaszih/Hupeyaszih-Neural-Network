#ifndef BRAIN_H
#define BRAIN_H

#include "utils/vector.h"
#include <stdint.h>

enum brain_region_type {
    BRAIN_REGION_TYPE_DEFAULT,
    BRAIN_REGION_TYPE_GABAERGIC,
    BRAIN_REGION_TYPE_DOPAMINERGIC,
    BRAIN_REGION_TYPE_MOTOR
};

struct brain_region_info {
    uint32_t region_id;
    char name[32];
    enum brain_region_type region_type;

    uint32_t neuron_count;
    uint32_t neuron_count_per_brain_part; ///< @detail In fact, Brain Parts are just blocks that equally represent an area of the brain region. They hold neuromodulators (such as dopamine count) etc.
    uint8_t inhibitory_percentage;
};

struct brain_region_wiring_info {
    uint32_t src_region_id;
    uint32_t dest_region_id;

    uint8_t connectivity_density; ///< @brief between 0-100
    uint32_t synaptic_latency_between_regions;
};

struct brain_map {
    struct vector *brain_region_infos;
    struct vector *brain_region_wiring_info;
};

struct neurons_data;
struct synapses_data;
struct brain_part;
struct brain;

struct brain *brain_create_brain(struct brain_map brain_map);
void brain_delete_brain(struct brain *brain);

void brain_init_brain_region_info(struct brain_region_info *info, const uint32_t region_id, const char *name, const enum brain_region_type type, const uint32_t neuron_count, const uint32_t neuron_count_per_brain_part, const uint8_t inhibitory_percentage);
void brain_init_brain_region_wiring_info(struct brain_region_wiring_info *info, uint32_t src_region_id, uint32_t dest_region_id, uint8_t connectivity_density, uint32_t synaptic_latency_between_regions);
struct brain_map brain_init_brain_map(struct vector *brain_region_info_list, struct vector *brain_region_wiring_info_list);

void brain_start(struct brain_map map); ///< @brief Main entry point of the brain.
#endif
