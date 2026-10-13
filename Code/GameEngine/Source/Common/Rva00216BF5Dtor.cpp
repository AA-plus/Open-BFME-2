// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva00216BF5@@UAE@XZ, retail 0x00216BF5..0x00216D2D (312 bytes, EH):
// by its literals AptBannerUI's destructor (a SubsystemInterface; opaque pin
// of its scalar deleting destructor 0x00216DA0, table 0x00BE59E4). With an
// Apt player it removes the over-button handlers of both banner locations'
// available and waiting buttons and background, and drops the
// "AptBannerUI::OnInitialized" and "AptBannerUI::OnBttnBanner" callbacks
// (rowed 0x00224455). Then the +0x28 buffer goes to GameFree (unwind copy
// 0x0007FAB3), the +0xC bucket table dies (rowed 0x00216B80; its wrapper's
// unwind copy is the 5-byte thunk 0x00216BF0) and SubsystemInterface last.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

class AptPlayer
{
public:
	void RemoveOverButtonHandler(const AsciiString &name);
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
// g_pRva00224BC9 is only an alias of the owned g_bfmeAptWindowManager (ledger names column); read it through this unit's view.
#define g_pRva00224BC9 (*(AptPlayer **)&g_bfmeAptWindowManager)

class Rva00224455
{
public:
	int RemoveCommandMap(const AsciiString *name);
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	int m_04;
	int m_08;
};

class Rva00216AF6
{
public:
	~Rva00216AF6();
private:
	unsigned char m_data[0x1C];
};

struct Rva00216BF0
{
	~Rva00216BF0() {}
	Rva00216AF6 m_table;
};

struct Gen_uw_0007fab3
{
	~Gen_uw_0007fab3() { if (m_begin) Rva00030830GameFree(m_begin); }
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class Rva00216BF5 : public SubsystemInterface
{
public:
	virtual ~Rva00216BF5();
private:
	Rva00216BF0 m_handlers;			// +0x0C
	Gen_uw_0007fab3 m_28;			// +0x28
};

Rva00216BF5::~Rva00216BF5()
{
	if (g_pRva00224BC9)
	{
		for (unsigned int i = 0; i < 2; ++i)
		{
			AsciiString path;
			path.format("BannerUI/~Location%d/Banner/AvailableBttn/", i);
			g_pRva00224BC9->RemoveOverButtonHandler(path);
			path.format("BannerUI/~Location%d/Banner/WaitingBttn/", i);
			g_pRva00224BC9->RemoveOverButtonHandler(path);
			path.format("BannerUI/~Location%d/Banner/Background", i);
			g_pRva00224BC9->RemoveOverButtonHandler(path);
		}
		{
			AsciiString name("AptBannerUI::OnInitialized");
			((Rva00224455 *)g_pRva00224BC9)->RemoveCommandMap(&name);
		}
		{
			AsciiString name("AptBannerUI::OnBttnBanner");
			((Rva00224455 *)g_pRva00224BC9)->RemoveCommandMap(&name);
		}
	}
}
