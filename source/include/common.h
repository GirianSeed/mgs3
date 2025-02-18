#ifndef __MGS3_COMMON_H__
#define __MGS3_COMMON_H__

#include <stddef.h>
#include <sys/types.h>
#include <eetypes.h>

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

/* Macro to test version of GCC.  Returns 0 for non-GCC or too old GCC. */
#ifndef __GNUC_PREREQ
#  if defined(__GNUC__) && defined(__GNUC_MINOR__)
#    define __GNUC_PREREQ(maj, min) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#  else
#    define __GNUC_PREREQ(maj, min) 0
#  endif
#endif
/* Version with trailing underscores for BSD compatibility. */
#ifndef __GNUC_PREREQ__
#define __GNUC_PREREQ__(maj, min) __GNUC_PREREQ(maj, min)
#endif

/*---------------------------------------------------------------------------*/

#ifndef MIN
#define MIN(x, y)       (((x) < (y)) ? (x) : (y))
#endif
#ifndef MAX
#define MAX(x, y)       (((x) > (y)) ? (x) : (y))
#endif
#ifndef ABS
#define ABS(x)          (((x) >= 0) ? (x) : -(x))
#endif

#ifndef CLAMP
#define CLAMP(x, min, max) (MAX(MIN(x, max), min))
#endif

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif
#define countof(array)  _countof(array)
#define COUNTOF(array)  _countof(array)

#define PACKED          __attribute__((packed))
#define ALIGN(_x)       __attribute__((aligned(_x)))
#define ALIGN8          ALIGN(8)
#define ALIGN16         ALIGN(16)
#define ALIGN64         ALIGN(64)
#define ALIGN128        ALIGN(128)

/*---------------------------------------------------------------------------*/

#define HANGUP()        (*(int *)1 = 0)

#define ASSERT(cond)                                            \
    if (!(cond)) {                                              \
        /* todo: decompile */                                   \
        HANGUP();                                               \
    }

#define XASSERT(cond, mesg ...)                                 \
    if (!(cond)) {                                              \
        /* todo: decompile */                                   \
        printf( mesg );                                         \
        HANGUP();                                               \
    }

/*---------------------------------------------------------------------------*/
// https://en.cppreference.com/w/c/language/arithmetic_types#Boolean_type
// NOTE: (bool)0.5 evaluates to true, whereas (int)0.5 evaluates to 0.

typedef int             BOOL;

#ifndef FALSE
#define FALSE           (0)
#endif
#ifndef TRUE
#define TRUE            (!FALSE)
#endif

/*---------------------------------------------------------------------------*/

typedef signed char     int8;           /*  8-bit signed integer    */
typedef unsigned char   u_int8;         /*  8-bit unsigned integer  */
typedef signed short    int16;          /* 16-bit signed integer    */
typedef unsigned short  u_int16;        /* 16-bit unsigned integer  */
typedef signed int      int32;          /* 32-bit signed integer    */
typedef unsigned int    u_int32;        /* 32-bit unsigned integer  */
typedef signed long     int64;          /* 64-bit signed integer    */
typedef unsigned long   u_int64;        /* 64-bit unsigned integer  */
typedef signed long     long64;         /* 64-bit signed integer    */
typedef unsigned long   u_long64;       /* 64-bit unsigned integer  */

// https://gcc.gnu.org/onlinedocs/gcc/_005f_005fint128.html
// https://gcc.gnu.org/onlinedocs/gccint/Machine-Modes.html

typedef long128         int128;         /* 128-bit signed integer   */
typedef u_long128       u_int128;       /* 128-bit unsigned integer */

/*---------------------------------------------------------------------------*/
// linear algebra typedefs (backported from MGS4's mgs_types.h)

#if defined(__ee__) && !__GNUC_PREREQ(2, 96)
// https://gcc.gnu.org/onlinedocs/gcc/Unnamed-Fields.html
// ee-gcc releases before 2.96-ee-001003-1 do not support unnamed fields.
#error "Compiler does not support anonymous structs."
#endif

typedef union CVECTOR {
    struct { unsigned char r, g, b, a; };
    unsigned char c[4];
    unsigned int rgba;
} CVECTOR;

typedef ALIGN16 struct FCOLOR {
    float r, g, b, a;
} FCOLOR;

typedef ALIGN8 struct SVECTOR {
    short vx, vy, vz, vw;
} SVECTOR;

typedef ALIGN16 union IVECTOR {
    struct { int vx, vy, vz, vw; };
    int i[4];
} IVECTOR;

typedef ALIGN16 union FVECTOR {
    struct { float vx, vy, vz, vw; };
    struct { int ix, iy, iz, iw; };
    float f[4];
} FVECTOR;

typedef ALIGN16 union FMATRIX {
    float   m[4][4];
    FVECTOR v[4];
    struct { FVECTOR x_axis, y_axis, z_axis, trans; };
} FMATRIX;

/*---------------------------------------------------------------------------*/
// type-conversion unions (backported from MGS4's mgs_types.h)
//
// These appear to be derived from the PlayStation 2 "Software Keyboard"
// sample library header 'skb/include/extypes.h' and/or 'psptypes.h' from
// the PSP devkit release.

typedef ALIGN16 union union128 {
    FVECTOR         fv;
    IVECTOR         iv;
    SVECTOR         sv[2];
    CVECTOR         cv[4];
    FCOLOR          fcol;
    u_long128       qw;
    u_long128       uq;
    long128         q;
    u_long64        ul[2];
    long64          l[2];
    unsigned int    ui[4];
    int             i[4];
    unsigned short  us[8];
    short           s[8];
    unsigned char   uc[16];
    signed char     c[16];
    float           f[4];
} union128;

typedef ALIGN8 union union64 {
    SVECTOR         sv;
    CVECTOR         cv[2];
    u_long64        ul;
    long64          l;
    unsigned int    ui[2];
    int             i[2];
    unsigned short  us[4];
    short           s[4];
    unsigned char   uc[8];
    signed char     c[8];
    float           f[2];
    struct          { u_int hi, lo; } hilo;
} union64;

typedef union union32 {
    CVECTOR         cv;
    unsigned int    ui;
    int             i;
    unsigned short  us[2];
    short           s[2];
    unsigned char   uc[4];
    signed char     c[4];
    float           f;
} union32;

#endif // {{{ END OF FILE }}}
