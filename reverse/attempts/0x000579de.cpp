// ??1?$deque@URva00056DEBElement@@V?$allocator@URva00056DEBElement@@@_STL@@@_STL@@QAE@XZ
// partial score=0.99 date=2026-10-13
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
struct Rva00056DEBElement { char bytes[1]; ~Rva00056DEBElement(); bool operator<(const Rva00056DEBElement&)const; bool operator==(const Rva00056DEBElement&)const; };
namespace _STL { template<> _Deque_base<Rva00056DEBElement, allocator<Rva00056DEBElement> >::~_Deque_base(); }
template _STL::deque<Rva00056DEBElement>::~deque();
