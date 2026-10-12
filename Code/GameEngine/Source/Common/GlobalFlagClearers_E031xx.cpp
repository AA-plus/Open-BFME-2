// Three B2-native flag-word clearers on two .data flag words
// (0x00E03110-0x00E03150):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03110;
// g_Va00E03110: matched references place it at VA 0xe03110 (zero-filled .bss).
unsigned int g_Va00E03110;
extern unsigned int g_Va00E03118;
// g_Va00E03118: matched references place it at VA 0xe03118 (zero-filled .bss).
unsigned int g_Va00E03118;

unsigned int Rva00786A39ClearFlag(void)
{
	return g_Va00E03110 &= 0xFFFFFFFEu;
}

unsigned int Rva00786A46ClearFlag(void)
{
	return g_Va00E03110 &= 0xFFFFFFFDu;
}

unsigned int Rva00786A89ClearFlag(void)
{
	return g_Va00E03118 &= 0xFFFFFFFEu;
}


// 0x00786F00 is the static BannerCarrierUpdate guard cleanup of the proven
// DelayedExperienceLevelGrantSystem parent00420C8E. Its generated funclet
// and guard now belong to that parent; the standalone second datum was removed.
