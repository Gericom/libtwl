#pragma once

#define REG_SNDCAP0CNT      (*(vu8*)0x04000508)
#define REG_SNDCAP1CNT      (*(vu8*)0x04000509)
#define REG_SNDCAP0DAD      (*(vu32*)0x04000510)
#define REG_SNDCAP0LEN      (*(vu32*)0x04000514)
#define REG_SNDCAP1DAD      (*(vu32*)0x04000518)
#define REG_SNDCAP1LEN      (*(vu32*)0x0400051C)

#define SNDCAP0CNT_CH0_ADD_CH1      (1 << 0)

#define SNDCAP1CNT_CH2_ADD_CH3      (1 << 0)

#define SNDCAP0CNT_SRC_LEFT_MIXER   (0 << 1)
#define SNDCAP0CNT_SRC_CH0          (1 << 1)

#define SNDCAP1CNT_SRC_RIGHT_MIXER  (0 << 1)
#define SNDCAP1CNT_SRC_CH2          (1 << 1)

#define SNDCAPCNT_REPEAT_LOOP       (0 << 2)
#define SNDCAPCNT_REPEAT_OFF        (1 << 2)

#define SNDCAPCNT_FORMAT_PCM16      (0 << 3)
#define SNDCAPCNT_FORMAT_PCM8       (1 << 3)

#define SNDCAPCNT_ENABLE            (1 << 7)
#define SNDCAPCNT_BUSY              (1 << 7)