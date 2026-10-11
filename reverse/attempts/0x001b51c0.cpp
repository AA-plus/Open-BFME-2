// ?rva001B51C0@SubsystemInterfaceList@@QAEXXZ
// partial score=0.99 date=2026-10-11
// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
//
// ??1SubsystemInterfaceList@@QAE@XZ, retail 0x001B5207, 95 bytes (EH).
// WorldBuilder 0x00A75980 names it (SubsystemInterface.cpp, assert at line
// 326). After the unrowed member 0x001B51C0 (pinned under an address name;
// WB calls it from the same spot) the three POD vectors at +0x00, +0x0C and
// +0x18 free their buffers (0x00030830) in reverse member order, the same
// tail as the rowed record destructor 0x00079554 (Rva00079554RecordDtor.cpp).
// Element types are unrecovered.
#include <vector>

// The registered entries: the subsystem and the owned object that is
// destroyed through its slot 0 (flag 0) and operator delete.
struct Rva001B51C0Object
{
	virtual void *destroy(unsigned flags);
};
struct BfmePod8
{
	void *m_first;
	Rva001B51C0Object *m_second;
};

class SubsystemInterfaceList
{
public:
	~SubsystemInterfaceList();
	void rva001B51C0();
private:
	_STL::vector<BfmePod8> m_00;
	_STL::vector<int> m_0C;
	_STL::vector<int> m_18;
	int m_24;
};

SubsystemInterfaceList::~SubsystemInterfaceList()
{
	rva001B51C0();
}

// ?rva001B51C0@SubsystemInterfaceList@@QAEXXZ, retail 0x001B51C0 (71 bytes):
// the member the destructor runs first (WorldBuilder 0x00A758D0, unnamed).
// It walks the +0x00 entries from the back, destroys each owned object and
// clears the entry, then erases the whole vector (rowed BfmePod8 erase
// 0x003FA4DB) and clears the +0x24 word. The name is a placeholder.
void SubsystemInterfaceList::rva001B51C0()
{
	int step = -1;
	for (BfmePod8 *it = m_00.end(); it != m_00.begin(); )
	{
		Rva001B51C0Object *object = it[-1].m_second;
		::operator delete(object ? object->destroy(0) : 0);
		BfmePod8 cleared;
		cleared.m_first = 0;
		cleared.m_second = 0;
		it += step;
		*it = cleared;
	}
	m_00.erase(m_00.begin(), m_00.end());
	m_24 = 0;
}
