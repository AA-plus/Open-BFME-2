// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??A?$map@VAsciiString@@UTreeHintPayload00217DE3@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload00217DE3@@@_STL@@@4@@_STL@@QAEAAUTreeHintPayload00217DE3@@ABVAsciiString@@@Z @0x00218AA4 124B
// map operator[]; tries explicit default ctor for direct in-place zero
#include <stl/_prolog.h>
#include <stl/type_traits.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#undef _STLP_DEFAULT_CONSTRUCTED
#define _STLP_DEFAULT_CONSTRUCTED(_TTp) _TTp()
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
struct TreeHintPayload00217DE3 { int m_val; TreeHintPayload00217DE3() : m_val(0) {} TreeHintPayload00217DE3(const TreeHintPayload00217DE3 &o) : m_val(o.m_val) {} };
typedef _STL::pair<const AsciiString, TreeHintPayload00217DE3> TreeHintPair00217DE3;
typedef _STL::_Rb_tree<AsciiString, TreeHintPair00217DE3, _STL::_Select1st<TreeHintPair00217DE3>, _STL::less<AsciiString>, _STL::allocator<TreeHintPair00217DE3> > TreeHint00217DE3;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
typedef _STL::map<AsciiString,TreeHintPayload00217DE3,_STL::less<AsciiString >,_STL::allocator<TreeHintPair00217DE3> > MapInsert00218AA4;
template TreeHintPayload00217DE3 &MapInsert00218AA4::operator[](const AsciiString &);
// bfme link decl-only begin
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<AsciiString const,TreeHintPayload00217DE3> > * _Rb_tree<AsciiString,_STL::pair<AsciiString const,TreeHintPayload00217DE3>,_STL::_Select1st<_STL::pair<AsciiString const,TreeHintPayload00217DE3> >,_STL::less<AsciiString>,_STL::allocator<_STL::pair<AsciiString const,TreeHintPayload00217DE3> > >::_M_create_node(_STL::pair<AsciiString const,TreeHintPayload00217DE3> const &); }
// bfme link decl-only end
