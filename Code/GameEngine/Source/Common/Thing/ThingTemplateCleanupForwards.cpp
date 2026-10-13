// cl: /O1 /MD /DNDEBUG
// Native five-byte tail forwards 0033CF2F->0033CD02 and0033D3B3->0033D00A.
// ThingTemplate ctor EH cleanup references establish the lifetime use.
// Constructor45-state EH identifies ModuleInfo and the per-unit FX map wrapper.
// Rename the existing owners; member destruction preserves their native tails.
class AsciiString;
struct BfmeStringRecord002CF4C6;
struct NoCaseTreeValue4;
struct BfmeStringNoCaseLess;
namespace _STL {
template<class T> class allocator;
template<class A,class B> struct pair;
template<class T> struct _Select1st;
template<class T,class A> class vector { void *words[3]; public: ~vector(); };
template<class K,class V,class S,class C,class A> class _Rb_tree { void *words[3]; public: ~_Rb_tree(); };
}
typedef _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> > StringRecordVector;
typedef _STL::pair<const AsciiString,NoCaseTreeValue4> NoCaseValue;
typedef _STL::_Rb_tree<AsciiString,NoCaseValue,_STL::_Select1st<NoCaseValue>,BfmeStringNoCaseLess,_STL::allocator<NoCaseValue> > NoCaseTree;
struct ModuleInfo { StringRecordVector records; ~ModuleInfo(); };
ModuleInfo::~ModuleInfo() {}
struct NoCaseMapView { NoCaseTree tree; ~NoCaseMapView(); };
NoCaseMapView::~NoCaseMapView() {}
