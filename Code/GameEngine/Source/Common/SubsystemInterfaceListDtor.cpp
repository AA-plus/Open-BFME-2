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

class SubsystemInterfaceList
{
public:
	~SubsystemInterfaceList();
	void rva001B51C0();
private:
	_STL::vector<int> m_00;
	_STL::vector<int> m_0C;
	_STL::vector<int> m_18;
};

SubsystemInterfaceList::~SubsystemInterfaceList()
{
	rva001B51C0();
}
