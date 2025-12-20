#pragma once

#define REG_MICCNT                          (*(vu16*)0x04004600)
#define REG_MIC_FIFO                        (*(vu32*)0x04004604)

#define MICCNT_FORMAT_MAKE_STEREO           (0 << 0)
#define MICCNT_FORMAT_NORMAL                (2 << 0)
#define MICCNT_FORMAT_NONE                  (3 << 0)

#define MICCNT_RATE_DIV_1                   (0 << 2)
#define MICCNT_RATE_DIV_2                   (1 << 2)
#define MICCNT_RATE_DIV_3                   (2 << 2)
#define MICCNT_RATE_DIV_4                   (3 << 2)

#define MICCNT_FIFO_EMPTY                   (1 << 8)
#define MICCNT_FIFO_HALF_FULL               (1 << 9)
#define MICCNT_FIFO_FULL                    (1 << 10)
#define MICCNT_FIFO_OVERFLOW                (1 << 11)

#define MICCNT_CLEAR_FIFO                   (1 << 12)

#define MICCNT_IRQ_NONE                     (0 << 13)
#define MICCNT_IRQ_HALF_FULL                (1 << 13)
#define MICCNT_IRQ_OVERFLOW                 (2 << 13)
#define MICCNT_IRQ_HALF_OVERFLOW            (3 << 13)

#define MICCNT_ENABLE                       (1 << 15)

#ifdef __cplusplus
extern "C" {
#endif

static inline void twlmic_configure(u32 format, u32 rate, u32 irq)
{
    REG_MICCNT = (REG_MICCNT & ~(MICCNT_FORMAT_NONE | MICCNT_RATE_DIV_4 | MICCNT_IRQ_HALF_OVERFLOW)) | format | rate | irq;
}

static inline bool twlmic_isFifoEmpty()
{
    return REG_MICCNT & MICCNT_FIFO_EMPTY;
}

static inline bool twlmic_isFifoHalfFull()
{
    return REG_MICCNT & MICCNT_FIFO_HALF_FULL;
}

static inline bool twlmic_isFifoFull()
{
    return REG_MICCNT & MICCNT_FIFO_FULL;
}

static inline bool twlmic_isFifoOverflow()
{
    return REG_MICCNT & MICCNT_FIFO_OVERFLOW;
}

static inline void twlmic_clearFifo()
{
    REG_MICCNT |= MICCNT_CLEAR_FIFO;
}

static inline void twlmic_start()
{
    REG_MICCNT |= MICCNT_ENABLE;
}

static inline void twlmic_stop()
{
    REG_MICCNT &= ~MICCNT_ENABLE;
}

#ifdef __cplusplus
}
#endif
