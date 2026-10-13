// ??0FullFadeTransition@@QAE@XZ
// partial score=0.9469793887704335 date=2026-10-13
// ??0FullFadeTransition@@QAE@XZ
// partial score=0.96 date=2026-10-13
// ??0FullFadeTransition@@QAE@XZ
// partial score=0.97 date=2026-10-13
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
// ??0FullFadeTransition@@QAE@XZ @ 0x0035F2B3 67B: derived ctor calling base
// ??0Rva001DBAA4 at 0x001DBAA4, vtable 0x0081663C (emitted by the Init TU's
// full view). Split TU: the owner Update TU builds under defaults while the
// ctor needs /O2 codegen (vtable store sunk below the start/end stores).
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/
// GameWindowTransitionsStyles.cpp FullFadeTransition::FullFadeTransition
// (frameLength/end, win NULL, drawState -1, forward TRUE); target adds
// pos/size zero and percent 0.0. Layout copied from FullFadeTransitionInit.cpp.
typedef int Int;
typedef bool Bool;
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif
class GameWindow;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva001DBAA4

{
 public:
 virtual ~Rva001DBAA4();
 Rva001DBAA4();
 Int m_frameLength;
// +0x04
 Bool m_isFinished;
// +0x08
 Bool m_isForward;
// +0x09
 Bool m_isReversed;
// +0x0a
 unsigned char m_pad0B;
// +0x0b
 GameWindow *m_win;
// +0x0c
 
}
;
class FullFadeTransition : public Rva001DBAA4

{
 public:
 virtual ~FullFadeTransition();
 virtual void init(GameWindow*); virtual void update(Int); virtual void reverse(); virtual void draw(); virtual void skip();
 FullFadeTransition();
 volatile Int m_startFrame;
// +0x10
 volatile Int m_endFrame;
// +0x14
 Int m_posX;
// +0x18
 Int m_posY;
// +0x1c
 Int m_sizeX;
// +0x20
 Int m_sizeY;
// +0x24
 float m_percent;
// +0x28
 Int m_drawState;
// +0x2c
 
}
;
FullFadeTransition::FullFadeTransition(){
m_startFrame = 0;
m_endFrame = 30;
m_posX = 0;
m_posY = 0;
m_sizeX = 0;
m_sizeY = 0;
m_percent = 0.0f;
_ReadWriteBarrier();
m_frameLength = m_endFrame;
m_isForward = TRUE;
m_drawState = -1;
m_win = 0;
}
