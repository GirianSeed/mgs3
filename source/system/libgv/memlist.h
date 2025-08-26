#ifndef __MGS3_MEMLIST_H__
#define __MGS3_MEMLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GV_MEMTAG {
    /* +0x00 */ struct _GV_MEMTAG *next;
    /* +0x04 */ int size;
    /* +0x08 */ int res1;
    /* +0x0C */ int res2;
} GV_MEMTAG; /* sizeof:0x10 */

typedef struct _GV_MEMLIST {
    /* +0x00 */ char *name;
    /* +0x04 */ void *top;
    /* +0x08 */ void *bottom;
    /* +0x0C */ void *now_bottom;
    /* +0x10 */ int align;
    /* +0x14 */ GV_MEMTAG empty;
} GV_MEMLIST; /* sizeof:0x24 */

/* memlist.c */
void GV_MlBufferInit(GV_MEMLIST *list, char *name, void *top, void *bottom, int align);
void *GV_MlMalloc(GV_MEMLIST *list, int size);
void GV_MlFree(GV_MEMLIST *list, void *ptr, int size);

#ifdef __cplusplus
}
#endif
#endif // {{{ END OF FILE }}}
