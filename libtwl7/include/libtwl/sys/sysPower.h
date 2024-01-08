#pragma once

#define POWCNT_SOUND_ENABLE         (1 << 0)
#define POWCNT_WIFI_ENABLE          (1 << 1)

#define REG_POWCNT                  (*(vu16*)0x04000304)

#ifdef __cplusplus
extern "C" {
#endif

static inline void sys_setSoundPower(bool enabled)
{
    if (enabled)
        REG_POWCNT |= POWCNT_SOUND_ENABLE;
    else
        REG_POWCNT &= ~POWCNT_SOUND_ENABLE;
}

static inline void sys_setWifiPower(bool enabled)
{
    if (enabled)
        REG_POWCNT |= POWCNT_WIFI_ENABLE;
    else
        REG_POWCNT &= ~POWCNT_WIFI_ENABLE;
}

#ifdef __cplusplus
}
#endif
