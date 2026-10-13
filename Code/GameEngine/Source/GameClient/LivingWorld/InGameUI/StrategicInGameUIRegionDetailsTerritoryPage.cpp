// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5E38EB..5E3947 complete92B and WB15F6AA0. Owner from
// admitted dtor5E362F and vtableC77BD0; Impl allocation16B from direct native call5E3753.
#include "ascii_string.h"
struct RvaSmallVtableZeroBase {void *m_04;};
class Rva0007DF07:public RvaSmallVtableZeroBase {public:virtual ~Rva0007DF07(){}};
class Rva005EEE5A:public Rva0007DF07 {public:Rva005EEE5A();bool active;};
namespace StrategicInGameUI {class RegionDetailsTerritoryPage {public:class Impl;};}
class StrategicInGameUI::RegionDetailsTerritoryPage::Impl {public:Impl(unsigned,const AsciiString&,void*);private:char storage[0x10];};
class Rva005E362F:public Rva005EEE5A {public:Rva005E362F(void*,void*,void*);virtual ~Rva005E362F();private:StrategicInGameUI::RegionDetailsTerritoryPage::Impl *impl;};
Rva005E362F::Rva005E362F(void *level,void *name,void *region):impl(new StrategicInGameUI::RegionDetailsTerritoryPage::Impl((unsigned)level,*(const AsciiString*)name,region)){}

class BaseA { int a; };
class BaseB { int b; };
class LivingWorldRegion : public BaseA, public BaseB {
public:
    int GetCommandPointBonus() { return *(int*)((char*)this + 0x94); }
    int GetAttackBonus() { return *(int*)((char*)this + 0x9c); }
    int GetDefenseBonus() { return *(int*)((char*)this + 0xa0); }
    int GetExperienceBonus() { return *(int*)((char*)this + 0xa4); }
    int GetResourceBonus() { return *(int*)((char*)this + 0x90); }
    int GetPowerPointBonus() { return *(int*)((char*)this + 0x98); }
};

namespace StrategicInGameUI {
    struct BonusPropertyEntry {
        int bonusType;
        int (LivingWorldRegion::*getter)();
    };

    static __declspec(noinline) int GetBonus(LivingWorldRegion *region, int bonusType) {
        static BonusPropertyEntry bonusTypePropertyMap[] = {
            { 0, &LivingWorldRegion::GetCommandPointBonus },
            { 1, &LivingWorldRegion::GetAttackBonus },
            { 2, &LivingWorldRegion::GetDefenseBonus },
            { 3, &LivingWorldRegion::GetExperienceBonus },
            { 4, &LivingWorldRegion::GetResourceBonus },
            { 5, &LivingWorldRegion::GetPowerPointBonus },
        };
        int i = 0;
        while (bonusTypePropertyMap[i].bonusType != bonusType)
            ++i;
        int (LivingWorldRegion::*getter)() = bonusTypePropertyMap[i].getter;
        return (region->*getter)();
    }
}

// ?GetBonusCaller absent-from-retail
void GetBonusCaller(LivingWorldRegion *region) {
    for (int i = 0; i < 6; ++i) {
        StrategicInGameUI::GetBonus(region, i);
    }
}
