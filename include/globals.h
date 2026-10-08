#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

const uint32_t FLOAT_RESOLUTION = 255; ///< @brief In this project, float is not going to be used. Therefore, floating numbers (for example, 0.0-1.0) represented by integers with scaling by a constant resolution.

#define MAKE_FLOATING_64(x) ((uint64_t) x * FLOAT_RESOLUTION)
#define MAKE_FLOATING_32(x) ((uint32_t) x * FLOAT_RESOLUTION)
#define MAKE_FLOATING_16(x) ((uint16_t) x * FLOAT_RESOLUTION)
#define MAKE_FLOATING_8 (x) ((uint8_t)  x * FLOAT_RESOLUTION) 
///< @attention be careful while using 'MAKE_FLOATING_8' because of the overflow risk!!!

#endif
