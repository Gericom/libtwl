#pragma once

#define POWCNT_LCD_ENABLE                  (1 << 0)
#define POWCNT_2D_GRAPHICS_MAIN_ENABLE     (1 << 1)
#define POWCNT_3D_RENDER_ENGINE_ENABLE     (1 << 2)
#define POWCNT_3D_GEOMETRY_ENGINE_ENABLE   (1 << 3)
#define POWCNT_2D_GRAPHICS_SUB_ENABLE      (1 << 9)

#define POWCNT_DISP_SUB_TOP_MAIN_BOTTOM    (0 << 15)
#define POWCNT_DISP_MAIN_TOP_SUB_BOTTOM    (1 << 15)

#define REG_POWCNT                         (*(vu16*)0x04000304)

#ifdef __cplusplus
extern "C" {
#endif

static inline void sys_set2DGraphicsMainPower(bool enabled)
{
    if (enabled)
        REG_POWCNT |= POWCNT_2D_GRAPHICS_MAIN_ENABLE;
    else
        REG_POWCNT &= ~POWCNT_2D_GRAPHICS_MAIN_ENABLE;
}

static inline void sys_set3DRenderEnginePower(bool enabled)
{
    if (enabled)
        REG_POWCNT |= POWCNT_3D_RENDER_ENGINE_ENABLE;
    else
        REG_POWCNT &= ~POWCNT_3D_RENDER_ENGINE_ENABLE;
}

static inline void sys_set3DGeometryEnginePower(bool enabled)
{
    if (enabled)
        REG_POWCNT |= POWCNT_3D_GEOMETRY_ENGINE_ENABLE;
    else
        REG_POWCNT &= ~POWCNT_3D_GEOMETRY_ENGINE_ENABLE;
}

static inline void sys_set2DGraphicsSubPower(bool enabled)
{
    if (enabled)
        REG_POWCNT |= POWCNT_2D_GRAPHICS_SUB_ENABLE;
    else
        REG_POWCNT &= ~POWCNT_2D_GRAPHICS_SUB_ENABLE;
}

static inline void sys_setMainEngineToTopScreen(void)
{
    REG_POWCNT |= POWCNT_DISP_MAIN_TOP_SUB_BOTTOM;
}

static inline void sys_setMainEngineToBottomScreen(void)
{
    REG_POWCNT &= ~POWCNT_DISP_MAIN_TOP_SUB_BOTTOM;
}

static inline void sys_setMainEngineScreen(bool topScreen)
{
    if (topScreen)
        REG_POWCNT |= POWCNT_DISP_MAIN_TOP_SUB_BOTTOM;
    else
        REG_POWCNT &= ~POWCNT_DISP_MAIN_TOP_SUB_BOTTOM;
}

#ifdef __cplusplus
}
#endif
