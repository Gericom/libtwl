#pragma once

typedef enum
{
    MEM_TWL_WRAM_A_SLOT_0 = 0,
    MEM_TWL_WRAM_A_SLOT_01 = 2,
    MEM_TWL_WRAM_A_SLOT_ALL = 3
} MemTwlWramASlots;

typedef enum
{
    MEM_TWL_WRAM_BC_SLOT_0 = 0,
    MEM_TWL_WRAM_BC_SLOT_01 = 1,
    MEM_TWL_WRAM_BC_SLOT_0123 = 2,
    MEM_TWL_WRAM_BC_SLOT_ALL = 3
} MemTwlWramBCSlots;

typedef enum
{
    MEM_TWL_WRAM_A_NONE = 0,
    MEM_TWL_WRAM_A_ARM9 = 0x80,
    MEM_TWL_WRAM_A_ARM7 = 0x81,
} MemTwlWramAMaster;

typedef enum
{
    MEM_TWL_WRAM_B_NONE = 0,
    MEM_TWL_WRAM_B_ARM9 = 0x80,
    MEM_TWL_WRAM_B_ARM7 = 0x81,
    MEM_TWL_WRAM_B_DSP_CODE = 0x82
} MemTwlWramBMaster;

typedef enum
{
    MEM_TWL_WRAM_C_NONE = 0,
    MEM_TWL_WRAM_C_ARM9 = 0x80,
    MEM_TWL_WRAM_C_ARM7 = 0x81,
    MEM_TWL_WRAM_C_DSP_DATA = 0x82
} MemTwlWramCMaster;

#define MEM_TWL_WRAM_BASE           0x03000000

#define MEM_TWL_WRAM_A_SLOT_COUNT   4
#define MEM_TWL_WRAM_A_SLOT_SIZE    0x10000

#define MEM_TWL_WRAM_BC_SLOT_COUNT  8
#define MEM_TWL_WRAM_BC_SLOT_SIZE   0x8000

#define REG_MBK1    (*(vu32*)0x04004040)
#define REG_MBK2    (*(vu32*)0x04004044)
#define REG_MBK3    (*(vu32*)0x04004048)
#define REG_MBK4    (*(vu32*)0x0400404C)
#define REG_MBK5    (*(vu32*)0x04004050)
#define REG_MBK6    (*(vu32*)0x04004054)
#define REG_MBK7    (*(vu32*)0x04004058)
#define REG_MBK8    (*(vu32*)0x0400405C)
#define REG_MBK9    (*(vu32*)0x04004060)

#ifdef __cplusplus
extern "C" {
#endif

static inline void mem_setTwlWramAMapping(MemTwlWramASlots usedSlots, u32 start, u32 length)
{
    start = (start - MEM_TWL_WRAM_BASE) >> 16;
    u32 end = start + (length >> 16);
    REG_MBK6 = (start << 4) | (usedSlots << 12) | (end << 20);
}

static inline void mem_setTwlWramBMapping(MemTwlWramBCSlots usedSlots, u32 start, u32 length)
{
    start = (start - MEM_TWL_WRAM_BASE) >> 15;
    u32 end = start + (length >> 15);
    REG_MBK7 = (start << 3) | (usedSlots << 12) | (end << 19);
}

static inline void mem_setTwlWramCMapping(MemTwlWramBCSlots usedSlots, u32 start, u32 length)
{
    start = (start - MEM_TWL_WRAM_BASE) >> 15;
    u32 end = start + (length >> 15);
    REG_MBK8 = (start << 3) | (usedSlots << 12) | (end << 19);
}

static inline void* mem_getTwlWramAStart(void)
{
    return (void*)(MEM_TWL_WRAM_BASE + (((REG_MBK6 >> 4) & 0xFF) << 16));
}

static inline void* mem_getTwlWramBStart(void)
{
    return (void*)(MEM_TWL_WRAM_BASE + (((REG_MBK7 >> 3) & 0x1FF) << 15));
}

static inline void* mem_getTwlWramCStart(void)
{
    return (void*)(MEM_TWL_WRAM_BASE + (((REG_MBK8 >> 3) & 0x1FF) << 15));
}

#ifdef LIBTWL_ARM9

static inline void mem_setTwlWramABlockMapping(MemTwlWramAMaster master, int block, int slot)
{
    ((vu8*)&REG_MBK1)[block] = master | (slot << 2);
}

static inline void mem_setTwlWramBBlockMapping(MemTwlWramBMaster master, int block, int slot)
{
    ((vu8*)&REG_MBK2)[block] = master | (slot << 2);
}

static inline void mem_setTwlWramCBlockMapping(MemTwlWramCMaster master, int block, int slot)
{
    ((vu8*)&REG_MBK4)[block] = master | (slot << 2);
}

#endif

static inline bool mem_isTwlWramUnlocked(void)
{
    if ((REG_SCFG_EXT & 0x80000000) == 0)
        return false; // SCFG and MBK registers are permanently locked

    if ((REG_MBK9 & 0xFFFF0F) != 0)
        return false; // One or more MBK registers are locked

    return true; 
}

#ifdef LIBTWL_ARM7

static inline bool mem_isTwlWramUnlockable(void)
{
    return (REG_SCFG_EXT & 0x80000000) != 0;
}

static inline void mem_unlockAllTwlWram(void)
{
    REG_MBK9 = 0;
}

#endif

#ifdef __cplusplus
}
#endif
