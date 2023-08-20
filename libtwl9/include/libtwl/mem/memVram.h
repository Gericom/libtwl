#pragma once

typedef enum
{
    MEM_VRAM_AB_NONE = 0,
    MEM_VRAM_AB_LCDC = 0x80,
    MEM_VRAM_AB_MAIN_BG_00000 = 0x81,
    MEM_VRAM_AB_MAIN_BG_20000 = 0x89,
    MEM_VRAM_AB_MAIN_BG_40000 = 0x91,
    MEM_VRAM_AB_MAIN_BG_60000 = 0x99,
    MEM_VRAM_AB_MAIN_OBJ_00000 = 0x82,
    MEM_VRAM_AB_MAIN_OBJ_20000 = 0x8A,
    MEM_VRAM_AB_TEX_SLOT_0 = 0x83,
    MEM_VRAM_AB_TEX_SLOT_1 = 0x8B,
    MEM_VRAM_AB_TEX_SLOT_2 = 0x93,
    MEM_VRAM_AB_TEX_SLOT_3 = 0x9B
} MemVramABMapping;

typedef enum
{
    MEM_VRAM_C_NONE = 0,
    MEM_VRAM_C_LCDC = 0x80,
    MEM_VRAM_C_MAIN_BG_00000 = 0x81,
    MEM_VRAM_C_MAIN_BG_20000 = 0x89,
    MEM_VRAM_C_MAIN_BG_40000 = 0x91,
    MEM_VRAM_C_MAIN_BG_60000 = 0x99,
    MEM_VRAM_C_ARM7_00000 = 0x82,
    MEM_VRAM_C_ARM7_20000 = 0x8A,
    MEM_VRAM_C_TEX_SLOT_0 = 0x83,
    MEM_VRAM_C_TEX_SLOT_1 = 0x8B,
    MEM_VRAM_C_TEX_SLOT_2 = 0x93,
    MEM_VRAM_C_TEX_SLOT_3 = 0x9B,
    MEM_VRAM_C_SUB_BG_00000 = 0x84
} MemVramCMapping;

typedef enum
{
    MEM_VRAM_D_NONE = 0,
    MEM_VRAM_D_LCDC = 0x80,
    MEM_VRAM_D_MAIN_BG_00000 = 0x81,
    MEM_VRAM_D_MAIN_BG_20000 = 0x89,
    MEM_VRAM_D_MAIN_BG_40000 = 0x91,
    MEM_VRAM_D_MAIN_BG_60000 = 0x99,
    MEM_VRAM_D_ARM7_00000 = 0x82,
    MEM_VRAM_D_ARM7_20000 = 0x8A,
    MEM_VRAM_D_TEX_SLOT_0 = 0x83,
    MEM_VRAM_D_TEX_SLOT_1 = 0x8B,
    MEM_VRAM_D_TEX_SLOT_2 = 0x93,
    MEM_VRAM_D_TEX_SLOT_3 = 0x9B,
    MEM_VRAM_D_SUB_OBJ_00000 = 0x84
} MemVramDMapping;

typedef enum
{
    MEM_VRAM_E_NONE = 0,
    MEM_VRAM_E_LCDC = 0x80,
    MEM_VRAM_E_MAIN_BG_00000 = 0x81,
    MEM_VRAM_E_MAIN_OBJ_00000 = 0x82,
    MEM_VRAM_E_TEX_PLTT_SLOT_0123 = 0x83,
    MEM_VRAM_E_MAIN_BG_EXT_PLTT_SLOT_0123 = 0x84
} MemVramEMapping;

typedef enum
{
    MEM_VRAM_FG_NONE = 0,
    MEM_VRAM_FG_LCDC = 0x80,
    MEM_VRAM_FG_MAIN_BG_00000 = 0x81,
    MEM_VRAM_FG_MAIN_BG_04000 = 0x89,
    MEM_VRAM_FG_MAIN_BG_10000 = 0x91,
    MEM_VRAM_FG_MAIN_BG_14000 = 0x99,
    MEM_VRAM_FG_MAIN_OBJ_00000 = 0x82,
    MEM_VRAM_FG_MAIN_OBJ_04000 = 0x8A,
    MEM_VRAM_FG_MAIN_OBJ_10000 = 0x92,
    MEM_VRAM_FG_MAIN_OBJ_14000 = 0x9A,
    MEM_VRAM_FG_TEX_PLTT_SLOT_0 = 0x83,
    MEM_VRAM_FG_TEX_PLTT_SLOT_1 = 0x8B,
    MEM_VRAM_FG_TEX_PLTT_SLOT_4 = 0x93,
    MEM_VRAM_FG_TEX_PLTT_SLOT_5 = 0x9B,
    MEM_VRAM_FG_MAIN_BG_EXT_PLTT_SLOT_01 = 0x84,
    MEM_VRAM_FG_MAIN_BG_EXT_PLTT_SLOT_23 = 0x8C,
    MEM_VRAM_FG_MAIN_OBJ_EXT_PLTT = 0x85
} MemVramFGMapping;

typedef enum
{
    MEM_VRAM_H_NONE = 0,
    MEM_VRAM_H_LCDC = 0x80,
    MEM_VRAM_H_SUB_BG_00000 = 0x81,
    MEM_VRAM_H_SUB_BG_EXT_PLTT_SLOT_0123 = 0x82
} MemVramHMapping;

typedef enum
{
    MEM_VRAM_I_NONE = 0,
    MEM_VRAM_I_LCDC = 0x80,
    MEM_VRAM_I_SUB_BG_08000 = 0x81,
    MEM_VRAM_I_SUB_OBJ_00000 = 0x82,
    MEM_VRAM_I_SUB_OBJ_EXT_PLTT = 0x83
} MemVramIMapping;

#define REG_VRAMCNT_A   (*(vu8*)0x04000240)
#define REG_VRAMCNT_B   (*(vu8*)0x04000241)
#define REG_VRAMCNT_C   (*(vu8*)0x04000242)
#define REG_VRAMCNT_D   (*(vu8*)0x04000243)
#define REG_VRAMCNT_E   (*(vu8*)0x04000244)
#define REG_VRAMCNT_F   (*(vu8*)0x04000245)
#define REG_VRAMCNT_G   (*(vu8*)0x04000246)
#define REG_VRAMCNT_H   (*(vu8*)0x04000248)
#define REG_VRAMCNT_I   (*(vu8*)0x04000249)

#ifdef __cplusplus
extern "C" {
#endif

static inline void mem_setVramAMapping(MemVramABMapping mapping)
{
    REG_VRAMCNT_A = (u8)mapping;
}

static inline MemVramABMapping mem_getVramAMapping(void)
{
    return (MemVramABMapping)REG_VRAMCNT_A;
}

static inline void mem_setVramBMapping(MemVramABMapping mapping)
{
    REG_VRAMCNT_B = (u8)mapping;
}

static inline MemVramABMapping mem_getVramBMapping(void)
{
    return (MemVramABMapping)REG_VRAMCNT_B;
}

static inline void mem_setVramCMapping(MemVramCMapping mapping)
{
    REG_VRAMCNT_C = (u8)mapping;
}

static inline MemVramCMapping mem_getVramCMapping(void)
{
    return (MemVramCMapping)REG_VRAMCNT_C;
}

static inline void mem_setVramDMapping(MemVramDMapping mapping)
{
    REG_VRAMCNT_D = (u8)mapping;
}

static inline MemVramDMapping mem_getVramDMapping(void)
{
    return (MemVramDMapping)REG_VRAMCNT_D;
}

static inline void mem_setVramEMapping(MemVramEMapping mapping)
{
    REG_VRAMCNT_E = (u8)mapping;
}

static inline MemVramEMapping mem_getVramEMapping(void)
{
    return (MemVramEMapping)REG_VRAMCNT_E;
}

static inline void mem_setVramFMapping(MemVramFGMapping mapping)
{
    REG_VRAMCNT_F = (u8)mapping;
}

static inline MemVramFGMapping mem_getVramFMapping(void)
{
    return (MemVramFGMapping)REG_VRAMCNT_F;
}

static inline void mem_setVramGMapping(MemVramFGMapping mapping)
{
    REG_VRAMCNT_G = (u8)mapping;
}

static inline MemVramFGMapping mem_getVramGMapping(void)
{
    return (MemVramFGMapping)REG_VRAMCNT_G;
}

static inline void mem_setVramHMapping(MemVramHMapping mapping)
{
    REG_VRAMCNT_H = (u8)mapping;
}

static inline MemVramHMapping mem_getVramHMapping(void)
{
    return (MemVramHMapping)REG_VRAMCNT_H;
}

static inline void mem_setVramIMapping(MemVramIMapping mapping)
{
    REG_VRAMCNT_I = (u8)mapping;
}

static inline MemVramIMapping mem_getVramIMapping(void)
{
    return (MemVramIMapping)REG_VRAMCNT_I;
}

#ifdef __cplusplus
}
#endif
