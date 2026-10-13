// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?bfmeForgetCC@BfmeRegistryCC@@QAEXPAX@Z @0x000480ED 47B. Vector find-and-erase
// on vector<CreateAHeroData*> at this+0x2a4 via rowed find 0x0020E873 and rowed
// voidptr erase 0x001FF51F. Evidence: same shape as Rva004DFB55HeroRemover
// (find+erase, frameless, void return) with larger disp32 offsets (+6B);
// caller 0x00072838 in BfmeOwnerCC dtor passes this; pin names BfmeRegistryCC.
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

class CreateAHeroData;

class BfmeRegistryCC
{
private:
	char m_pad[0x2a4];
	_STL::vector<CreateAHeroData *> m_vec2a4;
public:
	void bfmeForgetCC(void *owner);
};

void BfmeRegistryCC::bfmeForgetCC(void *owner)
{
	_STL::vector<CreateAHeroData *>::iterator it =
		_STL::find(m_vec2a4.begin(), m_vec2a4.end(), (CreateAHeroData * &)owner);
	if (it != m_vec2a4.end()) {
		((_STL::vector<void *> *)&m_vec2a4)->erase((void **)it);
	}
}
