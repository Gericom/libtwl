#include <nds.h>
#include "libtwl/rtos/rtosIrq.h"
#include "libtwl/ipc/ipcSync.h"
#include "libtwl/ipc/ipcFifo.h"
#include "libtwl/ipc/ipcFifoSystem.h"

#define HANDSHAKE_PART0     0xA
#define HANDSHAKE_PART1     0xB
#define HANDSHAKE_PART2     0xC

static ipc_fifo_ch_handler_func_t sHandlerFuncs[IPC_FIFO_MSG_CHANNEL_COUNT];
static void* sHandlerArgs[IPC_FIFO_MSG_CHANNEL_COUNT];

static void recvFifoNotEmptyIrq(u32 irqMask)
{
    while (!ipc_isRecvFifoEmpty())
    {
        u32 msg = ipc_recvWordDirect();
        u32 channel = msg & IPC_FIFO_MSG_CHANNEL_MASK;

        sHandlerFuncs[channel](channel, msg >> IPC_FIFO_MSG_CHANNEL_BITS, sHandlerArgs[channel]);
    }
}

static void dummyChannelHandler(u32 channel, u32 data, void* arg)
{

}

void ipc_initFifoSystem(void)
{
    for (int i = 0; i < IPC_FIFO_MSG_CHANNEL_COUNT; i++)
        sHandlerFuncs[i] = &dummyChannelHandler;

    u32 irqs = rtos_disableIrqs();
    {
        ipc_clearSendFifo();
        ipc_ackFifoError();
        ipc_enableRecvFifoNotEmptyIrq();
        ipc_enableFifo();

        rtos_ackIrqMask(RTOS_IRQ_IPC_FIFO_RECV);
        rtos_setIrqFunc(RTOS_IRQ_IPC_FIFO_RECV, recvFifoNotEmptyIrq);
        rtos_enableIrqMask(RTOS_IRQ_IPC_FIFO_RECV);

#ifdef LIBTWL_ARM9
        while (ipc_getArm7SyncBits() != HANDSHAKE_PART0);
        ipc_setArm9SyncBits(HANDSHAKE_PART0);
        while (ipc_getArm7SyncBits() != HANDSHAKE_PART1);
        ipc_setArm9SyncBits(HANDSHAKE_PART1);
        while (ipc_getArm7SyncBits() != HANDSHAKE_PART2);
        ipc_setArm9SyncBits(HANDSHAKE_PART2);
#endif
#ifdef LIBTWL_ARM7
        ipc_setArm7SyncBits(HANDSHAKE_PART0);
        while (ipc_getArm9SyncBits() != HANDSHAKE_PART0);
        ipc_setArm7SyncBits(HANDSHAKE_PART1);
        while (ipc_getArm9SyncBits() != HANDSHAKE_PART1);
        ipc_setArm7SyncBits(HANDSHAKE_PART2);
        while (ipc_getArm9SyncBits() != HANDSHAKE_PART2);
#endif
    }
    rtos_restoreIrqs(irqs);
}

void ipc_setChannelHandler(u32 channel, ipc_fifo_ch_handler_func_t handler, void* arg)
{
    if (handler == NULL)
        handler = &dummyChannelHandler;
    sHandlerFuncs[channel] = handler;
    sHandlerArgs[channel] = arg;
}

bool ipc_trySendFifoMessage(u32 channel, u32 data)
{
    u32 irqs = rtos_disableIrqs();
    if (ipc_isSendFifoFull())
    {
        rtos_restoreIrqs(irqs);
        return false;
    }
    ipc_sendWordDirect((channel & IPC_FIFO_MSG_CHANNEL_MASK) | (data << IPC_FIFO_MSG_CHANNEL_BITS));
    rtos_restoreIrqs(irqs);
    return true;
}

void ipc_sendFifoMessage(u32 channel, u32 data)
{
    while (!ipc_trySendFifoMessage(channel, data));
}