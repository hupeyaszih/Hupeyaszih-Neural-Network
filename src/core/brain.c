#include "core/brain.h"
#include <string.h>

struct brain {

};

struct brain *brain_create_brain(struct brain_map brain_map);

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

}
