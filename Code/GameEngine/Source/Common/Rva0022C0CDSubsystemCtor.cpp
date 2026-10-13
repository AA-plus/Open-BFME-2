// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0022C0CDSubsystem@@QAE@XZ, retail 0x0022DA03, 71 bytes.
//
// Evidence: the pin has carried this ctor address since the GameEngine::init
// recovery (initSubsystem<Rva0022C0CDSubsystem> news it), and
// Rva002E0427Dtor.cpp -- the rowed destructor of the same object -- names the
// three members: int at +0x0C, then two 0x14-byte hash members at +0x10 and
// +0x24 over the rowed SubsystemInterface base 0x001B4E63, with the same
// vtable 0x00BE7628 stored here. The member constructors are the rowed
// hash_map<int,Element> instantiations 0x0022D95A and 0x00224C76. Total size
// 0x38 matches the GameEngineInit view.

#include <hash_map>

struct Rva0022D95AElement
{
	char bytes[1];
	bool operator<(const Rva0022D95AElement &) const;
	bool operator==(const Rva0022D95AElement &) const;
};

struct Rva00224C76Element
{
	char bytes[1];
	bool operator<(const Rva00224C76Element &) const;
	bool operator==(const Rva00224C76Element &) const;
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	char m_pad04[8];
};

class Rva0022C0CDSubsystem : public SubsystemInterface
{
public:
	Rva0022C0CDSubsystem();
	virtual ~Rva0022C0CDSubsystem();

private:
	int m_0C; // +0x0C
	_STL::hash_map<int, Rva0022D95AElement> m_10; // +0x10
	_STL::hash_map<int, Rva00224C76Element> m_24; // +0x24
};

Rva0022C0CDSubsystem::Rva0022C0CDSubsystem()
	: m_0C(0)
{
}
