#ifndef __MGS3_MGS_DEFS_H__
#define __MGS3_MGS_DEFS_H__

#include <stddef.h>     // for NULL
#include <limits.h>

// NOTE: ee-gcc 2.9/2.96's limits.h wrongly defines the minimum and maximum
// values of 'long int' as if it were 32-bits wide, when it's actually 64-bits.
// This problem was fixed with ee-gcc 3.2.

/* MSVC defines _countof as an extension to stdlib.h */
#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif
/* alternate names without the leading underscore */
#define countof(array)  _countof(array)
#define COUNTOF(array)  _countof(array)

/*---------------------------------------------------------------------------*/
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html

#if defined(__GNUC__)
#if defined(__GNUC_PATCHLEVEL__) // GCC 3.0
#  define GCC_VERSION ((__GNUC__       * 10000)\
                      +(__GNUC_MINOR__ *   100)\
                      +(__GNUC_PATCHLEVEL__))
#else
#  define GCC_VERSION ((__GNUC__       * 10000)\
                      +(__GNUC_MINOR__ *   100))
#endif // __GNUC_PATCHLEVEL__
#else
#  define GCC_VERSION 0
#endif // __GNUC__

// Stolen from <features.h>
/* Macro to test version of GCC.  Returns 0 for non-GCC or too old GCC. */
#ifndef __GNUC_PREREQ
#  if defined(__GNUC__) && defined(__GNUC_MINOR__)
#    define __GNUC_PREREQ(maj, min) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#  else
#    define __GNUC_PREREQ(maj, min) 0
#  endif
#endif /* __GNUC_PREREQ */
/* Version with trailing underscores for BSD compatibility. */
#ifndef __GNUC_PREREQ__
#define __GNUC_PREREQ__(maj, min) __GNUC_PREREQ(maj, min)
#endif

/*---------------------------------------------------------------------------*/
// Common Macro #defines

#ifndef MIN
#define MIN(x, y)       (((x) < (y)) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y)       (((x) > (y)) ? (x) : (y))
#endif
#ifndef ABS
#define ABS(x)          (((x) < 0) ? -(x) : (x))
#endif

#define SIGN(x)         (((x) > 0) - ((x) < 0))
//#define SIGN(x)       (((x) < 0) ? -1 : ((x) > 0) ? 1 : 0)
//#define SIGN(x)       (((x) < 0) ? -1 : !!(x))

#ifndef CLAMP
#define CLAMP(x, min, max) (MAX(MIN(x, max), min))
//#define CLAMP(x, min, max) (((x) < (min)) ? (min) : ((x) > (max)) ? (max) : (x))
//#define CLAMP(x, min, max) (((x) > (max)) ? (max) : ((x) < (min)) ? (min) : (x))
#endif

/* Macros for counting and rounding. */
#ifndef HOWMANY
#define HOWMANY(x,y)    (((x) + ((y) - 1)) / (y))
#endif
#ifndef POWEROF2
#define POWEROF2(x)     ((((x) - 1) & (x)) == 0)
#endif
/* rounds to any y */
#ifndef ROUNDUP
#define ROUNDUP(x,y)    ((((x) + ((y) - 1)) / (y)) * (y))
#endif
#ifndef ROUNDDOWN
#define ROUNDDOWN(x,y)  (((x) / (y)) * (y))
#endif
/* if y is a power of two */
#ifndef ROUNDUP2
#define ROUNDUP2(x,y)   (((x) + ((y) - 1)) & ~((y) - 1))
#endif
#ifndef ROUNDDOWN2
#define ROUNDDOWN2(x,y) ((x) & ~((y) - 1))
#endif

/*---------------------------------------------------------------------------*/
// Compiler attribute #defines

#if defined(__GNUC__)
#define ALIGN(_x)       __attribute__((aligned(_x)))
#define PACKED          __attribute__((packed))
#elif defined(_MSC_VER)
#define ALIGN(_x)       __declspec(align(_x))
#define PACKED          /* discard */
#else
#define ALIGN(_x)       /* discard */
#define PACKED          /* discard */
#endif
/* common alignments */
#define ALIGN8          ALIGN(8)
#define ALIGN16         ALIGN(16)
#define ALIGN64         ALIGN(64)
#define ALIGN128        ALIGN(128)

// You can also just use ((void)foo) to suppress warnings.
#if defined(__GNUC__)
#define UNUSED          __attribute__((unused))
#else
#define UNUSED          /* discard */
#endif

// #define USE_STATIC_KEYWORD
#ifdef USE_STATIC_KEYWORD
#define STATIC          static
#else
#define STATIC          /* fake keyword for documentation */
#endif

/*---------------------------------------------------------------------------*/

// This will crash the program with the intention of invoking
// the MTS exception handler screen (which was compiled out).
//
// I guess KCEJ chose to dereference 1 instead of 0 to distinguish
// exceptions raised intentionally from actual NULL-pointer dereferences.
// Notice that it's also writing to an unaligned memory address.
//
#define HANGUP()        (*(int *)1 = 0)

// TODO: Should these be wrapped with 'do {} while (0)'?
#ifdef DEBUG
#define ASSERT(cond)                                            \
    if (!(cond)) {                                              \
        /* todo: decompile */                                   \
        HANGUP();                                               \
    }

#define XASSERT(cond, mesg...)                                  \
    if (!(cond)) {                                              \
        /* todo: decompile */                                   \
        printf( mesg );                                         \
        HANGUP();                                               \
    }
#else // DEBUG
#define ASSERT(cond)            ((void)0)   // do {} while (0)
#define XASSERT(cond, mesg...)  ((void)0)   // do {} while (0)
#endif // DEBUG

/*---------------------------------------------------------------------------*/
// Color Format #defines

/* RGBA8888 format */
#ifdef WORDS_BIGENDIAN
#define RGBA_R_SHIFT    (24)
#define RGBA_G_SHIFT    (16)
#define RGBA_B_SHIFT    ( 8)
#define RGBA_A_SHIFT    ( 0)
#else
#define RGBA_R_SHIFT    ( 0)
#define RGBA_G_SHIFT    ( 8)
#define RGBA_B_SHIFT    (16)
#define RGBA_A_SHIFT    (24)
#endif

#define MAKE_RGBA(_r,_g,_b,_a)                                  \
        ((unsigned int)((((_r) & 0xff) << RGBA_R_SHIFT) |       \
                        (((_g) & 0xff) << RGBA_G_SHIFT) |       \
                        (((_b) & 0xff) << RGBA_B_SHIFT) |       \
                        (((_a) & 0xff) << RGBA_A_SHIFT)))

#define MAKE_RGB0(_r,_g,_b)     MAKE_RGBA(_r,_g,_b,0x00)
#define MAKE_RGBX(_r,_g,_b)     MAKE_RGBA(_r,_g,_b,0xff)
#define MAKE_RGBH(_r,_g,_b)     MAKE_RGBA(_r,_g,_b,0x80) /* half-alpha */

#define GET_R_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_R_SHIFT) & 0xff)
#define GET_G_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_G_SHIFT) & 0xff)
#define GET_B_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_B_SHIFT) & 0xff)
#define GET_A_FROM_RGBA(_rgba)  (((_rgba) >> RGBA_A_SHIFT) & 0xff)

/* ARGB8888 format */
#ifdef WORDS_BIGENDIAN
#define ARGB_A_SHIFT    (24)
#define ARGB_R_SHIFT    (16)
#define ARGB_G_SHIFT    ( 8)
#define ARGB_B_SHIFT    ( 0)
#else
#define ARGB_A_SHIFT    ( 0)
#define ARGB_R_SHIFT    ( 8)
#define ARGB_G_SHIFT    (16)
#define ARGB_B_SHIFT    (24)
#endif

#define MAKE_ARGB(_a,_r,_g,_b)                                  \
        ((unsigned int)((((_a) & 0xff) << ARGB_A_SHIFT) |       \
                        (((_r) & 0xff) << ARGB_R_SHIFT) |       \
                        (((_g) & 0xff) << ARGB_G_SHIFT) |       \
                        (((_b) & 0xff) << ARGB_B_SHIFT)))

#define MAKE_0RGB(_r,_g,_b)     MAKE_ARGB(0x00,_r,_g,_b)
#define MAKE_XRGB(_r,_g,_b)     MAKE_ARGB(0xff,_r,_g,_b)
#define MAKE_HRGB(_r,_g,_b)     MAKE_ARGB(0x80,_r,_g,_b) /* half-alpha */

#define GET_A_FROM_ARGB(_argb)  (((_argb) >> ARGB_A_SHIFT) & 0xff)
#define GET_R_FROM_ARGB(_argb)  (((_argb) >> ARGB_R_SHIFT) & 0xff)
#define GET_G_FROM_ARGB(_argb)  (((_argb) >> ARGB_G_SHIFT) & 0xff)
#define GET_B_FROM_ARGB(_argb)  (((_argb) >> ARGB_B_SHIFT) & 0xff)

/* common colors */
#define COLOR_BLACK     MAKE_RGB0(  0,  0,  0)
#define COLOR_WHITE     MAKE_RGB0(255,255,255)
#define COLOR_GRAY      MAKE_RGB0(128,128,128)
#define COLOR_RED       MAKE_RGB0(255,  0,  0)
#define COLOR_GREEN     MAKE_RGB0(  0,255,  0)
#define COLOR_BLUE      MAKE_RGB0(  0,  0,255)
#define COLOR_CYAN      MAKE_RGB0(  0,255,255)
#define COLOR_MAGENTA   MAKE_RGB0(255,  0,255)
#define COLOR_YELLOW    MAKE_RGB0(255,255,  0)

#endif // {{{ END OF FILE }}}
