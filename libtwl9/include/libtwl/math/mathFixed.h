#pragma once

typedef s16 fx16;

#define FX16_SHIFT  12
#define FX16_ONE    (1 << FX16_SHIFT)

typedef s32 fx32;

#define FX32_SHIFT  12
#define FX32_ONE    (1 << FX32_SHIFT)

static inline fx32 math_mulFx32(fx32 x, fx32 y)
{
    return (((s64)x * y) + 0x800) >> FX32_SHIFT;
}
