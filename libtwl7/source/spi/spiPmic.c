#include <nds.h>
#include "libtwl/spi/spi.h"
#include "libtwl/spi/spiPmic.h"

u8 pmic_readRegister(u8 reg)
{
    spi_transferByte(SPICNT_DEVICE_PMIC | SPICNT_SPEED_1_MHZ, reg | (1 << 7));
    return spi_transferLastByte(SPICNT_DEVICE_PMIC | SPICNT_SPEED_1_MHZ, 0);
}

void pmic_writeRegister(u8 reg, u8 data)
{
    spi_transferByte(SPICNT_DEVICE_PMIC | SPICNT_SPEED_1_MHZ, reg);
    spi_transferLastByte(SPICNT_DEVICE_PMIC | SPICNT_SPEED_1_MHZ, data);
}
