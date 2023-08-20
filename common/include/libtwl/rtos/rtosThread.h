#pragma once
#include "rtosState.h"
#include "rtosObject.h"

enum
{
    RTOS_THREAD_STATE_SLEEPING,
    RTOS_THREAD_STATE_WAITING,
    RTOS_THREAD_STATE_READY,
    RTOS_THREAD_STATE_RUNNING,
    RTOS_THREAD_STATE_DEAD
};

struct rtos_thread_t;

typedef struct
{
    u32 divNumerLo;
    u32 divNumerHi;
    u32 divDenomLo;
    u32 divDenomHi;
    u16 sqrtCnt;
    u16 divCnt;
    u32 sqrtParamLo;
    u32 sqrtParamHi;
} math_div_sqrt_state_t;

typedef struct
{
    struct rtos_thread_t* head;
} rtos_thread_queue_t;

typedef struct rtos_thread_t
{
    u32 r[16];
    u32 cpsr;
#ifdef LIBTWL_ARM9
    math_div_sqrt_state_t divSqrtState;
#endif
    struct rtos_thread_t* prev;
    struct rtos_thread_t* next;
    u8 priority;
    u8 state;
    rtos_object_t* objListHead;
    rtos_thread_queue_t* inQueue;
    rtos_thread_queue_t joinQueue;
} rtos_thread_t;

#ifdef __cplusplus
extern "C" {
#endif

void rtos_startMainThread(void);
void rtos_createThread(rtos_thread_t* thread, u8 priority, void (*mainFunc)(void*), void* arg, u32* stack, u32 stackSize);
void rtos_wakeupThread(rtos_thread_t* thread);
void rtos_sleepThread(rtos_thread_t* thread);
void rtos_joinThread(rtos_thread_t* thread);
void rtos_queueThread(rtos_thread_t* thread, rtos_thread_queue_t* queue);
void rtos_wakeupQueue(rtos_thread_queue_t* queue);

static inline rtos_thread_t* rtos_getCurThread(void)
{
    return gRtosState.curThread;
}

static inline u8 rtos_getThreadPriority(const rtos_thread_t* thread)
{
    return thread->priority;
}

#ifdef __cplusplus
}
#endif
