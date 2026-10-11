// cl: /O1 /DNDEBUG /MD
// stlport
// The implicitly emitted public destructor is not a target identity claim.
// Its masked placement at 0x00490E7B was retracted: the actual destructor
// is the separately verified protected body at 0x004BA47C.
// ??1TransitionDamageFX@@UAE@XZ present-unmatched
//
// ??0TransitionDamageFX@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BA3EA,
// 71 bytes. TransitionDamageFX ctor over the rowed DamageModule base
// (0x4B9704, thing plus data). The TU-local DamageModule models the donor
// multiple inheritance (primary 0x0C plus two pure interface words, 0x14
// total) so the derived vtable group lands at ([esi], +0x0C, +0x10) ahead of
// the implicit vector member init; the _STL::vector<int> member at +0xD4
// builds through the folded Vector_base at 0x211E58 (existing H-spelling pin;
// the element type is unproven and int is selected to reuse it, the 29B body
// is T-independent). The clear array at +0x14 drains through the
// for-loop-over-ints idiom (rep stosd with lea-before-xor setup,
// DynamicPortalBehaviour precedent).
//
// The rowed instance factory 0x250D4F (sole caller, ModuleFactory
// registration literal) proves the class. Row supersedes the ctor pin.

#include <vector>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

class Thing;
class ModuleData;

// Primary base chain of the rowed DamageModule: vptr plus module data plus
// object (0x0C) with the two interface words following (0x14 total).
class DamageModuleBase
{
public:
	DamageModuleBase(Thing *thing, const ModuleData *moduleData);
	virtual ~DamageModuleBase();

protected:
	const ModuleData *m_moduleData;
	void *m_object;
};

class DamageModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class DamageModuleInterface2
{
public:
	virtual void slot2() = 0;
};

class DamageModule : public DamageModuleBase,
		     public DamageModuleInterface1,
		     public DamageModuleInterface2
{
public:
	DamageModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DamageModule();
};

class TransitionDamageFX : public DamageModule
{
public:
	TransitionDamageFX(Thing *thing, const ModuleData *moduleData);

private:
	int m_clear[0x30]; // +0x14
	_STL::vector<int> m_fxIds; // +0xD4
};

// ??0TransitionDamageFX@@QAE@PAVThing@@PBVModuleData@@@Z @0x4BA3EA
TransitionDamageFX::TransitionDamageFX(Thing *thing, const ModuleData *moduleData)
	: DamageModule(thing, moduleData)
{
	for (int i = 0; i < 0x30; ++i)
		m_clear[i] = 0;
}
