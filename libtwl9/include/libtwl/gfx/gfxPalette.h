#pragma once

#define GFX_PLTT_BG_MAIN    ((vu16*)0x05000000)
#define GFX_PLTT_OBJ_MAIN   ((vu16*)0x05000200)

#define GFX_PLTT_BG_SUB     ((vu16*)0x05000400)
#define GFX_PLTT_OBJ_SUB    ((vu16*)0x05000600)

typedef struct
{
    u16 r : 5;
    u16 g : 5; //g5-g1
    u16 b : 5;
    u16 g0 : 1;
} gfx_pltt_color_t;