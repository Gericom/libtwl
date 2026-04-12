#pragma once

#ifdef __cplusplus
extern "C" {
#endif

extern void swi_waitByLoop(u32 iterations);
extern u16 swi_getCrc16(u16 initialCrcValue, const void* src, u32 length);

#ifdef __cplusplus
}
#endif
