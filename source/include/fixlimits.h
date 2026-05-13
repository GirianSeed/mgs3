#ifndef __fixlimits_h__
#define __fixlimits_h__

#include <limits.h>
#include "gcctest.h"

// NOTE: ee-gcc 2.9/2.96's limits.h wrongly defines the minimum and maximum
// values of 'long int' as if it were 32-bits wide, when it's actually 64-bits.
// This problem was fixed with ee-gcc 3.2.

#if (defined(__R5900__) || defined(__ee__)) && !__GNUC_PREREQ(3, 2)

/* Minimum and maximum values a `signed long int' can hold.  */
#undef __LONG_MAX__
#define __LONG_MAX__ 9223372036854775807L

#undef LONG_MIN
#define LONG_MIN (-LONG_MAX-1)
#undef LONG_MAX
#define LONG_MAX __LONG_MAX__

/* Maximum value an `unsigned long int' can hold.  (Minimum is 0).  */
#undef ULONG_MAX
#define ULONG_MAX (LONG_MAX * 2UL + 1)

#endif
#endif // {{{ END OF FILE }}}
