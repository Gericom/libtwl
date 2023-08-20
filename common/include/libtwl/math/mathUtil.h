#pragma once

#ifdef __cplusplus
extern "C" {
#endif

static inline int math_abs(int x)
{
    return x >= 0 ? x : -x;
}

static inline int math_min(int x, int y)
{
    return x < y ? x : y;
}

static inline int math_max(int x, int y)
{
    return x > y ? x : y;
}

static inline u32 math_clz(u32 x)
{
    return __builtin_clz(x);
}

static inline int math_ctz(u32 x)
{
    if (!x)
        return 32;
    return 31 - __builtin_clz(x & -x);
}

static inline int math_ilog2(u32 x)
{
    return 31 - __builtin_clz(x);
}

#ifdef __cplusplus
}
#endif
