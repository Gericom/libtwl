.text
.thumb

.global swi_waitByLoop
.type swi_waitByLoop, %function
swi_waitByLoop:
    swi #3
    bx lr
