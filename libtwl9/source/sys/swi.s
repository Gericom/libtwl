.text
.thumb

.global swi_waitByLoop
.type swi_waitByLoop, %function
swi_waitByLoop:
    swi #3
    bx lr

.global swi_getCrc16
.type swi_getCrc16, %function
swi_getCrc16:
    swi #0xE
    bx lr
