#ifndef __gcctest_h__
#define __gcctest_h__

/*---------------------------------------------------------------------------*/
/* GNU-C Compiler Version Tests                                              */
/*---------------------------------------------------------------------------*/
// GCC documentation for predefined macros:
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html

#if defined(__GNUC__)
#if defined(__GNUC_PATCHLEVEL__) // GCC 3.0
#  define GCC_VERSION ((__GNUC__       * 10000) \
                      +(__GNUC_MINOR__ *   100) \
                      +(__GNUC_PATCHLEVEL__))
#else
#  define GCC_VERSION ((__GNUC__       * 10000) \
                      +(__GNUC_MINOR__ *   100))
#endif // __GNUC_PATCHLEVEL__
#else
#  define GCC_VERSION 0
#endif // __GNUC__

/* Convenience macro to test the version of GCC. */
/* Returns 0 for other compilers or versions older than GCC 2.0. */
#ifndef __GNUC_PREREQ
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define __GNUC_PREREQ(maj, min) \
        ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
#  define __GNUC_PREREQ(maj, min) 0
#endif
#endif /* __GNUC_PREREQ */
/* Version with trailing underscores for BSD compatibility. */
#ifndef __GNUC_PREREQ__
#define __GNUC_PREREQ__(maj, min) __GNUC_PREREQ(maj, min)
#endif

/*---------------------------------------------------------------------------*/
/* Clang C/C++ Compiler Version Tests                                        */
/*---------------------------------------------------------------------------*/

/* Clang's equivalent to GCC_VERSION as defined above. */
#if defined(__clang__)
#define CLANG_VERSION ((__clang_major__ * 10000) \
                      +(__clang_minor__ *   100) \
                      +(__clang_patchlevel__))
#else
#define CLANG_VERSION 0
#endif

/* Convenience macro to test the version of Clang. */
/* Clang's definitions of __GNUC(_MINOR)__ are fixed at 4.2.1, and features
   added to later versions of GCC may or may not be available in Clang. */
#ifndef __clang_prereq
#if defined(__clang_major__) && defined(__clang_minor__)
#  define __clang_prereq(maj, min) \
        ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else
#  define __clang_prereq(maj, min) 0
#endif
#endif

#endif // {{{ END OF FILE }}}
