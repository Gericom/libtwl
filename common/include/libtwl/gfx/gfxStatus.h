#pragma once

#define REG_DISPSTAT                (*(vu16*)0x04000004)
#define REG_VCOUNT                  (*(vu16*)0x04000006)

#define DISPSTAT_IN_VBLANK          (1 << 0)
#define DISPSTAT_IN_HBLANK          (1 << 1)
#define DISPSTAT_VCOUNT_MATCH       (1 << 2)

#define DISPSTAT_VBLANK_IRQ         (1 << 3)
#define DISPSTAT_HBLANK_IRQ         (1 << 4)
#define DISPSTAT_VCOUNT_MATCH_IRQ   (1 << 5)

#ifdef __cplusplus
extern "C" {
#endif

static inline bool gfx_isInVBlank(void)
{
    return REG_DISPSTAT & DISPSTAT_IN_VBLANK;
}

static inline bool gfx_isInHBlank(void)
{
    return REG_DISPSTAT & DISPSTAT_IN_HBLANK;
}

static inline bool gfx_isVCountMatch(void)
{
    return REG_DISPSTAT & DISPSTAT_VCOUNT_MATCH;
}

static inline bool gfx_getVBlankIrqEnabled(void)
{
    return REG_DISPSTAT & DISPSTAT_VBLANK_IRQ;
}

static inline void gfx_setVBlankIrqEnabled(bool enabled)
{
    if (enabled)
        REG_DISPSTAT |= DISPSTAT_VBLANK_IRQ;
    else
        REG_DISPSTAT &= ~DISPSTAT_VBLANK_IRQ;
}

static inline bool gfx_getHBlankIrqEnabled(void)
{
    return REG_DISPSTAT & DISPSTAT_HBLANK_IRQ;
}

static inline void gfx_setHBlankIrqEnabled(bool enabled)
{
    if (enabled)
        REG_DISPSTAT |= DISPSTAT_HBLANK_IRQ;
    else
        REG_DISPSTAT &= ~DISPSTAT_HBLANK_IRQ;
}

static inline bool gfx_getVCountMatchIrqEnabled(void)
{
    return REG_DISPSTAT & DISPSTAT_VCOUNT_MATCH_IRQ;
}

static inline void gfx_setVCountMatchIrqEnabled(bool enabled)
{
    if (enabled)
        REG_DISPSTAT |= DISPSTAT_VCOUNT_MATCH_IRQ;
    else
        REG_DISPSTAT &= ~DISPSTAT_VCOUNT_MATCH_IRQ;
}

static inline u32 gfx_getVCountMatchLine(void)
{
    u32 dispStat = REG_DISPSTAT;
    return (dispStat >> 8) | ((dispStat & 0x80) << 1);
}

static inline void gfx_setVCountMatchLine(u32 line)
{
    REG_DISPSTAT = (REG_DISPSTAT & ~0xFF80) | ((line & 0xFF) << 8) | ((line & 0x100) >> 1);
}

static inline u32 gfx_getVCount(void)
{
    return REG_VCOUNT;
}

static inline void gfx_setVCount(u32 line)
{
    REG_VCOUNT = line;
}

#ifdef __cplusplus
}
#endif