#include <stddef.h>
#include <stdlib.h>

#include <eekernel.h>
#include <sifrpc.h>
#include <libdev.h>
#include <libdma.h>
#include <libgraph.h>

#include "../system/libgv/libgv.h"
#include "../system/libfs/libfs.h"
#include "../system/libdg/libdg.h"
#include "../system/libgeo/libgeo.h"
#include "../system/libgcl/libgcl.h"
#include "../system/libmt/libmt.h"
#include "../system/libnav/libnav.h"
#include "../system/libzon/libzon.h"
#include "../game/game.h"

// from module/mts/mts.c
extern void MTS_BootThread( char *name, void (*func)(), int pri,
                void *stack_top, int stack_size, void *arg );

// local to main/main.c
extern int main_argc;
extern char **main_argv;
extern int main_thid;

extern char main_stack[0x4000];
extern void Main();

int main( int argc, char *argv[] )
{
    main_argc = argc;
    main_argv = argv;
    main_thid = GetThreadId();

    MTS_BootThread( "MGS/MAIN", Main, 18, main_stack, 0x4000, NULL );
    while (1) {
        SleepThread();
    }
}
