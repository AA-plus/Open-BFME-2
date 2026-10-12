// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0041573F@@QAE@ABV0@@Z @0x0041573F 67B
// Honest Rva copy ctor: BfmeOwnedRecordArray56 at +0 via rowed copy 0x004151A3
// plus _Rb_tree900 at +0x1C0 via rowed copy 0x0041559E. Declared Array56 dtor
// reproduces the retail EH state. Flags copied from sibling OwnedRecord900TreeCopy.cpp.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <map>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class Rva002390CB { void *a; void *b; public: __declspec(nothrow) Rva002390CB(const Rva002390CB &o); ~Rva002390CB(); };
struct BfmeStringRecord002CF550 {
	~BfmeStringRecord002CF550();
	AsciiString text;
	Rva002390CB ref;
};
bool operator<(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r);
namespace _STL { template <> struct less<BfmeStringRecord002CF550> { bool operator()(const BfmeStringRecord002CF550 &l, const BfmeStringRecord002CF550 &r) const; }; }
typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > Tree900;
class BfmeOwnedRecordArray56 {
	char m_data[0x1C0];
public:
	BfmeOwnedRecordArray56(const BfmeOwnedRecordArray56 &o);
	~BfmeOwnedRecordArray56();
};
class Rva0041573F {
public:
	Rva0041573F(const Rva0041573F &src);
	~Rva0041573F();
private:
	BfmeOwnedRecordArray56 m_arr;
	Tree900 m_tree;
};
Rva0041573F::Rva0041573F(const Rva0041573F &src)
	: m_arr(src.m_arr)
	, m_tree(src.m_tree)
{
}

class Rva0041579E {
public:
	Rva0041579E(const Rva0041579E &src);
	~Rva0041579E();
private:
	int m_00;
	Rva0041573F m_04;
};
Rva0041579E::Rva0041579E(const Rva0041579E &src)
	: m_00(src.m_00)
	, m_04(src.m_04)
{
}

Rva0041579E::~Rva0041579E()
{
}

// ??0Rva0022A809Subsystem@@QAE@XZ, retail 0x00415704, 59 bytes.
// Gap between ??1Rva0041579E 0x004156FC and ??0Rva0041573F 0x0041573F; called by matched GameEngine::init 0x0022ED66;
// calls rowed BFME2NativeNetwork::baseConstruct 0x001B4E63 and rowed hash_map ctor 0x00415643; vtable 0x0083A288; byte at +0x20.
#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
}
struct Rva00415643Element { char bytes[1]; };
class BFME2NativeNetwork
{
public:
};
// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class __declspec(novtable) Rva0022A809SubsystemBase
{
public:
	Rva0022A809SubsystemBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~Rva0022A809SubsystemBase();
private:
	unsigned char m_04;
	int m_08;
};
class Rva0022A809Subsystem : public Rva0022A809SubsystemBase
{
public:
	Rva0022A809Subsystem();
	virtual ~Rva0022A809Subsystem();
private:
	_STL::hash_map<int, Rva00415643Element> m_map0C; // +0x0C
	unsigned char m_20; // +0x20
};
Rva0022A809Subsystem::Rva0022A809Subsystem()
	: m_20(0)
{
}
