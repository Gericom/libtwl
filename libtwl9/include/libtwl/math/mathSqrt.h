#pragma once

#define REG_SQRTCNT         (*(vu32*)0x040002B0)
#define REG_SQRT_RESULT     (*(vu32*)0x040002B4)
#define REG_SQRT_PARAM_LO   (*(vu32*)0x040002B8)
#define REG_SQRT_PARAM      (*(vu64*)0x040002B8)

#define MATH_SQRTCNT_32BIT  0
#define MATH_SQRTCNT_64BIT  1
#define MATH_SQRTCNT_BUSY   (1 << 15)

#ifdef __cplusplus
extern "C" {
#endif

static inline void math_waitSqrt(void)
{
    while (REG_SQRTCNT & MATH_SQRTCNT_BUSY);
}

static inline void math_sqrt32Async(u32 x)
{
    REG_SQRTCNT = MATH_SQRTCNT_32BIT;
    REG_SQRT_PARAM_LO = x;
}

static inline u32 math_getSqrtResult(void)
{
    return REG_SQRT_RESULT;
}

static inline u32 math_sqrt32(u32 x)
{
    math_sqrt32Async(x);
    math_waitSqrt();
    return REG_SQRT_RESULT;
}

static inline void math_sqrt64Async(u64 x)
{
    REG_SQRTCNT = MATH_SQRTCNT_64BIT;
    REG_SQRT_PARAM = x;
}

static inline u32 math_sqrt64(u64 x)
{
    math_sqrt64Async(x);
    math_waitSqrt();
    return REG_SQRT_RESULT;
}

#ifdef __cplusplus
}
#endif
