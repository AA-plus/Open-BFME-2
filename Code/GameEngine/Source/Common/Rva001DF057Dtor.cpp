// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva001DF057@@UAE@XZ @0x001DF057 154B.
// Virtual dtor with primary vtable 0x00BDC5B8 and secondary 0x00BDC5A8.
// Primary base SubsystemInterface at +0 (size 0xC rowed 0x001B4E74).
// Secondary Snapshot at +0xC restored to g_00BBB554 inline (no call).
// Members in reverse destroy order: list<int> at +0x68 via rowed List_base
// 0x004EC395 then ptr at +0x5C via inline null-guarded free 0x00030830 then
// two hash tables at +0x48/+0x34 via dup 0x001DDBF3 (same bytes as rowed
// ??1Rva000427195 0x001FDEDB) then two vectors of Rva001DEF38Element at
// +0x28/+0x1C via rowed 0x001DEEF9 then tree Rva001DD70F at +0x10 via rowed
// 0x001DD9BB. Caller is ??_G at 0x001DF3D5 in OpaqueScalarDeletingDtorsB03.
#include <vector>
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

extern "C" void __cdecl free(void *block) throw(...);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[0x0C - 0x04];
};

extern const void *const g_00BBB554[];

class SnapBase
{
public:
	virtual ~SnapBase() { *(const void **)this = g_00BBB554; }
};

class Rva001DD70F
{
public:
	~Rva001DD70F();
private:
	void *m_header;
	int m_flag;
};

struct Rva001DEF38Element
{
	~Rva001DEF38Element();
};

class Rva000427195 {public:void rva003A2A41();};
struct Rva001DDBF3Buckets
{
	void **begin, **end, **capacity;
	~Rva001DDBF3Buckets() { if (begin) free(begin); }
};
// Target1DDBF3 reads the bucket array at+4 and calls the rowed clear3A2A41;
// parent1DF057 gives these two members a20-byte extent. Field meanings not
// independently read by those bodies remain carried from the existing donor.
struct Rva001DDBF3
{
	__declspec(noinline) ~Rva001DDBF3();
	void *unknown00;
	Rva001DDBF3Buckets buckets;
	unsigned count;
};
// The complete storage destructor is defined in its approved Eva.cpp home.
// This source relationship models the verified5B tail forwarder1DDEFF;
// it does not assert the original application's base-class hierarchy.
struct Rva000427195Hash : Rva001DDBF3 { ~Rva000427195Hash() {} };
typedef char HashStorageExtent[(sizeof(Rva000427195Hash)==20)?1:-1];

struct Rva001DF057Buf
{
	~Rva001DF057Buf()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
	void *m_ptr;
};

class Rva001DF057 : public SubsystemInterface, public SnapBase
{
public:
	virtual ~Rva001DF057();
private:
	Rva001DD70F m_tree10;
	char m_pad18[0x1C - 0x10 - sizeof(Rva001DD70F)];
	_STL::vector<Rva001DEF38Element, _STL::allocator<Rva001DEF38Element> > m_vec1C;
	_STL::vector<Rva001DEF38Element, _STL::allocator<Rva001DEF38Element> > m_vec28;
	Rva000427195Hash m_hash34;
	Rva000427195Hash m_hash48;
	Rva001DF057Buf m_buf5C;
	char m_pad60[0x68 - 0x5C - sizeof(Rva001DF057Buf)];
	_STL::_List_base<int, _STL::allocator<int> > m_list68;
};

Rva001DF057::~Rva001DF057()
{
}
