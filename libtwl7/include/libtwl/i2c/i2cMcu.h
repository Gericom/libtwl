#pragma once

#define MCU_REG_VER_INFO        0x00
#define MCU_REG_PMIC_INFO       0x01
#define MCU_REG_BATT_INFO       0x02

#define MCU_REG_IRQ             0x10
#define MCU_REG_COMMAND         0x11
#define MCU_REG_MODE            0x12

#define MCU_REG_POWER_INFO      0x20
#define MCU_REG_POWER_MODE      0x21

#define MCU_REG_WIFI            0x30
#define MCU_REG_CAMERA          0x31

#define MCU_REG_VOLUME          0x40
#define MCU_REG_BACKLIGHT       0x41

#define MCU_REG_BATT_CALIB      0x60
#define MCU_REG_CALIB_STATUS    0x61
#define MCU_REG_CALIB_VALUE     0x62
#define MCU_REG_POWER_LED       0x63

#define MCU_REG_WARMBOOT        0x70

#define MCU_REG_RESET_TIME      0x80
#define MCU_REG_PWOFF_TIME      0x81

#define MCU_IRQ_RESET           0x01
#define MCU_IRQ_POWER_OFF       0x02
#define MCU_IRQ_POWER_SWITCH    0x08
#define MCU_IRQ_BATTERY_EMPTY   0x10
#define MCU_IRQ_BATTERY_LOW     0x20
#define MCU_IRQ_VOLUME          0x40

#define MCU_COMMAND_HARD_RESET  1

#define MCU_I2C_SWI_WAIT_BY_LOOP_DELAY  0x180

#ifdef __cplusplus
extern "C" {
#endif

u8 mcu_readReg(u8 reg);
bool mcu_writeReg(u8 reg, u8 value);

static inline u8 mcu_getIrqMask(void)
{
    return mcu_readReg(MCU_REG_IRQ);
}

static inline bool mcu_setWarmBootFlag(bool warmBoot)
{
    return mcu_writeReg(MCU_REG_WARMBOOT, warmBoot ? 1 : 0);
}

static inline bool mcu_hardReset(void)
{
    return mcu_writeReg(MCU_REG_COMMAND, MCU_COMMAND_HARD_RESET);
}

#ifdef __cplusplus
}
#endif
