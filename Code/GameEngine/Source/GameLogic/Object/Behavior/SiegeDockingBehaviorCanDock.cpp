// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// SiegeDockingBehavior::rva00459C58, retail 0x00459C58 (104 B; WB 0x0117AA30,
// unnamed): slot 3 of the behavior's +0x20 dock interface. For an existing
// object it first refreshes the dock reservations (the rowed primary-this
// member 0x00459B68), then reports whether some dock entry (+0x24 list) is
// unreserved (+0x20) and either the object's template has kind bit +0x119&8
// or the entry's +0x04 slot is empty. Names are structural.
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct SiegeDockTemplateView
{
	unsigned char m_pad000[0x119];
	unsigned char m_kind119;	// +0x119
};

struct SiegeDockObjectView
{
	unsigned char m_pad00[4];
	const SiegeDockTemplateView *m_template;	// +0x04
};

struct SiegeDockEntry
{
	unsigned char m_pad00[4];
	void *m_occupant;			// +0x04
	unsigned char m_pad08[0x20 - 8];
	ObjectID m_reservedBy;		// +0x20
};

class SiegeDockPrimaryView
{
public:
	virtual ~SiegeDockPrimaryView();
private:
	unsigned char m_pad04[0x20 - 4];
};

class SiegeDockInterface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual bool rva00459C58(ObjectID id) = 0;
};

class SiegeDockingBehavior : public SiegeDockPrimaryView, public SiegeDockInterface
{
public:
	virtual bool rva00459C58(ObjectID id);
private:
	void rva00459B68() const;		// 0x00459B68
	_STL::vector<SiegeDockEntry *> m_entries;	// +0x24
};

bool SiegeDockingBehavior::rva00459C58(ObjectID id)
{
	SiegeDockObjectView *obj = (SiegeDockObjectView *)TheGameLogic->findObjectByID(id);
	if (obj == 0)
		return false;
	rva00459B68();
	unsigned int count = m_entries.size();
	if (count == 0)
		return false;
	for (unsigned int i = 0; i < count; ++i)
	{
		SiegeDockEntry *entry = m_entries[i];
		if (entry->m_reservedBy == INVALID_OBJECT_ID)
		{
			if ((obj->m_template->m_kind119 & 8) || entry->m_occupant == 0)
				return true;
		}
	}
	return false;
}
