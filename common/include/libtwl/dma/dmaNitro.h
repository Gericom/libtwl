#pragma once

#define REG_DMA0SAD     (*(vu32*)0x040000B0)
#define REG_DMA0DAD     (*(vu32*)0x040000B4)
#define REG_DMA0CNT     (*(vu32*)0x040000B8)

#define REG_DMA1SAD     (*(vu32*)0x040000BC)
#define REG_DMA1DAD     (*(vu32*)0x040000C0)
#define REG_DMA1CNT     (*(vu32*)0x040000C4)

#define REG_DMA2SAD     (*(vu32*)0x040000C8)
#define REG_DMA2DAD     (*(vu32*)0x040000CC)
#define REG_DMA2CNT     (*(vu32*)0x040000D0)

#define REG_DMA3SAD     (*(vu32*)0x040000D4)
#define REG_DMA3DAD     (*(vu32*)0x040000D8)
#define REG_DMA3CNT     (*(vu32*)0x040000DC)

#define REG_DMACNT(x)   (((vu32*)0x040000B8)[(x) * 3])

#ifdef LIBTWL_ARM9

#define REG_DMA0FILL    (*(vu32*)0x040000E0)
#define REG_DMA1FILL    (*(vu32*)0x040000E4)
#define REG_DMA2FILL    (*(vu32*)0x040000E8)
#define REG_DMA3FILL    (*(vu32*)0x040000EC)

#endif

#define DMACNT_COUNT(x)                     (x)

#define DMACNT_DST_MODE_INCREMENT           (0 << 21)
#define DMACNT_DST_MODE_DECREMENT           (1 << 21)
#define DMACNT_DST_MODE_FIXED               (2 << 21)
#define DMACNT_DST_MODE_INCREMENT_RELOAD    (3 << 21)

#define DMACNT_SRC_MODE_INCREMENT           (0 << 23)
#define DMACNT_SRC_MODE_DECREMENT           (1 << 23)
#define DMACNT_SRC_MODE_FIXED               (2 << 23)

#define DMACNT_REPEAT                       (1 << 25)

#define DMACNT_16BIT                        (0 << 26)
#define DMACNT_32BIT                        (1 << 26)

#ifdef LIBTWL_ARM9

#define DMACNT_MODE_IMMEDIATE               (0 << 27)
#define DMACNT_MODE_VBLANK                  (1 << 27)
#define DMACNT_MODE_HBLANK                  (2 << 27)
#define DMACNT_MODE_DISPLAY                 (3 << 27)
#define DMACNT_MODE_MMEM_DISP_FIFO          (4 << 27)
#define DMACNT_MODE_DS_ROM_XFER             (5 << 27)
#define DMACNT_MODE_GBA_DREQ                (6 << 27)
#define DMACNT_MODE_GX_FIFO                 (7 << 27)

#endif
#ifdef LIBTWL_ARM7
#define DMACNT_MODE_IMMEDIATE               (0 << 28)
#define DMACNT_MODE_VBLANK                  (1 << 28)
#define DMACNT_MODE_DS_ROM_XFER             (2 << 28)

#define DMA0CNT_MODE_WIFI                   (3 << 28)
#define DMA1CNT_MODE_GBA_DREQ               (3 << 28)
#define DMA2CNT_MODE_WIFI                   (3 << 28)
#define DMA3CNT_MODE_GBA_DREQ               (3 << 28)
#endif

#define DMACNT_IRQ                          (1 << 30)

#define DMACNT_ENABLE                       (1 << 31)

#ifdef __cplusplus
extern "C" {
#endif

// todo: arm7
#ifdef LIBTWL_ARM9

/// @brief Safely sets the parameters of a nitro dma channel to prevent lockups.
/// @param dma The nitro dma channel to configure
/// @param src The source address
/// @param dst The destination address
/// @param control The channel configuration
extern void dma_ntrSetParams(int dma, const void* src, volatile void* dst, u32 control);

/// @brief Stops a nitro dma channel with a special procedure to prevent a lockup if the dma was just about to start.
/// @param dma The nitro dma channel to stop
extern void dma_ntrStopSafe(int dma);

/// @brief Stops a nitro dma channel directly by writing 0 to the control register.
///        Use with caution! Stopping a dma that is just about to start can lock up the system!
///        A safe use case would for example be stopping a hblank dma during vblank.
/// @param dma The nitro dma channel to stop
static inline void dma_ntrStopDirect(int dma)
{
    REG_DMACNT(dma) = 0;
}

static inline void dma_ntrCopy16(int dma, const void* src, volatile void* dst, u32 length)
{
    dma_ntrSetParams(dma, src, dst, 
        DMACNT_ENABLE | DMACNT_MODE_IMMEDIATE | DMACNT_16BIT | 
        DMACNT_SRC_MODE_INCREMENT | DMACNT_DST_MODE_INCREMENT | 
        DMACNT_COUNT(length >> 1));
}

static inline void dma_ntrCopy32(int dma, const void* src, volatile void* dst, u32 length)
{
    dma_ntrSetParams(dma, src, dst, 
        DMACNT_ENABLE | DMACNT_MODE_IMMEDIATE | DMACNT_32BIT | 
        DMACNT_SRC_MODE_INCREMENT | DMACNT_DST_MODE_INCREMENT | 
        DMACNT_COUNT(length >> 2));
}

#endif

#ifdef __cplusplus
}
#endif
