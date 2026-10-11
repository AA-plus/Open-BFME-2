// ?update@DualWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9 date=2026-10-11
// cl: /O1 /Ob2 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// Native 0045AF14..0045B123, 527B; WB 0117D920, UpdateModule interface at +10.
// DualWeaponBehavior identity and settings come from the named module factory,
// the matched ctor and parse table C41858. BFME1 9e3be919b10a's clean ctor
// confirms the 20-byte UpdateModule and eight-byte derived state; no clean
// update donor was found. Control flow, offsets and calls below are target evidence.
#include <math.h>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };
enum WeaponSetType { WEAPONSET_CLOSE = 7 };
enum KindOfType { KIND_UNKNOWN = 0 };
class Object;
class AIUpdateInterface { public: Object *getCurrentVictim() const; };
class Rva0028B7AELeaGetter { public: void *get() const; };
struct DualWeaponFlags {
    unsigned int words[4];
    __forceinline bool test(unsigned i) const { return (words[i>>5] >> (i&31)) & 1; }
};
struct DualWeaponConditions {
    unsigned int words[19];
    __forceinline unsigned test(unsigned i) const { return words[i>>5] & (1u<<(i&31)); }
    __forceinline void set(unsigned i) { words[i>>5] |= 1u<<(i&31); }
    __forceinline void clear(unsigned i) { words[i>>5] &= ~(1u<<(i&31)); }
};
struct DualWeaponTemplateView { unsigned char pad[0x114]; unsigned int kindWord; };
class Object {
public:
    bool isKindOf(KindOfType) const;
    void setWeaponSetFlag(WeaponSetType);
    void clearWeaponSetFlag(WeaponSetType);
    void rva0028AE6D();
    __forceinline const DualWeaponFlags *getWeaponSetFlags() const {
        return (const DualWeaponFlags *)((const Rva0028B7AELeaGetter *)this)->get();
    }
    __forceinline const Coord3D *getPosition() const { return &position; }
    __forceinline const DualWeaponTemplateView *getTemplate() const { return tmplate; }
    __forceinline void setCloseCondition() {
        if (!conditions.test(160)) { conditions.set(160); rva0028AE6D(); }
    }
    __forceinline void clearCloseCondition() {
        if (conditions.test(160)) { conditions.clear(160); rva0028AE6D(); }
    }
    __forceinline AIUpdateInterface *getAIUpdateInterface() const { return ai; }
    __forceinline Object *getContainer() const { return container; }
    __forceinline bool isEffectivelyDead() const { return privateStatus & 1; }
    unsigned char pad0[4]; const DualWeaponTemplateView *tmplate;
    unsigned char pad8[0x38-8]; Coord3D position;
    unsigned char pad44[0x10c-0x44]; DualWeaponConditions conditions;
    unsigned char pad158[0x258-0x158]; AIUpdateInterface *ai;
    unsigned char pad25c[0x274-0x25c]; Object *container;
    unsigned char pad278[0x438-0x278]; unsigned char privateStatus;
};
class AttackPriorityInfo;
class PartitionFilter;
class AI {
public: Object *findClosestEnemy(const Object *, float, unsigned int,
    const AttackPriorityInfo *, PartitionFilter *, int);
};
extern AI *TheAI;
class GameLogic { public: unsigned char pad[0x40]; unsigned int frame; };
extern GameLogic *TheGameLogic;
extern const int g_009BA4E4;
struct DualWeaponBehaviorModuleData {
    unsigned char pad[8]; float switchDistance;
    bool useCloseWhileMounted;
    unsigned int minimumSwitchTime;
    bool useHordeRangeWeapon, useRealVictimRange;
};
class DualWeaponDeepBase {
public: virtual void anchor();
protected: const DualWeaponBehaviorModuleData *data; Object *object;
};
class DualWeaponInterface1 { public: virtual void anchor(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };
class UpdateModule : public DualWeaponDeepBase, public DualWeaponInterface1, public UpdateModuleInterface {
protected: unsigned int nextCallFrame; int indexInLogic, updateState;
};
class DualWeaponBehavior : public UpdateModule {
public: virtual UpdateSleepTime update();
private:
    __forceinline UpdateSleepTime sleepTime() const { return (UpdateSleepTime)g_009BA4E4; }
    __forceinline const DualWeaponBehaviorModuleData *getDualWeaponBehaviorModuleData() const { return data; }
    __forceinline Object *getObject() const { return object; }
    bool closeRangeActive; unsigned int switchTimer;
};

UpdateSleepTime DualWeaponBehavior::update()
{
    const DualWeaponBehaviorModuleData *d = getDualWeaponBehaviorModuleData();
    Object *obj = getObject();
    AIUpdateInterface *ai = obj->getAIUpdateInterface();
    if (!ai || obj->isEffectivelyDead()) return UPDATE_SLEEP_FOREVER;
    if (obj->getWeaponSetFlags()->test(8)) return sleepTime();
    Object *container = obj->getContainer();
    if (container && !(container->getTemplate()->kindWord & 0x2000))
        return sleepTime();
    if (d->useHordeRangeWeapon && container && (container->getTemplate()->kindWord & 0x2000)) {
        if (container->getWeaponSetFlags()->test(7)) goto setCloseRange;
        goto clearCloseRange;
    }
    if (obj->isKindOf((KindOfType)0xcf)) return sleepTime();
    if (!closeRangeActive) {
        float range = d->switchDistance;
        Object *victim = 0;
        if (d->useRealVictimRange && ai->getCurrentVictim()) {
            victim = ai->getCurrentVictim();
            Coord3D delta;
            delta.x = obj->getPosition()->x - victim->getPosition()->x;
            delta.y = obj->getPosition()->y - victim->getPosition()->y;
            delta.z = obj->getPosition()->z - victim->getPosition()->z;
            if (delta.x*delta.x + delta.y*delta.y + delta.z*delta.z > range*range) victim = 0;
        } else {
            victim = TheAI->findClosestEnemy(obj, range, 0x62, 0, 0, 0);
        }
        if (victim && fabs((double)victim->getPosition()->z - obj->getPosition()->z) > range*0.5f)
            victim = 0;
        if (!(d->useCloseWhileMounted && obj->isKindOf((KindOfType)0xd6))) {
            unsigned int now = TheGameLogic->frame;
            int remaining = (int)(switchTimer + d->minimumSwitchTime - now);
            if (remaining > 0) return (UpdateSleepTime)remaining;
            switchTimer = now;
            if (!victim || victim->isEffectivelyDead()) {
                if (!obj->getWeaponSetFlags()->test(7)) return sleepTime();
                goto clearCloseRange;
            }
        }
    }
    if (obj->getWeaponSetFlags()->test(7)) return sleepTime();
setCloseRange:
    obj->setWeaponSetFlag(WEAPONSET_CLOSE);
    obj->setCloseCondition();
    return sleepTime();
clearCloseRange:
    obj->clearWeaponSetFlag(WEAPONSET_CLOSE);
    obj->clearCloseCondition();
    return sleepTime();
}
