// ?rva002A71BC@Rva002A71BC@@QAEXH_N@Z
// partial score=0.92 date=2026-10-13
// ?rva002A71BC@Rva002A71BC@@QAEXH_N@Z
// partial score=0.9 date=2026-10-11
// cl: /O1 /G7 /MD /DNDEBUG /arch:SSE
class Player;
class PlayerList { public: int rva002A7C0B(bool); Player *getNthPlayer(int); };
class GameLogic;
class GlobalData;
struct LANGameInfo;
struct Rva0059E647World;
extern PlayerList *ThePlayerList;
extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern LANGameInfo *g_Rva00E02EEC;
extern Rva0059E647World *g_rva0059E647World;
class BfmeGlob939D { public: char bfmeCall939D(); };
struct Rva002E0CD4 { int rva002E14DD() const; };
struct CommandPair { int initial; int maximum; };
struct CommandDefaultsView {
 char prefix[0xdec];
 CommandPair human[2];
 char gap[8];
 CommandPair computer[2];
 CommandPair multiplayer[7][2];
};
struct CommandPlayerView { char prefix[0x5c]; int type; };
struct CommandWorldView {
 char prefix[0x98]; Rva002E0CD4 *player;
 char gap[0xb4-0x9c]; bool tactical;
};
struct CommandLogicView { char prefix[0x114]; int mode; };
struct CommandGameInfoView { char prefix[0x6c]; int percentage; };
class Rva002A71BC {
public:
 void rva002A71BC(int, bool);
private:
 int unknown0, total, unknown8, unknownC, maximum, playerIndex;
 int additionalHero, additionalNormal;
 char gap[0x2c-0x20]; bool preserved;
};
void Rva002A71BC::rva002A71BC(int index, bool hero) {
 if(index<0 || index>=20 || !ThePlayerList || !TheGameLogic) return;
 playerIndex=index;
 int maxPoints=0;
 int points=0;
 if(((BfmeGlob939D *)TheGameLogic)->bfmeCall939D()) {
  int count=ThePlayerList->rva002A7C0B(true);
  CommandDefaultsView *data=(CommandDefaultsView *)TheWritableGlobalData;
  CommandPair *normal;
  CommandPair *heroes;
  if(count>=8) { heroes=&data->multiplayer[6][1]; normal=&data->multiplayer[6][0]; }
  else if(count>=7) { heroes=&data->multiplayer[5][1]; normal=&data->multiplayer[5][0]; }
  else if(count>=6) { heroes=&data->multiplayer[4][1]; normal=&data->multiplayer[4][0]; }
  else if(count>=5) { heroes=&data->multiplayer[3][1]; normal=&data->multiplayer[3][0]; }
  else if(count==4) { heroes=&data->multiplayer[2][1]; normal=&data->multiplayer[2][0]; }
  else if(count==3) { heroes=&data->multiplayer[1][1]; normal=&data->multiplayer[1][0]; }
  else { heroes=&data->multiplayer[0][1]; normal=&data->multiplayer[0][0]; }
  if(hero) { points=heroes->initial; maxPoints=heroes->maximum; }
  else { points=normal->initial; maxPoints=normal->maximum; }
  points+=additionalNormal*normal->initial;
  points+=additionalHero*heroes->initial;
 } else {
  Player *player=ThePlayerList->getNthPlayer(playerIndex);
  if(!player) return;
  CommandDefaultsView *data=(CommandDefaultsView *)TheWritableGlobalData;
  if(((CommandPlayerView *)player)->type==0) {
   if(hero) { points=data->human[1].initial; maxPoints=data->human[1].maximum; }
   else { points=data->human[0].initial; maxPoints=data->human[0].maximum; }
   CommandWorldView *world=(CommandWorldView *)g_rva0059E647World;
   if(world && world->tactical) {
    Rva002E0CD4 *lwPlayer=world->player;
    if(lwPlayer) points+=lwPlayer->rva002E14DD();
   }
  } else {
   if(hero) { points=data->computer[1].initial; maxPoints=data->computer[1].maximum; }
   else { points=data->computer[0].initial; maxPoints=data->computer[0].maximum; }
  }
 }
 if(!preserved || maxPoints>maximum) maximum=maxPoints;
 if(!preserved || points>total) total=points;
 if(g_Rva00E02EEC && ((CommandLogicView *)TheGameLogic)->mode==3)
  maximum=maximum*((CommandGameInfoView *)g_Rva00E02EEC)->percentage/100;
}
