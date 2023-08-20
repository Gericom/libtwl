#include <nds.h>
#include "libtwl/rtos/rtosThread.h"
#include "libtwl/rtos/rtosIrq.h"
#include "libtwl/rtos/rtosEvent.h"

void rtos_createEvent(rtos_event_t* event)
{
    event->flag = false;
    event->queue.head = NULL;
}

void rtos_signalEvent(rtos_event_t* event)
{
    u32 irq = rtos_disableIrqs();

    if (event->flag)
    {
        rtos_restoreIrqs(irq);
        return;
    }

    event->flag = true;
    rtos_wakeupQueue(&event->queue);

    rtos_restoreIrqs(irq);
}

void rtos_waitEvent(rtos_event_t* event, bool waitNew, bool clearAfter)
{
    u32 irq = rtos_disableIrqs();

    if (!waitNew && event->flag)
    {
        if (clearAfter)
            event->flag = false;
        rtos_restoreIrqs(irq);
        return;
    }

    event->flag = false;

    rtos_queueThread(rtos_getCurThread(), &event->queue);

    if (clearAfter)
        event->flag = false;

    rtos_restoreIrqs(irq);
}
