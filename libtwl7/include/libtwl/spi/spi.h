#pragma once

#define REG_SPICNT              (*(vu16*)0x040001C0)
#define REG_SPIDATA             (*(vu16*)0x040001C2)

#define SPICNT_SPEED_4_MHZ      (0 << 0)
#define SPICNT_SPEED_2_MHZ      (1 << 0)
#define SPICNT_SPEED_1_MHZ      (2 << 0)
#define SPICNT_SPEED_512_KHZ    (3 << 0)
#define SPICNT_TWL_SPEED_8_MHZ  (4 << 0)

#define SPICNT_BUSY             (1 << 7)

#define SPICNT_DEVICE_PMIC      (0 << 8)
#define SPICNT_DEVICE_FLASH     (1 << 8)
#define SPICNT_DEVICE_TOUCH     (2 << 8)

#define SPICNT_8_BIT            (0 << 10)
#define SPICNT_16_BIT           (1 << 10)

#define SPICNT_HOLD_CS          (1 << 11)
#define SPICNT_IRQ              (1 << 14)
#define SPICNT_ENABLE           (1 << 15)

#ifdef __cplusplus
extern "C" {
#endif

static inline void spi_waitBusy(void)
{
    while (REG_SPICNT & SPICNT_BUSY);
}

static inline u8 spi_transferByte(u32 control, u8 data)
{
    spi_waitBusy();
    REG_SPICNT = control | SPICNT_ENABLE | SPICNT_HOLD_CS;
    REG_SPIDATA = data;
    spi_waitBusy();
    return REG_SPIDATA;
}

static inline u8 spi_transferLastByte(u32 control, u8 data)
{
    spi_waitBusy();
    REG_SPICNT = control | SPICNT_ENABLE;
    REG_SPIDATA = data;
    spi_waitBusy();
    return REG_SPIDATA;
}

#ifdef __cplusplus
}
#endif
