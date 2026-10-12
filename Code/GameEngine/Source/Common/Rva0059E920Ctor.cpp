// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0059E920@@QAE@XZ, retail 0x0059E920..0x0059E991 (113 bytes, EH,
// ret 0): the default constructor of the 0x20-byte object whose destructor
// 0x0059EA42 and deleting destructor 0x0059EAA3 are rowed (vtable
// 0x00C71138, named ??_7Rva0059EA42 in the data ledger; the constructor
// keeps its pinned address name). Built by the INI parse at 0x0059E9C0 (its
// field table 0x00C71178). The layout is the destructor's: an owned
// PlayerPosition at +0x04 (rowed ctor 0x00702805, MapMetaDataCopy.cpp's
// record), the AsciiString vector at +0x08 and the word buffer at +0x14. The
// body allocates the record and clears its loadAIScripts flag.
#include <vector>
#include "ascii_string.h"

struct PlayerPosition
{
	unsigned char human, computer, loadAIScripts;
	int forceTeam;
	unsigned char m_factions[0xC];
	PlayerPosition();										// 0x00702805
	~PlayerPosition();
};

class Rva0059E920
{
public:
	Rva0059E920();
	virtual ~Rva0059E920();

	PlayerPosition *m_record;							// +0x04
	_STL::vector<AsciiString> m_names;					// +0x08
	_STL::vector<int> m_buffer;							// +0x14
};

Rva0059E920::Rva0059E920() : m_record(0)
{
	m_record = new PlayerPosition;
	m_record->loadAIScripts = false;
}
