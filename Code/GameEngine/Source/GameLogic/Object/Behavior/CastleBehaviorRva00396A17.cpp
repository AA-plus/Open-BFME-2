// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include "../../../Common/GameLogicObjectLookupView.h"

class Player;
class Team;

class Player
{
public:
	Team *getDefaultTeam() const { return *(Team **)((const char *)this + 0x2ec); }
};

extern GameLogic *TheGameLogic;

struct Rva002A8AB1Record
{
	void rva002C6A4E(Object *object);
	void rva002C6A3D(Object *object);
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

class Object
{
public:
	void setTeam(Team *team);
};

class FoundationAIUpdate
{
public:
	virtual void rva00455B67(Player *oldOwner, Player *newOwner);
};

class CastleBehavior : public FoundationAIUpdate
{
public:
	virtual void rva00396A17(Player *oldPlayer, Player *newPlayer);
};

static __declspec(noinline) void rva00396999(_STL::vector<ObjectID> *vec, Player *oldPlayer, Player *newPlayer)
{
	Rva002A8AB1Record *oldRecord = g_00DFEEF8->rva002A8AB1(oldPlayer);
	Rva002A8AB1Record *newRecord = g_00DFEEF8->rva002A8AB1(newPlayer);
	ObjectID *end = vec->end();
	for (ObjectID *it = vec->begin(); it != end; ++it)
	{
		Object *object = TheGameLogic->findObjectByID(*it);
		if (object)
		{
			if (oldRecord)
				oldRecord->rva002C6A4E(object);
			if (newRecord)
				newRecord->rva002C6A3D(object);
			object->setTeam(newPlayer->getDefaultTeam());
		}
	}
}

void CastleBehavior::rva00396A17(Player *oldPlayer, Player *newPlayer)
{
	FoundationAIUpdate::rva00455B67(oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x50), oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x5c), oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x68), oldPlayer, newPlayer);
	rva00396999((_STL::vector<ObjectID> *)((char *)this + 0x74), oldPlayer, newPlayer);
}
