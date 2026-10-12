// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 public upper_bound wrapper. Native 4235B2..4235CD forwards
// four arguments and a null distance pointer to the rowed integer helper
// at 423098. Its comparator reads formation slot ObjectIDs; the former
// byte-element lower_bound identity did not describe this call contract.
#include <algorithm>
class Rva00422CA8 { public: bool operator()(int,int) const; };
namespace _STL {
// Bind the kept, independently verified helper rather than emit a new copy.
template<> int* __upper_bound<int*,int,Rva00422CA8,int>(int*,int*,const int&,Rva00422CA8,int*);
}
template int* _STL::upper_bound<int*,int,Rva00422CA8>(int*,int*,const int&,Rva00422CA8);
