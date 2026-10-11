// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Full native5A9824..5A990B and WorldBuilder1525700 establish AIEnemyManager::update.
// Native source-path literal names this file; matched PlayerList, POD erase,
// sort and random providers corroborate the WorldBuilder control flow.
// Owner0, vector4, eight-byte (player index, float priority) records and selected
// index14 are native facts. Counter10 remains neutral. BfmeE8/BfmePod8 are
// existing library stand-ins: erase touches only POD storage; sort uses float4.
// Priority350B remains unrowed. Its target-proven float/thiscall/RET4 binding
// retains the neutral bank name; the unresolved Coord3D return view is not imported.
// ThePlayerList uses the sole converged global spelling. No private Player layout.
#include <vector>
#include <algorithm>
struct BfmeE8 { int a; float b; };
struct BfmePod8 { int a[2]; };
namespace _STL {
 template<> BfmePod8 *vector<BfmePod8>::erase(BfmePod8 *);
 template<> void sort<BfmeE8 *>(BfmeE8 *,BfmeE8 *);
}
class Player;
class PlayerList { public: Player *getNthPlayer(int); };
extern PlayerList *ThePlayerList;
class Rva002AA22AByteField { public: unsigned char get()const; };
struct AIEnemyPlayerPrefix { char unknown00[0x54]; int index; };
int GetGameLogicRandomValue(int,int,char *,int);
class Rva005A9562 { public: float rva005A92DE(void *); };
class AIEnemyManager {
 void *owner;
 _STL::vector<BfmeE8> enemies;
 unsigned counter;
 int chosen;
public:
 void update();
};
void AIEnemyManager::update()
{
 bool choose=chosen==-1;
 for(BfmeE8 *item=enemies.begin();item!=enemies.end();) {
  Player *player=ThePlayerList->getNthPlayer(item->a);
  if(!player || ((Rva002AA22AByteField *)player)->get()) {
   if(((AIEnemyPlayerPrefix *)player)->index==chosen)choose=true;
   item=reinterpret_cast<BfmeE8 *>(reinterpret_cast<_STL::vector<BfmePod8> *>(&enemies)->erase(reinterpret_cast<BfmePod8 *>(item)));
  }else ++item;
 }
 if(enemies.empty()) { chosen=-1; return; }
 if(!choose)return;
 for(BfmeE8 *item=enemies.begin();item!=enemies.end();++item)
  item->b=((Rva005A9562 *)this)->rva005A92DE(ThePlayerList->getNthPlayer(item->a));
 _STL::sort<BfmeE8 *>(enemies.begin(),enemies.end());
 if(enemies.size()>=2 &&
    GetGameLogicRandomValue(1,100,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITargetChooser\\AIEnemyManager.cpp",122)<=50 &&
    !(enemies[1].b-enemies[0].b>1000.0f))
  chosen=enemies[1].a;
 else chosen=enemies[0].a;
}
