// cl: /MD
// stlport
// ??0Rva0059E511Data@@QAE@XZ @0x0059E499 32B: default ctor with vector at +4 and int zero at +0x10.
// Evidence: vtable 0x00C7102C, rowed _Vector_base<BfmeE16> 0x00211E58, caller 0x0059E531 in Rva0059E511Parse.
#include <vector>
struct BfmeE16 { float x; float y; float z; float w; };
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}
class Rva0059E511Data
{
public:
	Rva0059E511Data();
	virtual ~Rva0059E511Data();
private:
	_STL::vector<BfmeE16> m_04;
	int m_10;
};

Rva0059E511Data::Rva0059E511Data()
{
	m_10 = 0;
}
