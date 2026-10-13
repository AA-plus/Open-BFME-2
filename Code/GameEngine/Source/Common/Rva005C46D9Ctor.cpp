// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /EHsc /MD /DCRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva005C46D9@@QAE@ABV?$StringBase@D@@@Z, retail 0x005C46D9, 71 bytes.
//
// Evidence: base ctor 0x004FA815 takes the StringBase reference, the vtable
// 0x00C746CC and the two zeroed words at +8/+0xC follow, and the member map at
// +0x10 default-constructs through the pinned map<string,int> ctor 0x00413727.
// The prior wall was map initialization hoisting ahead of the vtable and
// member stores under the region flags; member declaration order here puts the
// map last so it constructs last.

#include <map>
#include <string>

#include "ascii_string.h"

class Rva004FA830
{
public:
	Rva004FA830(const StringBase<char> &text);
	virtual ~Rva004FA830();

private:
	char m_pad[4];
};

class Rva005C46D9 : public Rva004FA830
{
public:
	Rva005C46D9(const StringBase<char> &text);
	virtual ~Rva005C46D9();

private:
	int m_8;
	AsciiString m_c;
	std::map<std::string, int> m_map10;
};

Rva005C46D9::Rva005C46D9(const StringBase<char> &text)
	: Rva004FA830(text), m_8(0)
{
}
