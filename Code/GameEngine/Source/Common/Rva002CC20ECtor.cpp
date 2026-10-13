// cl: /Oy- /MD
// stlport
// ??0Rva002CC20E@@QAE@XZ @0x002CC20E 47B evidence: baseConstruct 0x001B4E63 plus vtable 0x00C02114 plus 2x Vector_base 0x00211E58 at +0x0C +0x18 plus caller 0x0022EB76; same pattern as Rva00426402Ctor with 3 vectors.
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

class __declspec(novtable) Rva002CC20EBase
{
public:
    Rva002CC20EBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
    virtual void unused();
    char m_flag;
    int m_value;
};

extern const void *const g_00C02114[];
// Unused vtable extern documents retail VA 0x00C02114; the ctor's implicit
// vtable store is gate-filled like the Rva00426402 precedent.

class Rva002CC20E : public Rva002CC20EBase
{
public:
    Rva002CC20E();
protected:
    virtual ~Rva002CC20E();
private:
    _STL::vector<BfmeE16> m_vec0C;
    _STL::vector<BfmeE16> m_vec18;
};

Rva002CC20E::Rva002CC20E()
    : m_vec0C()
    , m_vec18()
{
}
