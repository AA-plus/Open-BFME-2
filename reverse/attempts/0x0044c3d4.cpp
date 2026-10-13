// ?Rva0044C3D4@@YA_NXZ
// partial score=0.91 date=2026-10-13
// ?Rva0044C3D4@@YA_NXZ
// partial score=0.91 date=2026-10-11
// ?Rva0044C3D4@@YA_NXZ
// partial score=0.9 date=2026-10-11
// cl: /O1 /G6 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
void Rva00030830GameFree(void *);
namespace _STL {
template <> inline void vector<unsigned int>::_M_clear() {
 if(this->_M_start)Rva00030830GameFree(this->_M_start);
}
}
// Native HeroTransfer.cpp family. WB names are leads; field offsets and
// call ABIs below are from the complete retail bodies and their providers.
class CreateAHeroData;
class Rva0040A3F9 {public:CreateAHeroData *rva0040A32F(int);};
class CreateAHeroManager {public:
 bool GetAvailableHeroesForFaction(std::vector<unsigned int> *,int);
 Rva0040A3F9 *rva0021F797();
 void rva0021A428(const CreateAHeroData &);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva003FF0E7DwordSlot {public:void set(int);};
struct HeroTransferDataStats {char before[0xC];int first,second;};
class GameSlot {public:
 bool isOccupied() const;
 bool isAI() const;
 void rva0037AD8D(const CreateAHeroData &);
 char before[0x18];int playerTemplate;char beforeKind[0x50-0x1C];int kind,first,second,index;bool hasData;char align[3];char data[4];
 CreateAHeroData *heroData(){return hasData?(CreateAHeroData*)data:0;}
};
struct HeroTransferSavedSlot {
 char before[0x9C];int kind,first,second,index;bool hasData;char align[3];
 char data[0x1AC-0xB0];
 CreateAHeroData *heroData(){return hasData?(CreateAHeroData*)data:0;}
};
class GameInfo {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11)
#undef V
 virtual bool amIHost() const;
 virtual int getLocalSlotNum() const;
 GameSlot *getSlot(int);
 char before[0x88-4];int dispatchID;char beforeSaved[0xC8-0x8C];HeroTransferSavedSlot *saved;
};
extern GameInfo *TheGameInfo;
class NetworkInterface;
extern NetworkInterface *TheNetwork;
// Call-only prefix; no object or vtable is constructed from this view.
class HeroTransferNetworkCalls {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
 V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
 V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
 V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
#undef V
 virtual void beginHeroTransfer();
 virtual void endHeroTransfer();
 virtual void sendHero(const CreateAHeroData &,int,int,int);
};
void rva0044C2C6();
bool Rva0044C277Wait();


class PlayerTemplate {public:int rva001FD234() const;};
class PlayerTemplateStore {public:const PlayerTemplate *getNthPlayerTemplate(int) const;};
extern PlayerTemplateStore *ThePlayerTemplateStore;
int GetGameClientRandomValue(int,int,char *,int);

void rva0044C2C6() {
 if(!TheGameInfo)return;
 for(int i=0;i<8;++i) {
  GameSlot *slot=TheGameInfo->getSlot(i);
  if(!slot || slot->kind!=1 || !slot->isOccupied())continue;
  if(i!=TheGameInfo->getLocalSlotNum() && !(TheGameInfo->amIHost() && slot->isAI()))continue;
  std::vector<unsigned int> available;
  const PlayerTemplate *playerTemplate=ThePlayerTemplateStore->getNthPlayerTemplate(slot->playerTemplate);
  int faction=playerTemplate?playerTemplate->rva001FD234():-1;
  TheCreateAHeroManager->GetAvailableHeroesForFaction(&available,faction);
  if(available.size()>0) {
   int selected=GetGameClientRandomValue(0,available.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameNetwork\\HeroTransfer.cpp",65);
   ((Rva003FF0E7DwordSlot*)slot)->set(available[selected]);
  }
 }
}

static __forceinline bool heroTransferReady() { return TheGameInfo && TheCreateAHeroManager; }
bool Rva0044C3D4() {
 int i=0;
 if(!heroTransferReady())return false;
 else {
 HeroTransferSavedSlot *saved=TheGameInfo->saved;
 if(saved) {
  for(int i=0;i<8;++i,++saved) {
   CreateAHeroData *data=saved->heroData();
   if(data) {
    GameSlot *slot=TheGameInfo->getSlot(i);
    if(slot) {
     slot->rva0037AD8D(*data);
     slot->first=saved->first;
     slot->second=saved->second;
     ((Rva003FF0E7DwordSlot*)slot)->set(saved->index);
     slot->kind=saved->kind;
    }
   }
  }
  return true;
 }
 rva0044C2C6();
 if(TheNetwork)((HeroTransferNetworkCalls*)TheNetwork)->beginHeroTransfer();
 Rva0040A3F9 *heroes=TheCreateAHeroManager->rva0021F797();
 bool remote=false;
 for(;i<8;++i) {
  GameSlot *slot=TheGameInfo->getSlot(i);
  if(!slot || !slot->isOccupied())continue;
  bool send=false;
  switch(slot->kind) {
   case 1:
   case 3:
    if(i==TheGameInfo->getLocalSlotNum() || (TheGameInfo->amIHost() && slot->isAI()))send=true;
    else remote=true;
    if(!send)break;
   case 2: {
    CreateAHeroData *data=heroes->rva0040A32F(slot->index);
    if(data) {
     TheCreateAHeroManager->rva0021A428(*data);
     slot->rva0037AD8D(*data);
     if(send && TheGameInfo)((HeroTransferNetworkCalls*)TheNetwork)->sendHero(*data,TheGameInfo->dispatchID,i,0xFF);
    }
    break;
   }
  }
 }
 bool ready=true;
 if(remote)ready=Rva0044C277Wait();
 if(TheNetwork)((HeroTransferNetworkCalls*)TheNetwork)->endHeroTransfer();
 if(ready) {
  for(int i=0;i<8;++i) {
   GameSlot *slot=TheGameInfo->getSlot(i);
   if(slot) {
    CreateAHeroData *data=slot->heroData();
    if(data && slot->kind==1) {
     HeroTransferDataStats *stats=(HeroTransferDataStats*)data;
     slot->first=stats->first;
     slot->second=stats->second;
    }
   }
  }
 }
 return ready;
 }
}
