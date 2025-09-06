#pragma once

#define REG_I2SCNT                          (*(vu16*)0x04004700)

#define I2SCNT_MIX_RATIO_DSP_8_NITRO_0      (0 << 0)
#define I2SCNT_MIX_RATIO_DSP_7_NITRO_1      (1 << 0)
#define I2SCNT_MIX_RATIO_DSP_6_NITRO_2      (2 << 0)
#define I2SCNT_MIX_RATIO_DSP_5_NITRO_3      (3 << 0)
#define I2SCNT_MIX_RATIO_DSP_4_NITRO_4      (4 << 0)
#define I2SCNT_MIX_RATIO_DSP_3_NITRO_5      (5 << 0)
#define I2SCNT_MIX_RATIO_DSP_2_NITRO_6      (6 << 0)
#define I2SCNT_MIX_RATIO_DSP_1_NITRO_7      (7 << 0)
#define I2SCNT_MIX_RATIO_DSP_0_NITRO_8      (8 << 0)

#define I2SCNT_FREQUENCY_32728_HZ           (0 << 13)
#define I2SCNT_FREQUENCY_47605_HZ           (1 << 13)

#define I2SCNT_MUTE                         (1 << 14)

#define I2SCNT_ENABLE                       (1 << 15)
