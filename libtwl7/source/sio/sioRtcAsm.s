.text
.arm

.global rtc_waitByLoop
.type rtc_waitByLoop, %function
rtc_waitByLoop:
    subs r0, r0, #1
    bge rtc_waitByLoop
    bx lr
