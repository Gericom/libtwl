#include <nds.h>
#include "libtwl/gfx/gfx3dCmd.h"
#include "libtwl/sys/sysPower.h"
#include "libtwl/gfx/gfx3d.h"

void gx_init(void)
{
    sys_set3DGeometryEnginePower(true);
    sys_set3DRenderEnginePower(true);

    gx_clearFifo();
    gx_endVtxs();

    gx_waitGeometryEngineBusy();

    REG_DISP3DCNT = DISP3DCNT_ANTI_ALIASING | DISP3DCNT_ALPHA_BLENDING | DISP3DCNT_TEXTURE_MAPPING;
    REG_GXSTAT = 0;

    gx_reset();

    REG_CLEAR_COLOR = 0;
    REG_CLEAR_DEPTH = 0x7FFF;
    REG_CLRIMAGE_OFFSET = 0;
    REG_GX_TEXIMAGE_PARAM = 0;

    gx_mtxMode(GX_MTX_MODE_PROJECTION);
    gx_mtxIdentity();
    gx_mtxMode(GX_MTX_MODE_TEXTURE);
    gx_mtxIdentity();
    gx_mtxMode(GX_MTX_MODE_POSITION_VECTOR);
    gx_mtxIdentity();
}

void gx_reset(void)
{
    gx_waitGeometryEngineBusy();
    gx_ackColorBufferUnderflow();
    gx_ackPolyVtxRamOverflow();
    gx_resetMatrixStack();
}

void gx_resetMatrixStack(void)
{
    gx_ackMtxStackError();
    gx_waitMtxStackBusy();
    u32 projectionStackLevel = gx_getProjectionMtxStackLevel();
    u32 positionVectorStackLevel = gx_getPositionVectorMtxStackLevel();
    gx_mtxMode(GX_MTX_MODE_PROJECTION);
    if (projectionStackLevel)
        gx_mtxPop(projectionStackLevel);
    gx_mtxMode(GX_MTX_MODE_POSITION_VECTOR);
    if (positionVectorStackLevel)
        gx_mtxPop(positionVectorStackLevel);
}

void gx_clearFifo(void)
{
    for (u32 i = 0; i < 128; i++)
        REG_GXFIFO = 0;

    gx_waitGeometryEngineBusy();
}
