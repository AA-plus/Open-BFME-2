// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__uninitialized_fill_n@PAURva001741EBElement@@IU1@@_STL@@YAPAURva001741EBElement@@PAU1@IABU1@ABU__false_type@0@@Z
// @ 0x001733F6 (37B): count loop constructing via the pinned _Construct at
// 0x00173351 striding 0x30. Caller at 0x00173F67 in _M_insert_overflow
// 0x00173EF9. Same recipe as stlport_vector_bfmeassignrecord32_allocate_copy.cpp
// (37B fill_n via rowed _Construct stride 0x20).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Native173351..1733D0 (127B) is the placement-copy invoked by the
// already rowed48-byte vector push/copy/fill helpers. It constructs three
// sixteen-byte members through the empty47A6A9 callback, then copies all
// twelve words. The original record/member types remain unknown; these
// neutral words preserve their observed footprint and copy semantics.
// Native handler767C60 / FuncInfo90C6D8 has one placement-delete state:
// unwind767C52 passes the placement pointer and destination to existing
// operator delete(void*,void*)69E440. A trivial member destructor is correct;
// inventing a nontrivial destructor would select the wrong array iterator.
// The inline copy keeps the genuine placement lifetime and its EH cleanup.
struct Rva001741EBRow16 {
 __declspec(noinline) Rva001741EBRow16();
 unsigned words[4];
};
inline Rva001741EBRow16::Rva001741EBRow16() {}
struct Rva001741EBElement {
 Rva001741EBRow16 rows[3];
 Rva001741EBElement() {}
 __forceinline Rva001741EBElement(const Rva001741EBElement &x) {
  rows[0].words[0]=x.rows[0].words[0];
  rows[0].words[1]=x.rows[0].words[1];
  rows[0].words[2]=x.rows[0].words[2];
  rows[0].words[3]=x.rows[0].words[3];
  rows[1].words[0]=x.rows[1].words[0];
  rows[1].words[1]=x.rows[1].words[1];
  rows[1].words[2]=x.rows[1].words[2];
  rows[1].words[3]=x.rows[1].words[3];
  rows[2].words[0]=x.rows[2].words[0];
  rows[2].words[1]=x.rows[2].words[1];
  rows[2].words[2]=x.rows[2].words[2];
  rows[2].words[3]=x.rows[2].words[3];
 }
};
namespace _STL {
template <> void _Construct<Rva001741EBElement, Rva001741EBElement>(Rva001741EBElement *p, const Rva001741EBElement &x) { new(p) Rva001741EBElement(x); }
}
template class _STL::vector<Rva001741EBElement, _STL::allocator<Rva001741EBElement> >;
