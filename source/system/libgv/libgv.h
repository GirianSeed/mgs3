#ifndef __MGS3_LIBGV_H__
#define __MGS3_LIBGV_H__

#include <libpad.h>

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/

#define PAD_U           SCE_PADLup      // ↑   (0x1000)
#define PAD_D           SCE_PADLdown    // ↓   (0x4000)
#define PAD_L           SCE_PADLleft    // ←   (0x8000)
#define PAD_R           SCE_PADLright   // →   (0x2000)
#define PAD_A           SCE_PADRright   // ○   (0x0020)
#define PAD_B           SCE_PADRdown    // ×   (0x0040)
#define PAD_X           SCE_PADRup      // △   (0x0010)
#define PAD_Y           SCE_PADRleft    // □   (0x0080)
#define PAD_L1          SCE_PADL1       // L1   (0x0004)
#define PAD_R1          SCE_PADR1       // R1   (0x0008)
#define PAD_L2          SCE_PADL2       // L2   (0x0001)
#define PAD_R2          SCE_PADR2       // R2   (0x0002)
#define PAD_STA         SCE_PADstart    // STA  (0x0800)
#define PAD_SEL         SCE_PADselect   // SEL  (0x0100)
#define PAD_AL          SCE_PADi        // L3   (0x0200)
#define PAD_AR          SCE_PADj        // R3   (0x0400)

/* button masks */
#define PAD_UDLR        (PAD_U  | PAD_D  | PAD_L  | PAD_R)
#define PAD_ABXY        (PAD_A  | PAD_B  | PAD_X  | PAD_Y)
#define PAD_LR          (PAD_L1 | PAD_L2 | PAD_R1 | PAD_R2)

/* button aliases */
#define PAD_UP          PAD_U           // ↑
#define PAD_DOWN        PAD_D           // ↓
#define PAD_LEFT        PAD_L           // ←
#define PAD_RIGHT       PAD_R           // →
#define PAD_CIRCLE      PAD_A           // ○
#define PAD_CROSS       PAD_B           // ×
#define PAD_TRIANGLE    PAD_X           // △
#define PAD_SQUARE      PAD_Y           // □
#define PAD_START       PAD_STA         // START
#define PAD_SELECT      PAD_SEL         // SELECT
#define PAD_L3          PAD_AL          // L3
#define PAD_R3          PAD_AR          // R3

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
    /* +0x1C */ short   field_1C;
    /* +0x1E */ short   field_1E;
    /* +0x20 */ int     field_20;
    /* +0x24 */ int     field_24;
    /* +0x28 */ const char *filename;
    /* +0x2C */ int     field_2C;
    /* +0x30 */ struct _GV_ACT *child;
    /* +0x34 */ struct _GV_ACT *c_prev;
    /* +0x38 */ struct _GV_ACT *c_next;
    /* +0x3C */ int (*hook)(struct _GV_ACT *, int, int);
} GV_ACT; /* sizeof:0x40 */
#endif

typedef int (*GV_LOADFUNC)(void *, int);

/* gvd.c */
void GV_StartDaemon( void );

/* strcode.c */
int GV_StrCode( const char *string );

#ifdef __cplusplus
}
#endif
#endif // {{{ END OF FILE }}}
