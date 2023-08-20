#pragma once
#include "rtosObject.h"
#include "rtosThread.h"

typedef struct
{
    rtos_object_t obj;
    volatile u16 lockCount;
    rtos_thread_t* owner;
    rtos_thread_queue_t queue;
} rtos_mutex_t;

#ifdef __cplusplus
extern "C" {
#endif

void rtos_createMutex(rtos_mutex_t* mutex);
void rtos_lockMutex(rtos_mutex_t* mutex);
bool rtos_tryLockMutex(rtos_mutex_t* mutex);
void rtos_unlockMutex(rtos_mutex_t* mutex);

#ifdef __cplusplus
}
#endif
