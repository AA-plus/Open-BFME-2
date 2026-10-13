// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva00426612@Rva00426612@@QAEXPAVCreateAHeroData@@@Z, retail 0x00426612, 76 bytes.
// Move-one registry shuffle: null arg returns; rowed _STL::find 0x0020E873
// over the +0x0C/+0x10 pointer range; miss (== end) returns; hit goes through
// rowed vector<void*>::erase 0x001FF51F, sets byte +0x18C on the item, then
// rowed vector<ModuleData>::push_back 0x004DFCB0 into the +0x18 vector.
// Evidence: callees rowed; caller 0x004DCB6F unclaimed; layout from pushes
// (begin +0x0C, end +0x10, second vector +0x18); precedent
// GateOpenBehaviorListRva004E908C.cpp for the void-pointer erase cast.
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
#include <algorithm>
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

class CreateAHeroData
{
public:
	char m_pad[0x18C];
	unsigned char m_18C;
};

class ModuleData;

class Rva00426612
{
public:
	void rva00426612(CreateAHeroData *item);
private:
	char m_pad00[0x0C];
	CreateAHeroData **m_begin0C;
	CreateAHeroData **m_end10;
	void *m_cap14;
	const ModuleData **m_beg18;
	const ModuleData **m_end1C;
	const ModuleData **m_cap20;
};

void Rva00426612::rva00426612(CreateAHeroData *item)
{
	if (item == 0)
		return;
	CreateAHeroData **found = _STL::find(m_begin0C, m_end10, item);
	if (found == m_end10)
		return;
	((_STL::vector<void *, _STL::allocator<void *> > *)&m_begin0C)->erase((void **)found);
	item->m_18C = 1;
	((_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *)&m_beg18)->push_back(*(const ModuleData * const *)&item);
}
