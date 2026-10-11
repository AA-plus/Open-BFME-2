// cl: /O1 /G6 /arch:SSE /MD /DNDEBUG /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
void Rva00030830GameFree(void *);
namespace _STL {
template <> inline void vector<unsigned int>::_M_clear() {
 if(this->_M_start)Rva00030830GameFree(this->_M_start);
}
}
// HeroTransfer.cpp: native44C2C6..44C3D4 has its own EH entry and complete
// return. WB014B7FD0 names SelectRandomHero and carries the matching source
// file and call graph. Keep the established address name pending identity
// convergence. Native fields: slot player-template18, hero-kind50/index5C;
// GameInfo virtual host12/local-slot13. No reference implementation used.
// The vector<unsigned> and conditional game-free specialization follow the
// independently byte-verified CreateAHeroManagerAvailableHeroes.cpp provider.
class CreateAHeroData;
class CreateAHeroManager {public:
 bool GetAvailableHeroesForFaction(std::vector<unsigned int> *,int);
};
extern CreateAHeroManager *TheCreateAHeroManager;
class Rva003FF0E7DwordSlot {public:void set(int);};
class GameSlot {public:
 bool isOccupied() const;
 bool isAI() const;
 char before[0x18];int playerTemplate;char beforeKind[0x50-0x1C];int kind,first,second,index;
};
class GameInfo {public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11)
#undef V
 virtual bool amIHost() const;
 virtual int getLocalSlotNum() const;
 GameSlot *getSlot(int);
};
extern GameInfo *TheGameInfo;
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
   ((Rva003FF0E7DwordSlot*)slot)->set(available.begin()[selected]);
  }
 }
}
