// ?create@GenericObjectCreationNugget@@QBEXPBVObject@@PBUCoord3D@@1I@Z
// partial score=0.7 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /ICode/Libraries/Include /DNDEBUG /MD /EHsc
//
// GenericObjectCreationNugget members that gate and forward a create (retail
// 0x001F1513 and 0x001F14B6; ObjectCreationList.cpp in the debug build).
// The nugget keeps two upgrade-name lists, +0x114 and +0x120, 4-byte
// AsciiString entries each (the dtor TU's three tail vectors).
//
//   rva001F1513  the object may be created for: no +0x120 upgrade is
//                present on the primary or its player, and when the
//                +0x114 list is not empty at least one of its upgrades is
//   create       slot 2 of the nugget vftable (the object-pair create):
//                skip airborne primaries when +0xAF is set, check the
//                upgrades, then really create at the primary's position
//                (+0x38), transform (+0x08) and orientation (+0x44) and
//                drop the result
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include <math.h>

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum AICommandType { AICMD_MOVE_TO_POSITION = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0 };
class Module;
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
struct AICommandParms {
 AICommandParms(AICommandType, CommandSourceType);
 ~AICommandParms();
 int command, source;
 Coord3D position;
 char remaining[0xC0 - 0x14];
};
class AICommandInterface { public: virtual void aiDoCommand(const AICommandParms *); };
class StrafeAreaUpdate { public: bool rva003A4F21(const Coord3D *, const Coord3D *); };
class Thing { public: void setOrientation(float); };
float normalizeAngle(float);

class Player;

class Rva002AA8BF
{
public:
	bool testBit(int bit) const;
};

class Object
{
public:
	bool rva0028D9E5(int bit) const;
	Player *getControllingPlayer() const;
	bool isSignificantlyAboveTerrain() const;
	char m_pad00[0x38];
	float m_position[3];	// +0x38
	float m_pad44;		// +0x44 orientation
 char m_pad48[0x258 - 0x48];
 void *ai;
protected:
 Module *findModule(NameKeyType) const;
 friend class GenericObjectCreationNugget;
};

class UpgradeTemplate
{
public:
	char m_pad00[0x38];
	int m_38;		// +0x38 the bit the object and player test
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

struct NuggetNameList
{
	unsigned int size() const { return m_end - m_begin; }
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Coord3D;
class Matrix3D;

// reallyCreate's by-value result: three words torn down through the 5-byte
// thunk at 0x001F22A3.
struct NuggetCreated
{
	~NuggetCreated();
	Object **begin, **end, **capacity;
 unsigned int size() const { return end - begin; }
};

class GenericObjectCreationNugget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
	void create(const Object *primaryObj, const Coord3D *primary, const Coord3D *secondary, unsigned int lifetimeFrames) const;
 bool rva001F1513(const Object *obj) const;
	NuggetCreated reallyCreate(const Coord3D *pos, const Matrix3D *transform, float orientation,
		const Object *sourceObj, unsigned int lifetimeFrames) const;	// 0x001F1634
private:
	char m_pad04[0xAF - 4];
	bool m_skipIfSignificantlyAirborne;	// +0xAF
	char m_padB0[0x100 - 0xB0];
 bool m_moveToSecondary; // +100
 bool m_inheritOrientation; // +101
 bool m_faceSecondary; // +102
 bool m_strafe; // +103
 float m_orientationOffset; // +104
 char m_pad108[8];
 bool m_inheritTransform; // +110
 char m_pad111[3];
	NuggetNameList m_114;	// +0x114
	NuggetNameList m_120;	// +0x120
};

bool GenericObjectCreationNugget::rva001F1513(const Object *obj) const
{
	for (unsigned int i = 0; i < m_120.size(); ++i) {
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_120.m_begin[i]);
		if (upgrade) {
			int bit = upgrade->m_38;
			if (obj->rva0028D9E5(bit))
				return false;
			if (((Rva002AA8BF *)obj->getControllingPlayer())->testBit(bit))
				return false;
		}
	}
	if (m_114.size() == 0)
		return true;
	for (unsigned int i = 0; i < m_114.size(); ++i) {
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(m_114.m_begin[i]);
		if (upgrade) {
			int bit = upgrade->m_38;
			if (obj->rva0028D9E5(bit))
				return true;
			if (((Rva002AA8BF *)obj->getControllingPlayer())->testBit(bit))
				return true;
		}
	}
	return false;
}

void GenericObjectCreationNugget::create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const
{
	if (primary) {
		if (m_skipIfSignificantlyAirborne && primary->isSignificantlyAboveTerrain())
			return;
		if (rva001F1513(primary))
			reallyCreate((const Coord3D *)primary->m_position, (const Matrix3D *)((const char *)primary + 8),
				primary->m_pad44, primary, lifetimeFrames);
	}
}

// Native 001F2F0E..001F311B (525B); WB B03C80 names this create overload.
// ZH/BF1 provide the creation spine; secondary movement and strafe handling
// are reconstructed from BFME2. Flag names describe observed behavior only.
void GenericObjectCreationNugget::create(const Object *primaryObj,
 const Coord3D *primary, const Coord3D *secondary, unsigned int lifetimeFrames) const
{
 if (primaryObj && !rva001F1513(primaryObj)) return;
 if (!primary) return;
 float orientation = 0.0f;
 const Matrix3D *transform = 0;
 if (m_inheritOrientation) orientation = m_orientationOffset + primaryObj->m_pad44;
 if (m_inheritTransform) transform = (const Matrix3D *)((const char *)primaryObj + 8);
 NuggetCreated created = reallyCreate(primary, transform, orientation, primaryObj, lifetimeFrames);
 if (secondary && m_moveToSecondary) {
   for (unsigned int i = 0; i < created.size(); ++i) {
    Object *object = created.begin[i];
    if (!object || !object->ai) continue;
    if (m_strafe) {
     static const NameKeyType key = TheNameKeyGenerator->nameToKey("StrafeAreaUpdate");
     StrafeAreaUpdate *strafe = (StrafeAreaUpdate *)object->findModule(key);
     if (strafe && strafe->rva003A4F21(primary, secondary)) continue;
    }
    AICommandInterface *ai = (AICommandInterface *)((char *)object->ai + 0x20);
    AICommandParms command(AICMD_MOVE_TO_POSITION, CMD_FROM_PLAYER);
    command.position = *secondary;
    ai->aiDoCommand(&command);
   }
  }
  if (secondary && m_faceSecondary) {
   for (unsigned int i = 0; i < created.size(); ++i) {
    Object *object = created.begin[i];
    if (object) {
     float dx = secondary->x - object->m_position[0];
     float dy = secondary->y - object->m_position[1];
     ((Thing *)object)->setOrientation(normalizeAngle(atan2((double)dy, (double)dx) + m_orientationOffset));
    }
   }
  }
}
