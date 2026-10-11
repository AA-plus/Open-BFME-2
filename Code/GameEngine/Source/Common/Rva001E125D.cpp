// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
#include "ascii_string.h"
// ??1Rva001E125D@@UAE@XZ retail 0x001E125D 62B
// Evidence: unlock lane stores vtable at this then destroys member at +0x148 via releaseBuffer then base ??1Rva001DFA48Owner. Caller 0x001E1241 28B.
class Rva001DFA48Owner
{
public:
	virtual ~Rva001DFA48Owner();
};

class Rva001E125D : public Rva001DFA48Owner
{
public:
	virtual ~Rva001E125D();
private:
	char m_pad04[0x148 - 0x4];
	AsciiString m_str148;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva001E125D::~Rva001E125D()
{
}

// ?bfmeAnchorRva001E125DDtor absent-from-retail
void bfmeAnchorRva001E125DDtor(Rva001E125D *p)
{
	p->Rva001E125D::~Rva001E125D();
}
