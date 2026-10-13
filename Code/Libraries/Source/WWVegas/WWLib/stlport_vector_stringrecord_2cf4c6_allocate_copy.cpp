// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 20-byte BfmeStringRecord002CF4C6 vector allocation/copy helper at RVA 0x2CFC4E.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

class AsciiString { public: AsciiString(const AsciiString &); __forceinline ~AsciiString(); protected: void releaseBuffer(); private: void *m_data; };
#include "../../../../../reference/shims/bfme2_ascii/string_base.h"
__forceinline AsciiString::AsciiString(const AsciiString &that) { ((::StringBase<char> *)this)->StringBase<char>::StringBase(*(const ::StringBase<char> *)&that); }
struct BfmeStringRecord002CF4C6 {
    AsciiString text0, text1;
    unsigned int word0, word1;
    unsigned char flag0, flag1;
    BfmeStringRecord002CF4C6();
    BfmeStringRecord002CF4C6(const BfmeStringRecord002CF4C6 &o) : text0(o.text0), text1(o.text1), word0(o.word0), word1(o.word1), flag0(o.flag0), flag1(o.flag1) {}
};
#include <memory>
template void _STL::_Construct<BfmeStringRecord002CF4C6,BfmeStringRecord002CF4C6>(BfmeStringRecord002CF4C6*,const BfmeStringRecord002CF4C6&);
#include <vector>
namespace _STL { template<> vector<BfmeStringRecord002CF4C6> &vector<BfmeStringRecord002CF4C6>::operator=(const vector<BfmeStringRecord002CF4C6> &); }
template BfmeStringRecord002CF4C6* _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> >::_M_allocate_and_copy<const BfmeStringRecord002CF4C6*>(unsigned int,const BfmeStringRecord002CF4C6*,const BfmeStringRecord002CF4C6*);
template void _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> >::push_back(const BfmeStringRecord002CF4C6 &);
template _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> >::~vector();
// ?bfmeEmitstlport_vector_2cf4c6_uninitialized_copy@@YAXPAUBfmeStringRecord002CF4C6@@@Z present-unmatched
void bfmeEmitstlport_vector_2cf4c6_uninitialized_copy(const BfmeStringRecord002CF4C6 *p)
{
	_STL::__uninitialized_copy(p, p, (BfmeStringRecord002CF4C6 *)0, _STL::__false_type());
}
// ?bfmeEmitstlport_vector_2cf4c6_fill@@YAXPAUBfmeStringRecord002CF4C6@@@Z present-unmatched
void bfmeEmitstlport_vector_2cf4c6_fill(const BfmeStringRecord002CF4C6 *p)
{
	_STL::fill((BfmeStringRecord002CF4C6 *)0, (BfmeStringRecord002CF4C6 *)0, *p);
}
// ?bfmeEmitstlport_vector_2cf4c6_copy_backward@@YAXPAUBfmeStringRecord002CF4C6@@@Z present-unmatched
void bfmeEmitstlport_vector_2cf4c6_copy_backward(BfmeStringRecord002CF4C6 *p)
{
	_STL::__copy_backward(p, p, p, _STL::random_access_iterator_tag(), (int *)0);
}
// ?bfmeEmitstlport_vector_2cf4c6_copy_backward_ptrs@@YAXPAUBfmeStringRecord002CF4C6@@@Z present-unmatched
void bfmeEmitstlport_vector_2cf4c6_copy_backward_ptrs(BfmeStringRecord002CF4C6 *p)
{
	_STL::__copy_backward_ptrs(p, p, p, _STL::__false_type());
}
// ?bfmeEmitstlport_vector_2cf4c6_uninitialized_fill_n@@YAXPAUBfmeStringRecord002CF4C6@@@Z present-unmatched
void bfmeEmitstlport_vector_2cf4c6_uninitialized_fill_n(const BfmeStringRecord002CF4C6 *p)
{
	_STL::__uninitialized_fill_n((BfmeStringRecord002CF4C6 *)0, 0u, *p, _STL::__false_type());
}
