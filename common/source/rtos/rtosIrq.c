#include <nds.h>
#include "libtwl/rtos/rtosState.h"
#include "libtwl/math/mathUtil.h"
#include "libtwl/rtos/rtosIrq.h"

#ifdef LIBTWL_ARM7

#define ARM7_MAGIC_MUL      0x04D7651F
#define ARM7_MAGIC_SHIFT    27

#endif

static void irqDummyFunc(u32 irqMask)
{

}

void rtos_initIrq(void)
{
    REG_IME = 0;
    rtos_disableIrqs();
    
    rtos_disableIrqMask(~0);
    rtos_ackIrqMask(~0);
#ifdef LIBTWL_ARM7
    rtos_disableIrq2Mask(~0);
    rtos_ackIrq2Mask(~0);
#endif

    for (int i = 0; i < 32; i++)
        gRtosState.irqTable[i] = irqDummyFunc;

#ifdef LIBTWL_ARM7
    for (int i = 0; i < 32; i++)
        gRtosState.irq2Table[i] = irqDummyFunc;
#endif

    gRtosState.irqDepth = 0;

#ifdef LIBTWL_ARM9
    ((vu32*)&SystemVectors)[5] = (u32)&rtos_irqVector;
    setVectorBase(0);
#endif
#ifdef LIBTWL_ARM7
    BIOS_IRQ_HANDLER = (u32)&rtos_irqVector;
#endif

    rtos_enableIrqs();
    REG_IME = 1;
}

void rtos_setIrqFunc(u32 mask, rtos_irq_func_t func)
{
    if (!func)
        func = irqDummyFunc;
    while (mask)
    {
        u32 bit = (-mask) & mask;
        mask &= ~bit;
#ifdef LIBTWL_ARM9
        int idx = math_clz(bit);
#endif
#ifdef LIBTWL_ARM7
        int idx = (bit * ARM7_MAGIC_MUL) >> ARM7_MAGIC_SHIFT;
#endif
        gRtosState.irqTable[idx] = func;
    }    
}

#ifdef LIBTWL_ARM7
void rtos_setIrq2Func(u32 mask, rtos_irq_func_t func)
{
    if (!func)
        func = irqDummyFunc;
    while (mask)
    {
        u32 bit = (-mask) & mask;
        mask &= ~bit;
        int idx = (bit * ARM7_MAGIC_MUL) >> ARM7_MAGIC_SHIFT;
        gRtosState.irq2Table[idx] = func;
    }    
}
#endif
