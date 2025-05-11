#ifndef _eecache_h_
#define _eecache_h_

#include <eekernel.h>
#include <libver.h>     // need SDK 2.4(+)

#if (SCE_LIBRARY_VERSION >= 0x3000)
// The following COP0 Cache definitions were removed from eekernel.h
// in version 2.3.0 (Jan.22,2003), however the syscalls are still present
// within libkernl.a(klib.o).

#ifndef INST_CACHE
#define INST_CACHE              2
#define DATA_CACHE              1
#define CacheOn()               EnableCache(INST_CACHE | DATA_CACHE)
#define CacheOff()              DisableCache(INST_CACHE | DATA_CACHE)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * COP0
 */

int EnableCache(int);           /* Future Use */
int DisableCache(int);          /* Future Use */

#ifdef __cplusplus
}
#endif

#endif
#endif // _eecache_h_
