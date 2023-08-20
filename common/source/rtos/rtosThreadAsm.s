#ifdef LIBTWL_ARM9
.section .itcm
#endif
#ifdef LIBTWL_ARM7
.text
#endif
.arm

//r0=cur
//r1=new
.global rtos_switchThreads
rtos_switchThreads:
    add r0, r0, #16
    stmia r0!, {r4-r12,sp}
    mov r2, lr
    mrs r3, cpsr
    stmib r0!, {r2,r3} //pc,cpsr

#ifdef LIBTWL_ARM9
    //div/sqrt state
    mov r2, #0x04000000
    add r2, r2, #0x290
    ldmia r2, {r3-r12,sp,lr}
    ldr r7, [r2, #-0x10]
    ldr r8, [r1, #(16 * 4)]! //cpsr
    orr r11, r11, r7, lsl #16
    stmib r0, {r3-r6,r11,sp,lr}

    ldmib r1, {r3-r6,r11,sp,lr}
    stmia r2, {r3-r12,sp,lr}
    mov r3, r11, lsr #16
    strh r3, [r2, #-0x10]!

    ldr r3, [r2]
1:
    tst r3, #0x8000
    ldrne r3, [r2]
    bne 1b
#endif
#ifdef LIBTWL_ARM7
    ldr r8, [r1, #(16 * 4)]! //cpsr
#endif

    msr cpsr, #0xD3
    ldr lr, [r1, #-4]!
    msr spsr, r8
    ldmdb r1, {r0-r12,sp,lr}^
    nop
    movs pc, lr

.end