// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.95145 date=2026-10-13
// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.99 date=2026-10-13
// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.99 date=2026-10-13
// cl: /G7 /O1 /arch:SSE /Oy- /MD /ICode/Libraries/Include/Lib /I.
//
// Retail 0x005C61EE (234B, ret 4): TopFast reverse. 234/234 size-exact in
// SlideTopUpdate.cpp next to the rowed SlideFromTop update (0x005C6106,
// prev-row end == start). Sole wall: pure xmm0<->xmm1 swap in the slowdown
// block (retail slowed-value in xmm0 with zero in xmm1; this TU computes
// slowed in xmm1 with zero in xmm0). Tried, all neutral (same 234 swap):
// clamp operand order both ways, else 0.0f-x vs unary minus, mul operand
// order both ways, out copy-then-update (worse: size mismatch).
// Structure that closed everything else: startPos struct copy (own homes
// [ebp-0xc/-8], x dead), cur in scalar regs (no home), vel home [ebp-0x14],
// endPos struct copy (x dead-stored to startX home), setVel via out struct
// (vel.x self-copy), setFinished BEFORE winSetPosition in finish branch.
// Next lever: what pins slowed to xmm0 (first xmm value takes xmm0? named
// bound local? different mul spelling?).
struct Coord2D;
struct RvaTopVelocity { float x,y; };
#include "Code/Libraries/Include/Lib/ICoord2D.h"
class GameWindow { public: int winSetPosition(int,int); };
class AnimateWindow {
public:
 Coord2D getVel();
 void setVel(RvaTopVelocity value) { m_velocity=value; }
 void *vptr; unsigned delay; ICoord2D start,end,current,rest;
 GameWindow *window; RvaTopVelocity m_velocity;
 unsigned startTime,endTime; int animType; bool needsFinish,finished;
};
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
class ProcessAnimateWindowSlideFromTopFast {
public:
 virtual ~ProcessAnimateWindowSlideFromTopFast();
 virtual void initAnimateWindow(AnimateWindow*);
 virtual void initReverseAnimateWindow(AnimateWindow*,unsigned);
 virtual bool updateAnimateWindow(AnimateWindow*);
 virtual bool reverseAnimateWindow(AnimateWindow*);
 virtual void setMaxDuration(unsigned);
 RvaTopVelocity maxVel; int slowThreshold; float slowRatio,speedRatio;
};
bool ProcessAnimateWindowSlideFromTopFast::reverseAnimateWindow(AnimateWindow *a)
{
 if(!a) return true;
 if(a->finished) return true;
 unsigned startTime=a->startTime;
 if(timeGetTime()<startTime) return false;
 GameWindow *win=a->window;
 if(!win) return true;
 union { ICoord2D position; RvaTopVelocity velocity; } scratch;
 ICoord2D startPos=a->start;
 int curX=a->current.x;
 int curY=a->current.y;
 typedef void (AnimateWindow::*VelocityOutput)(RvaTopVelocity*);
 (a->*reinterpret_cast<VelocityOutput>(&AnimateWindow::getVel))(&scratch.velocity);
 curY+=(int)scratch.velocity.y;
 if(curY<startPos.y) {
  a->finished=true;
  win->winSetPosition(curX,startPos.y);
  return true;
 }
 win->winSetPosition(curX,curY);
 a->current.x=curX; a->current.y=curY;
 ICoord2D endPos=a->end;
 float slowed;
 if(endPos.y-curY<=slowThreshold)
  slowed=scratch.velocity.y*speedRatio;
 else
  slowed=-maxVel.y;
 if(slowed<-maxVel.y)
  slowed=-maxVel.y;
 RvaTopVelocity out;
 out.x=scratch.velocity.x;
 out.y=slowed;
 a->setVel(out);
 return false;
}
