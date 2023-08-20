#pragma once
#include "mathFixed.h"
#include "mathSqrt.h"

typedef struct
{
    fx32 x, y, z;
} vec3_t;

static inline void math_vecSet(vec3_t* dst, fx32 x, fx32 y, fx32 z)
{
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

static inline void math_vecAdd(vec3_t* dst, const vec3_t* a, const vec3_t* b)
{
    dst->x = a->x + b->x;
    dst->y = a->y + b->y;
    dst->z = a->z + b->z;
}

static inline void math_vecSub(vec3_t* dst, const vec3_t* a, const vec3_t* b)
{
    dst->x = a->x - b->x;
    dst->y = a->y - b->y;
    dst->z = a->z - b->z;
}

static inline void math_vecMul(vec3_t* dst, const vec3_t* a, fx32 b)
{
    dst->x = math_mulFx32(a->x, b);
    dst->y = math_mulFx32(a->y, b);
    dst->z = math_mulFx32(a->z, b);
}

static inline fx32 math_vecDot(const vec3_t* a, const vec3_t* b)
{
    return ((s64)a->x * b->x + (s64)a->y * b->y + (s64)a->z * b->z + 0x800) >> FX32_SHIFT;
}

static inline s64 math_vecMagSq64(const vec3_t* vec)
{
    return (s64)vec->x * vec->x + (s64)vec->y * vec->y + (s64)vec->z * vec->z;
}

static inline s64 math_vecMag(const vec3_t* vec)
{
    return math_sqrt64(math_vecMagSq64(vec));
}

