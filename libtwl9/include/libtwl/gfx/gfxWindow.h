#pragma once

#define REG_WIN0H               (*(vu16*)0x04000040)
#define REG_WIN1H               (*(vu16*)0x04000042)
#define REG_WIN0V               (*(vu16*)0x04000044)
#define REG_WIN1V               (*(vu16*)0x04000046)
#define REG_WININ               (*(vu16*)0x04000048)
#define REG_WINOUT              (*(vu16*)0x0400004A)

#define REG_WIN0H_SUB           (*(vu16*)0x04001040)
#define REG_WIN1H_SUB           (*(vu16*)0x04001042)
#define REG_WIN0V_SUB           (*(vu16*)0x04001044)
#define REG_WIN1V_SUB           (*(vu16*)0x04001046)
#define REG_WININ_SUB           (*(vu16*)0x04001048)
#define REG_WINOUT_SUB          (*(vu16*)0x0400104A)

#ifdef __cplusplus
extern "C" {
#endif

static inline void gfx_setWindow0(u8 x0, u8 y0, u8 x1, u8 y1)
{
    REG_WIN0H = (x0 << 8) | x1;
    REG_WIN0V = (y0 << 8) | y1;
}

static inline void gfx_setWindow1(u8 x0, u8 y0, u8 x1, u8 y1)
{
    REG_WIN1H = (x0 << 8) | x1;
    REG_WIN1V = (y0 << 8) | y1;
}

static inline void gfx_setSubWindow0(u8 x0, u8 y0, u8 x1, u8 y1)
{
    REG_WIN0H_SUB = (x0 << 8) | x1;
    REG_WIN0V_SUB = (y0 << 8) | y1;
}

static inline void gfx_setSubWindow1(u8 x0, u8 y0, u8 x1, u8 y1)
{
    REG_WIN1H_SUB = (x0 << 8) | x1;
    REG_WIN1V_SUB = (y0 << 8) | y1;
}

#ifdef __cplusplus
}
#endif
