// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??A?$map@VAsciiString@@UTreeHintPayload003012F0@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload003012F0@@@_STL@@@4@@_STL@@QAEAAUTreeHintPayload003012F0@@ABVAsciiString@@@Z @0x0030251A 121B
// map operator[] over AsciiString key with twelve-byte mapped value; same shape as 0x00218AA4 but with 3-dword payload (no zeroing)
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#include <map>
#include "ascii_string.h"

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
bool operator<(const AsciiString &, const AsciiString &);
struct TreeHintPayload003012F0 {
    unsigned int a, b, c;
    TreeHintPayload003012F0() {}
    TreeHintPayload003012F0(const TreeHintPayload003012F0 &other)
        : a(other.a), b(other.b), c(other.c) {}
};
typedef _STL::pair<const AsciiString, TreeHintPayload003012F0> TreeHintPair003012F0;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair003012F0, _STL::_Select1st<TreeHintPair003012F0>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair003012F0> > TreeHint003012F0;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
typedef _STL::map<AsciiString,TreeHintPayload003012F0,_STL::less<AsciiString >,_STL::allocator<TreeHintPair003012F0> > MapInsert0030251A;
template TreeHintPayload003012F0 &MapInsert0030251A::operator[](const AsciiString &);
// bfme link decl-only begin
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload003012F0> > * _Rb_tree<AsciiString,_STL::pair<AsciiString const,TreeHintPayload003012F0>,_STL::_Select1st<_STL::pair<AsciiString const,TreeHintPayload003012F0> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,TreeHintPayload003012F0> > >::_M_create_node(_STL::pair<AsciiString const,TreeHintPayload003012F0> const &); }
// bfme link decl-only end
