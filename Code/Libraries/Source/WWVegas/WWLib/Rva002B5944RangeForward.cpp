// cl: /O1 /EHsc /MD /D_CRTIMP=
// Reference-derived iterator forwarding shape from STLport4.5.3.
// Original template spelling is unknown. Input/output tokens are opaque pointers,
// not inferred game classes. Native calls and the existing matched callee fix behavior.
// The callee does not read iterator-metadata stack slots; direct canonical
// template binding preserves its existing provider and replaces the old alias.
struct Rva002B5944Input;
struct Rva002B5944Output;
class Rva002B2F97;
namespace _STL {
struct __false_type {};
template<class Input,class Output> Output __copy_backward_ptrs(Input,Input,Output,const __false_type &);
}

Rva002B5944Output* __cdecl Rva002B5944RangeForward(Rva002B5944Input*first,Rva002B5944Input*last,Rva002B5944Output*result)
{
    _STL::__false_type category;
    return reinterpret_cast<Rva002B5944Output*>(_STL::__copy_backward_ptrs(
        reinterpret_cast<Rva002B2F97*>(first),reinterpret_cast<Rva002B2F97*>(last),
        reinterpret_cast<Rva002B2F97*>(result),category));
}
