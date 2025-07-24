#ifndef __MGS3_STREAM_H__
#define __MGS3_STREAM_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef void FS_STREAM;

#define STREAM_TYPE_AUDIO       0x01
#define STREAM_TYPE_DEMO        0x02
#define STREAM_TYPE_JIMAKU      0x04
#define STREAM_TYPE_UNKNOWN_05  0x05
#define STREAM_TYPE_UNKNOWN_06  0x06
#define STREAM_TYPE_MOVIE       0x0E

#define STREAM_TYPE_DESCRIPT    0x10
#define STREAM_TYPE_DUMMY       0xF0

#define STREAM_AUDIO_TYPE_VOX   0x01
#define STREAM_AUDIO_TYPE_BGM   0x11
#define STREAM_DEMO_TYPE_00     0x00
#define STREAM_DEMO_TYPE_01     0x01
#define STREAM_DEMO_TYPE_02     0x02
#define STREAM_DEMO_TYPE_03     0x03

typedef struct {
    int type;   /* +0x00 */
    int size;   /* +0x04 */
    int time;   /* +0x08 */
    int option; /* +0x0c */
} STREAM_TAG;

#ifdef __cplusplus
}
#endif
#endif // {{{ END OF FILE }}}
