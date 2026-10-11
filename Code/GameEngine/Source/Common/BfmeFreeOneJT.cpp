// cl: /DNDEBUG /MD
//
// ?bfmeFreeOneJT@@YAXPAX@Z, retail 0x001B6410, 5 bytes: a single tail jump to
// the rowed duck_free (0x001B63A0) with the same argument. game.dat is not
// incrementally linked, so this is a real forwarding function, not an ILT
// stub. Two units (BfmeConv2079/2080, VP6_CreatePBInstance's callers) call it by this
// pinned name.

extern "C" void __cdecl duck_free(void *block);

void bfmeFreeOneJT(void *block)
{
	duck_free(block);
}
