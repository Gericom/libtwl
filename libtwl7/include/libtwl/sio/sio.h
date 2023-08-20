#pragma once

#define KEYINPUT_KEY_A              (1 << 0)
#define KEYINPUT_KEY_B              (1 << 1)
#define KEYINPUT_KEY_SELECT         (1 << 2)
#define KEYINPUT_KEY_START          (1 << 3)
#define KEYINPUT_KEY_DPAD_LEFT      (1 << 4)
#define KEYINPUT_KEY_DPAD_RIGHT     (1 << 5)
#define KEYINPUT_KEY_DPAD_UP        (1 << 6)
#define KEYINPUT_KEY_DPAD_DOWN      (1 << 7)
#define KEYINPUT_KEY_R              (1 << 8)
#define KEYINPUT_KEY_L              (1 << 9)

#define KEYCNT_MASK_KEY_A           (1 << 0)
#define KEYCNT_MASK_KEY_B           (1 << 1)
#define KEYCNT_MASK_KEY_SELECT      (1 << 2)
#define KEYCNT_MASK_KEY_START       (1 << 3)
#define KEYCNT_MASK_KEY_DPAD_LEFT   (1 << 4)
#define KEYCNT_MASK_KEY_DPAD_RIGHT  (1 << 5)
#define KEYCNT_MASK_KEY_DPAD_UP     (1 << 6)
#define KEYCNT_MASK_KEY_DPAD_DOWN   (1 << 7)
#define KEYCNT_MASK_KEY_R           (1 << 8)
#define KEYCNT_MASK_KEY_L           (1 << 9)

#define KEYCNT_IRQ                  (1 << 14)

#define KEYCNT_MODE_OR              (0 << 15)
#define KEYCNT_MODE_AND             (1 << 15)

#define RCNT0_L_DATA_SC             (1 << 0)
#define RCNT0_L_DATA_SD             (1 << 1)
#define RCNT0_L_DATA_SI             (1 << 2)
#define RCNT0_L_DATA_SO             (1 << 3)

#define RCNT0_L_DIR_SC_OUTPUT       (1 << 4)
#define RCNT0_L_DIR_SD_OUTPUT       (1 << 5)
#define RCNT0_L_DIR_SI_OUTPUT       (1 << 6)
#define RCNT0_L_DIR_SO_OUTPUT       (1 << 7)

#define RCNT0_L_IRQ                 (1 << 8)

#define RCNT0_L_MODE_MASK           (3 << 14)
#define RCNT0_L_MODE_SIO            (0 << 14)
#define RCNT0_L_MODE_GPIO           (2 << 14)
#define RCNT0_L_MODE_JOYBUS         (3 << 14)

#define RCNT0_H_DATA_KEY_X          (1 << 0)
#define RCNT0_H_DATA_KEY_Y          (1 << 1)
#define RCNT0_H_DATA_KEY_DEBUG      (1 << 3)
#define RCNT0_H_DATA_PEN            (1 << 6)
#define RCNT0_H_DATA_LID            (1 << 7)

#define RCNT1_DATA_RTC_SIO          (1 << 0)
#define RCNT1_DATA_RTC_SCK          (1 << 1)
#define RCNT1_DATA_RTC_CS           (1 << 2)

#define RCNT1_DIR_RTC_SIO_OUTPUT    (1 << 4)
#define RCNT1_DIR_RTC_SCK_OUTPUT    (1 << 5)
#define RCNT1_DIR_RTC_CS_OUTPUT     (1 << 6)

#define REG_SIOCNT_L                (*(vu16*)0x04000128)
#define REG_SIOCNT_H                (*(vu16*)0x0400012A)

#define REG_KEYINPUT                (*(vu16*)0x04000130)
#define REG_KEYCNT                  (*(vu16*)0x04000132)

#define REG_RCNT0_L                 (*(vu16*)0x04000134)
#define REG_RCNT0_H                 (*(vu16*)0x04000136)
#define REG_RCNT1                   (*(vu16*)0x04000138)

#define REG_JOYCNT                  (*(vu16*)0x04000140)

#ifdef __cplusplus
extern "C" {
#endif

static inline void sio_setGpioSiIrq(bool enabled)
{
    // SI must always be used as input
    REG_RCNT0_L &= ~RCNT0_L_DIR_SI_OUTPUT;
    if (enabled)
        REG_RCNT0_L |= RCNT0_L_IRQ;
    else
        REG_RCNT0_L &= ~RCNT0_L_IRQ;
}

static inline void sio_setGpioMode(u32 mode)
{
    REG_RCNT0_L = (REG_RCNT0_L & ~RCNT0_L_MODE_MASK) | (mode & RCNT0_L_MODE_MASK);
}

/// @brief Sets the direction and output levels of all rtc pins at once.
/// @param direction The pin directions as a combination of RCNT1_DIR_RTC_x_OUTPUT.
/// @param data The output levels as a combination of RCNT1_DATA_RTC_x.
static inline void sio_setRtcPins(u32 direction, u32 data)
{
    const u32 dirMask =
        RCNT1_DIR_RTC_SIO_OUTPUT | RCNT1_DIR_RTC_SCK_OUTPUT | RCNT1_DIR_RTC_CS_OUTPUT;
    const u32 dataMask =
        RCNT1_DATA_RTC_SIO | RCNT1_DATA_RTC_SCK | RCNT1_DATA_RTC_CS;
    REG_RCNT1 = (REG_RCNT1 & ~(dirMask | dataMask)) | (direction & dirMask) | (data & dataMask);
}

/// @brief Sets the rtc chip select output level. This function assumes the
///        pin has already been configured as output.
/// @param high True if the output level should be high, or false otherwise.
static inline void sio_setRtcChipSelect(bool high)
{
    if (high)
        REG_RCNT1 |= RCNT1_DATA_RTC_CS;
    else
        REG_RCNT1 &= ~RCNT1_DATA_RTC_CS;
}

#ifdef __cplusplus
}
#endif
