// cl: /O1 /DNDEBUG /MD
//
// ComputeObjectRank, retail 0x005C3180 (85B), from the WorldBuilder lead
// (UnitHelpSource.cpp): ask the object's experience tracker (Object +0x264,
// 0x0039AC0C) for its experience-level handle, and return the store's rank for
// it (ExperienceLevelStore::GetLevelRank) when the store reports the handle
// valid (ExperienceLevelStore::IsValid), else 0.
//
// Target facts: the store is the global at 0x00DFECC4 (pinned as
// TheExperienceLevelSystem); the handle is two dwords passed by value, copied with the
// member-wise copy constructor as in ExperienceLevelSystem.cpp.

typedef int Int;

struct ExperienceLevelNode;
class ExperienceLevelList;

struct ExperienceLevelIterator
{
	ExperienceLevelNode *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}

	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

class ExperienceLevelStore
{
public:
	bool IsValid(ExperienceLevelHandle handle) const;
	ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle handle) const;
	Int GetLevelRank(ExperienceLevelHandle handle) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class Rva005CB9FF
{
public:
	bool rva005CB9FF(int a);
};

class ExperienceTracker
{
public:
	ExperienceLevelHandle rva0039AC0C() const;
};

class Object
{
public:
	bool rva0028C149(int, float *, int);
	bool rva0028C15E(int, float *, int, int);
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }

private:
	unsigned char m_pad00[0x264];
	ExperienceTracker *m_experienceTracker;
};

extern "C" __declspec(dllimport) double __cdecl floor(double);
class ThingTemplate
{
public:
	unsigned char prefix[0x5bc];
	int meleeDamage;
	int rangedDamage;
};

static __declspec(noinline) void rva004E72CB(const ThingTemplate *, int &, int &, Object *);

Int ComputeObjectRank(const Object *obj)
{
	ExperienceLevelHandle handle = obj->getExperienceTracker()->rva0039AC0C();
	if (!reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(handle))
		return 0;
	return reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(handle);
}

static __declspec(noinline) Int ComputeObjectMaxRank(const Object *obj)
{
	ExperienceLevelHandle handle = obj->getExperienceTracker()->rva0039AC0C();
	if (!reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(handle))
		return 0;

	ExperienceLevelHandle next = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetNextLevel(handle);
	while (reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->IsValid(next))
	{
		handle = next;
		next = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetNextLevel(handle);
	}
	Int maxRank = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->GetLevelRank(handle);

	Int rankCap;
	if (reinterpret_cast<Rva005CB9FF *>(obj->getExperienceTracker())->rva005CB9FF(reinterpret_cast<int>(&rankCap)))
	{
		if (rankCap < maxRank)
			maxRank = rankCap;
	}
	return maxRank;
}
// ?ComputeObjectMaxRankCaller absent-from-retail
Int ComputeObjectMaxRankCaller(const Object *obj)
{
	Int rank = ComputeObjectRank(obj);
	if (rank > 0)
		return ComputeObjectMaxRank(obj);
	int melee, ranged;
	const ThingTemplate *tpl = *reinterpret_cast<const ThingTemplate *const *>(reinterpret_cast<const char *>(obj) + 4);
	rva004E72CB(tpl, melee, ranged, const_cast<Object *>(obj));
	return melee + ranged;
}

// Native4E72CB..4E7392 (199B) takes template in EDI, melee-out in ESI,
// ranged-out in EBX and Object on stack; the4E7506 tooltip caller establishes
// these roles. Fields5BC/5C0 are target damage integers with negative sentinel.
// The byte-owned Object modifier wrappers supply additive2 and multiplicative3
// values; native rounds with floor(value+0.5f), then CRT ftol2. Original helper
// spelling is unproved. File-static visibility preserves the private convention.

static __declspec(noinline) void rva004E72CB(const ThingTemplate *tpl,
	int &melee, int &ranged, Object *obj)
{
	float bonus;
	if (!obj->rva0028C149(2, &bonus, 0))
		bonus = 0.0f;
	int add = (int)floor(bonus + 0.5f);
	melee = tpl->meleeDamage;
	if (melee >= 0)
		melee += add;
	ranged = tpl->rangedDamage;
	if (ranged >= 0)
		ranged += add;
	float multiplier;
	if (obj->rva0028C15E(3, &multiplier, 0, 1))
	{
		if (melee > 0)
			melee = (int)floor(melee * multiplier + 0.5f);
		if (ranged > 0)
			ranged = (int)floor(ranged * multiplier + 0.5f);
	}
}
