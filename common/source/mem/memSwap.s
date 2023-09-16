.text
.arm

.global mem_swapByte
.type mem_swapByte, %function
mem_swapByte:
    swpb r0, r0, [r1]
    bx lr

.global mem_swapWord
.type mem_swapWord, %function
mem_swapWord:
    swp r0, r0, [r1]
    bx lr
