// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0CivilianSpawnUpdateModuleData@@QAE@XZ, retail 0x0047FA55 (78 bytes).
// EH derived ctor over a trivially-constructed base with a declared virtual
// dtor (its unwind state 0 covers the member calls): the +0x0C filter
// member constructs through the pinned Rva003623E5Filter ctor and the +0x14
// vector<int> member through the ICF-folded Vector_base at 0x00211E58 (both
// implicit, in declaration order, allocator temp on ebp), the compiler
// installs vtable 0x00C48530 automatically, then the body stores the global
// to +0x08 and 300 to +0x10. No further states (all members trivially
// destructible). Element type int is a stand-in (trivial plus resolving
// through the ICF-folded int row; the true element is unproven). Shard TU:
// the parse lives in the twin-owned CivilianSpawnUpdateModuleDataCtor.cpp
// (which reserves this ctor for follow-up); this TU carries only the ctor.
// Identity is the ModuleFactory registration under "CivilianSpawnUpdate"
// (sole-caller data factory per the superseded ctor pin).

#include <vector>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
};

extern int BfmeLogicFramesPerSecond;	// retail 0xDBA4E4, value 5 (DIR32-masked)

class CivilianSpawnBase
{
public:
	virtual ~CivilianSpawnBase();

protected:
	void *m_unsourced04;	// +0x04, retail never stores it
	int m_int08;	// +0x08, global store by the derived ctor
};

class CivilianSpawnUpdateModuleData : public CivilianSpawnBase
{
public:
	CivilianSpawnUpdateModuleData();
	virtual ~CivilianSpawnUpdateModuleData();

private:
	Rva003623E5Filter m_filter0C;	// +0x0C
	int m_int10;	// +0x10
	_STL::vector<int> m_vec14;	// +0x14, element stand-in
};

CivilianSpawnUpdateModuleData::CivilianSpawnUpdateModuleData()
	: m_vec14(_STL::allocator<int>())
{
	m_int08 = BfmeLogicFramesPerSecond;
	m_int10 = 300;
}
