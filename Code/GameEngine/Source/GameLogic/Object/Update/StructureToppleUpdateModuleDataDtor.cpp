// cl: /GX /DNDEBUG /MD /D_STLP_USE_MALLOC
// stlport
// ??1StructureToppleUpdateModuleData@@UAE@XZ @0x00257C88 48B
// ModuleData dtor: tears down the vector at +0x08 through the rowed
// vector<BfmeStringHeadRecord160> dtor at 0x00257583, then restores the
// Snapshot base vtable 0x00BBB554. Empty derived body with EH state 0
// (EH prolog 0xB71C4A, no base call since Snapshot dtor is inline).
// Evidence: unlock lane; caller is slot-0 ??_G at 0x00257C6C;
// layout via prev friend_new (same class) plus member via 0x00257583.
#include <vector>
struct BfmeStringHeadRecord160 { public: ~BfmeStringHeadRecord160(); };
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
class __declspec(novtable) StructureToppleUpdateModuleData : public Snapshot
{
public:
	virtual ~StructureToppleUpdateModuleData();
private:
	int m_unused04;
	_STL::vector<BfmeStringHeadRecord160, _STL::allocator<BfmeStringHeadRecord160> > m_vec08;
};
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline StructureToppleUpdateModuleData::~StructureToppleUpdateModuleData()
{
}

// ?bfmeAnchorStructureToppleUpdateModuleDataDtor absent-from-retail
void bfmeAnchorStructureToppleUpdateModuleDataDtor(StructureToppleUpdateModuleData *p)
{
	p->StructureToppleUpdateModuleData::~StructureToppleUpdateModuleData();
}
