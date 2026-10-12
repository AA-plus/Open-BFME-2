// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /EHsc /DNDEBUG /MD /arch:SSE /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??0Eva@@QAE@XZ, retail 0x001DF91B..0x001DFA48 (301 bytes, EH, ret 0):
// Eva's constructor (pinned; GameEngine::init creates the subsystem). Bases:
// SubsystemInterface at +0 (rowed ctor; table 0x00BDC5B8) and Snapshot at +0xC
// (0x00BDC5A8). Members are built through the rowed instantiations each call
// names: the int-keyed map at +0x10 (0x001DDBC6), vectors at +0x1C/+0x28/+0x5C
// (folded vector base), int-keyed hash maps at +0x34/+0x48 (0x001DED2B), the
// event queue list at +0x68 (list base 0x002049AD) with its position at +0x6C
// set to the list's end, then 0/1/3/true at +0x70..+0x7C. The body runs the
// rowed +0x80 setup (0x001DCF82), sizes the +0x5C status and +0x28 info
// vectors to the 22 events (rowed 0x001DEE92 / 0x001DF8F8), and registers each
// name of TheEvaMessageNames with its index in the +0x48 name table (rowed
// insert 0x001DE84F). The member views keep the existing address-derived
// spellings of Eva.cpp and the rowed helpers.
#include <map>
#include <list>
#include <hash_map>
#include <vector>
#include "Common/Snapshot.h"
#include "ascii_string.h"

class SubsystemInterface
{
public:
	SubsystemInterface();									// 0x001B4E63
	virtual ~SubsystemInterface();
private:
	unsigned char m_04[8];
};

struct Rva001DDBC6Record
{
	char bytes[4];
};

struct Rva001DED2BElement
{
	char bytes[4];
	bool operator==(const Rva001DED2BElement &) const;
};

struct upgradePair
{
	int a;
	int b;
};

struct NoCaseTreeValue4
{
	int m_index;
	NoCaseTreeValue4(int index) : m_index(index) {}
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct InsertResult
{
	void *m_node;
	void *m_table;
	bool m_inserted;
};

class Rva001DE556
{
public:
	InsertResult *rva001DE84F(InsertResult *out, const NocasePair &obj);	// 0x001DE84F
};

class Rva001DEE92Member
{
public:
	void rva001DEE92(int count);							// 0x001DEE92
};

class Rva001DF88CVector
{
public:
	void resize(unsigned n);								// 0x001DF8F8
};

class Rva001DCF82
{
public:
	void *rva001DCF82();									// 0x001DCF82
};

extern const char *TheEvaMessageNames[];

enum
{
	EVA_MESSAGE_COUNT = 22
};

class Eva : public SubsystemInterface, public Snapshot
{
public:
	Eva();
	virtual ~Eva();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	_STL::map<int, Rva001DDBC6Record> m_10;					// +0x10
	_STL::vector<int> m_1C;									// +0x1C
	_STL::vector<int> m_allEventInfos;						// +0x28
	_STL::hash_map<int, Rva001DED2BElement> m_34;			// +0x34
	_STL::hash_map<int, Rva001DED2BElement> m_names;		// +0x48
	_STL::vector<int> m_eventStatus;						// +0x5C
	_STL::list<upgradePair> m_queue;						// +0x68
	_STL::list<upgradePair>::iterator m_queuePosition;		// +0x6C
	int m_70;												// +0x70
	int m_74;												// +0x74
	int m_78;												// +0x78
	bool m_7C;												// +0x7C
	int m_80;												// +0x80
};

Eva::Eva()
	: m_queuePosition(m_queue.end()), m_70(0), m_74(1), m_78(3), m_7C(true)
{
	((Rva001DCF82 *)&m_80)->rva001DCF82();
	((Rva001DEE92Member *)&m_eventStatus)->rva001DEE92(EVA_MESSAGE_COUNT);
	((Rva001DF88CVector *)&m_allEventInfos)->resize(EVA_MESSAGE_COUNT);
	for (unsigned int i = 0; i < EVA_MESSAGE_COUNT; ++i)
	{
		NocasePair entry((AsciiString(TheEvaMessageNames[i])), NoCaseTreeValue4(i));
		InsertResult result;
		((Rva001DE556 *)&m_names)->rva001DE84F(&result, entry);
	}
}
