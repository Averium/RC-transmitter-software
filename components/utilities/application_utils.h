#ifndef APPLICATION_UTILS_H
#define APPLICATION_UTILS_H


#include "application_types.h"


#define MS_TO_S 0.001f
#define S_TO_MS 1000.0f
#define US_TO_S 0.000001f
#define S_TO_US 1000000.0f

#define US_TO_MS (MS_TO_S)
#define MS_TO_US (S_TO_MS)

#define BYTES_TO_BITS 8

#define U12_MAX 4095u
#define U16_MAX UINT16_MAX

#define U16_LIMIT_UNCALIBRATED ((uint16_limit){ U16_MAX, 0u })


inline float32 saturate_float32(float32 value, const float32_limit* limit) {
    if (value <= limit->min) { return limit->min; }
    if (value >= limit->max) { return limit->max; }
    return (float32)(value);
}


inline uint32 saturate_uint32(uint32 value, const uint32_limit* limit) {
    if (value <= limit->min) { return limit->min; }
    if (value >= limit->max) { return limit->max; }
    return (uint32)(value);
}


inline uint16 saturate_uint16(uint16 value, const uint16_limit* limit) {
    if (value <= limit->min) { return limit->min; }
    if (value >= limit->max) { return limit->max; }
    return (uint16)(value);
}


inline uint16 map_uint16(uint16 value, uint16_limit from, uint16_limit to) {
    float32 normalized_value = (float32)(value - from.min) / (float32)(from.max - from.min);
    return (uint16)(normalized_value * (float32)(to.max - to.min)) + to.min;
}


inline float32 map_float32(float32 value, float32_limit from, float32_limit to) {
    return (value - from.min) / (from.max - from.min) * (to.max - to.min) + to.min;
}


inline uint16_limit shrink_uint16_limit(uint16_limit limit, uint16 value) {
    return (uint16_limit) { limit.min + value, limit.max - value };
}


#endif