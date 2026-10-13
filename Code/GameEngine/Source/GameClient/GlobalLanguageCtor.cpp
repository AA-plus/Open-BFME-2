// cl: /O1 /G7 /arch:SSE /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??0GlobalLanguage@@QAE@XZ, retail 0x001EA9B5, 502 bytes.
//
// The pin has carried this ctor address since the GameEngine::init recovery,
// and GlobalLanguageDtor.cpp (rowed 0x001EABAB) fixes the same member offsets
// this ctor constructs: subsystem base 0x001B4E63, vtable 0x007DEFC8, the
// separator strings ".", "," and ":" at +0xC/+0x10/+0x14, the language string
// from the rowed GetRegistryLanguage 0x00235029 at +0x20, bool +0x24 and int
// +0x28, twenty-two FontDesc members at +0x2C..+0x128 through the rowed
// FontDesc ctor 0x00376900, the 0.7f at +0x134 (the shared constant at
// 0x00BC8180), and the list at +0x138. The three trailing releaseBuffer calls
// destroy +0x18, +0x1C and again +0x18, matching the three clear() calls.

#include <list>

#include "ascii_string.h"

typedef bool Bool;
#include "subsystem_interface.h"

struct FontDesc
{
	FontDesc();

	AsciiString name;
	int size;
	bool bold;
};

AsciiString GetRegistryLanguage();

// The real list element is the two-string record the rowed destructor names.
// The constructor never touches an element, so the ledger's already-rowed
// 8-byte fold spelling stands in for the _List_base ctor call (the same
// generator trick stlport_pod_map_bodies.cpp documents).
struct BfmePod8
{
	int words[2];
};

class GlobalLanguage : public SubsystemInterface
{
public:
	GlobalLanguage();
	virtual ~GlobalLanguage();

private:
	AsciiString m_s00C;
	AsciiString m_s010;
	AsciiString m_s014;
	AsciiString m_s018;
	AsciiString m_s01C;
	AsciiString m_language;
	bool m_useHardWrap;
	int m_militaryCaptionSpeed;
	FontDesc m_f02C;
	FontDesc m_f038;
	FontDesc m_f044;
	FontDesc m_f050;
	FontDesc m_f05C;
	FontDesc m_f068;
	FontDesc m_f074;
	FontDesc m_f080;
	FontDesc m_f08C;
	FontDesc m_f098;
	FontDesc m_f0A4;
	FontDesc m_f0B0;
	FontDesc m_f0BC;
	FontDesc m_f0C8;
	FontDesc m_f0D4;
	FontDesc m_f0E0;
	FontDesc m_f0EC;
	FontDesc m_f0F8;
	FontDesc m_f104;
	FontDesc m_f110;
	FontDesc m_f11C;
	FontDesc m_f128;
	float m_res134;
	_STL::list<BfmePod8, _STL::allocator<BfmePod8> > m_list138;
};

GlobalLanguage::GlobalLanguage()
	: m_s00C("."),
	  m_s010(","),
	  m_s014(":"),
	  m_language(GetRegistryLanguage()),
	  m_useHardWrap(false),
	  m_militaryCaptionSpeed(0),
	  m_res134(0.7f)
{
	m_s018.clear();
	m_s01C.clear();
	m_s018.clear();
}
