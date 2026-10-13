// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /EHsc /DNDEBUG /MD /O1 /Oy- /Gy
#include "unicode_string.h"
// ?Rva00559CE5@@YA?AVUnicodeString@@HH@Z, retail 0x00559CE5, 39 bytes.
// Target evidence: Ghidra gives this exact boundary. Its two retail callers pass a result slot
// and two integers, then use that slot as a UnicodeString. The body validates the first integer
// through the matched 0x00559B4B helper and forwards its byte result with the second integer to
// 0x00559C3D (WB 0x013F9DD0 RankPointValue::RankString). The WB wrapper (0x013F9F20) keeps a
// returned-temporary flag local (retail's `and [ebp-4],0`). The method and class identity
// of the wrapper remain unknown.
// Codegen: retail keeps `add esp,4` after the checker call and the ebp frame only when the
// checker's body is visible in the unit (its register effects are known); the visible copy is
// the same COMDAT name as the matched 0x00559B4B row, which the link resolves to retail's bytes.
__declspec(noinline) unsigned char __cdecl Rva00559B4BCheck(int v)
{
	return v == 3 || v == 4 || v == 5;
}
UnicodeString __cdecl Rva00559C3D(unsigned char valid, int value);
UnicodeString __cdecl Rva00559CE5(int type, int value)
{
	return Rva00559C3D(Rva00559B4BCheck(type), value);
}
