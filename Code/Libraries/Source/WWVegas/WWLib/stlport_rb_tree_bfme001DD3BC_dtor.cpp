// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$_Rb_tree@UBfmeRecord001DD3BC@@U1@U?$_Identity@UBfmeRecord001DD3BC@@@_STL@@U?$less@UBfmeRecord001DD3BC@@@3@V?$allocator@UBfmeRecord001DD3BC@@@3@@_STL@@QAE@XZ @0x001DDB8E 56B EH dtor calls clear 0x001DD9F3 then header free 0x00030830.
// Evidence: chain lane all callees rowed; same 56B shape as 0x00357C6A; set-tree identity via create_node row.
#include <map>

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
struct BfmeRecord001DD3BC {
	unsigned char m_data[8];
};
bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b);
typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;
template BfmeRecord001DD3BCSetTree::~_Rb_tree();
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<BfmeRecord001DD3BC>(BfmeRecord001DD3BC *); }
namespace _STL { template <> void _Rb_tree<BfmeRecord001DD3BC,BfmeRecord001DD3BC,_STL::_Identity<BfmeRecord001DD3BC>,_STL::less<BfmeRecord001DD3BC>,_STL::allocator<BfmeRecord001DD3BC> >::_M_erase(_STL::_Rb_tree_node<BfmeRecord001DD3BC> *); }
// bfme link decl-only end
