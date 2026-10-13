// ?solve@PartitionSolver@@QAEXXZ
// partial score=0.8402 date=2026-10-13
// ?solve@PartitionSolver@@QAEXXZ
// partial score=0.93 date=2026-10-13
// ?solve@PartitionSolver@@QAEXXZ
// partial score=0.9
// cl: /Ireference/shims/bfmealloc /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// PartitionSolver::solve, retail 0x005675B3..0x0056770 (321 B) = ZH PartitionSolver::solve.
// State: 316 B vs 321; the 0x4B-byte prologue through both sorts and the vector copy construct
// (0x4334D7) is EXACT, every callee resolves. What made it resolve (reusable):
//  * clear() on both solution vectors calls the ICF-twin row vector<BfmePod8>::erase (0x3FA4DB):
//    view the member as vector<BfmePod8> and give erase a decl-only explicit specialisation;
//  * the spaces copy-ctor is the BfmeE8 row 0x4334D7 and push_back is BfmeE8 0x539A2E: same trick;
//  * sort comparator is the rowed Rva00566EDDCompareSecondWords (0x566EDD), not a static
//    greater_than;
//  * unit flags: /Ireference/shims/bfmealloc FIRST in the /I list and no /D_STLP_USE_MALLOC
//    (retail frees through GameFree 0x30830) and the region /O1 default (EH_prolog helper);
//  * caching spacesStillAvailable.begin() in a local (sb) keeps it in EDI like retail.
// Left: retail keeps the inner-loop size n in EBX with a stack home [ebp-0x18] (frame 0x20, ours
// 0x1C) and hoists m_data[i].second into EDX; ours hoists it into EBX and keeps n in EAX.
// 14 declaration/hoist spellings of n / need / j only move the size between 302 and 317.

// stlport
//
// PartitionSolver::solve (WB PartitionSolver.cpp, ZH reference).
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/PartitionSolver.h"

struct BfmePod8 { int a[2]; };
struct BfmeE8 { int a, b; };
namespace _STL {
template<> BfmePod8 *vector<BfmePod8, allocator<BfmePod8> >::erase(BfmePod8 *, BfmePod8 *);
template<> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &);
template<> vector<BfmeE8, allocator<BfmeE8> >::vector(const vector<BfmeE8, allocator<BfmeE8> > &);
}
bool Rva00566EDDCompareSecondWords(PairObjectIDAndUInt a, PairObjectIDAndUInt b);

void PartitionSolver::solve(void)
{
	((std::vector<BfmePod8> *)&m_bestSolution)->clear();
	((std::vector<BfmePod8> *)&m_currentSolution)->clear();
	m_currentSolutionLeftovers = 0x7fffffff;

	Int minSizeForAllData = 0;
	Int slotsAllotted = 0;
	Int i, j;

	for (i = 0; i < m_data.size(); ++i) {
		minSizeForAllData += m_data[i].second;
	}

	for (i = 0; i < m_spacesForData.size(); ++i) {
		slotsAllotted += m_spacesForData[i].second;
	}

	std::sort(m_data.begin(), m_data.end(), Rva00566EDDCompareSecondWords);
	std::sort(m_spacesForData.begin(), m_spacesForData.end(), Rva00566EDDCompareSecondWords);

	std::vector<BfmeE8> spacesStillAvailable(*(const std::vector<BfmeE8> *)&m_spacesForData);
	BfmeE8 *sb = spacesStillAvailable.begin();

	if (m_howToSolve == PREFER_FAST_SOLUTION)
	{
		unsigned n = spacesStillAvailable.size();
		for (i = 0; i < m_data.size(); ++i)
		{
			for (j = 0; j < (Int)n; ++j)
			{
				if (m_data[i].second <= (unsigned)sb[j].b) {
					sb[j].b -= m_data[i].second;
					BfmeE8 entry;
					entry.a = m_data[i].first;
					entry.b = sb[j].a;
					((std::vector<BfmeE8> *)&m_bestSolution)->push_back(entry);
					break;
				}
			}
		}
	}
}
