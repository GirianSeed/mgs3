
INCLUDE_ASM("asm/nonmatchings/memst", memstTickReady);

INCLUDE_ASM("asm/nonmatchings/memst", memstTickPlay);

INCLUDE_ASM("asm/nonmatchings/memst", memstTick);

INCLUDE_ASM("asm/nonmatchings/memst", memstInit);

int memstQuit(void)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/memst", memstGetVoice);

INCLUDE_ASM("asm/nonmatchings/memst", memstTickOpen);
