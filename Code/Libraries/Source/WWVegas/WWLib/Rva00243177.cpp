// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0Rva00243177@@QAE@XZ @0x00243177 50B. Ctor stores vtable 0x00BEE024 then constructs map<long LadderPref> at +4.
// Evidence: vptr store plus rowed map ctor 0x00242F01 plus __EH_prolog plus caller 0x0024410C plus unblocks 0x00243EE7.
#include "unicode_string.h"
#include "ascii_string.h"
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

class LadderPref
{
public:
	LadderPref();
	LadderPref(const LadderPref &source);
	~LadderPref();

	UnicodeString name;
	AsciiString address;
	unsigned short port;
	long lastPlayDate;
};

class Rva00243177Base
{
public:
	virtual ~Rva00243177Base() {}
};

class Rva00243177 : public Rva00243177Base
{
public:
	Rva00243177();
	virtual ~Rva00243177();
private:
	_STL::map<long, LadderPref, _STL::less<long>, _STL::allocator<_STL::pair<const long, LadderPref> > > m_map;
};

Rva00243177::Rva00243177()
{
}
