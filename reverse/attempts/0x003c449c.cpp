// ?doTeamUseCommandButtonOnNearestObjectType@ScriptActions@@IAEXABVAsciiString@@00@Z
// partial score=0.9812264150943395 date=2026-10-14
// cl: /G7 /O1 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /I.
// BFME 2's "use a command button on the nearest object of a type" tail and its two callers
// (the dispatcher 0x003CA4BE reaches them at 0x003CCBC7 and 0x003CCDC1):
//
//   0x003BE11C  file-static helper (EBX/ESI/EDI, the unit in ESI, template and button on the
//               stack): from the unit's position the closest object of the template (thing
//               filter, plus the valid-target filter unless the button's +0x1C bit 5 is set,
//               all linked to the not-self filter) gets the button (0x00297000 with the
//               object, or 0x00297149 with its position under bit 5); with no object found
//               and kind 94 set on the template, the terrain's 0x0027F108 search around the
//               unit gives a position to command instead
//   0x003C42B9  the named unit
//   0x003C449C  every ready member of the named team (its template off the closest object of
//               the type list to the team's centre, or the single named template)
//
// The helper keeps retail's private register convention because it is static, never inlined
// and called from this unit; so it and its callers stay together here.
#include "ascii_string.h"

#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"

class Parameter;
class Player;
class ObjectTypes;
class ThingTemplate;
class CommandButton;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00C1FDEC, allow 0x00261750: +0x08 a thing template, +0x0C whether a match allows.
class Rva00261750Filter : public Rva000421C8
{
public:
	Rva00261750Filter(const ThingTemplate *tmpl, bool match) : m_template(tmpl), m_match(match) {}
	virtual bool allow(Object *obj);
	const ThingTemplate *m_template;
	bool m_match;
};

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C1FE34, allow 0x002614BC: +0x08 the source object, +0x0C the command button,
// +0x10 whether a valid target allows, +0x14 the command source.
class Rva002614BCFilter : public Rva000421C8
{
public:
	Rva002614BCFilter(Object *source, const CommandButton *button, bool match, int cmdSource)
		: m_source(source), m_button(button), m_match(match), m_cmdSource(cmdSource) {}
	virtual bool allow(Object *obj);
	Object *m_source;
	const CommandButton *m_button;
	bool m_match;
	int m_cmdSource;
};

class Object
{
public:
	bool rva002922D9(const CommandButton *button);	// 0x002922D9
	void rva00297000(const CommandButton *button, Object *target, int source, int flags);	// 0x00297000
	void rva00297149(const CommandButton *button, const Coord3D *pos, int source, int flags);	// 0x00297149
	const Coord3D *getPosition() const { return &m_pos; }
	char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;			// +0x38
};

class ThingTemplate
{
public:
	bool rva003BE11C94() const { return (m_113 & 0x40) != 0; }
	char m_pad00[0x113];
	unsigned char m_113;
};

class CommandButton
{
public:
	bool isReady(const Object *obj) const;	// 0x0035B069
	bool rva003BDCCA() const { return (m_options >> 5) & 1; }
	char m_pad00[0x1C];
	unsigned int m_options;	// +0x1C
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);	// 0x0031BE3C
};
extern ControlBar *TheControlBar;

template <class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];

public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;	// 0x00263864
	Coord3D *rva0039DA2A(Coord3D *center) const;	// 0x0039DA2A
};

class ScriptEngine
{
public:
	Team *getTeamNamed(AsciiString name, bool exact);	// 0x003584E9
	Object *getUnitNamed(Parameter *unit);	// 0x003588E7
	ObjectTypes *getObjectTypes(const AsciiString &name);	// 0x00357651
};
extern ScriptEngine *TheScriptEngine;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);	// 0x002D06CA
};
extern ThingFactory *TheThingFactory;

extern PartitionManager *ThePartitionManager;

// Native 0x27F108 takes four 32-bit argument slots and returns a result word the caller only
// tests for zero (see Rva004389AENearbyCheck.cpp).
class BfmeThingCME
{
public:
	int rva0027F108(void *position, float radius, int flag, int unused);
};
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

#define REALLY_FAR (100000 * 10.0f)

class ScriptActions
{
public:
	Object *rva003C24F0(const Coord3D *pos, ObjectTypes *types, Player *player, bool flag);
	void rva003C42B9(Parameter *param, const AsciiString &a, const AsciiString &b);
protected:
	void doTeamUseCommandButtonOnNearestObjectType(const AsciiString &teamName,
		const AsciiString &commandAbility, const AsciiString &objectType);
};

static __declspec(noinline) void rva003BE11C(Object *obj, const ThingTemplate *tmpl, const CommandButton *button)
{
	if (button->rva003BDCCA()) {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261750Filter(tmpl, true).link(&Rva002611BFFilter(obj)));
		if (target)
			obj->rva00297149(button, target->getPosition(), 1, 0);
	} else {
		Object *target = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva00261750Filter(tmpl, true).link(Rva002614BCFilter(obj, button, true, 1).link(&Rva002611BFFilter(obj))));
		if (!target) {
			if (tmpl->rva003BE11C94()) {
				int where = reinterpret_cast<BfmeThingCME *>(TheTerrainLogic)->rva0027F108(
					const_cast<Coord3D *>(obj->getPosition()), 10000000.0f, 1, 1);
				if (where)
					obj->rva00297149(button, (const Coord3D *)where, 1, 0);
			}
			return;
		} else {
			obj->rva00297000(button, target, 1, 0);
		}
	}
}

void ScriptActions::rva003C42B9(Parameter *param, const AsciiString &a, const AsciiString &b)
{
	Object *unit = TheScriptEngine->getUnitNamed(param);
	if (unit == 0)
		return;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(b);
	const ThingTemplate *tmpl;
	if (types != 0) {
		Object *obj = rva003C24F0(unit->getPosition(), types, 0, false);
		if (obj == 0)
			return;
		tmpl = obj->m_template;
	} else {
		tmpl = TheThingFactory->findTemplate(b);
	}
	if (tmpl == 0)
		return;
	const CommandButton *button = TheControlBar->findCommandButton(a);
	if (button == 0)
		return;
	if (!button->isReady(unit))
		return;
	if (!unit->rva002922D9(button))
		return;
	rva003BE11C(unit, tmpl, button);
}

void ScriptActions::doTeamUseCommandButtonOnNearestObjectType(const AsciiString &teamName,
	const AsciiString &commandAbility, const AsciiString &objectType)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;
	const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
	if (!commandButton)
		return;
	const ThingTemplate *tmpl;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(objectType);
	if (types) {
		Coord3D pos;
		Object *best = rva003C24F0(team->rva0039DA2A(&pos), types, 0, false);
		if (!best)
			return;
		tmpl = best->m_template;
	} else {
		tmpl = TheThingFactory->findTemplate(objectType);
	}
	if (!tmpl)
		return;
	Object *member;
	DLINK_ITERATOR<Object> iter;
	for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		member = iter.cur();
		if (commandButton->isReady(member))
			rva003BE11C(member, tmpl, commandButton);
	}
}
