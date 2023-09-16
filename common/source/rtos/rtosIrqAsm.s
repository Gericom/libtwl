#ifdef LIBTWL_ARM9
.section ".itcm", "ax"
#endif
#ifdef LIBTWL_ARM7
.text
#endif
.arm

.global rtos_disableIrqs
rtos_disableIrqs:
    mrs r0, cpsr
    orr r1, r0, #0x80
    msr cpsr_c, r1
    bx lr

.global rtos_enableIrqs
rtos_enableIrqs:
    mrs r0, cpsr
    bic r1, r0, #0x80
    msr cpsr_c, r1
    bx lr

.global rtos_restoreIrqs
rtos_restoreIrqs:
    msr cpsr_c, r0
    bx lr

.global rtos_halt
rtos_halt:
#ifdef LIBTWL_ARM9
    mov r0, #0
    mcr p15, 0, r0, c7, c0, 4
#endif
#ifdef LIBTWL_ARM7
    swi #(6 << 16)
#endif
    bx lr

#ifdef LIBTWL_ARM9
#define RTOS_STATE_IRQ_DEPTH_OFFSET     (32 * 4)
#endif
#ifdef LIBTWL_ARM7
#define RTOS_STATE_IRQ2_TABLE_OFFSET    (32 * 4)
#define RTOS_STATE_IRQ_DEPTH_OFFSET     (64 * 4)
#endif

.global rtos_irqVector
rtos_irqVector:
#ifdef LIBTWL_ARM7
    //subtract 4 from the lr stored on the stack by the bios
    ldr lr, [sp, #(5 * 4)]
    ldr r2,= (gRtosState + RTOS_STATE_IRQ_DEPTH_OFFSET)
    sub lr, lr, #4
    str lr, [sp, #(5 * 4)]
#endif
#ifdef LIBTWL_ARM9
    sub lr, lr, #4
    push {r0-r3,r12,lr}
    ldr r2,= (gRtosState + RTOS_STATE_IRQ_DEPTH_OFFSET)
#endif
    mov r12, #0x04000000
    ldr r3, [r2] // irqDepth
    add r12, r12, #0x210
    ldmia r12!, {r0, r1} // REG_IE and REG_IF
    add r3, r3, #1
    str r3, [r2], #-RTOS_STATE_IRQ_DEPTH_OFFSET // irqDepth

    ands r0, r0, r1
#ifdef LIBTWL_ARM9
        beq finish
#endif
#ifdef LIBTWL_ARM7
        beq arm7_check_irq2
#endif

handle_irq:
    rsb r1, r0, #0
    and r0, r1, r0
#ifdef LIBTWL_ARM9
    clz r1, r0
#endif
#ifdef LIBTWL_ARM7
    ldr r1,= 0x04D7651F
    mul r1, r0, r1
    mov r1, r1, lsr #27
#endif
    ldr r1, [r2, r1, lsl #2] //handler function is never NULL so no check needed
    str r0, [r12, #-4] //ack
    
#ifdef LIBTWL_ARM7
    adr lr, finish
    bx r1

arm7_check_irq2:
    ldmia r12!, {r0, r1}
    add r2, r2, #RTOS_STATE_IRQ2_TABLE_OFFSET
    ands r0, r0, r1
        bne handle_irq
    // we fall through to finish here
#endif
#ifdef LIBTWL_ARM9
    blx r1
#endif

finish:
    ldr r12,= (gRtosState + RTOS_STATE_IRQ_DEPTH_OFFSET)
    ldmia r12, {r0, r1, r2} //irqDepth, threadReadyList, curThread
    subs r0, r0, #1
    str r0, [r12] //irqDepth
        ldmnefd sp!, {r0-r3,r12,pc}^ //if nested irq, no thread switch

    cmp r2, r1 //curThread == threadReadyList?
        ldmeqfd sp!, {r0-r3,r12,pc}^

irq_thread_switch:
    str r1, [r12, #8] // curThread = threadReadyList
    pop {r0,r3,r12,lr}
    stmia r2!, {r0,r3,r12,lr} // r0,r1,r2,r3
    pop {r12,lr}
    mrs r3, spsr
    str lr, [r2, #0x2C] // pc
    str r3, [r2, #0x30] // cpsr
    msr cpsr, #0xD3

#ifdef LIBTWL_ARM9
    stmia r2, {r4-r12,sp,lr}^

    //div/sqrt state
    mov r0, #0x04000000
    add r0, r0, #0x290
    ldmia r0, {r3-r12,sp,lr}
    ldr r7, [r0, #-0x10]
    add r2, r2, #0x34
    orr r11, r11, r7, lsl #16
    stmia r2, {r3-r6,r11,sp,lr}

    ldr r2, [r1, #(16 * 4)]!
    ldmib r1, {r3-r6,r11,sp,lr}
    stmia r0, {r3-r12,sp,lr}
    mov r3, r11, lsr #16
    strh r3, [r0, #-0x10]!

    ldr r3, [r0]
1:
    tst r3, #0x8000
    ldrne r3, [r0]
    bne 1b

    ldr lr, [r1, #-4]!
    msr spsr, r2
    ldmdb r1, {r0-r12,sp,lr}^
#endif
#ifdef LIBTWL_ARM7
    ldr r0, [r1, #(16 * 4)] // cpsr
    stmia r2, {r4-r12,sp,lr}^
    ldr lr, [r1, #(15 * 4)]
    msr spsr, r0
    ldmia r1, {r0-r12,sp,lr}^
#endif
    nop // safety for loading user regs
    movs pc, lr

.pool
.end
