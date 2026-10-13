// ?_M_insert_overflow@?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@IAEXPAPAVObject@@ABQAV3@ABU__true_type@2@I_N@Z
// partial score=0.8 date=2026-10-13
// ?_M_insert_overflow@?$vector@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@IAEXPAPAVObject@@ABQAV3@ABU__true_type@2@I_N@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector::push_back for five element types whose _Construct
// and _M_insert_overflow rows already exist: retail 0x001ED285, 0x002B14EB,
// 0x004F93E7, 0x005ECC19 and 0x00337CEA, 55 bytes each.
// Evidence: each body is the unowned retail caller of its element's matched
// _Construct (fast path) and _M_insert_overflow (growth path), byte-identical
// with relocations masked to the rowed push_back siblings in
// StlportVectorGrowthFootprints.cpp, whose flags and footprint recipe this TU
// mirrors: out-of-line copy ctor and dtor, and _Construct declared as an
// explicit specialization so the fast path calls the element's _Construct row.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

// 36-byte element; layout owner StringContainerRecordCopyBFME2.cpp.
struct BfmeRecord001ECAF9 { char m_pad[36]; public: BfmeRecord001ECAF9(const BfmeRecord001ECAF9 &); ~BfmeRecord001ECAF9(); };
// 36-byte element; layout as in StlportVectorGrowthFootprints.cpp.
struct BfmeVectorRecord002AF478 { char m_pad[36]; public: BfmeVectorRecord002AF478(const BfmeVectorRecord002AF478 &); ~BfmeVectorRecord002AF478(); };
// 24-byte element; layout owner StringRecordInlineCopyBFME2.cpp.
struct BfmeStringRecord005EC43C { char m_pad[24]; public: BfmeStringRecord005EC43C(const BfmeStringRecord005EC43C &); ~BfmeStringRecord005EC43C(); };
// 12-byte element; layout as in StlportVectorGrowthFootprints.cpp.
struct Rva004F6352 { char m_pad[12]; public: Rva004F6352(const Rva004F6352 &); ~Rva004F6352(); };

// 20-byte element; layout owner Rva003371B1Copy.cpp.
class Rva003371B1 { char m_pad[20]; public: Rva003371B1(const Rva003371B1 &); ~Rva003371B1(); };

namespace _STL
{
template <> void _Construct<BfmeRecord001ECAF9, BfmeRecord001ECAF9>(BfmeRecord001ECAF9 *, const BfmeRecord001ECAF9 &);
template <> void _Construct<BfmeVectorRecord002AF478, BfmeVectorRecord002AF478>(BfmeVectorRecord002AF478 *, const BfmeVectorRecord002AF478 &);
template <> void _Construct<Rva004F6352, Rva004F6352>(Rva004F6352 *, const Rva004F6352 &);
template <> void _Construct<BfmeStringRecord005EC43C, BfmeStringRecord005EC43C>(BfmeStringRecord005EC43C *, const BfmeStringRecord005EC43C &);
template <> void _Construct<Rva003371B1, Rva003371B1>(Rva003371B1 *, const Rva003371B1 &);
}

template void _STL::vector<BfmeRecord001ECAF9>::push_back(const BfmeRecord001ECAF9 &);
template void _STL::vector<BfmeVectorRecord002AF478>::push_back(const BfmeVectorRecord002AF478 &);
template void _STL::vector<Rva004F6352>::push_back(const Rva004F6352 &);
template void _STL::vector<BfmeStringRecord005EC43C>::push_back(const BfmeStringRecord005EC43C &);
template void _STL::vector<Rva003371B1>::push_back(const Rva003371B1 &);

class Object;
template <> void _STL::vector<Object *>::_M_insert_overflow(Object **, Object * const &, const _STL::__true_type &, unsigned, bool);
template void _STL::vector<Object *>::push_back(Object * const &);


namespace _STL {
template <> void vector<Object *>::_M_clear();
template <> void vector<Object *>::_M_insert_overflow(Object **pos, Object * const &val, const __true_type &, unsigned n, bool at_end) {
 const unsigned old_size=this->_M_finish-this->_M_start;
 unsigned tmp=old_size;
 const unsigned *pmax=&n;
 if(old_size>=n)pmax=&tmp;
 const unsigned new_len=old_size+*pmax;
 Object **new_start;
 if(new_len) new_start=(Object **)allocator<char>::allocate(new_len*sizeof(Object *),0);
 else new_start=0;
 Object **new_finish=(Object **)__copy_trivial(this->_M_start,pos,new_start);
 unsigned c=n;
 if(c)do { *new_finish++=val; }while(--c);
 if(!at_end)new_finish=(Object **)__copy_trivial(pos,this->_M_finish,new_finish);
 _M_clear();
 this->_M_finish=new_finish;
 this->_M_start=new_start;
 this->_M_end_of_storage._M_data=new_start+new_len;
}
}

// W6-MO1 alternative 2026-10-12 score=0.8: explicit Object* overflow TU attempt
// (full bfmealloc + /EHsc, dtor suppressed to folded 0x7FAB3). __true_type gives
// 170B frameless-no-EH; __false_type gives 272B full-SEH; retail 147B EBP+EH.
// Needs /EHsc home TU (not Siblings-no-EHsc, not alloconly). Full TU in stash.
// (see re_log row for full TU text)
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport vector<Object*>::_M_insert_overflow (__true_type) at 0x001F2155,
// called from the rowed vector<Object*>::push_back 0x001F211B.
// Evidence: 147B body grows/copies 4B records; rowed byte allocator 0x307F0,
// out-of-line __copy_trivial 0x179B0, folded vector dtor 0x7FAB3 and the
// (pos, value-ref, tag, count, at-end) five-argument shape with ret 0x14.
// Uses the full bfmealloc shim (not alloconly) so allocation and the trivial
// copies resolve out of line as retail shows.
#include <vector>

class Object;

// This TU must not emit its own vector<Object*> teardown copy: the call
// binds the folded rowed copy at 0x7FAB3.
namespace _STL {
template <> vector<Object *, allocator<Object *> >::~vector();
}

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row).
// This unit-local overload keeps the inlined code and offers the link no
// second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

template void _STL::vector<Object *, _STL::allocator<Object *> >::_M_insert_overflow(
    Object **, Object * const &, const _STL::__true_type &, unsigned, bool);
