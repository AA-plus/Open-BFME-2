// cl: /MD
// stlport
// ??0Rva00577F77@@QAE@PAXH@Z @0x00577F77 48B: ctor calls base 0x005C6D4D then stores args to +0x3c/+0x40 then sets vtable g_00C6EA28 then constructs vector<BfmeE16> at +0x44. Evidence: unlock packet calls pin-only base plus rowed Vector_base plus caller 0x005782F4 pushes parent plus int.
#include <vector>
class Rva005C6D4D
{
public:
	virtual ~Rva005C6D4D();
	Rva005C6D4D();
};

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

extern const void *const g_00C6EA28[];

class Rva00577F77 : public Rva005C6D4D
{
public:
	Rva00577F77(void *p, int v);
	virtual ~Rva00577F77();
private:
	char _pad[0x38];
	void *m_3c;
	int m_40;
	_STL::vector<BfmeE16> m_44;
};

Rva00577F77::Rva00577F77(void *p, int v) : m_3c(p), m_40(v), m_44()
{
}
