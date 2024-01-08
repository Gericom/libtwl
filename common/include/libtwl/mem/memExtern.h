#pragma once

#define REG_EXMEMCNT                    (*(vu16*)0x04000204)

#define EXMEMCNT_SLOT2_RAM_WAIT_10      0
#define EXMEMCNT_SLOT2_RAM_WAIT_8       1
#define EXMEMCNT_SLOT2_RAM_WAIT_6       2
#define EXMEMCNT_SLOT2_RAM_WAIT_18      3

#define EXMEMCNT_SLOT2_ROM_WAIT1_10     (0 << 2)
#define EXMEMCNT_SLOT2_ROM_WAIT1_8      (1 << 2)
#define EXMEMCNT_SLOT2_ROM_WAIT1_6      (2 << 2)
#define EXMEMCNT_SLOT2_ROM_WAIT1_18     (3 << 2)

#define EXMEMCNT_SLOT2_ROM_WAIT2_6      (0 << 4)
#define EXMEMCNT_SLOT2_ROM_WAIT2_4      (1 << 4)

#define EXMEMCNT_SLOT2_PHI_LOW          (0 << 5)
#define EXMEMCNT_SLOT2_PHI_4_19_MHZ     (1 << 5)
#define EXMEMCNT_SLOT2_PHI_8_38_MHZ     (2 << 5)
#define EXMEMCNT_SLOT2_PHI_16_76_MHZ    (3 << 5)

#define EXMEMCNT_SLOT2_CPU_ARM9         (0 << 7)
#define EXMEMCNT_SLOT2_CPU_ARM7         (1 << 7)

#define EXMEMCNT_SLOT1_CPU_ARM9         (0 << 11)
#define EXMEMCNT_SLOT1_CPU_ARM7         (1 << 11)

#define EXMEMCNT_MAIN_MEM_MODE_ASYNC    (0 << 14)
#define EXMEMCNT_MAIN_MEM_MODE_SYNC     (1 << 14)

#define EXMEMCNT_MAIN_MEM_PRIO_ARM9     (0 << 15)
#define EXMEMCNT_MAIN_MEM_PRIO_ARM7     (1 << 15)

#ifdef __cplusplus
extern "C" {
#endif

static inline void mem_setGbaCartridgeRamWait(u32 ramWait)
{
    REG_EXMEMCNT = (REG_EXMEMCNT & ~EXMEMCNT_SLOT2_RAM_WAIT_18) | ramWait;
}

static inline void mem_setGbaCartridgeRomWaits(u32 romWait1, u32 romWait2)
{
    REG_EXMEMCNT = (REG_EXMEMCNT & ~(EXMEMCNT_SLOT2_ROM_WAIT1_18 | EXMEMCNT_SLOT2_ROM_WAIT2_4)) | romWait1 | romWait2;
}

static inline void mem_setGbaCartridgePhi(u32 phi)
{
    REG_EXMEMCNT = (REG_EXMEMCNT & ~EXMEMCNT_SLOT2_PHI_16_76_MHZ) | phi;
}

#ifdef LIBTWL_ARM9

static inline u32 mem_setGbaCartridgeCpu(u32 slot2Cpu)
{
    u32 exMemCnt = REG_EXMEMCNT;
    u32 oldValue = exMemCnt & EXMEMCNT_SLOT2_CPU_ARM7;
    REG_EXMEMCNT = (exMemCnt & ~EXMEMCNT_SLOT2_CPU_ARM7) | slot2Cpu;
    return oldValue;
}

static inline void mem_setDsCartridgeCpu(u32 slot1Cpu)
{
    REG_EXMEMCNT = (REG_EXMEMCNT & ~EXMEMCNT_SLOT1_CPU_ARM7) | slot1Cpu;
}

static inline void mem_setMainMemoryPriority(u32 mainMemoryPriority)
{
    REG_EXMEMCNT = (REG_EXMEMCNT & ~EXMEMCNT_MAIN_MEM_PRIO_ARM7) | mainMemoryPriority;
}

#endif

#ifdef __cplusplus
}
#endif
