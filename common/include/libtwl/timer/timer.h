#pragma once

#define REG_TM0CNT_L    (*(vu16*)0x04000100)
#define REG_TM0CNT_H    (*(vu16*)0x04000102)

#define REG_TM1CNT_L    (*(vu16*)0x04000104)
#define REG_TM1CNT_H    (*(vu16*)0x04000106)

#define REG_TM2CNT_L    (*(vu16*)0x04000108)
#define REG_TM2CNT_H    (*(vu16*)0x0400010A)

#define REG_TM3CNT_L    (*(vu16*)0x0400010C)
#define REG_TM3CNT_H    (*(vu16*)0x0400010E)

#define REG_TMCNT_L(x)  (((vu16*)0x04000100)[(x) * 2])
#define REG_TMCNT_H(x)  (((vu16*)0x04000102)[(x) * 2])

/// @brief System clock. Frequency: 33.513982 MHz.
#define TMCNT_H_CLK_SYS               (0 << 0)

/// @brief System clock divided by 64. Frequency: 523.65596875 kHz.
#define TMCNT_H_CLK_SYS_DIV_64        (1 << 0)

/// @brief System clock divided by 256: Frequency: 130.9139921875 kHz.
#define TMCNT_H_CLK_SYS_DIV_256       (2 << 0)

/// @brief System clock divided by 1024. Frequency: 32.728498046875 kHz.
#define TMCNT_H_CLK_SYS_DIV_1024      (3 << 0)

/// @brief Timer ticks when the previous timer overflows.
/// @note  This mode is not supported by timer 0 since it has no previous timer.
#define TMCNT_H_CLK_PREV_TMR_OVF      (1 << 2)

/// @brief Timer triggers an irq on overflow.
#define TMCNT_H_IRQ                   (1 << 6)

/// @brief Enables the timer.
#define TMCNT_H_ENABLE                (1 << 7)

#ifdef __cplusplus
extern "C" {
#endif

static inline void tmr_configure(int timer, int clock, u16 reload, bool irq)
{
    REG_TMCNT_H(timer) = clock | (irq ? TMCNT_H_IRQ : 0);
    REG_TMCNT_L(timer) = reload;
}

static inline void tmr_start(int timer)
{
    REG_TMCNT_H(timer) |= TMCNT_H_ENABLE;
}

static inline void tmr_stop(int timer)
{
    REG_TMCNT_H(timer) &= ~TMCNT_H_ENABLE;
}

static inline u16 tmr_getCounter(int timer)
{
    return REG_TMCNT_L(timer);
}

static inline void tmr_setReload(int timer, u16 reload)
{
    REG_TMCNT_L(timer) = reload;
}

#ifdef __cplusplus
}
#endif