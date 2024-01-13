#pragma once
#include "spi.h"

#define FLASH_CMD_PAGE_PROGRAM              0x02
#define FLASH_CMD_READ                      0x03
#define FLASH_CMD_WRITE_DISABLE             0x04
#define FLASH_CMD_STATUS                    0x05
#define FLASH_CMD_WRITE_ENABLE              0x06
#define FLASH_CMD_PAGE_WRITE                0x0A
#define FLASH_CMD_READ_FAST                 0x0B
#define FLASH_CMD_READ_ID                   0x9F
#define FLASH_CMD_DEEP_WAKEUP               0xAB
#define FLASH_CMD_DEEP_SLEEP                0xB9
#define FLASH_CMD_SECTOR_ERASE              0xD8
#define FLASH_CMD_PAGE_ERASE                0xDB

#define FLASH_STATUS_WRITE_IN_PROGRESS      (1 << 0)
#define FLASH_STATUS_WRITE_ENABLED          (1 << 1)

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Reads the status register of the firmware flash.
/// @return The status register value.
u32 flash_getStatus(void);

/// @brief Reads length bytes from the given flashAddress to the given destination buffer.
/// @param flashAddress The address in firmware flash to start reading from.
/// @param destination A pointer to the destination buffer. Must support byte writes.
/// @param length The number of bytes to read.
void flash_readBytes(u32 flashAddress, u8* destination, u32 length);

#ifdef __cplusplus
}
#endif
