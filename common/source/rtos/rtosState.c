#include <nds.h>
#include "libtwl/rtos/rtosState.h"

#ifdef LIBTWL_ARM9
DTCM_BSS rtos_state_t gRtosState;
#endif
#ifdef LIBTWL_ARM7
rtos_state_t gRtosState;
#endif
