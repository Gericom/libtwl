#pragma once
#include "rtosState.h"

enum
{
    RTOS_IRQ_VBLANK = 1 << 0,
    RTOS_IRQ_HBLANK = 1 << 1,
    RTOS_IRQ_VCOUNT = 1 << 2,
    RTOS_IRQ_TIMER0 = 1 << 3,
    RTOS_IRQ_TIMER1 = 1 << 4,
    RTOS_IRQ_TIMER2 = 1 << 5,
    RTOS_IRQ_TIMER3 = 1 << 6,
#ifdef LIBTWL_ARM7
    RTOS_IRQ_SIO = 1 << 7,
#endif
    RTOS_IRQ_DMA0 = 1 << 8,
    RTOS_IRQ_DMA1 = 1 << 9,
    RTOS_IRQ_DMA2 = 1 << 10,
    RTOS_IRQ_DMA3 = 1 << 11,
    RTOS_IRQ_KEYS = 1 << 12,
    RTOS_IRQ_GBA_IREQ = 1 << 13,
    RTOS_IRQ_DS_SLOTA_DETECT = 1 << 14,
    RTOS_IRQ_DS_SLOTB_DETECT = 1 << 15,
    RTOS_IRQ_IPC_SYNC = 1 << 16,
    RTOS_IRQ_IPC_FIFO_SEND = 1 << 17,
    RTOS_IRQ_IPC_FIFO_RECV = 1 << 18,
    RTOS_IRQ_DS_SLOTA_ROM_XFER = 1 << 19,
    RTOS_IRQ_DS_SLOTA_IREQ = 1 << 20,
#ifdef LIBTWL_ARM9
    RTOS_IRQ_GX_FIFO = 1 << 21,

    RTOS_IRQ_DSP = 1 << 24,
    RTOS_IRQ_CAMERA = 1 << 25,
#endif
#ifdef LIBTWL_ARM7
    RTOS_IRQ_PMIC = 1 << 22,
    RTOS_IRQ_SPI = 1 << 23,
    RTOS_IRQ_WIFI = 1 << 24,
#endif
    RTOS_IRQ_DS_SLOTB_ROM_XFER = 1 << 26,
    RTOS_IRQ_DS_SLOTB_IREQ = 1 << 27,
    RTOS_IRQ_NDMA0 = 1 << 28,
    RTOS_IRQ_NDMA1 = 1 << 29,
    RTOS_IRQ_NDMA2 = 1 << 30,
    RTOS_IRQ_NDMA3 = 1 << 31
};

#define RTOS_IRQ_TIMER(x)   (1 << ((x) + 3))

#ifdef LIBTWL_ARM7
enum
{
    RTOS_IRQ2_GPIO18_0 = 1 << 0,
    RTOS_IRQ2_GPIO18_1 = 1 << 1,
    RTOS_IRQ2_GPIO18_2 = 1 << 2,
    RTOS_IRQ2_GPIO33_0 = 1 << 4,
    RTOS_IRQ2_GPIO33_1 = 1 << 5,
    RTOS_IRQ2_MCU = 1 << 6, //GPIO33[2]
    RTOS_IRQ2_GPIO33_3 = 1 << 7,
    RTOS_IRQ2_SDMMC = 1 << 8,
    RTOS_IRQ2_SDMMC_DATA1 = 1 << 9,
    RTOS_IRQ2_SDIO = 1 << 10,
    RTOS_IRQ2_SDIO_DATA1 = 1 << 11,
    RTOS_IRQ2_AES = 1 << 12,
    RTOS_IRQ2_I2C = 1 << 13,
    RTOS_IRQ2_MIC = 1 << 14
};
#endif

#define REG_IME     (*(vu32*)0x04000208)

#define REG_IE      (*(vu32*)0x04000210)
#define REG_IF      (*(vu32*)0x04000214)

#ifdef LIBTWL_ARM7
#define REG_IE2     (*(vu32*)0x04000218)
#define REG_IF2     (*(vu32*)0x0400021C)

#define BIOS_IRQ_HANDLER    (*(vu32*)0x0380FFFC)
#endif

typedef void (*rtos_irq_func_t)(u32 irqMask);

#ifdef __cplusplus
extern "C" {
#endif

extern void rtos_halt(void);
extern void rtos_irqVector(void);

extern u32 rtos_disableIrqs(void);
extern u32 rtos_enableIrqs(void);
extern void rtos_restoreIrqs(u32 value);

void rtos_initIrq(void);
void rtos_setIrqFunc(u32 mask, rtos_irq_func_t func);

static inline u32 rtos_getIrqDepth(void)
{
    return gRtosState.irqDepth;
}

static inline void rtos_ackIrqMask(u32 mask)
{
    REG_IF = mask;
}

static inline void rtos_enableIrqMask(u32 mask)
{
    REG_IE |= mask;
}

static inline void rtos_disableIrqMask(u32 mask)
{
    REG_IE &= ~mask;
}

static inline void rtos_setIrqMask(u32 mask)
{
    REG_IE = mask;
}

static inline u32 rtos_getIrqMask(void)
{
    return REG_IE;
}

static inline u32 rtos_getIrqFlags(void)
{
    return REG_IF;
}

#ifdef LIBTWL_ARM7
static inline void rtos_ackIrq2Mask(u32 mask)
{
    REG_IF2 = mask;
}

static inline void rtos_enableIrq2Mask(u32 mask)
{
    REG_IE2 |= mask;
}

static inline void rtos_disableIrq2Mask(u32 mask)
{
    REG_IE2 &= ~mask;
}

static inline void rtos_setIrq2Mask(u32 mask)
{
    REG_IE2 = mask;
}

static inline u32 rtos_getIrq2Mask(void)
{
    return REG_IE2;
}

static inline u32 rtos_getIrq2Flags(void)
{
    return REG_IF2;
}
#endif

#ifdef __cplusplus
}
#endif
