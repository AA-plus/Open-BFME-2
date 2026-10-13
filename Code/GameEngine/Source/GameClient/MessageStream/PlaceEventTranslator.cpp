// cl: /O1 /G7 /arch:SSE /I. /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /MD /ICode/Libraries/Include /ICode/GameEngine/Source/Common /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// PlaceEventTranslator::translateGameMessage, retail 0x0043218A (1701 bytes).
//
// Semantic guide: Zero Hour GeneralsMD PlaceEventTranslator.cpp (left-button
// down anchors a placement, click/double-click places, raw mouse position
// drags the anchor). BFME 2 adds the click-tracking cases 14/16/27/28, the
// build-port path (isBuildPort / canPlacePort / getPortTransform) and the
// ghost-object overlap check. Case order, locals and their scopes follow the
// WorldBuilder debug twin at WB 0x012C88F0: its EH states show that BFME 2's
// Coord3D has a constructor and a destructor (state per world/newWorld
// object), which is what places retail's frame (0x74, newWorld beside the
// left-button world, newAngle in the message parameter slot).
#include <list>
#include <math.h>
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Common/BfmeAudioEventPrefix136.h"

extern GameLogic *TheGameLogic;

// ICoord2D; the rowed drag test below spells it with its address-derived name.
struct Rva001EDD80Pair
{
	int x, y;
};
typedef Rva001EDD80Pair ICoord2D;
// Give local pixel coordinates a lexical lifetime just as PlaceCoord does.
// The empty destructor emits no work. It preserves retail's overlapping
// mouse/anchor and build/builder spill homes with the canonical GameLogic API.
// Message union storage retains the plain two-int layout above.
struct PlacePixel : ICoord2D
{
    PlacePixel() {}
    PlacePixel(const ICoord2D &p) { x = p.x; y = p.y; }
    ~PlacePixel() {}
};

// Mouse::rva001EDD80 (0x001EDD80): the drag-distance test against the button-down position.
class Mouse
{
public:
	bool rva001EDD80(const ICoord2D *from, const ICoord2D *to);
	char m_pad[0x12F0];
	unsigned int m_doubleClickTime;
};
extern Mouse *TheMouse;

class Drawable;
class DrawableList : public _STL::list<Drawable *>
{
public:
	__forceinline DrawableList() {}
	~DrawableList() throw();
};

// BFME 2's Coord3D shape for locals and by-value arguments: empty default
// constructor and destructor, member-wise copy constructor (the WWMath owner
// view in coord3d.cpp).
struct PlaceCoord : Coord3D
{
	PlaceCoord() {}
	PlaceCoord(const PlaceCoord &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	~PlaceCoord() {}
};

class PickAndPlayInfo
{
public:
	PickAndPlayInfo();
	bool m_air;
	Drawable *m_drawTarget;
	void *m_weaponSlot;
	int m_specialPowerType;
	unsigned int m_unknown10;
	Coord3D m_position;
	unsigned int m_unknown20;
};

class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }
	char m_pad[0x54];
	int m_playerIndex;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Drawable *getDrawable() const;
	char m_pad[0x38];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
};

class ThingTemplate
{
public:
	char m_pad[0x11F];
	unsigned char m_kindOfByte23; // KindOf bits 184..191; 0x10 is bit 188
	char m_pad120[0x5D8 - 0x120];
	unsigned short m_templateID;
};

union GameMessageArgumentType
{
	int integer;
	ICoord2D pixel;
};

class GameMessage
{
public:
	enum Type
	{
		MSG_DOZER_CONSTRUCT = 0x41A,
		MSG_PORT_CONSTRUCT = 0x463,
		MSG_CANNOT_BUILD_VOICE = 0x7EB
	};
	const GameMessageArgumentType *getArgument(int index) const;
	void appendIntegerArgument(int value);
	void appendLocationArgument(const Coord3D &value);
	void appendRealArgument(float value);
	void appendObjectIDArgument(ObjectID value);
	Type getType() const { return m_type; }
	char m_pad[0x10];
	Type m_type;
};

void pickAndPlayUnitVoiceResponse(const DrawableList *list, GameMessage::Type msgType, PickAndPlayInfo *info);

// The rowed ghost-object overlap test (0x0030596C) takes the position by
// value; its owner unit declares a plain Coord3D, retail's call site builds
// the argument with BFME 2's member-wise copy constructor.
bool Rva0030596CIntersects(void *thing, Coord3D pos, float angle);
typedef bool (__cdecl *PlacementIntersects)(void *thing, PlaceCoord pos, float angle);

#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
struct PlacementOptions
{
	char m_pad[0x1C];
	int m_value;
};

class InGameUI
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14)
	virtual void message(AsciiString format, ...); // 0x3C
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24)
	virtual void displayCantBuildMessage(int lbc); // 0x64
	V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46)
	virtual void clearMode(bool b); // 0xBC
	virtual PlacementOptions *getOptions(); // 0xC0
	V(49) V(50) V(51) V(52) V(53) V(54)
	virtual void placeBuildAvailable(const ThingTemplate *build, const Object *buildDozer); // 0xDC
	virtual const ThingTemplate *getPendingPlaceType(); // 0xE0
	virtual ObjectID getPendingPlaceSourceObjectID(); // 0xE4
	virtual void setPlacementStart(const ICoord2D *start); // 0xE8
	virtual void setPlacementEnd(const ICoord2D *end); // 0xEC
	virtual bool isPlacementAnchored(); // 0xF0
	virtual void getPlacementPoints(ICoord2D *start, ICoord2D *end); // 0xF4
	virtual float getPlacementAngle(); // 0xF8
	virtual bool canPlacePort(); // 0xFC
	virtual void clearPlacementPort(bool b); // 0x100
	virtual void resetPlacementPort(); // 0x104
	V(66) V(67) V(68) V(69) V(70) V(71) V(72)
	virtual DrawableList *getAllSelectedDrawables(); // 0x124
	V(74) V(75) V(76) V(77) V(78) V(79) V(80)
	virtual void setRadiusCursorNone(); // 0x144
};
extern InGameUI *TheInGameUI;

class View
{
public:
	V10(0) V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7) V10(8)
	virtual void screenToTerrain(const ICoord2D *screen, Coord3D *world, bool b); // 0x168
};
extern View *TheTacticalView;

class BuildAssistant
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	virtual int isLocationLegalToBuild(const Coord3D *worldPos, const ThingTemplate *build, float angle,
		int options, Object *builderObject, Object *player); // 0x40
	V(17) V(18) V(19) V(20) V(21) V(22)
	virtual bool isBuildPort(const ThingTemplate *build, Object *builderObject); // 0x5C
	virtual int canMakeUnit(Object *builder, const ThingTemplate *build, int count); // 0x60
	void getPortTransform(const Coord3D *worldPos, const ThingTemplate *build, float angle,
		float *newAngle, Coord3D *newPos);
};
extern BuildAssistant *TheBuildAssistant;

class GhostObjectManager
{
public:
	char m_pad[4];
	int m_localPlayerIndex;
};
extern GhostObjectManager *TheGhostObjectManager;

class MessageStream
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
	virtual GameMessage *appendMessage(GameMessage::Type type); // 0x48
};
extern MessageStream *TheMessageStream;

struct MiscAudio
{
	char m_pad[0xE8];
	OpaqueRefElement4 m_noCanDoSound;
};

class AudioManager
{
public:
	V10(0) V10(1) V(20) V(21) V(22) V(23) V(24)
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *eventToAdd); // 0x64
	V(26) V(27) V(28) V(29) V10(3) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49)
	V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64)
	V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77)
	virtual MiscAudio *getMiscAudio(); // 0x138
};
extern AudioManager *TheAudio;
#undef V10
#undef V

enum GameMessageDisposition
{
	KEEP_MESSAGE = 0,
	DESTROY_MESSAGE = 1
};

class PlaceEventTranslator
{
public:
	virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
	ICoord2D m_downPos;
	unsigned int m_downFrame;
	unsigned int m_upFrame;
	bool m_isDown;
	bool m_isDragging;
};

GameMessageDisposition PlaceEventTranslator::translateGameMessage(const GameMessage *msg)
{
	GameMessageDisposition disp = KEEP_MESSAGE;

	switch (msg->getType())
	{
	case 4: // left button down
	{
		// if we're in a building placement mode, set the placement anchor
		const ThingTemplate *build = TheInGameUI->getPendingPlaceType();
		if (build && TheInGameUI->isPlacementAnchored() == false)
		{
			PlacePixel mouse = msg->getArgument(0)->pixel;
			PlaceCoord world;

			TheTacticalView->screenToTerrain(&mouse, &world, false);

			// if our source object is gone cancel this whole placement process
			Object *builderObject = TheGameLogic->findObjectByID(TheInGameUI->getPendingPlaceSourceObjectID());
			if (builderObject == 0)
			{
				TheInGameUI->placeBuildAvailable(0, 0);
				break;
			}

			TheInGameUI->setPlacementStart(&mouse);
			disp = DESTROY_MESSAGE;
		}
		break;
	}

	case 14: // raw left button down: remember where and when
		m_downPos = msg->getArgument(0)->pixel;
		m_downFrame = msg->getArgument(2)->integer;
		m_isDown = true;
		m_isDragging = false;
		break;

	case 16: // raw left button up
		if (m_isDown)
		{
			m_upFrame = msg->getArgument(2)->integer;
			m_isDown = false;
		}
		break;

	case 27:
	case 28: // right click: cancel the placement unless it ended a long drag
		if (TheInGameUI->getPendingPlaceType())
		{
			bool cancel = true;
			if (m_isDragging && m_upFrame - m_downFrame >= TheMouse->m_doubleClickTime)
				cancel = false;
			if (cancel)
			{
				TheInGameUI->clearMode(false);
				TheInGameUI->placeBuildAvailable(0, 0);
				disp = DESTROY_MESSAGE;
			}
		}
		break;

	case 23:
	case 24: // left click / double click: place the anchored building
	{
		const ThingTemplate *pendingBuild = TheInGameUI->getPendingPlaceType();

		// ... and also remove any radius cursor that is active.
		TheInGameUI->setRadiusCursorNone();

		if (pendingBuild && TheInGameUI->isPlacementAnchored())
		{
			// Reuse the pending template through the active placement path.
			// Its native pointer spills remain exact with the shared GameLogic API.
			GameMessage *placeMsg;
			PlaceCoord world;
			float angle;
			PlacePixel anchorStart, anchorEnd;

			angle = TheInGameUI->getPlacementAngle();
			TheInGameUI->getPlacementPoints(&anchorStart, &anchorEnd);
			TheTacticalView->screenToTerrain(&anchorStart, &world, false);

			Object *builderObj = TheGameLogic->findObjectByID(TheInGameUI->getPendingPlaceSourceObjectID());
			bool isPort = TheBuildAssistant->isBuildPort(pendingBuild, builderObj);

			// make sure we can still afford and queue it
			int cmt = TheBuildAssistant->canMakeUnit(builderObj, pendingBuild, -1);
			if (cmt != 0 && cmt != 1)
			{
				if (cmt == 2)
				{
					TheInGameUI->message("GUI:NotEnoughMoneyToBuild");
					break;
				}
				else if (cmt == 4)
				{
					TheInGameUI->message("GUI:ProductionQueueFull");
					break;
				}
				else if (cmt == 5)
				{
					TheInGameUI->message("GUI:ParkingPlacesFull");
					break;
				}
				else if (cmt == 6)
				{
					TheInGameUI->message("GUI:UnitMaxedOut");
					break;
				}
				// get out of pending placement mode, this will also clear the arrow anchor status
				TheInGameUI->placeBuildAvailable(0, 0);
				break;
			}

			// check to see if this is a legal location to build something at
			int lbc = -1;
			if (isPort)
				lbc = 0;
			else
				lbc = TheBuildAssistant->isLocationLegalToBuild(&world, pendingBuild, angle, 0x49F, builderObj, 0);

			// the local player may not build over a ghost object it remembers
			if (builderObj)
			{
				int localIndex = TheGhostObjectManager->m_localPlayerIndex;
				if (localIndex == builderObj->getControllingPlayer()->getPlayerIndex())
				{
					if (((PlacementIntersects)Rva0030596CIntersects)((void *)pendingBuild, world, angle))
						lbc = 8;
				}
			}

			bool portBlocked = false;
			if (isPort && !TheInGameUI->canPlacePort())
			{
				TheInGameUI->setPlacementStart(0);
				portBlocked = true;
			}

			if (lbc == 0 && !portBlocked)
			{
				if (pendingBuild->m_kindOfByte23 & 0x10)
				{
					PlaceCoord newWorld;
					float newAngle;
					TheBuildAssistant->getPortTransform(&world, pendingBuild, angle, &newAngle, &newWorld);
					angle = newAngle;
					world = newWorld;
				}

				if (TheBuildAssistant->isBuildPort(pendingBuild, builderObj))
				{
					if (TheInGameUI->canPlacePort())
					{
						placeMsg = TheMessageStream->appendMessage(GameMessage::MSG_PORT_CONSTRUCT);
						placeMsg->appendIntegerArgument(pendingBuild->m_templateID);
						placeMsg->appendLocationArgument(builderObj->m_position);
						placeMsg->appendLocationArgument(world);
						TheInGameUI->clearPlacementPort(false);
						TheInGameUI->resetPlacementPort();
						int value = 0xFFFFFE;
						PlacementOptions *options = TheInGameUI->getOptions();
						if (options)
							value = options->m_value;
						placeMsg->appendIntegerArgument(value);
						placeMsg->appendObjectIDArgument(builderObj->m_id);
					}
				}
				else
				{
					placeMsg = TheMessageStream->appendMessage(GameMessage::MSG_DOZER_CONSTRUCT);
					placeMsg->appendIntegerArgument(pendingBuild->m_templateID);
					placeMsg->appendLocationArgument(world);
					placeMsg->appendRealArgument(angle);
					pickAndPlayUnitVoiceResponse(TheInGameUI->getAllSelectedDrawables(), placeMsg->getType(), 0);
					TheInGameUI->clearPlacementPort(false);
					TheInGameUI->resetPlacementPort();
				}

				// get out of pending placement mode, this will also clear the arrow anchor status
				TheInGameUI->clearMode(false);
				TheInGameUI->placeBuildAvailable(0, 0);
			}
			else
			{
				if (portBlocked)
				{
					disp = DESTROY_MESSAGE;
					break;
				}

				// can't place, display why
				TheInGameUI->displayCantBuildMessage(lbc);

				// cannot build here -- play the voice sound from the builder
				DrawableList list;
				list.push_back(builderObj->getDrawable());
				PickAndPlayInfo info;
				info.m_position = world;
				pickAndPlayUnitVoiceResponse(&list, GameMessage::MSG_CANNOT_BUILD_VOICE, &info);

				// play a can't do that sound (UI beep type sound)
				static BfmeAudioEventPrefix136 noCanDoSound(TheAudio->getMiscAudio()->m_noCanDoSound, 0);
				TheAudio->addAudioEvent(&noCanDoSound);

				// unhook the anchor so they can try again
				TheInGameUI->setPlacementStart(0);
			}

			// used the input
			disp = DESTROY_MESSAGE;
		}
		break;
	}

	case 3: // raw mouse position
	{
		PlacePixel mouse = msg->getArgument(0)->pixel;
		if (m_isDown && TheMouse->rva001EDD80(&m_downPos, &mouse))
			m_isDragging = true;

		// if a building placement is in progress update the destination position
		if (TheInGameUI->isPlacementAnchored())
		{
			ICoord2D start;
			TheInGameUI->getPlacementPoints(&start, 0);

			int x, y;
			x = mouse.x - start.x;
			y = mouse.y - start.y;
			float dist = (float)sqrt((double)(x * x + y * y));
			if (dist >= 5.0f)
			{
				TheInGameUI->setPlacementEnd(&mouse);
				disp = DESTROY_MESSAGE;
			}
		}
		break;
	}
	}

	return disp;
}
