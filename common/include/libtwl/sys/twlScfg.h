#pragma once

#define REG_SCFG_ROM    (*(vu16*)0x04004000)
#define REG_SCFG_CLK    (*(vu16*)0x04004004)

#ifdef LIBTWL_ARM9

#define REG_SCFG_RST    (*(vu16*)0x04004006)

#else

#define REG_SCFG_JTAG   (*(vu16*)0x04004006)

#endif

#define REG_SCFG_EXT    (*(vu32*)0x04004008)
