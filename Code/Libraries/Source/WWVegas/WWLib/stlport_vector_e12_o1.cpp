// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct BfmeE12 { float x, y, z; };
namespace _STL { template<> vector<BfmeE12> &vector<BfmeE12>::operator=(const vector<BfmeE12> &); }

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?swap@SidesInfoStringVector@@QAEXAAV1@@Z=?swap@?$vector@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@QAEXAAV12@@Z")
// ?bfmeEmitstlport_vector_e12_o1_copy@@YAXPAUBfmeE12@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_copy(const BfmeE12 *p)
{
	_STL::__copy(p, p, (BfmeE12 *)0, _STL::random_access_iterator_tag(), (int *)0);
}
// ?bfmeEmitstlport_vector_e12_o1_copy_backward@@YAXPAUBfmeE12@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_copy_backward(BfmeE12 *p)
{
	_STL::__copy_backward(p, p, p, _STL::random_access_iterator_tag(), (int *)0);
}
// ?bfmeEmitstlport_vector_e12_o1_uninitialized_copy@@YAXPAUBfmeE12@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_uninitialized_copy(const BfmeE12 *p)
{
	_STL::__uninitialized_copy(p, p, (BfmeE12 *)0, _STL::__false_type());
}
// ?bfmeEmitstlport_vector_e12_o1_uninitialized_fill_n@@YAXPAUBfmeE12@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_uninitialized_fill_n(const BfmeE12 *p)
{
	_STL::__uninitialized_fill_n((BfmeE12 *)0, 0u, *p, _STL::__false_type());
}
// ?bfmeEmitstlport_vector_e12_o1_fill@@YAXPAUBfmeE12@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_fill(const BfmeE12 *p)
{
	_STL::fill((BfmeE12 *)0, (BfmeE12 *)0, *p);
}

// ?bfmeEmitstlport_vector_e12_o1_size@@YAXPBUBfmeE12@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_size(const _STL::vector<BfmeE12,_STL::allocator<BfmeE12> > *p)
{
	volatile unsigned int s = p->size();
	(void)s;
}
// ?bfmeEmitstlport_vector_e12_o1_swap@@YAXPAV?$vector@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_swap(_STL::vector<BfmeE12,_STL::allocator<BfmeE12> > *p)
{
	p->swap(*p);
}
// ?bfmeEmitstlport_vector_e12_o1_pop_back@@YAXPAV?$vector@UBfmeE12@@V?$allocator@UBfmeE12@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_pop_back(_STL::vector<BfmeE12,_STL::allocator<BfmeE12> > *p)
{
	p->pop_back();
}
// ?bfmeEmitstlport_vector_e12_o1_vector_base@@YAXXZ present-unmatched
void bfmeEmitstlport_vector_e12_o1_vector_base()
{
	void *buf = 0;
	new (buf) _STL::_Vector_base<BfmeE12,_STL::allocator<BfmeE12> >(_STL::allocator<BfmeE12>());
}
// ?bfmeEmitstlport_vector_e12_o1_copy_backward_ptrs@@YAXPAUBfmeE12@@@Z present-unmatched
void bfmeEmitstlport_vector_e12_o1_copy_backward_ptrs(BfmeE12 *p)
{
	_STL::__copy_backward_ptrs(p, p, p, _STL::__false_type());
}
