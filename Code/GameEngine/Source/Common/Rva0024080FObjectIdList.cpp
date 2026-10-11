// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfmelist /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <list>

// Declaration-only: retail has one list<int>::insert (rowed in stlport_list_int_insert.cpp, node creation out of line);
// this unit calls it rather than emitting a copy with the node creation inlined.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::insert(list<int, allocator<int> >::iterator, const int &);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// ?Rva0024080FAdd@@YAXPAXPAV?$list@HV?$allocator@H@_STL@@@_STL@@@Z, RVA 0x0024080F, 34 bytes.
// Address-based callback; retail tests two pointer arguments, reads an integer at first-argument offset 0x74, and appends it to the second argument's list<int>. Stored as a callback at 0x002487F0.
void __cdecl Rva0024080FAdd(void *object, _STL::list<int> *ids)
{
	if (object == 0 || ids == 0)
		return;
	int id = *(int *)((char *)object + 0x74);
	ids->push_back(id);
}
