#pragma once

struct rtos_thread_t;

typedef struct
{
    void* irqTable[32];
#ifdef LIBTWL_ARM7
    void* irq2Table[32];
#endif
    u32 irqDepth;
    struct rtos_thread_t* threadReadyList;
    struct rtos_thread_t* curThread;
} rtos_state_t;

extern rtos_state_t gRtosState;
