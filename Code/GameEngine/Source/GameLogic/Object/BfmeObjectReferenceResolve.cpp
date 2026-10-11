// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/GameLogic/Object/BfmeObjectReferenceResolve.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?resolve@BfmeObjectReference@@QAEPAVObject@@XZ 0x003775F7 (28B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Object;

struct BfmeObjectIdValue
{
	int m_id;
};

struct BfmeObjectIdSlot
{
	BfmeObjectIdValue *m_value;
};

class BfmeObjectReference
{
public:
	Object *resolve();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
// Zero Hour's GameCommon.h spells the id an enum; retail's 0x00049DC5 row takes it.
enum ObjectID { INVALID_ID = 0, FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff };
namespace _STL { template <class T> class allocator; template <class T, class A> class vector; }
// LINK: 0x0036F710 is rowed as AIGroup::getAllIDs; the reference reads the same
// word, so the slot read keeps its shape through a member-pointer cast.
class AIGroup
{
public:
	const _STL::vector<ObjectID, _STL::allocator<ObjectID> > &getAllIDs() const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

Object *BfmeObjectReference::resolve()
{
	if (this != 0) {
		BfmeObjectIdSlot *slot = (((AIGroup *)this)->*reinterpret_cast<BfmeObjectIdSlot *(AIGroup::*)()>(&AIGroup::getAllIDs))();
		return TheGameLogic->findObjectByID((ObjectID)slot->m_value->m_id);
	}
	return 0;
}
