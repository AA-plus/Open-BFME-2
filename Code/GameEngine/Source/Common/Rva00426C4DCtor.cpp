// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0Rva00426C4D@@QAE@XZ @0x00426C4D 28B evidence: stores vtable g_00C3C458 at +0 plus vector BfmeE16 at +4 via rowed Vector_base ctor 0x211E58; callers 0x426CEB 0x426D3F prove 0x10-byte class with new 0x10 plus initFromINI wrapper 0x42666E
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class Rva00426C4D
{
public:
	Rva00426C4D();
	virtual void s00();
private:
	_STL::vector<BfmeE16> m_04;
};

Rva00426C4D::Rva00426C4D()
{
}
