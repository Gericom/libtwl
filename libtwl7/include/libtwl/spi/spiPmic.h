#pragma once
#include "spi.h"

#define PMIC_REG_CONTROL            0
#define PMIC_REG_BATTERY            1
#define PMIC_REG_MICROPHONE         2
#define PMIC_REG_MICROPHONE_GAIN    3
#define PMIC_REG_BACKLIGHT          4
#define PMIC_REG_TWL                0x10

#define PMIC_CONTROL_AMP_ENABLE                 (1 << 0)
#define PMIC_CONTROL_AMP_MUTE                   (1 << 1)
#define PMIC_CONTROL_BOTTOM_BACKLIGHT_ENABLE    (1 << 2)
#define PMIC_CONTROL_TOP_BACKLIGHT_ENABLE       (1 << 3)

#define PMIC_CONTROL_POWER_LED_BLINK_NONE       (0 << 4)
#define PMIC_CONTROL_POWER_LED_BLINK_SLOW       (1 << 4)
#define PMIC_CONTROL_POWER_LED_BLINK_FAST       (3 << 4)
#define PMIC_CONTROL_POWER_LED_BLINK_MASK       (3 << 4)

#define PMIC_CONTROL_SHUTDOWN                   (1 << 6)

#define PMIC_BATTERY_LOW                        (1 << 0)

#define PMIC_MICROPHONE_AMP_ENABLE              (1 << 0)

#define PMIC_MICROPHONE_AMP_GAIN_20_DB          (0 << 0)
#define PMIC_MICROPHONE_AMP_GAIN_40_DB          (1 << 0)
#define PMIC_MICROPHONE_AMP_GAIN_80_DB          (2 << 0)
#define PMIC_MICROPHONE_AMP_GAIN_160_DB         (3 << 0)

#define PMIC_BACKLIGHT_LOW                      (0 << 0)
#define PMIC_BACKLIGHT_MEDIUM                   (1 << 0)
#define PMIC_BACKLIGHT_HIGH                     (2 << 0)
#define PMIC_BACKLIGHT_MAX                      (3 << 0)
#define PMIC_BACKLIGHT_MASK                     (3 << 0)

#define PMIC_BACKLIGHT_MAX_WHEN_EXTERNAL_POWER  (1 << 2)
#define PMIC_BACKLIGHT_EXTERNAL_POWER           (1 << 3)

#define PMIC_TWL_REBOOT                         (1 << 0)

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Reads the given register of the SPI power management chip.
/// @param reg The register to read.
/// @return The value read from the register.
u8 pmic_readRegister(u8 reg);

/// @brief Writes the given value to the given register of the SPI power management chip.
/// @param reg The register to write.
/// @param data The value to write to the register.
void pmic_writeRegister(u8 reg, u8 data);

static inline void pmic_setAmplifierEnable(bool enabled)
{
    u32 control = pmic_readRegister(PMIC_REG_CONTROL);
    if (enabled)
    {
        control |= PMIC_CONTROL_AMP_ENABLE;
        control &= ~PMIC_CONTROL_AMP_MUTE;
    }
    else
    {
        control &= ~PMIC_CONTROL_AMP_ENABLE;
        control |= PMIC_CONTROL_AMP_MUTE;
    }
    pmic_writeRegister(PMIC_REG_CONTROL, control);
}

static inline void pmic_setTopBacklightEnable(bool enabled)
{
    u32 control = pmic_readRegister(PMIC_REG_CONTROL);
    if (enabled)
        control |= PMIC_CONTROL_TOP_BACKLIGHT_ENABLE;
    else
        control &= ~PMIC_CONTROL_TOP_BACKLIGHT_ENABLE;
    pmic_writeRegister(PMIC_REG_CONTROL, control);
}

static inline void pmic_setBottomBacklightEnable(bool enabled)
{
    u32 control = pmic_readRegister(PMIC_REG_CONTROL);
    if (enabled)
        control |= PMIC_CONTROL_BOTTOM_BACKLIGHT_ENABLE;
    else
        control &= ~PMIC_CONTROL_BOTTOM_BACKLIGHT_ENABLE;
    pmic_writeRegister(PMIC_REG_CONTROL, control);
}

static inline void pmic_setPowerLedBlink(u32 blinkMode)
{
    u32 control = pmic_readRegister(PMIC_REG_CONTROL);
    control &= ~PMIC_CONTROL_POWER_LED_BLINK_MASK;
    control |= blinkMode;
    pmic_writeRegister(PMIC_REG_CONTROL, control);
}

static inline void pmic_shutdown(void)
{
    pmic_writeRegister(PMIC_REG_CONTROL, PMIC_CONTROL_SHUTDOWN);
}

static inline bool pmic_isBatteryLow(void)
{
    return pmic_readRegister(PMIC_REG_BATTERY) & PMIC_BATTERY_LOW;
}

static inline bool pmic_isExternalPowerConnected(void)
{
    return pmic_readRegister(PMIC_REG_BACKLIGHT) & PMIC_BACKLIGHT_EXTERNAL_POWER;
}

static inline void pmic_setMicrophoneAmplifierEnable(bool enabled)
{
    pmic_writeRegister(PMIC_REG_MICROPHONE, enabled ? PMIC_MICROPHONE_AMP_ENABLE : 0);
}

static inline void pmic_setMicrophoneAmplifierGain(u32 gain)
{
    pmic_writeRegister(PMIC_REG_MICROPHONE_GAIN, gain);
}

static inline void pmic_setBacklightLevel(u32 backlightLevel)
{
    u32 control = pmic_readRegister(PMIC_REG_CONTROL);
    control &= ~PMIC_BACKLIGHT_MASK;
    control |= backlightLevel;
    pmic_writeRegister(PMIC_REG_CONTROL, control);
}

/// @brief Only on DSi causes the device to reboot. Also works in DS mode.
static inline void pmic_rebootTwl(void)
{
    pmic_writeRegister(PMIC_REG_TWL, PMIC_TWL_REBOOT);
}

#ifdef __cplusplus
}
#endif
