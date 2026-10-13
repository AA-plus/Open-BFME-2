// ?rva0059DD3F@Rva0059DD3F@@QAEXPAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@HPAVRva004FF8DA@@PAVRva004FF5B7@@HPAHH@Z
// cl: /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0x0059DD3F..0x0059DF60: 545 bytes, RET 0x1C.
// WB 0x014FEB80 and caller 0x004FB27E establish eight weighted type
// deficits, region threat ordering, and recruitment/unit picker calls.
// Names and layouts below are address-owned views, not recovered names.
// Keep STL reserve/push_back definitions visible: hiding them loses alias
// information, spills this, and prevents the retail sort pointer induction.
// The nested picker branches follow WB; a flattened continue changes codegen.
#include <map>
#include <vector>
class Rva00319CED;
struct BfmeE8 {int id;Rva00319CED*unit;};
struct Rva0059D90CSource {char pad[0x34];_STL::vector<int> first,second;};
class Rva004FF8DA;
class Rva004FF5B7;
class Rva0059CFAACallee;
struct Rva004FCD6DElement {short words[1];bool operator<(const Rva004FCD6DElement&x)const{return words[0]<x.words[0];}bool operator==(const Rva004FCD6DElement&x)const{return words[0]==x.words[0];}};
typedef _STL::map<Rva004FCD6DElement,int> RegionMap;
typedef _STL::pair<RegionMap::const_iterator,RegionMap::const_iterator> RegionRange;
class Rva005003C7 {public:RegionRange rva005003C7(Rva004FCD6DElement)const;};
class Rva004FF997Owner {public:int rva004FF997(int);};
class Rva0059DA34 {public:int rva0059DA34(int,int,bool,int,Rva004FF5B7*,int*);bool rva0059DB48(_STL::vector<BfmeE8>*,const Rva0059D90CSource*,Rva004FF8DA*,Rva004FF5B7*,int,int,int*);};
class Rva0059D90C {public:bool rva0059D90C(_STL::vector<BfmeE8>*,const Rva0059D90CSource*,Rva004FF8DA*,int,int*);};
typedef _STL::map<int,int> IntMap;
struct TallyWorld {int field00;IntMap players;inline int regionCount(int id){return *(int*)((char*)&players.find(id)->second+0x0c);}};
// ScienceType is the existing enum-vector provider spelling only. These
// records are observed region IDs; their original enum identity is unknown.
enum ScienceType { SCIENCE_INVALID=0 };
class Rva0059DD3F {public:
 void rva0059D7C4(int,TallyWorld*,int*);
 unsigned rva0059D8A5(int,int,Rva0059CFAACallee*);
 void rva0059DD3F(_STL::vector<BfmeE8>*,int,Rva004FF8DA*,Rva004FF5B7*,int,int*,int);
 float weights[8];int counts[8],tally[8];
};
void Rva0059DD3F::rva0059DD3F(_STL::vector<BfmeE8>*out,int playerID,Rva004FF8DA*types,Rva004FF5B7*info,int budget,int*spent,int difficulty){
 *spent=0;
 int current[8];rva0059D7C4(playerID,(TallyWorld*)info,current);
 Rva004FCD6DElement key={{(short)playerID}};
 RegionRange range=((Rva005003C7*)info)->rva005003C7(key);
 RegionMap::const_iterator p=range.first;
 int total=0;for(int i=0;i<8;++i)total+=current[i];
 for(int i=0;i<8;++i) {
  int desired=(int)(weights[i]*total);int one=1;
  const int&high=desired<one?one:desired;
  int missing=high-current[i];int zero=0;
  const int&remaining=missing<zero?zero:missing;
  counts[i]=remaining;
 }
 _STL::vector<ScienceType> regions;
 regions.reserve(((TallyWorld*)info)->regionCount(playerID));
 for(;p!=range.second;++p)regions.push_back((const ScienceType&)p->second);
 if(difficulty>3) {
  
  for(unsigned i=0;i<regions.size();++i) {
   unsigned best=rva0059D8A5(playerID,regions[i],(Rva0059CFAACallee*)info);
   for(unsigned j=i+1;j<regions.size();++j) {
    unsigned candidate=rva0059D8A5(playerID,regions[j],(Rva0059CFAACallee*)info);
    if(candidate>best){ScienceType tmp=regions[i];regions[i]=regions[j];regions[j]=tmp;best=candidate;}
   }
  }
 }
 
 for(unsigned i=0;i<regions.size();++i) {
  const Rva0059D90CSource*source=(const Rva0059D90CSource*)((Rva004FF997Owner*)info)->rva004FF997(regions[i]);
  if(source->second.size()+source->first.size()!=0) {
   int armyCount=((Rva0059DA34*)this)->rva0059DA34(*(int*)source,playerID,false,2,info,tally);
   if(difficulty>2) {
    if(armyCount==0) { ((Rva0059D90C*)this)->rva0059D90C(out,source,types,budget,spent); }
    else if(!((Rva0059DA34*)this)->rva0059DB48(out,source,types,info,playerID,budget,spent)) { ((Rva0059D90C*)this)->rva0059D90C(out,source,types,budget,spent); }
   } else { ((Rva0059D90C*)this)->rva0059D90C(out,source,types,budget,spent); }
  }
 }
}
