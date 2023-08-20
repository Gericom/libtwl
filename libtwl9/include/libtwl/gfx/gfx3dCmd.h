#pragma once
#include "../math/mathVec3.h"

enum
{
    GX_CMD_NOP = 0x00,

    GX_CMD_MTX_MODE = 0x10,
    GX_CMD_MTX_PUSH,
    GX_CMD_MTX_POP,
    GX_CMD_MTX_STORE,
    GX_CMD_MTX_RESTORE,
    GX_CMD_MTX_IDENTITY,
    GX_CMD_MTX_LOAD_44,
    GX_CMD_MTX_LOAD_43,
    GX_CMD_MTX_MULT_44,
    GX_CMD_MTX_MULT_43,
    GX_CMD_MTX_MULT_33,
    GX_CMD_MTX_SCALE,
    GX_CMD_MTX_TRANS,

    GX_CMD_COLOR = 0x20,
    GX_CMD_NORMAL,
    GX_CMD_TEXCOORD,
    GX_CMD_VTX_16,
    GX_CMD_VTX_10,
    GX_CMD_VTX_XY,
    GX_CMD_VTX_XZ,
    GX_CMD_VTX_YZ,
    GX_CMD_VTX_DIFF,
    GX_CMD_POLYGON_ATTR,
    GX_CMD_TEXIMAGE_PARAM,
    GX_CMD_PLTT_BASE,

    GX_CMD_DIF_AMB = 0x30,
    GX_CMD_SPE_EMI,
    GX_CMD_LIGHT_VECTOR,
    GX_CMD_LIGHT_COLOR,
    GX_CMD_SHININESS,

    GX_CMD_BEGIN_VTXS = 0x40,
    GX_CMD_END_VTXS,

    GX_CMD_SWAP_BUFFERS = 0x50,

    GX_CMD_VIEWPORT = 0x60,

    GX_CMD_BOX_TEST = 0x70,
    GX_CMD_POS_TEST,
    GX_CMD_VEC_TEST
};

typedef enum
{
    GX_MTX_MODE_PROJECTION = 0,
    GX_MTX_MODE_POSITION = 1,
    GX_MTX_MODE_POSITION_VECTOR = 2,
    GX_MTX_MODE_TEXTURE = 3
} GxMtxMode;

typedef enum
{
    GX_PRIMITIVE_TRIANGLE = 0,
    GX_PRIMITIVE_QUAD = 1,
    GX_PRIMITIVE_TRIANGLE_STRIP = 2,
    GX_PRIMITIVE_QUAD_STRIP = 3
} GxPrimitiveType;

typedef enum
{
    GX_XLU_SORT_AUTO = 0,
    GX_XLU_SORT_MANUAL = 1
} GxXluSortMode;

typedef enum
{
    GX_DEPTH_MODE_Z = 0,
    GX_DEPTH_MODE_W = 1
} GxDepthMode;

typedef enum
{
    GX_TEXGEN_NONE = 0,
    GX_TEXGEN_TEXCOORD = 1,
    GX_TEXGEN_NORMAL = 2,
    GX_TEXGEN_VERTEX = 3
} GxTexGen;

typedef enum
{
    GX_TEXFMT_NONE = 0,
    GX_TEXFMT_A3I5 = 1,
    GX_TEXFMT_PLTT4 = 2,
    GX_TEXFMT_PLTT16 = 3,
    GX_TEXFMT_PLTT256 = 4,
    GX_TEXFMT_COMP4x4 = 5,
    GX_TEXFMT_A5I3 = 6,
    GX_TEXFMT_DIRECT = 7
} GxTexFormat;

typedef enum
{
    GX_TEXSIZE_8 = 0,
    GX_TEXSIZE_16 = 1,
    GX_TEXSIZE_32 = 2,
    GX_TEXSIZE_64 = 3,
    GX_TEXSIZE_128 = 4,
    GX_TEXSIZE_256 = 5,
    GX_TEXSIZE_512 = 6,
    GX_TEXSIZE_1024 = 7
} GxTexSize;

typedef enum
{
    GX_LIGHTMASK_NONE = 0b0000,
    GX_LIGHTMASK_0 = 0b0001,
    GX_LIGHTMASK_1 = 0b0010,
    GX_LIGHTMASK_01 = 0b0011,
    GX_LIGHTMASK_2 = 0b0100,
    GX_LIGHTMASK_02 = 0b0101,
    GX_LIGHTMASK_12 = 0b0110,
    GX_LIGHTMASK_012 = 0b0111,
    GX_LIGHTMASK_3 = 0b1000,
    GX_LIGHTMASK_03 = 0b1001,
    GX_LIGHTMASK_13 = 0b1010,
    GX_LIGHTMASK_013 = 0b1011,
    GX_LIGHTMASK_23 = 0b1100,
    GX_LIGHTMASK_023 = 0b1101,
    GX_LIGHTMASK_123 = 0b1110,
    GX_LIGHTMASK_0123 = 0b1111
} GxLightMask;

typedef enum
{
    GX_POLYGON_MODE_MODULATE = 0,
    GX_POLYGON_MODE_DECAL = 1,
    GX_POLYGON_MODE_TOON_HIGHLIGHT = 2,
    GX_POLYGON_MODE_SHADOW = 3
} GxPolygonMode;

typedef enum
{
    GX_DISPLAY_MODE_NONE = 0,
    GX_DISPLAY_MODE_BACK = 1,
    GX_DISPLAY_MODE_FRONT = 2,
    GX_DISPLAY_MODE_BOTH = 3
} GxDisplayMode;

typedef enum
{
    GX_DEPTH_FUNC_LESS = 0,
    GX_DEPTH_FUNC_EQUAL = 1
} GxDepthFunc;

#define GX_CMD_PACK(a,b,c,d)    ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

#define REG_GXFIFO              (*(vu32*)0x04000400)

#define REG_GX_MTX_MODE         (*(vu32*)0x04000440)
#define REG_GX_MTX_PUSH         (*(vu32*)0x04000444)
#define REG_GX_MTX_POP          (*(vu32*)0x04000448)
#define REG_GX_MTX_STORE        (*(vu32*)0x0400044C)
#define REG_GX_MTX_RESTORE      (*(vu32*)0x04000450)
#define REG_GX_MTX_IDENTITY     (*(vu32*)0x04000454)
#define REG_GX_MTX_LOAD_44      (*(vu32*)0x04000458)
#define REG_GX_MTX_LOAD_43      (*(vu32*)0x0400045C)
#define REG_GX_MTX_MULT_44      (*(vu32*)0x04000460)
#define REG_GX_MTX_MULT_43      (*(vu32*)0x04000464)
#define REG_GX_MTX_MULT_33      (*(vu32*)0x04000468)
#define REG_GX_MTX_SCALE        (*(vu32*)0x0400046C)
#define REG_GX_MTX_TRANS        (*(vu32*)0x04000470)

#define REG_GX_COLOR            (*(vu32*)0x04000480)
#define REG_GX_NORMAL           (*(vu32*)0x04000484)
#define REG_GX_TEXCOORD         (*(vu32*)0x04000488)
#define REG_GX_VTX_16           (*(vu32*)0x0400048C)
#define REG_GX_VTX_10           (*(vu32*)0x04000490)
#define REG_GX_VTX_XY           (*(vu32*)0x04000494)
#define REG_GX_VTX_XZ           (*(vu32*)0x04000498)
#define REG_GX_VTX_YZ           (*(vu32*)0x0400049C)
#define REG_GX_VTX_DIFF         (*(vu32*)0x040004A0)
#define REG_GX_POLYGON_ATTR     (*(vu32*)0x040004A4)
#define REG_GX_TEXIMAGE_PARAM   (*(vu32*)0x040004A8)
#define REG_GX_TEXPLTT_BASE     (*(vu32*)0x040004AC)

#define REG_GX_DIF_AMB          (*(vu32*)0x040004C0)
#define REG_GX_SPE_EMI          (*(vu32*)0x040004C4)
#define REG_GX_LIGHT_VECTOR     (*(vu32*)0x040004C8)
#define REG_GX_LIGHT_COLOR      (*(vu32*)0x040004CC)
#define REG_GX_SHININESS        (*(vu32*)0x040004D0)

#define REG_GX_BEGIN_VTXS       (*(vu32*)0x04000500)
#define REG_GX_END_VTXS         (*(vu32*)0x04000504)

#define REG_GX_SWAP_BUFFERS     (*(vu32*)0x04000540)

#define REG_GX_VIEWPORT         (*(vu32*)0x04000580)

#define REG_GX_BOX_TEST         (*(vu32*)0x040005C0)
#define REG_GX_POS_TEST         (*(vu32*)0x040005C4)
#define REG_GX_VEC_TEST         (*(vu32*)0x040005C8)

#define GX_VTX_PACK(a,b)    ((u16)(a) | ((b) << 16))

static inline void gx_mtxMode(GxMtxMode mode)
{
    REG_GX_MTX_MODE = mode;
}

static inline void gx_mtxPush(void)
{
    REG_GX_MTX_PUSH = 0;
}

static inline void gx_mtxPop(int count)
{
    REG_GX_MTX_POP = count;
}

static inline void gx_mtxStore(u32 id)
{
    REG_GX_MTX_STORE = id;
}

static inline void gx_mtxRestore(u32 id)
{
    REG_GX_MTX_RESTORE = id;
}

static inline void gx_mtxIdentity(void)
{
    REG_GX_MTX_IDENTITY = 0;
}

static inline void gx_mtxScale(fx32 x, fx32 y, fx32 z)
{
    REG_GX_MTX_SCALE = x;
    REG_GX_MTX_SCALE = y;
    REG_GX_MTX_SCALE = z;
}

static inline void gx_mtxScaleVec(const vec3_t* scale)
{
    REG_GX_MTX_SCALE = scale->x;
    REG_GX_MTX_SCALE = scale->y;
    REG_GX_MTX_SCALE = scale->z;
}

static inline void gx_mtxTranslate(fx32 x, fx32 y, fx32 z)
{
    REG_GX_MTX_TRANS = x;
    REG_GX_MTX_TRANS = y;
    REG_GX_MTX_TRANS = z;
}

static inline void gx_mtxTranslateVec(const vec3_t* translation)
{
    REG_GX_MTX_TRANS = translation->x;
    REG_GX_MTX_TRANS = translation->y;
    REG_GX_MTX_TRANS = translation->z;
}

static inline void gx_polygonAttr(GxLightMask lightMask, GxPolygonMode polygonMode,
    GxDisplayMode displayMode, bool xluDepthUpdate, bool clipFarPlane, bool render1Dot,
    GxDepthFunc depthFunc, bool fogEnable, u32 alpha, u32 polygonId)
{
    REG_GX_POLYGON_ATTR
        = lightMask
        | (polygonMode << 4)
        | (displayMode << 6)
        | (xluDepthUpdate << 11)
        | (clipFarPlane << 12)
        | (render1Dot << 13)
        | (depthFunc << 14)
        | (fogEnable << 15)
        | ((alpha & 31) << 16)
        | ((polygonId & 63) << 24);
}

static inline void gx_texImageParam(u16 address, bool repeatS, bool repeatT,
    bool flipS, bool flipT, GxTexSize sizeS, GxTexSize sizeT, GxTexFormat format,
    bool color0Transparent, GxTexGen texGen)
{
    REG_GX_TEXIMAGE_PARAM
        = address
        | (repeatS << 16)
        | (repeatT << 17)
        | (flipS << 18)
        | (flipT << 19)
        | (sizeS << 20)
        | (sizeT << 23)
        | (format << 26)
        | (color0Transparent << 29)
        | (texGen << 30);
}

static inline void gx_texPlttBase(u16 address)
{
    REG_GX_TEXPLTT_BASE = address;
}

static inline void gx_color(u32 color)
{
    REG_GX_COLOR = color;
}

static inline void gx_texCoord(s16 s, s16 t)
{
    REG_GX_TEXCOORD = (t << 16) | (u16)s;
}

static inline void gx_vtx16(fx16 x, fx16 y, fx16 z)
{
    REG_GX_VTX_16 = GX_VTX_PACK(x, y);
    REG_GX_VTX_16 = z;
}

static inline void gx_vtx10(int x, int y, int z)
{
    REG_GX_VTX_10 = (x & 0x3FF) | ((y & 0x3FF) << 10) | (z << 20);
}

static inline void gx_vtxXY(fx16 x, fx16 y)
{
    REG_GX_VTX_XY = GX_VTX_PACK(x, y);
}

static inline void gx_vtxXZ(fx16 x, fx16 z)
{
    REG_GX_VTX_XZ = GX_VTX_PACK(x, z);
}

static inline void gx_vtxYZ(fx16 y, fx16 z)
{
    REG_GX_VTX_YZ = GX_VTX_PACK(y, z);
}

static inline void gx_vtxDiff(int x, int y, int z)
{
    REG_GX_VTX_10 = (x & 0x3FF) | ((y & 0x3FF) << 10) | (z << 20);
}

static inline void gx_beginVtxs(GxPrimitiveType type)
{
    REG_GX_BEGIN_VTXS = type;
}

static inline void gx_endVtxs(void)
{
    REG_GX_END_VTXS = 0;
}

static inline void gx_swapBuffers(GxXluSortMode xluSortMode, GxDepthMode depthMode)
{
    REG_GX_SWAP_BUFFERS = xluSortMode | (depthMode << 1);
}

static inline void gx_viewport(u8 x1, u8 y1, u8 x2, u8 y2)
{
    REG_GX_VIEWPORT = x1 | (y1 << 8) | (x2 << 16) | (y2 << 24);
}
