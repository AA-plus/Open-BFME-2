// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0BfmeItemERF@@QAE@XZ @0x003F609E 42B evidence: leaf pin plus caller resize 0x003F700F plus rowed Vector-base 0x00211E58 twice plus members +0 +4 +0x10
#include <vector>

#include "../../../Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class BfmeItemERF
{
public:
	BfmeItemERF();

private:
	int m_0;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_04;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_10;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline BfmeItemERF::BfmeItemERF() : m_0(-2)
{
}

// ?bfmeAnchorBfmeItemERF absent-from-retail
void *bfmeAnchorBfmeItemERF(void *where)
{
	return new (where) BfmeItemERF();
}

