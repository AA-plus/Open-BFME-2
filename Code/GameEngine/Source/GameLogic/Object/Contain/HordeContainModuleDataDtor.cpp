// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1HordeContainModuleData@@UAE@XZ, retail 0x00475942..0x00475BDD (667
// bytes, EH): table 0x00C457B0 (constructor 0x00475C9A in
// HordeContainModuleDataCtor.cpp, slot-0 scalar deleting destructor
// 0x00475E86). It deletes and empties its three owned-record vectors at
// +0x18C/+0x198/+0x1A4 (record destructors rowed 0x004703E0, 0x00469D86 and
// 0x00469DCE; range erase 0x0031BD55), clears the +0x1B4 list and the two
// name sets, empties the +0x1F4 and +0x218 string vectors, deletes and
// empties the +0x20C owned strings, empties the +0x224 string vector and
// ::deletes its +0x258 object. Retail's unwind map then destroys the
// members in reverse and TransportContainModuleData (rowed 0x004684F1). The
// sets' wrapper unwind copy is the 5-byte thunk 0x00073116 (set destructor
// 0x000730DE); the list's is 0x00200667. Members past the cited offsets
// keep the constructor view's placeholders.
#include <list>
#include <vector>
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

struct Rva004FA1FObserver;
namespace _STL {
template<> void _List_base<Rva004FA1FObserver *, allocator<Rva004FA1FObserver *> >::clear();
template<> _List_base<Rva004FA1FObserver *, allocator<Rva004FA1FObserver *> >::~_List_base();
template<> vector<AsciiString, allocator<AsciiString> >::~vector();
template<> vector<AsciiString, allocator<AsciiString> >::iterator vector<AsciiString, allocator<AsciiString> >::erase(iterator first, iterator last);
template<> inline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> vector<void *>::iterator vector<void *>::erase(iterator first, iterator last);
}

class TransportContainModuleData
{
public:
	virtual ~TransportContainModuleData();
private:
	unsigned char m_pad04[0x18C - 4];
};

class Rva004703E0 { public: ~Rva004703E0(); };
class Rva00469D86 { public: ~Rva00469D86(); };
class Rva0046AA69Record { public: ~Rva0046AA69Record(); };

struct Rva00200667
{
	~Rva00200667() {}
	_STL::list<Rva004FA1FObserver *> m_list;
};

class Rva00072FE6
{
public:
	~Rva00072FE6();
	void rva00072FE6();
private:
	unsigned char m_data[0xC];
};

struct Rva00073116
{
	~Rva00073116() {}
	Rva00072FE6 m_set;
};

class HordeContainOwned
{
public:
	virtual ~HordeContainOwned();
};

class HordeContainModuleData : public TransportContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();
private:
	_STL::vector<void *> m_vec18C;
	_STL::vector<void *> m_vec198;
	_STL::vector<void *> m_vec1A4;
	AsciiString m_s1B0;
	Rva00200667 m_list1B4;
	Rva00073116 m_set1B8;
	Rva00073116 m_set1C4;
	unsigned char m_pad1D0[0x1F4 - 0x1D0];
	_STL::vector<AsciiString> m_vec1F4;
	unsigned char m_pad200[0x20C - 0x200];
	_STL::vector<void *> m_vec20C;
	_STL::vector<AsciiString> m_vec218;
	_STL::vector<AsciiString> m_vec224;
	unsigned char m_pad230[0x23C - 0x230];
	AsciiString m_s23C;
	unsigned char m_pad240[0x258 - 0x240];
	HordeContainOwned *m_258;
	unsigned char m_pad25C[0x274 - 0x25C];
};

HordeContainModuleData::~HordeContainModuleData()
{
	unsigned int i;
	for (i = 0; i < m_vec18C.size(); ++i)
		delete static_cast<Rva004703E0 *>(m_vec18C[i]);
	m_vec18C.clear();
	for (i = 0; i < m_vec198.size(); ++i)
		delete static_cast<Rva00469D86 *>(m_vec198[i]);
	m_vec198.clear();
	for (i = 0; i < m_vec1A4.size(); ++i)
		delete static_cast<Rva0046AA69Record *>(m_vec1A4[i]);
	m_vec1A4.clear();

	m_list1B4.m_list.clear();
	m_set1B8.m_set.rva00072FE6();
	m_set1C4.m_set.rva00072FE6();
	m_vec1F4.clear();
	m_vec218.clear();

	for (i = 0; i < m_vec20C.size(); ++i)
		delete static_cast<AsciiString *>(m_vec20C[i]);
	m_vec20C.clear();
	m_vec224.clear();

	::delete m_258;
}
