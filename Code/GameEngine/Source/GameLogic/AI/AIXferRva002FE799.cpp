// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?rva002FE799@AI@@UAEXPAVXfer@@@Z, retail 0x002FE799..0x002FE87D (228B, EH):
// a Ghidra-unlisted slot of the AI snapshot table 0x00C073C0. BFME 2 folds
// Zero Hour's AI::crc and AI::xfer into one body: a CRC pass snapshots the
// pathfinder, every TAiData and every AIGroup behind retail's own
// "MARKER:TAiData" / "MARKER:AIGroup" literals (Zero Hour AI.cpp order);
// otherwise it writes version 1, the +0x10 word and four raw bytes at +0x14.
// Xfer slots follow the ledger's LivingWorld snapshot view (3 IsCRC,
// 9 user bytes, 12 xferSnapshot, 27 xferAsciiString, 30 the +0x10 word).
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include <list>

class Xfer
{
public:
	virtual void s0();
	virtual bool IsLoading() const;
	virtual void s2();
	virtual bool IsCRC() const;
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8();
	virtual void xferUser(void *data, int size);
	virtual void s10(); virtual void s11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
	virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26();
	virtual void xferAsciiString(AsciiString *s);
	virtual void s28(); virtual void s29();
	virtual void xfer30(int *value);
	void Version1();										// 0x000053EE
};

class PathfinderBase
{
public:
	virtual void b0();
};

class Pathfinder : public PathfinderBase, public Snapshot
{
};

class TAiData : public Snapshot
{
public:
	char m_pad004[0x100 - 4];
	TAiData *m_next;										// +0x100
};

class AIGroup : public Snapshot
{
};

class AI
{
public:
	virtual void rva002FE799(Xfer *xfer);
private:
	Pathfinder *m_pathfinder;								// +0x04
	_STL::list<AIGroup *> m_groupList;						// +0x08
	TAiData *m_aiData;										// +0x0C
	int m_10;												// +0x10
	int m_14;												// +0x14
};

void AI::rva002FE799(Xfer *xfer)
{
	if (xfer->IsCRC())
	{
		xfer->xferSnapshot(m_pathfinder);

		AsciiString marker;
		TAiData *aiData = m_aiData;
		while (aiData)
		{
			marker = "MARKER:TAiData";
			xfer->xferAsciiString(&marker);
			xfer->xferSnapshot(aiData);
			aiData = aiData->m_next;
		}

		// Compare the public node identities directly, preserving the inlined walk
		// without emitting this TU's non-retail iterator-comparison COMDAT.
		for (_STL::list<AIGroup *>::iterator groupIt = m_groupList.begin(); groupIt._M_node != m_groupList.end()._M_node; ++groupIt)
		{
			if (*groupIt)
			{
				marker = "MARKER:AIGroup";
				xfer->xferAsciiString(&marker);
				xfer->xferSnapshot(*groupIt);
			}
		}
	}
	else
	{
		xfer->Version1();
		xfer->xfer30(&m_10);
		xfer->xferUser(&m_14, 4);
	}
}
