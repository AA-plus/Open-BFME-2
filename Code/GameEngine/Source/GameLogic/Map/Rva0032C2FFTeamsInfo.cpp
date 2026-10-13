// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHs /MD
//
// ?rva0032C2FF@Rva0032C2FF@@QAEXABVAsciiString@@@Z @0x0032C2FF (103B EH).
// Target evidence: thiscall receiver owns a list at +0x20 whose node value is
// an AsciiString at +0x08. Every existing value is copied to a stack temp and
// compared; on a match the function returns (temp destroyed), otherwise the
// argument is appended through the rowed list push_back
// (?push_back@?$list@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@
// QAEXABVAsciiString@@@Z at 0x001FD868). The scanner's 108-byte gap swallowed
// an unreferenced 5-byte 'jmp _Rb_tree::clear' fragment at 0x0032C366 that no
// relocation or FuncInfo references, so the real extent is 103.
// Class identity is unproven, so the owner keeps an address-derived name.

#include "ascii_string.h"
#include "Rva0032C2FFTeamsInfo.h"

class Rva0032C2FF
{
public:
	void rva0032C2FF(const AsciiString &value);

private:
	char m_unknown[0x20];
	_STL::list<AsciiString, _STL::allocator<AsciiString> > m_values;
};

void Rva0032C2FF::rva0032C2FF(const AsciiString &value)
{
	_STL::list<AsciiString, _STL::allocator<AsciiString> >::node *node = m_values.m_head->next;
	while (node != m_values.m_head)
	{
		AsciiString current(node->value);
		if (value.compare(current) == 0)
			return;
		node = node->next;
	}
	m_values.push_back(value);
}
