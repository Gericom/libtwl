#pragma once

#define IPCSYNC_REMOTE_DATA_MASK    (0xF << 0)
#define IPCSYNC_LOCAL_DATA_SHIFT    8
#define IPCSYNC_LOCAL_DATA_MASK     (0xF << IPCSYNC_LOCAL_DATA_SHIFT)

#define IPCSYNC_IRQ_TRIGGER         (1 << 13)
#define IPCSYNC_REMOTE_IRQ_ENABLE   (1 << 14)

#define REG_IPCSYNC     (*(vu32*)0x04000180)

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBTWL_ARM9

static inline u32 ipc_getArm7SyncBits(void)
{
    return REG_IPCSYNC & IPCSYNC_REMOTE_DATA_MASK;
}

static inline void ipc_setArm9SyncBits(u32 bits)
{
    REG_IPCSYNC = (REG_IPCSYNC & ~IPCSYNC_LOCAL_DATA_MASK) | ((bits & 0xF) << IPCSYNC_LOCAL_DATA_SHIFT);
}

static inline void ipc_enableArm7Irq(void)
{
    REG_IPCSYNC |= IPCSYNC_REMOTE_IRQ_ENABLE;
}

static inline void ipc_disableArm7Irq(void)
{
    REG_IPCSYNC &= ~IPCSYNC_REMOTE_IRQ_ENABLE;
}

static inline void ipc_triggerArm9Irq(void)
{
    REG_IPCSYNC |= IPCSYNC_IRQ_TRIGGER;
}

#endif

#ifdef LIBTWL_ARM7

static inline u32 ipc_getArm9SyncBits(void)
{
    return REG_IPCSYNC & IPCSYNC_REMOTE_DATA_MASK;
}

static inline void ipc_setArm7SyncBits(u32 bits)
{
    REG_IPCSYNC = (REG_IPCSYNC & ~IPCSYNC_LOCAL_DATA_MASK) | ((bits & 0xF) << IPCSYNC_LOCAL_DATA_SHIFT);
}

static inline void ipc_enableArm9Irq(void)
{
    REG_IPCSYNC |= IPCSYNC_REMOTE_IRQ_ENABLE;
}

static inline void ipc_disableArm9Irq(void)
{
    REG_IPCSYNC &= ~IPCSYNC_REMOTE_IRQ_ENABLE;
}

static inline void ipc_triggerArm7Irq(void)
{
    REG_IPCSYNC |= IPCSYNC_IRQ_TRIGGER;
}

#endif

#ifdef __cplusplus
}
#endif
