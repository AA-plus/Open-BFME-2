// ?rva0020874B@ScriptEngine@@QAEPAXVAsciiString@@@Z
// partial score=0.94 date=2026-10-02
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs
// stlport
// ?rva0020874B@ScriptEngine@@QAEPAXVAsciiString@@@Z @0x0020874B 207B
// Unlock callee of 24 free functions via resolveName plus Rva0002C4FD plus Make plus insert_unique
// Target evidence: callers 0x00208F89 0x00209330 etc unblocks 11 ready; neighbours 0x002086BD 0x0020881A same cl
// member at this+0x190A0 is first team map per sibling second map at +0x190AC in ScriptEngineRva0020881A
#include "ascii_string.h"
#include <set>

class AsciiString;

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);
};

struct Rva0002C4FD : public _STL::pair<const AsciiString, AsciiString>
{
	Rva0002C4FD(const StringBase<char> &a, const StringBase<char> &b);
};

struct Rva00204A83
{
	_STL::pair<AsciiString, AsciiString> m_pair;
	__int64 m_val;
	Rva00204A83(const _STL::pair<AsciiString, AsciiString> &p, const __int64 &v);
};

Rva00204A83 Rva00205655Make(const _STL::pair<AsciiString, AsciiString> &p, const __int64 &v);

struct Rva00204B12
{
	_STL::pair<AsciiString, AsciiString> m_pair;
	int m_a;
	int m_b;
	Rva00204B12(const Rva00204B12 &o);
};

bool operator<(const _STL::pair<AsciiString, AsciiString> &a, const _STL::pair<AsciiString, AsciiString> &b);
inline bool operator<(const Rva00204B12 &a, const Rva00204B12 &b) { return (const _STL::pair<AsciiString, AsciiString> &)a.m_pair < (const _STL::pair<AsciiString, AsciiString> &)b.m_pair; }

typedef _STL::_Rb_tree<Rva00204B12, Rva00204B12, _STL::_Identity<Rva00204B12>, _STL::less<Rva00204B12>, _STL::allocator<Rva00204B12> > Rva00204B12Tree;

class ScriptEngine : public Rva002046C0Owner
{
public:
// ?rva0020874B@ScriptEngine@@QAEPAXVAsciiString@@@Z present-unmatched
	void *rva0020874B(AsciiString name);
private:
	char m_pad[0x190A0];
	Rva00204B12Tree m_map190A0;
};

void *ScriptEngine::rva0020874B(AsciiString name)
{
	AsciiString resolved = resolveName(name);
	Rva0002C4FD key(*(const StringBase<char> *)&resolved, *(const StringBase<char> *)&name);
	Rva00204A83 maker = Rva00205655Make(*(const _STL::pair<AsciiString, AsciiString> *)(const void *)&key, __int64(0));
	Rva00204B12 node(*(const Rva00204B12 *)(const void *)&maker);
	return (void *)((char *)m_map190A0.insert_unique(node).first._M_node + 0x18);
}
