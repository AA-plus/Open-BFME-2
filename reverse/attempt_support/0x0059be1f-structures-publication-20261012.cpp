// ?rva0059BE1F@LivingWorldAIArmyMover@@QAEXPAURegionView@@HHPAV?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@11PAVRva004FF5B7@@H@Z
// partial score=0.791700506066703 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// Native0059BE1F..0059C010, 497 bytes, thiscall RET32; WB014FB870..014FBC5B.
// WB's method is unnamed. Its source path and complete call graph establish
// the owning subsystem; the address name preserves the unknown original name.
// Target evidence: region ID12C, army owner54, player ID14; map value begins
// at node14 and region army tree is at value4C. Existing provider ABIs and
// globals are reused; map/vector views do not identify original element types.
// Whole C++ near miss: emits513B, frame24 versus retail18, iterator/army homes
// differ. Every REL32 resolves; complete native132B path literal preserved.
// No Code row, new pin, duplicate global, or assembly was admitted.
// stlport
#include <map>
#include <vector>
class ModuleData;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern unsigned g_Va00E04544;
class Rva002E2903Player;
struct Rva002B488EResult;
class Rva002BA8F1Logic {public:Rva002E2903Player *find(int,unsigned*);Rva002B488EResult *rva002B488E(int);};
class Rva002E071E {public:int rva002E0BC0(int);};
struct Rva004FF5B7Node {char pad[0x14];};
struct Rva004FF5B7Iter {Rva004FF5B7Node *m_ptr;};
class Rva004FF5B7 {public:Rva004FF5B7Iter rva004FF5B7(int);};
struct RegionView {char pad[0x12c];int id;int getID()const{return id;} };
struct ArmyView {char pad[0x54];int owner;};
struct PlayerView {char pad[0x14];int id;};
struct RegionInfoView {char pad[0x4c];_STL::multimap<int,int> armies;};
typedef _STL::vector<void*> RawVector;
typedef _STL::vector<const ModuleData*> PointerVector;
namespace _STL {
template<> void PointerVector::push_back(const ModuleData *const&);
template<> void * *RawVector::erase(void**,void**);
}
int GetGameLogicRandomValue(int,int,char*,int);
class LivingWorldAIArmyMover {public:void rva0059BE1F(RegionView*,int,int,RawVector*,RawVector*,RawVector*,Rva004FF5B7*,int);};
void LivingWorldAIArmyMover::rva0059BE1F(RegionView *region,int maxLevel,int playerID,RawVector *friends,RawVector *enemies,RawVector *players,Rva004FF5B7 *info,int mode) {
 Rva002E071E *player=reinterpret_cast<Rva002E071E*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->find(playerID,0));
 friends->erase(friends->begin(),friends->end());enemies->erase(enemies->begin(),enemies->end());
 typedef _STL::map<int,int> IntMap;
 IntMap *routes=reinterpret_cast<IntMap*>(&g_Va00E04544);
 if(routes->find(region->getID())!=routes->end()) {
  const _STL::multimap<int,int> *levels=reinterpret_cast<const _STL::multimap<int,int>*>(&routes->find(region->getID())->second);
  for(playerID=0;playerID<=maxLevel;++playerID) {
   _STL::pair<_STL::multimap<int,int>::const_iterator,_STL::multimap<int,int>::const_iterator> range=levels->equal_range(playerID);
   for(_STL::multimap<int,int>::const_iterator it=range.first;it!=range.second;++it) {
    RegionInfoView *r=reinterpret_cast<RegionInfoView*>(reinterpret_cast<char*>(info->rva004FF5B7(it->second).m_ptr)+0x14);
    for(_STL::multimap<int,int>::iterator a=r->armies.begin();a!=r->armies.end();++a) {
     const ModuleData *army=reinterpret_cast<const ModuleData*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->rva002B488E(a->second));
     if((unsigned char)player->rva002E0BC0(a->first)) {
      reinterpret_cast<PointerVector*>(friends)->push_back(army);
      int id=reinterpret_cast<const ArmyView*>(army)->owner;
      bool found=false;for(unsigned i=0;i<players->size();++i)if(reinterpret_cast<PlayerView*>((*players)[i])->id==id){found=true;break;}
      if(!found) {const ModuleData *p=reinterpret_cast<const ModuleData*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->find(id,0));reinterpret_cast<PointerVector*>(players)->push_back(p);}
     }else {
      int upper=2;if(mode==3)upper=1;else if(mode==2)upper=0;
      if(playerID==0||GetGameLogicRandomValue(0,upper,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIArmyMover.cpp",289)==0) {
       reinterpret_cast<PointerVector*>(enemies)->push_back(army);
       int id=reinterpret_cast<const ArmyView*>(army)->owner;
       bool found=false;for(unsigned i=0;i<players->size();++i)if(reinterpret_cast<PlayerView*>((*players)[i])->id==id){found=true;break;}
       if(!found) {const ModuleData *p=reinterpret_cast<const ModuleData*>(reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->find(id,0));reinterpret_cast<PointerVector*>(players)->push_back(p);}
      }
     }
    }
   }
  }
 }
}
