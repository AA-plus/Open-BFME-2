// ?Rva001363A1Get@@YAPBDI@Z @0x001363A1 43B
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Unlock map unsigned-to-ptr lookup plus empty-string fallback plus data-plus-8. Evidence: callee 0x00357180 rowed map find; globals 0x00DF29B4 no name yet 0x007BAC1C empty in use; callers 0x0014C85F 0x0014CBB0 unclaimed; prev 0x0013623C next 0x001363CC.
#include <map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}

extern _STL::map<unsigned int, void *> g_00DF29B4;

const char *Rva001363A1Get(unsigned int key)
{
	_STL::map<unsigned int, void *>::iterator it = g_00DF29B4.find(key);
	if (it == g_00DF29B4.end())
		return 0;
	void *p = it->second;
	return p != 0 ? (const char *)p + 8 : "";
}
