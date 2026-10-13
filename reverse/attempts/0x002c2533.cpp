// ?winCreate@GameWindowManager@@QAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
// partial score=0.94 date=2026-10-13
// ?winCreate@GameWindowManager@@QAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
// partial score=0.94 date=2026-10-13
// ?winCreate@GameWindowManager@@QAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
// partial score=0.8 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /DNDEBUG /MD
//
// ?winCreate@GameWindowManager@@QAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z,
// retail 0x002C2533, 263 bytes. GameWindowManager record-based window create.
//
// BFME1 donor (game/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp,
// winCreate): allocate via the record's allocator (or the manager fallback
// with a dump-list diagnostic), parent into the caller list, copy instance
// data, order pairs, send create, then resolve the font from the global
// language (falling back to 14pt Times New Roman). BFME2 facts
// (all retail-measured):
// - The record is Rva0047EDE0CreateInfo (parent@0, allocator@0x18, instance
//   at +0x30); the manager/table views follow the adapted donor.
// - Manager slots: +0x38 unanswered-getter, +0x3C record allocator fallback,
//   +0xE0 addWindowToParent, +0xE8 winSendSystemMsg (slot 58), +0x130
//   winFindFont(name, size, bold) with the name passed by value (the same
//   temp-in-arg-slot idiom as setWindowText's TU).
// - Window slot +0x28 is a boolean gate; Rva00477DF0::orderPairs reaches the
//   rowed body through the TU-local view (its TU aliases GameWindow spelling).
// - GameWindow::winSetFont is invoked qualified (direct call, no vtable).
// - The language name emptiness uses the out-of-line StringBase::isEmpty
//   worker at 0x401E2F (the shared shim inlines it).
// - Callees rowed or pinned: dumpWindow 0x002C1148, linkWindow 0x002C0A89,
//   winSetInstanceData 0x0031495C, orderPairs 0x0031394A, winSetFont
//   0x00313D73, StringBase ctors 0x000365F0/0x000437BA0, release-free
//   StringBase::isEmpty 0x000401E2F.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;


#ifndef NULL
#define NULL 0
#endif

#ifndef FALSE
#define FALSE false
#endif

class AsciiString;
class UnicodeString;
class GameFont;
class GameWindow;
class WinInstanceData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"

struct Rva0047EDE0CreateInfo
{
	GameWindow *m_parent;
	UnsignedInt m_field04;
	Int m_field08, m_field0C, m_field10, m_field14;
	GameWindow *(__stdcall *m_allocator)(Rva0047EDE0CreateInfo *);
	void *m_field1C;
	Int m_field20, m_field24, m_field28, m_field2C;
	WinInstanceData *m_field30;
};

struct Rva00477DF0
{
	void orderPairs();
};

struct Rva0047EDE0FontDesc
{
	AsciiString name;
	Int size;
	bool bold;
};

struct Rva0047EDE0GlobalLanguage
{
	unsigned char m_pad00[0xA4];
	Rva0047EDE0FontDesc m_defaultWindowFont;
};

class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;



class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual int slot14();
	virtual GameWindow *slot15(Rva0047EDE0CreateInfo *info);
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void addWindowToParent(GameWindow *window, GameWindow *parent);
	virtual void slot57();
	virtual int winSendSystemMsg(GameWindow *window, UnsignedInt msg, int mData1, int mData2);
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual GameFont *winFindFont(AsciiString name, Int size, bool bold);
	GameWindow *winCreate(Rva0047EDE0CreateInfo *info);
private:
	unsigned char m_pad04[0x0C - 0x04];
	GameWindow *m_windowList;
protected:
	void dumpWindow(GameWindow *window);
public:
	void linkWindow(GameWindow *win);
};

class GameWindow
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Bool windowSlot10();
	virtual void winSetFont(GameFont *font);
	Int winSetInstanceData(WinInstanceData *data);
	int m_field04;
	unsigned char m_pad08[0x1F8 - 0x08];
	GameWindow *m_next;
};

// ?winCreate@GameWindowManager@@QAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
GameWindow *GameWindowManager::winCreate(Rva0047EDE0CreateInfo *info)
{
	GameWindow *window;
	_ReadWriteBarrier();

	if (info->m_allocator)
	{
		window = info->m_allocator(info);
		if (window->m_field04 == 0 && window->windowSlot10())
			window->m_field04 = slot14();
	}
	else
	{
		window = slot15(info);
		if (window == NULL)
		{
			GameWindow *win;
			for (win = m_windowList; win; win = win->m_next)
				dumpWindow(win);
			return NULL;
		}
	}

	if (info->m_parent)
		addWindowToParent(window, info->m_parent);
	else
		linkWindow(window);

	if (info->m_field30)
		window->winSetInstanceData(info->m_field30);

	((Rva00477DF0 *)window)->orderPairs();

	winSendSystemMsg(window, 1, 0, 0);

	Rva0047EDE0GlobalLanguage *language = (Rva0047EDE0GlobalLanguage *)TheGlobalLanguageData;
	if (language && !((const StringBase<char> *)&language->m_defaultWindowFont.name)->isEmpty())
		window->GameWindow::winSetFont(winFindFont(AsciiString(language->m_defaultWindowFont.name),
			language->m_defaultWindowFont.size, language->m_defaultWindowFont.bold));
	else
		window->GameWindow::winSetFont(winFindFont(AsciiString("Times New Roman"), 14, FALSE));

	return window;
}
