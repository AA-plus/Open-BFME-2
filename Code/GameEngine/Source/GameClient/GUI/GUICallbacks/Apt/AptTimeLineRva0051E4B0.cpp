// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0051E4B0@Rva0051E4B0@@QAEXXZ retail 0x0051E4B0 97B (WB lead: the AptTimeLine
// unit, 0x013DB390). Chain via 0x005BE264; neighbours Rva0051E458PowFloat and Rva0051E939Copy.
// Evidence: thiscall reads ecx first, string AptTimeLine::RenderGraph, TheRva00222A8BTarget via 0x002246B1, this+0x218 via 0x0052493F, this+0x280 guard for 0x005BE264.
#include "ascii_string.h"

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;

class Rva002246B1
{
public:
	int RemoveCustomRender(const AsciiString *key);
};

class Rva0052493F
{
public:
	void rva0052493F();
};

// 0x005BE264 ignores ECX, but this caller reaches it as a member of the
// +0x280 object (it loads that pointer into ECX); thiscall pin spelling.
class Rva005BE264Owner
{
public:
	void rva005BE264();
};

class Rva0051E4B0
{
public:
	void rva0051E4B0();
	char m_pad[0x280];
	Rva005BE264Owner *m_280;
};

void Rva0051E4B0::rva0051E4B0()
{
	{
		AsciiString s("AptTimeLine::RenderGraph");
		((Rva002246B1 *)TheRva00222A8BTarget)->RemoveCustomRender(&s);
	}
	((Rva0052493F *)((char *)this + 0x218))->rva0052493F();
	if (m_280)
		m_280->rva005BE264();
}
