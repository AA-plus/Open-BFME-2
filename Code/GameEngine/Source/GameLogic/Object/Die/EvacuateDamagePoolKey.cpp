// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ivendor/stlport
// stlport
// ?rva0004BAE83@EvacuateDamage@@SA?AW4NameKeyType@@XZ @0x4BAE83
// (69B): cached pool-name key for EvacuateDamage. The class
// identity comes from the pool-name string the body pushes
// ("EvacuateDamage"); the body guards a function-local static
// key fetched once through TheNameKeyGenerator. It is NOT getClassMemoryPool:
// retail stores nameToKey's return (a key, not a pool pointer) and returns it,
// and the address carries no getClassMemoryPool row anywhere. /EHsc for the
// static-guard EH prologue; globals are TU-local externs (DIR32 slots patch
// from retail, no pins; nameToKey resolves via its matched row).

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

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Thing;
class ModuleData;

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();

private:
	const ModuleData *m_moduleData;
	void *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class EvacuateDamageInterface { public: virtual void slot(); };

// The target's three-vptr base is only address-identified at 0x004B96CC.
class Rva004B96CC : public PB_DeepBase,
                     public PB_Iface1,
                     public EvacuateDamageInterface
{
public:
	virtual ~Rva004B96CC();
};

typedef Rva004B96CC DamageModule;

struct EvacuationRecord
{
	unsigned int m_data[2];
};

class EvacuateDamage : public DamageModule
{
public:
	static NameKeyType rva0004BAE83();

protected:
	virtual ~EvacuateDamage();

private:
	// Retail calls the ICF-canonical List_base<int> destructor at 0x004EC395.
	// EvacuationRecord is two POD dwords; the list object and teardown are
	// storage-identical here, and the typed pin for this dtor points elsewhere.
	std::list<int> m_pendingEvacuations;
};

// ?rva0004BAE83@EvacuateDamage@@SA?AW4NameKeyType@@XZ
NameKeyType EvacuateDamage::rva0004BAE83()
{
	static NameKeyType TheEvacuateDamagePoolKey =
		TheNameKeyGenerator->nameToKey("EvacuateDamage");
	return TheEvacuateDamagePoolKey;
}

EvacuateDamage::~EvacuateDamage()
{
}
