// cl: /MD
// stlport
// ??0Rva00524415@@QAE@XZ @0x00524415 33B
// Default ctor of two BfmeE16 vectors at +0 and +0xc via rowed _Vector_base
// 0x00211E58 with dummy allocator. Unlocks 5 callers including 0x002D2C34.
// Evidence: lea [ebp-1] push mov esi ecx call then lea ecx [esi+0xc] call.
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
namespace _STL { template <> vector<BfmeE16,_STL::allocator<BfmeE16> >::~vector(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}
struct Rva00524415
{
	_STL::vector<BfmeE16> m_00;
	_STL::vector<BfmeE16> m_0c;
	Rva00524415();
};
Rva00524415::Rva00524415()
{
}
