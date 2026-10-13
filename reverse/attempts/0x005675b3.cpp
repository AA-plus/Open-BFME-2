// ?solve@PartitionSolver@@QAEXXZ
// partial score=0.950156 date=2026-10-13
// cl: /O1 /Ireference/shims/bfmealloc /I. /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHs-c- /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP=  /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /EHs
// stlport
// ZH PartitionSolver donor; target identity independently confirmed by WB1432AC0
// (automatic wb_show mapping to1432960 is the constructor and is wrong).
// /EHs-c- followed by /EHs restores all321 instruction bytes; no barrier needed.
#include "PreRTS.h"
#include "Common/PartitionSolver.h"
namespace _STL { template <> int __lg<int>(int); }
bool Rva00566EDDCompareSecondWords(PairObjectIDAndUInt,PairObjectIDAndUInt);
// ?solve@PartitionSolver@@ present-unmatched
void PartitionSolver::solve(void)
{
	m_bestSolution.clear();
	m_currentSolution.clear();
	m_currentSolutionLeftovers = 0x7fffffff;
	
	Int minSizeForAllData = 0;
	Int slotsAllotted = 0;
	Int i, j;

	// first, determine whether there is an actual solution, or we're going to have to fudge it.
	for (i = 0; i < m_data.size(); ++i) {
		minSizeForAllData += m_data[i].second;
	}

	for (i = 0; i < m_spacesForData.size(); ++i) {
		slotsAllotted += m_spacesForData[i].second;
	}

	// we want to attempt to place the largest things first. This allows us to throw
	// out whole classes of solutions

	std::sort(m_data.begin(), m_data.end(), Rva00566EDDCompareSecondWords);
	
	// Also make the largest partition first.
	std::sort(m_spacesForData.begin(), m_spacesForData.end(), Rva00566EDDCompareSecondWords);

	// work in our temporary vector.
	SpacesVec spacesStillAvailable = m_spacesForData;
	
	if (m_howToSolve == PREFER_FAST_SOLUTION) 
	{
		// we prefer the fast, but not necessarily correct solution
		// simply start placing the stuff. Skip things you can't place.
		for (i = 0; i < m_data.size(); ++i) 
		{
			for (j = 0; j < spacesStillAvailable.size(); ++j) 
			{
				if (m_data[i].second <= spacesStillAvailable[j].second) 
				{
					spacesStillAvailable[j].second -= m_data[i].second;
					m_bestSolution.push_back(std::make_pair(m_data[i].first, spacesStillAvailable[j].first));
					break;
				}
			}
		}
	} else {
		DEBUG_CRASH(("PREFER_CORRECT_SOLUTION @todo impl"));
	}
}

