// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00239A10@Rva00239A10@@QAEXPAX@Z @0x00239A10 48B.
// Linear find-erase over vector<void*> at +0xE8 via rowed erase 0x001FF51F.
// Same recipe as Rva00568F04::rva00568F04 at +0x58. Evidence: caller 0x00362E41
// in UNCLAIMED 0x00362E1C; neighbours 0x002399EB 0x00239A40; no VTABLE; no strings.
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void * * __copy_ptrs<void * *,void * *>(void * *,void * *,void * *,_STL::__true_type); }
namespace _STL { template <> void * * vector<void *,_STL::allocator<void *> >::erase(void * *); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

class Rva00239A10
{
public:
	void rva00239A10(void *item);

private:
	char _pad[0xe8];
	void **m_begin;
	void **m_end;
};

void Rva00239A10::rva00239A10(void *item)
{
	void **cur = m_begin;
	void **finish = m_end;
	for (; cur != finish; ++cur)
	{
		if (*cur == item)
		{
			((::_STL::vector<void *, _STL::allocator<void *> > *)(void *)((char *)this + 0xe8))->erase(cur);
			return;
		}
	}
}
