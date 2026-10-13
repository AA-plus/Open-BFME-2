// ?rva002CBBF5@WeaponTemplate@@QAEXPAVObject@@HHH0HPBUCoord3D@@H_NPAVWeapon@@H@Z
// partial score=0.9973962532548357 date=2026-10-13
// W7-ASTRA bank, 2026-10-13: WeaponTemplate fire body, native 0x002CBBF5..0x002CC20E RET44.
// Identity lead: WorldBuilder 0xBB0E40 WeaponTemplate::fireWeaponTemplate;
// target evidence fixes the eleven-word ABI, fields/calls, and the differences from ZH Weapon.cpp.
// Whole owner integration: existing collision body at 0x002CBA7C (377B) stays byte-exact.
// Canonical Coord3D plus nontrivial derived scatter argument copy/dtor reproduces the scalar
// outgoing copies and ESP records without a private canonical-class replacement.
// Native virtual containment slot +0xF4 takes &victim->pos; the old bank omitted this argument.
// Named guarded containment receivers, sound and Pathfinder receiver reproduce retail load order.
// Volatile scatter removes the scalar's register competition and restores victim=EBX/position=EDI.
// Retail filename is bfme2patch103\\bfme2 (WB's shorter filename is not valid target evidence).
// Current full extent 1561B, all calls resolved, score .9973962532548357: only four instructions
// differ, two swaps: POP ECX/FSTP after atan2f at +0x225, and ESI/EDI reloads after first MOVSD copy.
// U1 chain and guarded beam, ABI/receiver/scalar grids and redundant bool-member rereads tried.
// Reject original generator's duplicated distance call and unconditional victim member hoist.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include /ICode/GameEngine/Source
//
// ?shouldProjectileCollideWith@WeaponTemplate@@QBE_NPBVObject@@00W4ObjectID@@@Z
// retail 0x002CBA7C, 377 bytes (Ghidra FUN_006cba7c, ret 0x10).
//
// Donor: Zero Hour / BFME 1 Weapon.cpp WeaponTemplate::shouldProjectileCollideWith
// (launcher, projectile, thingWeCollidedWith, intendedVictimID).
//
// Target evidence: four stack args; null projectile/thing guards; the
// intended victim id compare against Object +0x74; the launcher == thing and
// launcher->getContainedBy() (+0x274) == thing rejections; the sneaky
// targeting probe through the thing's AI (+0x258, vtable +0x200, NULL); the
// rowed Object::getRelationship (0x0028D156) mapping ALLIES/ENEMIES/NEUTRAL to
// collide bits 1/2/4; the STRUCTURE split on getControllingPlayer
// (0x0028AFA9) into 0x200/8; the ThingTemplate KindOf words at +0x108 and
// fence width at +0x4A0 feeding the SHRUBBERY/PROJECTILE/WALLS/SMALL_MISSILE/
// BALLISTIC_MISSILE bits; and the final test against the collide mask at
// this+0x118.
//
// BFME 2 differences (target evidence): the burned-thing rejection asks the
// rowed WeaponTemplate damage-type query 0x002CA9CA for type 6 with the
// launcher's current weapon (0x0028AEBD), inside the launcher block, and
// tests status 0xB; the airfield parking case is gone; a new KindOf bit 10
// adds collide bit 0x400; and a thing with KindOf bit 60 ignores a collision
// when the intended victim (TheGameLogic->findObjectByID) reports more than
// one from the rowed Object getter 0x0028B511.

#include "Lib/Coord3D.h"

struct WeaponScatterPoint : Coord3D
{
    ~WeaponScatterPoint() {}
    WeaponScatterPoint()
    {
    }
    WeaponScatterPoint(const Coord3D &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }
    WeaponScatterPoint(const WeaponScatterPoint &p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }
};
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "Common/GameLogicObjectLookupView.h"

enum WeaponSlotType
{
    PRIMARY_WEAPON
};

enum Relationship
{
    ENEMIES = 0,
    NEUTRAL = 1,
    ALLIES = 2
};

enum ObjectStatusTypes
{
    OBJECT_STATUS_BURNED = 0x0B
};

enum WeaponCollideMaskType
{
    WEAPON_COLLIDE_ALLIES = 0x0001,
    WEAPON_COLLIDE_ENEMIES = 0x0002,
    WEAPON_COLLIDE_NEUTRALS = 0x0004,
    WEAPON_COLLIDE_STRUCTURES = 0x0008,
    WEAPON_COLLIDE_SHRUBBERY = 0x0010,
    WEAPON_COLLIDE_PROJECTILE = 0x0020,
    WEAPON_COLLIDE_WALLS = 0x0040,
    WEAPON_COLLIDE_SMALL_MISSILES = 0x0080,
    WEAPON_COLLIDE_BALLISTIC_MISSILES = 0x0100,
    WEAPON_COLLIDE_CONTROLLED_STRUCTURES = 0x0200,
    WEAPON_COLLIDE_BFME2_400 = 0x0400
};

class Player;
class Object;
class FXList;
extern "C" float atan2f(float, float);
float GetGameLogicRandomValueReal(float, float, char *, int);
class Drawable
{
  public:
    bool handleWeaponFireFX(int, int, int, float, float, float, int);
};

class WeaponBody
{
  public:
    virtual void s000();
    virtual void s004();
    virtual void s008();
    virtual void s00C();
    virtual void s010();
    virtual void s014();
    virtual void s018();
    virtual void s01C();
    virtual void s020();
    virtual void s024();
    virtual void s028();
    virtual void s02C();
    virtual void s030();
    virtual void s034();
    virtual void s038();
    virtual void s03C();
    virtual void s040();
    virtual void s044();
    virtual void s048();
    virtual void s04C();
    virtual void s050();
    virtual void s054();
    virtual void s058();
    virtual void s05C();
    virtual void s060();
    virtual void s064();
    virtual void s068();
    virtual void s06C();
    virtual void s070();
    virtual void s074();
    virtual void s078();
    virtual void s07C();
    virtual void s080();
    virtual void s084();
    virtual void s088();
    virtual float s8C();
};
class WeaponContain
{
  public:
    virtual void s000();
    virtual void s004();
    virtual void s008();
    virtual void s00C();
    virtual void s010();
    virtual void s014();
    virtual void s018();
    virtual void s01C();
    virtual void s020();
    virtual void s024();
    virtual void s028();
    virtual void s02C();
    virtual void s030();
    virtual void s034();
    virtual void s038();
    virtual void s03C();
    virtual void s040();
    virtual void s044();
    virtual void s048();
    virtual void s04C();
    virtual void s050();
    virtual void s054();
    virtual void s058();
    virtual void s05C();
    virtual void s060();
    virtual void s064();
    virtual void s068();
    virtual void s06C();
    virtual void s070();
    virtual void s074();
    virtual void s078();
    virtual int s7C();
    virtual void s080();
    virtual void s084();
    virtual void s088();
    virtual void s08C();
    virtual void s090();
    virtual void s094();
    virtual void s098();
    virtual void s09C();
    virtual void s0A0();
    virtual void s0A4();
    virtual void s0A8();
    virtual void s0AC();
    virtual void s0B0();
    virtual void s0B4();
    virtual void s0B8();
    virtual void s0BC();
    virtual void s0C0();
    virtual void s0C4();
    virtual void s0C8();
    virtual void s0CC();
    virtual void s0D0();
    virtual void s0D4();
    virtual void s0D8();
    virtual void s0DC();
    virtual void s0E0();
    virtual void s0E4();
    virtual void s0E8();
    virtual void s0EC();
    virtual void s0F0();
    virtual Object *sF4(const Coord3D *);
};

class Thing
{
  public:
    Drawable *getDrawable() const;
};
struct TBridgeAttackInfo
{
    Coord3D point1, point2;
};
class TerrainLogic
{
  public:
    void getBridgeAttackPoints(const Object *, TBridgeAttackInfo *);
};
extern TerrainLogic *TheTerrainLogic;
class Pathfinder
{
  public:
    bool IsPointOnWall(int, bool);
};
class AI
{
  public:
    char pad[0x10];
    Pathfinder *pathfinder;
};
extern AI *TheAI;
class Rva002C9B80Owner
{
  public:
    float rva002C9B80(void *, float);
    bool isWithinAttackRange(Object *, const Coord3D *, Object *, const Coord3D *, float, bool);
};
class Weapon
{
  public:
    char pad[0x30];
    unsigned fxUntil;
    char pad34[0x50 - 0x34];
    unsigned rangeUntil;
};
class FXList
{
  public:
    static void doFXObj(const FXList *, const Object *, const Object *);
};
class WeaponNugget
{
  public:
    virtual void s000();
    virtual bool s04(Weapon *, Object *);
    virtual bool s08(Weapon *, const Coord3D *);
    virtual void s00C();
    virtual void s010();
    virtual void s14(Weapon *, Object *);
    virtual void s18(Weapon *, const Coord3D *);
    virtual void s01C();
    virtual void s020();
    virtual void s024();
    virtual void s028();
    virtual void s02C();
    virtual bool s30();
};
struct WeaponNuggetNode
{
    WeaponNuggetNode *next, *prev;
    WeaponNugget *nugget;
};

class Weapon;
struct Coord3D;

class ThingTemplate
{
  public:
    // KindOf words: 0x80 STRUCTURE, 0x40 SHRUBBERY, 0x2000000 PROJECTILE, 0x400 (BFME 2) in
    // word 0; 0x100000 SMALL_MISSILE, 0x10000000 (BFME 2) in word 1; 0x800 BALLISTIC_MISSILE in word 2.
    UnsignedInt testKindOf(Int word, UnsignedInt mask) const
    {
        return m_kindOf[word] & mask;
    }
    unsigned char kindByte(int i) const
    {
        return ((const unsigned char *)m_kindOf)[i];
    }
    __declspec(dllimport) __forceinline Real getFenceWidth() const
    {
        return m_fenceWidth;
    }

  private:
    char m_pad000[0x108];
    UnsignedInt m_kindOf[4]; // +0x108
    char m_pad118[0x4A0 - 0x118];
    Real m_fenceWidth; // +0x4A0
};

class AIUpdateInterface
{
  public:
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual int s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual Bool getSneakyTargetingOffset(Coord3D *offset) const; // +0x200
};

class Object
{
  public:
    const ThingTemplate *getTemplate() const
    {
        return m_template;
    }
    ObjectID getID() const
    {
        return m_id;
    }
    Object *getContainedBy() const
    {
        return m_containedBy;
    }
    AIUpdateInterface *getAI() const
    {
        return m_ai;
    }
    Bool testStatus(ObjectStatusTypes bit) const;
    Relationship getRelationship(const Object *that) const;
    Player *getControllingPlayer() const;
    const Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0) const;
    Int rva0028B511() const;
    float rva002C97E8(const Coord3D *, const Coord3D *) const;
    float rva00263763(const void *) const;
    bool rva0028F44C(const Object *) const;
    bool isLocallyControlled() const;
    bool rva002943B2(const Player *);

  public:
    void *m_vtbl;
    const ThingTemplate *volatile m_template;
    char m_pad008[0x38 - 8];
    Coord3D pos;
    char m_pad044[0x74 - 0x44];
    ObjectID m_id; // +0x74
    char m_pad078[0x250 - 0x78];
    WeaponContain *contain250;
    WeaponBody *body254;
    AIUpdateInterface *m_ai; // +0x258
    char m_pad25C[0x274 - 0x25C];
    Object *m_containedBy; // +0x274
};

extern GameLogic *TheGameLogic;

class Rva002CA9CA
{
  public:
    Bool rva002CA9CA(Int damageType, const void *weapon);
};

class WeaponTemplate
{
  public:
    Bool isDamageType(Int damageType, const Weapon *weapon) const
    {
        return ((Rva002CA9CA *)this)->rva002CA9CA(damageType, weapon);
    }
    __declspec(dllimport) __forceinline Int getProjectileCollideMask() const
    {
        return m_projectileCollideMask;
    }

    Bool shouldProjectileCollideWith(const Object *projectileLauncher, const Object *projectile,
                                     const Object *thingWeCollidedWith,
                                     ObjectID intendedVictimID) const;

  public:
    void rva002CBBF5(Object *, int, int, int, Object *, int, const Coord3D *, int, bool, Weapon *,
                     int);
    float getMinimumAttackRange() const;
    Coord3D *getAimPosition(Coord3D *, const Object *, const Object *, int);
    Coord3D bfmeCalcScatterTargetPos(const Object *, const Object *, Coord3D);
    char pad00[0x3C];
    bool eachNugget3C, wall3D;
    char pad3E[0x68 - 0x3E];
    float sound68;
    char pad6C[0x75 - 0x6C];
    bool dodge75;
    char pad76[0x84 - 0x76];
    float pitch84;
    char pad88[0xA4 - 0x88];
    FXList *fxA4;
    char padA8[0xB4 - 0xA8];
    FXList *fxB4;
    char padB8[0x118 - 0xB8];
    Int m_projectileCollideMask;
    bool self11C;
    char pad11D[0x135 - 0x11D];
    bool localFX135;
    char pad136[0x14C - 0x136];
    float infantry14C;
    char pad150[8];
    float chance158, chance15C;
    char pad160[0x17C - 0x160];
    WeaponNuggetNode *nuggets;
};

//-------------------------------------------------------------------------------------------------
Bool WeaponTemplate::shouldProjectileCollideWith(
    const Object *projectileLauncher, const Object *projectile, const Object *thingWeCollidedWith,
    ObjectID intendedVictimID // could be INVALID_OBJECT_ID for a position-shot
) const
{
    if (!projectile || !thingWeCollidedWith)
        return false;

    // if it's our intended victim, we want to collide with it, regardless of any of the subsequent checks.
    if (intendedVictimID == thingWeCollidedWith->getID())
        return true;

    if (projectileLauncher != 0)
    {
        // Don't hit your own launcher, ever.
        if (projectileLauncher == thingWeCollidedWith)
            return false;

        // If our launcher is inside something, and that something is 'thingWeCollidedWith' we won't collide
        const Object *launcherContainedBy = projectileLauncher->getContainedBy();
        if (launcherContainedBy == thingWeCollidedWith)
            return false;

        // never bother burning already-burned things. (srj)
        if (isDamageType(6, projectileLauncher->getCurrentWeapon()))
        {
            if (thingWeCollidedWith->testStatus(OBJECT_STATUS_BURNED))
                return false;
        }
    }

    // if something has a Sneaky Target offset, it is momentarily immune to being hit...
    const AIUpdateInterface *ai = thingWeCollidedWith->getAI();
    if (ai != 0 && ai->getSneakyTargetingOffset(0))
        return false;

    Int requiredMask = 0;

    Relationship r = projectile->getRelationship(thingWeCollidedWith);
    if (r == ALLIES)
        requiredMask = WEAPON_COLLIDE_ALLIES;
    else if (r == ENEMIES)
        requiredMask = WEAPON_COLLIDE_ENEMIES;
    else if (r == NEUTRAL)
        requiredMask = WEAPON_COLLIDE_NEUTRALS;

    if (thingWeCollidedWith->getTemplate()->testKindOf(0, 0x80))
    {
        if (thingWeCollidedWith->getControllingPlayer() == projectile->getControllingPlayer())
            requiredMask |= WEAPON_COLLIDE_CONTROLLED_STRUCTURES;
        else
            requiredMask |= WEAPON_COLLIDE_STRUCTURES;
    }

    const ThingTemplate *tmpl = thingWeCollidedWith->getTemplate();
    if (tmpl->testKindOf(0, 0x40))
        requiredMask |= WEAPON_COLLIDE_SHRUBBERY;
    if (tmpl->testKindOf(0, 0x2000000))
        requiredMask |= WEAPON_COLLIDE_PROJECTILE;
    if (tmpl->getFenceWidth() > 0)
        requiredMask |= WEAPON_COLLIDE_WALLS;
    if (tmpl->testKindOf(1, 0x100000))
        requiredMask |= WEAPON_COLLIDE_SMALL_MISSILES;
    if (tmpl->testKindOf(2, 0x800))
        requiredMask |= WEAPON_COLLIDE_BALLISTIC_MISSILES;
    if (tmpl->testKindOf(0, 0x400))
        requiredMask |= WEAPON_COLLIDE_BFME2_400;

    // if any in requiredMask are present in collidemask, do the collision. (srj)
    if ((getProjectileCollideMask() & requiredMask) == 0)
        return false;

    if (tmpl->testKindOf(1, 0x10000000) && intendedVictimID != INVALID_OBJECT_ID)
    {
        Object *victim = TheGameLogic->findObjectByID(intendedVictimID);
        if (victim && victim->rva0028B511() > 1)
            return false;
    }

    return true;
}

void WeaponTemplate::rva002CBBF5(Object *source, int wordC, int barrel, int word14, Object *victim, int word1C, const Coord3D *position, int word24, bool ignore, Weapon *weapon, int word30)
{
    if (!source || (!victim && !position)) return;
    const Coord3D *sourcePos=&source->pos;
 float distance;
    Coord3D shifted;
    TBridgeAttackInfo bridge;
    if (victim)
    {
        position = &victim->pos;
        Coord3D offset;
        const AIUpdateInterface *ai = victim->getAI();
        if (ai && ai->getSneakyTargetingOffset(&offset))
        {
            shifted = *position;
            shifted.x += offset.x;
            shifted.y += offset.y;
            shifted.z += offset.z;
            position = &shifted;
            victim = 0;
            distance = source->rva002C97E8(sourcePos, position);
        }
        else if (victim->getTemplate()->kindByte(2) & 0x40)
        {
            TheTerrainLogic->getBridgeAttackPoints(victim, &bridge);
            distance = source->rva002C97E8(sourcePos, &bridge.point1);
            float other = source->rva002C97E8(sourcePos, &bridge.point2);
            if (other < distance)
            {
                distance = other;
                position = &bridge.point2;
            }
        }
        else
            distance = source->rva00263763(victim);
    }
    else
        distance = source->rva002C97E8(sourcePos, position);
    if (!ignore && weapon->rangeUntil <= TheGameLogic->getFrame())
    {
        float range =
            ((Rva002C9B80Owner *)weapon)->rva002C9B80(source, position->z - source->pos.z);
        if (distance > range * range &&
            !((Rva002C9B80Owner *)weapon)
                 ->isWithinAttackRange(source, sourcePos, victim, position, 0.f, true))
            return;
        float minimum = getMinimumAttackRange();
        if (distance < minimum * minimum)
            return;
    }
    if (((const Thing *)source)->getDrawable())
    {
        Coord3D firePosition;
        if (victim)
        {
            Coord3D adjusted;
            firePosition = *getAimPosition(&adjusted, source, victim, 1);
        }
        else
        {
            firePosition.x = position->x;
            firePosition.y = position->y;
            firePosition.z = position->z;
        }
        float pitch = pitch84;
        float heading;
        if(pitch != 0.f)
        {
            heading=atan2f(position->y - source->pos.y, position->x - source->pos.x);
        }
        else
            heading=0.f;
        FXList *fx = 0;
        if (victim && victim->rva0028F44C(source))
            fx = fxB4;
        if (!fx)
            fx = fxA4;
        if (TheGameLogic->getFrame() < weapon->fxUntil)
            fx = 0;
        if (source->isLocallyControlled() || !source->rva002943B2(0) || localFX135)
        {
            float sound=sound68;
            if (!((const Thing *)source)
                     ->getDrawable()
                     ->handleWeaponFireFX(barrel, word14, (int)fx, sound, pitch, heading,
                                          (int)&firePosition) &&
                fx)
                FXList::doFXObj(fx, source, victim);
        }
    }
    float oldZ = position->z;
    if (self11C)
    {
        position = sourcePos;
        victim = 0;
    }
    const Coord3D *aim = position ? position : &victim->pos;
    typedef Coord3D (WeaponTemplate::*ScatterFn)(const Object *, const Object *,
                                                 WeaponScatterPoint);
    ScatterFn scatterFn = reinterpret_cast<ScatterFn>(&WeaponTemplate::bfmeCalcScatterTargetPos);
    Coord3D target;
    target.x = aim->x;
    target.y = aim->y;
    target.z = aim->z;
    if (self11C && source->m_ai->s097())
        target.z = oldZ;
    volatile bool scatter = false;
    Pathfinder *pathfinder;
    if (infantry14C > 0.f && victim && (victim->getTemplate()->kindByte(1) & 1) &&
        (!wall3D || !(pathfinder=TheAI->pathfinder, pathfinder->IsPointOnWall((int)&victim->pos, false))))
        scatter = true;
    char *filename =
        "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Weapon."
        "cpp";
    if (chance158 < 1.f)
    {
        float chance = chance158;
        if (GetGameLogicRandomValueReal(0, 1, filename, 0x5D1) >= chance)
            scatter = true;
    }
    if (dodge75 && victim && victim->body254->s8C() > 0.f)
    {
        WeaponBody *body = victim->body254;
        float random = GetGameLogicRandomValueReal(0, 1, filename, 0x5D7);
        if (body->s8C() >= random)
            scatter = true;
    }
    bool useContained = false;
    if (!scatter && victim)
    {
        WeaponContain *contain=victim->contain250;
        if(contain && !contain->s7C() && chance15C > 0.f)
    {
        float chance = chance15C;
        if (chance >= GetGameLogicRandomValueReal(0, 1, filename, 0x5E1))
        {
            useContained = true;
            scatter = false;
        }
    }
    }
    if (eachNugget3C)
    {
        for (WeaponNuggetNode *it = nuggets->next; it != nuggets; it = it->next)
        {
            WeaponNugget *nugget = it->nugget;
            if (scatter)
            {
                target = (this->*scatterFn)(source, victim, WeaponScatterPoint(target));
                victim = 0;
            }
            if (nugget->s08(weapon, &target))
                nugget->s18(weapon, &target);
        }
    }
    else
    {
        if (scatter)
        {
            target = (this->*scatterFn)(source, victim, WeaponScatterPoint(target));
            victim = 0;
        }
        else if(useContained == true)
        {
            WeaponContain *contain=victim->contain250;
            if(contain) {
                Object *inside=contain->sF4(&victim->pos);
                if(inside) victim=inside;
            }
        }
        for (WeaponNuggetNode *it = nuggets->next; it != nuggets; it = it->next)
        {
            WeaponNugget *nugget = it->nugget;
            if (victim && !nugget->s30())
            {
                if (nugget->s04(weapon, victim))
                    nugget->s14(weapon, victim);
            }
            else if (nugget->s08(weapon, &target))
                nugget->s18(weapon, &target);
        }
    }
}
