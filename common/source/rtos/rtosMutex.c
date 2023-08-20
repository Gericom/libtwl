#include <nds.h>
#include "libtwl/rtos/rtosThread.h"
#include "libtwl/rtos/rtosIrq.h"
#include "libtwl/rtos/rtosMutex.h"

void rtos_createMutex(rtos_mutex_t* mutex)
{
    mutex->obj.prev = NULL;
    mutex->obj.next = NULL;
    mutex->obj.type = RTOS_OBJECT_TYPE_MUTEX;
    mutex->lockCount = 0;
    mutex->owner = NULL;
    mutex->queue.head = NULL;
}

void rtos_lockMutex(rtos_mutex_t* mutex)
{
    u32 irq = rtos_disableIrqs();

    rtos_thread_t* curThread = rtos_getCurThread();

    if (mutex->owner == curThread)
    {
        mutex->lockCount++;
        rtos_restoreIrqs(irq);
        return;
    }

    while (1)
    {
        if (mutex->lockCount == 0)
        {
            mutex->owner = curThread;
            mutex->lockCount = 1;
            mutex->obj.prev = NULL;
            mutex->obj.next = curThread->objListHead;
            if (curThread->objListHead)
                curThread->objListHead->prev = &mutex->obj;
            curThread->objListHead = &mutex->obj;
            break;
        }
        rtos_queueThread(rtos_getCurThread(), &mutex->queue);
    }

    rtos_restoreIrqs(irq);
}

bool rtos_tryLockMutex(rtos_mutex_t* mutex)
{
    u32 irq = rtos_disableIrqs();

    rtos_thread_t* curThread = rtos_getCurThread();

    if (mutex->owner == curThread)
    {
        mutex->lockCount++;
        rtos_restoreIrqs(irq);
        return true;
    }

    if (mutex->lockCount == 0)
    {
        mutex->owner = curThread;
        mutex->lockCount = 1;
        mutex->obj.prev = NULL;
        mutex->obj.next = curThread->objListHead;
        if (curThread->objListHead)
            curThread->objListHead->prev = &mutex->obj;
        curThread->objListHead = &mutex->obj;
        rtos_restoreIrqs(irq);
        return true;
    }

    rtos_restoreIrqs(irq);
    return false;
}

void rtos_unlockMutex(rtos_mutex_t* mutex)
{
    u32 irq = rtos_disableIrqs();

    if (--mutex->lockCount == 0)
    {
        mutex->owner = NULL;
        rtos_wakeupQueue(&mutex->queue);
    }

    rtos_restoreIrqs(irq);
}
