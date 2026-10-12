// ?update@AttributeModifierPoolUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.8 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <vector>
#include "../reference/shims/bfme2_ascii/ascii_string.h"
#include "../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva001E42F2 {public:void rva001E42F2(const int *);};
class Object {public:void rva00293077(const void *);};
class Rva00297360Element {public:
 ~Rva00297360Element();
 int index;AsciiString name;unsigned expiration,upgrade;
};
class Rva0040314A {public:unsigned rva0040314A();};
namespace _STL {
template<> Rva00297360Element *vector<Rva00297360Element>::erase(Rva00297360Element*);
}
struct BfmeWordValue4 {unsigned bits;};
namespace _STL {template<>struct __type_traits<BfmeWordValue4>:__type_traits_aux<1>{};}
namespace _STL {
template<> void deque<BfmeWordValue4>::push_back(const BfmeWordValue4 &);
template<> void deque<BfmeWordValue4>::pop_front();
template<> _Deque_base<BfmeWordValue4,allocator<BfmeWordValue4> >::~_Deque_base();
}
struct AttributeConditionWords {int words[19];};
class AttributeModifierStore {public:
 void *rva00214801(void *,int);
 void *getEndFX(int,Object *);
 void *GetCategoryContainer(int);
 void *getDelayedUpgrade(int);
};
extern AttributeModifierStore *TheAttributeModifierStore;
class FXList {public:static void doFXObj(const FXList *,const Object *,const Object *);};
struct CategoryView {char unknown00[12];int category;};
struct DelayedUpgradeView {void *upgrade;unsigned delay;};
enum UpdateSleepTime {UPDATE_SLEEP_FOREVER=0x3fffffff};
class AttributeDeepBase {public:virtual ~AttributeDeepBase();void *data;Object *object;};
class AttributeBehaviorInterface {public:virtual void slot0()=0;};
class AttributeUpdateInterface {public:virtual UpdateSleepTime update()=0;};
class AttributeUpdateBase:public AttributeDeepBase,public AttributeBehaviorInterface,public AttributeUpdateInterface {
public:unsigned wake;int index,reserved;
};
class AttributeModifierPoolUpdate:public AttributeUpdateBase {public:
 virtual UpdateSleepTime update();
 _STL::vector<Rva00297360Element> modifiers;
 unsigned maxFrame;
 AsciiString names[15];
 unsigned counts[15];
 Object *getObject() const {return object;}
};
UpdateSleepTime AttributeModifierPoolUpdate::update()
{
 unsigned frame=TheGameLogic->getFrame();
 unsigned next=UPDATE_SLEEP_FOREVER;
 _STL::deque<BfmeWordValue4> pending;
 for(Rva00297360Element *it=modifiers.begin();it!=modifiers.end();) {
   Rva00297360Element *entry=it;
   unsigned &upgrade=entry->upgrade;
   if(upgrade>0 && frame>=upgrade) {
     BfmeWordValue4 key;key.bits=entry->index;
     pending.push_back(key);
     upgrade=0;
   }
   if(frame>=entry->expiration) {
     AttributeConditionWords clear;
     TheAttributeModifierStore->rva00214801(&clear,entry->index);
     ((Rva001E42F2*)getObject())->rva001E42F2(clear.words);
     if(upgrade<=frame) {
       const FXList *fx=(const FXList*)TheAttributeModifierStore->getEndFX(entry->index,getObject());
       if(fx)FXList::doFXObj(fx,getObject(),0);
       CategoryView *category=(CategoryView*)TheAttributeModifierStore->GetCategoryContainer(entry->index);
       if(category)--counts[category->category];
       it=modifiers.erase(it);
     } else {
       ++it;
       next=next<upgrade?next:upgrade;
     }
   } else {
     ++it;
     next=next<((Rva0040314A*)entry)->rva0040314A()?next:((Rva0040314A*)entry)->rva0040314A();
   }
 }
 maxFrame=next<UPDATE_SLEEP_FOREVER?next:UPDATE_SLEEP_FOREVER;
 while(!pending.empty()) {
   DelayedUpgradeView *upgrade=(DelayedUpgradeView*)TheAttributeModifierStore->getDelayedUpgrade((int)pending.front().bits);
   if(upgrade&&upgrade->upgrade)getObject()->rva00293077(upgrade->upgrade);
   pending.pop_front();
 }
 if(maxFrame<UPDATE_SLEEP_FOREVER)return (UpdateSleepTime)(maxFrame-frame);
 maxFrame=UPDATE_SLEEP_FOREVER;
 return UPDATE_SLEEP_FOREVER;
}
