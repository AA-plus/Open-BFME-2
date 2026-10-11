// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva003A393A@@QAE@XZ @0x003A393A 31B: Armor hash_map-shape default ctor twin of 0x00360B99.
// Identical 31B pushing 0x64 with three empty params calling the Armor hashtable ctor
// (rowed 0x00360B59, dup 0x003A37FA). Evidence: same bytes except call target; caller
// 0x003A3959 constructs member at +4 through this body; landing unblocks 0x003A3959/50
// and 0x003A39A7/471. Honest ctor name for an unknown owner; hashtable layout matches
// ArmorStoreCtor's ArmorTemplateMap.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <cstddef>
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{

template <typename T> struct hash
{
	size_t operator()(const T &value) const;
};

}

class ArmorTemplate
{
public:
	float m_damageCoefficient[38];
};

typedef std::hash_map<
	NameKeyType,
	ArmorTemplate,
	rts::hash<NameKeyType>,
	std::equal_to<NameKeyType> > ArmorTemplateMap;

typedef ArmorTemplateMap::value_type ArmorPair003A393A;
typedef ArmorTemplateMap::hasher ArmorHasher003A393A;
typedef ArmorTemplateMap::key_equal ArmorEqual003A393A;
typedef ArmorTemplateMap::allocator_type ArmorAlloc003A393A;

typedef _STL::hashtable<
	ArmorPair003A393A,
	NameKeyType,
	ArmorHasher003A393A,
	_STL::_Select1st<ArmorPair003A393A>,
	ArmorEqual003A393A,
	ArmorAlloc003A393A> ArmorHashtable003A393A;

class Rva003A393A
{
public:
	Rva003A393A();
private:
	ArmorHashtable003A393A m_table;
};

Rva003A393A::Rva003A393A() : m_table(100, ArmorHasher003A393A(), ArmorEqual003A393A(), ArmorAlloc003A393A()) {}
