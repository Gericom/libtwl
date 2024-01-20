#include <nds.h>
#include "libtwl/spi/spi.h"
#include "libtwl/spi/spiCodec.h"

u8 codec_readRegister(u8 reg)
{
    spi_transferByte(SPICNT_DEVICE_TOUCH | SPICNT_SPEED_4_MHZ, (reg << 1) | 1);
    return spi_transferLastByte(SPICNT_DEVICE_TOUCH | SPICNT_SPEED_4_MHZ, 0);
}

void codec_writeRegister(u8 reg, u8 data)
{
    spi_transferByte(SPICNT_DEVICE_TOUCH | SPICNT_SPEED_4_MHZ, reg << 1);
    spi_transferLastByte(SPICNT_DEVICE_TOUCH | SPICNT_SPEED_4_MHZ, data);
}
