// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.95 date=2026-10-13
// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.95 date=2026-10-13
// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.93 date=2026-10-13
// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.93 date=2026-10-13
// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /O1 /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
//
// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z,
// retail 0x005C54BC, 233 bytes. Left reverse: slide the window back toward
// its start position, snapping and finishing on arrival, otherwise moving
// and easing the velocity near the end. X-mirror of the TopFast reverse. BFME2 facts
// (all retail-measured):
// - AnimateWindow accessors are header-inline (direct field traffic, no
//   calls); only getVel is out-of-line (rowed 0x005C5046).
// - winSetPosition is the rowed 0x00313A9E member; timeGetTime rides the
//   winmm import.
// - Slowdown state lives on the process object (maxVel at +0x4, threshold
//   at +0xC, speed-up ratio at +0x14); the min() clamp over -maxVel.y is
//   the comiss/jbe/movaps idiom under /arch:SSE.
// - 2026-10-13 (muse-spark-1.3-contributor): 233B exact-size, 11 diff lines,
//   single xmm0/xmm1 accumulator swap in the slowdown block (retail product
//   in xmm0/spare-zero in xmm1, ours mirrored) plus consequent spill order.
//   Branches/frame/calls all exact. Six shapes tried with NO movement:
//   clamp relation swap (b>a), product temp, ternary clamp, inline
//   Max(bound,value) helper, slowedVel y-before-x assignment. The twin
//   Right (landed, `>` clamp) cannot be copied (different semantics).
//   The allocator choice is stable; needs a new lever.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "PreRTS.h"
#include "GameClient/ProcessAnimateWindow.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromTopFast@@UAE_NPAVAnimateWindow@@@Z
Bool ProcessAnimateWindowSlideFromLeft::reverseAnimateWindow(AnimateWindow *animWin)
{
	if (!animWin)
		return TRUE;
	if (animWin->isFinished())
		return TRUE;

	if (timeGetTime() < animWin->getStartTime())
		return FALSE;

	GameWindow *win = animWin->getGameWindow();
	if (!win)
		return TRUE;

	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if (curPos.x < startPos.x)
	{
		animWin->setFinished(TRUE);
		win->winSetPosition(startPos.x, curPos.y);
		return TRUE;
	}

	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	Real slowedX;
	if (endPos.x - curPos.x <= m_slowDownThreshold)
		slowedX = vel.x * m_speedUpRatio;
	else
		slowedX = -m_maxVel.x;
	if (slowedX < -m_maxVel.x)
		slowedX = -m_maxVel.x;
	Coord2D slowedVel;
	slowedVel.x = slowedX;
	_ReadWriteBarrier();
	slowedVel.y = vel.y;
	animWin->setVel(slowedVel);
	return FALSE;
}
