// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??0LivingWorldAutoResolveBattle@@QAE@ABUPlayerStorage@@@Z, retail 0x004fa3c9, 495 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// Native4FA3C9..4FA5B8 and WB12E96E0. Provider storage views only;
// unresolved member callbacks remain unadmitted rather than inventing pins.
#include <vector>
#include <map>
struct BfmeE16 {float x,y,z,w;};
struct BfmePod52 {int a[13];};
struct Rva004F6986 {char bytes[8];};
struct Rva004F7D7FRecord {char bytes[1];};
class ModuleData;
typedef _STL::vector<BfmePod52> PlayerCopy;
typedef _STL::vector<Rva004F6986> PairReserve;
typedef _STL::vector<const ModuleData*> PointerProvider;
typedef _STL::vector<Rva004F7D7FRecord> UnitCleanup;
namespace _STL {
template<> PlayerCopy::vector(const PlayerCopy&);
template<> void PairReserve::reserve(unsigned);
template<> void PointerProvider::reserve(unsigned);
template<> inline __declspec(noinline) void PointerProvider::push_back(const ModuleData *const&x) {
 if(this->_M_finish != this->_M_end_of_storage._M_data) {
  _Construct(this->_M_finish,x); ++this->_M_finish;
 } else _M_insert_overflow(this->_M_finish,x,_IsPODType(),1UL,true);
}
template<> UnitCleanup::~vector();
}
class LivingWorldAutoResolveResourceBonusSchedule {public:int *getBonusForResourceAmount(int);};
class Rva004F5FD8 {
public:__declspec(nothrow) Rva004F5FD8(const Rva004F5FD8&);virtual ~Rva004F5FD8();
private:int words[10];
};
struct ArmyPair {int a[2];};
class ArmySummary {public:char prefix[0x40];_STL::vector<ArmyPair> entries;};
struct Rva0040DC56Element {int value;};
typedef _STL::vector<Rva0040DC56Element> EntryVector;
struct PlayerRecord {
 _STL::map<int,ArmySummary*> reinforcements;
 EntryVector entries;int opaque18[3];
 LivingWorldAutoResolveResourceBonusSchedule *schedule;
 Rva004F5FD8 *bonusInput;int side,opaque30;
};
class Rva004FA168Storage {public:
 unsigned start,finish,capacity;
 Rva004FA168Storage() {
 typedef _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > H;
 ((H*)this)->H::_Vector_base(_STL::allocator<BfmeE16>());
 }
 ~Rva004FA168Storage(){((UnitCleanup*)this)->UnitCleanup::~vector();}
};
class Rva004FA168Map {
public:Rva004FA168Map();~Rva004FA168Map();
private:unsigned words[3];
};
struct HeaderStorage {
 unsigned start,finish,capacity;
 __forceinline HeaderStorage() {
 typedef _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> > H;
 ((H*)this)->H::_Vector_base(_STL::allocator<BfmeE16>());
 }
 ~HeaderStorage();
 void push(Rva004F5FD8 *const&p) {((PointerProvider*)this)->push_back((const ModuleData *const&)p);}
};
struct PlayerStorage {
 PlayerRecord *start,*finish,*capacity;
 PlayerStorage(const PlayerStorage&p){((PlayerCopy*)this)->PlayerCopy::vector(*(const PlayerCopy*)&p);}
 ~PlayerStorage();
 unsigned size()const{return finish-start;}
};
class Rva004F7DF9Vector {public:void reserve(unsigned);};
class Rva004F6187 {public:void rva004F61B1();};
class LivingWorldAutoResolveBattle {
public:LivingWorldAutoResolveBattle(const PlayerStorage&);
 void rva004F68B8(unsigned,bool);
 void rva004F9658(Rva004FA168Storage&,EntryVector&,ArmySummary*,unsigned,bool);
 void buildReinforcementMaps();void addUnitsForCurrentRound(int);
private:PlayerStorage players;Rva004FA168Storage currentUnits[2];Rva004FA168Map maps[2];
 HeaderStorage combined,bonusInputs,bonuses,opaque60,opaque6c;
 int winner,roundNumber;
};
LivingWorldAutoResolveBattle::LivingWorldAutoResolveBattle(const PlayerStorage&input):players(input) {
 roundNumber=0;
 ((PointerProvider*)&bonusInputs)->reserve(players.size());
 unsigned counts[2];
 for(int side=0;side<2;++side)counts[side]=0;
 for(unsigned index=0;index<players.size();++index) {
  PlayerRecord &player=players.start[index];
  if(player.bonusInput)bonusInputs.push(new Rva004F5FD8(*player.bonusInput));
  else bonusInputs.push(0);
  bonuses.push(0);
  rva004F68B8(index,true);
  rva004F9658(currentUnits[player.side],player.entries,0,index,true);
  counts[player.side]+=player.entries.size();
  _STL::map<int,ArmySummary*>::iterator end=player.reinforcements.end();
  for(_STL::map<int,ArmySummary*>::iterator p=player.reinforcements.begin();p!=end;++p) {
   ArmySummary *army=p->second;
   counts[player.side]+=army->entries.size();
  }
 }
 unsigned total=0;
 for(int side=0;side<2;++side) {
  total+=counts[side];((Rva004F7DF9Vector*)&currentUnits[side])->reserve(counts[side]);
 }
 ((PairReserve*)&combined)->reserve(total);
 buildReinforcementMaps();addUnitsForCurrentRound(1);
 winner=-1;((Rva004F6187*)this)->rva004F61B1();
}
