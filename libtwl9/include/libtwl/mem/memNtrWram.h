#pragma once

typedef enum
{
    MEM_NTR_WRAM_ARM9 = 0,
    MEM_NTR_WRAM_ARM7 = 1
} MemNtrWramMapping;

#define REG_WRAMCNT     (*(vu8*)0x04000247)

#ifdef __cplusplus
extern "C" {
#endif

static inline void mem_setNtrWram0Mapping(MemNtrWramMapping mapping)
{
    REG_WRAMCNT = (REG_WRAMCNT & ~1) | mapping;
}

static inline MemNtrWramMapping mem_getNtrWram0Mapping(void)
{
    return (MemNtrWramMapping)(REG_WRAMCNT & 1);
}

static inline void mem_setNtrWram1Mapping(MemNtrWramMapping mapping)
{
    REG_WRAMCNT = (REG_WRAMCNT & ~2) | (mapping << 1);
}

static inline MemNtrWramMapping mem_getNtrWram1Mapping(void)
{
    return (MemNtrWramMapping)((REG_WRAMCNT >> 1) & 1);
}

static inline void mem_setNtrWramMapping(MemNtrWramMapping block0, MemNtrWramMapping block1)
{
    REG_WRAMCNT = block0 | (block1 << 1);
}

#ifdef __cplusplus
}
#endif
