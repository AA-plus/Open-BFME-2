// cl: /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /DNDEBUG /MD /GX- /O2 /Ob2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// Add_Prototype thin wrapper (BFME1 Add_Prototype.cpp pattern).
// Null-check the global resource enumerator at VA 0x00E09C0C,
// then thiscall into Add_Prototype_Impl at 0x00621710.
//
// The enumerator itself lives here too: Begin (retail 0x00621480, 69 bytes)
// snapshots the prototype registry's hash table under the enumerator lock,
// entering the critical section at +0x34, copying the begin() iterator of
// the int->int table at +0x4C into the +0x60/+0x64 cursor, recording the
// tag at +0x1F0 and leaving the lock. The table is stlport's raw hashtable
// (retail calls hashtable::begin at 0x00620A80 directly). The imports are
// hand-declared like BfmeDX8ThreadLock.cpp's.

#include <hash_map>
// bfme link decl-only begin
namespace _STL { template <> void hashtable<pair<int const, int>, int, hash<int>, _Select1st<pair<int const, int> >, equal_to<int>, allocator<pair<int const, int> > >::resize(unsigned int); }
// bfme link decl-only end

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);
}

// 24-byte Windows critical section (DebugInfo, LockCount, RecursionCount,
// OwningThread, LockSemaphore, SpinCount).
struct BfmeCriticalSection
{
	void *m_debugInfo;
	long m_lockCount;
	long m_recursionCount;
	void *m_owningThread;
	void *m_lockSemaphore;
	unsigned long m_spinCount;
};

typedef _STL::hashtable<_STL::pair<const int, int>, int, _STL::hash<int>,
	_STL::_Select1st<_STL::pair<const int, int> >, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, int> > > BfmePrototypeTable;

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, int> > > BfmePrototypeMap;

// String-interning name table holding the 45007-bucket registry that
// Add_Prototype_Impl queries. Retail 0x00620500 (187B) hashes the name
// case-insensitively (tolower fold, times 33), buckets via div 0xAFCF,
// compares with strcmp and allocates 12-byte nodes via operator new;
// it returns the interned integer ID, or 0 for a null name.
enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    NAMEKEY_MAX = 1 << 23,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToLowercaseKey(const char *prototypeName);
};

// Prototype template handed to Add_Prototype_Impl. The allocating caller
// (Create_Rva00972880_Prototype at 0x00181130) builds a 20-byte
// GenBase-derived object, installs vtable 0xBD5090 whose slot 0 returns
// the "NULL" name, then forwards here. Retail proves three members:
// the vptr, a 16-bit reference count at +4 (inc word) and the interned
// integer ID at +8.
struct BfmeAddedPrototype
{
	virtual const char *GetPrototypeName() const;
	short m_referenceCount; // +4
	short m_padding06; // +6: aligns m_prototypeId
	int m_prototypeId; // +8
};

// Raw-critical-section RAII guard. The constructor stores the section
// pointer then enters it; the destructor leaves it. Normal paths inline
// both to direct Enter/Leave imports while the stored pointer plus the
// EH state drive the out-of-line unwind that leaves on throw.
struct BfmeCriticalSectionGuard
{
	void *m_guardedSection;
	BfmeCriticalSectionGuard(void *section) : m_guardedSection(section)
	{
		EnterCriticalSection(section);
	}
	~BfmeCriticalSectionGuard()
	{
		LeaveCriticalSection(m_guardedSection);
	}
};

class BfmeResourceEnumerator
{
public:
	void Add_Prototype_Impl(void *prototype);
	void Begin(unsigned tag);

private:
	// +0x00 vptr and +0x04..0x33 unrecovered; the absolute offsets below are
	// what the retail bodies prove.
	unsigned char m_unknown00[0x34];
	BfmeCriticalSection m_lock; // +0x34
	BfmePrototypeTable m_prototypes; // +0x4C
	void *m_cachedNode; // +0x60: begin()._M_cur snapshot
	void *m_cachedTable; // +0x64: begin()._M_ht snapshot
	unsigned char m_unknown68[0x1F0 - 0x68];
	unsigned m_tag; // +0x1F0
	unsigned char m_unknownF4[0x1F8 - 0x1F4];
	NameKeyGenerator *m_nameTable; // +0x1F8
};

extern BfmeResourceEnumerator *TheResourceEnumerator;

// ?Add_Prototype@@YAXPAX@Z
void Add_Prototype(void *prototype)
{
	if (TheResourceEnumerator)
		TheResourceEnumerator->Add_Prototype_Impl(prototype);
}

void BfmeResourceEnumerator::Begin(unsigned tag)
{
	EnterCriticalSection(&m_lock);
	BfmePrototypeTable::iterator iter = m_prototypes.begin();
	m_cachedNode = iter._M_cur;
	m_cachedTable = iter._M_ht;
	m_tag = tag;
	LeaveCriticalSection(&m_lock);
}

// ?Add_Prototype_Impl@BfmeResourceEnumerator@@QAEXPAX@Z
void BfmeResourceEnumerator::Add_Prototype_Impl(void *prototype)
{
	BfmeAddedPrototype *addedPrototype = (BfmeAddedPrototype *)prototype;
	if (!addedPrototype)
		return;
	BfmeCriticalSectionGuard registryGuard(&m_lock);
	const char *prototypeName = addedPrototype->GetPrototypeName();
	int prototypeId = m_nameTable->nameToLowercaseKey(prototypeName);
	if (prototypeId == 0)
		return;
	BfmePrototypeTable::iterator foundIter = m_prototypes.find(prototypeId);
	if (foundIter._M_cur != 0)
		return;
	++addedPrototype->m_referenceCount;
	BfmePrototypeMap &prototypeMap = (BfmePrototypeMap &)m_prototypes;
	prototypeMap[prototypeId] = (int)addedPrototype;
	addedPrototype->m_prototypeId = prototypeId;
	BfmePrototypeTable::iterator beginIter = m_prototypes.begin();
	m_cachedNode = beginIter._M_cur;
	m_cachedTable = beginIter._M_ht;
}
