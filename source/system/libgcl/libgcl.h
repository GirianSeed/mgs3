#ifndef __MGS3_LIBGCL_H__
#define __MGS3_LIBGCL_H__

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*/

typedef int GCL_COMMANDFUNC(char *);

typedef struct {
    int             id;         /* +0x00 */
    GCL_COMMANDFUNC *func;      /* +0x04 */
} GCL_COMMANDLIST;

typedef struct _gcl_commanddef {
    struct _gcl_commanddef *next;   /* +0x00 */
    int             n_commlist;     /* +0x04 */
    GCL_COMMANDLIST *commlist;      /* +0x08 */
} GCL_COMMANDDEF;

typedef struct {
    u_short argc;               /* +0x00 */
    int    *argv;               /* +0x04 */
} GCL_ARGS;

/*---------------------------------------------------------------------------*/

static inline int GCL_GetLong( char *ptr )
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | (p[3]);
}

static inline unsigned int GCL_GetULong( char *ptr )
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | (p[3]);
}

static inline unsigned int GCL_GetVarCode( char *ptr )
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | (p[3]);
}

static inline int GCL_Get3Bytes( char *ptr )
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (p[0] << 16) | (p[1] << 8) | (p[2] << 0);
}

static inline int GCL_GetShort( char *ptr )
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (signed short)((p[0] << 8) | (p[1]));
}

static inline unsigned int GCL_GetUShort( char *ptr )
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (unsigned short)((p[0] << 8) | (p[1]));
}

static inline unsigned char GCL_GetByte( char *ptr )
{
    return (unsigned char)*ptr;
}

static inline int GCL_GetStrCode( char *ptr )
{
    unsigned char *p;
    p = (unsigned char *)ptr;
    return (p[0] << 16) | (p[1] << 8) | (p[2] << 0);
}

/*---------------------------------------------------------------------------*/

/* gcl_init.c */
void GCL_ChangeSenerioCode( int code );
void GCL_Initialize( void );
void GCL_ResetSystem( void );

/* basic.c */
void GCL_InitBasicCommands( void );

/* command.c */
extern GCL_ARGS gcl_null_args;

void GCL_ResetCommList( void );
int GCL_AddCommMulti( GCL_COMMANDDEF *def );

/* expr.c */
int GCL_Expr( char *data );

/* parse.c */
//...

/* variable.c */
//...

#ifdef __cplusplus
}
#endif
#endif // {{{ END OF FILE }}}
