// ?rva0059C93C@LivingWorldAIArmyMover@@QAEXPAV?$vector@UBfmePod20@@V?$allocator@UBfmePod20@@@_STL@@@_STL@@HPAXPAVRva004FF5B7@@H@Z
// partial score=0.9522595066602177 date=2026-10-12
// ?rva0059C93C@LivingWorldAIArmyMover@@QAEXPAV?$vector@UBfmePod20@@V?$allocator@UBfmePod20@@@_STL@@@_STL@@HPAXPAVRva004FF5B7@@H@Z
// cl: /O1 /G7 /arch:SSE /MD /EHs  /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native59C93C..59CE80:1348B and frame90 exact. Fifty-nine stack-slot
// bytes differ; every instruction/call/register/branch/EH state aligns.
// WB14FAE80 places this movement-order pass in the army-mover class and
// independently supplies the same DefendHomeTerritory/WinTestBattle graph.
// The original method name and most view/type spellings remain unproven.
// The strategic779B helper and WinTestBattle are now matched dependencies;
// this candidate resolves normally without a diagnostic map or new pins.
// The 24-byte cleanup base is an ABI adapter, not original inheritance.
// RegionInfo +8 is the observed score, +10/+1C are four-byte building lists;
// node+10 is the region owner key. Army record +8 is its unit-tree node count.
// This is a bank, not a verified recovery.
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
class Rva002E2903Player {public:char pad14[0x14];int id;char pad18[0x1c];int faction;};
class Rva002BA8F1Logic {public:Rva002E2903Player*find(int,unsigned*);Rva002E2903Player*rva002B52A8(int);Rva002B488EResult*rva002B488E(int);};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002E071E {public:int rva002E0BC0(int);};
struct ArmyMoverRegionInfo {int id,owner,m_08,m_0c;_STL::vector<int>m_10,m_1c,m_28,m_34,m_40;IntMap armies;};
struct Rva004FF5B7Node:public _STL::_Rb_tree_node_base {int key;ArmyMoverRegionInfo region;};
struct Rva004FF5B7Iter {Rva004FF5B7Node*m_ptr;};
class Rva004FF5B7 {public:__forceinline ArmyMoverRegionInfo*get(int id){return &rva004FF5B7(id).m_ptr->region;}Rva004FF5B7Iter rva004FF5B7(int);};
struct ArmyMoverDistanceLookup { IntMap::iterator find(int id){return ((IntMap*)this)->find(id);} };
extern unsigned g_Va00E04544;
int GetGameLogicRandomValue(int,int,char*,int);
struct ArmyMoverRegion {char pad[0x12c];int id;char gap130[12];int owner;char gap140[0x62];bool enabled;};

struct BfmePod20 {int m_id;bool m_flag;int m_08,m_0c,m_step;};
struct Range0059BD85;
class Rva004FF997Owner {public:int rva004FF997(int);};
class Rva004FF9B6 {public:void*rva004FF9B6(int);};
class Rva0020E89C;
class Rva0020EAF6View {public:Rva0020E89C*rva0020EAF6(int);};
int rva0050059A(int,int);int rva005009AA(int,int);
struct StrategyRegion {int id,owner;};
struct StrategyBonus {char gap00[0x14];int a,b,c;char gap20[12];_STL::vector<int> regions;};
struct StrategyDefinition {char gap00[0x5c];_STL::vector<StrategyBonus*> bonuses;};
struct StrategyManager {char gap00[8];StrategyDefinition*definition;};
struct StrategyLogic {char gap00[0xb0];StrategyManager*manager;__forceinline StrategyManager*getManager(){return manager;}};
struct StrategyArmy {int id;int unknown04;unsigned strength;int unknown0c;StrategyRegion*region;};
typedef _STL::vector<StrategyArmy> StrategyArmies;

class Rva0059CFAACallee;
class LivingWorldAIArmyMover {public:void DefendHomeTerritory(_STL::vector<BfmePod20>*,int,int,Rva0059CFAACallee*);void rva0059C93C(_STL::vector<BfmePod20>*,int,void*,Rva004FF5B7*,int);char gap00[0x18];int weightA,weightB,weightC;bool rva0059BD85(Range0059BD85*,int,void*);void rva0059C631(_STL::vector<BfmePod20>*,int,void*,Rva004FF5B7*,int);int WinTestBattle(ArmyMoverRegion*,int,int,const ModuleData*,void*,Rva004FF5B7*,int);void rva0059BE1F(ArmyMoverRegion*,int,int,PointerVector*,PointerVector*,PointerVector*,Rva004FF5B7*,int);};

struct PlayerListLogic {char gap00[0x8c];_STL::vector<Rva002E2903Player*>players;int numPlayers(){return players.size();}};
struct Rva00E02D6CCampaign {char gap00[0x1c];void*scenario;};
class Rva00E02D6C {public:char gap00[0x10];int current;_STL::vector<Rva00E02D6CCampaign*>campaigns;Rva00E02D6CCampaign*getCurrentCampaign(){return campaigns[current];}};
extern Rva00E02D6C*TheCampaignManager;
class Rva004FD448 {public:void rva004FD571(int,PointerVector*,int*)const;};
class Rva004FD4D4 {public:void rva004FD4D4(int,PointerVector*,int*)const;};
class Rva002E0A9FElem {public:int rva002E0A9F(void*);};
struct ArmyObject {char gap00[0x20];int id;};
class Rva005003DF {public:int rva005003DF(int,const int&,int*)const;};
struct Rva004FFA6ESource;
class Rva004FFA6E {public:bool rva004FF9DC(int,int,Rva004FFA6ESource*const&);};
class Rva002B82D5 {public:~Rva002B82D5();char trees[24];};
class Rva0050055D:public Rva002B82D5 {public:Rva0050055D(const Rva0050055D&);IntTree&first(){return *(IntTree*)this;}};
namespace _STL {
template<> _STL::pair<IntTree::iterator,IntTree::iterator>IntTree::equal_range(const int&);
template<class V,class L,class R>static inline bool operator!=(const _Rb_tree_iterator<V,L>&a,const _Rb_tree_iterator<V,R>&b){return a._M_node!=b._M_node;}
}
void LivingWorldAIArmyMover::rva0059C93C(_STL::vector<BfmePod20>*moves,int playerID,void*unused,Rva004FF5B7*info,int difficulty) {
 Rva002E2903Player*player=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(playerID,0);
 int faction=player->faction;
 DefendHomeTerritory(moves,playerID,(int)unused,(Rva0059CFAACallee*)info);
 if(difficulty>2)rva0059C631(moves,playerID,unused,info,difficulty);
 PointerVector targets;targets.clear();
 int found=0;
 void*scenario=TheCampaignManager->getCurrentCampaign()->scenario;
 ((Rva004FD448*)scenario)->rva004FD571(faction,&targets,&found);
 for(int i=0;i<((PlayerListLogic*)TheLivingWorldLogic)->numPlayers();++i) {
  Rva002E2903Player*other=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B52A8(i);
  if(!(unsigned char)((Rva002E071E*)other)->rva002E0BC0(playerID)) {
   int count=0;
   int otherID=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B52A8(i)->id;
   ((Rva004FD4D4*)scenario)->rva004FD4D4(otherID,&targets,&count);
  }
 }
 StrategyArmies*armies=(StrategyArmies*)((Rva004FF9B6*)info)->rva004FF9B6(playerID);
 for(unsigned a=0;a<armies->size();++a) {
  ArmyObject*army=(ArmyObject*)((Rva002E0A9FElem*)player)->rva002E0A9F((void*)(*armies)[a].id);
  unsigned j;
  for(j=0;j<moves->size();++j)if((*moves)[j].m_id==army->id)break;
  if(j<moves->size())continue;
  ArmyMoverRegionInfo*from=info->get((*armies)[a].region->id);
  Rva004FF5B7Iter fromIt=info->rva004FF5B7((*armies)[a].region->id);
  int closestDistance=9999;
  int closest=((Rva005003DF*)info)->rva005003DF(playerID,from->id,&closestDistance);
  int targetID=-1,targetDistance=9999;
  for(unsigned t=0;t<targets.size();++t) {
   int distance=rva0050059A(from->id,((ArmyMoverRegion*)targets[t])->id);
   if(distance<targetDistance && !(unsigned char)((Rva002E071E*)player)->rva002E0BC0(((ArmyMoverRegion*)targets[t])->owner)) {
    targetDistance=distance;targetID=((ArmyMoverRegion*)targets[t])->id;
   }
  }
  Rva0050055D distances(*(Rva0050055D*)&((IntMap*)&g_Va00E04544)->find(from->id)->second);
  _STL::pair<IntTree::iterator,IntTree::iterator> zeroRange=distances.first().equal_range(0);
  IntTree::iterator best=zeroRange.first;
  int bestScore=from->m_08+from->m_1c.size()*3;
  if(((Rva004FFA6E*)info)->rva004FF9DC(playerID,1,(Rva004FFA6ESource*const&)fromIt.m_ptr))bestScore+=5+from->m_10.size()*5;
  _STL::pair<IntTree::iterator,IntTree::iterator> range=distances.first().equal_range(1);
  for(IntTree::iterator it=range.first;it!=range.second;++it) {
   Rva004FF5B7Iter region=info->rva004FF5B7(it->second);
   int score=region.m_ptr->region.m_08;
   ArmyMoverRegion*r=(ArmyMoverRegion*)((Rva0020EAF6View*)((StrategyLogic*)TheLivingWorldLogic)->getManager())->rva0020EAF6(region.m_ptr->region.id);
   int outcome=WinTestBattle(r,1,playerID,(const ModuleData*)army,unused,info,difficulty);
   if(r->enabled) {
   if(region.m_ptr->key==-1) {
    score+=10;
    if(rva0050059A(region.m_ptr->region.id,closest)<closestDistance)score+=10;
    if(targetID!=-1 && rva0050059A(region.m_ptr->region.id,targetID)<targetDistance)score+=15;
    if(outcome!=2)score+=10;
   } else if((unsigned char)((Rva002E071E*)((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(playerID,0))->rva002E0BC0(region.m_ptr->key)) {
    score+=5+region.m_ptr->region.m_1c.size()*3;
    if(rva0050059A(region.m_ptr->region.id,closest)<closestDistance)score+=10;
    if(targetID!=-1 && rva0050059A(region.m_ptr->region.id,targetID)<targetDistance)score+=15;
    if(((Rva004FFA6E*)info)->rva004FF9DC(playerID,2,(Rva004FFA6ESource*const&)region.m_ptr)) {
     if(outcome!=2)score+=10;
     score+=region.m_ptr->region.m_10.size()*5;
    }
   } else {
    if(targetID!=-1 && rva0050059A(region.m_ptr->region.id,targetID)<targetDistance)score+=15;
    if(outcome==0)score+=40;
    else if(outcome==1)score+=25;
    else if(score<10)score=0;
    else score-=10;
   }
   } else score=0;
   if(outcome!=1) {
    for(unsigned m=0;m<moves->size();++m)
     if((*moves)[m].m_id!=army->id && (*moves)[m].m_flag && (*moves)[m].m_step==it->second)score>>=1;
   }
   if(score>bestScore){bestScore=score;best=it;}
  }
  if(best->first>0) {
   BfmePod20 move;move.m_id=army->id;move.m_flag=true;move.m_08=0;move.m_step=best->second;moves->push_back(move);
  }
 }
}
