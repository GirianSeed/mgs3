#ifndef __MGS3_MIOBASE_H__
#define __MGS3_MIOBASE_H__

#include <sys/types.h>

typedef struct _mio_message {
    u_short msgid;      // command ID
    u_short len;        // payload length
    u_int   serial;     // sequence no.
    u_char  digest[16]; // MD5 digest
    u_char  body[];     // payload data
} mio_message;

#endif // __MGS3_MIOBASE_H__
