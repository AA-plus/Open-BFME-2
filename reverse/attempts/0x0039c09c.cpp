// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ
// partial score=0.7 date=2026-10-09
// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/moduledata /I. /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ @0x0039C09C 88B
// Evidence: LINK BONUS via 0x0039C2B5; rowed _free at 0x00030830 releases the copied buffer. The allocator name is redirected only while including the TU-scoped STLport allocator header, using existing target name Rva00030830FreeAllocation. retail calls rowed vector<unsigned> copy 0x002CFAB9
// plus rowed Rva0055A91A::rva0055A91A 0x0055A91A plus rowed _free 0x00030830 plus __EH_prolog;
// member vector at +0x304 (4B elements reused as Rva0055A91A pointers); neighbours
// 0x0039BFC5/0x0039C0F4 prove /O1 /DNDEBUG /MD /EHsc TU flags; loop over temp copy
// calling Clear on each pointee then freeing temp matches retail pointer-chase shape.

#include <stdlib.h>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <vector>
#undef free

#include "Code/GameEngine/Source/Common/ScoredKillTrackerView.h"
template _STL::vector<unsigned>::vector(const _STL::vector<unsigned>&);
class ScoreKeeper
{
public:
	void unhookAllScoredKillTrackers();
private:
	char m_pad[0x304];
	std::vector<unsigned int> m_vec;
};

// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ present-unmatched
void ScoreKeeper::unhookAllScoredKillTrackers()
{
	const std::vector<unsigned int> tmp(m_vec);
	const unsigned int *begin = tmp.begin();
	
	if (tmp.end() != begin)
	{
		const unsigned int *it = begin;
		do
		{
			((ScoredKillTracker *)*it)->rva0055A91A();
			it++;
		} while (it != tmp.end());
	}
}

// ?unhookAllScoredKillTrackers@ScoreKeeper@@QAEXXZ
// partial score=0.95 date=2026-10-12 seat=w6-mo1
// Alternative via _Vector_base<unsigned> dtor spec routing to Rva00030830GameFree
// (see ScoreKeeperReset.cpp) + do-while with begin/end/p separation (end-var forces
// edi/esi split but adds loads; fresh-load CSE-merges). 84-85/88B. Needs begin/p
// unmerge + early push order. Function body only.
// Retail 0x0039C09C, 88 bytes. Unhooks every tracked kill: copies the
// trackedKills vector (the unhook mutates keeper state, so it iterates a
// copy), invokes ScoredKillTracker::rva0055A91A on each entry, then frees
// the copy's storage. Called from the destructor 0x0039C2B5. Evidence:
// callers 0x0039C2B5; rowed vector<unsigned> copy 0x002CFAB9,
// ScoredKillTracker::rva0055A91A 0x0055A91A and _free 0x00030830;
// trackedKills at +0x304 per the destructor layout.
void ScoreKeeper::unhookAllScoredKillTrackers()
{
	_STL::vector<unsigned> tmp = trackedKills;
	unsigned *begin = tmp.begin();
	unsigned *end = tmp.end();
	unsigned *p = begin;
	if (begin != end)
	{
		do
		{
			((ScoredKillTracker *)*p)->rva0055A91A();
			++p;
		} while (p != tmp.end());
	}
}


// Supporting declarations for the above (from ScoreKeeperReset.cpp):
// void __cdecl Rva00030830GameFree(void *);
// namespace _STL {
// template <> inline _Vector_base<unsigned, allocator<unsigned> >::~_Vector_base()
// { if (_M_start) Rva00030830GameFree(_M_start); }
// }
