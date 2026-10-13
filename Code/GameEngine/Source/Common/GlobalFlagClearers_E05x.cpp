// Nine B2-native flag-word clearers on six .data flag words
// (0x00E05F38-0x00E05F64):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_E049xx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E05F38;
// g_Va00E05F38: matched references place it at VA 0xe05f38 (zero-filled .bss).
unsigned int g_Va00E05F38;
extern unsigned int g_Va00E05F40;
// g_Va00E05F40: matched references place it at VA 0xe05f40 (zero-filled .bss).
unsigned int g_Va00E05F40;
extern unsigned int g_Va00E05F50;
// g_Va00E05F50: matched references place it at VA 0xe05f50 (zero-filled .bss).
unsigned int g_Va00E05F50;
extern unsigned int g_Va00E05F58;
// g_Va00E05F58: matched references place it at VA 0xe05f58 (zero-filled .bss).
unsigned int g_Va00E05F58;
extern unsigned int g_Va00E05F64;
// g_Va00E05F64: matched references place it at VA 0xe05f64 (zero-filled .bss).
unsigned int g_Va00E05F64;

unsigned int Rva00797AE0ClearFlag(void)
{
	return g_Va00E05F38 &= 0xFFFFFFFEu;
}

unsigned int Rva00797AF5ClearFlag(void)
{
	return g_Va00E05F38 &= 0xFFFFFFFDu;
}

unsigned int Rva00797B02ClearFlag(void)
{
	return g_Va00E05F38 &= 0xFFFFFFFBu;
}

unsigned int Rva00797B0FClearFlag(void)
{
	return g_Va00E05F38 &= 0xFFFFFFF7u;
}

unsigned int Rva00797B26ClearFlag(void)
{
	return g_Va00E05F40 &= 0xFFFFFFFEu;
}

unsigned int Rva00797B87ClearFlag(void)
{
	return g_Va00E05F50 &= 0xFFFFFFFEu;
}

unsigned int Rva00797B94ClearFlag(void)
{
	return g_Va00E05F50 &= 0xFFFFFFFDu;
}

unsigned int Rva00797BABClearFlag(void)
{
	return g_Va00E05F58 &= 0xFFFFFFFEu;
}

unsigned int Rva00797BDCClearFlag(void)
{
	return g_Va00E05F64 &= 0xFFFFFFFEu;
}


// Former7979F5/797A02/797A0F rows are the three static-key unwind
// handlers emitted by ControlBar::processCommandUI; its guard ownsE05E14.
