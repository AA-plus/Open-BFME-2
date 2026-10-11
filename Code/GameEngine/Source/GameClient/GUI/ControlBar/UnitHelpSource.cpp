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
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }

private:
	unsigned char m_pad00[0x264];
	ExperienceTracker *m_experienceTracker;
};

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
	return 0;
}
