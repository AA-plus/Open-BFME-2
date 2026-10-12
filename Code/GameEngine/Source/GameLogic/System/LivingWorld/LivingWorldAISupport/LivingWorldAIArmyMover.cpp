// ?rva0059BE1F@LivingWorldAIArmyMover@@QAEXPAUArmyMoverRegion@@HHPAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@11PAVRva004FF5B7@@H@Z
// cl: /O1 /G7 /arch:SSE /MD /EHs  /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 59BE1F..59C010, 497B, thiscall RET20, unused this.
// WB14FB870 establishes vector collection, distance tree and difficulty filter.
// Method name and original container/element spellings remain unknown.
// Target evidence: native 0x0059BE1F..0x0059C010, RET 0x20, and WB
// 0x014FB870 establish the distance-filtered collection behavior. The player,
// region and army records remain offset views, not recovered source layouts.
// The inline region lookup wrapper controls the returned iterator lifetime;
// it retains retail's owner load after RNG/push and closes register allocation.
// Every call resolves through existing ledger providers; no new pins.
#include <vector>
#include <map>
class ModuleData;
typedef _STL::vector<const ModuleData*> PointerVector;
namespace _STL {
template<> inline __declspec(noinline) void PointerVector::push_back(const ModuleData*const&x) {
 if(_M_finish!=_M_end_of_storage._M_data){_Construct(_M_finish,x);++_M_finish;}
 else _M_insert_overflow(_M_finish,x,_IsPODType(),1UL,true);
}
template<> const ModuleData**PointerVector::erase(const ModuleData**,const ModuleData**);
}
typedef _STL::map<int,int> IntMap;
typedef _STL::_Rb_tree<int,_STL::pair<const int,int>,_STL::_Select1st<_STL::pair<const int,int> >,_STL::less<int>,_STL::allocator<_STL::pair<const int,int> > > IntTree;
struct Rva002B488EResult {char pad[0x54];int owner;};
class Rva002E2903Player;
class Rva002BA8F1Logic {public:Rva002E2903Player*find(int,unsigned*);Rva002B488EResult*rva002B488E(int);};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002E071E {public:int rva002E0BC0(int);};
struct ArmyMoverRegionInfo {int id;char pad[0x48];IntMap armies;};
struct Rva004FF5B7Node:public _STL::_Rb_tree_node_base {int key;ArmyMoverRegionInfo region;};
struct Rva004FF5B7Iter {Rva004FF5B7Node*m_ptr;};
class Rva004FF5B7 {public:__forceinline ArmyMoverRegionInfo*get(int id){return &rva004FF5B7(id).m_ptr->region;}Rva004FF5B7Iter rva004FF5B7(int);};
struct ArmyMoverDistanceLookup { IntMap::iterator find(int id){return ((IntMap*)this)->find(id);} };
extern unsigned g_Va00E04544;
int GetGameLogicRandomValue(int,int,char*,int);
struct ArmyMoverRegion {char pad[0x12c];int id;char gap130[12];int owner;};
class LivingWorldAIArmyMover {public:int WinTestBattle(ArmyMoverRegion*,int,int,const ModuleData*,void*,Rva004FF5B7*,int);void rva0059BE1F(ArmyMoverRegion*,int,int,PointerVector*,PointerVector*,PointerVector*,Rva004FF5B7*,int);};

// WB14FBC60 and native59C15B..59C631 establish two simulated battles.
// Original parameter and record spellings remain unknown; views below carry
// only independently observed extents and fields. The no-storage base adapter
// invokes the existing cleanup provider; it is not original inheritance.
struct SetupPlayer;struct SetupArmy;struct SetupRecord52;struct SetupSimulation44;
class LivingWorldLogic {public:void SetUpAutoResolveBattle(const _STL::vector<SetupPlayer*>*,SetupPlayer*,const _STL::vector<SetupArmy*>*,void*,_STL::vector<SetupRecord52>*,_STL::vector<SetupSimulation44>*);};
struct BfmeE16 {float x,y,z,w;};
struct Rva002BBB96Element {char gap00[0x18];float weapon,armor,experience;void*science;void*simulation;int side,playerID;~Rva002BBB96Element();};
typedef _STL::vector<Rva002BBB96Element> BattlePlayers;
namespace _STL {
template<> BattlePlayers::~vector();
template<> inline BattlePlayers::vector(const allocator<Rva002BBB96Element>&a):_Vector_base<Rva002BBB96Element,allocator<Rva002BBB96Element> >(a) {}
}
struct PlayerStorage;
class Rva004FA2E2 {public:~Rva004FA2E2();char gap00[0x78];int winner;int round;};
class LivingWorldAutoResolveBattle: public Rva004FA2E2 {public:LivingWorldAutoResolveBattle(const PlayerStorage&);};
class Rva004FA10FOwner {public:void rva004FA10F();};
// ?WinTestBattle@LivingWorldAIArmyMover@@QAEHPAUArmyMoverRegion@@HHPBVModuleData@@PAXPAVRva004FF5B7@@H@Z
int LivingWorldAIArmyMover::WinTestBattle(ArmyMoverRegion*region,int distance,int playerID,const ModuleData*army,void*unused,Rva004FF5B7*info,int difficulty) {
 PointerVector friendly,enemy,players;
 friendly.clear();enemy.clear();players.clear();
 rva0059BE1F(region,distance,playerID,&friendly,&enemy,&players,info,difficulty);
 int ownerID=region->owner;Rva002E2903Player *owner=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(ownerID,0);
 unsigned enemyCount=enemy.size();if(enemyCount>0) {
  BattlePlayers records;
  _STL::vector<unsigned int> battleArmies=*(const _STL::vector<unsigned int>*)&enemy;
  ((PointerVector*)&battleArmies)->push_back(army);
  TheLivingWorldLogic->SetUpAutoResolveBattle((const _STL::vector<SetupPlayer*>*)&players,(SetupPlayer*)owner,(const _STL::vector<SetupArmy*>*)&battleArmies,region,(_STL::vector<SetupRecord52>*)&records,0);
  if(difficulty<5) {
   int playerIndex=-1;
   for(unsigned i=0;i<records.size();++i)if(records[i].playerID==playerID){playerIndex=i;break;}
   if(playerIndex>=0) {
    if(difficulty==3){records[playerIndex].weapon*=0.9f;records[playerIndex].armor*=1.1f;}
    else if(difficulty==2){records[playerIndex].weapon*=0.75f;records[playerIndex].armor*=1.25f;}
   }
  }
  LivingWorldAutoResolveBattle battleManager(*(const PlayerStorage*)&records);
  while(battleManager.winner==-1)((Rva004FA10FOwner*)&battleManager)->rva004FA10F();
  if(!owner || ((unsigned char)((Rva002E071E*)owner)->rva002E0BC0(playerID) && battleManager.winner==0) || battleManager.winner==1)return 0;
 }
 unsigned friendlyCount=friendly.size();const ModuleData **friendlyBegin=friendly.begin();if(friendlyCount>0 && enemyCount>0) {
  BattlePlayers records;
  _STL::vector<unsigned int> battleArmies=*(const _STL::vector<unsigned int>*)&enemy;
  for(unsigned i=0;i<friendlyCount;++i)((PointerVector*)&battleArmies)->push_back(friendlyBegin[i]);
  TheLivingWorldLogic->SetUpAutoResolveBattle((const _STL::vector<SetupPlayer*>*)&players,(SetupPlayer*)owner,(const _STL::vector<SetupArmy*>*)&battleArmies,region,(_STL::vector<SetupRecord52>*)&records,0);
  if(difficulty<5) {
   int playerIndex=-1;
   for(unsigned i=0;i<records.size();++i)if(records[i].playerID==playerID){playerIndex=i;break;}
   if(playerIndex>=0) {
    if(difficulty==3){records[playerIndex].weapon*=0.9f;records[playerIndex].armor*=1.1f;}
    else if(difficulty==2){records[playerIndex].weapon*=0.5f;records[playerIndex].armor*=1.5f;}
   }
  }
  LivingWorldAutoResolveBattle battleManager(*(const PlayerStorage*)&records);
  while(battleManager.winner==-1)((Rva004FA10FOwner*)&battleManager)->rva004FA10F();
  if(!owner || ((unsigned char)((Rva002E071E*)owner)->rva002E0BC0(playerID) && battleManager.winner==0) || battleManager.winner==1)return 1;
 }
 return enemyCount>0 ? 2 : 0;
}

void LivingWorldAIArmyMover::rva0059BE1F(ArmyMoverRegion*region,int maxDistance,int playerID,PointerVector*friendly,PointerVector*enemy,PointerVector*players,Rva004FF5B7*info,int difficulty) {
 Rva002E2903Player*player=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(playerID,0);
 friendly->clear();enemy->clear();
 ArmyMoverDistanceLookup&distances=*(ArmyMoverDistanceLookup*)&g_Va00E04544;

 if(distances.find(region->id)!=((IntMap*)&distances)->end()) {
  IntTree&tree=*(IntTree*)&distances.find(region->id)->second;
  for(int distance=0;distance<=maxDistance;distance++) {
   _STL::pair<IntTree::const_iterator,IntTree::const_iterator> range=((const IntTree&)tree).equal_range(distance);
   for(IntTree::const_iterator r=range.first;r!=range.second;r++) {
    ArmyMoverRegionInfo*ri=info->get(r->second);
    for(IntMap::iterator a=ri->armies.begin();a!=ri->armies.end();++a) {
     const Rva002B488EResult*army=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B488E(a->second);
     if((unsigned char)((Rva002E071E*)player)->rva002E0BC0(a->first)) {
      friendly->push_back((const ModuleData*const&)army);
      unsigned int owner=army->owner;bool found=false;
      for(unsigned j=0;j<players->size();++j) {
       if(*(int*)((char*)(*players)[j]+0x14)==owner) {found=true;break;}
      }
      if((found == 0)) {Rva002E2903Player*p=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(owner,0);players->push_back((const ModuleData*const&)p);}
     } else {
      int chance=2;if(3 == difficulty)chance=1;else if(difficulty==2)chance=0;
      if(0 != distance && GetGameLogicRandomValue(0,chance,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\System\\LivingWorld\\LivingWorldAISupport\\LivingWorldAIArmyMover.cpp",289)!=0)continue;
      enemy->push_back((const ModuleData*const&)army);
      int owner=army->owner;bool found=false;
      for(unsigned j=0;j<players->size();++j) {
       if(*(int*)((char*)(*players)[j]+0x14)==owner) {found=true;break;}
      }
      if((found == 0)) {Rva002E2903Player*p=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(owner,0);players->push_back((const ModuleData*const&)p);}
     }
    }
   }
  }
 }
}
