// Twenty-six B2-native flag-word clearers on 25 .data flag words
// (0x00E03B00-0x00E03BF4):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Axx.cpp.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E03B00;
// g_Va00E03B00: matched references place it at VA 0xe03b00 (zero-filled .bss).
unsigned int g_Va00E03B00;
extern unsigned int g_Va00E03B0C;
// g_Va00E03B0C: matched references place it at VA 0xe03b0c (zero-filled .bss).
unsigned int g_Va00E03B0C;
extern unsigned int g_Va00E03B14;
// g_Va00E03B14: matched references place it at VA 0xe03b14 (zero-filled .bss).
unsigned int g_Va00E03B14;
extern unsigned int g_Va00E03B1C;
// g_Va00E03B1C: matched references place it at VA 0xe03b1c (zero-filled .bss).
unsigned int g_Va00E03B1C;
extern unsigned int g_Va00E03B24;
// g_Va00E03B24: matched references place it at VA 0xe03b24 (zero-filled .bss).
unsigned int g_Va00E03B24;
extern unsigned int g_Va00E03B2C;
// g_Va00E03B2C: matched references place it at VA 0xe03b2c (zero-filled .bss).
unsigned int g_Va00E03B2C;
extern unsigned int g_Va00E03B34;
// g_Va00E03B34: matched references place it at VA 0xe03b34 (zero-filled .bss).
unsigned int g_Va00E03B34;
extern unsigned int g_Va00E03B40;
// g_Va00E03B40: matched references place it at VA 0xe03b40 (zero-filled .bss).
unsigned int g_Va00E03B40;
extern unsigned int g_Va00E03B4C;
// g_Va00E03B4C: matched references place it at VA 0xe03b4c (zero-filled .bss).
unsigned int g_Va00E03B4C;
extern unsigned int g_Va00E03B58;
// g_Va00E03B58: matched references place it at VA 0xe03b58 (zero-filled .bss).
unsigned int g_Va00E03B58;
extern unsigned int g_Va00E03B60;
// g_Va00E03B60: matched references place it at VA 0xe03b60 (zero-filled .bss).
unsigned int g_Va00E03B60;
extern unsigned int g_Va00E03B78;
// g_Va00E03B78: matched references place it at VA 0xe03b78 (zero-filled .bss).
unsigned int g_Va00E03B78;
extern unsigned int g_Va00E03B84;
// g_Va00E03B84: matched references place it at VA 0xe03b84 (zero-filled .bss).
unsigned int g_Va00E03B84;
extern unsigned int g_Va00E03B8C;
// g_Va00E03B8C: matched references place it at VA 0xe03b8c (zero-filled .bss).
unsigned int g_Va00E03B8C;
extern unsigned int g_Va00E03B98;
// g_Va00E03B98: matched references place it at VA 0xe03b98 (zero-filled .bss).
unsigned int g_Va00E03B98;
extern unsigned int g_Va00E03BA0;
// g_Va00E03BA0: matched references place it at VA 0xe03ba0 (zero-filled .bss).
unsigned int g_Va00E03BA0;
extern unsigned int g_Va00E03BA8;
// g_Va00E03BA8: matched references place it at VA 0xe03ba8 (zero-filled .bss).
unsigned int g_Va00E03BA8;
extern unsigned int g_Va00E03BB4;
// g_Va00E03BB4: matched references place it at VA 0xe03bb4 (zero-filled .bss).
unsigned int g_Va00E03BB4;
extern unsigned int g_Va00E03BC4;
// g_Va00E03BC4: matched references place it at VA 0xe03bc4 (zero-filled .bss).
unsigned int g_Va00E03BC4;
extern unsigned int g_Va00E03BCC;
// g_Va00E03BCC: matched references place it at VA 0xe03bcc (zero-filled .bss).
unsigned int g_Va00E03BCC;
extern unsigned int g_Va00E03BD8;
// g_Va00E03BD8: matched references place it at VA 0xe03bd8 (zero-filled .bss).
unsigned int g_Va00E03BD8;
extern unsigned int g_Va00E03BE4;
// g_Va00E03BE4: matched references place it at VA 0xe03be4 (zero-filled .bss).
unsigned int g_Va00E03BE4;
extern unsigned int g_Va00E03BEC;
// g_Va00E03BEC: matched references place it at VA 0xe03bec (zero-filled .bss).
unsigned int g_Va00E03BEC;
extern unsigned int g_Va00E03BF4;
// g_Va00E03BF4: matched references place it at VA 0xe03bf4 (zero-filled .bss).
unsigned int g_Va00E03BF4;

unsigned int Rva0078D53AClearFlag(void)
{
	return g_Va00E03B00 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D595ClearFlag(void)
{
	return g_Va00E03B0C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D5E0ClearFlag(void)
{
	return g_Va00E03B14 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D61BClearFlag(void)
{
	return g_Va00E03B1C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D64EClearFlag(void)
{
	return g_Va00E03B24 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D6A6ClearFlag(void)
{
	return g_Va00E03B2C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D6BDClearFlag(void)
{
	return g_Va00E03B34 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D7AFClearFlag(void)
{
	return g_Va00E03B40 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D829ClearFlag(void)
{
	return g_Va00E03B4C &= 0xFFFFFFFEu;
}

unsigned int Rva0078D8F9ClearFlag(void)
{
	return g_Va00E03B58 &= 0xFFFFFFFEu;
}

unsigned int Rva0078D934ClearFlag(void)
{
	return g_Va00E03B60 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DAA8ClearFlag(void)
{
	return g_Va00E03B78 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DABFClearFlag(void)
{
	return g_Va00E03B84 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB02ClearFlag(void)
{
	return g_Va00E03B8C &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB19ClearFlag(void)
{
	return g_Va00E03B98 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB42ClearFlag(void)
{
	return g_Va00E03BA0 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB59ClearFlag(void)
{
	return g_Va00E03BA8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DB82ClearFlag(void)
{
	return g_Va00E03BB4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DBB6ClearFlag(void)
{
	return g_Va00E03BC4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DC0AClearFlag(void)
{
	return g_Va00E03BCC &= 0xFFFFFFFEu;
}

unsigned int Rva0078DC4CClearFlag(void)
{
	return g_Va00E03BD8 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DCBDClearFlag(void)
{
	return g_Va00E03BE4 &= 0xFFFFFFFEu;
}

unsigned int Rva0078DCD4ClearFlag(void)
{
	return g_Va00E03BEC &= 0xFFFFFFFEu;
}

unsigned int Rva0078DD17ClearFlag(void)
{
	return g_Va00E03BF4 &= 0xFFFFFFFEu;
}


// 78D9C9 and78DA27 are the two static-name initialization unwind actions
// emitted by ProductionUpdate::update; its compiler-owned guard is E03B6C.
