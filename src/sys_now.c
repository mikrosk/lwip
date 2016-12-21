#include "lwip/sys.h"

#include <time.h>

u32_t sys_now(void) {
    clock_t ticks = clock();
    // 5ms resolution
    return (u32_t)(ticks * 1000 / CLOCKS_PER_SEC);
}
