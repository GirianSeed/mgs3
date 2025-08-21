#ifndef __MGS3_CHARA_H__
#define __MGS3_CHARA_H__

#include "strcode.h"

// XXX The empty parameter list is widely regarded as one of old C's
// XXX anti-features. C++ and C23 have changed its meaning to (void).

typedef void *NEWCHARA();

typedef struct {
    unsigned int class_id;
    NEWCHARA *func;
} CHARA;

#endif // {{{ END OF FILE }}}
