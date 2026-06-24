#ifndef __MGS3_LIBGV_H__
#define __MGS3_LIBGV_H__

#include <libpad.h>     // for SCE_PAD*

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/

#define _PAD_U          SCE_PADLup      // 0x1000 ↑
#define _PAD_D          SCE_PADLdown    // 0x4000 ↓
#define _PAD_L          SCE_PADLleft    // 0x8000 ←
#define _PAD_R          SCE_PADLright   // 0x2000 →
#define _PAD_A          SCE_PADRright   // 0x0020 ○
#define _PAD_B          SCE_PADRdown    // 0x0040 ×
#define _PAD_X          SCE_PADRup      // 0x0010 △
#define _PAD_Y          SCE_PADRleft    // 0x0080 □
#define _PAD_L1         SCE_PADL1       // 0x0004 L1
#define _PAD_R1         SCE_PADR1       // 0x0008 R1
#define _PAD_L2         SCE_PADL2       // 0x0001 L2
#define _PAD_R2         SCE_PADR2       // 0x0002 R2
#define _PAD_L3         SCE_PADi        // 0x0200 L3
#define _PAD_R3         SCE_PADj        // 0x0400 R3
#define _PAD_START      SCE_PADstart    // 0x0800 START
#define _PAD_SELECT     SCE_PADselect   // 0x0100 SELECT

/* button masks */
#define _PAD_UDLR       (_PAD_U  | _PAD_D  | _PAD_L  | _PAD_R)
#define _PAD_ABXY       (_PAD_A  | _PAD_B  | _PAD_X  | _PAD_Y)
#define _PAD_LR         (_PAD_L1 | _PAD_L2 | _PAD_R1 | _PAD_R2)

/* button aliases */
#define _PAD_UP         _PAD_U          // ↑
#define _PAD_DOWN       _PAD_D          // ↓
#define _PAD_LEFT       _PAD_L          // ←
#define _PAD_RIGHT      _PAD_R          // →
#define _PAD_CIRCLE     _PAD_A          // ○
#define _PAD_CROSS      _PAD_B          // ×
#define _PAD_TRIANGLE   _PAD_X          // △
#define _PAD_SQUARE     _PAD_Y          // □

/*---------------------------------------------------------------------------*/

#if 0 // (MGS2 ver.)
typedef struct _GV_ACT {
    /* +0x00 */ struct _GV_ACT *next;
    /* +0x04 */ void (*act)(struct _GV_ACT *);
    /* +0x08 */ int     flag;
    /* +0x0C */ int     strcode;
    /* +0x10 */ struct _GV_ACT *prev;
    /* +0x14 */ void (*die)(struct _GV_ACT *);
    /* +0x18 */ void (*free)(void *);
    /* +0x1C */ short   priority;
    /* +0x1E */ short   field_1E;
    /* +0x20 */ int     runtime;
    /* +0x24 */ int     count;
    /* +0x28 */ const char *filename;
    /* +0x2C */ int     res1;
    /* +0x30 */ struct _GV_ACT *child;
    /* +0x34 */ struct _GV_ACT *c_prev;
    /* +0x38 */ struct _GV_ACT *c_next;
    /* +0x3C */ int (*hook)(struct _GV_ACT *, int, int);
} GV_ACT; /* sizeof:0x40 */
#endif

typedef int (*GV_LOADFUNC)(void *, int);

/*---------------------------------------------------------------------------*/

/* gvd.c */
void GV_StartDaemon( void );

/* strcode.c */
int GV_StrCode( const char *string );

#ifdef __cplusplus
}
#endif
#endif // {{{ END OF FILE }}}
