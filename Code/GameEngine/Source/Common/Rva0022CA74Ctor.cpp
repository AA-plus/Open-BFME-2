// cl: /MD
// stlport
// ??0Rva0022CA74@@QAE@XZ @0x0022CA74 33B
// Derived ctor: baseConstruct via inlined base then vtable 0xBE2704 then
// BfmeE16 Vector_base at +0xC. Same 33B shape as rowed ??0Rva00421242 at
// 0x00421242 (push ecx push esi mov esi ecx call baseConstruct lea eax
// [esp+7] push eax lea ecx [esi+0xC] mov [esi] vtable call Vector_base).
// Evidence: leaf packet calls rowed baseConstruct 0x001B4E63 and rowed
// Vector_base 0x00211E58; vtable store 0xBE2704; caller at 0x0022EA0A.
#include <vector>

struct BfmeE16 { float x, y, z, w; };
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

class __declspec(novtable) Rva0022CA74Base
{
public:
	Rva0022CA74Base() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual void unused();
	char m_flag;
	int m_value;
};

class Rva0022CA74 : public Rva0022CA74Base
{
public:
	Rva0022CA74();
protected:
	virtual ~Rva0022CA74();
private:
	_STL::vector<BfmeE16> m_vec;
};

Rva0022CA74::Rva0022CA74()
: m_vec()
{
}
