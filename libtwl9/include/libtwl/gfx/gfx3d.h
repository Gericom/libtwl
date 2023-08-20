#pragma once

#define DISP3DCNT_TEXTURE_MAPPING               (1 << 0)

#define DISP3DCNT_TOON_SHADING                  (0 << 1)
#define DISP3DCNT_HIGHLIGHT_SHADING             (1 << 1)

#define DISP3DCNT_ALPHA_TEST                    (1 << 2)
#define DISP3DCNT_ALPHA_BLENDING                (1 << 3)
#define DISP3DCNT_ANTI_ALIASING                 (1 << 4)
#define DISP3DCNT_EDGE_MARKING                  (1 << 5)

#define DISP3DCNT_FOG_MODE_COLOR_ALPHA          (0 << 6)
#define DISP3DCNT_FOG_MODE_ALPHA                (1 << 6)

#define DISP3DCNT_FOG                           (1 << 7)

#define DISP3DCNT_FOG_SHIFT(x)                  ((x) << 8)

#define DISP3DCNT_COLOR_BUFFER_UNDERFLOW        (1 << 12)

#define DISP3DCNT_POLY_VTX_RAM_OVERFLOW         (1 << 13)

#define DISP3DCNT_CLEAR_IMAGE                   (1 << 14)

#define GXSTAT_TEST_BUSY                        (1 << 0)
#define GXSTAT_BOX_TEST_RESULT                  (1 << 1)

#define GXSTAT_POS_VEC_MTX_STACK_LEVEL_MASK     (0x1F)
#define GXSTAT_POS_VEC_MTX_STACK_LEVEL_SHIFT    (8)

#define GXSTAT_PROJ_MTX_STACK_LEVEL_MASK        (1)
#define GXSTAT_PROJ_MTX_STACK_LEVEL_SHIFT       (13)

#define GXSTAT_MTX_STACK_BUSY                   (1 << 14)
#define GXSTAT_MTX_STACK_ERROR                  (1 << 15)
#define GXSTAT_GEOMETRY_ENGINE_BUSY             (1 << 27)


#define REG_DISP3DCNT                (*(vu16*)0x04000060)

#define REG_RDLINES_COUNT            (*(vu16*)0x04000320)

#define REG_EDGE_COLOR(x)            (((vu32*)0x04000330)[(x)])

#define REG_ALPHA_TEST_REF           (*(vu16*)0x04000340)

#define REG_CLEAR_COLOR              (*(vu32*)0x04000350)
#define REG_CLEAR_DEPTH              (*(vu16*)0x04000354)
#define REG_CLRIMAGE_OFFSET          (*(vu16*)0x04000356)

#define REG_FOG_COLOR                (*(vu32*)0x04000358)
#define REG_FOG_OFFSET               (*(vu16*)0x0400035C)
#define REG_FOG_TABLE(x)             (((vu32*)0x04000360)[(x)])

#define REG_GXSTAT                   (*(vu32*)0x04000600)
#define REG_LISTRAM_COUNT            (*(vu16*)0x04000604)
#define REG_VTXRAM_COUNT             (*(vu16*)0x04000606)

#define REG_DISP_1DOT_DEPTH          (*(vu16*)0x04000610)

#ifdef __cplusplus
extern "C" {
#endif

void gx_init(void);
void gx_reset(void);
void gx_resetMatrixStack(void);
void gx_clearFifo(void);

static inline bool gx_getColorBufferUnderflow(void)
{
    return REG_DISP3DCNT & DISP3DCNT_COLOR_BUFFER_UNDERFLOW;
}

static inline void gx_ackColorBufferUnderflow(void)
{
    REG_DISP3DCNT |= DISP3DCNT_COLOR_BUFFER_UNDERFLOW;
}

static inline bool gx_getPolyVtxRamOverflow(void)
{
    return REG_DISP3DCNT & DISP3DCNT_POLY_VTX_RAM_OVERFLOW;
}

static inline void gx_ackPolyVtxRamOverflow(void)
{
    REG_DISP3DCNT |= DISP3DCNT_POLY_VTX_RAM_OVERFLOW;
}

static inline void gx_setClearImageEnabled(bool enabled)
{
    if (enabled)
        REG_DISP3DCNT |= DISP3DCNT_CLEAR_IMAGE;
    else
        REG_DISP3DCNT &= ~DISP3DCNT_CLEAR_IMAGE;
}

static inline bool gx_isTestBusy(void)
{
    return REG_GXSTAT & GXSTAT_TEST_BUSY;
}

static inline void gx_waitTestBusy(void)
{
    while (gx_isTestBusy());
}

static inline bool gx_getBoxTestResult(void)
{
    return REG_GXSTAT & GXSTAT_BOX_TEST_RESULT;
}

static inline u32 gx_getPositionVectorMtxStackLevel(void)
{
    return (REG_GXSTAT >> GXSTAT_POS_VEC_MTX_STACK_LEVEL_SHIFT) & GXSTAT_POS_VEC_MTX_STACK_LEVEL_MASK;
}

static inline u32 gx_getProjectionMtxStackLevel(void)
{
    return (REG_GXSTAT >> GXSTAT_PROJ_MTX_STACK_LEVEL_SHIFT) & GXSTAT_PROJ_MTX_STACK_LEVEL_MASK;
}

static inline bool gx_isMtxStackBusy(void)
{
    return REG_GXSTAT & GXSTAT_MTX_STACK_BUSY;
}

static inline void gx_waitMtxStackBusy(void)
{
    while (gx_isMtxStackBusy());
}

static inline bool gx_getMtxStackError(void)
{
    return REG_GXSTAT & GXSTAT_MTX_STACK_ERROR;
}

static inline void gx_ackMtxStackError(void)
{
    REG_GXSTAT |= GXSTAT_MTX_STACK_ERROR;
}

static inline bool gx_isGeometryEngineBusy(void)
{
    return REG_GXSTAT & GXSTAT_GEOMETRY_ENGINE_BUSY;
}

static inline void gx_waitGeometryEngineBusy(void)
{
    while (gx_isGeometryEngineBusy());
}

#ifdef __cplusplus
}
#endif
