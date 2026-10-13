// cl: /O1 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_insert@?$_Rb_tree@UBfmeStringRecord00448113@@U1@U?$_Identity@UBfmeStringRecord00448113@@@_STL@@U?$less@UBfmeStringRecord00448113@@@3@V?$allocator@UBfmeStringRecord00448113@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@UBfmeStringRecord00448113@@U?$_Nonconst_traits@UBfmeStringRecord00448113@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABUBfmeStringRecord00448113@@0@Z @ 0x00448E64 (148B).
// Set _M_insert for BfmeStringRecord00448113 via insert_unique instantiation.
// Comparator is rowed free operator< at 0x48D3C. Same recipe as BfmePod20 insert.
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
struct BfmeStringRecord00448113 { public: unsigned char m_data[8]; };
bool operator<(const BfmeStringRecord00448113 &, const BfmeStringRecord00448113 &);
typedef _STL::_Rb_tree<BfmeStringRecord00448113, BfmeStringRecord00448113, _STL::_Identity<BfmeStringRecord00448113>, _STL::less<BfmeStringRecord00448113>, _STL::allocator<BfmeStringRecord00448113> > UBfmeStringRecord00448113SetTree;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
// ?insert_unique@?$_Rb_tree@UBfmeStringRecord00448113@@U1@U?$_Identity@UBfmeStringRecord00448113@@@_STL@@U?$less@UBfmeStringRecord00448113@@@3@V?$allocator@UBfmeStringRecord00448113@@@3@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@UBfmeStringRecord00448113@@U?$_Nonconst_traits@UBfmeStringRecord00448113@@@_STL@@@_STL@@_N@2@ABUBfmeStringRecord00448113@@@Z present-unmatched
template _STL::pair<UBfmeStringRecord00448113SetTree::iterator, bool> UBfmeStringRecord00448113SetTree::insert_unique(const UBfmeStringRecord00448113SetTree::value_type &);
// bfme link decl-only begin
namespace _STL { template <> void _Construct<BfmeStringRecord00448113,BfmeStringRecord00448113>(BfmeStringRecord00448113 *,BfmeStringRecord00448113 const &); }
namespace _STL { template <> _STL::_Rb_tree_node<BfmeStringRecord00448113> * _Rb_tree<BfmeStringRecord00448113,BfmeStringRecord00448113,_STL::_Identity<BfmeStringRecord00448113>,_STL::less<BfmeStringRecord00448113>,_STL::allocator<BfmeStringRecord00448113> >::_M_create_node(BfmeStringRecord00448113 const &); }
// bfme link decl-only end
