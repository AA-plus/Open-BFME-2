// cl: /MD
// stlport
// ??0Rva002AC3BE@@QAE@PAX@Z @0x002AC3BE 34B: holder ctor storing void* at +0
// then default vector<BfmeE16> at +4 via rowed Vector_base 0x00211E58 with
// one-byte stack allocator temp at [ebp+0xb] and zeroing byte at +0x14.
// Size 0x18 proven by new 0x18 at caller 0x002ACD09; int at +0x10 left uninit
// and set by caller 0x002ACD09 with second arg; second caller 0x002B1C55.
// Prev SubsystemNameGetters2 no flags next PlayerGetRelationship /O1 /MD.
// Honest address-derived name; BfmeE16 is the 16B stand-in from
// stlport_vector_e16_o1.cpp following Rva00506A34 30B precedent plus 4B mov.
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
namespace _STL { template <> vector<BfmeE16,_STL::allocator<BfmeE16> >::~vector(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}
class Rva002AC3BE
{
public:
	Rva002AC3BE(void *a);
private:
	void *m_00;
	_STL::vector<BfmeE16> m_04;
	int m_10;
	bool m_14;
};

Rva002AC3BE::Rva002AC3BE(void *a)
	: m_00(a)
{
	m_14 = false;
}
