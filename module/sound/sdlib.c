#include <string.h>
#include <kernel.h>
#include <libsd.h>
#include "sdlib.h"

#define VER(MM, mm) (((MM) << 8) | (mm))
ModuleInfo Module = { "kcej_sound_basic_lib", VER(2,11) };

/*---------------------------------------------------------------------------*/

#define SD_ALLOC_SIZE       16
#define SD_QUEUE_SIZE       16
#define SD_PCM_BUFFER_SIZE  0x400U
#define SD_CLEARBUFF_SIZE   0x3000U
#define SD_STACK_SIZE       0x800U

typedef struct {
    int used : 8;
    int addr : 24;
    int size : 24;
} SD_ALLOC;

typedef struct {
    int fSdlibActive:1;
    int fSdMono:1;
    int smSpuWrite;
    int smSpuAlloc;
    int smSpuSet;
    char clearBuff[SD_CLEARBUFF_SIZE];
} SD_SYS;

typedef struct {
    SD_VOICE voice;
    sint8 unk1;
    sint8 unk2;
    sint8 keyoffs;
    sint8 unk3;
    uint32 next;
} SD_CHAN;

typedef struct {
    sint32 addr:24;
    uint32 mode:8;
    uint32 newmode:8;
    sint32 newdepth:8;
    sint32 depth:16;
    sint32 atten;
} SD_DSP;

typedef struct {
    char buffer[2][SD_PCM_BUFFER_SIZE];
    uint32 count;
    sd_pcm_job job1;
    sd_pcm_job job2;
} SD_PCM;

enum {
    SD_QUEUE_READY = 0,
    SD_QUEUE_BUSY = 1,
    SD_QUEUE_PENDING = 2,
};

typedef struct {
    short unk0;
    sint8 status;
    char channel;
    uint32 s_addr;
    void *m_addr;
    int size;
} SD_QUEUE;

typedef struct {
    uint32 newclk:6;
    uint32 clk:6;
} SD_NOISE;

/*---------------------------------------------------------------------------*/

//.rodata
static const int defCore[_SD_NCORE] = { 0,1 };
static const int defVc[_SD_NCHAN] = {
    0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46
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
    0x0000,0x0002,0x0006,0x000c,0x0014,0x001e,0x002a,0x0038,
    0x0048,0x005a,0x006f,0x0085,0x009d,0x00b7,0x00d3,0x00f2,
    0x0112,0x0134,0x0158,0x017f,0x01a7,0x01d1,0x01fe,0x022c,
    0x025c,0x028f,0x02c3,0x02fa,0x0332,0x036d,0x03a9,0x03e7,
    0x0428,0x046a,0x04af,0x04f6,0x053e,0x0589,0x05d5,0x0624,
    0x0675,0x06c7,0x071c,0x0773,0x07cb,0x0826,0x0883,0x08e1,
    0x0942,0x09a5,0x0a0a,0x0a70,0x0ad9,0x0b44,0x0bb1,0x0c20,
    0x0c91,0x0d04,0x0d78,0x0def,0x0e68,0x0ee3,0x0f60,0x0fdf,
    0x1060,0x10e3,0x1168,0x11ef,0x1278,0x1303,0x1390,0x1420,
    0x14b1,0x1544,0x15d9,0x1670,0x1709,0x17a5,0x1842,0x18e1,
    0x1982,0x1a26,0x1acb,0x1b72,0x1c1b,0x1cc7,0x1d74,0x1e23,
    0x1ed5,0x1f88,0x203e,0x20f5,0x21ae,0x226a,0x2327,0x23e7,
    0x24a8,0x256c,0x2631,0x26f9,0x27c2,0x288e,0x295c,0x2a2b,
    0x2afd,0x2bd1,0x2ca6,0x2d7e,0x2e58,0x2f33,0x3011,0x30f1,
    0x31d2,0x32b6,0x339c,0x3484,0x356e,0x3659,0x3747,0x3837,
    0x3929,0x3a1d,0x3b13,0x3c0b,0x3d05,0x3e01,0x3f00,0x3fff
};
static const short volumeTable2[128] = {
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
    0x0000,0x0000,0x0000,0x0001,0x0001,0x0001,0x0001,0x0002,
    0x0002,0x0003,0x0004,0x0004,0x0005,0x0006,0x0008,0x0009,
    0x000b,0x000d,0x000f,0x0011,0x0014,0x0018,0x001b,0x0020,
    0x0024,0x002a,0x0030,0x0037,0x003e,0x0047,0x0051,0x005c,
    0x0068,0x0076,0x0085,0x0096,0x00a9,0x00bd,0x00d4,0x00ee,
    0x010a,0x0129,0x014c,0x0171,0x019b,0x01c9,0x01fb,0x0232,
    0x026e,0x02b0,0x02f8,0x0346,0x039c,0x03f9,0x045f,0x04ce,
    0x0546,0x05c9,0x0656,0x06f0,0x0796,0x084a,0x090d,0x09e0,
    0x0ac3,0x0bb9,0x0cc1,0x0dde,0x0f12,0x105c,0x11bf,0x133d,
    0x14d8,0x1690,0x1869,0x1a63,0x1c81,0x1ec6,0x2134,0x23cd,
    0x2694,0x298b,0x2cb6,0x3017,0x33b2,0x378a,0x3ba3,0x3fff
};
static const short panpotTable[128] = {
    0x3fff,0x3ffd,0x3ffa,0x3ff5,0x3fee,0x3fe5,0x3fda,0x3fcd,
    0x3fbd,0x3fac,0x3f99,0x3f84,0x3f6c,0x3f53,0x3f37,0x3f1a,
    0x3efa,0x3ed9,0x3eb5,0x3e90,0x3e68,0x3e3f,0x3e13,0x3de5,
    0x3db5,0x3d84,0x3d50,0x3d1a,0x3ce2,0x3ca8,0x3c6c,0x3c2e,
    0x3bee,0x3bac,0x3b68,0x3b22,0x3ada,0x3a90,0x3a44,0x39f6,
    0x39a5,0x3953,0x38ff,0x38a8,0x3850,0x37f6,0x3799,0x373b,
    0x36da,0x3678,0x3613,0x35ad,0x3544,0x34d9,0x346d,0x33fe,
    0x338d,0x331a,0x32a6,0x322f,0x31b6,0x313b,0x30be,0x303f,
    0x2fbe,0x2f3b,0x2eb6,0x2e2f,0x2da6,0x2d1b,0x2c8d,0x2bfe,
    0x2b6d,0x2ada,0x2a44,0x29ad,0x2914,0x2878,0x27db,0x273b,
    0x269a,0x25f6,0x2551,0x24a9,0x23ff,0x2354,0x22a6,0x21f6,
    0x2145,0x2091,0x1fdb,0x1f23,0x1e69,0x1dad,0x1cef,0x1c2f,
    0x1b6d,0x1aa9,0x19e3,0x191b,0x1851,0x1785,0x16b7,0x15e6,
    0x1514,0x1440,0x136a,0x1291,0x11b7,0x10da,0x0ffc,0x0f1b,
    0x0e39,0x0d54,0x0c6e,0x0b85,0x0a9b,0x09ae,0x08bf,0x07ce,
    0x06dc,0x05e7,0x04f0,0x03f7,0x02fc,0x01ff,0x0100,0
};

//.data
static int fSdLoop = SD_FALSE;  // sizeof:4
static int fVcFlushReq = SD_FALSE; // sizeof:4
static int fVcFlushJob = SD_FALSE; // sizeof:4
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
static uint32 update[_SD_NCORE];   // sizeof:8
static SD_CHAN _stChan[_SD_NCORE][_SD_NCHAN]; // sizeof:0x780
static SD_DSP stDsp[_SD_NCORE]; // sizeof:0x18
static SD_NOISE stNoise[_SD_NCORE];  // sizeof:8
static sint16 dmaQueueNo[2];    // sizeof:4
static SD_ALLOC stSpuAlloc[SD_ALLOC_SIZE];    // sizeof:0x80 (ES21: 0x100)
static SD_QUEUE queueSpuTrans[SD_QUEUE_SIZE]; // sizeof:0x100
static sint8 fSpuTrans[2];      // sizeof:2
static SD_PCM iPcm;             // sizeof:0x80C

/*---------------------------------------------------------------------------*/

static int SdJobSpuWrite(void)
{
    int channel;

    while (rQueueSpuTrans != wQueueSpuTrans) {
        if (queueSpuTrans[rQueueSpuTrans].size > 0) {
            channel = -1;

            if (!fSpuTrans[1]) {
                channel = 1;
            }

            if (channel == -1) {
                return 1;
            }

            queueSpuTrans[rQueueSpuTrans].channel = channel;

            if (sceSdVoiceTrans(
                queueSpuTrans[rQueueSpuTrans].channel, 0,
                queueSpuTrans[rQueueSpuTrans].m_addr,
                queueSpuTrans[rQueueSpuTrans].s_addr,
                queueSpuTrans[rQueueSpuTrans].size) < 0) {
                break;
            }

            queueSpuTrans[rQueueSpuTrans].size = 0;
            queueSpuTrans[rQueueSpuTrans].status = SD_QUEUE_BUSY;
            queueSpuTrans[rQueueSpuTrans].unk0 = 0;

            dmaQueueNo[channel] = rQueueSpuTrans;
            fSpuTrans[channel] = SD_TRUE;
        }

        rQueueSpuTrans = (rQueueSpuTrans + 1) % SD_QUEUE_SIZE;
    }

    return SD_SUCCESS;
}

#if 0
// TODO: Fix store being moved out of delay slot
int SdSpuWrite(uint32 dst, void *src, int size)
{
    int index;

    if (((wQueueSpuTrans + 1) % SD_QUEUE_SIZE) == rQueueSpuTrans) {
        return SD_ERROR;
    }

    WaitSema(iSys.smSpuWrite);
    index = wQueueSpuTrans;

    if (size == 0) {
        queueSpuTrans[index].status = SD_QUEUE_READY;
    } else {
        queueSpuTrans[index].status = SD_QUEUE_PENDING;
    }

    if (src) {
        queueSpuTrans[index].channel = -1;
        queueSpuTrans[index].s_addr = dst;
        queueSpuTrans[index].m_addr = src;
        queueSpuTrans[index].size = size;

        wQueueSpuTrans = (wQueueSpuTrans + 1) % SD_QUEUE_SIZE;
    } else {
        if (size % SD_CLEARBUFF_SIZE) {
            index = wQueueSpuTrans;
            queueSpuTrans[index].status = SD_QUEUE_PENDING;
            queueSpuTrans[index].channel = -1;
            queueSpuTrans[index].s_addr = dst;
            queueSpuTrans[index].m_addr = iSys.clearBuff;
            queueSpuTrans[index].size = size % SD_CLEARBUFF_SIZE;

            wQueueSpuTrans = (wQueueSpuTrans + 1) % SD_QUEUE_SIZE;
            size -= size % SD_CLEARBUFF_SIZE;
        }

        while (size > 0) {
            index = wQueueSpuTrans;
            queueSpuTrans[index].status = SD_QUEUE_PENDING;
            queueSpuTrans[index].channel = -1;
            queueSpuTrans[index].s_addr = dst;
            queueSpuTrans[index].m_addr = iSys.clearBuff;
            queueSpuTrans[index].size = SD_CLEARBUFF_SIZE;

            wQueueSpuTrans = (wQueueSpuTrans + 1) % SD_QUEUE_SIZE;
            size -= SD_CLEARBUFF_SIZE;
        }
    }

    SignalSema(iSys.smSpuWrite);
    return index + 1;
}
#endif

void SdSetVoice(SD_VOICE *voice)
{
    sint8 c, v;
    int bit;

    WaitSema(iSys.smSpuSet);

    for (c = 0; c < _SD_NCORE; c++) {
        bit = 1;

        for (v = 0, bit = 1; v < _SD_NCHAN; v++, bit <<= 1) {
            if (!(voice->chans[c] & bit)) {
                continue;
            }

            if (voice->mask & SD_VC_VOLL) {
                _stChan[c][v].voice.volL = voice->volL;
                _stChan[c][v].voice.mask |= SD_VC_VOLL;
            }

            if (voice->mask & SD_VC_VOLR) {
                _stChan[c][v].voice.volR = voice->volR;
                _stChan[c][v].voice.mask |= SD_VC_VOLR;
            }

            if (voice->mask & SD_VC_PITCH) {
                _stChan[c][v].voice.pitch = voice->pitch;
                _stChan[c][v].voice.mask |= SD_VC_PITCH;
            }

            if (voice->mask & SD_VC_ADDR) {
                _stChan[c][v].voice.addr = voice->addr;
                _stChan[c][v].voice.mask |= SD_VC_ADDR;
            }

            if (voice->mask & SD_VC_ADSR) {
                _stChan[c][v].voice.adsr = voice->adsr;
                _stChan[c][v].voice.mask |= SD_VC_ADSR;
            }

            _stChan[c][v].voice.chans[c] = bit;
            update[c] |= bit;
        }
    }

    SignalSema(iSys.smSpuSet);
}

void SdSetKey(uint8 param, int *key)
{
    sint16 c;
    int bits;
    int voice;

    WaitSema(iSys.smSpuSet);

    for (c = 0; c < _SD_NCORE; c++) {
        switch(param) {
        case SD_KEY_ON:
            keyOn[c] |= key[c];
            bits = key[c];
            voice = 0;

            while (bits != 0 && voice < _SD_NCHAN) {
                if (bits & 0x1) {
                    _stChan[c][voice].keyoffs = 4;
                }

                voice++;
                bits >>= 1;
            }
            break;
        case SD_KEY_OFF:
            keyOff[c] |= key[c] & ~keyOn[c];
            keyOff2[c] |= key[c] & keyOn[c];
            break;
        case SD_DSP_OFF:
            dspOff[c] |= key[c] & ~dspOn[c];
            dspOff2[c] |= key[c] & dspOn[c];
            break;
        case SD_DSP_ON:
            dspOn[c] |= key[c];
            break;
        case SD_NOISE_OFF:
            noiseOff[c] |= key[c] & ~noiseOn[c];
            noiseOff2[c] |= key[c] & noiseOn[c];
            break;
        case SD_NOISE_ON:
            noiseOn[c] |= key[c];
            break;
        }
    }

    SignalSema(iSys.smSpuSet);
}

static void SdFlushSetDsp(void)
{
    static short step[_SD_NCORE] = { 0, 0 }; //.data step.46
    static short wait[_SD_NCORE] = { 0, 0 }; //.data wait.47
    static short idQ[_SD_NCORE] = { -1, -1 }; //.data idQ.48
    static short szDsp[_SD_NCORE]; //.bss szDsp.49
    static short adDsp[_SD_NCORE]; //.bss adDsp.50

    sceSdEffectAttr attr;
    sceSdEffectAttr attr2;
    sint16 c;
    int index;
    int status;

    for (c = 0; c < _SD_NCORE; c++) {
        switch (step[c]) {
        case 0:
            if (stDsp[c].mode != stDsp[c].newmode) {
                stDsp[c].newmode &= 0xF;
                sceSdSetCoreAttr(defCore[c] | SD_C_EFFECT_ENABLE, 0);
                step[c] = 0x3C;
            } else if (stDsp[c].depth != (stDsp[c].newdepth << 8)) {
                stDsp[c].atten = (stDsp[c].newdepth << 8) - stDsp[c].depth;
                stDsp[c].depth = stDsp[c].newdepth << 8;
                step[c] = 0x8C;
            }
            break;
        case 0x3C:
            adDsp[c] = stDsp[c].addr / 64;
            szDsp[c] = dspSize[iDspNo[7]] / 64;
            /* fallthrough */
        case 0x3F:
            if (szDsp[c] > 768) {
                idQ[c] = SdSpuWrite(adDsp[c] * 64, NULL, SD_CLEARBUFF_SIZE);
                adDsp[c] += SD_CLEARBUFF_SIZE / 64;
                szDsp[c] -= SD_CLEARBUFF_SIZE / 64;
            } else {
                idQ[c] = SdSpuWrite(adDsp[c] * 64, NULL, szDsp[c] * 64);
                adDsp[c] = 0;
                szDsp[c] = 0;
            }

            step[c] = 0x41;
            break;
        case 0x41:
            if (idQ[c] <= 0) {
                index = -1;
                if (fSpuTrans[1] == 0) {
                    index = 1;
                }

                status = -1;
                if (index != -1) {
                    status = 0;
                }
            } else {
                status = queueSpuTrans[idQ[c] - 1].status;
            }

            if (status == SD_QUEUE_READY) {
                if (szDsp[c] > 0) {
                    step[c] = 0x3F;
                } else {
                    idQ[c] = -1;
                    step[c] = 0x64;
                }
            }
            break;
        case 0x64:
            if (wait[c] > 0) {
                wait[c]--;
                break;
            }

            if (stDsp[c].mode != stDsp[c].newmode) {
                sceSdSetCoreAttr(defCore[c] | SD_C_EFFECT_ENABLE, 0);

                attr.mode = SD_REV_MODE_OFF;
                attr.depth_L = attr.depth_R = 0;
                sceSdSetEffectAttr(defCore[c], &attr);

                stDsp[c].mode = stDsp[c].newmode;
                stDsp[c].atten = stDsp[c].depth = stDsp[c].newdepth << 8;
                step[c] = 0x6E;
            } else if (stDsp[c].depth != (stDsp[c].newdepth << 8)) {
                sceSdSetCoreAttr(defCore[c] | SD_C_EFFECT_ENABLE, 1);

                stDsp[c].atten = stDsp[c].depth = stDsp[c].newdepth << 8;
                sceSdSetParam(defCore[c] | SD_P_EVOLL, 0);
                sceSdSetParam(defCore[c] | SD_P_EVOLR, 0);
                step[c] = 0x8C;
            }
            break;
        case 0x6E:
            attr2.depth_L = attr2.depth_R = 0;
            attr2.mode = stDsp[c].mode;
            sceSdSetEffectAttr(defCore[c], &attr2);
            step[c] = 0x82;
            break;
        case 0x82:
            sceSdSetCoreAttr(defCore[c] | SD_C_EFFECT_ENABLE, 1);
            step[c] = 0x8C;
            break;
        case 0x8C:
            stDsp[c].atten = (stDsp[c].atten * 7) / 8;
            if (stDsp[c].atten == 0) {
                stDsp[c].depth = stDsp[c].newdepth << 8;
                sceSdSetParam(defCore[c] | SD_P_EVOLL, stDsp[c].depth & 0xFF00);
                sceSdSetParam(defCore[c] | SD_P_EVOLR, stDsp[c].depth);
                step[c] = 0;
            } else {
                sceSdSetParam(defCore[c] | SD_P_EVOLL, stDsp[c].depth - stDsp[c].atten);
                sceSdSetParam(defCore[c] | SD_P_EVOLR, stDsp[c].depth - stDsp[c].atten);
            }
            break;
        }

        if (dspOn[c] != 0 || dspOff[c] != 0) {
            dspBit[c] &= ~dspOff[c];
            dspBit[c] |= dspOn[c];

            dspOff[c] = dspOff2[c];
            dspOff2[c] = 0;
            dspOn[c] = 0;

            sceSdSetSwitch(defCore[c] | SD_S_VMIXEL, dspBit[c]);
            sceSdSetSwitch(defCore[c] | SD_S_VMIXER, dspBit[c]);
        }
    }
}

static void SdChannelCheck(void)
{
    int core;
    int voice;
    SD_CHAN *chan;
    int bit;

    for (core = 0; core < _SD_NCORE; core++) {
        chan = _stChan[core];
        bit = 1;

        for (voice = 0; voice < _SD_NCHAN; voice++, chan++) {
            if (!(keyOn[core] & bit) && (sceSdGetParam(defCore[core] | defVc[voice] | SD_VP_ENVX) == 0)) {
                if (chan->keyoffs == 1) {
                    keyOff[core] |= chan->keyoffs << voice;
                }

                if (chan->keyoffs > 0) {
                    chan->keyoffs--;
                }

                chan->next = 0;
            } else {
                chan->next = sceSdGetAddr(defCore[core] | defVc[voice] | SD_VA_NAX);
            }

            bit <<= 1;
        }
    }
}

static void SdVoiceSet(void)
{
    int core;
    int voice;
    SD_CHAN *chan;

    for (core = 0; core < _SD_NCORE; core++) {
        for (voice = 0; voice < _SD_NCHAN; voice++) {
            if (update[core] & 0x1) {
                chan = &_stChan[core][voice];

                if (chan->voice.mask & SD_VC_VOLR) {
                    sceSdSetParam(defCore[core] | defVc[voice] | SD_VP_VOLR, chan->voice.volR);
                }

                if (chan->voice.mask & SD_VC_VOLL) {
                    sceSdSetParam(defCore[core] | defVc[voice] | SD_VP_VOLL, chan->voice.volL);
                }

                if (chan->voice.mask & SD_VC_PITCH) {
                    sceSdSetParam(defCore[core] | defVc[voice] | SD_VP_PITCH, chan->voice.pitch);
                }

                if (chan->voice.mask & SD_VC_ADDR) {
                    sceSdSetAddr(defCore[core] | defVc[voice] | SD_VA_SSA, chan->voice.addr);
                }

                if (chan->voice.mask & SD_VC_ADSR) {
                    sceSdSetParam(defCore[core] | defVc[voice] | SD_VP_ADSR1, chan->voice.adsr);
                    sceSdSetParam(defCore[core] | defVc[voice] | SD_VP_ADSR2, chan->voice.adsr >> 16);
                }

                chan->voice.mask = 0;
            }

            update[core] >>= 1;
        }
    }
}

static void SdNoiseSet(void)
{
    int i;

    for (i = 0; i < _SD_NCORE; i++) {
        if (stNoise[i].clk != stNoise[i].newclk) {
            stNoise[i].clk = stNoise[i].newclk;
            sceSdSetCoreAttr(defCore[i] | SD_C_NOISE_CLK, stNoise[i].clk);
        }

        if ((noiseOn[i] != 0) || (noiseOff[i] != 0)) {
            noiseBit[i] &= ~noiseOff[i];
            noiseBit[i] |= noiseOn[i];
            noiseOff[i] = noiseOff2[i];
            noiseOn[i] = noiseOff2[i] = 0;
            sceSdSetSwitch(defCore[i] | SD_S_NON, noiseBit[i]);
        }
    }
}

static inline void sdSetKeyOn(int i)
{
    sceSdSetSwitch(defCore[i] | SD_S_KON, keyOn[i]);
}

static inline void sdClearKeyOn(int i)
{
    keyOn[i] = 0;
}

static void SdFlushSetVoice(void)
{
    int i;
    int old;

    WaitSema(iSys.smSpuSet);

    SdChannelCheck();

    for (i = 0; i < _SD_NCORE; i++) {
        if (keyOff[i] != 0) {
            sceSdSetSwitch(defCore[i] | SD_S_KOFF, keyOff[i]);
            keyOff[i] = keyOff2[i];
            keyOff2[i] = 0;
        }
    }

    SdVoiceSet();
    SdNoiseSet();
    SdFlushSetDsp();

    CpuSuspendIntr(&old);
    sdSetKeyOn(0);
    sdSetKeyOn(1);
    sdClearKeyOn(0);
    sdClearKeyOn(1);
    CpuResumeIntr(old);

    SignalSema(iSys.smSpuSet);
}

static void sortByAddr(void)
{
    SD_ALLOC temp;
    short i, j;

    for (i = 1; i < SD_ALLOC_SIZE - 1; i++) {
        for (j = i + 1; j < SD_ALLOC_SIZE - 1; j++) {
            if (stSpuAlloc[i].addr > stSpuAlloc[j].addr && stSpuAlloc[j].addr > 0) {
                temp = stSpuAlloc[i];
                stSpuAlloc[i] = stSpuAlloc[j];
                stSpuAlloc[j] = temp;
            }
        }
    }
}

int SdSpuMalloc(int size)
{
    short i, j;

    WaitSema(iSys.smSpuAlloc);

    for (i = 0; i < SD_ALLOC_SIZE; i++) {
        if (stSpuAlloc[i].used == 0 && stSpuAlloc[i].size >= size) {
            break;
        }
    }

    if (i == SD_ALLOC_SIZE) {
        i = -1;
    } else {
        for (j = 0; j < SD_ALLOC_SIZE; j++) {
            if (stSpuAlloc[j].used == 0 && stSpuAlloc[j].addr == 0) {
                break;
            }
        }

        if (j < SD_ALLOC_SIZE) {
            stSpuAlloc[j].size = stSpuAlloc[i].size;
            stSpuAlloc[i].size = size;
            stSpuAlloc[j].size -= stSpuAlloc[i].size;

            if (stSpuAlloc[j].size != 0) {
                stSpuAlloc[j].addr = stSpuAlloc[i].addr + stSpuAlloc[i].size;
            } else {
                stSpuAlloc[j].addr = 0;
            }
        }
    }

    stSpuAlloc[i].used = 1;

    sortByAddr();
    SignalSema(iSys.smSpuAlloc);
    return stSpuAlloc[i].addr;
}

#if 0
// TODO: Fix bad codegen
int SdPcmCtrl(int index, sd_pcm_job job)
{
    switch (index) {
    case 0:
        iPcm.job1 = job;
        break;
    case 1:
        iPcm.job2 = job;
        break;
    }

    return SD_SUCCESS;
}
#endif

static void SdInitSpu(void)
{
    int addr[_SD_NCORE];
    int key[_SD_NCORE];
    sceSdEffectAttr attr;
    int *keyp = key;
    short i;
    int voice;

    sceSdInit(0);

    addr[0] = 0x1FFFF;
    addr[1] = 0x1FFFFF;

    sceSdSetParam(defCore[1] | SD_P_MVOLL, 0);
    sceSdSetParam(defCore[1] | SD_P_MVOLR, 0);
    sceSdSetParam(defCore[0] | SD_P_MVOLL, 0);
    sceSdSetParam(defCore[0] | SD_P_MVOLR, 0);

    keyp[0] = 0xFFFFFF;
    keyp[1] = 0xFFFFFF;
    SdSetKey(SD_KEY_OFF, keyp);

    keyp[0] = 0xFFFFFF;
    keyp[1] = 0xFFFFFF;
    SdSetKey(SD_DSP_OFF, keyp);

    sceSdSetParam(SD_CORE_0 | SD_P_MMIX, ~(SD_MMIX_MINEL | SD_MMIX_MINER) & 0xFFF);
    sceSdSetParam(SD_CORE_1 | SD_P_MMIX, ~(SD_MMIX_MINEL | SD_MMIX_MINER | SD_MMIX_SINEL | SD_MMIX_SINER) & 0xFFF);

    sceSdSetCoreAttr(SD_C_SPDIF_MODE, SD_SPDIF_MEDIA_DVD | SD_SPDIF_COPY_PROHIBIT);

    for (i = 0; i < _SD_NCORE; i++) {
        sceSdSetCoreAttr(defCore[i] | SD_C_EFFECT_ENABLE, 0);

        stDsp[i].addr = addr[i] - dspSize[iDspNo[7]] + 1;
        sceSdSetAddr(defCore[i] | SD_A_EEA, addr[i]);

        attr.mode = stDsp[i].mode | SD_REV_MODE_CLEAR_WA;
        attr.depth_L = attr.depth_R = stDsp[i].depth;

        sceSdSetEffectAttr(defCore[i], &attr);
        sceSdClearEffectWorkArea(i, i, iDspNo[7]);

        sceSdSetSwitch(defCore[i] | SD_S_VMIXL, 0xFFFFFF);
        sceSdSetSwitch(defCore[i] | SD_S_VMIXR, 0xFFFFFF);
        sceSdSetSwitch(defCore[i] | SD_S_VMIXEL, 0);
        sceSdSetSwitch(defCore[i] | SD_S_VMIXER, 0);

        sceSdSetParam(defCore[i] | SD_P_AVOLL, 0x7FFF);
        sceSdSetParam(defCore[i] | SD_P_AVOLR, 0x7FFF);
        sceSdSetParam(defCore[i] | SD_P_EVOLL, 0);
        sceSdSetParam(defCore[i] | SD_P_EVOLR, 0);

        for (voice = 0; voice < _SD_NCHAN; voice++) {
            sceSdSetParam(defCore[i] | defVc[voice] | SD_VP_VOLL, 0);
            sceSdSetParam(defCore[i] | defVc[voice] | SD_VP_VOLR, 0);
        }
    }

    for (i = 120; i != 0; i--) {
        WaitNonVblank();
        WaitVblankEnd();
    }

    sceSdSetParam(defCore[0] | SD_P_MVOLL, 0x3FFF);
    sceSdSetParam(defCore[0] | SD_P_MVOLR, 0x3FFF);
    sceSdSetParam(defCore[1] | SD_P_MVOLL, 0x3FFF);
    sceSdSetParam(defCore[1] | SD_P_MVOLR, 0x3FFF);
    sceSdSetParam(defCore[0] | SD_P_BVOLL, 0x7FFF);
    sceSdSetParam(defCore[0] | SD_P_BVOLR, 0x7FFF);
    sceSdSetParam(defCore[1] | SD_P_BVOLL, 0);
    sceSdSetParam(defCore[1] | SD_P_BVOLR, 0);

    memset(iPcm.buffer, 0, sizeof(iPcm.buffer));
    sceSdBlockTrans(0, SD_TRANS_MODE_WRITE | SD_BLOCK_LOOP, (char *)iPcm.buffer, sizeof(iPcm.buffer));
    sceSdSetTransIntrHandler(0, (sceSdTransIntrHandler)SdTransIrqCallback, NULL);

    CancelWakeupThread(GetThreadId());
}

void SdInitSdlib2(void)
{
    uint32 i, j;

    for (i = 0; i < _SD_NCORE; i++) {
        dmaQueueNo[i] = 0;
        keyOn[i] = keyOff[i] = dspOn[i] = dspOff[i] = dspBit[i] = update[i] = 0;

        stDsp[i].voice = 0;
        stDsp[i].mode = 0xFF;
        stDsp[i].newdepth = 0;
        stDsp[i].depth = -1;

        for (j = 0; j < _SD_NCHAN; j++) {
            _stChan[i][j].unk1 = j + i * _SD_NCHAN;
        }
    }

    memset(stSpuAlloc, 0, sizeof(stSpuAlloc));

    stSpuAlloc[0].used = 2;
    stSpuAlloc[0].size = 0x5100;
    stSpuAlloc[0].addr = 0;

    stSpuAlloc[1].used = 0;
    stSpuAlloc[1].addr = 0x5100;
    stSpuAlloc[1].size = 0x1AF00 - dspSize[iDspNo[7]];

    stSpuAlloc[2].used = 2;
    stSpuAlloc[2].addr = 0x20000 - dspSize[iDspNo[7]];
    stSpuAlloc[2].size = dspSize[iDspNo[7]];

    stSpuAlloc[3].used = 0;
    stSpuAlloc[3].addr = 0x20000;
    stSpuAlloc[3].size = 0x1E0000 - dspSize[iDspNo[7]];

    stSpuAlloc[14].used = 2;
    stSpuAlloc[14].addr = 0x200000 - dspSize[iDspNo[7]];
    stSpuAlloc[14].size = dspSize[iDspNo[7]];

    stSpuAlloc[15].used = 0;
    stSpuAlloc[15].addr = 0x200000;
    stSpuAlloc[15].size = 0x200000 - stSpuAlloc[14].addr - stSpuAlloc[14].size;
}

static inline void sdSetDspZero(sint8 core)
{
    WaitSema(iSys.smSpuSet);

    stDsp[core].newmode = 0;
    stDsp[core].newdepth = 0;

    if ((dspNo[stDsp[core].newmode] & 0xF) >= 8) {
        stDsp[core].newmode = iDspNo[7];
    }

    SignalSema(iSys.smSpuSet);
}

void SdQuitSdlib2(void)
{
    uint32 key[_SD_NCORE];
    short core;

    key[0] = 0xFFFFFF;
    key[1] = 0xFFFFFF;
    SdSetKey(SD_KEY_OFF, key);

    key[0] = 0xFFFFFF;
    key[1] = 0xFFFFFF;
    SdSetKey(SD_DSP_OFF, key);

    for (core = 0; core < _SD_NCORE; core++) {
        sceSdSetParam(defCore[core] | SD_P_MVOLL, 0);
        sceSdSetParam(defCore[core] | SD_P_MVOLR, 0);
        sceSdSetParam(defCore[core] | SD_P_EVOLL, 0);
        sceSdSetParam(defCore[core] | SD_P_EVOLR, 0);
        sceSdSetParam(defCore[core] | SD_P_AVOLL, 0);
        sceSdSetParam(defCore[core] | SD_P_AVOLR, 0);
        sceSdSetSwitch(defCore[core] | SD_S_VMIXL, 0);
        sceSdSetSwitch(defCore[core] | SD_S_VMIXR, 0);
        sceSdSetCoreAttr(defCore[core] | SD_C_EFFECT_ENABLE, 0);
        sdSetDspZero(core);
    }

    sceSdSetParam(SD_CORE_0 | SD_P_MMIX, 0);
    sceSdSetParam(SD_CORE_1 | SD_P_MMIX, 0);
}

#if 0
// TODO: Fix -g2 breaking the match
static void SdLoop(void)
{
    int reqcnt;
    int i, j;

    SdInitSpu();

    rQueueSpuTrans = wQueueSpuTrans = 0;
    fSpuTrans[0] = fSpuTrans[1] = 1;

    SdSpuWrite(0x5100, NULL, 0x40);
    SdSpuWrite(0x5200, NULL, 0x40);

    fSdLoop = 1;
    while (fSdLoop) {
        sdSync++;

        SleepThread();
        GetTimerCounter(gTimerID);

        reqcnt = CancelWakeupThread(GetThreadId()) + 1;

        if (sceSdVoiceTransStatus(1, SD_TRANS_STATUS_CHECK) &&
            queueSpuTrans[dmaQueueNo[1]].status == SD_QUEUE_BUSY) {
            fSpuTrans[1] = 0;
            queueSpuTrans[dmaQueueNo[1]].status = SD_QUEUE_READY;
        } else {
            fSpuTrans[1] = sceSdVoiceTransStatus(1, SD_TRANS_STATUS_CHECK) == 0;
        }

        SdJobSpuWrite();

        for (i = 15; i >= 0; i--) {
            for (j = reqcnt; j != 0; j--) {
                if (thRegist[i] > 0) {
                    WakeupThread(thRegist[i]);
                }
            }
        }

        GetTimerCounter(gTimerID);
    }

    StopHardTimer(gTimerID);
    FreeHardTimer(gTimerID);
    SdQuitSdlib2();
    iSys.fSdlibActive = SD_FALSE;

    DeleteSema(iSys.smSpuWrite);
    DeleteSema(iSys.smSpuAlloc);
    DeleteSema(iSys.smSpuSet);
    ExitThread();
}
#endif

int SdInitSdlib(void)
{
    struct ThreadParam thread;
    struct SemaParam sema;

    memset(&iSys, 0, sizeof(iSys));

    if (iSys.fSdlibActive == SD_TRUE) {
        return SD_SUCCESS;
    }

    iSys.fSdlibActive = SD_TRUE;

    SdInitSdlib2();
    FlushDcache();

    sema.attr = SA_THPRI;
    sema.maxCount = 1;
    sema.initCount = 0;
    iSys.smSpuWrite = CreateSema(&sema);

    sema.attr = SA_THPRI;
    sema.maxCount = 1;
    sema.initCount = 0;
    iSys.smSpuAlloc = CreateSema(&sema);

    sema.attr = SA_THPRI;
    sema.maxCount = 1;
    sema.initCount = 0;
    iSys.smSpuSet = CreateSema(&sema);

    SignalSema(iSys.smSpuWrite);
    SignalSema(iSys.smSpuAlloc);
    SignalSema(iSys.smSpuSet);

    thread.attr         = TH_C;
    thread.entry        = SdLoop;
    thread.initPriority = 24;
    thread.stackSize    = SD_STACK_SIZE;
    thread.option       = 0;
    thSdLoop = CreateThread(&thread);
    if (thSdLoop <= 0) {
        return SD_ERROR;
    }
    StartThread(thSdLoop, 0);

    thread.attr         = TH_C;
    thread.entry        = SdLoopRegset;
    thread.initPriority = 26;
    thread.stackSize    = SD_STACK_SIZE;
    thread.option       = 0;
    thSdLoopRegset = CreateThread(&thread);
    if (thSdLoopRegset <= 0) {
        return SD_ERROR;
    }
    StartThread(thSdLoopRegset, 0);

    thread.attr         = TH_C;
    thread.entry        = SdLoopPcm;
    thread.initPriority = 25;
    thread.stackSize    = SD_STACK_SIZE;
    thread.option       = 0;
    thSdLoopPcm = CreateThread(&thread);
    if (thSdLoopPcm <= 0) {
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
        avail = !fSpuTrans[1] ? 1 : -1;

        if (avail != -1) {
            return SD_SUCCESS;
        }

        return SD_ERROR;
    }

    return queueSpuTrans[queue - 1].status;
}

uint32 SdGetSpuPlayAddr(sint8 core, sint8 voice)
{
    return sceSdGetAddr(defCore[core] | defVc[voice] | SD_VA_NAX);
}

int SdGetKeyoffCount(sint8 core, sint8 voice)
{
    return _stChan[core][voice].keyoffs;
}

int SdSetKeyoffCount(int core, int voice, int count)
{
    WaitSema(iSys.smSpuSet);

    if (count > 127) {
        _stChan[core][voice].keyoffs = 127;
    } else {
        _stChan[core][voice].keyoffs = count;
    }

    SignalSema(iSys.smSpuSet);
    return _stChan[core][voice].keyoffs;
}

int SdGetVolume(sint8 core, sint8 voice)
{
    uint32 lo, hi;

    lo = sceSdGetParam(defCore[core] | defVc[voice] | SD_VP_VOLXL);
    hi = sceSdGetParam(defCore[core] | defVc[voice] | SD_VP_VOLXR);
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

void SdSetDsp(sint8 core, sint8 mode, sint8 depth)
{
    WaitSema(iSys.smSpuSet);

    stDsp[core].newmode = mode;
    stDsp[core].newdepth = depth;

    if ((dspNo[stDsp[core].newmode] & 0xF) >= 8) {
        stDsp[core].newmode = iDspNo[7];
    }

    SignalSema(iSys.smSpuSet);
}

void SdSetNoise(sint8 core, int freq)
{
    WaitSema(iSys.smSpuSet);
    stNoise[core].newclk = freq;
    SignalSema(iSys.smSpuSet);
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
    iSys.fSdMono = mono;
    return SD_SUCCESS;
}

int SdPanToVol14(sint8 pan, sint8 side)
{
    if (iSys.fSdMono)
    {
        return panpotTable[64];
    }

    return (side == 0) ? panpotTable[pan] : panpotTable[127 - pan];
}

int SdSpuFree(int ptr)
{
    short i;

    WaitSema(iSys.smSpuAlloc);

    for (i = 0; i < SD_ALLOC_SIZE; i++)
    {
        if (stSpuAlloc[i].used == 1 && stSpuAlloc[i].addr == ptr) {
            stSpuAlloc[i].used = 0;
            break;
        }
    }

    sortByAddr();
    SignalSema(iSys.smSpuAlloc);
    return SD_SUCCESS;
}

#if 0
// TODO: Fix -g2 breaking the match
void SdVoiceFlush(int flush)
{
    mVcFlush = flush;
    fVcFlushReq = 1 - fVcFlushJob;
}
#endif

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

    return usec / 1000U + sec * 1000;
}

#if 0
// TODO: Fix -g2 breaking the match
int SdIrqRegist(int thid)
{
    static int num = 0;

    if (num < 0 || num >= 16) {
        return SD_ERROR;
    }

    thRegist[num++] = thid;
    return num;
}
#endif

void SdQuitSdlib(void)
{
    fSdLoop = SD_FALSE;
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
    fSpuTrans[0] = fSpuTrans[1] = SD_TRUE;
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

static uint32 SdIrqCallback(void *ptr)
{
    iWakeupThread(thSdLoop);
    iWakeupThread(thSdLoopRegset);
    return SYSCLOCK / IRQ_TIME;
}

static void SdLoopPcm(void)
{
    int which;

    while (!fSdLoop) {
        SleepThread();
    }

    while (fSdLoop) {
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
    while (!fSdLoop) {
        SleepThread();
    }

    while (fSdLoop) {
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
