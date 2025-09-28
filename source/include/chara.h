#ifndef __MGS3_CHARA_H__
#define __MGS3_CHARA_H__

// NOTE: According to MGS4's debug info, CHARA & NEWCHARA were defined in THREE
// separate locations, each with slighly different (yet functionally identical)
// definitions.
//
// The return type of NEWCHARA is defined as 'GV_HANDLE' (u_int64) in game.h,
// and simply 'void' in the tool-generated chara table sources. I've split the
// difference and specified the return type as 'void *' here.
//
// MGS4's game.h defines CHARA.class_id as 'u_long', hinting that the typedefs
// were either modified or added to the header after the PS3's ABI was changed
// from LP64 to IPL32 with SDK 080.000 in early 2006.

// XXX The empty parameter list is widely regarded as one of old C's
// XXX anti-features. C++ and C23 have changed its meaning to (void).

typedef void *NEWCHARA();

typedef struct {
    unsigned int class_id;
    NEWCHARA *func;
} CHARA;

#endif // {{{ END OF FILE }}}
