// cl: /O1 /DNDEBUG /MD /EHsc
// Native005007AA..005007CF copies the 20-byte army record.
// The tree at +4 uses the actual whole165B copy provider at004FFFF9.
// Rva004FFFF9Element is that provider's existing opaque8B element spelling;
// this call-only view does not assert its original application identity.
namespace _STL {
template<class T> class allocator;
template<class T> struct less;
template<class T> struct _Identity;
template<class K,class V,class KeyOfValue,class C,class A> class _Rb_tree {
public:
 _Rb_tree(const _Rb_tree&);
 char header[12];
};
}
struct Rva004FFFF9Element;
typedef _STL::_Rb_tree<Rva004FFFF9Element,Rva004FFFF9Element,_STL::_Identity<Rva004FFFF9Element>,_STL::less<Rva004FFFF9Element>,_STL::allocator<Rva004FFFF9Element> > ArmyCopyTree;
struct Rva00501E3FElement {
 Rva00501E3FElement(const Rva00501E3FElement&);
 int m_00;
 ArmyCopyTree m_04;
 int m_10;
};
Rva00501E3FElement::Rva00501E3FElement(const Rva00501E3FElement& src)
 :m_00(src.m_00),m_04(src.m_04),m_10(src.m_10)
{}
