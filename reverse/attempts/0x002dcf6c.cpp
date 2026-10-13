// ?rva002DCF6C@GameState@@QAEXPAVSnapshot@@I@Z
// partial score=0.985 date=2026-10-13
// ?rva002DCF6C@GameState@@QAEXPAVSnapshot@@I@Z
// partial score=0.995 date=2026-10-13
// ?rva002DCF6C@GameState@@QAEXPAVSnapshot@@I@Z
// partial score=0.983367198838897 date=2026-10-10
// ?rva002DCF6C@GameState@@QAEXPAVSnapshot@@I@Z
// partial score=0.983367198838897 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/moduledata /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /O1 /G7  /arch:SSE /DNDEBUG /MD /EHsc
// stlport
#include <list>
#include <string.h>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Rva0004224C { public:Rva0004224C *rva0004224C(); };
class GameStateFPScope {
public:
 GameStateFPScope() {((Rva0004224C*)this)->rva0004224C();}
 ~GameStateFPScope() {if(TheGameLogic)--((LogicFPView*)TheGameLogic)->depth;}
private:struct LogicFPView {char opaque[0x1B4];int depth;};
};
class ObjectSellInfo;
struct BfmeSpecialPowerTimer8 { unsigned int m_templateID; unsigned int m_readyFrame; };
class GameState {
 char opaque[0xE0C];
 _STL::list<ObjectSellInfo*> m_post;
 _STL::list<BfmeSpecialPowerTimer8> m_marks;
public:
 void rva002DCF6C(Snapshot*,unsigned);
};
void GameState::rva002DCF6C(Snapshot *snapshot,unsigned sequence)
{
 if(!snapshot)return;
 const char *name=snapshot->GetSnapshotName();
 ObjectSellInfo *postCopy=(ObjectSellInfo*)snapshot;
 if(name && !strcmp(name,"Object"))m_post.push_front(postCopy);
 else {
  if(name && !strcmp(name,"Weapon"))return;
  m_post.push_back(postCopy);
 }
 BfmeSpecialPowerTimer8 record;
 BfmeSpecialPowerTimer8 *rp = &record;
 rp->m_templateID = (unsigned)snapshot;
 rp->m_readyFrame = sequence;
 _STL::list<BfmeSpecialPowerTimer8> *mp = &m_marks;
 mp->push_back(*rp);
}
