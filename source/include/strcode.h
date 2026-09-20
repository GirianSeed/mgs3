#ifndef __MGS3_STRCODE_H__
#define __MGS3_STRCODE_H__

/*---------------------------------------------------------------------------*/

#define GCX_scenerio            0x00180720  // GV_StrCode("scenerio")

/* system/libgcl/basic.c */
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

#if 0
/*---------------------------------------------------------------------------*/
// NOTE: Some function names were taken from MGS4 (2006.09.07 builds).
// Additional NewChara function names exist in MGS3's binaries, but not all
// have been added yet.
//
//  +---------------> METAL GEAR SOLID 3: TRIAL VERSION
//  | +-------------> METAL GEAR SOLID 3: SNAKE EATER
//  | | +-----------> METAL GEAR SOLID 3: SUBSISTENCE
//  | | |  +-----------> DISC 1: SUBSISTENCE
//  | | |  | +---------> DISC 2: PERSISTENCE
//  | | |  | | +-------> DISC 3: EXISTENCE
//  | | |  | | | +-----> METAL GEAR ONLINE
//  v v v  v v v v
/*------------------*/
/*  - O O (1 2 - N) */  0x00001846  // GV_StrCode("紙") NewPaper
/*  - O O (1 - - N) */  0x000018e3  // GV_StrCode("雪") NewSnow
/*  O O O (1 - - -) */  0x00001933  // GV_StrCode("蝶") NewButterfly
/*  - O O (1 2 - N) */  0x00003d59
/*  - O O (1 - - -) */  0x000063ab
/*  - O O (1 2 - -) */  0x00009c13
/*  - O O (1 2 - -) */  0x00019a53  // GV_StrCode("cos") NewGclCos
/*  - O O (1 2 - -) */  0x0001d98e  // GV_StrCode("sin") NewGclSin
/*  - O O (1 - - -) */  0x0002a797
/*  - O O (1 - - -) */  0x0002c078
/*  - - O (- - - N) */  0x0002e075
/*  - O O (1 - - -) */  0x00030464  // GV_StrCode("メインメニュー設定")
/*  - O O (1 - - -) */  0x00036a1d
/*  - O O (1 - - -) */  0x000406a2
/*  - - O (- 2 3 -) */  0x0004b093
/*  - - O (1 2 - N) */  0x0004effa
/*  O O O (1 2 3 N) */  0x00053da0  // NewGclVarClear
/*  - O O (1 - - -) */  0x0005e0ab
/*  O O O (1 2 - N) */  0x00061ade  // GV_StrCode("カメラ") NewCamera
/*  - O O (1 - - -) */  0x00069104  // GV_StrCode("敵兵メモリー読み取り") ENEMEM_GclGet
/*  - O O (1 2 - N) */  0x0006b8cb
/*  - O O (1 2 - -) */  0x0006bdf6  // GV_StrCode("マーコール") NewMarkhor
/*  - O O (1 2 - -) */  0x0006ee2c
/*  - O O (1 - - -) */  0x0006fb39
/*  - O O (1 2 - -) */  0x00070a7d
/*  O O O (1 2 - N) */  0x0007cda7
/*  O O O (1 - - -) */  0x00087298
/*  O O O (1 2 - N) */  0x0008ed2e
/*  - O O (1 2 - -) */  0x00094a4c
/*  - - O (- - - N) */  0x0009a1a8
/*  - O O (1 - - -) */  0x0009c882
/*  O O O (1 2 - -) */  0x000a06c7
/*  - O O (1 2 - -) */  0x000a3e0b  // GV_StrCode("ドア状態取得") COM_DoorGetLockStatus
/*  - - O (1 2 - N) */  0x000b17f8  // GV_StrCode("平行カメラ") NewSphericalCamera
/*  O O O (1 2 - -) */  0x000b56f4
/*  - O O (1 2 - -) */  0x000bf5f2  // GV_StrCode("クリアリング設定") COM_SetClearingData
/*  - O O (1 2 - -) */  0x000c4faf
/*  - O O (1 2 - -) */  0x000c7ada
/*  O O O (1 2 - N) */  0x000c7f0e
/*  - O O (1 2 - -) */  0x000c942e
/*  - O O (1 - - -) */  0x000cd3af  // GV_StrCode("スペシャルモード設定") COM_SetSpecialMode
/*  - O O (1 2 - -) */  0x000d02fd  // GV_StrCode("鏡面モデル管理") NewMirrorControl
/*  - O O (1 - - -) */  0x000d7c37
/*  - O O (1 - - -) */  0x000d9578
/*  - O O (1 - - -) */  0x000dcfb6
/*  - O O (1 - - -) */  0x000dd485
/*  - O O (1 - - -) */  0x000e0767
/*  - O O (1 - - -) */  0x000e9f80
/*  - - O (- - - N) */  0x000f3d40  // ComGetCurrentStage
/*  - O O (1 2 - -) */  0x000f47ae
/*  - - O (- - - N) */  0x000f6a54
/*  O O O (1 2 3 N) */  0x000fa91c
/*  - O O (1 2 - -) */  0x000fdc57
/*  O O O (1 2 - -) */  0x00103a44
/*  - O O (1 - - -) */  0x0010f943
/*  - O O (1 - - -) */  0x0011488e
/*  O O O (1 2 - N) */  0x0011f61d
/*  - O O (1 - - -) */  0x00123141
/*  - O O (1 2 - -) */  0x00127162
/*  - O - (- - - -) */  0x00127f37
/*  O O O (1 2 - -) */  0x00128946  // GV_StrCode("プレイヤー") NewPlayer
/*  - O O (1 2 - -) */  0x0012bd53  // GV_StrCode("雨制御") NewRainControl
/*  - O O (1 2 - -) */  0x0013010a
/*  - O O (1 - - -) */  0x00138004
/*  - O O (1 2 - -) */  0x00138a16
/*  - O O (1 - - -) */  0x0013e297
/*  - - O (- - - N) */  0x001433b7
/*  - - O (- 2 - -) */  0x00144e5f
/*  O O O (1 2 - N) */  0x00147784  // GV_StrCode("サバイバルビューワ治療モード") NewSurvivalCureModeScn
/*  - O O (1 2 - -) */  0x0014b909
/*  - O O (1 - - -) */  0x00157ba6
/*  O O O (1 2 - -) */  0x0015d3da
/*  - O O (1 2 - -) */  0x0015dd87
/*  - O O (1 2 - -) */  0x0015fb8b
/*  - O O (1 - - -) */  0x0017a281
/*  O O O (1 2 - -) */  0x0018227c
/*  - O - (- - - -) */  0x00182ad7
/*  - O O (1 2 - -) */  0x00182db4
/*  O O O (1 2 - N) */  0x00182f0b
/*  O O O (1 2 - -) */  0x0018d40b  // GV_StrCode("字幕制御") NewJimakuControl
/*  - - O (- - - N) */  0x00190342
/*  - O O (1 2 - -) */  0x001922ff
/*  - O O (1 - - -) */  0x00193292
/*  - O O (1 - - -) */  0x0019608b
/*  - O O (1 - - -) */  0x001993d9
/*  - O O (1 2 - N) */  0x0019b364
/*  - O O (1 2 - -) */  0x0019dc5f
/*  - - O (- - 3 -) */  0x001a273a
/*  - - O (- - - N) */  0x001a7e08
/*  - O - (- - - -) */  0x001aae5f
/*  O O O (1 2 - -) */  0x001af92a  // GV_StrCode("レーダー") NewRadar
/*  - O O (1 2 - -) */  0x001ba50e
/*  - O O (1 2 3 -) */  0x001c2370  // GV_StrCode("アイテムフェイスペイント設定") GM_COM_InventoryFacePaintEnable
/*  - O O (1 - - -) */  0x001c5d31
/*  - O O (1 - - -) */  0x001d65f8
/*  - - O (- - - N) */  0x001e226c  // ComGetCurrentRule
/*  - O O (1 - - -) */  0x001f119a  // GV_StrCode("エンディング") NewEnding
/*  - - O (- - - N) */  0x001f1ae9
/*  O O O (1 2 - N) */  0x0020377d
/*  O O O (1 2 - -) */  0x002056f8
/*  - O O (1 - - -) */  0x0020f5a1
/*  - O O (1 2 - -) */  0x002156c2
/*  - O O (1 2 - -) */  0x00232853
/*  O O O (1 2 - -) */  0x00236330  // GV_StrCode("水面監視") NewCheckWaterLevel
/*  - O O (1 2 - -) */  0x00240e13
/*  - - O (1 2 - -) */  0x00242db9
/*  - - O (- - - N) */  0x002431fb
/*  - - O (- - - N) */  0x00246285
/*  - - O (- - - N) */  0x0024b801
/*  - O O (1 - - -) */  0x0025849f
/*  O O O (1 2 3 N) */  0x0025e019
/*  - O O (1 - - -) */  0x00264a32  // GV_StrCode("ソロー") NewSorrow
/*  - - O (- - - N) */  0x0027b5ee
/*  - O O (1 2 3 -) */  0x00283977
/*  - O O (1 - - -) */  0x00289035
/*  - - O (- - - N) */  0x0028a0fd
/*  - O O (1 2 - N) */  0x00291919
/*  - O O (1 2 - -) */  0x00294a42
/*  O O O (1 2 - -) */  0x002a5803
/*  - O O (1 2 - -) */  0x002a89a9
/*  - - O (- - - N) */  0x002abfa6
/*  - O O (- 2 - -) */  0x002ac7e3
/*  - O O (1 2 - -) */  0x002ae72c  // GV_StrCode("ケロタン") NewKerotan
/*  - O O (1 - - -) */  0x002af8ee
/*  O O O (1 2 - N) */  0x002b2336
/*  O O O (1 2 - N) */  0x002bbe1e
/*  - O O (1 - - -) */  0x002c7dbf
/*  - O O (1 2 - -) */  0x002cb94b
/*  O O O (1 2 - -) */  0x002cd772
/*  - O O (1 2 - -) */  0x002d5509
/*  - O O (1 2 - -) */  0x002d8b5c
/*  - O O (1 - - -) */  0x002dd63c
/*  O O O (1 2 - -) */  0x002e9c03
/*  - - O (- 2 - -) */  0x002f0a89
/*  O - - (- - - -) */  0x002fec39
/*  - O O (1 - - -) */  0x00300842
/*  - O O (1 - - -) */  0x0030aa8c
/*  - O O (1 2 - -) */  0x0030ca36
/*  O O O (1 2 - -) */  0x0030ca90  // NewHQC
/*  - O O (1 2 - -) */  0x003120ee
/*  - O O (1 2 - -) */  0x00316839
/*  - O O (1 2 - -) */  0x00317ba4
/*  - O O (1 2 - -) */  0x003190fc
/*  - O O (1 - - -) */  0x0031b090
/*  - O O (1 2 - -) */  0x0031f1c3
/*  - O O (1 2 - -) */  0x00325c8e  // GV_StrCode("atan") NewGclAtan
/*  O O O (1 2 - N) */  0x00325ee3
/*  - - O (- - - N) */  0x0032977d
/*  O O O (1 - - -) */  0x0032fb70  // GV_StrCode("StreamStopAll") NewStreamStopAll
/*  - O O (1 2 3 -) */  0x00334080
/*  - O O (1 2 - -) */  0x00336e1b
/*  - O O (- 2 - -) */  0x00339bf8
/*  O O O (1 - - -) */  0x0033a20f  // GV_StrCode("demo") NewPolygonDemoStart
/*  - O O (1 2 - -) */  0x003465ae
/*  - O O (1 - - -) */  0x00349f5c
/*  O O O (1 2 - -) */  0x0035508a
/*  - - O (- - 3 -) */  0x00355d54
/*  O O O (1 2 - N) */  0x0035a2cf  // GV_StrCode("マップ") NewSetMap
/*  - - O (- - - N) */  0x00367d64
/*  O O O (1 2 - -) */  0x0036b6b2
/*  - - O (1 - - -) */  0x00370e86
/*  - - O (- - - N) */  0x0037a451
/*  - O O (1 2 - -) */  0x0037d96f
/*  - O O (1 2 - -) */  0x0037e71b
/*  - O O (1 - - -) */  0x003874a0
/*  - O O (1 2 - -) */  0x00395ca2
/*  - O O (1 - - -) */  0x003981ee
/*  - O O (1 2 3 -) */  0x00398e32  // GV_StrCode("武器・アイテム所持数セーブ") GM_COM_InventorySave
/*  - O O (1 - - -) */  0x0039dd1f
/*  - O O (1 - - -) */  0x0039e451
/*  - O O (1 - - -) */  0x0039e4eb
/*  - - O (- - - N) */  0x003a3347
/*  O O O (1 2 - N) */  0x003a9224  // GV_StrCode("rand") NewRand
/*  - O O (1 2 - -) */  0x003b184b
/*  - O O (1 - - -) */  0x003b9ed6
/*  - O O (1 - - -) */  0x003baee1
/*  - - O (- - - N) */  0x003c1027
/*  - O O (1 2 - -) */  0x003c1a5c
/*  - O O (1 2 - N) */  0x003c6528
/*  - O O (1 2 - N) */  0x003c8494
/*  - O O (1 - - -) */  0x003d7a83
/*  - O O (1 2 - -) */  0x003d7f5f
/*  - O O (1 2 3 N) */  0x003db09f
/*  - O O (1 2 - -) */  0x003dfd0b  // GV_StrCode("エフェクトバウンド実行") UTL_EFT_ExecCallback
/*  - O O (1 - - -) */  0x003e9879
/*  O O O (1 2 3 N) */  0x003ec885  // GV_StrCode("武器・アイテム所持数追加") GM_COM_InventoryAddNum
/*  - O O (1 - - -) */  0x003f1072
/*  - O O (- 2 - -) */  0x003f30d7
/*  - O O (1 2 - -) */  0x003f3b77
/*  - O O (1 2 - -) */  0x003f3f97
/*  - O O (1 2 - -) */  0x003f47bd
/*  - O O (1 - - -) */  0x003f6dc0
/*  - O O (1 - - -) */  0x003f7038
/*  - O O (- 2 - -) */  0x004030d7
/*  - O O (1 - - -) */  0x00407e28
/*  - O O (- 2 - -) */  0x004130d7
/*  - O O (1 - - -) */  0x00413f60
/*  O O O (1 2 - -) */  0x004147a5  // GV_StrCode("ＳＥ字幕登録") GM_COM_AddSeJimaku
/*  - O O (1 2 - -) */  0x0042181a  // GV_StrCode("エフェクトバウンド追加") UTL_EFT_AddBoundFromGCL
/*  - O O (- 2 - -) */  0x004230d7
/*  - O O (1 - - -) */  0x00424392
/*  - O O (1 2 - -) */  0x00425441
/*  - O O (1 2 - -) */  0x00426afb
/*  - - O (- - - N) */  0x0043059f
/*  - O O (1 - - -) */  0x0043635c
/*  - O O (1 - - -) */  0x00437870
/*  - O O (1 - - -) */  0x00439eb4
/*  - O O (1 2 - N) */  0x0043bc3e
/*  O O O (1 2 - N) */  0x0043f718  // GV_StrCode("カメラ設定") COM_SetCamera
/*  - O O (1 - - -) */  0x00447870
/*  - O O (1 2 - -) */  0x0044fda5
/*  O O O (1 2 - -) */  0x00456267
/*  - O O (1 - - -) */  0x00457870
/*  - O O (1 2 - -) */  0x0045ca8d
/*  - - O (- - - N) */  0x0045d09d
/*  - O O (1 2 - -) */  0x00464066
/*  - O O (1 2 - -) */  0x0046fcd2  // GV_StrCode("敵兵メモリー更新") ENEMEM_GclRenewMemory
/*  O O O (1 2 - -) */  0x00478411
/*  O O O (1 2 - -) */  0x00479c81
/*  - O O (1 2 - -) */  0x0047c980
/*  - O O (1 - - -) */  0x0047e5e1
/*  - O O (1 2 - -) */  0x00480a35
/*  - O O (1 - - -) */  0x0048ef2f
/*  - - O (- - - N) */  0x0048f40e  // NewOnlineErrorCheck
/*  - O O (1 - - -) */  0x0048fea7
/*  - O O (1 2 - -) */  0x004953ff
/*  - O - (- - - -) */  0x004956cb
/*  O O O (1 2 - -) */  0x00495ef5  // GV_StrCode("プレイヤー強制モーション") PL_COM_SetForce
/*  - O O (1 - - -) */  0x00497ac3
/*  O O O (1 2 - -) */  0x00497be6  // GV_StrCode("無線状態") CodecStatus
/*  - - O (- - - N) */  0x004984cf
/*  O O O (1 2 - N) */  0x0049b880
/*  - - O (1 2 - -) */  0x0049e772
/*  O O O (1 2 - -) */  0x004a243a  // GV_StrCode("無線設定") NewCodec
/*  O O O (1 2 - N) */  0x004ab3b2
/*  O O O (1 2 - -) */  0x004ac6dc
/*  - O O (1 - - -) */  0x004aeee6
/*  - O O (1 2 - -) */  0x004b5fd9
/*  - O O (1 - - -) */  0x004bbb60
/*  - O O (1 - - -) */  0x004bf65a
/*  - O O (1 - - -) */  0x004c4879
/*  - - O (1 - - -) */  0x004caf18
/*  - O O (1 2 - -) */  0x004d2cb4
/*  - - O (1 2 - -) */  0x004dca90
/*  - O O (1 2 - -) */  0x004e3a78
/*  O O O (1 2 - -) */  0x004e61bf
/*  - O O (1 2 - -) */  0x004e84a4
/*  O O O (1 2 - -) */  0x004eeb4b  // GV_StrCode("プレイヤーエルード") PL_COM_SetElude
/*  - O O (1 - - -) */  0x004f8a22
/*  - O O (1 - - -) */  0x004fae63
/*  O O O (1 2 - -) */  0x00503da9
/*  - O O (1 - - -) */  0x00512854
/*  - O O (1 2 - -) */  0x00519afa
/*  - - O (1 2 - -) */  0x0051b0c9
/*  - O O (1 - - -) */  0x0051dac1  // GV_StrCode("スクリーン") NewScreen (TV in Graniny Gorki Lab B1)
/*  O O O (1 - - -) */  0x00527980
/*  - O O (1 - - -) */  0x005290cd
/*  O O O (1 2 - -) */  0x00537c0a  // GV_StrCode("カメラチェック無効") NewCameraCheckDisable
/*  - O O (1 2 - -) */  0x0053973d
/*  - - O (- - - N) */  0x0053bd7a
/*  - O O (1 2 - -) */  0x0053cf3a
/*  O O O (1 2 - -) */  0x0053dc0a  // GV_StrCode("カメラチェック有効") NewCameraCheckEnable
/*  O O O (1 2 3 N) */  0x00542b2d  // GV_StrCode("foreach") NewForeach
/*  - - O (- - - N) */  0x00546382
/*  - O O (1 2 - -) */  0x005585fa
/*  O O O (1 2 - -) */  0x0055b942  // GV_StrCode("ドア") NewDoor
/*  - O O (1 2 - -) */  0x0055e068
/*  - - O (- - - N) */  0x00560808
/*  - O O (1 2 - -) */  0x00567092
/*  - O O (1 2 - -) */  0x0056ab3a
/*  O O O (1 2 - -) */  0x0056e234  // GV_StrCode("マップ接合") NewMapConnect
/*  - O O (1 2 - -) */  0x0056e784
/*  O O O (1 2 - N) */  0x0056ef97  // GV_StrCode("マップ設定") NewMapSet
/*  - O O (1 - - -) */  0x00573139
/*  O O O (1 2 3 -) */  0x00573507
/*  - O O (1 - - -) */  0x0058191a
/*  - O O (1 2 - -) */  0x00588da3
/*  - O O (1 2 3 -) */  0x00598e28  // GV_StrCode("武器・アイテム所持数ロード") GM_COM_InventoryLoad
/*  O O O (1 2 - -) */  0x0059ab1e
/*  O O O (1 2 - N) */  0x0059ec5a
/*  - O O (1 2 - -) */  0x005a5816
/*  O O O (1 2 3 N) */  0x005a8c59
/*  - O O (1 - - -) */  0x005a92a4
/*  - O O (1 - - -) */  0x005ae655  // GV_StrCode("マップ表示") NewShowMap
/*  - O O (1 2 3 N) */  0x005af36e  // GM_COM_InventoryWeaponSet
/*  O O O (1 2 - N) */  0x005b316e  // GV_StrCode("varsave") NewSaveVariable
/*  - O O (1 2 3 -) */  0x005b364b  // GV_StrCode("武器弾数") GM_COM_InventoryWeaponNum
/*  - O O (1 - - -) */  0x005b3d4e
/*  - O O (1 - - -) */  0x005b5e45
/*  - O O (1 - - -) */  0x005b7832  // GV_StrCode("椅子") NewChair
/*  O O O (1 2 - -) */  0x005bb791
/*  - O O (1 2 - -) */  0x005bc599  // GV_StrCode("自動ドア") NewAutomaticDoor
/*  - O O (1 - - -) */  0x005c0bae  // GV_StrCode("パッドデモ") NewPadDemoPlay
/*  - O O (1 2 - -) */  0x005c65b0
/*  - O O (1 2 - N) */  0x005cb38e
/*  - O O (1 - - -) */  0x005d1667
/*  - O O (1 2 - -) */  0x005d7e30
/*  - O O (1 - - -) */  0x005e3345
/*  O O O (1 2 - N) */  0x005e5a53
/*  - O O (1 2 - -) */  0x005e826b
/*  - O O (1 2 - -) */  0x005f5cf7
/*  O O O (1 - - -) */  0x005f64a4
/*  - O O (1 2 - -) */  0x005fd3c4
/*  - O O (1 2 - -) */  0x005fe46d
/*  - O O (1 2 - N) */  0x00605b52
/*  - O O (1 - - -) */  0x00609a10
/*  - O - (- - - -) */  0x0060d52e
/*  - O O (1 2 - -) */  0x00614f27
/*  - - O (- 2 - -) */  0x006184e7
/*  - O O (1 2 - -) */  0x00618d6a
/*  O O O (1 2 - -) */  0x0061d13b
/*  - O O (1 - - -) */  0x0061f0ba
/*  - O O (1 2 - -) */  0x006239b1
/*  - O O (1 2 - N) */  0x006263f9  // GV_StrCode("エフェクトバウンド初期化") UTL_EFT_InitBound
/*  - O O (1 - - -) */  0x00626785
/*  O O O (1 2 - N) */  0x0062ff2e  // NewGrassMng
/*  - O O (1 2 - -) */  0x006339b1
/*  O O O (1 2 - -) */  0x00635875  // GV_StrCode("ゲームオーバー処理開始") GM_GameOverStartScn
/*  O O O (1 2 3 N) */  0x0063c1d8
/*  - O O (1 2 - -) */  0x0063cf9b
/*  - O O (1 - - -) */  0x006408fc
/*  - O O (1 2 - -) */  0x006422b0
/*  - O O (1 2 - -) */  0x006439b1
/*  - O O (1 - - -) */  0x00645113  // GV_StrCode("死体君") NewCorpGcl
/*  - O O (1 2 - -) */  0x00647dff
/*  - O O (1 2 - -) */  0x0064b3f4  // GV_StrCode("大佐")
/*  O O O (1 2 - -) */  0x006539fc  // GV_StrCode("敵兵")
/*  - O O (1 2 - -) */  0x00653bbf
/*  - O O (1 - - -) */  0x0065b8b4
/*  - O O (1 2 - -) */  0x00661b4a
/*  - - O (- - - N) */  0x00661f68
/*  - O - (- - - -) */  0x00663da5
/*  - - O (- - - N) */  0x0066d654
/*  - O O (1 - - -) */  0x0066e5d4
/*  - O O (1 - - -) */  0x00678c46
/*  - - O (- - - N) */  0x00679afb
/*  - O O (1 - - -) */  0x0067a960
/*  - O O (1 2 - -) */  0x00684209  // GV_StrCode("蜂壁") NewBeeWall
/*  O O O (1 2 - N) */  0x00684bfa
/*  O O O (1 2 - -) */  0x006856c1  // GV_StrCode("ゲームオーバー処理終了") GM_GameOverEndScn
/*  - - O (1 2 - N) */  0x00686853  // NewSCBoundTrapChara
/*  - O O (- 2 - -) */  0x00686b4d
/*  - O O (1 - - -) */  0x0068cb9c  // GV_StrCode("パッド振動") NewPadVibrationScn
/*  - O O (1 2 - -) */  0x00690245
/*  O O O (1 2 - -) */  0x00690610  // GV_StrCode("シネマスクリーン") NewCinemaScreen
/*  O O O (1 2 - N) */  0x0069b87e  // COM_PutStageModel_MeshControl
/*  - O O (1 2 - -) */  0x0069eb6c
/*  - O O (1 2 - -) */  0x006a3940
/*  O O O (1 2 3 -) */  0x006a725a  // GV_StrCode("パッド操作") NewPadControl
/*  - O O (1 2 - -) */  0x006aa0dc
/*  O O O (1 2 3 N) */  0x006b237d  // GV_StrCode("assert") NewGclAssert
/*  - O O (1 2 - -) */  0x006b25fd
/*  - O O (1 2 - -) */  0x006bc9a5
/*  - O O (1 - - -) */  0x006bdb60
/*  - O O (1 2 - -) */  0x006c109d
/*  - O O (1 - - -) */  0x006cb041
/*  - O O (1 2 - -) */  0x006e520e
/*  - O O (1 2 - -) */  0x006e6102
/*  - O O (1 - - -) */  0x006e989d
/*  - O O (1 - - -) */  0x006e989e
/*  - - O (- - - N) */  0x006e9c2c
/*  - O O (1 2 - -) */  0x006ea2a8
/*  O O O (1 2 3 N) */  0x006f7d4d  // NewGameInit
/*  O O O (1 2 - -) */  0x006f8307
/*  - O O (1 - - -) */  0x00706450
/*  - O O (1 2 - -) */  0x00708c6b
/*  - O O (1 2 - -) */  0x0070b8e6
/*  - O O (1 - - -) */  0x0070d322
/*  - O O (1 - - -) */  0x0070f3aa
/*  - O O (1 2 3 N) */  0x007128d0  // GV_StrCode("武器・アイテム名称設定") GM_COM_InventorySetNames
/*  O O O (1 2 - N) */  0x00712f17
/*  O O O (1 2 - N) */  0x0071e7d6  // NewSystemLightSet
/*  - O O (1 - - -) */  0x0072007f
/*  O O O (1 2 - -) */  0x00723f41
/*  O O O (1 2 - N) */  0x007267b7
/*  - O O (1 - - -) */  0x0072705f
/*  O O O (1 2 - -) */  0x00729f2d
/*  O O O (1 2 - -) */  0x0072f23c  // GV_StrCode("プットモーションモデル")
/*  - O O (1 2 - -) */  0x00735ef7
/*  O O O (1 2 3 N) */  0x00743c9f  // GV_StrCode("delay") NewDelay
/*  - - O (- - - N) */  0x0074cb83  // NewDefeatedCameraGCL
/*  O O O (1 2 3 N) */  0x0074e86b  // NewGclLangUpdate
/*  - O O (1 - - -) */  0x007546ba
/*  - O O (1 2 - -) */  0x007555e2
/*  O O O (1 2 - -) */  0x007576da
/*  O O O (1 2 3 -) */  0x00757d0a
/*  - O O (1 2 - -) */  0x0075fed4
/*  - O O (1 2 - -) */  0x007632dc
/*  - O O (1 2 - -) */  0x00767f58
/*  - O O (1 2 - -) */  0x0076d431
/*  O - - (- - - -) */  0x0077318d
/*  - O O (1 2 - -) */  0x00773af5
/*  - O O (1 2 - -) */  0x0077ab68
/*  - O O (1 2 - -) */  0x0077c520
/*  - O O (1 2 - -) */  0x00783abd
/*  - O O (1 - - -) */  0x00789c04
/*  - O O (1 - - -) */  0x00790b97
/*  - O O (1 2 - -) */  0x00795ac9
/*  - O O (1 - - -) */  0x0079705d
/*  - O O (1 2 - -) */  0x0079912b
/*  O O O (1 2 - -) */  0x007a0761  // GV_StrCode("無線メモリー") NewCodecMemory
/*  - O O (1 - - -) */  0x007a5d76
/*  - O O (1 - - -) */  0x007a8432
/*  - O O (1 - - -) */  0x007a86b8
/*  O O O (1 2 - -) */  0x007aa13a  // GV_StrCode("Stream") NewStreamSet
/*  - O O (1 - - -) */  0x007aee60
/*  - O O (1 2 - -) */  0x007b2a7c
/*  O O O (1 2 - N) */  0x007b4944  // GV_StrCode("カモフラ設定")
/*  O O O (1 2 3 N) */  0x007bc389
/*  O O O (1 2 - -) */  0x007c4d11  // GV_StrCode("汎用動物")
/*  - O O (1 - - -) */  0x007c6960
/*  O O O (1 2 - N) */  0x007cbbcf  // GV_StrCode("子画面")
/*  - O O (1 2 - -) */  0x007d55de
/*  - O O (1 - - -) */  0x007d7aec
/*  - O O (1 - - -) */  0x007e2caf
/*  - O O (1 2 - -) */  0x007e5115
/*  O O O (1 2 - N) */  0x007e641f  // NewPutStageModelSet
/*  - O O (1 - - -) */  0x007e750c
/*  - O O (1 2 - -) */  0x007eedb2
/*  - O O (1 2 - -) */  0x007f3c88  // GV_StrCode("カメラ視界チェック") NewViewCheckCommand
/*  - O O (1 - - -) */  0x007f52a2
/*  - - O (1 2 - -) */  0x007f6650
/*  - O O (1 - - -) */  0x007ff1b0
/*  O O O (1 2 - -) */  0x0080b977  // GV_StrCode("システムコールバック") NewSystemCallback
/*  - O O (1 2 - -) */  0x008175a4
/*  O O O (1 2 - -) */  0x0081f1ef  // GV_StrCode("SILVER_DISP") NewSilverDisp
/*  - O O (1 - - -) */  0x0081fb77
/*  - O O (1 - - -) */  0x00824a42
/*  - O O (1 2 - -) */  0x00829346
/*  - O O (1 - - -) */  0x0082a05e  // GV_StrCode("store_loadedvar") ComStoreLoadedVariable
/*  - - O (- - - N) */  0x0082b327
/*  - O O (1 2 - -) */  0x0082bdc0  // GV_StrCode("VecLen") NewGclVecLen
/*  O O O (1 - - -) */  0x0082cb3e  // GV_StrCode("reboot") NewGclReboot
/*  O O O (1 2 - N) */  0x0083102f
/*  - - O (- - - N) */  0x00831ee1
/*  - O O (1 2 - -) */  0x00843fea
/*  O O O (1 2 - -) */  0x0084594d
/*  - O O (1 2 - -) */  0x00849ba0  // GV_StrCode("プレイヤーライフ加算") PL_COM_LifeAdd
/*  - O O (1 2 - -) */  0x0084aa82
/*  - O O (1 2 - -) */  0x0085b70d
/*  - O O (1 - - -) */  0x008673c6
/*  - - O (- - 3 -) */  0x0086c63a
/*  - O O (1 - - -) */  0x0086d1cf  // GV_StrCode("敵兵メモリーコピー") ENEMEM_GclCopy
/*  - O O (1 - - -) */  0x00870aac
/*  O O O (1 2 3 N) */  0x0087a1c0  // GV_StrCode("select") NewSelect
/*  - - O (- - 3 -) */  0x0088117d
/*  - O O (1 - - -) */  0x008855a7
/*  - O O (1 2 - -) */  0x0088f9b0  // GV_StrCode("敵兵メモリーオールリセット") ENEMEM_GclAllReset
/*  - O O (1 2 - -) */  0x00890539
/*  - O O (1 2 - -) */  0x008961cd
/*  - O O (1 2 - -) */  0x008961eb
/*  O O O (1 2 3 -) */  0x0089a17e  // GV_StrCode("repeat") NewRepeat
/*  - - O (- 2 - -) */  0x0089ab22
/*  - O O (1 - - -) */  0x0089c7aa
/*  - - O (- - 3 -) */  0x0089ed67
/*  O O O (1 2 - N) */  0x008a02c7
/*  - O O (1 2 - -) */  0x008a7b70  // GV_StrCode("フィアー") NewFear
/*  - O O (1 2 - -) */  0x008a7b7a
/*  - O O (1 2 - -) */  0x008aa572  // GV_StrCode("ロッカー") NewLocker
/*  O O O (1 - - -) */  0x008b0ce2
/*  - O O (1 2 - -) */  0x008b19f0  // GV_StrCode("プレイヤー無敵セット") NewPlayerSetInvincible
/*  - O O (1 2 - -) */  0x008b1e74
/*  - O O (- 2 - -) */  0x008b3466
/*  - O O (1 - - -) */  0x008b4322
/*  O O O (1 2 - -) */  0x008b5ace
/*  - O O (1 2 3 -) */  0x008b6086  // GM_COM_PadCheck
/*  - - O (- - - N) */  0x008b94e9
/*  - O O (1 2 - -) */  0x008b976d  // GV_StrCode("ロッカー状態") NewLockerStatus
/*  O O O (1 - - -) */  0x008ba20a  // GV_StrCode("ソコロフ") NewSokolov
/*  - - O (- 2 - -) */  0x008c301c
/*  - O O (1 2 - -) */  0x008d06cc
/*  - O O (1 2 - -) */  0x008d4ec1
/*  - O O (1 2 - -) */  0x008d5639
/*  - O O (1 2 - -) */  0x008d92ed
/*  - O O (1 2 - -) */  0x008dc8ae
/*  O O O (1 2 3 -) */  0x008e298d  // GV_StrCode("デモキャンセルチェック") NewPadCancel
/*  - - O (- - - N) */  0x008e7500
/*  - O O (1 - - -) */  0x008f8e19
/*  - O O (1 - - -) */  0x008fdada
/*  - O O (1 - - -) */  0x009027e9
/*  - O O (1 2 - -) */  0x00909f7f  // GV_StrCode("フューリー") NewFury
/*  O O O (1 2 3 N) */  0x0091818c  // NewBGColorSet
/*  - O O (1 - - -) */  0x009197cf
/*  - - O (1 - - -) */  0x00919ade
/*  - O O (1 2 - -) */  0x0092034e
/*  - - O (- - - N) */  0x00921c90
/*  - O O (1 2 3 N) */  0x0092a625  // GV_StrCode("プロダクトコード設定") ComSetProductCode
/*  - O O (1 2 3 N) */  0x0092eb54  // GV_StrCode("getconfig") NewGetConfig
/*  - O O (1 2 - -) */  0x00934cb2
/*  - O O (1 - - -) */  0x009351d9
/*  - O O (1 - - -) */  0x00936419
/*  - O - (- - - -) */  0x00939b07
/*  - O O (1 - - -) */  0x0093aab1
/*  - O O (1 - - -) */  0x0093e44a  // GV_StrCode("スペシャルモード") NewSpecialMode
/*  O O O (1 - - -) */  0x0093f33d  // GV_StrCode("ドアロック") COM_DoorLock
/*  O O O (1 2 3 -) */  0x00944e11  // GV_StrCode("メニュー設定") NewSetMenuStatus
/*  O O O (1 2 3 N) */  0x009474ff
/*  - - O (1 2 - -) */  0x0095bc75
/*  O O O (1 - - -) */  0x0095c0ca
/*  O O O (1 2 - -) */  0x00962fbc
/*  O O O (1 2 - N) */  0x009634b1
/*  - - O (- - - N) */  0x009634f6
/*  - O O (- 2 - -) */  0x0096dfdc
/*  O O O (1 2 - -) */  0x0097451b
/*  - O O (1 - - N) */  0x00978db6  // GV_StrCode("雪表示") NewSnowDisplay
/*  O O O (1 2 - -) */  0x0097a3cf
/*  - O O (1 - - -) */  0x00985c58
/*  - O O (1 2 - -) */  0x0098b109
/*  - O O (1 2 - -) */  0x0099f754
/*  O O O (1 2 - N) */  0x009a0d0a  // GV_StrCode("エフェクト初期化") UTL_EFT_Initialize
/*  - O O (1 2 - -) */  0x009a1040
/*  - O O (1 2 3 -) */  0x009af657
/*  - - O (- - - N) */  0x009b8923
/*  O O O (1 2 3 N) */  0x009bc19a
/*  - O O (1 - - -) */  0x009bc48f
/*  - O O (1 - - -) */  0x009bc4ad
/*  - O O (1 - - -) */  0x009ce52c
/*  - O O (1 - - -) */  0x009d0339
/*  - O O (1 2 - -) */  0x009d7b8e
/*  - O O (1 - - -) */  0x009d9093
/*  - O O (1 - - -) */  0x009dc687
/*  O O O (1 2 - N) */  0x009e8ba6
/*  - - O (- - - N) */  0x009e9407
/*  O O O (1 2 - N) */  0x009f406f
/*  - O O (1 - - -) */  0x009f4866
/*  - O O (1 2 - -) */  0x009f4aa0
/*  - O O (1 - - -) */  0x009ff2c6
/*  - O O (1 2 - -) */  0x009ff6eb
/*  - O O (- 2 - -) */  0x00a066ac
/*  O O O (1 2 - N) */  0x00a0b247  // GV_StrCode("プレイヤーステータスＯＲ") PL_COM_GetPlayerStatusOr
/*  - O O (1 2 - -) */  0x00a11fd7
/*  - O O (1 2 - -) */  0x00a1a4fb
/*  - O O (1 2 - -) */  0x00a1f82d
/*  - O O (1 2 - -) */  0x00a202d2
/*  - O O (1 2 - -) */  0x00a2125d
/*  - O O (1 2 - -) */  0x00a21d45
/*  - O O (- 2 - -) */  0x00a314f7
/*  - O O (1 2 - -) */  0x00a314f8
/*  O O O (1 2 - N) */  0x00a366ff  // GV_StrCode("スリットライト") NewSlitLight
/*  - O O (1 - - -) */  0x00a3bf7b
/*  - O O (1 - - -) */  0x00a3c689
/*  - O O (1 2 - -) */  0x00a42bee
/*  - O O (1 2 - -) */  0x00a47661
/*  - O O (1 2 - -) */  0x00a4a2c3
/*  O O O (1 2 - N) */  0x00a56fcf  // GV_StrCode("弾痕エフェクト") NewBulletMark
/*  O O O (1 2 3 -) */  0x00a5b1ec  // GV_StrCode("while") NewGclWhile
/*  - - O (- - - N) */  0x00a63bd9
/*  - - O (- - - N) */  0x00a6b60b
/*  - O O (1 - - -) */  0x00a72bc6
/*  - O O (1 2 - -) */  0x00a7593d
/*  - - O (- - - N) */  0x00a7f286
/*  - O O (1 2 - -) */  0x00a833fe
/*  - O O (1 2 3 -) */  0x00a85df0
/*  - - O (- - - N) */  0x00a8e328
/*  - - O (- - - N) */  0x00a8e8ac
/*  O O O (1 2 - -) */  0x00a900fe  // GV_StrCode("カメラチェック") NewCameraCheck
/*  - O O (1 - - -) */  0x00a934ea
/*  - O O (1 - - -) */  0x00a97d6f  // GV_StrCode("両開きドア") NewMzTwindoor (Ponizovje Warehouse's exterior doors)
/*  - O O (1 - - -) */  0x00a99275
/*  O - - (- - - -) */  0x00a9b595
/*  - O O (1 - - -) */  0x00aacac8
/*  - O O (1 2 - -) */  0x00aaf706
/*  O O O (1 - - -) */  0x00ab3f7c
/*  - - O (- 2 - -) */  0x00ab55dc
/*  O O O (1 2 3 N) */  0x00ab5a2a  // GV_StrCode("常駐リソース設定") NewResidentResourceSet
/*  - - O (- - - N) */  0x00ab73fd
/*  O O O (1 2 - -) */  0x00ab8ce6
/*  - O O (1 2 - -) */  0x00abab99
/*  - O O (1 2 - N) */  0x00abd4e4
/*  - O O (1 2 - -) */  0x00ac4ee8  // GV_StrCode("ランダム初期化")
/*  - O O (1 2 - -) */  0x00ac684a
/*  - O O (1 2 - -) */  0x00ac82f9
/*  - - O (- - 3 -) */  0x00acc699
/*  - O O (1 - - -) */  0x00ad6f9c
/*  - O O (1 - - -) */  0x00adc02a
/*  - O O (1 - - -) */  0x00af1f08
/*  - - O (- - - N) */  0x00af33b6
/*  - O O (1 2 - -) */  0x00af44a8
/*  - O O (1 2 - -) */  0x00b00c01
/*  - O O (1 2 - N) */  0x00b101ec
/*  - - O (- - - N) */  0x00b121a2
/*  - - O (- 2 - -) */  0x00b13b94
/*  - O O (1 2 - -) */  0x00b19a58
/*  - O O (1 2 - -) */  0x00b2f7ee
/*  - - O (- - - N) */  0x00b38a65
/*  O O O (1 2 - -) */  0x00b3a94e
/*  - O O (1 2 - -) */  0x00b3ba87
/*  - O O (1 - - -) */  0x00b3f1b7
/*  - O O (1 2 - -) */  0x00b4a39d
/*  - O O (1 - - -) */  0x00b4d338
/*  O O O (1 2 - -) */  0x00b57eca
/*  - O O (1 - - -) */  0x00b58481
/*  - O O (1 2 - -) */  0x00b61cc0
/*  - O O (1 - - -) */  0x00b687e8
/*  - O O (1 2 - -) */  0x00b6e94e
/*  - O O (1 - - -) */  0x00b712e6
/*  O O O (1 2 - -) */  0x00b74a98
/*  - O O (1 2 - N) */  0x00b7f7d1
/*  - O O (1 2 - -) */  0x00b916d4
/*  - O O (1 2 - -) */  0x00b91a2d
/*  - O O (1 2 - -) */  0x00b96482
/*  - O O (1 - - -) */  0x00b97d41  // GV_StrCode("敵兵メモリーリセット") ENEMEM_GclReset
/*  - - O (- - - N) */  0x00b9cd73
/*  - O O (1 2 - -) */  0x00b9da1d
/*  - O O (1 - - -) */  0x00b9e1f4
/*  - O - (- - - -) */  0x00b9f944
/*  O O O (1 2 - N) */  0x00ba3a38  // GV_StrCode("マップシステム") NewMapSystem
/*  - O O (1 2 - -) */  0x00bae1be
/*  - O O (1 - - -) */  0x00baf651
/*  - - O (- - - N) */  0x00bce74e
/*  O O O (1 2 3 N) */  0x00bcf6ff
/*  - O O (1 2 - -) */  0x00bd400b  // GV_StrCode("影管理") NewShadowControl
/*  O O O (1 2 - N) */  0x00bd8d95
/*  O O O (1 - - -) */  0x00beb908
/*  O O O (1 2 - -) */  0x00bf0504
/*  - - O (1 2 3 N) */  0x00bf051f
/*  - - O (- - - N) */  0x00bf76c9
/*  - O O (1 2 - -) */  0x00c075b9
/*  - - O (- - - N) */  0x00c08865
/*  - O O (1 2 - -) */  0x00c090b1
/*  - O O (1 - - -) */  0x00c19aa4
/*  - O O (1 2 - -) */  0x00c1f2f3
/*  O - - (- - - -) */  0x00c2d9fe
/*  - O O (1 2 - -) */  0x00c392d3
/*  O O O (1 - - -) */  0x00c3ec86  // GV_StrCode("ドアアンロック") COM_DoorUnlock
/*  O O O (1 2 - -) */  0x00c3f409
/*  O O O (1 2 - -) */  0x00c44d8b  // GV_StrCode("敵兵状態取得") COM_GetEnemyStatus
/*  - O O (1 - - -) */  0x00c455c8
/*  - O O (1 - - -) */  0x00c5162b  // GV_StrCode("武器・アイテムスロットクリア") GM_COM_InventorySlotClear
/*  - O O (1 2 - -) */  0x00c51848
/*  - O O (1 2 - -) */  0x00c53ae7
/*  - O O (1 2 - N) */  0x00c53b05
/*  - O O (1 2 - -) */  0x00c65d9f
/*  - O O (1 2 - -) */  0x00c6fdfc
/*  - O O (1 - - -) */  0x00c70c04
/*  - O O (1 - - -) */  0x00c710c6
/*  O O O (1 2 3 N) */  0x00c74f97  // GV_StrCode("配列セット") NewArraySet
/*  O O O (1 2 - -) */  0x00c78563
/*  O O O (1 - - -) */  0x00c7f9ca
/*  O O O (1 2 - -) */  0x00c851b0
/*  O O O (1 2 - N) */  0x00c885a5
/*  - O O (1 2 - -) */  0x00c88764  // GV_StrCode("スリットライトフェード") NewSlitLightFade
/*  - - O (- - - N) */  0x00c8e303
/*  O O O (1 2 3 -) */  0x00c8e3fd  // GV_StrCode("フェード") NewFadeInOutScn
/*  - - O (- - - N) */  0x00c8e80a
/*  - O O (1 2 - N) */  0x00c8fb44
/*  - O O (1 - - -) */  0x00c9af4c
/*  O O O (1 2 - N) */  0x00c9bbe9
/*  - O O (1 2 - -) */  0x00ca337e
/*  - O O (1 2 - -) */  0x00ca3e5b
/*  - O O (1 - - -) */  0x00ca91c4
/*  - O O (1 - - -) */  0x00cafda9
/*  - O O (1 - - -) */  0x00cb1834  // GV_StrCode("ジョニー") NewJohnny
/*  - O O (1 2 - -) */  0x00cb3fd9
/*  - O O (1 - - -) */  0x00cbfca6
/*  - O O (1 - - -) */  0x00cc2e24
/*  - O O (1 2 - -) */  0x00cc5a5a
/*  O O O (1 2 - -) */  0x00cc9a2b
/*  - - O (- - - N) */  0x00ccbefe
/*  - O O (1 2 - -) */  0x00ccd7f9
/*  O O O (1 2 3 N) */  0x00cd646f  // GM_InventoryDaemonStart
/*  - O O (1 2 - -) */  0x00cda34c
/*  - O O (1 2 - -) */  0x00cda34e
/*  - O O (1 - - -) */  0x00cdd822  // GV_StrCode("鉄橋爆破") NewRailBridgeDemolition
/*  - O O (1 2 - -) */  0x00cde39f
/*  - O O (1 - - -) */  0x00ce2d79
/*  O O O (1 2 - N) */  0x00cf9028
/*  - O O (1 - - -) */  0x00d00676
/*  - O O (1 - - -) */  0x00d05ba0
/*  - O O (1 - - -) */  0x00d0cf49
/*  - O O (1 - - -) */  0x00d0f729
/*  - O O (1 - - -) */  0x00d0fb6d
/*  - O O (1 2 - -) */  0x00d110ce  // GV_StrCode("オプションモード設定") COM_SetOptionMode
/*  - O O (1 2 - -) */  0x00d17a99
/*  - O O (1 2 - -) */  0x00d19e27
/*  - O O (1 2 - -) */  0x00d25d5a
/*  - O O (1 - - -) */  0x00d29bb4
/*  - O O (1 2 - N) */  0x00d2bd87  // GV_StrCode("風制御") NewWindManager
/*  O O O (1 2 - -) */  0x00d30863  // GV_StrCode("StreamStop") NewStreamStop
/*  - O O (1 2 - -) */  0x00d4381c
/*  - O O (1 2 - -) */  0x00d45cf1
/*  - O O (1 2 - -) */  0x00d46f76
/*  - O O (1 2 - -) */  0x00d4b51a
/*  - - O (- - - N) */  0x00d4d8a5
/*  - - O (- - - N) */  0x00d4ea76  // NewHeadUpDisplay
/*  - O O (1 2 - -) */  0x00d517fe
/*  O O O (1 2 - -) */  0x00d5545b  // GV_StrCode("右スティックカメラ設定") COM_SetCameraRightStick
/*  - O O (1 - - -) */  0x00d5cb81
/*  - O O (1 - - -) */  0x00d61bf6
/*  - O O (1 2 - -) */  0x00d65266
/*  - O O (1 2 - -) */  0x00d6fd05
/*  - O O (1 - - -) */  0x00d73a9c
/*  - O O (1 2 - -) */  0x00d7b646  // GV_StrCode("オプションモード") COM_OptionMode
/*  - O O (1 2 - -) */  0x00d8361e
/*  - O O (1 - - -) */  0x00d8714a
/*  O O O (1 2 - N) */  0x00d8cb74
/*  - O O (1 - - -) */  0x00d8d32f
/*  O O O (1 2 - N) */  0x00d8fd67
/*  - O O (1 - - N) */  0x00d9046e
/*  - O O (1 2 - -) */  0x00d98b39
/*  - O O (1 - - -) */  0x00d9b7de
/*  - O O (1 2 - -) */  0x00da2917
/*  - O O (1 - - -) */  0x00da9244
/*  O O O (1 2 - -) */  0x00da97fb  // GV_StrCode("トラップ切り替え") GM_COM_TrapSwitchCommand
/*  - - O (- - 3 -) */  0x00daad6b
/*  - O O (1 2 - -) */  0x00dac400
/*  - O O (1 - - -) */  0x00daed21
/*  O O O (1 2 3 N) */  0x00daf423
/*  - - O (- - - N) */  0x00db4ee7
/*  - O O (1 - - -) */  0x00dbb521
/*  - - O (- - - N) */  0x00dc2db5
/*  O O O (1 2 3 N) */  0x00dc83c5  // GV_StrCode("ロードサウンドパック") GM_LoadPack
/*  - O O (1 - - -) */  0x00dd173e
/*  - - O (- 2 - -) */  0x00dd5eb6
/*  - - O (- 2 - -) */  0x00dd5eb7
/*  O O O (1 2 - N) */  0x00dde914  // NewFogSet
/*  O O O (1 2 3 N) */  0x00de07c0  // GV_StrCode("フォント初期化") NewFontInit
/*  - O O (1 - - -) */  0x00de2c60
/*  - O O (1 - - -) */  0x00de545a
/*  - O O (1 2 - -) */  0x00deb2a3
/*  O O O (1 2 - -) */  0x00dec9e1
/*  - O O (1 - - -) */  0x00decc26
/*  - O O (1 2 - -) */  0x00dee2e0
/*  - O O (1 2 - -) */  0x00df1d9c
/*  O O O (1 2 - -) */  0x00df4cae  // GV_StrCode("アイテムボックス") NewItemBox
/*  - O O (1 2 - -) */  0x00e002ea
/*  O O O (1 2 - -) */  0x00e08648
/*  O O O (1 2 - -) */  0x00e0dbba  // GV_StrCode("２Ｄスプライト表示") New2DSprite
/*  - O O (1 2 - -) */  0x00e0f9c7
/*  - O O (1 2 - -) */  0x00e22b51
/*  O O O (1 - - -) */  0x00e2808c
/*  O O O (1 2 - -) */  0x00e29adb  // GV_StrCode("シナリオデモ開始") NewStartScenarioDemo
/*  - O O (1 - - -) */  0x00e387af
/*  - O O (1 2 - -) */  0x00e44f0c
/*  - O O (1 - - -) */  0x00e4750f  // GV_StrCode("VecResize") NewGclResizeVector
/*  - - O (- - - N) */  0x00e4b84a
/*  - O O (1 - - -) */  0x00e5619d
/*  - O O (1 - - -) */  0x00e5dfd7
/*  O O O (1 2 - N) */  0x00e5fd50
/*  - O O (1 2 - -) */  0x00e764b2
/*  - O O (1 2 3 N) */  0x00e76d74  // NewGclVariableMove
/*  - O O (1 2 - -) */  0x00e78c6d
/*  - O O (1 - - -) */  0x00e7939b
/*  O O O (1 2 - -) */  0x00e79927  // GV_StrCode("シナリオデモ終了") NewEndScenarioDemo
/*  - - O (- 2 - N) */  0x00e7a1d7
/*  - O O (1 - - -) */  0x00e81436
/*  O O O (1 2 - -) */  0x00e82679
/*  - O O (1 2 - -) */  0x00e84f76
/*  - O O (1 - - -) */  0x00e923a5  // GV_StrCode("プレイヤーステータスＡＮＤ") PL_COM_GetPlayerStatusAnd
/*  - O O (1 - - -) */  0x00e93330
/*  O O O (1 2 - -) */  0x00e96d82  // GV_StrCode("無線システム") NewCodecDaemon
/*  - - O (1 2 - -) */  0x00e99d79
/*  - - O (- - - N) */  0x00e9cacf
/*  - - O (1 2 - -) */  0x00e9fd79
/*  - O O (1 2 - -) */  0x00ea1854
/*  O O O (1 2 - -) */  0x00eacdac
/*  - - O (- - - N) */  0x00eaf7bb
/*  - O O (1 2 - -) */  0x00eb0f77
/*  - O O (1 2 - -) */  0x00eb2429
/*  - O - (- - - -) */  0x00eb660a
/*  O O O (1 2 - -) */  0x00eb72e4
/*  - O O (1 2 - -) */  0x00eb837a
/*  - O O (1 - - -) */  0x00eb98e0  // GV_StrCode("ブラーエフェクト") NewBlur
/*  - O O (1 - - -) */  0x00ec3235
/*  O O O (1 2 3 -) */  0x00ec341f
/*  - O O (1 - - -) */  0x00ec94ca
/*  O O O (1 2 - -) */  0x00ed0fa0
/*  - O O (1 - - -) */  0x00ed1c87
/*  - O O (1 2 - -) */  0x00edbf7a
/*  - O O (1 - - -) */  0x00edd516
/*  - O O (1 2 - -) */  0x00edda6d
/*  - - O (1 2 3 -) */  0x00ee47ad
/*  - O O (1 2 - -) */  0x00ef16a0
/*  O O O (1 2 - -) */  0x00ef8aaf
/*  - - O (1 2 3 -) */  0x00f02397
/*  - O O (1 2 - N) */  0x00f10849
/*  - - O (- - 3 -) */  0x00f1745e
/*  O O O (1 2 - -) */  0x00f19dce
/*  - O O (1 - - -) */  0x00f2dfcd  // GV_StrCode("load_restart") NewLoadRestart
/*  - O O (1 2 - -) */  0x00f32f4e
/*  - - O (- - - N) */  0x00f3658f
/*  - - O (1 2 - -) */  0x00f4cdf7
/*  - O O (1 2 - -) */  0x00f526ea  // GV_StrCode("ペイン") NewPain
/*  - O O (1 2 - -) */  0x00f53bd3  // GV_StrCode("プレイヤースタミナ加算") PL_COM_StaminaAdd
/*  O O O (1 2 - -) */  0x00f552a3
/*  - O O (1 2 - -) */  0x00f5ade7
/*  - O O (1 2 - -) */  0x00f63a97
/*  - O O (1 - - -) */  0x00f66375
/*  - - O (- - - N) */  0x00f69343
/*  - O O (1 2 - -) */  0x00f6a218
/*  - O O (1 - - -) */  0x00f6ef99  // GV_StrCode("メインメニュー") NewMainMenuScn
/*  - - O (- - - N) */  0x00f74d93
/*  - - O (- - - N) */  0x00f75d58
/*  - O O (1 - - -) */  0x00f7a440
/*  - O O (1 2 - -) */  0x00f817d3  // GV_StrCode("プレイヤースタミナ減算") PL_COM_StaminaDec
/*  - O O (1 - - -) */  0x00f8675e
/*  - O O (1 2 - -) */  0x00f88982
/*  - O O (1 2 - -) */  0x00f8e4bc
/*  - O O (1 2 - -) */  0x00f8fbb2
/*  - - O (- - - N) */  0x00faa832
/*  - O O (1 2 - -) */  0x00fac9cf
/*  - O O (1 2 - -) */  0x00fafbcd  // GV_StrCode("ステージ環境天候変更") GM_COM_SetEnvStage_SetWeather
/*  O O O (1 2 - -) */  0x00fb50d6
/*  - O O (1 - - -) */  0x00fb8044
/*  O O O (1 2 - -) */  0x00fbbdba
/*  O O O (1 2 - -) */  0x00fbeb7f  // GV_StrCode("ゲームオーバーチェック") GM_COM_IsGameOver
/*  - O O (1 - - -) */  0x00fc9315
/*  - - O (- - - N) */  0x00fca54f
/*  - O O (1 2 - -) */  0x00fd6b3f  // GV_StrCode("アイテム数") GM_COM_InventoryItemNum
/*  - O O (1 2 - -) */  0x00fd6c92
/*  - O O (1 - - -) */  0x00fddbab
/*  - O O (1 - - -) */  0x00fe6730  // GV_StrCode("sound_test") NewSoundTest
/*  - O O (1 2 - -) */  0x00fe950a
/*  - O O (1 - - -) */  0x00ff40ce
/*  O O O (1 2 - N) */  0x00ff46e5
/*  - - O (- - - N) */  0x00ff7af1
/*  - O O (1 2 - -) */  0x00ff8e39
/*  O O O (1 2 - N) */  0x00ffbe20
/*  - O O (1 2 3 -) */  0x00ffbece  // GV_StrCode("MOVIE再生") NewMpegPssMovieStr
/*  - O O (1 2 - -) */  0x00ffecfd

/*--- Polygon Demo Charas ---*/
/*  O O O (1 - - -) */  0x01000000
/*  O O O (1 2 - -) */  0x01000001
/*  O O O (1 - - -) */  0x01000002
/*  O O O (1 - - -) */  0x01000003
/*  O O O (1 - - -) */  0x01000004
/*  O O O (1 - - -) */  0x01000005
/*  O O O (1 - - -) */  0x01000006
/*  O O O (1 - - -) */  0x01000007
/*  O O O (1 - - -) */  0x01000008
/*  O O O (1 - - -) */  0x01000009
/*  O O O (1 - - -) */  0x0100000a
/*  - O O (1 - - -) */  0x0100000b
/*  - O O (1 - - -) */  0x0100000c
/*  O O O (1 - - -) */  0x0100000d
/*  - O O (1 - - -) */  0x01000501
/*  - O O (1 - - -) */  0x01000502
/*  O O O (1 - - -) */  0x01000503
/*  - O O (1 - - -) */  0x01000504
/*  - O O (1 - - -) */  0x01000505
/*  - O O (1 - - -) */  0x01000506
/*  - O O (1 - - -) */  0x01000507
/*  - O O (1 - - -) */  0x01000508
/*  O O O (1 - - -) */  0x01000800
/*  O O O (1 - - -) */  0x01000801
/*  O O O (1 - - -) */  0x01000802
/*  - O O (1 - - -) */  0x01000804
/*  - O O (1 - - -) */  0x01000805
/*  - O O (1 - - -) */  0x01000806
/*  - O O (1 - - -) */  0x01000807
/*  - O O (1 - - -) */  0x01000808
/*  - O O (1 - - -) */  0x01000809
/*  - O O (1 - - -) */  0x0100080a
/*  - O O (1 - - -) */  0x0100080b
/*  - O O (1 - - -) */  0x0100080d
/*  O O O (1 - - -) */  0x01001000
/*  O O O (1 - - -) */  0x01001001
/*  - O O (1 - - -) */  0x01001002
/*  - O O (1 - - -) */  0x01001003
/*  O O O (1 - - -) */  0x01001004
/*  O O O (1 - - -) */  0x01001005
/*  O O O (1 - - -) */  0x01001006
/*  O O O (1 - - -) */  0x01001007
/*  O O O (1 - - -) */  0x01001008
/*  O O O (1 - - -) */  0x01001009
/*  O O O (1 - - -) */  0x0100100a
/*  O O O (1 - - -) */  0x0100100b
/*  - O O (1 - - -) */  0x0100100c
/*  O O O (1 - - -) */  0x0100100e
/*  O O O (1 - - -) */  0x0100100f
/*  O O O (1 - - -) */  0x01001010
/*  - O O (1 - - -) */  0x01001011
/*  - O O (1 - - -) */  0x01001012
/*  - O O (1 - - -) */  0x01001013
/*  - O O (1 - - -) */  0x01001014
/*  O O O (1 - - -) */  0x01001015
/*  O O O (1 - - -) */  0x01001016
/*  O O O (1 - - -) */  0x01001017
/*  - O O (1 - - -) */  0x01001018
/*  - O O (1 - - -) */  0x01001019
/*  - O O (1 - - -) */  0x0100101a
/*  - O O (1 - - -) */  0x0100101b
/*  - O O (1 - - -) */  0x0100101c
/*  O O O (1 - - -) */  0x0100101d
/*  - O O (1 - - -) */  0x0100101e
/*  O O O (1 - - -) */  0x0100101f
/*  O O O (1 - - -) */  0x01001020
/*  O O O (1 - - -) */  0x01001021
/*  - O O (1 - - -) */  0x01001022
/*  O O O (1 - - -) */  0x01001023
/*  O O O (1 - - -) */  0x01001024
/*  - O O (1 - - -) */  0x01001025
/*  - O O (1 - - -) */  0x01001026
/*  - O O (1 - - -) */  0x01001027
/*  - O O (1 - - -) */  0x01001028
/*  - O O (1 - - -) */  0x01001201
/*  - O O (1 - - -) */  0x01001202
/*  - O O (1 - - -) */  0x01001203
/*  - O O (1 - - -) */  0x01001204
/*  - O O (1 - - -) */  0x01001205
/*  - O O (1 - - -) */  0x01001206
/*  - O O (1 - - -) */  0x01001501
/*  - O O (1 - - -) */  0x01001502
/*  - O O (1 - - -) */  0x01001503
/*  - O O (1 - - -) */  0x01001504
/*  - O O (1 - - -) */  0x01001505
/*  - O O (1 - - -) */  0x01001506
/*  - O O (1 - - -) */  0x01001507
/*  - O O (1 - - -) */  0x01001508
/*  - O O (1 - - -) */  0x01001509
/*  - O O (1 - - -) */  0x0100150a
/*  - O O (1 - - -) */  0x0100150b
/*  - O O (1 - - -) */  0x0100150c
/*  - O O (1 - - -) */  0x0100150d
/*  - O O (1 - - -) */  0x0100150e
/*  - O O (1 - - -) */  0x0100150f
/*  - O O (1 - - -) */  0x01001510
/*  - O O (1 - - -) */  0x01001511
/*  - O O (1 - - -) */  0x01001512
/*  - O O (1 - - -) */  0x01001513
/*  - O O (1 - - -) */  0x01001514
/*  - O O (1 - - -) */  0x01001515
/*  - O O (1 - - -) */  0x01001516
/*  - O O (1 - - -) */  0x01001518
/*  - O O (1 - - -) */  0x01001519
/*  - O O (1 - - -) */  0x0100151a
/*  - O O (1 - - -) */  0x0100151b
/*  - O O (1 - - -) */  0x0100151c
/*  - O O (1 - - -) */  0x0100151d
/*  - O O (1 - - -) */  0x0100151e
/*  - O O (1 - - -) */  0x0100151f
/*  - O O (1 - - -) */  0x01001520
/*  - O O (1 - - -) */  0x01001521
/*  - O O (1 - - -) */  0x01001522
/*  - O O (1 - - -) */  0x01001523
/*  - O O (1 - - -) */  0x01001524
/*  - O O (1 - - -) */  0x01001525
/*  - O O (1 - - -) */  0x01001526
/*  - O O (1 - - -) */  0x01001527
/*  - O O (1 - - -) */  0x01001528
/*  - O O (1 - - -) */  0x01001529
/*  - O O (1 - - -) */  0x0100152a
/*  - O O (1 - - -) */  0x0100152b
/*  - O O (1 - - -) */  0x0100152c
/*  - O O (1 - - -) */  0x0100152d
/*  - O O (1 - - -) */  0x0100152e
/*  - O O (1 - - -) */  0x0100152f
/*  - O O (1 - - -) */  0x01001530
/*  - O O (1 - - -) */  0x01001531
/*  - O O (1 - - -) */  0x01001533
/*  - O O (1 - - -) */  0x01001534
/*  - O O (1 - - -) */  0x01001535
/*  - O O (1 - - -) */  0x01001536
/*  - O O (1 - - -) */  0x01001537
/*  - O O (1 - - -) */  0x01001538
/*  - O O (1 - - -) */  0x01001539
/*  - O O (1 - - -) */  0x0100153a
/*  - O O (1 - - -) */  0x0100153b
/*  - O O (1 - - -) */  0x0100153d
/*  - O O (1 - - -) */  0x0100153e
/*  - O O (1 - - -) */  0x0100153f
/*  - O O (1 - - -) */  0x01001540
/*  - O O (1 - - -) */  0x01001541
/*  - O O (1 - - -) */  0x01001542
/*  - O O (1 - - -) */  0x01001543
/*  - O O (1 - - -) */  0x01001544
/*  - O O (1 - - -) */  0x01001545
/*  - O O (1 - - -) */  0x01001613
/*  - O O (1 - - -) */  0x01001800
/*  - O O (1 - - -) */  0x01001801
/*  - O O (1 - - -) */  0x01001802
/*  O O O (1 - - -) */  0x01001803
/*  - O O (1 - - -) */  0x01001804
/*  - O O (1 - - -) */  0x01001805
/*  - O O (1 - - -) */  0x01001806
/*  - O O (1 - - -) */  0x01001807
/*  - O O (1 - - -) */  0x01001808
/*  - O O (1 - - -) */  0x01001809
/*  - O O (1 - - -) */  0x0100180a
/*  - O O (1 - - -) */  0x0100180b
/*  - O O (1 - - -) */  0x0100180c
/*  - O O (1 - - -) */  0x0100180d
/*  - O O (1 - - -) */  0x0100180e
/*  - O O (1 - - -) */  0x0100180f
/*  - O O (1 - - -) */  0x01001811
/*  - O O (1 - - -) */  0x01002000  // NewEffectCallEmit_TGS2005_2000Launch (?)
/*  - O O (1 - - -) */  0x01002001
/*  O O O (1 - - -) */  0x01002002
/*  O O O (1 - - -) */  0x01002003
/*  O O O (1 - - -) */  0x01002004
/*  O O O (1 - - -) */  0x01002006
/*  O O O (1 - - -) */  0x01002007
/*  - O O (1 - - -) */  0x0100200a
/*  O O O (1 - - -) */  0x0100200c
/*  - O O (1 - - -) */  0x0100200e
/*  O O O (1 - - -) */  0x0100200f
/*  - O O (1 - - -) */  0x01002010
/*  - O O (1 - - -) */  0x01002011
/*  - O O (1 - - -) */  0x01002012
/*  - O O (1 - - -) */  0x01002013
/*  - O O (1 - - -) */  0x01002014
/*  - O O (1 - - -) */  0x01002015
/*  - O O (1 - - -) */  0x01002016
/*  - O O (1 - - -) */  0x01002204
/*  - O O (1 - - -) */  0x01002501
/*  - O O (1 - - -) */  0x01002502
/*  - O O (1 - - -) */  0x01002503
/*  - O O (1 - - -) */  0x01002504
/*  - O O (1 - - -) */  0x01002505
/*  O O O (1 - - -) */  0x01002506  // NewCommonParticle_Demo_2506Launch
/*  O O O (1 - - -) */  0x01002507
/*  - O O (1 - - -) */  0x01002508
/*  - O O (1 - - -) */  0x01002509
/*  - O O (1 - - -) */  0x01002510
/*  - O O (1 - - -) */  0x01002511
/*  - O O (1 - - -) */  0x01002512
/*  - O O (1 - - -) */  0x01002513
/*  - O O (1 - - -) */  0x01002514
/*  - O O (1 - - -) */  0x01002515
/*  - O O (1 - - -) */  0x01002516
/*  - O O (1 - - -) */  0x01002517
/*  - O O (1 - - -) */  0x01002518
/*  - O O (1 - - -) */  0x01002519
/*  - O O (1 - - -) */  0x0100251a
/*  - O O (1 - - -) */  0x0100251b
/*  - O O (1 - - -) */  0x0100251c
/*  - O O (1 - - -) */  0x0100251d
/*  - O O (1 - - -) */  0x0100251e
/*  - O O (1 - - -) */  0x0100251f
/*  - O O (1 - - -) */  0x01002520
/*  - O O (1 - - -) */  0x01002521
/*  - O O (1 - - -) */  0x01002522
/*  - O O (1 - - -) */  0x01002523
/*  - O O (1 - - -) */  0x01002524
/*  - O O (1 - - -) */  0x01002526
/*  - O O (1 - - -) */  0x01002527
/*  - O O (1 - - -) */  0x01002528
/*  - O O (1 - - -) */  0x01002529
/*  - O O (1 - - -) */  0x0100252a
/*  - O O (1 - - -) */  0x0100252c
/*  - O O (1 - - -) */  0x0100252d
/*  - O O (1 - - -) */  0x0100252e
/*  - O O (1 - - -) */  0x0100252f
/*  - O O (1 - - -) */  0x01002530
/*  O O O (1 - - -) */  0x01002800
/*  - O O (1 - - -) */  0x01002801
/*  - O O (1 - - -) */  0x01002802
/*  - O O (1 - - -) */  0x01002804
/*  - O O (1 - - -) */  0x01002806
/*  - O O (1 - - -) */  0x01002807
/*  - O O (1 - - -) */  0x01002808
/*  - O O (1 - - -) */  0x01002809
/*  - O O (1 - - -) */  0x0100280a
/*  - O O (1 - - -) */  0x0100280b
/*  - O O (1 - - -) */  0x0100280c
/*  - O O (1 - - -) */  0x0100280d
/*  - O O (1 - - -) */  0x0100280e
/*  - O O (1 - - -) */  0x0100280f
/*  - O O (1 - - -) */  0x01002810
/*  - O O (1 - - -) */  0x01002811
/*  - O O (1 - - -) */  0x01002812
/*  - O O (1 - - -) */  0x01002813
/*  - O O (1 - - -) */  0x01002815
/*  - O O (1 - - -) */  0x01002816
/*  - O O (1 - - -) */  0x01002817
/*  - O O (1 - - -) */  0x01002818
/*  - O O (1 - - -) */  0x01002819
/*  - O O (1 - - -) */  0x0100281a
/*  - O O (1 - - -) */  0x01003d00
/*  - O O (1 - - -) */  0x0100f500
/*  - O O (1 - - -) */  0x0100f501
/*  - O O (1 - - -) */  0x0100f502
/*  - O O (1 - - -) */  0x0100f503
/*  - O O (1 - - -) */  0x0100f504
/*  - O O (1 - - -) */  0x0100f505
/*  O O O (1 - - -) */  0x0100ff01
/*  O O O (1 - - -) */  0x0100ff03
/*  O O O (1 2 - -) */  0x0100ff05  // NewDemoEffectInitialize_ff05Launch
/*  O O O (1 - - -) */  0x0100ff08  // NewShadowRange_DemoWrap_ff08Launch
/*  O O O (1 - - -) */  0x0100ff09  // NewFogAnimDemo_ff09Launch
/*  O O O (1 - - -) */  0x0100ff0a
/*  O O O (1 - - -) */  0x0100ff0b
/*  O O O (1 - - -) */  0x0100ff0c
/*  - O O (1 2 - -) */  0x0100ff0d  // NewEffectMeshVisInv_ff0dLaunch
/*  O O O (1 2 - -) */  0x0100ff0e  // NewExposureControl_DemoWrap_ff0eLaunch
/*  O O O (1 - - -) */  0x0100ff0f  // NewMGS3Glare_DemoWrap_ff0fLaunch
/*  O O O (1 - - -) */  0x0100ff10
/*  - O O (1 - - -) */  0x0100ff11  // NewDepthOfField_MGS3Compatible_ff11Launch
/*  - O O (1 - - -) */  0x0100ff13
/*  O O O (1 - - -) */  0x0100ff14
/*  - O O (1 - - -) */  0x0100ff16
/*  - O O (1 - - -) */  0x0100ff17
/*  O O O (1 2 - -) */  0x0100fff2  // GlobalEffect_SetEnvRange_fff2Launch
/*  O O O (1 2 - -) */  0x0100fff3  // DM_ChangeAmbient_fff3Launch
/*  O O O (1 - - -) */  0x0100fff4  // DM_ChangeParallel_fff4Launch
/*  O O O (1 - - -) */  0x0100fff5
/*  O O O (1 - - -) */  0x0110ff12
/*  - O O (1 - - -) */  0x0140ff04
/*  - O O (1 - - -) */  0x01f0f506

/*--- 0x02 Charas ---*/
/*  O O O (1 2 - N) */  0x0203737f
/*  O O O (1 2 - N) */  0x0204443e
/*  - O O (1 2 - N) */  0x022134b7
/*  - O O (1 2 - -) */  0x02269716
/*  - O O (1 2 - -) */  0x02456e88
/*  - O O (- 2 - -) */  0x02675751
/*  - O O (1 2 - -) */  0x0267973f
/*  O O O (1 2 - N) */  0x026b7d08
/*  - O O (1 2 - N) */  0x027bd9dd
/*  O O O (1 2 - N) */  0x027f461f
/*  O O O (1 2 - N) */  0x027f4620
/*  O O O (1 2 - N) */  0x027f4621
/*  O O O (1 2 - N) */  0x027f4622
/*  - O O (1 2 - -) */  0x027fb217
/*  O O O (1 2 - N) */  0x0281d9dd
/*  O O O (1 2 - -) */  0x028a9405
/*  O O O (1 2 - N) */  0x02914e5e
/*  - O O (1 2 - N) */  0x02914e5f
/*  - O O (1 2 - -) */  0x02994e5e
/*  - O O (1 2 - N) */  0x02994e5f
/*  - O O (1 2 - N) */  0x02994e60
/*  - O O (1 2 - N) */  0x029bd9de
/*  O O O (1 2 - N) */  0x02bb757f
/*  O O O (1 2 - N) */  0x02c2489d
/*  O O O (1 2 - N) */  0x02c2489e
/*  O O O (1 2 - N) */  0x02c2489f
/*  O O O (1 2 - N) */  0x02df898d
/*  - O O (1 2 - N) */  0x02e4dd9e
/*  O O O (1 2 - N) */  0x02f25bf9
/*  O O O (1 2 - N) */  0x02fc4a1c
/*  O O O (1 2 - N) */  0x02fd6fd5
/*  - O O (1 - - N) */  0x02ff181e
/*  O O O (1 2 - N) */  0x02ff3ddc
/*  O O O (1 2 - N) */  0x02ff3ddd

#endif // 0
#endif // {{{ END OF FILE }}}
