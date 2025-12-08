#ifndef __KCEJ_SDLIB_H__
#define __KCEJ_SDLIB_H__

typedef signed int      sint32;
typedef signed short    sint16;
typedef signed char     sint8;
typedef unsigned int    uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;
typedef sint32          int32;
typedef sint16          int16;
typedef sint8           int8;

// NOTE: Copied from keyboardmania
enum {
    IRQ_TIME = 200,         // km: IRQ_TIME = 250
    IRQ_HCOUNT = 79,        // km: IRQ_HCOUNT = 63
    SYSCLOCK = 36864000,    // added for MGS3
    SD_FALSE = 0,
    SD_TRUE = 1,
    SD_OFF = 0,
    SD_ON = 1,
    SD_LOCK = 2,
    SD_BUSY = -2,
    SD_ERROR = -1,
    SD_SUCCESS = 0,
    SD_JOB = 1,
    SD_READY = 2,
    SD_KEY_OFF = 0,
    SD_KEY_ON = 1,
    SD_DSP_OFF = 2,
    SD_DSP_ON = 3,
    _SD_NCORE = 2,
    _SD_NCHAN = 24,
    _SD_CH00 = 0,
    _SD_CH01 = 1,
    _SD_CH02 = 2,
    _SD_CH03 = 3,
    _SD_CH04 = 4,
    _SD_CH05 = 5,
    _SD_CH06 = 6,
    _SD_CH07 = 7,
    _SD_CH08 = 8,
    _SD_CH09 = 9,
    _SD_CH10 = 10,
    _SD_CH11 = 11,
    _SD_CH12 = 12,
    _SD_CH13 = 13,
    _SD_CH14 = 14,
    _SD_CH15 = 15,
    _SD_CH16 = 16,
    _SD_CH17 = 17,
    _SD_CH18 = 18,
    _SD_CH19 = 19,
    _SD_CH20 = 20,
    _SD_CH21 = 21,
    _SD_CH22 = 22,
    _SD_CH23 = 23,
    SD_CH00 = (1 << _SD_CH00),  // 0x00000001
    SD_CH01 = (1 << _SD_CH01),  // 0x00000002
    SD_CH02 = (1 << _SD_CH02),  // 0x00000004
    SD_CH03 = (1 << _SD_CH03),  // 0x00000008
    SD_CH04 = (1 << _SD_CH04),  // 0x00000010
    SD_CH05 = (1 << _SD_CH05),  // 0x00000020
    SD_CH06 = (1 << _SD_CH06),  // 0x00000040
    SD_CH07 = (1 << _SD_CH07),  // 0x00000080
    SD_CH08 = (1 << _SD_CH08),  // 0x00000100
    SD_CH09 = (1 << _SD_CH09),  // 0x00000200
    SD_CH10 = (1 << _SD_CH10),  // 0x00000400
    SD_CH11 = (1 << _SD_CH11),  // 0x00000800
    SD_CH12 = (1 << _SD_CH12),  // 0x00001000
    SD_CH13 = (1 << _SD_CH13),  // 0x00002000
    SD_CH14 = (1 << _SD_CH14),  // 0x00004000
    SD_CH15 = (1 << _SD_CH15),  // 0x00008000
    SD_CH16 = (1 << _SD_CH16),  // 0x00010000
    SD_CH17 = (1 << _SD_CH17),  // 0x00020000
    SD_CH18 = (1 << _SD_CH18),  // 0x00040000
    SD_CH19 = (1 << _SD_CH19),  // 0x00080000
    SD_CH20 = (1 << _SD_CH20),  // 0x00100000
    SD_CH21 = (1 << _SD_CH21),  // 0x00200000
    SD_CH22 = (1 << _SD_CH22),  // 0x00400000
    SD_CH23 = (1 << _SD_CH23),  // 0x00800000
    //SD_ALLCH = 0x00ffffff,
    SD_ALLCH = (SD_CH00 | SD_CH01 | SD_CH02 | SD_CH03 | SD_CH04 |
                SD_CH05 | SD_CH06 | SD_CH07 | SD_CH08 | SD_CH09 |
                SD_CH10 | SD_CH11 | SD_CH12 | SD_CH13 | SD_CH14 |
                SD_CH15 | SD_CH16 | SD_CH17 | SD_CH18 | SD_CH19 |
                SD_CH20 | SD_CH21 | SD_CH22 | SD_CH23),
    _SD_VOICE_VOLL = 0,
    _SD_VOICE_VOLR = 1,
    _SD_VOICE_CENTER = 2,
    _SD_VOICE_NOTE = 3,
    _SD_VOICE_PITCH = 4,
    _SD_VOICE_ADDR = 5,
    _SD_VOICE_ADSR = 6,
    SD_VC_VOLL  = (1 << _SD_VOICE_VOLL),  // 0x01
    SD_VC_VOLR  = (1 << _SD_VOICE_VOLR),  // 0x02
    SD_VC_PITCH = (1 << _SD_VOICE_PITCH), // 0x10
    SD_VC_ADDR  = (1 << _SD_VOICE_ADDR),  // 0x20
    SD_VC_ADSR  = (1 << _SD_VOICE_ADSR),  // 0x40
};

// NOTE: Copied from keyboardmania
typedef struct { // 0x20
    /* 0x000 */ uint32 mask;
    /* 0x004 */ uint32 chans[2];
    /* 0x00c */ sint16 volL;
    /* 0x00e */ sint16 volR;
    /* 0x010 */ uint16 pitch;
    /* 0x012 */ uint16 pad[3];
    /* 0x018 */ uint32 addr;
    /* 0x01c */ uint32 adsr;
} SD_VOICE;

#ifdef __cplusplus
extern "C" {
#endif

/* sdlib.c */
int SdSpuWrite(uint32 dst, void *src, int size);
// SdSetVoice();
// SdSetKey();
int SdSpuMalloc(int size);
// SdPcmCtrl();
int SdInitSdlib(void);
int SdIsEmptyQueue(void);
int SdIsTrans(int queue);
uint32 SdGetSpuPlayAddr(sint8 core, sint8 voice);
int SdGetKeyoffCount(sint8 core, sint8 voice);
int SdSetKeyoffCount(int core, int voice, int count);
int SdGetVolume(sint8 core, sint8 voice);
void SdGetKey(uint8 param, int *out);
void SdSetDsp(sint8 core, sint8 voice, sint8 arg2);
void SdSetNoise(sint8 core, int freq);
int SdVol7ToVol14(int vol, int arg1);
int SdMono(int mono);
int SdPanToVol14(sint8 pan, sint8 side);
int SdSpuFree(int ptr);
void SdVoiceFlush(int flush);
int SdGetHLine(void);
int SdGetUTime(void);
int SdGetTime(void);
int SdIrqRegist(int thid);
void SdQuitSdlib(void);

#ifdef __cplusplus
}
#endif
#endif // __KCEJ_SDLIB_H__
