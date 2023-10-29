#pragma once

#define REG_DISPCNT             (*(vu32*)0x04000000)

#define REG_MOSAIC              (*(vu16*)0x0400004C)
#define REG_BLDCNT              (*(vu16*)0x04000050)
#define REG_BLDALPHA            (*(vu16*)0x04000052)
#define REG_BLDY                (*(vu16*)0x04000054)
#define REG_DISPCAPCNT          (*(vu32*)0x04000064)
#define REG_MMEM_FIFO           (*(vu32*)0x04000068)
#define REG_MASTER_BRIGHT       (*(vu16*)0x0400006C)

#define REG_DISPCNT_SUB         (*(vu32*)0x04001000)

#define REG_MOSAIC_SUB          (*(vu16*)0x0400104C)
#define REG_BLDCNT_SUB          (*(vu16*)0x04001050)
#define REG_BLDALPHA_SUB        (*(vu16*)0x04001052)
#define REG_BLDY_SUB            (*(vu16*)0x04001054)
#define REG_MASTER_BRIGHT_SUB   (*(vu16*)0x0400106C)
