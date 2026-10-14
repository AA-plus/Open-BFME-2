// cl: /O1 /Ireference/shims/bfmealloc /I. /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHs-c- /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP=  /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /EHs
// stlport
// Adapted from the EA GPLv3 Zero Hour PartitionSolver.cpp donor at BFME1
// cee35b7d8. WB1432AC0 independently identifies solve (the automatic
// WB1432960 mapping is the constructor). Native 005675B3..005676F4.
// The source header supplies the donor's ObjectID pair relationships.
// Retail's vector calls use the already verified eight-byte storage providers:
// copy4334D7, erase3FA4DB, push539A2E. These views preserve two 32-bit fields
// and the three-pointer vector ABI; no original BFME2 template spelling is
// inferred from a byte match. The donor's vectors have trivial element lifetime.
// /EHs retains the native cleanup assumption around extern-C allocation.
#include "PreRTS.h"
#include "Common/PartitionSolver.h"
namespace _STL { template <> int __lg<int>(int); }
struct BfmeE8 { int a, b; };
struct BfmePod8 { int a[2]; };
typedef _STL::vector<BfmeE8, _STL::allocator<BfmeE8> > SolverStorage;
typedef _STL::vector<BfmePod8, _STL::allocator<BfmePod8> > SolverEraseStorage;
bool Rva00566EDDCompareSecondWords(PairObjectIDAndUInt,PairObjectIDAndUInt);
void PartitionSolver::solve(void)
{
	reinterpret_cast<SolverEraseStorage &>(m_bestSolution).clear();
	reinterpret_cast<SolverEraseStorage &>(m_currentSolution).clear();
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
	SolverStorage spacesStillAvailable = reinterpret_cast<const SolverStorage &>(m_spacesForData);
	
	if (m_howToSolve == PREFER_FAST_SOLUTION) 
	{
		// we prefer the fast, but not necessarily correct solution
		// simply start placing the stuff. Skip things you can't place.
		for (i = 0; i < m_data.size(); ++i) 
		{
			for (j = 0; j < spacesStillAvailable.size(); ++j) 
			{
				if (m_data[i].second <= spacesStillAvailable[j].b) 
				{
					spacesStillAvailable[j].b -= m_data[i].second;
					BfmeE8 assignment = { m_data[i].first, spacesStillAvailable[j].a };
					reinterpret_cast<SolverStorage &>(m_bestSolution).push_back(assignment);
					break;
				}
			}
		}
	} else {
		DEBUG_CRASH(("PREFER_CORRECT_SOLUTION @todo impl"));
	}
}

