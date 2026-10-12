// ??0FullFadeTransition@@QAE@XZ
// partial score=0.93 date=2026-10-13
// ??0FullFadeTransition@@QAE@XZ
// partial score=0.93 date=2026-10-13
// cl: /O2 /DNDEBUG /MD /arch:SSE
// ??0FullFadeTransition@@QAE@XZ @0x0035F2B3 67B. R3 decode (retail bytes): base 0x1DBAA4, mem-inits start=0/end=30 (BEFORE the vtable store), vtable 0x81663C, pos/size zero, ecx=end, drawState via or-imm -1, win=0, percent=xmm0, frameLength=end-via-ecx, isForward=byte-1. So: : m_startFrame(0), m_endFrame(30) + m_frameLength = m_endFrame. BLOCKED: vtable needs reverse/skip slots (only init/update/draw rowed); Init/Update TUs declare ~FullFadeTransition but never define it so no TU emits the real vtable; dtor lives under Rva0035F1D0 in FamilyTailDtors (minimal view). Unblocks when reverse+skip land.
// FullFadeTransition ctor: base Rva001DBAA4 (Transition) then vtable 0x0081663C,
// start 0 end 0x1E pos/size zero percent 0.0 drawState -1 frameLength from end.
// Donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp
//   FullFadeTransition::FullFadeTransition (frameLength/end START/END win NULL drawState -1 forward TRUE).
// Target evidence: vtable 0x0081663C (init 0x0035F1DF slot1 update 0x0035F241 slot2),
// factory 0x0035F312 news 0x30, sole caller 0x0035F334, base ctor row 0x001DBAA4.
class GameWindow;

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_frameLength; // +4
	bool m_isFinished; // +8
	bool m_isForward; // +9
	bool m_isReversed; // +0xA
	unsigned char m_pad0B; // +0xB
	GameWindow *m_win; // +0xC
};

class FullFadeTransition : public Rva001DBAA4
{
public:
	virtual ~FullFadeTransition();
	virtual void init(GameWindow *win);
	virtual void update(int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();
	FullFadeTransition();
	int m_startFrame; // +0x10
	int m_endFrame; // +0x14
	int m_posX; // +0x18
	int m_posY; // +0x1C
	int m_sizeX; // +0x20
	int m_sizeY; // +0x24
	float m_percent; // +0x28
	int m_drawState; // +0x2C
};

// ??0FullFadeTransition@@QAE@XZ present-unmatched
FullFadeTransition::FullFadeTransition()
{
	m_startFrame = 0;
	m_endFrame = 30;
	m_posX = 0;
	m_posY = 0;
	m_sizeX = 0;
	m_sizeY = 0;
	m_drawState = -1;
	m_win = 0;
	m_percent = 0.0f;
	m_frameLength = 30;
	m_isForward = true;
}
