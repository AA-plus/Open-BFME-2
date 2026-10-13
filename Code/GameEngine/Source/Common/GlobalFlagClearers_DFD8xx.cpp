// Eight B2-native flag-word clearers across six .data flag words of one
// contiguous run (0x0076929D-0x0076B9FF):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot (0x0090E178
// and on). Identity is not recovered; names derive from addresses,
// following GlobalFlagClearers_08.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00DFD8E4;
extern unsigned int g_Va00DFDC48;
// g_Va00DFDC48: matched references place it at VA 0xdfdc48 (zero-filled .bss).
unsigned int g_Va00DFDC48;
extern unsigned int g_Va00DFDC50;
// g_Va00DFDC50: matched references place it at VA 0xdfdc50 (zero-filled .bss).
unsigned int g_Va00DFDC50;
extern unsigned int g_Va00DFDCD8;
// g_Va00DFDCD8: matched references place it at VA 0xdfdcd8 (zero-filled .bss).
unsigned int g_Va00DFDCD8;
extern unsigned int g_Va00DFDCF4;
// g_Va00DFDCF4: matched references place it at VA 0xdfdcf4 (zero-filled .bss).
unsigned int g_Va00DFDCF4;
extern unsigned int g_Va00DFE014;
// g_Va00DFE014: matched references place it at VA 0xdfe014 (zero-filled .bss).
unsigned int g_Va00DFE014;

unsigned int Rva0076929DClearFlag(void)
{
	return g_Va00DFD8E4 &= 0xFFFFFFFDu;
}

unsigned int Rva007692AAClearFlag(void)
{
	return g_Va00DFD8E4 &= 0xFFFFFFFBu;
}

unsigned int Rva00769BDDClearFlag(void)
{
	return g_Va00DFDC48 &= 0xFFFFFFFEu;
}

unsigned int Rva00769BF4ClearFlag(void)
{
	return g_Va00DFDC50 &= 0xFFFFFFFEu;
}

unsigned int Rva0076B063ClearFlag(void)
{
	return g_Va00DFDCD8 &= 0xFFFFFFFEu;
}

unsigned int Rva0076B21CClearFlag(void)
{
	return g_Va00DFDCF4 &= 0xFFFFFFFBu;
}

unsigned int Rva0076B229ClearFlag(void)
{
	return g_Va00DFDCF4 &= 0xFFFFFFF7u;
}

// The76B248 action belongs to positional GenericObjectCreationNugget::create.
// Its native parent now emits the guard cleanup and owns the sole guard datum.

unsigned int Rva0076B9FFClearFlag(void)
{
	return g_Va00DFE014 &= 0xFFFFFFFDu;
}
