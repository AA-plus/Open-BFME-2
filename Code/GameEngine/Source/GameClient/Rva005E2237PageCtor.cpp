// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// Retail 0x005E2237..0x005E228C is the complete 86-byte RET0 constructor
// between the rowed 0x005E2226 forwarder and the rowed Icon getter 0x005E228D,
// in the StrategicInGameUI RegionDetailsStructuresPage chapter.
// Target facts: the constructor builds an AsciiString temporary from the
// literal "RegionDetailsPanelStructuresPage" (the shim's AsciiString(const char*)
// emits the rowed StringBase<char>::StringBase(const char*) call 0x00037BA0 and
// its releaseBuffer destruction 0x00036410), passes that temporary to the base
// constructor at 0x00221635, then stores the class vtable (retail 0x00C77AD8)
// and the dword 0x80ffffff at +8.  The literal names the registered page; it
// does not establish the C++ class name, so the class keeps an address-derived
// name.  The base is the same 8-byte polymorphic holder as the StatsDisplay
// sibling: its constructor 0x00221635 takes the const AsciiString& (pinned
// ??0Rva0022167C@@QAE@ABVAsciiString@@@Z) and its virtual destructor
// 0x0022167C is pinned as ??1Rva0022167C@@UAE@XZ, which is the cleanup retail's
// state-2 unwind action calls with the spilled this at [ebp-0x14].
#include "ascii_string.h"

class Rva0022167C {
public:
	Rva0022167C(const AsciiString &name);
	virtual ~Rva0022167C();
private:
	void *m_at4;
};

class Rva005E2237 : public Rva0022167C {
public:
	Rva005E2237();
private:
	int m_08;
};

Rva005E2237::Rva005E2237() : Rva0022167C(AsciiString("RegionDetailsPanelStructuresPage"))
{
	m_08 = 0x80ffffff;
}
