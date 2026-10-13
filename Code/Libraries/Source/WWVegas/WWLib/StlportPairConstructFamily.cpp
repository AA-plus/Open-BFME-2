// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<pair<const int, T>, ...> placement copies (45 bytes:
// EH-guarded placement new calling the pair's out-of-line copy constructor)
// for four int-keyed hash maps whose _M_new_node rows already pin these
// names at these addresses (stlport_pod_hash_bodies.cpp views), with the
// flags of StlportConstructFamily.cpp, whose 45-byte shape these share.
// The mapped records are declared with just the copy constructor the pair
// copy calls; only their sizes are claimed.
//
//   _Construct  _M_new_node  pair copy   mapped view
//   0x002E00CC  0x002E0273   0x002DFD82  BfmePod72
//   0x00418985  0x004189ED   0x0041890F  BfmePod32
//   0x004192A4  0x0041930C   0x0041922E  BfmePod20
// The native 41985E/4198C6 family now uses the typed string-key record
// in Rva004197E8Pair.cpp; its former integer-key view was retired.
//
// The BfmePod72 pair copy at 0x002DFD82 (first int, then the record's copy
// constructor at 0x002DFC1B) is this unit's own implicit copy and is landed
// from it too; the other three pair copies copy string members differently
// and stay pinned only.
#include <memory>
#include <utility>

struct BfmePod72 { int a[18]; BfmePod72(const BfmePod72 &); };
struct BfmePod32 { int a[8]; BfmePod32(const BfmePod32 &); };
struct BfmePod20 { int a[5]; BfmePod20(const BfmePod20 &); };

typedef _STL::pair<const int, BfmePod72> IntPod72Pair;
typedef _STL::pair<const int, BfmePod32> IntPod32Pair;
typedef _STL::pair<const int, BfmePod20> IntPod20Pair;

// This payload's native pair copy has its own string-aware provider.
// Do not emit the generic BfmePod20 copy from this placement-only view.
template <> _STL::pair<const int, BfmePod20>::pair(const _STL::pair<const int, BfmePod20> &);

template void _STL::_Construct<IntPod72Pair, IntPod72Pair>(IntPod72Pair *, const IntPod72Pair &);
template void _STL::_Construct<IntPod20Pair, IntPod20Pair>(IntPod20Pair *, const IntPod20Pair &);
template _STL::pair<const int, BfmePod72>::pair(const int &, const BfmePod72 &);

// LivingWorld AI's non-const-key temporaries convert to tree value_type.
// GatherWorldInformation 0x0050366B calls these at the same native bodies
// as the independently rowed pair<const int, T> copy constructors. Only
// the verified record extents and their existing copy providers are used.
// The STLport 4.5.3 member template copies first, then constructs second;
// each complete emitted 29-byte body must prove the fold before it is pinned.
struct Rva00501656
{
	int storage[0x58 / 4];
	Rva00501656(const Rva00501656 &);
};
struct Rva00501776
{
	int storage[0x2C / 4];
	Rva00501776(const Rva00501776 &);
};
struct Rva00501E3FElement
{
	int storage[0x14 / 4];
	Rva00501E3FElement(const Rva00501E3FElement &);
};

template _STL::pair<const int, Rva00501656>::pair(const _STL::pair<int, Rva00501656> &);
template _STL::pair<const int, Rva00501776>::pair(const _STL::pair<int, Rva00501776> &);
template _STL::pair<const int, Rva00501E3FElement>::pair(const _STL::pair<int, Rva00501E3FElement> &);

// Native 0x0078671B: complete 14-byte placement-new failure cleanup.
// The exact 45-byte parent and native EH graph bind this action to the
// existing no-op placement delete; the original record identity stays unknown.
