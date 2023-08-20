#pragma once

#define IPC_FIFO_MSG_CHANNEL_BITS   5
#define IPC_FIFO_MSG_CHANNEL_COUNT  (1 << IPC_FIFO_MSG_CHANNEL_BITS)
#define IPC_FIFO_MSG_CHANNEL_MASK   ((1 << IPC_FIFO_MSG_CHANNEL_BITS) - 1)

typedef void (*ipc_fifo_ch_handler_func_t)(u32 channel, u32 data, void* arg);

#ifdef __cplusplus
extern "C" {
#endif

void ipc_initFifoSystem(void);
void ipc_setChannelHandler(u32 channel, ipc_fifo_ch_handler_func_t handler, void* arg);

bool ipc_trySendFifoMessage(u32 channel, u32 data);
void ipc_sendFifoMessage(u32 channel, u32 data);

#ifdef __cplusplus
}
#endif
