// ?onComingOutOfShroud@Drawable@@AAEXXZ
// partial score=0.87 date=2026-10-13
// ?onComingOutOfShroud@Drawable@@AAEXXZ
// partial score=0.87 date=2026-10-13
// ?onComingOutOfShroud@Drawable@@AAEXXZ
// partial score=0.87 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?onComingOutOfShroud@Drawable@@AAEXXZ, retail 0x0027893E..0x00278C29 (747 bytes).
// Owner TU: Code/GameEngine/Source/GameClient/DrawableLazyHelper.cpp
// (contiguous with rowed 0x002788C7; region default supplies -arch:SSE -G7).
// Identity: WorldBuilder twin 0x00CA3700 (Drawable::onComingOutOfShroud,
// Drawable.cpp; EnemyObjectSighted / EnemyCampSighted debug lines, line 2084
// castle assert). Retail offsets (target-measured; WB debug layout differs):
// template +0x04 (kind bytes +0x108, EVA events +0x59C/+0x5A0/+0x5A4/+0x5A8),
// object +0xFC, status bits +0x114, reported bytes +0x445/+0x446,
// object status +0x438. All callees rowed or pinned with verified manglings:
// Eva 0x1DE2DA (bool(EvaEventID,Coord3D*,Coord3D*)), 272AD5, 272A6A, 294471 pin
// (bool(void*,int) thiscall), 28AFA9, 2AB08B, 4A1828 (cdecl, caller pop-ecx
// cleanup reproduced), 270260, 2706A8, 28B6D6 (PROTECTED const: declare under
// protected: with friend class Drawable to get the IBE mangling), 49DC5,
// 5508E2 (call as Object::getDrawable const, same spelling as landed sibling
// DrawableShroud.cpp; folds to rowed Thing::getDrawable), 3955DA (static),
// 3974CE, 2706F0 (cdecl callback, DIR32). NameKeyGenerator::nameToKey via the
// 0x148E1A (const char*) row. Static "CastleMemberBehavior" key init matches
// (guard byte + EH state + nameToKey). Early region (through 0x278AB4)
// byte-identical modulo relocs/jump targets.
// WALL (single allocator fixed point, ~34 bytes): retail spills obj to a home
// (mov [ebp-0x10],ebx right after the two loads; frame 0x18 vs 0x14) and keeps
// the 0x80 mask homeless in ebx (mov ebx,0x80 twice: before the kind-7 test
// and after the static-init barrier; test byte [edi+0x108],bl / test bl,al /
// or eax,ebx). Ours keeps obj in ebx to the end (no home) so the mask spills
// (immediates, or eax,edx via a home). Late obj uses must all come from the
// [ebp-0x10] home (controllingPlayer, nearest, findModule, castle 272AD5 and
// position, both dead tests, both positions, revealed+shrouded 272AD5; edx
// carries it into the shared revealed/shrouded tail at 0x278BF3).
// PROVEN NEGATIVES (do not retry): plain copies/refs/structs of obj fold
// (U1); declaration/statement order neutral; isKindOf(7) vs (k[0]&mask)
// same-block folds to imm - the kind-7 use must share the live mask web;
// volatile obj-copy forces the top home store but sorts its slot last
// (-0x14 not -0x10) and rotates this/obj/tmpl (this loses esi); sibling-scope
// twin mask80 decls; goto-form of the holder/controller join (+3B).
// T-PROBE (diagnostic): deleting one late addr-use flips obj home-based but
// re-ranks tmpl into ebx - obj/tmpl are within one use of each other.
// PRESCRIPTION: find a non-volatile, non-reshuffling home anchor for the late
// obj web that sorts its slot FIRST (-0x10); a single shared 0x80 local (kind7
// + 2 tests + 2 ors, born right before kind7) should then take ebx.
// t=40 model=muse-spark (seat W7-MP6).

#include "Coord3D.h"
#include "../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Player;
class Drawable;

class ThingTemplate
{
public:
	__forceinline bool isKindOf(int kind) const
	{ return (m_kindOf[kind >> 3] & (1 << (kind & 7))) != 0; }
	char m_pad000[0x108];
	unsigned char m_kindOf[0x20]; // +0x108
	char m_pad128[0x59C - 0x128];
	int m_sightedEvent; // +0x59C
	int m_sightedEventAlt; // +0x5A0
	int m_revealedEvent; // +0x5A4
	int m_shroudedEvent; // +0x5A8
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

enum EvaEventID
{
	EVA_EVENT_INVALID = -1
};

class Eva
{
public:
	bool reportEvaEvent(EvaEventID event, const Coord3D *position, const Coord3D *position2);
};
extern Eva *TheEva;

struct ModuleData
{
	char pad[0x4C];
	int m_campSightedEvent; // +0x4C
};

class Module
{
public:
	void *m_vtable;
	const ModuleData *m_moduleData; // +0x04
	char pad08[0x18 - 0x08];
	ObjectID m_castleID; // +0x18
};

class Rva003974CE
{
public:
	int apply(int (*func)(Object *obj, int arg), int arg);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

class Rva004A1828Holder
{
public:
	virtual ObjectID getID();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool isReady();
};
struct Rva004A1828Owner;
int Rva004A1828Get(Rva004A1828Owner *owner);

class Object
{
	friend class Drawable;
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_position; }
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }
	bool rva00294471(void *player, int arg);
	Player *getControllingPlayer() const;
	Drawable *getDrawable() const;
protected:
	Module *findModule(NameKeyType key) const;
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_position; // +0x38
	char m_pad44[0x438 - 0x44];
	unsigned char m_privateStatus; // +0x438
};

class Player
{
public:
	int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_localPlayer; }
private:
	char m_pad000[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class Rva00270260
{
public:
	bool rva00270260();
};

class Rva002706A8
{
public:
	void rva002706A8();
};

int rva00272A6A(Object *obj, void *userData);
int rva002706F0(Object *obj, int arg);

class Drawable
{
public:
	Object *rva00272AD5();
	void onComingOutOfShroud();
private:
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0xFC - 0x08];
	Object *m_object; // +0xFC
	char m_pad100[0x114 - 0x100];
	unsigned int m_status; // +0x114
	unsigned char m_pad118[0x445 - 0x118];
	bool m_sightReported; // +0x445
	bool m_useAltSightedEvent; // +0x446
};

struct SightedEventData
{
	Drawable *drawable;
	int event;
};

void Drawable::onComingOutOfShroud()
{
	Object *obj = m_object;
	Object *target = obj;
	const ThingTemplate *tmpl = m_template;
	Player *localPlayer = ThePlayerList ? ThePlayerList->getLocalPlayer() : 0;
	if (!tmpl || !obj || !localPlayer || !TheGameLogic || TheGameLogic->getFrame() <= 5)
		return;

	if (obj->rva00294471(localPlayer, 1)) {
		if (!obj->isEffectivelyDead() && tmpl->m_sightedEvent != -1 && !tmpl->isKindOf(47) && !m_sightReported) {
			Rva004A1828Holder *holder = (Rva004A1828Holder *)Rva004A1828Get((Rva004A1828Owner *)obj);
			bool skip;
			if (holder && holder->isReady()) {
				skip = false;
			} else {
				Player *controller = target->getControllingPlayer();
				if (controller) {
					SightedEventData data;
					data.drawable = this;
					data.event = tmpl->m_sightedEvent;
					if (controller->iterateObjects(rva00272A6A, &data) == 1)
						skip = false;
					else
						skip = true;
				} else {
					skip = true;
				}
			}
			if (!skip) {
				Object *nearest = ((Drawable *)target)->rva00272AD5();
				if (nearest) {
					int event = tmpl->m_sightedEvent;
					if (m_useAltSightedEvent && tmpl->m_sightedEventAlt != -1)
						event = tmpl->m_sightedEventAlt;
					if (TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), target->getPosition()) && holder && holder->isReady()) {
						m_sightReported = true;
						Object *holderObject = TheGameLogic->findObjectByID(holder->getID());
						if (holderObject) {
							Drawable *draw = holderObject->getDrawable();
							if (draw)
								((Rva002706A8 *)draw)->rva002706A8();
						}
					}
				}
			}
		}

		int mask80 = 0x80;
		if (((tmpl->m_kindOf[0] & mask80) != 0) && !(m_status & 0x40)) {
			static NameKeyType key_CastleMemberBehavior = TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
			Module *member = target->findModule(key_CastleMemberBehavior);
			if (member) {
				Object *castle = TheGameLogic->findObjectByID(member->m_castleID);
				if (castle) {
					Module *castleBehavior = castle->findModule(CastleBehavior::rva0003955DA());
					if (castleBehavior) {
						int event = castleBehavior->m_moduleData->m_campSightedEvent;
						if (event != -1) {
							Drawable *castleDraw = castle->getDrawable();
							if (castleDraw) {
								if (!(castleDraw->m_status & 0x40)) {
									Object *nearest = ((Drawable *)target)->rva00272AD5();
									if (nearest)
										TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), target->getPosition());
								}
								((Rva003974CE *)castleBehavior)->apply(rva002706F0, 0);
							}
						}
					}
				}
			}
		}

		if (!(m_status & mask80) && !target->isEffectivelyDead()) {
			m_status |= mask80;
			int event = tmpl->m_revealedEvent;
			if (event != -1) {
				Object *nearest = ((Drawable *)target)->rva00272AD5();
				if (nearest)
					TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), target->getPosition());
			}
		}
	} else {
		if (((Rva00270260 *)this)->rva00270260())
			return;
		int mask80 = 0x80;
		if (!(m_status & mask80) && !target->isEffectivelyDead()) {
			m_status |= mask80;
			int event = tmpl->m_shroudedEvent;
			if (event != -1) {
				Object *nearest = ((Drawable *)target)->rva00272AD5();
				if (nearest)
					TheEva->reportEvaEvent((EvaEventID)event, nearest->getPosition(), target->getPosition());
			}
		}
	}
}
