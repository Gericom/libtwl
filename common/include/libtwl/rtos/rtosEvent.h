#pragma once

#include "rtosThread.h"

typedef struct
{
    bool flag;
    rtos_thread_queue_t queue;
} rtos_event_t;

#ifdef __cplusplus
extern "C" {
#endif

void rtos_createEvent(rtos_event_t* event);
void rtos_signalEvent(rtos_event_t* event);

static inline void rtos_clearEvent(rtos_event_t* event)
{
    event->flag = false;
}

void rtos_waitEvent(rtos_event_t* event, bool waitNew, bool clearAfter);

#ifdef __cplusplus
}
#endif
