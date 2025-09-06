#pragma once

#define REG_SCFG_A9ROM  (*(vu8*)0x04004000)
#define REG_SCFG_A7ROM  (*(vu8*)0x04004001)
#define REG_SCFG_CLK    (*(vu16*)0x04004004)

#ifdef LIBTWL_ARM9

#define REG_SCFG_RST    (*(vu16*)0x04004006)

#else

#define REG_SCFG_JTAG   (*(vu16*)0x04004006)

#endif

#define REG_SCFG_EXT    (*(vu32*)0x04004008)

#define SCFG_A9ROM_DISABLE_SECURE       (1 << 0)
#define SCFG_A9ROM_NITRO                (1 << 1)

#ifdef LIBTWL_ARM7

#define SCFG_A7ROM_DISABLE_SECURE       (1 << 0)
#define SCFG_A7ROM_NITRO                (1 << 1)
#define SCFG_A7ROM_DISABLE_FUSE         (1 << 2)

#define SCFG_CLK_AES                    (1 << 2)

#define SCFG_EXT_AES                    (1 << 17)

#endif