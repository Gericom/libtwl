#pragma once

/// @brief Sets the volume of the sound channel.
#define SOUNDCNT_VOLUME(x)      ((x) << 0)

/// @brief No shift is applied to samples (100% volume).
#define SOUNDCNT_SHIFT_0        (0 << 8)
/// @brief Sample values are shifted right by 1 (50% volume).
#define SOUNDCNT_SHIFT_1        (1 << 8)
/// @brief Sample values are shifted right by 2 (25% volume).
#define SOUNDCNT_SHIFT_2        (2 << 8)
/// @brief Sample values are shifted right by 4 (6.25% volume).
#define SOUNDCNT_SHIFT_4        (3 << 8)

/// @brief When set the last sample value keeps being output when
///        playback ends in SOUNDCNT_MODE_ONCE.
/// @note  This is bugged in the sense that when restarting the
///        channel it will stop outputting for a few samples.
#define SOUNDCNT_HOLD           (1 << 15)

/// @brief Sets the pan of the sound channel. 0 = left, 127 = right.
/// @note  The pan is actually the volume ratio between the left and right
///        speaker. When setting center (64) the volume level will
///        be 50% on each speaker. To get full volume for mono sounds
///        you need two sound channels.
#define SOUNDCNT_PAN(x)         ((x) << 16)

/// @brief Square wave duty cycle of 12.5%.
#define SOUNDCNT_DUTY_12_5      (0 << 24)
/// @brief Square wave duty cycle of 25.0%.
#define SOUNDCNT_DUTY_25_0      (1 << 24)
/// @brief Square wave duty cycle of 37.5%.
#define SOUNDCNT_DUTY_37_5      (2 << 24)
/// @brief Square wave duty cycle of 50.0%.
#define SOUNDCNT_DUTY_50_0      (3 << 24)
/// @brief Square wave duty cycle of 62.5%.
#define SOUNDCNT_DUTY_62_5      (4 << 24)
/// @brief Square wave duty cycle of 75.0%.
#define SOUNDCNT_DUTY_75_0      (5 << 24)
/// @brief Square wave duty cycle of 87.5%.
#define SOUNDCNT_DUTY_87_5      (6 << 24)

#define SOUNDCNT_DUTY_MASK      (3 << 24)

/// @brief The sound channel must be manually stopped.
#define SOUNDCNT_MODE_MANUAL    (0 << 27)
/// @brief The sound channel plays PNT once, then loops LEN infinitely.
#define SOUNDCNT_MODE_LOOP      (1 << 27)
/// @brief The sound channel stops automatically when the end is reached (PNT + LEN).
#define SOUNDCNT_MODE_ONCE      (2 << 27)

/// @brief Signed 8 bit PCM.
/// @note  PCM8 value 0xAB is treated as PCM16 value 0xAB00.
#define SOUNDCNT_FORMAT_PCM8    (0 << 29)
/// @brief Signed 16 bit PCM.
#define SOUNDCNT_FORMAT_PCM16   (1 << 29)
/// @brief IMA-ADPCM.
#define SOUNDCNT_FORMAT_ADPCM   (2 << 29)
/// @brief Not available on channels 0-7, square wave on channels 8-13, noise on channels 14-15.
#define SOUNDCNT_FORMAT_PSG     (3 << 29)

/// @brief Gets or sets whether the channel is currently playing.
#define SOUNDCNT_ENABLED        (1 << 31)

#ifdef LIBTWL_ARM7

/// @brief Sound channel x control register.
#define REG_SOUNDxCNT(x)        (*(vu32*)(0x04000400 + (x) * 0x10))

/// @brief Sound channel x source address register.
#define REG_SOUNDxSAD(x)        (*(vu32*)(0x04000404 + (x) * 0x10))

/// @brief Sound channel x timer register.
/// @note  Reload value of an increasing timer that runs at 16756991 Hz.
///        A new sample is fetched when the timer overflows.
///        Usually computed as -16756991 / frequency.
#define REG_SOUNDxTMR(x)        (*(vu16*)(0x04000408 + (x) * 0x10))

/// @brief Sound channel x loop point register.
/// @note  Counted in 32 bit words.
#define REG_SOUNDxPNT(x)        (*(vu16*)(0x0400040A + (x) * 0x10))

/// @brief Sound channel x length register.
/// @note  Counted in 32 bit words. Minimum length is 4 words (=16 bytes).
#define REG_SOUNDxLEN(x)        (*(vu32*)(0x0400040C + (x) * 0x10))

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Starts the given sound channel.
/// @param channel The channel to start.
static inline void snd_startChannel(u32 channel)
{
    REG_SOUNDxCNT(channel) |= SOUNDCNT_ENABLED;
}

/// @brief Stops the given sound channel.
/// @param channel The channel to stop.
static inline void snd_stopChannel(u32 channel)
{
    REG_SOUNDxCNT(channel) &= ~SOUNDCNT_ENABLED;
}

/// @brief Checks whether the given sound channel is playing.
/// @param channel The channel to check.
/// @return True if the channel is playing, or false otherwise.
static inline bool snd_isChannelPlaying(u32 channel)
{
    return REG_SOUNDxCNT(channel) & SOUNDCNT_ENABLED;
}

/// @brief Sets the volume of the given sound channel.
/// @param channel The channel to set the volume of.
/// @param volume The volume to set.
static inline void snd_setChannelVolume(u32 channel, u32 volume)
{
    ((vu8*)&REG_SOUNDxCNT(channel))[0] = volume;
}

/// @brief Sets the shift of the given sound channel.
/// @param channel The channel to set the shift of.
/// @param shift The shift to set.
static inline void snd_setChannelShift(u32 channel, u32 shift)
{
    REG_SOUNDxCNT(channel) = (REG_SOUNDxCNT(channel) & ~SOUNDCNT_SHIFT_4) | shift;
}

/// @brief Sets the pan of the given sound channel.
/// @param channel The channel to set the pan of.
/// @param pan The pan to set.
static inline void snd_setChannelPan(u32 channel, u32 pan)
{
    ((vu8*)&REG_SOUNDxCNT(channel))[2] = pan;
}

/// @brief Sets the timer value of the given sound channel.
/// @param channel The channel to set the timer value of.
/// @param timer The timer value to set.
static inline void snd_setChannelTimer(u32 channel, u16 timer)
{
    REG_SOUNDxTMR(channel) = timer;
}

/// @brief Sets the square wave duty cycle of the given sound channel.
/// @param channel The channel to set the duty cyle value of.
/// @param duty The duty cycle value to set.
static inline void snd_setChannelDuty(u32 channel, u32 duty)
{
    REG_SOUNDxCNT(channel) = (REG_SOUNDxCNT(channel) & ~SOUNDCNT_DUTY_MASK) | duty;
}

#ifdef __cplusplus
}
#endif

#endif
