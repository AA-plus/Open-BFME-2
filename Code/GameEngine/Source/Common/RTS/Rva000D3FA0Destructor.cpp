// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Byte-twin of ??1TeamRelationMap@@UAE@XZ at 0x000F21C0
// (Code/GameEngine/Source/Common/RTS/TeamRelationMapDestructor.cpp): identical
// 89 bytes once relocations are masked, itself the ZH-twin of
// ??1DisplayString@@MAE@XZ (m_map.clear(); the compiler inlines the empty
// Snapshot destructor). The installed derived vtable (0x01083E94) differs
// from TeamRelationMap's own, matching the sibling class installed by the
// constructor twin Rva000DA590Constructor.cpp (0x000DA590); no name is
// provable, so this is claimed address-derived.

#include <hash_map>
#include <cstddef>
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

class Xfer;

class Rva000D3FA0PoolObject
{
public:
	virtual ~Rva000D3FA0PoolObject() {}

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

typedef unsigned int TeamID;
enum Rva000D3FA0Relationship
{
	Rva000D3FA0_NEUTRAL = 0
};

typedef _STL::pair<const TeamID, Rva000D3FA0Relationship> Rva000D3FA0MapPair;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Rva000D3FA0Map : public Rva000D3FA0PoolObject
{
public:
	virtual ~Rva000D3FA0Map();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	_STL::hash_map<TeamID, Rva000D3FA0Relationship, _STL::hash<TeamID>, _STL::equal_to<TeamID>, _STL::allocator<Rva000D3FA0MapPair> > m_map;
};

// ??1Rva000D3FA0Map@@UAE@XZ
Rva000D3FA0Map::~Rva000D3FA0Map()
{
	m_map.clear();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?crc@Rva000D3FA0PoolObject@@MAEXPAVXfer@@@Z=__purecall")
#pragma comment(linker, "/alternatename:?xfer@Rva000D3FA0PoolObject@@MAEXPAVXfer@@@Z=__purecall")
#pragma comment(linker, "/alternatename:?loadPostProcess@Rva000D3FA0PoolObject@@MAEXXZ=__purecall")
#pragma comment(linker, "/alternatename:?crc@Rva000D3FA0Map@@MAEXPAVXfer@@@Z=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?xfer@Rva000D3FA0Map@@MAEXPAVXfer@@@Z=?name@Rva002431A9Named@@QBEPBDXZ")
