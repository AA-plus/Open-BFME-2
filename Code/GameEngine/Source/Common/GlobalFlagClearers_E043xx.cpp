// Twenty-one B2-native flag-word clearers on 21 .data flag words
// (0x00E04304-0x00E043E0):
//
//     mov eax,[<address>] / and al,<mask8> / mov [<address>],eax / ret
//
// Same /G7 byte-register narrowing as GlobalFlagClearers_08.cpp (defaults
// emit `and eax,imm`). Each body carries a .rdata table slot. Identity is
// not recovered; names derive from addresses.
// following GlobalFlagClearers_E03Fxx.cpp.
// 0x00790AE8 and guard VA 0x00E043D8 are now owned by the exact
// UnleashSpecialPower::rva004CE0D9 static-initialization EH graph.
// 0x00790AFF and guard VA 0x00E043E0 belong to triggerAbilityEffect.
// cl: /G7 /MD /EHsc /DNDEBUG

extern unsigned int g_Va00E04304;
// g_Va00E04304: matched references place it at VA 0xe04304 (zero-filled .bss).
unsigned int g_Va00E04304;
extern unsigned int g_Va00E04310;
// g_Va00E04310: matched references place it at VA 0xe04310 (zero-filled .bss).
unsigned int g_Va00E04310;
extern unsigned int g_Va00E04318;
// g_Va00E04318: matched references place it at VA 0xe04318 (zero-filled .bss).
unsigned int g_Va00E04318;
extern unsigned int g_Va00E04320;
// g_Va00E04320: matched references place it at VA 0xe04320 (zero-filled .bss).
unsigned int g_Va00E04320;
extern unsigned int g_Va00E0432C;
// g_Va00E0432C: matched references place it at VA 0xe0432c (zero-filled .bss).
unsigned int g_Va00E0432C;
extern unsigned int g_Va00E04338;
// g_Va00E04338: matched references place it at VA 0xe04338 (zero-filled .bss).
unsigned int g_Va00E04338;
extern unsigned int g_Va00E04344;
// g_Va00E04344: matched references place it at VA 0xe04344 (zero-filled .bss).
unsigned int g_Va00E04344;
extern unsigned int g_Va00E04350;
// g_Va00E04350: matched references place it at VA 0xe04350 (zero-filled .bss).
unsigned int g_Va00E04350;
extern unsigned int g_Va00E0435C;
// g_Va00E0435C: matched references place it at VA 0xe0435c (zero-filled .bss).
unsigned int g_Va00E0435C;
extern unsigned int g_Va00E04370;
// g_Va00E04370: matched references place it at VA 0xe04370 (zero-filled .bss).
unsigned int g_Va00E04370;
extern unsigned int g_Va00E0437C;
// g_Va00E0437C: matched references place it at VA 0xe0437c (zero-filled .bss).
unsigned int g_Va00E0437C;
extern unsigned int g_Va00E04388;
// g_Va00E04388: matched references place it at VA 0xe04388 (zero-filled .bss).
unsigned int g_Va00E04388;
extern unsigned int g_Va00E04390;
// g_Va00E04390: matched references place it at VA 0xe04390 (zero-filled .bss).
unsigned int g_Va00E04390;
extern unsigned int g_Va00E04398;
// g_Va00E04398: matched references place it at VA 0xe04398 (zero-filled .bss).
unsigned int g_Va00E04398;
extern unsigned int g_Va00E043A0;
// g_Va00E043A0: matched references place it at VA 0xe043a0 (zero-filled .bss).
unsigned int g_Va00E043A0;
extern unsigned int g_Va00E043A8;
// g_Va00E043A8: matched references place it at VA 0xe043a8 (zero-filled .bss).
unsigned int g_Va00E043A8;
extern unsigned int g_Va00E043B0;
// g_Va00E043B0: matched references place it at VA 0xe043b0 (zero-filled .bss).
unsigned int g_Va00E043B0;
extern unsigned int g_Va00E043B8;
// g_Va00E043B8: matched references place it at VA 0xe043b8 (zero-filled .bss).
unsigned int g_Va00E043B8;
extern unsigned int g_Va00E043C0;
// g_Va00E043C0: matched references place it at VA 0xe043c0 (zero-filled .bss).
unsigned int g_Va00E043C0;
extern unsigned int g_Va00E043C8;
// g_Va00E043C8: matched references place it at VA 0xe043c8 (zero-filled .bss).
unsigned int g_Va00E043C8;
extern unsigned int g_Va00E043D0;
// g_Va00E043D0: matched references place it at VA 0xe043d0 (zero-filled .bss).
unsigned int g_Va00E043D0;

unsigned int Rva0079041FClearFlag(void)
{
	return g_Va00E04304 &= 0xFFFFFFFEu;
}

unsigned int Rva00790468ClearFlag(void)
{
	return g_Va00E04310 &= 0xFFFFFFFEu;
}

unsigned int Rva00790491ClearFlag(void)
{
	return g_Va00E04318 &= 0xFFFFFFFEu;
}

unsigned int Rva007904C5ClearFlag(void)
{
	return g_Va00E04320 &= 0xFFFFFFFEu;
}

unsigned int Rva007904DCClearFlag(void)
{
	return g_Va00E0432C &= 0xFFFFFFFEu;
}

unsigned int Rva007904F3ClearFlag(void)
{
	return g_Va00E04338 &= 0xFFFFFFFEu;
}

unsigned int Rva00790550ClearFlag(void)
{
	return g_Va00E04344 &= 0xFFFFFFFEu;
}

unsigned int Rva00790567ClearFlag(void)
{
	return g_Va00E04350 &= 0xFFFFFFFEu;
}

unsigned int Rva007905B4ClearFlag(void)
{
	return g_Va00E0435C &= 0xFFFFFFFEu;
}

unsigned int Rva007907A3ClearFlag(void)
{
	return g_Va00E04370 &= 0xFFFFFFFEu;
}

unsigned int Rva007907BAClearFlag(void)
{
	return g_Va00E0437C &= 0xFFFFFFFEu;
}

unsigned int Rva00790866ClearFlag(void)
{
	return g_Va00E04388 &= 0xFFFFFFFEu;
}

unsigned int Rva0079088FClearFlag(void)
{
	return g_Va00E04390 &= 0xFFFFFFFEu;
}

unsigned int Rva0079090DClearFlag(void)
{
	return g_Va00E04398 &= 0xFFFFFFFEu;
}

unsigned int Rva0079095CClearFlag(void)
{
	return g_Va00E043A0 &= 0xFFFFFFFEu;
}

unsigned int Rva007909B7ClearFlag(void)
{
	return g_Va00E043A8 &= 0xFFFFFFFEu;
}

unsigned int Rva007909CEClearFlag(void)
{
	return g_Va00E043B0 &= 0xFFFFFFFEu;
}

unsigned int Rva00790A3DClearFlag(void)
{
	return g_Va00E043B8 &= 0xFFFFFFFEu;
}

unsigned int Rva00790AA3ClearFlag(void)
{
	return g_Va00E043C0 &= 0xFFFFFFFEu;
}

unsigned int Rva00790ABAClearFlag(void)
{
	return g_Va00E043C8 &= 0xFFFFFFFEu;
}

unsigned int Rva00790AD1ClearFlag(void)
{
	return g_Va00E043D0 &= 0xFFFFFFFEu;
}
