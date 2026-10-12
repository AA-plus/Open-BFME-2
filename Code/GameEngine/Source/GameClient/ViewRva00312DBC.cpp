// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00312DBC@View@@UAEXXZ, retail 0x00312DBC (14 bytes), slot 3 of the view tables
// (W3DView 0x007C7514): empties the view's 184-byte record vector at +0x2C through the rowed
// erase 0x00312C44. The slot's name is not recovered.
#include <vector>

struct BfmeStringHeadRecord184
{
	char m_bytes[184];
};

namespace _STL {
template <> BfmeStringHeadRecord184 *vector<BfmeStringHeadRecord184>::erase(BfmeStringHeadRecord184 *first, BfmeStringHeadRecord184 *last);
}

class View
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void rva00312DBC();
private:
	unsigned char m_pad04[0x2C - 4];
	_STL::vector<BfmeStringHeadRecord184> m_records;		// +0x2C
};

void View::rva00312DBC()
{
	m_records.clear();
}
