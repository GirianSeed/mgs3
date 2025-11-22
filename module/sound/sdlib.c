#include <string.h>
#include <kernel.h>
#include <libsd.h>
#include "sdlib.h"

#define VER(MM, mm) (((MM) << 8) | (mm))
ModuleInfo Module = { "kcej_sound_basic_lib", VER(2,11) };

//.rodata
static const short defCore[2] = { 0,1 };
static const short defVc[48] = {
    0, 0,
    2, 0,
    4, 0,
    6, 0,
    8, 0,
    10, 0,
    12, 0,
    14, 0,
    16, 0,
    18, 0,
    20, 0,
    22, 0,
    24, 0,
    26, 0,
    28, 0,
    30, 0,
    32, 0,
    34, 0,
    36, 0,
    38, 0,
    40, 0,
    42, 0,
    44, 0,
    46, 0
};
static const int dspSize[10] = {
    0x00000080,
    0x000026c0,
    0x00001f40,
    0x00004840,
    0x00007000,
    0x0000ae00,
    0x0000f6c0,
    0x00018040,
    0x00018040,
    0x00003c00
};
static const int dspNo[10] = { 0,2,1,4,5,6,7,8,9,3 };
static const int iDspNo[10] = { 0,2,1,9,3,4,5,6,7,8 };
static const short volumeTable[128] = {
    0x0000,0x0002,0x0006,0x000c,
    0x0014,0x001e,0x002a,0x0038,
    0x0048,0x005a,0x006f,0x0085,
    0x009d,0x00b7,0x00d3,0x00f2,
    0x0112,0x0134,0x0158,0x017f,
    0x01a7,0x01d1,0x01fe,0x022c,
    0x025c,0x028f,0x02c3,0x02fa,
    0x0332,0x036d,0x03a9,0x03e7,
    0x0428,0x046a,0x04af,0x04f6,
    0x053e,0x0589,0x05d5,0x0624,
    0x0675,0x06c7,0x071c,0x0773,
    0x07cb,0x0826,0x0883,0x08e1,
    0x0942,0x09a5,0x0a0a,0x0a70,
    0x0ad9,0x0b44,0x0bb1,0x0c20,
    0x0c91,0x0d04,0x0d78,0x0def,
    0x0e68,0x0ee3,0x0f60,0x0fdf,
    0x1060,0x10e3,0x1168,0x11ef,
    0x1278,0x1303,0x1390,0x1420,
    0x14b1,0x1544,0x15d9,0x1670,
    0x1709,0x17a5,0x1842,0x18e1,
    0x1982,0x1a26,0x1acb,0x1b72,
    0x1c1b,0x1cc7,0x1d74,0x1e23,
    0x1ed5,0x1f88,0x203e,0x20f5,
    0x21ae,0x226a,0x2327,0x23e7,
    0x24a8,0x256c,0x2631,0x26f9,
    0x27c2,0x288e,0x295c,0x2a2b,
    0x2afd,0x2bd1,0x2ca6,0x2d7e,
    0x2e58,0x2f33,0x3011,0x30f1,
    0x31d2,0x32b6,0x339c,0x3484,
    0x356e,0x3659,0x3747,0x3837,
    0x3929,0x3a1d,0x3b13,0x3c0b,
    0x3d05,0x3e01,0x3f00,0x3fff
};
static const short volumeTable2[128] = {
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0001,
    0x0001,0x0001,0x0001,0x0002,
    0x0002,0x0003,0x0004,0x0004,
    0x0005,0x0006,0x0008,0x0009,
    0x000b,0x000d,0x000f,0x0011,
    0x0014,0x0018,0x001b,0x0020,
    0x0024,0x002a,0x0030,0x0037,
    0x003e,0x0047,0x0051,0x005c,
    0x0068,0x0076,0x0085,0x0096,
    0x00a9,0x00bd,0x00d4,0x00ee,
    0x010a,0x0129,0x014c,0x0171,
    0x019b,0x01c9,0x01fb,0x0232,
    0x026e,0x02b0,0x02f8,0x0346,
    0x039c,0x03f9,0x045f,0x04ce,
    0x0546,0x05c9,0x0656,0x06f0,
    0x0796,0x084a,0x090d,0x09e0,
    0x0ac3,0x0bb9,0x0cc1,0x0dde,
    0x0f12,0x105c,0x11bf,0x133d,
    0x14d8,0x1690,0x1869,0x1a63,
    0x1c81,0x1ec6,0x2134,0x23cd,
    0x2694,0x298b,0x2cb6,0x3017,
    0x33b2,0x378a,0x3ba3,0x3fff
};
static const short panpotTable[128] = {
    0x3fff,0x3ffd,0x3ffa,0x3ff5,
    0x3fee,0x3fe5,0x3fda,0x3fcd,
    0x3fbd,0x3fac,0x3f99,0x3f84,
    0x3f6c,0x3f53,0x3f37,0x3f1a,
    0x3efa,0x3ed9,0x3eb5,0x3e90,
    0x3e68,0x3e3f,0x3e13,0x3de5,
    0x3db5,0x3d84,0x3d50,0x3d1a,
    0x3ce2,0x3ca8,0x3c6c,0x3c2e,
    0x3bee,0x3bac,0x3b68,0x3b22,
    0x3ada,0x3a90,0x3a44,0x39f6,
    0x39a5,0x3953,0x38ff,0x38a8,
    0x3850,0x37f6,0x3799,0x373b,
    0x36da,0x3678,0x3613,0x35ad,
    0x3544,0x34d9,0x346d,0x33fe,
    0x338d,0x331a,0x32a6,0x322f,
    0x31b6,0x313b,0x30be,0x303f,
    0x2fbe,0x2f3b,0x2eb6,0x2e2f,
    0x2da6,0x2d1b,0x2c8d,0x2bfe,
    0x2b6d,0x2ada,0x2a44,0x29ad,
    0x2914,0x2878,0x27db,0x273b,
    0x269a,0x25f6,0x2551,0x24a9,
    0x23ff,0x2354,0x22a6,0x21f6,
    0x2145,0x2091,0x1fdb,0x1f23,
    0x1e69,0x1dad,0x1cef,0x1c2f,
    0x1b6d,0x1aa9,0x19e3,0x191b,
    0x1851,0x1785,0x16b7,0x15e6,
    0x1514,0x1440,0x136a,0x1291,
    0x11b7,0x10da,0x0ffc,0x0f1b,
    0x0e39,0x0d54,0x0c6e,0x0b85,
    0x0a9b,0x09ae,0x08bf,0x07ce,
    0x06dc,0x05e7,0x04f0,0x03f7,
    0x02fc,0x01ff,0x0100,0
};

//.data
static int fSdLoop = 0;         // sizeof:4
static int fVcFlushReq = 0;     // sizeof:4
static int fVcFlushJob = 0;     // sizeof:4
static int mVcFlush = 0;        // sizeof:4
static int thRegist[16] = {0};  // sizeof:64
static int sdSync = 0;          // sizeof:4
static sint8 rQueueSpuTrans = 0;
static sint8 wQueueSpuTrans = 0;

//.sbss
int gTimerID;
int commonIrq;

//.bss
static iSys;                    // sizeof:0x3010
static int thSdLoop;            // sizeof:4
static int thSdLoopRegset;      // sizeof:4
static int thSdLoopPcm;         // sizeof:4
static keyOn;                   // sizeof:8
static keyOff;                  // sizeof:8
static keyOff2;                 // sizeof:8
static dspOn;                   // sizeof:8
static dspOff;                  // sizeof:8
static dspOff2;                 // sizeof:8
static dspBit;                  // sizeof:8
static noiseOn;                 // sizeof:8
static noiseOff;                // sizeof:8
static noiseOff2;               // sizeof:8
static noiseBit;                // sizeof:8
static update;                  // sizeof:8
static _stChan;                 // sizeof:0x780
static stDsp;                   // sizeof:0x18
static stNoise;                 // sizeof:8
static dmaQueueNo;              // sizeof:4
static stSpuAlloc;              // sizeof:0x80 (ES21: 0x100)
static queueSpuTrans;           // sizeof:0x100
static fSpuTrans;               // sizeof:8
static iPcm;                    // sizeof:0x80C (?)

static SdJobSpuWrite()
{
    /* todo: decompile */
}

SdSpuWrite()
{
    /* todo: decompile */
}

SdSetVoice()
{
    /* todo: decompile */
}

SdSetKey()
{
    /* todo: decompile */
}

static SdFlushSetDsp()
{
    static short step[2] = { 0, 0 }; //.data step.46
    static short wait[2] = { 0, 0 }; //.data wait.47
    static short idQ[2] = { -1, -1 }; //.data idQ.48
    static short szDsp[2]; //.bss szDsp.49
    static short adDsp[2]; //.bss adDsp.50
    /* todo: decompile */
}

static SdChannelCheck()
{
    /* todo: decompile */
}

static SdVoiceSet()
{
    /* todo: decompile */
}

static SdNoiseSet()
{
    /* todo: decompile */
}

static SdFlushSetVoice()
{
    /* todo: decompile */
}

static sortByAddr()
{
    /* todo: decompile */
}

SdSpuMalloc()
{
    /* todo: decompile */
}

SdPcmCtrl()
{
    /* todo: decompile */
}

static SdInitSpu()
{
    /* todo: decompile */
}

SdInitSdlib2()
{
    /* todo: decompile */
}

SdQuitSdlib2()
{
    /* todo: decompile */
}

static SdLoop()
{
    /* todo: decompile */
}

SdInitSdlib()
{
    /* todo: decompile */
}

int SdIsEmptyQueue(void)
{
    return (rQueueSpuTrans == wQueueSpuTrans);
}

SdIsTrans()
{
    /* todo: decompile */
}

SdGetSpuPlayAddr()
{
    /* todo: decompile */
}

SdGetKeyoffCount()
{
    /* todo: decompile */
}

SdSetKeyoffCount()
{
    /* todo: decompile */
}

SdGetVolume()
{
    /* todo: decompile */
}

SdGetKey()
{
    /* todo: decompile */
}

SdSetDsp()
{
    /* todo: decompile */
}

SdSetNoise()
{
    /* todo: decompile */
}

SdVol7ToVol14()
{
    /* todo: decompile */
}

SdMono()
{
    /* todo: decompile */
}

SdPanToVol14()
{
    /* todo: decompile */
}

SdSpuFree()
{
    /* todo: decompile */
}

SdVoiceFlush()
{
    /* todo: decompile */
}

SdGetHLine()
{
    /* todo: decompile */
}

SdGetUTime()
{
    /* todo: decompile */
}

SdGetTime()
{
    /* todo: decompile */
}

SdIrqRegist()
{
    static int num = 0; //.data num.69
    /* todo: decompile */
}

void SdQuitSdlib(void)
{
    fSdLoop = 0;
}

int sdlibInit()
{
    extern libhead sdlib_entry;

    if (RegisterLibraryEntries(&sdlib_entry) != 0) {
        return NO_RESIDENT_END;
    }
    return RESIDENT_END;
}

SdInitSpuWrite()
{
    /* todo: decompile */
}

static SdTransIrqCallback()
{
    /* todo: decompile */
}

static unsigned int SdIrqCallback(void *ptr)
{
    iWakeupThread(thSdLoop);
    iWakeupThread(thSdLoopRegset);
    return 0x2D000;
}

static SdLoopPcm()
{
    /* todo: decompile */
}

static SdLoopRegset()
{
    /* todo: decompile */
}
