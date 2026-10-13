// Remaining B2-native flag-word clearers on .data flag words
// (0x00E02D74-0x00E02DFC):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses,
// following GlobalFlagClearers_DFEExx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E02DA4;
// g_Va00E02DA4: matched references place it at VA 0xe02da4 (zero-filled .bss).
unsigned int g_Va00E02DA4;
extern unsigned int g_Va00E02DBC;
// g_Va00E02DBC: matched references place it at VA 0xe02dbc (zero-filled .bss).
unsigned int g_Va00E02DBC;
extern unsigned int g_Va00E02DC4;
// g_Va00E02DC4: matched references place it at VA 0xe02dc4 (zero-filled .bss).
unsigned int g_Va00E02DC4;
extern unsigned int g_Va00E02DCC;
// g_Va00E02DCC: matched references place it at VA 0xe02dcc (zero-filled .bss).
unsigned int g_Va00E02DCC;
extern unsigned int g_Va00E02DD4;
// g_Va00E02DD4: matched references place it at VA 0xe02dd4 (zero-filled .bss).
unsigned int g_Va00E02DD4;
extern unsigned int g_Va00E02DDC;
// g_Va00E02DDC: matched references place it at VA 0xe02ddc (zero-filled .bss).
unsigned int g_Va00E02DDC;
extern unsigned int g_Va00E02DE4;
// g_Va00E02DE4: matched references place it at VA 0xe02de4 (zero-filled .bss).
unsigned int g_Va00E02DE4;


unsigned int Rva007828B2ClearFlag(void)
{
	return g_Va00E02DA4 &= 0xFFFFFFFEu;
}



unsigned int Rva00782B88ClearFlag(void)
{
	return g_Va00E02DBC &= 0xFFFFFFFEu;
}

unsigned int Rva00782D59ClearFlag(void)
{
	return g_Va00E02DC4 &= 0xFFFFFFFEu;
}

unsigned int Rva00782D70ClearFlag(void)
{
	return g_Va00E02DCC &= 0xFFFFFFFEu;
}

unsigned int Rva00782D87ClearFlag(void)
{
	return g_Va00E02DD4 &= 0xFFFFFFFEu;
}

unsigned int Rva00782D9EClearFlag(void)
{
	return g_Va00E02DDC &= 0xFFFFFFFEu;
}

unsigned int Rva00782DEFClearFlag(void)
{
	return g_Va00E02DE4 &= 0xFFFFFFFEu;
}



