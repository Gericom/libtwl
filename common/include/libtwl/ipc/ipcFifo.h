#pragma once

#define IPCFIFOCNT_SEND_FIFO_EMPTY          (1 << 0)
#define IPCFIFOCNT_SEND_FIFO_FULL           (1 << 1)
#define IPCFIFOCNT_SEND_FIFO_EMPTY_IRQ      (1 << 2)
#define IPCFIFOCNT_SEND_FIFO_CLEAR          (1 << 3)

#define IPCFIFOCNT_RECV_FIFO_EMPTY          (1 << 8)
#define IPCFIFOCNT_RECV_FIFO_FULL           (1 << 9)
#define IPCFIFOCNT_RECV_FIFO_NOT_EMPTY_IRQ  (1 << 10)

#define IPCFIFOCNT_ERROR                    (1 << 14)
#define IPCFIFOCNT_ENABLE                   (1 << 15)

#define REG_IPCFIFOCNT     (*(vu32*)0x04000184)

#define REG_IPCFIFOSEND    (*(vu32*)0x04000188)
#define REG_IPCFIFORECV    (*(vu32*)0x04100000)

#ifdef __cplusplus
extern "C" {
#endif

static inline bool ipc_isSendFifoEmpty(void)
{
    return REG_IPCFIFOCNT & IPCFIFOCNT_SEND_FIFO_EMPTY;
}

static inline bool ipc_isSendFifoFull(void)
{
    return REG_IPCFIFOCNT & IPCFIFOCNT_SEND_FIFO_FULL;
}

static inline void ipc_enableSendFifoEmptyIrq(void)
{
    REG_IPCFIFOCNT |= IPCFIFOCNT_SEND_FIFO_EMPTY_IRQ;
}

static inline void ipc_disableSendFifoEmptyIrq(void)
{
    REG_IPCFIFOCNT &= ~IPCFIFOCNT_SEND_FIFO_EMPTY_IRQ;
}

static inline void ipc_clearSendFifo(void)
{
    REG_IPCFIFOCNT |= IPCFIFOCNT_SEND_FIFO_CLEAR;
}

static inline bool ipc_isRecvFifoEmpty(void)
{
    return REG_IPCFIFOCNT & IPCFIFOCNT_RECV_FIFO_EMPTY;
}

static inline bool ipc_isRecvFifoFull(void)
{
    return REG_IPCFIFOCNT & IPCFIFOCNT_RECV_FIFO_FULL;
}

static inline void ipc_enableRecvFifoNotEmptyIrq(void)
{
    REG_IPCFIFOCNT |= IPCFIFOCNT_RECV_FIFO_NOT_EMPTY_IRQ;
}

static inline void ipc_disableRecvFifoNotEmptyIrq(void)
{
    REG_IPCFIFOCNT &= ~IPCFIFOCNT_RECV_FIFO_NOT_EMPTY_IRQ;
}

static inline bool ipc_isFifoError(void)
{
    return REG_IPCFIFOCNT & IPCFIFOCNT_ERROR;
}

static inline void ipc_ackFifoError(void)
{
    REG_IPCFIFOCNT |= IPCFIFOCNT_ERROR;
}

static inline void ipc_enableFifo(void)
{
    REG_IPCFIFOCNT |= IPCFIFOCNT_ENABLE;
}

static inline void ipc_disableFifo(void)
{
    REG_IPCFIFOCNT &= ~IPCFIFOCNT_ENABLE;
}

static inline void ipc_sendWordDirect(u32 word)
{
    REG_IPCFIFOSEND = word;
}

static inline u32 ipc_recvWordDirect(void)
{
    return REG_IPCFIFORECV;
}

#ifdef __cplusplus
}
#endif
