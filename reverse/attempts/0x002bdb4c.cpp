// ?logicMessageDispatcher@LivingWorldLogic@@QAEXPAVGameMessage@@PAX@Z
// partial score=0.99845 date=2026-10-12
// ?logicMessageDispatcher@LivingWorldLogic@@QAEXPAVGameMessage@@PAX@Z
// cl: /I. /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native body3058 plus112B table; landing extent3170. Partial evidence, not progress.
// See reverse/attempt_evidence/astra-high-a/dispatcher-partial/integration-notes.txt.
#include "reverse/attempt_support/astra-high-a/dispatcher-home-snapshot.inc"

struct DispatcherPlayer {
 char pad00[0x14]; int id; char pad18[0x44-0x18];int kind;
 char pad48[0x2b4-0x48];int resolve,exitVote,loadVote,startVote,ready;
 char pad2c8[0x3c4-0x2c8];bool gone,localFlag;
};
class Player {public:char pad00[0x50];int nameKey;};
class PlayerList {public:Player *getNthPlayer(int);};
extern PlayerList *ThePlayerList;
enum NameKeyType { DISPATCH_KEY_INVALID=-1 };
class NameKeyGenerator {public:NameKeyType nameToKey(const AsciiString&);};
extern NameKeyGenerator *TheNameKeyGenerator;
struct LANGameInfo;extern LANGameInfo *g_Rva00E02EEC;
struct DispatcherGameInfo {char pad00[0x80];int preference;};
class GameInfo {public:GameSlot*getSlot(int);};
struct DispatcherGameLogic {char pad00[0x38];int frame;char pad3c[8];bool field44;char pad45[0x114-0x45];int field114;};
class MessageStream {public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14();virtual void s18();virtual void s1c();virtual void s20();virtual void s24();virtual void s28();virtual void s2c();virtual void s30();virtual void s34();virtual void s38();virtual void s3c();virtual void s40();virtual void s44();virtual GameMessage *append(int);
};
extern MessageStream *MessageStreamSubsystem;
struct DispatcherSlot {char pad00[0x34];AsciiString name;char pad38[0x4c-0x38];int id;};
class BfmeSelectionState {public:bool isSelectionLocked()const;};
class Rva002E0699 {public:int rva002E0699();};
class Rva002B9349 {public:void rva002B9349(int,int);};
class Rva002B9386 {public:void rva002B9386(ScienceType);};
class Rva003F1093 {public:void rva003F1CA2(CreateAHeroData*,bool);};
class Rva003F1C56Plot;struct Rva003F1BD3TemplateView;
class ArmorTemplate;
class Rva002B6498 {public:ArmorTemplate *rva002B6498(NameKeyType);};
class Rva002BAF01 {public:void rva002BAF01(struct Rva002BAF01Region*,CreateAHeroData*);};
class AptMessageBox {public:static void Show(void*,void*,void*);static void Change(void*,void*,void*);};
static __forceinline void dispatchShow(int kind,const UnicodeString&title,const UnicodeString&body){AptMessageBox::Show((void*)kind,(void*)&title,(void*)&body);}
static __forceinline void dispatchChange(int kind,const UnicodeString&title,const UnicodeString&body){AptMessageBox::Change((void*)kind,(void*)&title,(void*)&body);}
class Rva0023D26F {public:void rva0023D26F(bool);};
class Rva0023D2DD {public:void rva0023D2DD();};
class LivingWorldManager {public:void rva0021100E();};
class Rva0021237E {public:void rva0021246D(struct Rva0021246DInput*);};
struct DispatcherResolver {void*logic;LivingWorldBattle*battle;};
class DispatcherSpawn {
 public:virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14(int);virtual void s18();virtual void s1c();virtual void s20();virtual void s24(int);virtual void s28(int);
};
class Rva004E0625 {public:int rva004E0625()const;};
static __declspec(noinline) bool rva002B2D5E(GameMessage*msg,void**out,int i){
 void *p=((Rva002BA8F1Logic*)TheLivingWorldLogic)->rva002B2579(msg->getArgument(i)->integer);
 if(!p)return false;*out=(void*)((Rva004E0625*)p)->rva004E0625();return *out!=0;
}
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
static __declspec(noinline) bool rva002B2CE7(GameMessage*msg,Rva0020E89C**out,int i){
 int key=((const volatile GameMessageArgumentType*)msg->getArgument(i))->integer;
 _ReadWriteBarrier();
 Rva0020EAF6View*m=*(Rva0020EAF6View**)((char*)TheLivingWorldLogic+0xb0);
 *out=(m?m:m)->rva0020EAF6(key);return *out!=0;
}
// Placeholder declaration until the private helper body is brought into this TU.
static void HandleSwapArmiesInBattleMessage(GameMessage*);
static __declspec(noinline) bool rva002B2DAD(GameMessage*msg,void**out,int i){
 if(i<0)return false; if(i>=(int)msg->getArgumentCount())return false;
 int key=((const volatile GameMessageArgumentType*)msg->getArgument(i))->integer;
 LivingWorldRegionManager*m=*(LivingWorldRegionManager**)((char*)TheLivingWorldLogic+0xb0);
 *out=m->rva0020E5BB(key);return *out!=0;
}
static __declspec(noinline) void DisbandArmy(void*self){
 ArmySummary *summary=((LivingWorldArmy*)self)->m_summary;
 int count=(int)((Rva002B3325Summary*)summary)->m_entries.size();
 for(int i=0;i<count;++i){
  ArmySummaryEntry*entry=(ArmySummaryEntry*)((Rva0040CB2CIndexedField*)summary)->get(i);
  if(CanDisbandArmyMember(entry)){entry->m_disbanded=true;entry->CancelUpgrades();}
 }
}
class DispatcherClient {
 public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14();virtual void s18();virtual void s1c();virtual void s20();virtual void s24();virtual void s28();virtual void s2c();virtual void s30();virtual void s34();virtual void s38();virtual void s3c();virtual void s40();virtual void s44();virtual void s48();virtual void s4c();virtual void s50();virtual void s54();virtual void s58();virtual void s5c();virtual void s60();virtual void s64();virtual void s68();virtual void s6c();virtual void s70();virtual void s74();virtual void s78();virtual void s7c();virtual void s80();virtual void s84();virtual void s88();virtual void s8c();virtual void s90();virtual void s94();virtual void s98();
};
static __declspec(noinline) bool rva002B2E31(GameMessage *message, int *out, int index, Rva003F468D *battle, int side, int player)
{
	if (index < 0) return false;
	if (index >= (int)message->getArgumentCount()) return false;
	int value = message->getArgument(index)->integer;
	*out = value;
	return value >= 0 && value < ((Rva003F4DCA *)battle)->rva003F4DCA(side, player);
}

// HandleSwapArmiesInBattleMessage, retail 0x002B4141 (179 bytes): WB's file-static
// in LivingWorldLogic.cpp; argument 0 is battle, argument 1 is side, argument 2
// is player, arguments 3 and 4 are army indices to swap.
static __declspec(noinline) void HandleSwapArmiesInBattleMessage(GameMessage *msg)
{
	Rva003F468D *battle;
	if (!rva002B2DAD(msg, (void **)&battle, 0))
		return;
	if (msg->getArgumentCount() <= 1)
		return;
	int side = msg->getArgument(1)->integer;
	if (side < 0)
		return;
	int numSides = (int)(((LivingWorldBattle*)battle)->m_sidesEnd - ((LivingWorldBattle*)battle)->m_sides);
	if (side >= numSides)
		return;
	if (msg->getArgumentCount() <= 2)
		return;
	int player = msg->getArgument(2)->integer;
	if (player < 0)
		return;
	if (player >= battle->rva003F4DAE(side))
		return;
	int armyIndex1;
	if (!rva002B2E31(msg, &armyIndex1, 3, battle, side, player))
		return;
	int armyIndex2;
	if (!rva002B2E31(msg, &armyIndex2, 4, battle, side, player))
		return;
	((LivingWorldBattle *)battle)->rva003F5397(side, player, armyIndex1, armyIndex2);
}


__forceinline void CancelArmyMemberDisband(LivingWorldArmy*army,int id){ArmySummaryEntryRef entry=army->m_summary->GetEntry(id);if(entry.m_entry)entry.m_entry->m_disbanded=false;}
void LivingWorldLogic::logicMessageDispatcher(GameMessage*msg,void*unused){
 if(!ThePlayerList)return;
 Player *sender=ThePlayerList->getNthPlayer(((const int*)msg)[5]);
 if(!sender)return;
 int key=sender->nameKey;
 DispatcherPlayer *player=0;
 for(int i=0;i<8;++i){
  if(!((Rva00210C66CmpBoolField*)TheGameLogic)->get()){player=(DispatcherPlayer*)m_players[0];break;}
  if(((GameInfo*)g_Rva00E02EEC)->getSlot(i)&&((GameInfo*)g_Rva00E02EEC)->getSlot(i)->isHuman()&&TheNameKeyGenerator->nameToKey(((DispatcherSlot*)((GameInfo*)g_Rva00E02EEC)->getSlot(i))->name)==key){
   int id=((DispatcherSlot*)((GameInfo*)g_Rva00E02EEC)->getSlot(i))->id;
   player=(DispatcherPlayer*)((Rva002BA8F1Logic*)this)->find(id,0);break;
  }
 }
 if(!player)return;
 switch(((const int*)msg)[4]){
 case 1701:
  if(TheGameLogic&&msg->getArgument(0)->integer==((DispatcherGameLogic*)TheGameLogic)->frame){GameMessage*out=MessageStreamSubsystem->append(29);out->appendIntegerArgument(1);}
  break;
 case 1704:{LivingWorldArmy*army;Rva0020E89C*region;
  if(getArmyFromMessage(&army,msg,0)&&rva002B2CE7(msg,&region,1)){
   struct Pos3{float x,y,z;};const Pos3*in=(const Pos3*)msg->getArgument(2);Pos3 pos;pos.x=in->x;pos.y=in->y;pos.z=in->z;armyMoveRequest(army,(Rva00318C32Ret*)region,(Coord2D*)&pos,1);
  }break;}
 case 1705:{LivingWorldArmy*army;if(getArmyFromMessage(&army,msg,0))rva002B2834(army,1);break;}
 case 1706:{Rva0020E89C*region;if(rva002B2CE7(msg,&region,0)){
  LivingWorldBuildPlot*plot=((LivingWorldRegion*)region)->rva003F088C(msg->getArgument(1)->integer);
  if(plot){ArmorTemplate*t=((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)msg->getArgument(2)->integer);if(t)((LivingWorldRegion*)region)->BuildBuilding((Rva003F1C56Plot*)plot,(const Rva003F1BD3TemplateView*)t);}
 }break;}
 case 1707:{Rva0020E89C*region;if(rva002B2CE7(msg,&region,0)){LivingWorldBuildPlot*plot=((LivingWorldRegion*)region)->rva003F088C(msg->getArgument(1)->integer);if(plot)((Rva003F1093*)region)->rva003F1CA2((CreateAHeroData*)plot,true);}break;}
 case 1708:{void*p;if(rva002B2D5E(msg,&p,0)){int key=msg->getArgument(1)->integer;if(key)((DispatcherSpawn*)p)->s14(key);}break;}
 case 1709:{void*p;if(rva002B2D5E(msg,&p,0)){int key=msg->getArgument(1)->integer;if(key)((DispatcherSpawn*)p)->s28(key);}break;}
 case 1710:{void*p;if(rva002B2D5E(msg,&p,0)){int key=msg->getArgument(1)->integer;((DispatcherSpawn*)p)->s24(key);}break;}
 case 1703:{
  LivingWorldBattle*battle=(LivingWorldBattle*)m_field0B0->rva0020E501(msg->getArgument(1)->integer);if(!battle)break;
  int choice=msg->getArgument(0)->integer;if(choice!=1&&choice!=2&&choice!=3)break;
  player->resolve=choice;int flags=0,active=0;
  for(int side=0;side<(int)(battle->m_sidesEnd-battle->m_sides);++side){
   for(int p=0;p<((Rva003F468D*)battle)->rva003F4DAE(side);++p){
    int choice=((Rva002E0699*)((Rva003F468D*)battle)->rva003F468D(side,p))->rva002E0699();
    if(choice==0)flags|=1;else if(choice==2)flags|=4;else if(choice==1){flags|=2;++active;}else if(choice==3){flags|=8;++active;}
   }
  }
  if(flags&1)break;
  if(flags&4){
   for(unsigned p=0;p<m_players.size();++p)if(m_players[p]){
    if(((Rva002E0699*)m_players[p])->rva002E0699()==2){
     battle->RetreatArmiesForPlayer(m_players[p]);
     ((Rva002B6126List*)((char*)this+0x6c))->forEach(&Rva002B6126Listener::notify,this,(int)m_players[p],(int)battle);
    }
    DispatcherPlayer*entry=(DispatcherPlayer*)m_players[p];if(!entry->kind)entry->resolve=0;
   }
   if(!battle->rva003F4538()){
    if(battle->rva003F459A()>0){battle->m_side=battle->rva003F45DF();OnBattleComplete(battle);}
    m_field0B0->rva0020FB8B(battle);break;
   }
   if(m_field0B0->rva0020E4C8())break;
  }
  if((unsigned char)((Rva002B254F*)this)->rva002B254F())rva002BD90D(2,(int)battle);
  else {DispatcherGameInfo*info=(DispatcherGameInfo*)g_Rva00E02EEC;if(info){
   if(((Rva00210C66CmpBoolField*)TheGameLogic)->get()&&active<((Rva002BA8F1Logic*)this)->rva002B5256(false)){flags&=~8;flags|=2;}
   int preference=info->preference;
   int first,second;
   if(preference==0){first=2;second=8;}else if(preference==1){first=8;second=2;}
   if(flags&first)rva002BD90D(first,(int)battle);else if(flags&second)rva002BD90D(second,(int)battle);
  }}
  break;
 }
 case 1717:{LivingWorldBattle*b=(LivingWorldBattle*)m_field0B0->rva0020E501(msg->getArgument(0)->integer);if(b)rva002BD90D(8,(int)b);break;}
 case 1702:{int turn=msg->getArgument(0)->integer;int phase=msg->getArgument(1)->integer;
  if(turn==m_turn&&phase==m_turnPhase){int id=msg->getArgument(2)->integer;DispatcherPlayer*p=(DispatcherPlayer*)((Rva002BA8F1Logic*)this)->find(id,0);if(p)p->ready=1;}break;}
 case 1720:{int id=msg->getArgument(0)->integer;*((bool*)this+0x175)=true;
  if(!((DispatcherGameLogic*)TheGameLogic)->field114&&((BfmeSelectionState*)this)->isSelectionLocked()&&((DispatcherPlayer*)m_localPlayer)->localFlag){rva002B88EC();break;}
  for(unsigned i=0;i<m_players.size();++i){DispatcherPlayer*p=(DispatcherPlayer*)((Rva002BA8F1Logic*)this)->rva002B52A8(i);if(!p->gone&&(unsigned char)((Rva002E071E*)p)->rva002E0BC0(id))RemovePlayer((LivingWorldPlayer*)p);}
  rva002B9DC7();if(!((BfmeSelectionState*)this)->isSelectionLocked())rva002B88EC();break;}
 case 1711:HandleSwapArmyMembersMessage(msg);break;
 case 1712:{LivingWorldArmy*army;if(getArmyFromMessage(&army,msg,0))CancelArmyMemberMove(army,msg->getArgument(1)->integer);break;}
 case 1713:{LivingWorldArmy*army;if(getArmyFromMessage(&army,msg,0))DisbandArmyMember(army,msg->getArgument(1)->integer);break;}
 case 1714:{LivingWorldArmy*army;if(getArmyFromMessage(&army,msg,0))DisbandArmy(army);break;}
 case 1715:{LivingWorldArmy*army;if(getArmyFromMessage(&army,msg,0))CancelArmyMemberDisband(army,msg->getArgument(1)->integer);break;}
 case 1716:HandleSwapArmiesInBattleMessage(msg);break;
 case 1719:{Rva0020E89C*r;if(rva002B2CE7(msg,&r,0)){int key=msg->getArgument(1)->integer;DispatcherPlayer*p=(DispatcherPlayer*)((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(key,0);if(p)((Rva002BAF01*)this)->rva002BAF01((Rva002BAF01Region*)r,(CreateAHeroData*)p);}break;}
 case 1721:{
  player->exitVote=msg->getArgument(0)->integer;
  if(player==(DispatcherPlayer*)m_localPlayer&&((DispatcherPlayer*)m_localPlayer)->exitVote==1)dispatchShow(4,UnicodeString(),TheGameText->fetch("APT:MultiplayerExitWaiting"));
  int result=1;
  for(unsigned i=0;i<m_players.size();++i){if(m_players[i]&&!((DispatcherPlayer*)m_players[i])->kind){int vote=((DispatcherPlayer*)m_players[i])->exitVote;if(vote==0){result=0;break;}if(vote!=1)result=vote;}}
  switch(result){
   case 0:break;
   case 1:
    if(((DispatcherPlayer*)m_localPlayer)->exitVote==1)Rva00437E9C(0);
    *((bool*)this+0x174)=true;rva002B88EC();
    for(unsigned i=0;i<m_players.size();++i)if(m_players[i])((DispatcherPlayer*)m_players[i])->exitVote=0;
    break;
   default:
    if(((DispatcherPlayer*)m_localPlayer)->exitVote==1)dispatchChange(0,UnicodeString(),TheGameText->fetch("APT:MultiplayerExitOverruled"));
    for(unsigned i=0;i<m_players.size();++i)if(m_players[i])((DispatcherPlayer*)m_players[i])->exitVote=0;
    break;
  }break;
 }
 case 1722:
  player->loadVote=msg->getArgument(0)->integer;
  for(unsigned i=0;i<m_players.size();++i){DispatcherPlayer*p=(DispatcherPlayer*)m_players[i];if(p&&!p->kind&&!p->gone&&p->loadVote!=1)return;}
  for(unsigned i=0;i<m_players.size();++i)if(m_players[i])((DispatcherPlayer*)m_players[i])->loadVote=0;
  ((DispatcherClient*)g_00DFEF18)->s94();*((bool*)this+0x176)=false;
  {Rva002B3740Item*p=((Rva002BA8F1Logic*)this)->rva002B2B2D();if(p)((Rva0021237E*)TheLivingWorldManager)->rva0021246D((Rva0021246DInput*)p);}
  *((bool*)this+0xb5)=false;((Rva0023D26F*)TheGameLogic)->rva0023D26F(true);break;
 case 1723:
  player->startVote=msg->getArgument(0)->integer;
  for(unsigned i=0;i<m_players.size();++i){DispatcherPlayer*p=(DispatcherPlayer*)m_players[i];if(p&&!p->kind&&!p->gone&&p->startVote!=1)return;}
  for(unsigned i=0;i<m_players.size();++i)if(m_players[i])((DispatcherPlayer*)m_players[i])->startVote=0;
  ((DispatcherClient*)g_00DFEF18)->s98();*((bool*)this+0x177)=false;
  TheLivingWorldManager->rva0021100E();*((bool*)this+0xb5)=true; m_fieldB6=false;
  ((Rva0023D26F*)TheGameLogic)->rva0023D26F(false);
  {GameLogic*logic=TheGameLogic;if(((Rva00210C66CmpBoolField*)logic)->get())logic->CreateWOTRMPPlayers();}
  ((Rva0023D2DD*)TheGameLogic)->rva0023D2DD();((DispatcherGameLogic*)TheGameLogic)->field44=true;break;
 case 1725:{
  if(!m_autoBattleResolver.get())break;void*b;
  if(rva002B2DAD(msg,&b,0)&&b==((DispatcherResolver*)m_autoBattleResolver.get())->battle){int id=player->id;((Rva002B9349*)m_autoBattleResolver.get())->rva002B9349(id,msg->getArgument(1)->integer);}break;
 }
 case 1726:{
  if(!m_autoBattleResolver.get())break;void*b;
  if(rva002B2DAD(msg,&b,0)&&b==((DispatcherResolver*)m_autoBattleResolver.get())->battle)((Rva002B9386*)m_autoBattleResolver.get())->rva002B9386((ScienceType)player->id);break;
 }
 case 1727:HandleMarkUnitForUpgradeMessage(msg);break;
 case 1728:HandleUnmarkUnitForUpgradeMessage(msg);break;
 }
}
