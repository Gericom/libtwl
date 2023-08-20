#include <nds.h>
#include "libtwl/rtos/rtosMutex.h"
#include "libtwl/rtos/rtosIrq.h"
#include "libtwl/rtos/rtosThread.h"

#ifdef LIBTWL_ARM9
static DTCM_BSS rtos_thread_t sMainThread;
#endif
#ifdef LIBTWL_ARM7
static rtos_thread_t sMainThread;
#endif
static rtos_thread_t sIdleThread;
static u32 sIdleStack[64];

static void insertReadyList(rtos_thread_t* thread)
{
    thread->state = RTOS_THREAD_STATE_READY;

    int prio = thread->priority;

    rtos_thread_t* t = gRtosState.threadReadyList;
    if (t->priority <= prio)
    {
        gRtosState.threadReadyList = thread;
        thread->prev = NULL;
        thread->next = t;
        t->prev = thread;
    }
    else
    {
        while (t->priority > prio)
            t = t->next;
        
        thread->next = t;
        rtos_thread_t* newPrev = t->prev;
        thread->prev = newPrev;
        t->prev = thread;
        newPrev->next = thread;
    }
}

static void idleMain(void* arg)
{
    while (true)
    {
        rtos_halt();
    }
}

void rtos_startMainThread(void)
{
    rtos_createThread(&sIdleThread, 0, idleMain, NULL, sIdleStack, sizeof(sIdleStack));
    sMainThread.inQueue = NULL;
    sMainThread.priority = 16;
    gRtosState.curThread = &sMainThread;
    gRtosState.threadReadyList = &sMainThread;
    gRtosState.threadReadyList->prev = NULL;
    gRtosState.threadReadyList->next = &sIdleThread;
    sIdleThread.prev = &sMainThread;
    sIdleThread.next = NULL;
    sIdleThread.state = RTOS_THREAD_STATE_READY;
    sMainThread.state = RTOS_THREAD_STATE_RUNNING;
}

extern void rtos_switchThreads(rtos_thread_t* cur, rtos_thread_t* new);

static void reschedule(void)
{
    if (gRtosState.curThread == gRtosState.threadReadyList || gRtosState.irqDepth)
        return;
    rtos_thread_t* cur = gRtosState.curThread;
    gRtosState.curThread = gRtosState.threadReadyList;
    gRtosState.curThread->state = RTOS_THREAD_STATE_RUNNING;
    rtos_switchThreads(cur, gRtosState.threadReadyList);
}

static void wakeupQueueWithoutReschedule(rtos_thread_queue_t* queue)
{
    rtos_thread_t* t = queue->head;
    while (t)
    {
        rtos_thread_t* next = t->next;
        t->inQueue = NULL;
        insertReadyList(t);
        t = next;
    }
    queue->head = NULL;
}

static void threadEnd(void)
{
    u32 irq = rtos_disableIrqs();

    rtos_thread_t* cur = gRtosState.curThread;

    cur->state = RTOS_THREAD_STATE_DEAD;
    gRtosState.threadReadyList = cur->next;
    cur->next->prev = NULL;
    cur->next = NULL;
    cur->prev = NULL;

    rtos_object_t* obj = cur->objListHead;
    while (obj)
    {
        rtos_object_t* next = obj->next;
        if (obj->type == RTOS_OBJECT_TYPE_MUTEX)
        {
            rtos_mutex_t* mutex = (rtos_mutex_t*)obj;
            mutex->owner = NULL;
            mutex->lockCount = 0;
            wakeupQueueWithoutReschedule(&mutex->queue);
        }
        obj->prev = NULL;
        obj->next = NULL;
        obj = next;
    }

    wakeupQueueWithoutReschedule(&cur->joinQueue);

    reschedule();

    //we'll never return here

    rtos_restoreIrqs(irq);
}

void rtos_createThread(rtos_thread_t* thread, u8 priority, void (*mainFunc)(void*), void* arg, u32* stack, u32 stackSize)
{
    u32* stackTop = (u32*)((u8*)stack + stackSize);
    thread->r[0] = (u32)arg;
    thread->r[13] = (u32)stackTop;
    thread->r[14] = (u32)threadEnd;
    thread->r[15] = (u32)mainFunc;
    thread->cpsr = /*0x13*/0x1F | (((u32)mainFunc & 1) ? 0x20 : 0); //cpsr, svc mode, irq and fiq on
    thread->next = NULL;
    thread->prev = NULL;
    thread->state = RTOS_THREAD_STATE_SLEEPING;
    thread->priority = priority;
    thread->objListHead = NULL;
    thread->inQueue = NULL;
    thread->joinQueue.head = NULL;
}

void rtos_wakeupThread(rtos_thread_t* thread)
{
    u32 irq = rtos_disableIrqs();

    if (thread->state != RTOS_THREAD_STATE_SLEEPING)
    {
        rtos_restoreIrqs(irq);
        return;
    }

    insertReadyList(thread);

    reschedule();

    rtos_restoreIrqs(irq);
}

void rtos_sleepThread(rtos_thread_t* thread)
{
    u32 irq = rtos_disableIrqs();

    if (thread == NULL)
        thread = gRtosState.curThread;
    
    if (thread->state == RTOS_THREAD_STATE_DEAD || thread->state == RTOS_THREAD_STATE_SLEEPING)
    {
        rtos_restoreIrqs(irq);
        return;
    }

    thread->state = RTOS_THREAD_STATE_SLEEPING;

    if (!thread->prev)
    {
        gRtosState.threadReadyList = thread->next;
        thread->next->prev = NULL;
        thread->next = NULL;
        thread->prev = NULL;
        reschedule();
    }
    else
    {
        thread->prev->next = thread->next;
        thread->next->prev = thread->prev;
        thread->next = NULL;
        thread->prev = NULL;
    }

    rtos_restoreIrqs(irq);
}

void rtos_joinThread(rtos_thread_t* thread)
{
    rtos_queueThread(rtos_getCurThread(), &thread->joinQueue);
}

void rtos_queueThread(rtos_thread_t* thread, rtos_thread_queue_t* queue)
{
    u32 irq = rtos_disableIrqs();

    thread->state = RTOS_THREAD_STATE_SLEEPING;
    thread->inQueue = queue;

    if (!thread->prev)
    {
        gRtosState.threadReadyList = thread->next;
        thread->next->prev = NULL;

        thread->next = queue->head;
        if (queue->head)
            queue->head->prev = thread;
        queue->head = thread;
        thread->prev = NULL;
        reschedule();
    }
    else
    {
        thread->prev->next = thread->next;
        thread->next->prev = thread->prev;

        thread->next = queue->head;
        if (queue->head)
            queue->head->prev = thread;
        queue->head = thread;
        thread->prev = NULL;
    }

    rtos_restoreIrqs(irq);
}

void rtos_wakeupQueue(rtos_thread_queue_t* queue)
{
    u32 irq = rtos_disableIrqs();

    wakeupQueueWithoutReschedule(queue);
    reschedule();

    rtos_restoreIrqs(irq);
}