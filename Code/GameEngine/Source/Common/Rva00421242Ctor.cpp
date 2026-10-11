// cl: /MD
// stlport
// ??0Rva00421242@@QAE@XZ @0x00421242 33B
// Derived ctor: baseConstruct via inlined base then vtable 0x0083BE00 then
// BfmeE16 Vector_base at +0xC. Retail is push ecx / push esi / mov esi,ecx /
// call baseConstruct / lea eax,[esp+7] / push eax / lea ecx,[esi+0xC] /
// mov [esi],vtable / call Vector_base / mov eax,esi / pop / ret (33B).
// Evidence: leaf lane; callees baseConstruct 0x001B4E63 and Vector_base
// 0x00211E58 rowed; caller at 0x0022F0F0; neighbours share /O1.
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
	void baseConstruct();
};

class __declspec(novtable) Rva00421242Base
{
public:
	Rva00421242Base() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual void unused();
	char m_flag;
	int m_value;
};

class Rva00421242 : public Rva00421242Base
{
public:
	Rva00421242();
protected:
	virtual ~Rva00421242();
private:
	_STL::vector<BfmeE16> m_vec;
};
Rva00421242::Rva00421242()
: m_vec()
{
}
