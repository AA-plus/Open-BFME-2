// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?addSupplyWarehouse@ResourceGatheringManager@@QAEXPAVObject@@@Z, retail 0x004F5C64, 32 bytes.
// BFME1 donor game/GameEngine/Source/Common/RTS/ResourceGatheringManagerLists.cpp
// addSupplyWarehouse: null check then m_supplyWarehouses.push_back(newWarehouse->getID()).
// Slice: vtbl +0x00, warehouses +0x04, centers +0x08, ObjectID at Object+0x74.
// Repair for target: list<int> to match rowed push_back 0x0005548F (H not I).
// _STLP_NO_EXCEPTIONS so _M_create_node inlines (donor note).
#define _STLP_NO_EXCEPTIONS 1
#include <list>

// LINK: single-node insert binds the verified native STLport owner at RVA
// 0x005925E2; keep the out-of-line call without emitting a competing copy.
namespace _STL {
template <> list<int>::iterator list<int>::insert(iterator position, const int &x);
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

typedef int ObjectID;

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	char m_objectPad[0x74];
	ObjectID m_id;
};

class ResourceGatheringManager
{
public:
	void addSupplyWarehouse(Object *newWarehouse);
	void rva004F5C44(Object *newCenter);
private:
	typedef _STL::list<ObjectID> objectIDList;
	void *m_slice_vtbl;
	objectIDList m_supplyWarehouses;
	objectIDList m_supplyCenters;
};

void ResourceGatheringManager::addSupplyWarehouse(Object *newWarehouse)
{
	if (newWarehouse == NULL)
		return;
	m_supplyWarehouses.push_back(newWarehouse->getID());
}

void ResourceGatheringManager::rva004F5C44(Object *newCenter)
{
	if (newCenter == NULL)
		return;
	m_supplyCenters.push_back(newCenter->getID());
}
