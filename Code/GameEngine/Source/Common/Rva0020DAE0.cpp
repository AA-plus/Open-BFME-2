// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0020DAE0@@YAXPAX@Z 0x0020DAE0 41B remove ptr from global vector via erase
// Evidence: retail loads begin end from g_00DFE1AC g_00DFE1B0 then calls rowed vector voidptr erase 0x001FF51F; callers 0x00285766 0x00286FC6 0x004ABFCF use cdecl pop cleanup
#include <vector>
// Suppress this TU's non-retail vector<void*> begin/end copies (family2-LK3 rows 6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

extern _STL::vector<void *> g_00DFE1AC;

void __cdecl Rva0020DAE0(void *p)
{
	void **begin = *(void **volatile *)&g_00DFE1AC;
	void **end = *(void **volatile *)((char *)&g_00DFE1AC + 4);
	for (void **it = begin; it != end; ++it) {
		if (*it == p) {
			g_00DFE1AC.erase(it);
			return;
		}
	}
}
