// cl: /O1 /MD /DNDEBUG
// Native five-byte tail forwards 0033CF2F->0033CD02 and0033D3B3->0033D00A.
// ThingTemplate ctor EH cleanup references establish the lifetime use.
// Enclosing member names remain unknown. Use the existing concrete STL
// providers; these are callable forwards, not alternate destructor identities.
class AsciiString;
struct BfmeStringRecord002CF4C6;
struct NoCaseTreeValue4;
struct BfmeStringNoCaseLess;
namespace _STL {
template<class T> class allocator;
template<class A,class B> struct pair;
template<class T> struct _Select1st;
template<class T,class A> class vector { public: ~vector(); };
template<class K,class V,class S,class C,class A> class _Rb_tree { public: ~_Rb_tree(); };
}
typedef _STL::vector<BfmeStringRecord002CF4C6,_STL::allocator<BfmeStringRecord002CF4C6> > StringRecordVector;
typedef _STL::pair<const AsciiString,NoCaseTreeValue4> NoCaseValue;
typedef _STL::_Rb_tree<AsciiString,NoCaseValue,_STL::_Select1st<NoCaseValue>,BfmeStringNoCaseLess,_STL::allocator<NoCaseValue> > NoCaseTree;
struct Rva0033CF2FCleanupForward { void cleanup(); };
void Rva0033CF2FCleanupForward::cleanup()
{
 reinterpret_cast<StringRecordVector *>(this)->~StringRecordVector();
}
struct Rva0033D3B3CleanupForward { void cleanup(); };
void Rva0033D3B3CleanupForward::cleanup()
{
 reinterpret_cast<NoCaseTree *>(this)->~NoCaseTree();
}
