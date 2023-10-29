#pragma once

#define REG_BG0CNT      (*(vu16*)0x04000008)
#define REG_BG1CNT      (*(vu16*)0x0400000A)
#define REG_BG2CNT      (*(vu16*)0x0400000C)
#define REG_BG3CNT      (*(vu16*)0x0400000E)
#define REG_BG0HOFS     (*(vu16*)0x04000010)
#define REG_BG0VOFS     (*(vu16*)0x04000012)
#define REG_BG1HOFS     (*(vu16*)0x04000014)
#define REG_BG1VOFS     (*(vu16*)0x04000016)
#define REG_BG2HOFS     (*(vu16*)0x04000018)
#define REG_BG2VOFS     (*(vu16*)0x0400001A)
#define REG_BG3HOFS     (*(vu16*)0x0400001C)
#define REG_BG3VOFS     (*(vu16*)0x0400001E)
#define REG_BG2PA       (*(vs16*)0x04000020)
#define REG_BG2PB       (*(vs16*)0x04000022)
#define REG_BG2PC       (*(vs16*)0x04000024)
#define REG_BG2PD       (*(vs16*)0x04000026)
#define REG_BG2X        (*(vs32*)0x04000028)
#define REG_BG2Y        (*(vs32*)0x0400002C)
#define REG_BG3PA       (*(vs16*)0x04000030)
#define REG_BG3PB       (*(vs16*)0x04000032)
#define REG_BG3PC       (*(vs16*)0x04000034)
#define REG_BG3PD       (*(vs16*)0x04000036)
#define REG_BG3X        (*(vs32*)0x04000038)
#define REG_BG3Y        (*(vs32*)0x0400003C)

#define REG_BG0CNT_SUB  (*(vu16*)0x04001008)
#define REG_BG1CNT_SUB  (*(vu16*)0x0400100A)
#define REG_BG2CNT_SUB  (*(vu16*)0x0400100C)
#define REG_BG3CNT_SUB  (*(vu16*)0x0400100E)
#define REG_BG0HOFS_SUB (*(vu16*)0x04001010)
#define REG_BG0VOFS_SUB (*(vu16*)0x04001012)
#define REG_BG1HOFS_SUB (*(vu16*)0x04001014)
#define REG_BG1VOFS_SUB (*(vu16*)0x04001016)
#define REG_BG2HOFS_SUB (*(vu16*)0x04001018)
#define REG_BG2VOFS_SUB (*(vu16*)0x0400101A)
#define REG_BG3HOFS_SUB (*(vu16*)0x0400101C)
#define REG_BG3VOFS_SUB (*(vu16*)0x0400101E)
#define REG_BG2PA_SUB   (*(vs16*)0x04001020)
#define REG_BG2PB_SUB   (*(vs16*)0x04001022)
#define REG_BG2PC_SUB   (*(vs16*)0x04001024)
#define REG_BG2PD_SUB   (*(vs16*)0x04001026)
#define REG_BG2X_SUB    (*(vs32*)0x04001028)
#define REG_BG2Y_SUB    (*(vs32*)0x0400102C)
#define REG_BG3PA_SUB   (*(vs16*)0x04001030)
#define REG_BG3PB_SUB   (*(vs16*)0x04001032)
#define REG_BG3PC_SUB   (*(vs16*)0x04001034)
#define REG_BG3PD_SUB   (*(vs16*)0x04001036)
#define REG_BG3X_SUB    (*(vs32*)0x04001038)
#define REG_BG3Y_SUB    (*(vs32*)0x0400103C)

#define GFX_BG_MAIN     ((vu16*)0x06000000)
#define GFX_BG_SUB      ((vu16*)0x06200000)

#ifdef __cplusplus
extern "C" {
#endif

static inline void gfx_setBg2Affine(s16 pa, s16 pb, s16 pc, s16 pd, int x, int y)
{
    REG_BG2PA = pa;
    REG_BG2PB = pb;
    REG_BG2PC = pc;
    REG_BG2PD = pd;
    REG_BG2X = x;
    REG_BG2Y = y;
}

static inline void gfx_setBg3Affine(s16 pa, s16 pb, s16 pc, s16 pd, int x, int y)
{
    REG_BG3PA = pa;
    REG_BG3PB = pb;
    REG_BG3PC = pc;
    REG_BG3PD = pd;
    REG_BG3X = x;
    REG_BG3Y = y;
}

static inline void gfx_setSubBg2Affine(s16 pa, s16 pb, s16 pc, s16 pd, int x, int y)
{
    REG_BG2PA_SUB = pa;
    REG_BG2PB_SUB = pb;
    REG_BG2PC_SUB = pc;
    REG_BG2PD_SUB = pd;
    REG_BG2X_SUB = x;
    REG_BG2Y_SUB = y;
}

static inline void gfx_setSubBg3Affine(s16 pa, s16 pb, s16 pc, s16 pd, int x, int y)
{
    REG_BG3PA_SUB = pa;
    REG_BG3PB_SUB = pb;
    REG_BG3PC_SUB = pc;
    REG_BG3PD_SUB = pd;
    REG_BG3X_SUB = x;
    REG_BG3Y_SUB = y;
}

#ifdef __cplusplus
}
#endif
