// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// GarrisonContain::healSingleObject: retail 0x004786F8-0x0047876A, 114B.
// Source: Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20,
// game/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainHealSingleObject.cpp,
// and the canonical ZH healing algorithm. Target sibling 0x00478BE0 walks
// contained objects when the rowed module-data's +0x98 HealObjects flag is set,
// passing +0x9C framesForFullHeal. The constructor is the existing 0x7C
// DamageInfo initializer at 0x00263895. Retail reads body +0x254 and contained
// frame +0x27C, writes damage type 7 / death type 1 / amount at +0x10/+0x1C/+0x20,
// and calls getMaxHealth/attemptHealing through slots +0x18/+0x04. These local
// address-derived views preserve the target ABI without claiming complete layouts.
class Object;
class GameLogic;
extern GameLogic* TheGameLogic;
struct Rva004786F8LogicView { char m_lead[0x40]; unsigned int m_frame; };
class DamageInfo {
public:
    DamageInfo();
    char m_lead[0x10];
    int m_damageType;
    char m_gap[8];
    int m_deathType;
    float m_amount;
    char m_tail[0x7c-0x24];
};
class Rva004786F8Body {
public:
    virtual void slot00();
    virtual void attemptHealing(DamageInfo*);
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual float getMaxHealth() const;
};
struct Rva004786F8TemplateView {
    char m_lead[0x111];
    unsigned char m_kindof111;
};
struct Rva004786F8ObjectView {
    char m_lead00[4];
    const Rva004786F8TemplateView* m_template;
    char m_lead08[0x254-8];
    Rva004786F8Body* m_body;
    char m_gap[0x24];
    unsigned int m_containedByFrame;
};
enum BodyDamageType {
    BODY_PRISTINE = 0,
    BODY_DAMAGED = 1,
    BODY_RUBBLE = 2
};
class Rva004786F8Primary {
protected:
    virtual void p00();
    const void* m_moduleData;
    Rva004786F8ObjectView* m_object;
    char m_pad0C[0x20-0x0C];
};
class Rva004786F8ContainIface {
public:
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19();
    virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23();
    virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
    virtual void c28(); virtual void c29(); virtual void c30(); virtual void c31();
    virtual void cSlot32(int);
    virtual void c33(); virtual void c34();
    virtual void cSlot35(int);
    virtual void c36(); virtual void c37(); virtual void c38(); virtual void c39();
    virtual void c40(); virtual void c41(); virtual void c42(); virtual void c43();
    virtual void c44(); virtual void c45(); virtual void c46(); virtual void c47();
    virtual void c48(); virtual void c49(); virtual void c50(); virtual void c51();
    virtual void c52(); virtual void c53(); virtual void c54(); virtual void c55();
    virtual void c56(); virtual void c57(); virtual void c58(); virtual void c59();
    virtual void c60(); virtual void c61(); virtual void c62(); virtual void c63();
    virtual void c64(); virtual void c65(); virtual void c66(); virtual void c67();
    virtual void c68();
    virtual unsigned int getContainCount(int) const;
    char m_pad24[8];
};
class Rva004786F8DamageIface {
public:
    virtual void d00();
    virtual void rva0047876A(const DamageInfo* damageInfo, BodyDamageType oldState, BodyDamageType newState);
};
class GarrisonContain : public Rva004786F8Primary, public Rva004786F8ContainIface, public Rva004786F8DamageIface {
public:
    virtual void rva0047876A(const DamageInfo* damageInfo, BodyDamageType oldState, BodyDamageType newState);
protected:
    void healSingleObject(Object*,float);
};
void GarrisonContain::healSingleObject(Object* object,float framesForFullHeal) {
    DamageInfo healInfo;
    healInfo.m_damageType=7;
    healInfo.m_deathType=1;
    Rva004786F8ObjectView* view=(Rva004786F8ObjectView*)object;
    Rva004786F8Body* body=view->m_body;
    if(((Rva004786F8LogicView*)TheGameLogic)->m_frame-view->m_containedByFrame >= framesForFullHeal)
        healInfo.m_amount=body->getMaxHealth();
    else
        healInfo.m_amount=body->getMaxHealth()/framesForFullHeal;
    body->attemptHealing(&healInfo);
}
void GarrisonContain::rva0047876A(const DamageInfo*, BodyDamageType, BodyDamageType newState) {
    if(newState == BODY_RUBBLE && !(m_object->m_template->m_kindof111 & 0x80)) {
        if(getContainCount(0) > 0) {
            cSlot35(2);
            cSlot32(2);
        }
    }
}
