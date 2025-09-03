#include "game.h"
#include "common.h"
#include "../system/libgcl/libgcl.h"

extern int GM_TrapCommand(); /* in trap.c */

/*---------------------------------------------------------------------------*/

static int LoadCmd(char *top)
{
    // todo: decompile
}

static int CharaCmd(char *top)
{
    // todo: decompile
}

static int CommandCmd(char *top)
{
    // todo: decompile
}

static int RestartCmd(char *top)
{
    // todo: decompile
}

static int MesgCmd(char *top)
{
    // todo: decompile
}

static int RMesgCmd(char *top)
{
    // todo: decompile
}

/*---------------------------------------------------------------------------*/

static GCL_COMMANDLIST Commands[] = {
    { 0x0037c884, LoadCmd        }, // GV_StrCode("load")
    { 0x00082bc9, CommandCmd     }, // GV_StrCode("command")
    { 0x006592a7, CharaCmd       }, // GV_StrCode("chara")
    { 0x006bb005, RestartCmd     }, // GV_StrCode("restart")
    { 0x003bd490, GM_TrapCommand }, // GV_StrCode("trap")
    { 0x003822c7, MesgCmd        }, // GV_StrCode("mesg")
    { 0x00ccbde3, RMesgCmd       }  // GV_StrCode("rapid_mesg")
};

static GCL_COMMANDDEF script_commands = {
    NULL,               // next
    countof(Commands),  // n_commlist
    Commands            // commlist
};

void GM_InitBinds( void )
{
    /* do nothing */
}

void GM_InitScript( void )
{
    GM_InitBinds();
    GCL_AddCommMulti( &script_commands );
}
