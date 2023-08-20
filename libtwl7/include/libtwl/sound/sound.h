#pragma once

#define REG_SOUNDCNT                (*(vu32*)0x04000500)
#define REG_SOUNDBIAS               (*(vu32*)0x04000504)

#define SOUNDCNT_MASTER_VOLUME(x)   ((x) << 0)

#define SOUNDCNT_LEFT_OUT_MIXER     (0 << 8)
#define SOUNDCNT_LEFT_OUT_CH1       (1 << 8)
#define SOUNDCNT_LEFT_OUT_CH3       (2 << 8)
#define SOUNDCNT_LEFT_OUT_CH1_CH3   (3 << 8)

#define SOUNDCNT_RIGHT_OUT_MIXER    (0 << 10)
#define SOUNDCNT_RIGHT_OUT_CH1      (1 << 10)
#define SOUNDCNT_RIGHT_OUT_CH3      (2 << 10)
#define SOUNDCNT_RIGHT_OUT_CH1_CH3  (3 << 10)

#define SOUNDCNT_CH1_MIX_DISABLE    (1 << 12)
#define SOUNDCNT_CH3_MIX_DISABLE    (1 << 13)
#define SOUNDCNT_MASTER_ENABLE      (1 << 15)

#ifdef __cplusplus
extern "C" {
#endif

static inline void snd_setMasterVolume(u8 volume)
{
    *(vu8*)&REG_SOUNDCNT = volume;
}

static inline void snd_setOutputs(int left, int right)
{
    REG_SOUNDCNT = (REG_SOUNDCNT & ~0xF00) | left | right;
}

static inline void snd_setCh1ToMixer(bool outputToMixer)
{
    if (outputToMixer)
        REG_SOUNDCNT &= ~SOUNDCNT_CH1_MIX_DISABLE;
    else
        REG_SOUNDCNT |= SOUNDCNT_CH1_MIX_DISABLE;
}

static inline void snd_setCh3ToMixer(bool outputToMixer)
{
    if (outputToMixer)
        REG_SOUNDCNT &= ~SOUNDCNT_CH3_MIX_DISABLE;
    else
        REG_SOUNDCNT |= SOUNDCNT_CH3_MIX_DISABLE;
}

static inline void snd_setMasterEnable(bool enabled)
{
    if (enabled)
        REG_SOUNDCNT |= SOUNDCNT_MASTER_ENABLE;
    else
        REG_SOUNDCNT &= ~SOUNDCNT_MASTER_ENABLE;
}

#ifdef __cplusplus
}
#endif