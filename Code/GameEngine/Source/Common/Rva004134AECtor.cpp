// cl: /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ??0Rva004134AE@@QAE@XZ, retail 0x0041345B, 55 bytes (RET0).
// The constructor of the class whose nonvirtual dtor 0x004134AE and deleting
// dtor 0x00413492 are rowed (Rva004134AEDtor.cpp). Retail: base ctor
// ??0SubsystemInterface@@QAE@XZ 0x001B4E63 with ecx=this, EH state 0, vtable
// store at +0, then the +0xC member constructed through the rowed map default
// ctor 0x00242F01 (pinned as ?$map@JVLadderPref@@...), returning this. The
// mangled name and the member's original element type are not asserted beyond
// the rowed callee spellings.
#include <map>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_pad04[8];
};

class LadderPref { public: char m_opaque[0x2C]; };

class Rva004134AE : public SubsystemInterface
{
public:
	Rva004134AE();

private:
	_STL::map<long, LadderPref> m_tree0C;
};

Rva004134AE::Rva004134AE()
{
}
