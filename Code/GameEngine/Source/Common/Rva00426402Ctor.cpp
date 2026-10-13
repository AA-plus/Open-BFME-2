// cl: /Oy- /MD
// stlport
// ??0Rva00426402@@QAE@XZ @0x00426402 59B evidence: baseConstruct 0x001B4E63 plus vtable 0x0083C350 plus 3x Vector_base 0x00211E58 at +0x0C +0x18 +0x24 plus caller 0x0022EF95
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

class BFME2NativeNetwork
{
public:
};

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class __declspec(novtable) Rva00426402Base
{
public:
	Rva00426402Base() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual void unused();
	char m_flag;
	int m_value;
};

class Rva00426402 : public Rva00426402Base
{
public:
	Rva00426402();
protected:
	virtual ~Rva00426402();
private:
	_STL::vector<BfmeE16> m_vec0C;
	_STL::vector<BfmeE16> m_vec18;
	_STL::vector<BfmeE16> m_vec24;
};

Rva00426402::Rva00426402()
	: m_vec0C()
	, m_vec18()
	, m_vec24()
{
}
