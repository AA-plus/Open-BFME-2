// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Gy
// stlport
//
// ?resize@?$vector@V?$vector@W4ScienceType@@...@Z @0x0033A2E9 39B: the
// single-argument resize of vector<vector<ScienceType>> (the INI science
// vector-vector parser's resize(1)): builds the default (empty) element in
// the outgoing by-value argument through the rowed empty vector-base
// constructor 0x00211E58 and calls the rowed two-argument by-value resize
// (RET 0x10 at 0x0033A23A's neighbour in stlport_uninitialized_copy_sciencevec.cpp).
//
// Same shape as 0x003F3B28 (Rva003F3B28Resize.cpp): retail passes the
// allocator temporary as lea eax,[ebp+0xb] with no stack slot, which cl only
// does once it can see the constructor never reads it, so the STLport
// _Vector_base<ScienceType> constructor is instantiated here ahead of the
// caller (/Gy keeps the copy an identical COMDAT). The outer vector is a
// hand-written view because the retail resize passes the element by value.
#include <vector>

enum ScienceType { SCIENCE_INVALID = -1 };
typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > SciVec;

template _STL::_Vector_base<ScienceType, _STL::allocator<ScienceType> >::_Vector_base(const _STL::allocator<ScienceType> &);

namespace _STL {
template <>
class vector<SciVec, allocator<SciVec> >
{
public:
	void resize(unsigned int n, SciVec value);
	void resize(unsigned int n);

private:
	SciVec *m_start;
	SciVec *m_finish;
	SciVec *m_end_of_storage;
};
}


void _STL::vector<SciVec, _STL::allocator<SciVec> >::resize(unsigned int n) { resize(n, SciVec()); }
