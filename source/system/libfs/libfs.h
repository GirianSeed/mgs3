#ifndef __MGS3_LIBFS_H__
#define __MGS3_LIBFS_H__

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char *name;             /* +0x00 */
    u_int pos;              /* +0x04 */
    unsigned char media;    /* +0x08 */
    unsigned char layer;    /* +0x09 */
    unsigned char alt;      /* +0x0a */
    unsigned char pad;      /* +0x0b */
} FS_FILE_INFO;

extern FS_FILE_INFO fs_file_info[]; /* in file.cnf */

#ifdef SUBSISTENCE
#define FS_FILEID_STAGE         ( 0)    // stage.dat
#define FS_FILEID_STAGE_2       ( 1)    // stage_2.dat
#define FS_FILEID_STAGE_N       ( 2)    // stage_n.dat
#define FS_FILEID_STAGE_3       ( 3)    // stage_3.dat
#define FS_FILEID_CODEC         ( 4)    // codec.dat
#define FS_FILEID_CODEC_2       ( 5)    // codec_2.dat
#define FS_FILEID_CODEC_3       ( 6)    // codec_3.dat
#define FS_FILEID_BGM           ( 7)    // bgm.dat
#define FS_FILEID_BGM_2         ( 8)    // bgm_2.dat
#define FS_FILEID_BGM_3         ( 9)    // bgm_3.dat
#define FS_FILEID_MOVIE         (10)    // movie.dat
#define FS_FILEID_MOVIE_2       (11)    // movie_2.dat
#define FS_FILEID_MOVIE_3       (12)    // movie_3.dat
#define FS_FILEID_VOX           (13)    // vox.dat
#define FS_FILEID_VOX_2         (14)    // vox_2.dat
#define FS_FILEID_VOX_3         (15)    // vox_3.dat
#define FS_FILEID_DEMO          (16)    // demo.dat
#define FS_FILEID_DEMO_2        (17)    // demo_2.dat
#define FS_FILEID_DEMO_3        (18)    // demo_3.dat
#define FS_FILEID_SLOT          (19)    // slot.dat
#define FS_FILEID_SLOT_N        (20)    // slot_n.dat
#define FS_FILEID_SLOT_3        (21)    // slot_3.dat
#define FS_MAX_FILEID           (22)
#else // SNAKE_EATER
#define FS_FILEID_STAGE         (0)     // stage.dat
#define FS_FILEID_CODEC         (1)     // codec.dat
#define FS_FILEID_FACE          (2)     // face.dat
#define FS_FILEID_BGM           (2)     // bgm.dat
#define FS_FILEID_MOVIE         (3)     // movie.dat
#define FS_FILEID_VOX           (4)     // vox.dat
#define FS_FILEID_DEMO          (5)     // demo.dat
#define FS_FILEID_SLOT          (6)     // slot.dat
#define FS_MAX_FILEID           (7)
#endif

/* select.c */
void FS_StartDaemon( void );

#ifdef __cplusplus
}
#endif
#endif // {{{ END OF FILE }}}
