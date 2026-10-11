// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva0022CA95@@MAE@XZ, retail 0x002149AA..0x00214A6E (196 bytes, EH): the
// AttributeModifier store's destructor (constructor 0x0022CA95, table
// 0x00BE5348, slot-0 scalar deleting destructor 0x00214A6E; its slots 4 and
// 5 are the RIF reload notices in ReloadIniFileNotices.cpp). It deletes
// every entry of its two pointer vectors at +0xC and +0x18 by index (entry
// destructor rowed 0x004043FF); then both vectors' storage goes to GameFree
// (unwind copies 0x0007FAB3) and SubsystemInterface dies last.
#include <vector>

void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> inline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
}

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	int m_04;
	int m_08;
};

class Rva002146F7
{
public:
	~Rva002146F7();
};

class Rva0022CA95 : public SubsystemInterface
{
public:
	Rva0022CA95();
protected:
	virtual ~Rva0022CA95();
private:
	_STL::vector<void *> m_first;		// +0x0C
	_STL::vector<void *> m_second;		// +0x18
};

Rva0022CA95::~Rva0022CA95()
{
	unsigned int i;
	for (i = 0; i < m_first.size(); ++i)
		delete static_cast<Rva002146F7 *>(m_first[i]);
	for (i = 0; i < m_second.size(); ++i)
		delete static_cast<Rva002146F7 *>(m_second[i]);
}
