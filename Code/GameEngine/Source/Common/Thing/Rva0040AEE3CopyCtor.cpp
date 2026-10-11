// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0040AEE3@@QAE@ABV0@@Z @0x0040AEE3 27B
// Evidence: unlock lane; calls rowed vector<ScienceType> copy 0x0054878E; copies int at +0xC; caller 0x0040B16A.
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

enum ScienceType
{
	SCIENCE_NONE = 0
};

class Rva0040AEE3
{
public:
	Rva0040AEE3(const Rva0040AEE3 &other);
	Rva0040AEE3 &operator=(const Rva0040AEE3 &other);
private:
	_STL::vector<ScienceType> m_0000;
	int m_000C;
};

Rva0040AEE3::Rva0040AEE3(const Rva0040AEE3 &other)
	: m_0000(other.m_0000)
	, m_000C(other.m_000C)
{
}

Rva0040AEE3 &Rva0040AEE3::operator=(const Rva0040AEE3 &other)
{
	if (&other != this) {
		// Folded 4B-POD assign: ScienceType and int share bytes (PlayerScienceAssign
		// precedent); int spelling pins to 0x0021C21B, ScienceType pin sits at 0x120C0.
		(_STL::vector<int> &)m_0000 = (const _STL::vector<int> &)other.m_0000;
		m_000C = other.m_000C;
	}
	return *this;
}
