// cl: -DNDEBUG -MD -EHsc /Ob1 -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// class-gate: allow UnicodeString donor private view is what emits the retail 78B body at 0x00521AC8; the shared header changes the StringBase ctor calls
// Retail 0x00579690: show a supplied skirmish-screen message only when the
// callback flag is set.  The title is the retail empty wide literal.

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};


class GameWindow;
GameWindow *MessageBoxOk(UnicodeString title, UnicodeString body,
	void (*callback)(void));

class BfmeAptScreenSkirmish
{
public:
	void showError(const UnicodeString &message, int show);
};

// ?showError@BfmeAptScreenSkirmish@@QAEXABVUnicodeString@@H@Z
void BfmeAptScreenSkirmish::showError(const UnicodeString &message, int show)
{
	if(--show == 0)
		MessageBoxOk(UnicodeString((const unsigned short *)L""),
			message, 0);
}

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_CLOSED = 1,
	SLOT_EASY_AI = 2,
	SLOT_MED_AI = 3,
	SLOT_BRUTAL_AI = 4,
	SLOT_AI_5 = 5,
	SLOT_PLAYER = 6
};

struct GameSlotConnectInfo
{
	unsigned int m_nat;
	unsigned short m_port;
};

class GameSlot
{
public:
	void setState(SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo);
};

// ?Rva00521B16@@YG_NPAVGameSlot@@W4SlotState@@ABVUnicodeString@@@Z @0x00521B16 (50B)
bool __stdcall Rva00521B16(GameSlot *slot, SlotState state, const UnicodeString &name)
{
	GameSlotConnectInfo info;
	info.m_nat = 0;
	info.m_port = 0;
	slot->setState(state, name, &info);
	return true;
}
