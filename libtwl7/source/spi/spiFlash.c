#include <nds/ndstypes.h>
#include "libtwl/spi/spiFlash.h"

u32 flash_getStatus(void)
{
    // Status command
    spi_transferByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, FLASH_CMD_STATUS);

    // Read status value and release chip select
    return spi_transferLastByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, 0);
}

void flash_readBytes(u32 flashAddress, u8* destination, u32 length)
{
    if (length == 0)
        return;

    // Read command
    spi_transferByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, FLASH_CMD_READ);

    // Address
    spi_transferByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, (flashAddress >> 16) & 0xFF);
    spi_transferByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, (flashAddress >> 8) & 0xFF);
    spi_transferByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, flashAddress & 0xFF);

    // Receive data
    for (u32 i = 0; i < length - 1; i++) 
    {
        *destination++ = spi_transferByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, 0);
    }

    // Release chip select on last byte
    *destination = spi_transferLastByte(SPICNT_DEVICE_FLASH | SPICNT_SPEED_4_MHZ, 0);
}
