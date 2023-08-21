#pragma once

#include <stdint.h>
#include "feature.h"

#define unlikely(x) __builtin_expect((x), 0)
#define likely(x) __builtin_expect((x), 1)

#define UNUSED __attribute__((unused))

#define MASK(n) (~((~0UL << (n))))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

/* Ensure that __builtin_clz is never called with 0 argument */
static inline int ilog2(uint32_t x)
{
    // FIXME: likely inefficient (but also rarely used...)
#if C64
    uint8_t lz=0;
    while(x>>=1)
	lz++;
    return lz;
#else
    return 31 - __builtin_clz(x | 1);
#endif
}

/* Range check
 * For any variable range checking:
 *     if (x >= minx && x <= maxx) ...
 * it is faster to use bit operation:
 *     if ((signed)((x - minx) | (maxx - x)) >= 0) ...
 */
#define RANGE_CHECK(x, minx, size) \
    ((int32_t) ((x - minx) | (minx + size - 1 - x)) >= 0)
