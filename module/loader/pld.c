#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <kernel.h>
#include <sif.h>
#include <sifcmd.h>
#include <sifrpc.h>

typedef struct {
    unsigned int paksize;   /* size of block    */
    unsigned int elfsize;   /* size of module   */
    unsigned int strsize;   /* strlen(name)+1   */
    unsigned int pad0;      /* padding          */
} ipkModuleTag;

#define XORKEY_1STVAL   0x7e8a6b4c
#define XORKEY_ADDVAL   0xa84e6b2e

static u_long xor_work = XORKEY_1STVAL;

static void decode( u_long *dst, void *src, size_t size )
{
    int i;
    sceSifReceiveData rd;

    sceSifGetOtherData( &rd, src, dst, size, 0 );

    for (i = size; i > 0; dst++) {
        *dst ^= xor_work;
        i -= sizeof(u_long);
        xor_work += XORKEY_ADDVAL;
    }
}

static int iopLoadInit( void *src )
{
    ipkModuleTag modtag;
    ModuleStatus modstat;
    int modid;
    int oldstat, res;

    void *buffer;
    char *name, *argp;
    int args;

    while (1) {
        xor_work = XORKEY_1STVAL;
        decode( (u_long *)&modtag, src, sizeof(ipkModuleTag) );
        src += sizeof(ipkModuleTag);

        if (modtag.paksize == 0) {
            break;
        }
        CpuSuspendIntr( &oldstat );
        buffer = AllocSysMemory( SMEM_High, modtag.paksize, 0 );
        CpuResumeIntr( oldstat );

        if (buffer == NULL) {
            return -1;
        }
        decode( buffer, src, modtag.paksize );
        src += modtag.paksize;

        name = (char *)(buffer + modtag.elfsize);
        argp = (char *)(name + strlen( name ) + 1);
        args = (modtag.strsize - (strlen( name ) + 1));

        modid = LoadModuleBuffer( buffer );
        FreeSysMemory( buffer );

        if (modid < 0) {
            continue;
        }
        ReferModuleStatus( modid, &modstat );
        res = StartModule( modid, name, args, argp, &res );
    }
    return 0;
}

int start( int argc, char *argv[] )
{
    long addr = strtol( argv[1], NULL, 16 );

    sceSifInitRpc( 0 );

    if (iopLoadInit( (void *)addr ) < 0) {
        return -1;
    }
    return NO_RESIDENT_END;
}
