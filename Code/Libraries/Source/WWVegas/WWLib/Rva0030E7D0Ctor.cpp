// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
// ??0Rva0030E7D0@@QAE@XZ @0x0030E7D0 46B ctor vector BfmeE16 at +0 via rowed Vector_base 0x00211E58 zeroes +0xC +0x10 +0x18 and byte +0x1C float +0x14 from g_Va00BBB8D8 evidence callers 0x0008BA61 neighbours ParabolicEase and StlportVectorFill
#include <vector>

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

#include "../../../Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

extern float g_Va00BBB8D8;

class Rva0030E7D0
{
public:
	Rva0030E7D0();
private:
	_STL::vector<BfmeE16> m_vec00;
	int m_0C;
	int m_10;
	float m_14;
	int m_18;
	bool m_1C;
};

Rva0030E7D0::Rva0030E7D0()
	: m_vec00()
{
	m_14 = g_Va00BBB8D8;
	m_0C = 0;
	m_10 = 0;
	m_18 = 0;
	m_1C = false;
}
