// cl: /EHsc /Ireference/shims/bfme2_ascii /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// ??0Rva0040B707@@QAE@ABV0@@Z @0x0040B707 119B unlock copy ctor with vector ScienceType plus three AsciiStrings plus vector BfmeRecord0040B61A; caller 0x0040B9BB
#include <vector>
#include "ascii_string.h"

enum ScienceType
{
	ScienceType_0
};
struct BfmeRecord0040B61A
{
	char m_bytes[1];
};

class Rva0040B707
{
public:
	Rva0040B707(const Rva0040B707 &o);
private:
	int m_00;
	_STL::vector<ScienceType> m_04;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	_STL::vector<BfmeRecord0040B61A> m_1C;
};

// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeRecord0040B61A,BfmeRecord0040B61A>(BfmeRecord0040B61A *,BfmeRecord0040B61A const &); }
namespace _STL { template <> void _Destroy<BfmeRecord0040B61A *>(BfmeRecord0040B61A *,BfmeRecord0040B61A *); }
namespace _STL { template <> void _Destroy<BfmeRecord0040B61A>(BfmeRecord0040B61A *); }
namespace _STL { template <> void __destroy<BfmeRecord0040B61A *,BfmeRecord0040B61A>(BfmeRecord0040B61A *,BfmeRecord0040B61A *,BfmeRecord0040B61A *); }
namespace _STL { template <> void __destroy_aux<BfmeRecord0040B61A *>(BfmeRecord0040B61A *,BfmeRecord0040B61A *,_STL::__false_type const &); }
namespace _STL { template <> BfmeRecord0040B61A * __uninitialized_copy<BfmeRecord0040B61A const *,BfmeRecord0040B61A *>(BfmeRecord0040B61A const *,BfmeRecord0040B61A const *,BfmeRecord0040B61A *,_STL::__false_type const &); }
namespace _STL { template <> _Vector_base<BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> >::_Vector_base(unsigned int,_STL::allocator<BfmeRecord0040B61A> const &); }
namespace _STL { template <> _Vector_base<ScienceType,_STL::allocator<ScienceType> >::_Vector_base(unsigned int,_STL::allocator<ScienceType> const &); }
namespace _STL { template <> vector<BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> >::vector(_STL::vector<BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> > const &); }
namespace _STL { template <> vector<ScienceType,_STL::allocator<ScienceType> >::vector(_STL::vector<ScienceType,_STL::allocator<ScienceType> > const &); }
namespace _STL { template <> _Vector_base<BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> >::~_Vector_base(); }
namespace _STL { template <> _Vector_base<ScienceType,_STL::allocator<ScienceType> >::~_Vector_base(); }
namespace _STL { template <> vector<BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> >::~vector(); }
namespace _STL { template <> vector<ScienceType,_STL::allocator<ScienceType> >::~vector(); }
namespace _STL { template <> BfmeRecord0040B61A * _STLP_alloc_proxy<BfmeRecord0040B61A *,BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> >::allocate(unsigned int); }
namespace _STL { template <> ScienceType * _STLP_alloc_proxy<ScienceType *,ScienceType,_STL::allocator<ScienceType> >::allocate(unsigned int); }
namespace _STL { template <> BfmeRecord0040B61A * allocator<BfmeRecord0040B61A>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> ScienceType * allocator<ScienceType>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<BfmeRecord0040B61A *,BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> >::deallocate(BfmeRecord0040B61A *,unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<ScienceType *,ScienceType,_STL::allocator<ScienceType> >::deallocate(ScienceType *,unsigned int); }
namespace _STL { template <> void allocator<BfmeRecord0040B61A>::deallocate(BfmeRecord0040B61A *,unsigned int) const; }
namespace _STL { template <> void allocator<ScienceType>::deallocate(ScienceType *,unsigned int) const; }
namespace _STL { template <> unsigned int vector<BfmeRecord0040B61A,_STL::allocator<BfmeRecord0040B61A> >::size() const; }
// bfme link decl-only end
Rva0040B707::Rva0040B707(const Rva0040B707 &o) : m_00(o.m_00), m_04(o.m_04), m_10(o.m_10), m_14(o.m_14), m_18(o.m_18), m_1C(o.m_1C)
{
}
