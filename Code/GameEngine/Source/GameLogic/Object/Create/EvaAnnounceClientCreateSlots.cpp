// cl: /DNDEBUG /MD /ICode/Libraries/Include
//
// ?rva004C9A51@EvaAnnounceClientCreate@@UAEXXZ, retail 0x004C9A51, 49 bytes:
// slot 1 of the vtable EvaAnnounceClientCreate's ctor 0x004C99D4 installs at
// +0x0C (0x00C5ED48; slot 0 is the shared no-op). Once (the +0x14 flag), sets
// the frame at +0x10 to TheGameLogic's frame (+0x40) plus the module data's
// +0x14 delay, at least 2, and never earlier than frame 7 (the at-least-2
// written as a running maximum is what gives retail's cmova under
// /arch:SSE). Compiled with the +0x0C subobject this. Names by address.
#include "Lib/Coord3D.h"

typedef unsigned int UnsignedInt;

enum Relationship
{
	ENEMIES = 0,
	NEUTRAL = 1,
	ALLIES = 2
};

class Object;

class Player
{
public:
	Relationship getRelationship(const Object *that) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

enum EvaEventID { EVA_EVENT_NONE = 0 };
class Eva
{
public:
	bool reportEvaEvent(EvaEventID event, const Coord3D *pos, const Coord3D *pos2);
};

extern Eva *TheEva;

// The drawable test is rowed at 0x00270260 under its own address-named class.
class Rva00270260
{
public:
	bool rva00270260();
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	unsigned char m_pad000[0xFC];
	Object *m_FC; // +0xFC
	unsigned char m_pad100[0x114 - 0x100];
	unsigned char m_114; // +0x114
	unsigned char m_pad115[0x440 - 0x115];
	bool m_440; // +0x440
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

struct EvaAnnounceClientCreateModuleData
{
	unsigned char m_pad00[0x08];
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
	UnsignedInt m_delay; // +0x14
	bool m_18; // +0x18
	bool m_19; // +0x19
	bool m_1A; // +0x1A
};

class ClientCreateModule
{
public:
	virtual ~ClientCreateModule();
	virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8();
	virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void rva004C9A82() = 0;
protected:
	const EvaAnnounceClientCreateModuleData *m_moduleData; // +0x04
	Drawable *m_drawable; // +0x08
};

class CreateModuleInterface
{
public:
	virtual void slot0();
	virtual void rva004C9A51() = 0;
};

class EvaAnnounceClientCreate : public ClientCreateModule, public CreateModuleInterface
{
public:
	virtual void rva004C9A51();
	virtual void rva004C9A82();
private:
	UnsignedInt m_10; // +0x10
	bool m_14; // +0x14
};

void EvaAnnounceClientCreate::rva004C9A51()
{
	if (m_14)
		return;
	m_14 = true;
	UnsignedInt delay = 2;
	if (m_moduleData->m_delay > delay)
		delay = m_moduleData->m_delay;
	m_10 = delay + TheGameLogic->getFrame();
	if (m_10 < 7)
		m_10 = 7;
}

void EvaAnnounceClientCreate::rva004C9A82()
{
	if (m_10 == 0 || m_10 > TheGameLogic->getFrame())
		return;
	Drawable *draw = m_drawable;
	const EvaAnnounceClientCreateModuleData *d = m_moduleData;
	m_10 = 0;
	if (d->m_18 && (draw->m_440 || ((Rva00270260 *)draw)->rva00270260()))
		return;
	Object *obj = draw->m_FC;
	if (obj == 0)
		return;
	if (d->m_19)
		draw->m_114 |= 0x80;
	int event;
	Player *ctl = obj->getControllingPlayer();
	if (ctl == ThePlayerList->getLocalPlayer())
		event = d->m_10;
	else
	{
		switch (ThePlayerList->getLocalPlayer()->getRelationship(obj))
		{
		case ENEMIES:
		case NEUTRAL:
			event = d->m_08;
			break;
		case ALLIES:
			event = d->m_0C;
			break;
		default:
			event = -1;
			break;
		}
	}
	if (event == -1)
		return;
	const Coord3D *pos = 0;
	if (d->m_1A)
		pos = draw->getPosition();
	TheEva->reportEvaEvent((EvaEventID)event, pos, draw->getPosition());
}
