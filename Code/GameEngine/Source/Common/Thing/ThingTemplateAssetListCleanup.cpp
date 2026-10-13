// cl: /O1 /G7 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native ThingTemplate's two 20-byte AssetList members at +3C4/+3D8:
// constructor callback 0006D577; destructor callback 0006C94B.
// Existing AssetList ctor and operator<< prove pointer set, four-byte pad,
// and changed flag. Destruction must fold with the complete native tree.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct Rva001408C0Target;
typedef Rva001408C0Target *AssetKey;
typedef _STL::set<AssetKey,_STL::less<AssetKey>,_STL::allocator<AssetKey> > AssetSet;
typedef _STL::_Rb_tree<AssetKey,AssetKey,_STL::_Identity<AssetKey>,_STL::less<AssetKey>,_STL::allocator<AssetKey> > AssetTree;
// The enclosing AssetList destructor is already emitted by GameLogicInit.
template AssetTree::~_Rb_tree();
