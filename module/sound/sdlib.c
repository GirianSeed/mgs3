#include <string.h>
#include <kernel.h>
#include <libsd.h>
#include "sdlib.h"

#define SD_ALLOC_SIZE       16
#define SD_QUEUE_SIZE       16
#define SD_PCM_BUFFER_SIZE  0x400
#define SD_TRANSBUF_SIZE    0x3000
#define SD_STACK_SIZE       0x800

#define VER(MM, mm) (((MM) << 8) | (mm))
ModuleInfo Module = { "kcej_sound_basic_lib", VER(2,11) };

typedef struct {
    int unk1 : 8;
    int unk2 : 24;
    int unk3;
} SD_ALLOC;

typedef struct {
    int on : 1;
    int mono : 1;
    int sema1;
    int sema2;
    int sema3;
    char transbuf[SD_TRANSBUF_SIZE];
} SD_SYS;

typedef struct {
    char pad1[0x22];
    sint8 keyoffs;
    char pad2[0x5];
} SD_CHAN;

typedef struct {
    int unk1;
    uint8 voice;
    char unk3;
    char unk4;
    char unk5;
    int unk6;
} SD_DSP;

typedef void (*sd_pcm_job)(void *, int);

typedef struct {
    char buffer[2][SD_PCM_BUFFER_SIZE];
    unsigned int count;
    sd_pcm_job job1;
    sd_pcm_job job2;
} SD_PCM;

enum {
    SD_QUEUE_READY = 0,
    SD_QUEUE_BUSY = 1,
    SD_QUEUE_PENDING = 2,
};

typedef struct {
    char unk0;
    char unk1;
    uint8 status;
    char channel;
    unsigned int s_addr;
    void *m_addr;
    unsigned int size;
} SD_QUEUE;

//.rodata
static const int defCore[_SD_NCORE] = { 0,1 };
static const int defVc[_SD_NCHAN] = {
    0,
    2,
    4,
    6,
    8,
    10,
    12,
    14,
    16,
    18,
    20,
    22,
    24,
    26,
    28,
    30,
    32,
    34,
    36,
    38,
    40,
    42,
    44,
    46
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
static SD_SYS iSys;             // sizeof:0x3010
static int thSdLoop;            // sizeof:4
static int thSdLoopRegset;      // sizeof:4
static int thSdLoopPcm;         // sizeof:4
static int keyOn[_SD_NCORE];    // sizeof:8
static int keyOff[_SD_NCORE];   // sizeof:8
static int keyOff2[_SD_NCORE];  // sizeof:8
static int dspOn[_SD_NCORE];    // sizeof:8
static int dspOff[_SD_NCORE];   // sizeof:8
static int dspOff2[_SD_NCORE];  // sizeof:8
static int dspBit[_SD_NCORE];   // sizeof:8
static int noiseOn[_SD_NCORE];  // sizeof:8
static int noiseOff[_SD_NCORE]; // sizeof:8
static int noiseOff2[_SD_NCORE]; // sizeof:8
static int noiseBit[_SD_NCORE]; // sizeof:8
static int update[_SD_NCORE];   // sizeof:8
static SD_CHAN _stChan[_SD_NCORE][_SD_NCHAN]; // sizeof:0x780
static SD_DSP stDsp[_SD_NCORE]; // sizeof:0x18
static int stNoise[_SD_NCORE];  // sizeof:8
static dmaQueueNo;              // sizeof:4
static SD_ALLOC stSpuAlloc[SD_ALLOC_SIZE];    // sizeof:0x80 (ES21: 0x100)
static SD_QUEUE queueSpuTrans[SD_QUEUE_SIZE]; // sizeof:0x100
static sint8 fSpuTrans[2];      // sizeof:2
static SD_PCM iPcm;             // sizeof:0x80C

static SdJobSpuWrite()
{
    /* todo: decompile */
}

int SdSpuWrite(unsigned int dst, void *src, unsigned int size)
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


int SdInitSdlib(void)
{
    struct ThreadParam thread;
    struct SemaParam sema;

    memset(&iSys, 0, sizeof(iSys));

    if (iSys.on == SD_TRUE) {
        return SD_SUCCESS;
    }

    iSys.on = SD_TRUE;

    SdInitSdlib2();
    FlushDcache();

    sema.attr = SA_THPRI;
    sema.maxCount = 1;
    sema.initCount = 0;
    iSys.sema1 = CreateSema(&sema);

    sema.attr = SA_THPRI;
    sema.maxCount = 1;
    sema.initCount = 0;
    iSys.sema2 = CreateSema(&sema);

    sema.attr = SA_THPRI;
    sema.maxCount = 1;
    sema.initCount = 0;
    iSys.sema3 = CreateSema(&sema);

    SignalSema(iSys.sema1);
    SignalSema(iSys.sema2);
    SignalSema(iSys.sema3);

    thread.attr = TH_C;
    thread.entry = SdLoop;
    thread.initPriority = 24;
    thread.stackSize = SD_STACK_SIZE;
    thread.option = 0;

    if ((thSdLoop = CreateThread(&thread)) <= 0) {
        return SD_ERROR;
    }

    StartThread(thSdLoop, 0);

    thread.attr = TH_C;
    thread.entry = SdLoopRegset;
    thread.initPriority = 26;
    thread.stackSize = SD_STACK_SIZE;
    thread.option = 0;

    if ((thSdLoopRegset = CreateThread(&thread)) <= 0) {
        return SD_ERROR;
    }

    StartThread(thSdLoopRegset, 0);

    thread.attr = TH_C;
    thread.entry = SdLoopPcm;
    thread.initPriority = 25;
    thread.stackSize = SD_STACK_SIZE;
    thread.option = 0;

    if ((thSdLoopPcm = CreateThread(&thread)) <= 0) {
        return SD_ERROR;
    }

    StartThread(thSdLoopPcm, 0);

    gTimerID = AllocHardTimer(TC_SYSCLOCK, 32, 1);
    SetTimerHandler(gTimerID, SYSCLOCK / IRQ_TIME, SdIrqCallback, &thSdLoop);
    SetupHardTimer(gTimerID, TC_SYSCLOCK, TM_NO_GATE, 1);
    StartHardTimer(gTimerID);
    return SD_SUCCESS;
}

int SdIsEmptyQueue(void)
{
    return (rQueueSpuTrans == wQueueSpuTrans);
}

int SdIsTrans(int queue)
{
    int avail;

    if (queue <= 0) {
        avail = (fSpuTrans[1] == 0) ? 1 : -1;

        if (avail != -1) {
            return 0;
        }

        return -1;
    }

    return queueSpuTrans[queue - 1].status;
}

unsigned int SdGetSpuPlayAddr(sint8 core, sint8 voice)
{
    return sceSdGetAddr(defCore[core] | defVc[voice] | SD_VA_NAX);
}

int SdGetKeyoffCount(sint8 core, sint8 voice)
{
    return _stChan[core][voice].keyoffs;
}

/*
TODO: Fix -O3 breaking the match

int SdSetKeyoffCount(int core, int voice, int count)
{
    WaitSema(iSys.sema3);

    if (count > 127) {
        _stChan[core][voice].keyoffs = 127;
    } else {
        _stChan[core][voice].keyoffs = count;
    }

    SignalSema(iSys.sema3);
    return _stChan[core][voice].keyoffs;
}
*/

int SdGetVolume(sint8 core, sint8 voice)
{
    uint16 addr;
    uint32 lo, hi;

    addr = defCore[core] | defVc[voice];
    lo = sceSdGetParam(addr | SD_VP_VOLXL);
    hi = sceSdGetParam(addr | SD_VP_VOLXR);
    return (hi << 16) | lo;
}

void SdGetKey(uint8 param, int *out)
{
    switch (param) {
    case 0:
        out[0] = keyOff[0];
        out[1] = keyOff[1];
        break;
    case 1:
        out[0] = keyOn[0];
        out[1] = keyOn[1];
        break;
    case 2:
        out[0] = dspOff[0];
        out[1] = dspOff[1];
        break;
    case 3:
        out[0] = dspOn[0];
        out[1] = dspOn[1];
        break;
    case 4:
        out[0] = noiseOff[0];
        out[1] = noiseOff[1];
        break;
    case 5:
        out[0] = noiseOn[0];
        out[1] = noiseOn[1];
        break;
    default:
        break;
    }
}

void SdSetDsp(sint8 core, sint8 voice, sint8 arg2)
{
    int num;

    WaitSema(iSys.sema3);

    stDsp[core].voice = voice;
    num = dspNo[stDsp[core].voice];

    stDsp[core].unk3 = arg2;

    if ((num & 0xF) >= 8) {
        stDsp[core].voice = iDspNo[7];
    }

    SignalSema(iSys.sema3);
}

void SdSetNoise(sint8 core, int freq)
{
    WaitSema(iSys.sema3);
    stNoise[core] = (stNoise[core] & ~0x3F) | (freq & 0x3F);
    SignalSema(iSys.sema3);
}

int SdVol7ToVol14(int vol, int arg1)
{
    if (arg1 < 0)
    {
        return (((arg1 + 128) * volumeTable[vol]) / 128) + ((-arg1 * volumeTable2[vol]) / 128);
    }
    else
    {
        return (arg1 * vol) + (((128 - arg1) * volumeTable[vol]) / 128);
    }
}

int SdMono(int mono)
{
    iSys.mono = mono;
    return SD_SUCCESS;
}

int SdPanToVol14(sint8 pan, sint8 side)
{
    if (iSys.mono)
    {
        return panpotTable[64];
    }

    return (side == 0) ? panpotTable[pan] : panpotTable[127 - pan];
}

int SdSpuFree(int arg0)
{
    short i;

    WaitSema(iSys.sema2);

    for (i = 0; i < SD_ALLOC_SIZE; i++)
    {
        if ((stSpuAlloc[i].unk1 == 1) && (stSpuAlloc[i].unk2 == arg0)) {
            stSpuAlloc[i].unk1 = 0;
            break;
        }
    }

    sortByAddr();
    SignalSema(iSys.sema2);
    return SD_SUCCESS;
}

void SdVoiceFlush(int flush)
{
    mVcFlush = flush;
    fVcFlushReq = 1 - fVcFlushJob;
}

int SdGetHLine(void)
{
    return (sdSync * IRQ_HCOUNT) + GetTimerCounter(gTimerID);
}

int SdGetUTime(void)
{
    struct SysClock clock;
    int sec;
    int usec;

    GetSystemTime(&clock);
    SysClock2USec(&clock, &sec, &usec);

    return usec + sec * 1000000;
}

int SdGetTime(void)
{
    struct SysClock clock;
    int sec;
    int usec;

    GetSystemTime(&clock);
    SysClock2USec(&clock, &sec, &usec);

    return (unsigned int)usec / 1000 + sec * 1000;
}

int SdIrqRegist(int thid)
{
    static int num = 0;

    if (num < 0 || num >= 16) {
        return SD_ERROR;
    }

    thRegist[num++] = thid;
    return num;
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

void SdInitSpuWrite(void)
{
    wQueueSpuTrans = 0;
    rQueueSpuTrans = 0;
    fSpuTrans[0] = fSpuTrans[1] = 1;
    SdSpuWrite(0x5100, NULL, 64);
    SdSpuWrite(0x5200, NULL, 64);
}

static void SdTransIrqCallback(void)
{
    int old;
    int which;

    iReleaseWaitThread(thSdLoopPcm);

    if (iPcm.job2) {
        CpuSuspendIntr(&old);
        which = ((sceSdBlockTransStatus(0, 0) >> 24) ^ 1) & 1;
        iPcm.job2(iPcm.buffer[which], 1);
        CpuResumeIntr(old);
    }
}

static unsigned int SdIrqCallback(void *ptr)
{
    iWakeupThread(thSdLoop);
    iWakeupThread(thSdLoopRegset);
    return SYSCLOCK / IRQ_TIME;
}

static void SdLoopPcm(void)
{
    int which;

    while (fSdLoop == 0) {
        SleepThread();
    }

    while (fSdLoop != 0) {
        SleepThread();
        iPcm.count++;

        if (iPcm.job1) {
            which = ((sceSdBlockTransStatus(0, 0) >> 24) ^ 1) & 1;
            iPcm.job1(iPcm.buffer[which], 1);
        }
    }

    ExitThread();
}

static void SdLoopRegset(void)
{
    while (fSdLoop == 0) {
        SleepThread();
    }

    while (fSdLoop != 0) {
        SleepThread();
        CancelWakeupThread(GetThreadId());

        switch (mVcFlush) {
        case 0:
            SdFlushSetVoice();
            break;
        case 1:
            if (fVcFlushJob != fVcFlushReq) {
                SdFlushSetVoice();
                fVcFlushJob = fVcFlushReq;
            }
            break;
        }
    }

    ExitThread();
}
