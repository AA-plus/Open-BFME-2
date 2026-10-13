// cl: /Ireference/shims/bfme2_ascii /MD
// ?append@Rva0049B6AE@@QAEXPBDPAV?$StringBase@D@@@Z, retail 0x0049B6AE, 47 bytes.
// Path-like join: if String non-null and non-empty prepend default at 0x00BBD40C then append char arg.
// Evidence: callees isEmpty 0x1E2F concat 0x5629 rowed; callers 8x 234B; prev Disp8 next UpdateDeletingDtors.
// A member: every caller (the 234B bitstring-list drivers 0x0033B84E, 0x002C8754,
// 0x00256499, 0x003B1017, 0x003FB508, ...) sets ecx to its own receiver right
// before the push/call pair. The body never reads ecx, so the drivers' different
// receiver classes all reach this one address; the class name is address-derived.
#include "string_base.h"

class Rva0049B6AE
{
public:
	void append(const char *a, StringBase<char> *b);
};

void Rva0049B6AE::append(const char *a, StringBase<char> *b)
{
	if (b == 0)
		return;
	if (!b->isEmpty())
		b->concat(" ");
	b->concat(a);
}
