// ?update@WoundArrowUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.760806916426513 date=2026-10-12
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Include
// stlport
#include <math.h>

#include "Code/Libraries/Include/Lib/Coord3D.h"
#define BFME_HAVE_COORD3D
class WoundArrowConditionBits0026E1F0
{
public:
    unsigned test(int bit) const { return m_words[bit>>5] & (1U<<(bit&31)); }
    void set(int bit) { m_words[bit>>5] |= (1U<<(bit&31)); }
    void reset(int bit) { m_words[bit>>5] &= ~(1U<<(bit&31)); }
private:
    unsigned m_words[19];
};
typedef WoundArrowConditionBits0026E1F0 ModelConditionFlags;
#define BFME_HAVE_MODELCONDITIONFLAGS
enum CommandSourceType { CMD_FROM_AI=2 };
enum WeaponLockType { WOUND_LOCK=2 };
class AIUpdateInterface;
class Object { public:
 void rva0028AE6D(); void releaseWeaponLock(WeaponLockType);
 char pad00[0x38];Coord3D m_cachedPos;
 char pad44[0x10C-0x44];ModelConditionFlags m_modelConditionFlags;
 char pad158[0x258-0x158];AIUpdateInterface *m_ai;
};

enum LocomotorSetType { LOCOMOTORSET_0026E1F0 = 4 };
class AIUpdateInterface { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual void slot93();
virtual void slot94();
virtual void slot95();
virtual void slot96();
virtual void slot97();
virtual void slot98();
virtual void slot99();
virtual void slot100();
virtual void slot101();
virtual void slot102();
virtual void slot103();
virtual void slot104();
virtual void slot105();
virtual void slot106();
virtual void slot107();
virtual void slot108();
virtual void slot109();
virtual bool isIdle() const;
virtual void slot111();
virtual void slot112();
virtual void slot113();
virtual void slot114();
virtual void slot115();
virtual void slot116();
virtual void slot117();
virtual void slot118();
virtual void slot119();
virtual void slot120();
virtual void slot121();
virtual void slot122();
virtual void slot123();
virtual void slot124();
virtual void slot125();
virtual void slot126();
virtual void slot127();
virtual void slot128();
virtual void slot129();
virtual void slot130();
virtual void slot131();
virtual void slot132();
virtual void slot133();
virtual void slot134();
virtual void slot135();
virtual void slot136();
virtual void slot137();
virtual void slot138();
virtual void slot139();
virtual void slot140();
virtual void slot141();
virtual bool chooseLocomotorSet(LocomotorSetType);
};
class AICommandInterface
{
public:
    void aiMoveToPosition(const Coord3D *, CommandSourceType);
};
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class BfmeThing916D { public: void bfmeGo916D(void *); };
class WoundArrowUpdate;
class SpecialAbilityUpdate
{
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10();
private:
    void onExit(bool, bool);
public:
    virtual void slot11();
public:
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16();
    virtual void triggerAbilityEffect();
    friend class WoundArrowUpdate;
};
class WoundArrowUpdateModuleData
{
public:
    unsigned char m_pad000[0xC8];
    float m_rangeC8;
};
enum UpdateSleepTime { UPDATE_SLEEP_1 = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
class WoundArrowUpdate
{
public:
    virtual UpdateSleepTime update();
    Object *getObject() const { return *(Object **)((const char *)this - 8); }
    const WoundArrowUpdateModuleData *getWoundArrowUpdateModuleData() const
    { return *(const WoundArrowUpdateModuleData **)((const char *)this - 0xc); }
private:
    unsigned char m_pad004[0x30 - 4];
    ObjectID m_targetID;
    unsigned char m_pad34[0x78 - 0x34];
    bool m_hasAppliedWound;
};
static __forceinline void setCondition0026E1F0(Object *object, int bit)
{
    if (!object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.set(bit);
        object->rva0028AE6D();
    }
}
static __forceinline void clearCondition0026E1F0(Object *object, int bit)
{
    if (object->m_modelConditionFlags.test(bit)) {
        object->m_modelConditionFlags.reset(bit);
        object->rva0028AE6D();
    }
}

// ?update@WoundArrowUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime WoundArrowUpdate::update()
{
    if (!m_hasAppliedWound) {
        ((SpecialAbilityUpdate *)((char *)this - 0x10))->triggerAbilityEffect();
        return UPDATE_SLEEP_1;
    }
    if (!getObject()->m_ai->isIdle())
        return UPDATE_SLEEP_1;
    Object *owner = getObject();
    m_hasAppliedWound = false;
    ObjectID targetID = m_targetID;
    Object *target = TheGameLogic->findObjectByID(targetID);
    if (target) {
        AIUpdateInterface *ai = target->m_ai;
        if (!ai)
            return UPDATE_SLEEP_FOREVER;
        const WoundArrowUpdateModuleData *data = getWoundArrowUpdateModuleData();
        float dx = target->m_cachedPos.x - owner->m_cachedPos.x;
        float dy = target->m_cachedPos.y - owner->m_cachedPos.y;
        float inverse = 1.0f / (float)sqrt(dx * dx + dy * dy);
        float unitX = dx * inverse;
        float unitY = dy * inverse;
        Coord3D position;
        position.x = unitX * data->m_rangeC8;
        position.y = unitY * data->m_rangeC8;
        position.x += target->m_cachedPos.x;
        position.y += target->m_cachedPos.y;
        ai->chooseLocomotorSet(LOCOMOTORSET_0026E1F0);
        ((AICommandInterface *)((char *)ai + 0x20))->aiMoveToPosition(&position, CMD_FROM_AI);
        setCondition0026E1F0(target, 77);
    }
    owner->releaseWeaponLock(WOUND_LOCK);
    clearCondition0026E1F0(owner, 207);
    ((SpecialAbilityUpdate *)((char *)this - 0x10))->SpecialAbilityUpdate::onExit(false, false);
    return UPDATE_SLEEP_FOREVER;
}
