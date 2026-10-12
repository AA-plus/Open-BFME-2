// ??1Rva00557CCC@@QAE@XZ
// cl: /O1 /arch:SSE /G7 /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00557CCC@@QAE@XZ @0x00557CCC 204B
// The address-derived class identity comes from its vtable/deleting-destructor
// anchor. Member order and offsets below follow the retail cleanup calls;
// unnamed storage and owned-pointer meanings remain structural inferences.
#include <deque>

namespace _STL { }

struct MutexClass { unsigned int unknown[2]; ~MutexClass(); struct LockClass { ~LockClass(); }; };
struct Rva00553222 { virtual void virtualSlot(); void rva00553222(); ~Rva00553222() {} };
struct Rva005562DD { unsigned int unknown[3]; ~Rva005562DD(); };
void __cdecl operator delete(void *);
// Existing neutral lock-owner pin at9990D: this unit emits its whole26B
// null/clear/LockClass613AC0/delete2FD60 teardown equal to the rowed clear
// provider. The12B member extent follows the parent layout; fields after
// the pointer remain unknown. No original class identity is asserted.
struct Rva006609D0LockHolder {
 MutexClass::LockClass *m_ptr;
 unsigned int unknown[2];
 __declspec(noinline) ~Rva006609D0LockHolder() {
  MutexClass::LockClass *old=m_ptr;
  m_ptr=0;
  if(!old)return;
  old->~LockClass();
  ::operator delete(old);
 }
};

struct BfmeOpaqueOwnedRecord1408 {
	unsigned int head[2];
	unsigned char bytes[1400];
	BfmeOpaqueOwnedRecord1408();
	BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &);
};
struct BfmeOpaqueOwnedRecord1432 {
	unsigned int words[358];
	unsigned int tail;
	BfmeOpaqueOwnedRecord1432();
	BfmeOpaqueOwnedRecord1432(const BfmeOpaqueOwnedRecord1432 &);
};

extern "C" void free(void *);

typedef _STL::deque<BfmeOpaqueOwnedRecord1408,
	_STL::allocator<BfmeOpaqueOwnedRecord1408> > BfmeDeque1408;
typedef _STL::deque<BfmeOpaqueOwnedRecord1432,
	_STL::allocator<BfmeOpaqueOwnedRecord1432> > BfmeDeque1432;

struct Rva00142D70 {
	void *value;
	unsigned int unknown[2];
	~Rva00142D70() { if (value) free(value); }
};

class Rva00557CCC : public Rva00553222 {
public:
	~Rva00557CCC();
private:
	MutexClass m_mutex0;
	MutexClass m_mutex1;
	BfmeDeque1432 m_deque1432;
	BfmeDeque1408 m_deque1408;
	unsigned int m_gap64[2];
	Rva00142D70 m_owned6c;
	Rva00142D70 m_owned78;
	Rva00142D70 m_owned84;
	Rva005562DD m_member90;
	MutexClass m_mutex9c;
	Rva006609D0LockHolder m_clearA4;
};

Rva00557CCC::~Rva00557CCC()
{
	Rva00553222::rva00553222();
}
