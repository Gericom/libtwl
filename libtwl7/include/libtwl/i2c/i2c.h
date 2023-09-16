#pragma once

typedef enum
{
    I2C_DIRECTION_WRITE = 0,
    I2C_DIRECTION_READ = 1
} I2cDirection;

#define REG_I2C_DATA    (*(vu8*)0x04004500)
#define REG_I2C_CNT     (*(vu8*)0x04004501)

#define I2C_CNT_LAST        (1 << 0)
#define I2C_CNT_FIRST       (1 << 1)
#define I2C_CNT_ERROR       (1 << 2)
#define I2C_CNT_ACK         (1 << 4)

#define I2C_CNT_DIR_WRITE   (0 << 5)
#define I2C_CNT_DIR_READ    (1 << 5)

#define I2C_CNT_IRQ         (1 << 6)
#define I2C_CNT_ENABLE      (1 << 7)

#define I2C_DEVICE_MCU              0x4A
#define I2C_DEVICE_CAMERA_BACK      0x78
#define I2C_DEVICE_CAMERA_FRONT     0x7A

#ifdef __cplusplus
extern "C" {
#endif

static inline void i2c_waitBusy(void)
{
    while (REG_I2C_CNT & I2C_CNT_ENABLE);
}

static inline bool i2c_start(u8 device, I2cDirection direction)
{
    i2c_waitBusy();
    REG_I2C_DATA = device | direction;
    REG_I2C_CNT = I2C_CNT_FIRST | I2C_CNT_DIR_WRITE | I2C_CNT_ENABLE;
    i2c_waitBusy();
    return (REG_I2C_CNT & I2C_CNT_ACK);
}

static inline u8 i2c_read(bool last)
{
    REG_I2C_CNT = (last ? I2C_CNT_LAST : I2C_CNT_ACK) | I2C_CNT_DIR_READ | I2C_CNT_ENABLE;
    i2c_waitBusy();
    return REG_I2C_DATA;
}

static inline bool i2c_write(u8 data, bool last)
{
    REG_I2C_DATA = data;
    REG_I2C_CNT = (last ? I2C_CNT_LAST : 0) | I2C_CNT_DIR_WRITE | I2C_CNT_ENABLE;
    i2c_waitBusy();
    return (REG_I2C_CNT & I2C_CNT_ACK);
}

#ifdef __cplusplus
}
#endif
