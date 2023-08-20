#pragma once

#define REG_DIVCNT              (*(vu32*)0x04000280)
#define REG_DIV_NUMER_LO        (*(vs32*)0x04000290)
#define REG_DIV_NUMER           (*(vs64*)0x04000290)
#define REG_DIV_DENOM_LO        (*(vs32*)0x04000298)
#define REG_DIV_DENOM           (*(vs64*)0x04000298)
#define REG_DIV_RESULT_LO       (*(vs32*)0x040002A0)
#define REG_DIV_RESULT          (*(vs64*)0x040002A0)
#define REG_DIVREM_RESULT_LO    (*(vs32*)0x040002A8)
#define REG_DIVREM_RESULT       (*(vs64*)0x040002A8)

#define MATH_DIVCNT_32_32           0
#define MATH_DIVCNT_64_32           1
#define MATH_DIVCNT_64_64           2
#define MATH_DIVCNT_DIV_BY_ZERO     (1 << 14)
#define MATH_DIVCNT_BUSY            (1 << 15)

#ifdef __cplusplus
extern "C" {
#endif

static inline void math_waitDiv(void)
{
    while (REG_DIVCNT & MATH_DIVCNT_BUSY);
}

static inline void math_div32Async(s32 x, s32 y)
{
    REG_DIVCNT = MATH_DIVCNT_32_32;
    REG_DIV_NUMER_LO = x;
    REG_DIV_DENOM_LO = y;
}

static inline s32 math_getDiv32Result(void)
{
    return REG_DIV_RESULT_LO;
}

static inline s32 math_getRem32Result(void)
{
    return REG_DIVREM_RESULT_LO;
}

static inline s32 math_div32(s32 x, s32 y)
{
    math_div32Async(x, y);
    math_waitDiv();
    return REG_DIV_RESULT_LO;
}

static inline s32 math_rem32(s32 x, s32 y)
{
    math_div32Async(x, y);
    math_waitDiv();
    return REG_DIVREM_RESULT_LO;
}

static inline s32 math_divRem32(s32 x, s32 y, s32* rem)
{
    math_div32Async(x, y);
    math_waitDiv();
    *rem = REG_DIVREM_RESULT_LO;
    return REG_DIV_RESULT_LO;
}

static inline void math_div6432Async(s64 x, s32 y)
{
    REG_DIVCNT = MATH_DIVCNT_64_32;
    REG_DIV_NUMER = x;
    REG_DIV_DENOM_LO = y;
}

static inline s64 math_getDiv6432Result(void)
{
    return REG_DIV_RESULT;
}

static inline s32 math_getRem6432Result(void)
{
    return REG_DIVREM_RESULT_LO;
}

static inline s64 math_div6432(s64 x, s32 y)
{
    math_div6432Async(x, y);
    math_waitDiv();
    return REG_DIV_RESULT;
}

static inline s32 math_rem6432(s64 x, s32 y)
{
    math_div6432Async(x, y);
    math_waitDiv();
    return REG_DIVREM_RESULT_LO;
}

static inline s64 math_divRem6432(s64 x, s32 y, s32* rem)
{
    math_div6432Async(x, y);
    math_waitDiv();
    *rem = REG_DIVREM_RESULT_LO;
    return REG_DIV_RESULT;
}

static inline void math_div64Async(s64 x, s64 y)
{
    REG_DIVCNT = MATH_DIVCNT_64_64;
    REG_DIV_NUMER = x;
    REG_DIV_DENOM = y;
}

static inline s64 math_getDiv64Result(void)
{
    return REG_DIV_RESULT;
}

static inline s64 math_getRem64Result(void)
{
    return REG_DIVREM_RESULT;
}

static inline s64 math_div64(s64 x, s64 y)
{
    math_div64Async(x, y);
    math_waitDiv();
    return REG_DIV_RESULT;
}

static inline s64 math_rem64(s64 x, s64 y)
{
    math_div64Async(x, y);
    math_waitDiv();
    return REG_DIVREM_RESULT;
}

static inline s64 math_divRem64(s64 x, s64 y, s64* rem)
{
    math_div64Async(x, y);
    math_waitDiv();
    *rem = REG_DIVREM_RESULT;
    return REG_DIV_RESULT;
}

#ifdef __cplusplus
}
#endif
