// Native 0x0059D7C4..0x0059D8A5, 225B, RET0C, unused this.
// WB14FEFB0 and caller59DD3F establish eight per-type counts over two
// stride20 vectors, each record holding a tree header at +4. Owner entry
// vectors begin at +14/+20; the store map starts at +4. Original names
// and semantic type spellings remain unidentified. The inline by-value
// player lookup reproduces the native temporary key lifetime.
// cl: /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <map>
#include <vector>
typedef _STL::map<int,int> CountMap;
struct TallyRecord20 {int field00;CountMap counts;int field10;};
struct TallyPlayer {char pad[0x14];_STL::vector<TallyRecord20> first,second;};
struct TallyWorld {int field00;CountMap players; inline TallyPlayer*getPlayer(int id){return (TallyPlayer*)&players.find(id)->second;}};
class Rva0059DD3F {public:void rva0059D7C4(int,TallyWorld*,int*);};
void Rva0059DD3F::rva0059D7C4(int playerID,TallyWorld*info,int*out) {
 for(int i=0;i<8;++i)out[i]=0;
 TallyPlayer*player=info->getPlayer(playerID);
 for(unsigned i=0;i<player->first.size();++i) {
  for(CountMap::iterator p=player->first[i].counts.begin();p!=player->first[i].counts.end();++p)out[p->first]+=p->second;
 }
 for(unsigned i=0;i<player->second.size();++i) {
  for(CountMap::iterator p=player->second[i].counts.begin();p!=player->second[i].counts.end();++p)out[p->first]+=p->second;
 }
}
