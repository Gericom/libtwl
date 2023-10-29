#pragma once

#define GFX_OBJ_MAIN    ((vu16*)0x06400000)
#define GFX_OBJ_SUB     ((vu16*)0x06600000)

#define GFX_OAM_MAIN    ((vu16*)0x07000000)
#define GFX_OAM_SUB     ((vu16*)0x07000400)

#define GFX_OAM_ATTR0_Y(y)              ((y) & 0xFF)
#define GFX_OAM_ATTR0_AFFINE            (1 << 8)
#define GFX_OAM_ATTR0_DOUBLE_AFFINE     (3 << 8)
#define GFX_OAM_ATTR0_HIDDEN            (2 << 8)

#define GFX_OAM_ATTR0_MODE_NORMAL       (0 << 10)
#define GFX_OAM_ATTR0_MODE_TRANSLUCENT  (1 << 10)
#define GFX_OAM_ATTR0_MODE_WINDOW       (2 << 10)
#define GFX_OAM_ATTR0_MODE_BITMAP       (3 << 10)

#define GFX_OAM_ATTR0_MOSAIC            (1 << 12)

#define GFX_OAM_ATTR0_PLTT16            (0 << 13)
#define GFX_OAM_ATTR0_PLTT256           (1 << 13)

#define GFX_OAM_ATTR0_SHAPE_SQUARE      (0 << 14)
#define GFX_OAM_ATTR0_SHAPE_LONG        (1 << 14)
#define GFX_OAM_ATTR0_SHAPE_TALL        (2 << 14)

#define GFX_OAM_ATTR0_SHAPE_8_8         GFX_OAM_ATTR0_SHAPE_SQUARE
#define GFX_OAM_ATTR0_SHAPE_16_16       GFX_OAM_ATTR0_SHAPE_SQUARE
#define GFX_OAM_ATTR0_SHAPE_32_32       GFX_OAM_ATTR0_SHAPE_SQUARE
#define GFX_OAM_ATTR0_SHAPE_64_64       GFX_OAM_ATTR0_SHAPE_SQUARE
#define GFX_OAM_ATTR0_SHAPE_16_8        GFX_OAM_ATTR0_SHAPE_LONG
#define GFX_OAM_ATTR0_SHAPE_32_8        GFX_OAM_ATTR0_SHAPE_LONG
#define GFX_OAM_ATTR0_SHAPE_32_16       GFX_OAM_ATTR0_SHAPE_LONG
#define GFX_OAM_ATTR0_SHAPE_64_32       GFX_OAM_ATTR0_SHAPE_LONG
#define GFX_OAM_ATTR0_SHAPE_8_16        GFX_OAM_ATTR0_SHAPE_TALL
#define GFX_OAM_ATTR0_SHAPE_8_32        GFX_OAM_ATTR0_SHAPE_TALL
#define GFX_OAM_ATTR0_SHAPE_16_32       GFX_OAM_ATTR0_SHAPE_TALL
#define GFX_OAM_ATTR0_SHAPE_32_64       GFX_OAM_ATTR0_SHAPE_TALL

#define GFX_OAM_ATTR1_X(x)              ((x) & 0x1FF)
#define GFX_OAM_ATTR1_MTX(mtx)          (((mtx) & 0x1F) << 9)
#define GFX_OAM_ATTR1_HFLIP             (1 << 12)
#define GFX_OAM_ATTR1_VFLIP             (1 << 13)

#define GFX_OAM_ATTR1_SIZE_0            (0 << 14)
#define GFX_OAM_ATTR1_SIZE_1            (1 << 14)
#define GFX_OAM_ATTR1_SIZE_2            (2 << 14)
#define GFX_OAM_ATTR1_SIZE_3            (3 << 14)

#define GFX_OAM_ATTR1_SIZE_8_8          GFX_OAM_ATTR1_SIZE_0
#define GFX_OAM_ATTR1_SIZE_16_8         GFX_OAM_ATTR1_SIZE_0
#define GFX_OAM_ATTR1_SIZE_8_16         GFX_OAM_ATTR1_SIZE_0
#define GFX_OAM_ATTR1_SIZE_16_16        GFX_OAM_ATTR1_SIZE_1
#define GFX_OAM_ATTR1_SIZE_32_8         GFX_OAM_ATTR1_SIZE_1
#define GFX_OAM_ATTR1_SIZE_8_32         GFX_OAM_ATTR1_SIZE_1
#define GFX_OAM_ATTR1_SIZE_32_32        GFX_OAM_ATTR1_SIZE_2
#define GFX_OAM_ATTR1_SIZE_32_16        GFX_OAM_ATTR1_SIZE_2
#define GFX_OAM_ATTR1_SIZE_16_32        GFX_OAM_ATTR1_SIZE_2
#define GFX_OAM_ATTR1_SIZE_64_64        GFX_OAM_ATTR1_SIZE_3
#define GFX_OAM_ATTR1_SIZE_64_32        GFX_OAM_ATTR1_SIZE_3
#define GFX_OAM_ATTR1_SIZE_32_64        GFX_OAM_ATTR1_SIZE_3

#define GFX_OAM_ATTR2_VRAM_OFFS(offs)   ((offs) & 0x3FF)
#define GFX_OAM_ATTR2_PRIORITY(prio)    (((prio) & 3) << 10)
#define GFX_OAM_ATTR2_PLTT(pltt)        (((pltt) & 0xF) << 12)
#define GFX_OAM_ATTR2_BMP_ALPHA(alpha)  (((alpha) & 0xF) << 12)

typedef struct
{
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 affine;
} gfx_oam_entry_t;

typedef struct
{
    u16 obj0[3];
    s16 pa;
    u16 obj1[3];
    s16 pb;
    u16 obj2[3];
    s16 pc;
    u16 obj3[3];
    s16 pd;
} gfx_oam_mtx_t;

typedef union
{
    gfx_oam_entry_t objs[128];
    gfx_oam_mtx_t mtxs[32];
} gfx_oam_table_t;