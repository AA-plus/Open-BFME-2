// ??0Rva001F206E@@QAE@ABU0@@Z
// partial score=0.7481174520483069 date=2026-10-13
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
struct Rva004598CCElement;
namespace _STL {
template<> allocator<unsigned int> vector<unsigned int>::get_allocator() const;
template<> Rva004598CCElement** __copy_aux<Rva004598CCElement**,Rva004598CCElement**>(Rva004598CCElement**,Rva004598CCElement**,Rva004598CCElement**,__true_type);
}
struct Rva001F20D6 {
 Rva001F20D6(unsigned int,const _STL::allocator<int>&);
 ~Rva001F20D6();
 Rva004598CCElement **first,**last,**end;
};
struct Rva001F206E: Rva001F20D6 {
 Rva001F206E(const Rva001F206E &);
};
Rva001F206E::Rva001F206E(const Rva001F206E&r):Rva001F20D6(r.last-r.first,*reinterpret_cast<const _STL::allocator<int>*>(&reinterpret_cast<const _STL::vector<unsigned int>*>(&r)->get_allocator())) {
 
 typedef Rva004598CCElement**(*Copy)(Rva004598CCElement**,Rva004598CCElement**,Rva004598CCElement**,const _STL::__true_type&);
 typedef Rva004598CCElement**(*CopyValue)(Rva004598CCElement**,Rva004598CCElement**,Rva004598CCElement**,_STL::__true_type);
 last=reinterpret_cast<Copy>(static_cast<CopyValue>(&_STL::__copy_aux<Rva004598CCElement**,Rva004598CCElement**>))(r.first,r.last,first,_STL::__true_type());
}
