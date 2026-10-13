// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert_unique@?$_Rb_tree@UBfmeStringRecord004D05B8@@U1@U?$_Identity@UBfmeStringRecord004D05B8@@@_STL@@U?$less@UBfmeStringRecord004D05B8@@@3@V?$allocator@UBfmeStringRecord004D05B8@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@UBfmeStringRecord004D05B8@@U?$_Nonconst_traits@UBfmeStringRecord004D05B8@@@_STL@@@2@U342@ABUBfmeStringRecord004D05B8@@@Z @ 0x004D2209 310B: hint insert_unique for WORD-key set
// calls rowed 0x004D2050 _M_insert and rowed 0x004D20DA insert_unique plus rowed increment/decrement.
// Evidence: chain packet calls 0x004D2050 now resolved; same 310B size as hint 0x004D1F1A; ret 0xc hidden iterator.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

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
struct BfmeStringRecord004D05B8 { unsigned short m_key; unsigned char m_pad[6]; };
inline bool operator<(const BfmeStringRecord004D05B8 &x, const BfmeStringRecord004D05B8 &y) { return x.m_key < y.m_key; }
typedef _STL::_Rb_tree<BfmeStringRecord004D05B8, BfmeStringRecord004D05B8, _STL::_Identity<BfmeStringRecord004D05B8>, _STL::less<BfmeStringRecord004D05B8>, _STL::allocator<BfmeStringRecord004D05B8> > UBfmeStringRecord004D05B8SetTree;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
template UBfmeStringRecord004D05B8SetTree::iterator UBfmeStringRecord004D05B8SetTree::insert_unique(UBfmeStringRecord004D05B8SetTree::iterator, const UBfmeStringRecord004D05B8SetTree::value_type &);
// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeStringRecord004D05B8,BfmeStringRecord004D05B8>(BfmeStringRecord004D05B8 *,BfmeStringRecord004D05B8 const &); }
namespace _STL { template <> _STL::_Rb_tree_node<BfmeStringRecord004D05B8> * _Rb_tree<BfmeStringRecord004D05B8,BfmeStringRecord004D05B8,_STL::_Identity<BfmeStringRecord004D05B8>,_STL::less<BfmeStringRecord004D05B8>,_STL::allocator<BfmeStringRecord004D05B8> >::_M_create_node(BfmeStringRecord004D05B8 const &); }
// bfme link decl-only end
