#ifndef __MGS3_STRCODE_H__
#define __MGS3_STRCODE_H__

/*---------------------------------------------------------------------------*/

#define GCX_scenerio            0x00180720  // GV_StrCode("scenerio")

/* libgcl/basic.c */
#define CMD_if                  0x00000d86  // GV_StrCode("if")
#define CMD_switch              0x00a65db5  // GV_StrCode("switch")
#define CMD_eval                0x0034648c  // GV_StrCode("eval")
#define CMD_call                0x003311ec  // GV_StrCode("call")
#define CMD_return              0x008be398  // GV_StrCode("return")
#define CMD_print               0x003ab23b  // GV_StrCode("print")

/* game/script.c */
#define CMD_load                0x0037c884  // GV_StrCode("load") LoadCmd
#define CMD_command             0x00082bc9  // GV_StrCode("command") CommandCmd
#define CMD_chara               0x006592a7  // GV_StrCode("chara") CharaCmd
#define CMD_restart             0x006bb005  // GV_StrCode("restart") RestartCmd
#define CMD_trap                0x003bd490  // GV_StrCode("trap") GM_TrapCommand
#define CMD_mesg                0x003822c7  // GV_StrCode("mesg") MesgCmd
#define CMD_rapid_mesg          0x00ccbde3  // GV_StrCode("rapid_mesg") RMesgCmd

/*---------------------------------------------------------------------------*/

//
//
//
//
//

#endif // {{{ END OF FILE }}}
