.text
.arm

//r0=command
//r1=params pointer (64 bytes)
.global gx_fifoSend64
.type gx_fifoSend64, %function
gx_fifoSend64:
    push {r4-r7,lr}
    mov r12, #0x04000000
    str r0, [r12, #0x400]! // REG_GXFIFO
    ldmia r1!, {r0,r2-r7,lr}
    stmia r12, {r0,r2-r7,lr}
    ldmia r1!, {r0,r2-r7,lr}
    stmia r12, {r0,r2-r7,lr}
    pop {r4-r7,pc}

//r0=command
//r1=params pointer (48 bytes)
.global gx_fifoSend48
.type gx_fifoSend48, %function
gx_fifoSend48:
    push {r4,r5,lr}
    mov r12, #0x04000000
    str r0, [r12, #0x400]! // REG_GXFIFO
    ldmia r1!, {r0,r2-r5,lr}
    stmia r12, {r0,r2-r5,lr}
    ldmia r1!, {r0,r2-r5,lr}
    stmia r12, {r0,r2-r5,lr}
    pop {r4,r5,pc}

//r0=command
//r1=params pointer (36 bytes)
.global gx_fifoSend36
.type gx_fifoSend36, %function
gx_fifoSend36:
    push {lr}
    mov r12, #0x04000000
    str r0, [r12, #0x400]! // REG_GXFIFO
    ldmia r1!, {r0,r2,r3,lr}
    stmia r12, {r0,r2,r3,lr}
    ldmia r1, {r0-r3,lr}
    stmia r12, {r0-r3,lr}
    pop {pc}

.pool
.end
