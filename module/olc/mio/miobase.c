#include "miobase.h"

// from "mgs4/module/olc/mio/miobase.c"
static char scrambler[4] = { 0x5a,0x70,0x85,0xaf };
// *(unsigned int *)&scrambler[0] == 0x5a7085af (BE)
// *(unsigned int *)&scrambler[0] == 0xaf85705a (LE)
