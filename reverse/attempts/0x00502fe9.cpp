// ?rva00502FE9@Rva00502FE9@@QAEXH@Z
// partial score=0.9151033207774306 date=2026-10-12
// ?rva00502FE9@Rva00502FE9@@QAEXH@Z
// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native502FE9..503554:1387B; WB12FB830 unnamed shared callgraph.
// Complete first reconstruction of the building/army-template table pass.
// Current body1386B/frame160 versus retail1387B/frame154. Remaining deltas:
// stack allocation, two vector-size load sequences, copied-record address
// materialization, and an extra saved-ESP slot around the tree hint copy.
// AsReference prevents the compiler from eliding the required second 92B
// record copy. Both copies and their destructors are present in the body.
// A diagnostic comparison mapped the unlanded447B distance helper5020CC
// and two29B _Vector_base constructors to211E58. Each constructor was
// independently whole-body verified with all relocations there; no alias
// row or pin was added. Ordinary resolution now verifies those folds and
// leaves only the distance helper unresolved.
// The original owner/method and record names remain unknown. Field offsets
// come from this native body; existing provider spellings and the12B vector/
// tree cleanup adapters preserve ABI without asserting original C++ types.
// In particular pair<const int,PodVectors>::second uses the existing12B
// cleanup provider as a storage adapter, not an upstream pair declaration.
// Blocked-on=0x005020CC remains applicable. This is evidence, not a match.
#include "ascii_string.h"
#include <vector>
#include <map>
#include <set>
enum ScienceType {SCIENCE_NONE=0};
enum NameKeyType {NAMEKEY_NONE=0};
class Rva0022C0CDSubsystem;extern Rva0022C0CDSubsystem*TheLivingWorldBuildingTemplateStore;
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva00E02D6C;extern Rva00E02D6C*TheCampaignManager;
class ArmorTemplate;class Rva002B6498 {public:ArmorTemplate*rva002B6498(NameKeyType);};
class Rva002E02F0 {public:void rva002E02F0(int,_STL::vector<ScienceType>*);};
class Rva002E2903Player {public:char gap[0x40];int score;};
class Rva002BA8F1Logic {public:Rva002E2903Player*find(int,unsigned*);};
class BuildingNuggetView {public:char gap[8];int type;int amount;};
class LivingWorldBuildingTemplate {public:BuildingNuggetView*findNugget(const AsciiString&)const;};
struct Rva003F751ANode {char gap[0x18];int value;};
class Rva003F751A {public:Rva003F751ANode*rva003F751A(const int*);};
struct StrengthenNugget {char gap[16];Rva003F751ANode*header;};
class Rva00319CED {public:bool rva00319CED();};
class Rva003B8E89 {public:void*rva003B8E89(void*);};
class Rva0040CB2CIndexedField {public:int get(int)const;};
class BfmeY1038 {public:int bfmeVal1038();};
class Rva0033A674 {public:void*rva0033A674();};
class ThingTemplate;class ThingFactory {public:const ThingTemplate*findTemplate(const AsciiString&);};extern ThingFactory*TheThingFactory;
struct TemplateView {char gap[0x5c4];int category;};
struct SummaryView {char gap[0x40];_STL::vector<_STL::pair<int,int> >entries;};
class Rva004E3184 {public:virtual ~Rva004E3184();Rva004E3184(const Rva004E3184&);char data[84];};
class Rva00500500 {public:Rva00500500(void*&,const Rva004E3184&);Rva00500500(const Rva00500500&);void*key;Rva004E3184 value;};
struct SpawnView {char gap[8];_STL::vector<Rva004E3184>entries;};
struct BfmePod88 {char body[88];};
typedef _STL::vector<BfmePod88> PodVector;
typedef _STL::vector<PodVector> PodVectors;
struct Rva00500EFARecord {char bytes[12];};
namespace _STL {template<> void vector<Rva00500EFARecord>::reserve(unsigned);}
namespace _STL {template<> void PodVectors::push_back(const PodVector&);}
struct Rva004FABE2 {
 _STL::_Vector_base<BfmePod88,_STL::allocator<BfmePod88> > data;
 Rva004FABE2():data(_STL::allocator<BfmePod88>()){}
 ~Rva004FABE2();
};
struct Rva00500E3D {
 _STL::_Vector_base<PodVector,_STL::allocator<PodVector> > data;
 Rva00500E3D():data(_STL::allocator<PodVector>()){}
 ~Rva00500E3D();
 PodVector&operator[](int i){return ((PodVectors*)this)->operator[](i);}
 void reserve(unsigned n){((_STL::vector<Rva00500EFARecord>*)this)->reserve(n);}
 void push_back(const Rva004FABE2&v){((PodVectors*)this)->push_back((const PodVector&)v);}
};
struct Rva004FFE96Element {char bytes[8];};
typedef _STL::set<Rva004FFE96Element> NativeSet;
namespace _STL {template<> NativeSet::set();}
struct Rva004FF582 {NativeSet data;~Rva004FF582();};
struct Rva005020AFSub:public Rva004FF582 {Rva005020AFSub(){};Rva005020AFSub(const Rva005020AFSub&);};
struct Rva0050245DElement {int key;Rva005020AFSub value;Rva0050245DElement(const int&,const Rva005020AFSub&);};
struct Rva00502667Element {int key;Rva005020AFSub value;Rva00502667Element(const Rva00502667Element&);};
struct Rva00502BCDMapped {char data[12];};
typedef _STL::map<int,Rva00502BCDMapped> SetMap;
namespace _STL {
template<> struct pair<const int,PodVectors> {const int first;Rva00500E3D second;pair(const int&,const PodVectors&);pair(const pair&);};
template<> void vector<ScienceType>::push_back(const ScienceType&);
template<> void PodVector::push_back(const BfmePod88&);

template<> SetMap::iterator SetMap::insert(SetMap::iterator,const SetMap::value_type&);
}
typedef _STL::map<int,PodVectors> VectorMap;
namespace _STL {template<> VectorMap::iterator VectorMap::insert(VectorMap::iterator,const VectorMap::value_type&);}
class Rva00500BF5Tree {public:typedef _STL::_Rb_tree_iterator<Rva00500500,_STL::_Nonconst_traits<Rva00500500> >Iterator;Iterator insertEqual(Iterator,const Rva00500500&);};
class Rva00501F2D {public:void rva0050247A();};class Rva005007CF {public:void rva00500AA6();};
static __forceinline const Rva00500500&AsReference(const Rva00500500&v){return v;}
void Rva005020CCBuildRegionDistances();
class Rva00502FE9 {public:void rva00502FE9(int);int commandBuilding,spawnBuilding,strengthBuilding,upgradeBuilding;_STL::vector<ScienceType>spawnBuildings;int commandPoints;float average;char gap24[12];int strengthenAmount,upgradeAmount;VectorMap vectors;SetMap sets;};
void Rva00502FE9::rva00502FE9(int playerID) {
 _STL::vector<ScienceType> buildings;
 int playerScore=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(playerID,0)->score;
 ((Rva002E02F0*)TheLivingWorldBuildingTemplateStore)->rva002E02F0(playerScore,&buildings);
 for(unsigned i=0;i<buildings.size();++i) {
  BuildingNuggetView*command=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("IncreaseCommandPoints"));
  BuildingNuggetView*spawn=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("SpawnArmy"));
  BuildingNuggetView*strengthen=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("StrengthenArmy"));
  BuildingNuggetView*upgrade=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("UpgradeTroops"));
  if(command && command->type!=1)command=0;
  if(command){commandBuilding=buildings[i];commandPoints=command->amount;}
  else if(strengthen){strengthBuilding=buildings[i];int key=1;StrengthenNugget*s=(StrengthenNugget*)strengthen;Rva003F751ANode*it=((Rva003F751A*)&s->header)->rva003F751A(&key);if(it!=s->header)strengthenAmount=it->value;}
  else if(upgrade){upgradeBuilding=buildings[i];upgradeAmount=10;}
  if(spawn){if(!command&&!strengthen&&!upgrade)spawnBuilding=buildings[i];spawnBuildings.push_back(buildings[i]);}
 }
 ((Rva00501F2D*)&vectors)->rva0050247A();((Rva005007CF*)&sets)->rva00500AA6();
 for(unsigned i=0;i<spawnBuildings.size();++i){
  int count=0;Rva00500E3D byCategory;byCategory.reserve(8);Rva004FABE2 empty;
  for(int j=0;j<8;++j)byCategory.push_back(empty);
  Rva005020AFSub ordered;
  SpawnView*spawn=(SpawnView*)((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)spawnBuildings[i]))->findNugget(AsciiString("SpawnArmy"));
  if(spawn)for(unsigned j=0;j<spawn->entries.size();++j){
   Rva004E3184&entry=spawn->entries[j];
   if(((Rva00319CED*)&entry)->rva00319CED()){
    SummaryView*summary=(SummaryView*)((Rva003B8E89*)TheCampaignManager)->rva003B8E89((char*)&entry+0x2c);
    int size=summary->entries.size();
    for(int k=0;k<size;++k){
     int row=((Rva0040CB2CIndexedField*)summary)->get(k);AsciiString name(*(AsciiString*)(row+4));
     const ThingTemplate*thing=TheThingFactory->findTemplate(name);
     byCategory[((TemplateView*)thing)->category].push_back((const BfmePod88&)entry);
     void*key=((Rva0033A674*)thing)->rva0033A674();
     ((Rva00500BF5Tree*)&ordered)->insertEqual(Rva00500BF5Tree::Iterator((_STL::_Rb_tree_node<Rva00500500>*)*(void**)&ordered),Rva00500500(AsReference(Rva00500500(key,entry))));
    }
    average+=(float)((BfmeY1038*)summary)->bfmeVal1038();++count;
   }
  }
  _STL::pair<const int,PodVectors> vectorPair(reinterpret_cast<const int&>(spawnBuildings[i]),(const PodVectors&)byCategory);
  { _STL::pair<const int,PodVectors> copied(vectorPair);vectors.insert(vectors.begin(),copied); }
  Rva0050245DElement setPair(reinterpret_cast<const int&>(spawnBuildings[i]),ordered);
  { Rva00502667Element copied((const Rva00502667Element&)setPair);sets.insert(sets.begin(),(const SetMap::value_type&)copied); }
  if(count>0)average/=count;else average=0;
 }
 Rva005020CCBuildRegionDistances();
}
