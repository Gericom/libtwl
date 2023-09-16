#include <nds.h>
#include "libtwl/i2c/i2c.h"
#include "libtwl/sys/swi.h"
#include "libtwl/i2c/i2cMcu.h"

static inline void mcu_delay(void)
{
    swi_waitByLoop(MCU_I2C_SWI_WAIT_BY_LOOP_DELAY);
}

static inline bool tryReadReg(u8 reg, u8* value)
{
    if (!i2c_start(I2C_DEVICE_MCU, I2C_DIRECTION_WRITE))
        return false;
    mcu_delay();
    if (!i2c_write(reg, true))
        return false;
    mcu_delay();
    if (!i2c_start(I2C_DEVICE_MCU, I2C_DIRECTION_READ))
        return false;
    mcu_delay();
    i2c_read(false);
    mcu_delay();
    REG_I2C_CNT = I2C_CNT_LAST | I2C_CNT_DIR_READ | I2C_CNT_ERROR | I2C_CNT_ENABLE;
    i2c_waitBusy();
    *value = REG_I2C_DATA;
    return true;
}

u8 mcu_readReg(u8 reg)
{
    u8 value;
    for (int i = 0; i < 8; ++i)
    {
        if (tryReadReg(reg, &value))
            return value;
        REG_I2C_CNT = I2C_CNT_LAST | I2C_CNT_DIR_WRITE | I2C_CNT_ERROR | I2C_CNT_ENABLE;
    }
    return 0;
}

static inline bool tryWriteReg(u8 reg, u8 value)
{
    if (!i2c_start(I2C_DEVICE_MCU, I2C_DIRECTION_WRITE))
        return false;
    mcu_delay();
    if (!i2c_write(reg, false))
        return false;
    mcu_delay();
    if (!i2c_write(value, false))
        return false;
    mcu_delay();
    REG_I2C_CNT = I2C_CNT_LAST | I2C_CNT_DIR_WRITE | I2C_CNT_ERROR | I2C_CNT_ENABLE;
    i2c_waitBusy();
    return true;
}

bool mcu_writeReg(u8 reg, u8 value)
{
    for (int i = 0; i < 8; ++i)
    {
        if (tryWriteReg(reg, value))
            return true;
        REG_I2C_CNT = I2C_CNT_LAST | I2C_CNT_DIR_WRITE | I2C_CNT_ERROR | I2C_CNT_ENABLE;
    }
    return false;
}
