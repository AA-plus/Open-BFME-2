// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7
// The297B destructor, WB AptCreateAHero callgraph, constructor5142B0
// and both retail vptrs C65D20/C65D1C establish the owner. Exact native
// accesses establish the consumed member layout; the constructor proves
// the trailing flags and full438B storage extent used here.
// Use the constructor-owned s_instance datum (RVA A048D4 / VA E048D4).
// The old separate address-named declaration is removed. Original names
// of saved preview flags and the remaining manager method stay unresolved.
#include "ascii_string.h"

class GameWindow
{
protected:
	virtual ~GameWindow();
private:
	unsigned char m_pad004[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	unsigned char m_pad004[0x58 - 4];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename; // +0x270
	int m_274;
	char m_278;
};

class AptMyHero
{
public:
	virtual ~AptMyHero();
private:
	unsigned char m_opaque[0x18C];
};

class CreateAHeroPage
{
public:
	virtual ~CreateAHeroPage();
};

class GameWindowTransitionsHandler
{
public:
#define V(n) virtual void slot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8)
#undef V
	virtual void slot9();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva002246B1
{
public:
	int RemoveCustomRender(const AsciiString *name);
};
class AptPlayer;
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct DestructorGlobalData
{
	unsigned char m_pad000[0x68];
	bool m_68;
	unsigned char m_pad069[0x9A5 - 0x69];
	bool m_9A5;
	unsigned char m_pad9a6[0x9BD - 0x9A6];
	bool m_9BD;
	unsigned char m_pad9be[0xD45 - 0x9BE];
	bool m_D45;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
#define TheGlobalDataView ((DestructorGlobalData *)TheWritableGlobalData)

class CreateAHeroManager
{
public:
	void rva0021F5F8();
	unsigned char m_pad[0x184];
	bool m_184;
};
extern CreateAHeroManager *TheCreateAHeroManager;
extern unsigned char g_Va00DFD944;

class AptCreateAHero;


class AptCreateAHero : public _bfme_AptGameWindow
{
public:
	virtual ~AptCreateAHero();
private:
	AptMyHero m_myHero; // +0x27C
	int m_mode; // +0x40C
	void *m_page; // +0x410
	void *m_previousPage; // +0x414
	CreateAHeroPage *m_pages[5]; // +0x418
	bool m_42c;
	bool m_42d;
	bool m_42e;
	bool m_takePicture,m_rotateLeft,m_rotateRight,m_zoomIn,m_zoomOut;
	int m_pictureFrames;
	static AptCreateAHero *s_instance;
};

AptCreateAHero::~AptCreateAHero()
{
	TheTransitionHandler->slot9();
	if (s_instance == this)
	{
		for (int i = 0; i < 5; ++i)
		{
			::delete m_pages[i];
			m_pages[i] = 0;
		}
		{
			AsciiString name("CreateAHero::DrawMapComponent");
			((Rva002246B1 *)reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager))->RemoveCustomRender(&name);
		}
		TheGlobalDataView->m_68 = m_42e;
		TheGlobalDataView->m_9A5 = true;
		TheGlobalDataView->m_9BD = m_42c;
		TheGlobalDataView->m_D45 = m_42d;
		g_Va00DFD944 = m_42d;
		TheCreateAHeroManager->rva0021F5F8();
		TheCreateAHeroManager->m_184 = false;
		s_instance = 0;
	}
}
