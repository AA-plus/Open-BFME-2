// ?rva004467AC@AptLanLobby@@AAE_NXZ
// partial score=0.98 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BFME2's LAN lobby gadget initialization callback, retail 0x00445DA5
// (153 bytes). The screen's constructor 0x00445EE3 binds it as a member
// function pointer on the whole screen object (vftable 0x00C3E0F8; the
// callback interface AptLanLobby.cpp views sits at +0x27C).
//
// Donor: Open-BFME-1 GUICallbacks/Apt/AptLanLobby_onInitGadget.cpp
// (AptLanLobby::_bfme_onInitGadget, BFME1 0x005187F0); the name is
// the donor's identity for the same role and "LanLobby::" gadget names.
// BFME2 target evidence: only CustomGamesList (stored at +0x6A8, games
// tooltip 0x00445BAA) and NameEntry remain; NameEntry's link helper at
// +0x6AC (destroyed by ??1Rva0031455E) attaches through its vslot 1 and
// keeps the window at its +0x08 (+0x6B4), and the screen clears +0x6C0.

#include "unicode_string.h"
#include "ascii_string.h"
#include <list>
#include <map>
#include <string.h>

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class MapMetaData
{
public:
	unsigned char m_pad00[0x28];
	unsigned int m_filesize; // +0x28
	unsigned int m_CRC; // +0x2C
};

// Its 0x00305749 (98 bytes, refreshes the cache) is unrowed and pinned.
class MapCache : public _STL::map<AsciiString, MapMetaData>
{
public:
	void updateCache();
};

extern MapCache *TheMapCache;

class GameSlot
{
public:
	void setPlayerTemplate(int playerTemplate);
	void setMapAvailability(bool available);

	unsigned char m_pad00[0x0C];
	int m_color; // +0x0C
	unsigned char m_pad10[0x40 - 0x10];
	int m_40; // +0x40
};

class Rva00447773
{
public:
	void *rva00447773(int index);
};

extern "C" int __cdecl strcmp(const char *left, const char *right);

class LANGameInfo;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class WinInstanceData;

class GameWindow
{
public:
	int winSetTooltipFunc(void (*tooltip)(GameWindow *window, WinInstanceData *data, unsigned int mouse));
};

class BfmeKeyLC;

void GadgetListBoxReset(GameWindow *window);
void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);
void __cdecl Rva0032060D(GameWindow *window, int value);
void bfmeGo924F(BfmeKeyLC *key, unsigned short value);

// The custom games list tooltip, unrowed 0x00445BAA (507 bytes; BFME1's is
// Rva00518150LanLobbyTooltip), pinned by address.
void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

// The name entry's link helper (BFME1's Gen_00479A60): it keeps the
// attached window at +0x08.
class Rva0031455E
{
public:
	virtual void v0();
	virtual void attach(GameWindow *window);

	void *m_04;
	GameWindow *m_owner; // +0x08
};

class LanguageFilter
{
public:
	void filterLine(UnicodeString &line);
};

extern LanguageFilter *TheLanguageFilter;

UnicodeString GadgetTextEntryGetText(GameWindow *textEntry);

// Retail expands UnicodeString::isEmpty inline as the header test
// (m_data == 0 || m_data->length == 0); the shared shim keeps it out of line.
static inline bool unicodeIsEmpty(const UnicodeString &text)
{
	const unsigned char *data = *(const unsigned char *const *)&text;
	return data == 0 || *(const unsigned short *)(data + 4) == 0;
}

// The LAN preferences at +0x684 (ledger spelling of its setUserName); vslot 3
// writes the file.
class LanLobbyUserNamePrefs
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual bool write();

	void setUserName(UnicodeString name);

	unsigned char m_pad04[0x1C - 0x04];
};

// Other units' views of this same screen object, called by address name.
class Rva00580316
{
public:
	void rva00580316(void *prefs);

	unsigned char m_pad00[0x1C];
};

class Rva004442FD
{
public:
	void rva004442FD();
};

class Rva00444165
{
public:
	int rva00444165();
};

// Enables (rva00444083) or disables (rva004440F4) the create (1) and join
// (2) buttons.
class Rva00444083
{
public:
	void rva00444083(int flags);
	void rva004440F4(int flags);
};

class GameInfo
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();
	virtual void resetStartSpots();
	virtual void adjustSlotsForMap();

	int getNumPlayers() const;
	int getNumOpenOrOccupiedSlots() const;
	GameSlot *getSlot(int index);
	void setMapForwarder(AsciiString mapName);
	void setMapCRC(unsigned int mapCRC);
	void setMapSize(unsigned int mapSize);
	// Unrowed 0x003FF1A7 (27 bytes; stores the game mode at +0x5C and resets
	// the rules for it), pinned by address.
	void rva003FF1A7(int mode);
};

// TheLAN's game list: eight 0x1D0-byte slots from +0xDC end at +0xF5C, where
// the next game is linked.
class LANGameInfo : public GameInfo
{
public:
	unsigned char m_pad004[0x44 - 0x04];
	unsigned int m_mapCRC; // +0x44
	unsigned int m_mapSize; // +0x48
	unsigned char m_pad04c[0x58 - 0x4C];
	int m_58; // +0x58
	int m_5c; // +0x5C (game mode)
	int m_rules[10]; // +0x60
	int m_88; // +0x88
	unsigned char m_pad08c[0xF5C - 0x8C];
	LANGameInfo *m_next; // +0xF5C
};

class ModuleData;

// More views of the +0x668 object (rva00601941 resets it, rva00580B40 adds
// an entry) and of the +0x288 panel (enable).
class Rva00601941
{
public:
	void rva00601941();
};

class Rva00580B40
{
public:
	void rva00580B40(const ModuleData *entry);
};

class Rva0043DB66ByteOneSetter
{
public:
	void enable();
};

// The +0x288 panel (destroyed by ??1Rva004421E1); 0x0043DE19 (265 bytes) is
// unrowed and pinned by address.
class Rva004421E1
{
public:
	void rva0043DE19();
	// Unrowed panel methods, pinned by address: 0x0043FFCF (8 bytes),
	// 0x00440BDF (1693 bytes), 0x0044127C (544 bytes), 0x00443EA8 (358 bytes).
	void rva0043FFCF();
	bool rva00440BDF(bool flag);
	bool rva0044127C();
	void rva00443EA8();
	// And its message handler 0x00442CB3 (690 bytes) and 0x0043FA68 (244
	// bytes), likewise unrowed and pinned.
	int rva00442CB3(int msg, unsigned int data1, unsigned int data2);
	void rva0043FA68(int game);
	// And 0x00442C9C (23 bytes), 0x0043E750 (417 bytes) and 0x00443C6E
	// (570 bytes), likewise unrowed and pinned.
};
class AptMpGameSetup
{
public:
	bool rva00442C9C();
	bool InitGameInfoFromSaveGame(GameInfo *game);
	bool Init(GameInfo *game, int flag);
};

// The screen's base class (destroyed by 0x005126F5); its message handler
// 0x0051274F (136 bytes, vftable 0x00C659E8 slot 2) is unrowed and pinned.
class Rva005126F5
{
public:
	int rva0051274F(int msg, unsigned int data1, unsigned int data2);
};

class Rva00444362
{
public:
	void rva00444362(void *unused);
};

class Rva00580172
{
public:
	bool rva00580172();
};

class GameEngine
{
public:
	void rva004443E7();
};

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

// The two GameLogic fields read by the update (TheGameLogic, 0x00DFE78C).
class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva00446443GameLogic
{
	unsigned char m_pad000[0x40];
	int m_40; // +0x40
	unsigned char m_pad044[0x110 - 0x44];
	int m_110; // +0x110
};

void __cdecl Rva005118F3Show(int mode, bool show);
void __cdecl Rva00434160Init(int a, int b, bool c);
void __cdecl Rva003B3371Call(int value);
void Rva00444040Enable();
void GadgetListBoxGetSelected(GameWindow *listbox, int *selected);

// Unrowed 0x0044C0A8 (message box with title, text and callback), pinned.
void Rva0044C0A8(UnicodeString title, UnicodeString text, void *callback);

// The +0x684 preferences as GameModePreferences; 0x0044D774 (194 bytes),
// 0x0044DB54 (81 bytes) and 0x0044D986 (290 bytes) are unrowed and pinned.
class GameModePreferences
{
public:
	UnicodeString rva0044D330();
	int rva0044D836();
	int rva0044D88C();
	int getStrategicScenario();
	bool rva0044D774(GameSlot *slot);
	bool rva0044DB54(int *rules);
	AsciiString rva0044D986();
};

class EnumeratedIP
{
public:
	void *m_next;
	unsigned int m_ip; // +0x04
};

class IPEnumeration
{
public:
	IPEnumeration();
	~IPEnumeration();
	EnumeratedIP *getAddresses();

private:
	void *m_addresses;
	int m_isWinsockInitialized;
};

// The two GlobalData fields read here (TheWritableGlobalData, 0x00DFE758).
class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva004452A8GlobalData
{
	unsigned char m_pad000[0x26];
	unsigned char m_26; // +0x26
	unsigned char m_pad027[0xA48 - 0x27];
	unsigned int m_defaultIP; // +0xA48
};

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

// Unrowed 0x00437421 (482 bytes, no arguments), pinned by address.
void Rva00437421();

// Window manager vslots 44 and 45 are registerTabList and clearTabList
// (GameWindowManager_registerTabList.cpp; vtable 0x007C7C90). Retail copies
// the window into a temporary before the push_back, so the list is spelled
// here with int elements: its out-of-line bodies are the int list's
// (ICF-identical to the GameWindow * list) and already pinned.
class GameWindowManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void registerTabList(_STL::list<int> tabList);
	virtual void clearTabList();
};

extern GameWindowManager *TheWindowManager;

struct TransportAddress
{
	TransportAddress() : m_ip(0), m_port(0) {}

	unsigned int m_ip;
	unsigned short m_port;
};

class LANAPI
{
public:
	LANAPI();
	virtual void v00();
	virtual void init();
	virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07(); virtual void v08();
	virtual void reset();
	virtual void update();
	virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void RequestLocations();
	virtual void v16(LANGameInfo *game, TransportAddress *address);
	virtual void v17(); virtual void v18(); virtual void v19();
	virtual void RequestHasMap();
	virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26();
	virtual void v27(UnicodeString text, int value);
	virtual void v28();
	virtual void RequestSetName(UnicodeString name);
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
	virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
	virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
	virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50();
	virtual LANGameInfo *v51();
	virtual void v52();
	virtual bool SetLocalIP(unsigned int ip);
	virtual bool AmIHost();
	virtual void v55();
	virtual LANGameInfo *GetMyGame();
	virtual void v57();
	virtual void v58();

	unsigned char m_pad04[0x5D - 0x04];
	unsigned char m_isInLANMenu; // +0x5D
	unsigned char m_pad5e[0x60 - 0x5E];
};

extern LANAPI *g_00DFE958;
#define TheLAN g_00DFE958

class AptLanLobby
{
public:
	void _bfme_onInitGadget(const char *name, void *argument, GameWindow *window);
	void rva00446386(bool enable);
	void submitNameRva00444760();
	void rva00446772();
	void rva0044469C();
	void rva00445E3E(LANGameInfo *games);
	bool initLanRva004452A8();
	int rva00446443();
	int rva00444826(int msg, unsigned int data1, unsigned int data2);

	GameModePreferences &modePrefs() { return *reinterpret_cast<GameModePreferences *>(&m_prefs); }

	// Unrowed 0x004457BC (1006 bytes; rebuilds the games list box), pinned by
	// address.
	void rva004457BC();

private:
	bool rva004467AC();
	unsigned char m_pad000[0x274];
	void *m_owner; // +0x274
	unsigned char m_pad278[0x288 - 0x278];
	Rva004421E1 m_panel; // +0x288
	unsigned char m_pad289[0x304 - 0x289];
	int m_304; // +0x304
	unsigned char m_pad308[0x538 - 0x308];
	int m_538; // +0x538
	unsigned char m_pad53c[0x668 - 0x53C];
	Rva00580316 m_668; // +0x668
	LanLobbyUserNamePrefs m_prefs; // +0x684
	UnicodeString m_userName; // +0x6A0
	int m_6a4; // +0x6A4
	GameWindow *m_customGamesList; // +0x6A8
	Rva0031455E m_nameEntry; // +0x6AC
	unsigned char m_pad6b8[0x6B9 - 0x6B8];
	unsigned char m_6b9; // +0x6B9
	unsigned char m_socketError; // +0x6BA
	bool m_6bb; // +0x6BB
	unsigned char m_pad6bc[0x6C0 - 0x6BC];
	unsigned char m_6c0; // +0x6C0
};

// Retail 0x004467AC, 549 bytes. Donor Open-BFME-1
// BfmeAptScreenLanLobbyRefreshGame.cpp (refreshLanGameRva00519CB0, BFME1
// 0x00519CB0), whose address-name pattern it keeps. BFME2 target evidence:
// the host first lets the +0x288 panel restore the game (0x0043E750) and sets
// the lobby's game mode (+0x304) on it; only when nothing was restored does it
// seed slot 0 and the rules from the preferences (and the strategic scenario
// in mode 1); mode 1 always uses the Mirkwood map; it bumps the game's +0x88
// and the panel applies the game through 0x00443C6E. GameEngineRva004443E7.cpp
// calls this body as GameEngine::rva004467AC (bound below).
bool AptLanLobby::rva004467AC()
{
	if (((AptMpGameSetup *)&m_panel)->rva00442C9C() && TheLAN && TheLAN->GetMyGame())
	{
		TheMapCache->updateCache();
		LANGameInfo *game = TheLAN->GetMyGame();
		if (TheLAN->AmIHost())
		{
			bool restored = ((AptMpGameSetup *)&m_panel)->InitGameInfoFromSaveGame(game);
			game->rva003FF1A7(m_304);
			if (!restored)
			{
				GameSlot *slot = (GameSlot *)reinterpret_cast<Rva00447773 *>(game)->rva00447773(0);
				slot->m_color = modePrefs().rva0044D836();
				slot->setPlayerTemplate(modePrefs().rva0044D88C());
				modePrefs().rva0044D774(slot);
				slot->m_40 = 1;
				if (m_304 == 1)
					game->m_58 = modePrefs().getStrategicScenario();
				int rules[10];
				modePrefs().rva0044DB54(rules);
				memcpy(game->m_rules, rules, sizeof(rules));
			}

			AsciiString mapName;
			if (m_304 == 1)
				mapName = "maps\\map wor mirkwood\\map wor mirkwood.map";
			else
				mapName = modePrefs().rva0044D986();
			game->setMapForwarder(mapName);
			mapName.toLower();
			MapCache::iterator it = TheMapCache->find(mapName);
			if (it != TheMapCache->end())
			{
				game->getSlot(0)->setMapAvailability(true);
				game->setMapCRC((*it).second.m_CRC);
				game->setMapSize((*it).second.m_filesize);
				if (!restored)
					game->adjustSlotsForMap();
			}
			{volatile int *p88=(volatile int *)((char *)game + 0x88);int v=*p88;*p88=v+1;}
		}
		else
		{
			((AptMpGameSetup *)&m_panel)->InitGameInfoFromSaveGame(game);
			game->setMapCRC(game->m_mapCRC);
			game->setMapSize(game->m_mapSize);
			TheLAN->RequestHasMap();
		}
		return ((AptMpGameSetup *)&m_panel)->Init(TheLAN->GetMyGame(), 0);
	}
	return false;
}

