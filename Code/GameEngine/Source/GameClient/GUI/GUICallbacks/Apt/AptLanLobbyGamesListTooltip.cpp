// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva00445BAALanLobbyTooltip@@YAXPAVGameWindow@@PAVWinInstanceData@@I@Z,
// retail 0x00445BAA..0x00445DA5 (507 bytes, cdecl, plain ret). The LAN lobby's
// custom games list tooltip callback: AptLanLobby::InitGadgets (0x00445DA5)
// installs it on the "LanLobby::CustomGamesList" window with winSetTooltipFunc.
// WorldBuilder names it AptLanLobby::GamesListTooltipFunc (AptLanLobby.cpp,
// debug build 0x014144F0); the address name stays the ledger identity.
//
// Source shape from the WorldBuilder debug body (the retail body merges it):
// the three "no game under the cursor" exits are separate blocks, each calling
// the mouse tooltip setter with the empty string and returning (row or column
// -1, then a failed ValidateGameInfo). Cases 0..2 test the column's item data
// into a local first (retail keeps the zero in ESI and compares against it);
// every case ends in the common exit. Merging the three empty-string tails
// into one trailing call, or returning from each case, leaves the
// `mov ecx,esp` / `mov [ebp-0x18],esp` pair of the final by-value copy in the
// wrong order.
//
// Target evidence: nothing happens without the lobby screen (0x00E03354); the
// game comes from column 3's item data; column 0, 1 and 2 give their own
// TOOLTIP: strings only when that column's item data is set (column 2 picks
// MpSaveGame or GameStarted by the game's 16-byte nonzero test 0x003FF1C2);
// other columns list the human players' names, one per line. Donor: Open-BFME-1
// GameNetwork/GameSpy/LanLobbyGamesTooltip.cpp (Rva00518150LanLobbyTooltip,
// BFME1 0x00518150), read as a semantic guide only.
//
// Callees resolve through rows: GadgetListBoxGetEntryBasedOnXY 0x00323F6F,
// GadgetListBoxGetItemData 0x003253BE, LANAPI::ValidateGameInfo 0x00449969,
// Mouse 0x001EEA6D, StringBase ctor/concat 0x00037050/0x00006A2A and the slot
// reads of TheGameText (vslot 15) and GameInfo::getConstSlot.

#include "unicode_string.h"

class WinInstanceData;

class GameWindow
{
};


int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, int x, int y, int &row, int &column);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);

class GameSlot
{
public:
	bool isHuman() const;

	unsigned char m_pad00[0x30];
	UnicodeString m_name; // +0x30
};

class GameInfo
{
public:
	const GameSlot *getConstSlot(int slot) const;
};

class LANGameInfo : public GameInfo
{
};

// GameInfo's 16-byte nonzero test (rowed under its address name).
class Rva003FF1C2
{
public:
	bool rva003FF1C2() const;
};

void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

class LANAPI
{
	friend void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *data, unsigned int mouse);

protected:
	bool ValidateGameInfo(LANGameInfo *game);
};

extern LANAPI *TheLAN;

struct RGBColor;

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

extern Mouse *TheMouse;

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

extern int g_Va00A03354; // Existing storage owner; this body only tests zero.

// Retail 0x00445BAA, 507 bytes: the custom games list tooltip. Donor
// Open-BFME-1 GameNetwork/GameSpy/LanLobbyGamesTooltip.cpp
// (Rva00518150LanLobbyTooltip, BFME1 0x00518150), whose address name it
// keeps. BFME2 target evidence: it does nothing without the lobby screen
// (0x00E03354), reads the game from column 3's item data, and gives columns
// 0..2 their own TOOLTIP: strings (each only when that column's item data is
// set; column 2 picks MpSaveGame or GameStarted by the game's 16-byte
// nonzero test); other columns list the human players' names.
void Rva00445BAALanLobbyTooltip(GameWindow *window, WinInstanceData *, unsigned int mouse)
{
	if (!g_Va00A03354)
		return;

	int x, y, row, column;
	x = mouse & 0xffff;
	y = mouse >> 16;
	GadgetListBoxGetEntryBasedOnXY(window, x, y, row, column);
	if (row == -1 || column == -1)
	{
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		return;
	}
	LANGameInfo *game = (LANGameInfo *)GadgetListBoxGetItemData(window, row, 3);
	if (!TheLAN->ValidateGameInfo(game))
		game = 0;
	if (game == 0)
	{
		TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
		return;
	}
	switch (column)
	{
	case 0:
		{
			void *item = GadgetListBoxGetItemData(window, row, 0);
			if (item != 0)
				TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:UserMapIcon"), -1, 0, 1.0f);
		}
		break;
	case 1:
		{
			void *item = GadgetListBoxGetItemData(window, row, 1);
			if (item != 0)
				TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:AdvSetting"), -1, 0, 1.0f);
		}
		break;
	case 2:
		{
			void *item = GadgetListBoxGetItemData(window, row, 2);
			if (item != 0)
			{
				if (((const Rva003FF1C2 *)game)->rva003FF1C2())
					TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:MpSaveGame"), -1, 0, 1.0f);
				else
					TheMouse->rva001EEA6D(TheGameText->fetch("TOOLTIP:GameStarted"), -1, 0, 1.0f);
			}
		}
		break;
	default:
		{
			UnicodeString tooltip;
			for (int i = 0; i < 8; ++i)
			{
				const GameSlot *slot = game->getConstSlot(i);
				if (slot->isHuman())
				{
					if (tooltip.getLength() != 0)
						tooltip += (const unsigned short *)L"\n";
					tooltip += slot->m_name;
				}
			}
			TheMouse->rva001EEA6D(tooltip, -1, 0, 1.0f);
		}
		break;
	}
}
