// ?rva002088A0@ScriptEngine@@QAEPAXVAsciiString@@@Z
// partial score=0.98 date=2026-10-02
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs
// stlport
// ?rva002088A0@ScriptEngine@@QAEPAXVAsciiString@@@Z @0x002088A0 200B
// Unlock chain from 0x0020881A via resolveName plus Rva0002C4FD plus Make plus insert_unique
// Target evidence: callers 0x0005FE56 and 0x002093AA and 0x0020942F unblocks 0x00209382 and 0x0005FDCA
// neighbours landed 0x0020881A and stlport growth 0x00209952
// member at this+0x190AC is set of Rva0033A4F0 per insert_unique row 0x002078D6
#include "ascii_string.h"
#include <utility>
#include <set>

class AsciiString;
struct TeamMapNode;

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

struct Rva0002C4FD : public _STL::pair<const AsciiString, AsciiString>
{
	Rva0002C4FD(const StringBase<char> &a, const StringBase<char> &b);
};

struct Rva00204AA4
{
	_STL::pair<AsciiString, AsciiString> m_pair;
	bool m_flag;
	Rva00204AA4(const _STL::pair<AsciiString, AsciiString> &p, const bool &f);
};

Rva00204AA4 Rva00205670Make(const _STL::pair<AsciiString, AsciiString> &p, const bool &f);

bool operator<(const _STL::pair<AsciiString, AsciiString> &, const _STL::pair<AsciiString, AsciiString> &);

class Rva0033A4F0
{
public:
	_STL::pair<AsciiString, AsciiString> key;
	char rest[4];
	Rva0033A4F0(const Rva0033A4F0 &other);
};

inline bool operator<(const Rva0033A4F0 &a, const Rva0033A4F0 &b) { return a.key < b.key; }

typedef _STL::_Rb_tree<Rva0033A4F0, Rva0033A4F0, _STL::_Identity<Rva0033A4F0>, _STL::less<Rva0033A4F0>, _STL::allocator<Rva0033A4F0> > Rva0033A4F0Tree;

class ScriptEngine : public Rva002046C0Owner
{
public:
	void *rva002088A0(AsciiString name);
private:
	char m_pad[0x190AC];
	Rva0033A4F0Tree m_set;
};

// ?rva002088A0@ScriptEngine@@QAEPAXVAsciiString@@@Z present-unmatched
void *ScriptEngine::rva002088A0(AsciiString name)
{
	AsciiString resolved = resolveName(name);
	Rva0002C4FD key(*(const StringBase<char> *)&resolved, *(const StringBase<char> *)&name);
	_STL::pair<Rva0033A4F0Tree::iterator, bool> res = ((Rva0033A4F0Tree *)((char *)this + 0x190AC))->insert_unique(Rva0033A4F0(*(const Rva0033A4F0 *)&Rva00205670Make(*(const _STL::pair<AsciiString, AsciiString> *)&key, false)));
	return (void *)((char *)res.first._M_node + 0x18);
}
