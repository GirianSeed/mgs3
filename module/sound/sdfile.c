#include <libsd.h>

INCLUDE_ASM("asm/nonmatchings/sdfile", sdCdRead);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoadTpat);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoad);

INCLUDE_ASM("asm/nonmatchings/sdfile", adjustMemory);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoadCommand);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoadTick);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoadSector);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoadInit);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoadQuit);

INCLUDE_ASM("asm/nonmatchings/sdfile", sdCdOpen);

INCLUDE_ASM("asm/nonmatchings/sdfile", sdCdSeek);

INCLUDE_ASM("asm/nonmatchings/sdfile", sdCdSeekSub);

INCLUDE_ASM("asm/nonmatchings/sdfile", sdCdReadSub);

INCLUDE_ASM("asm/nonmatchings/sdfile", sdCdClose);

INCLUDE_ASM("asm/nonmatchings/sdfile", psqLoadLoop);
