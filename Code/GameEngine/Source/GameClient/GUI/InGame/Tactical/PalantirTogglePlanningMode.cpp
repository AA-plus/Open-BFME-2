// cl: /O1 /DNDEBUG /MD
// ?TogglePlanningMode@Impl@Palantir@@QAEXXZ @0x002D2F32 109B
// Renamed from placeholder Rva002D2F32Owner::rva002D2F32. Identity: the
// WorldBuilder build's twin asserts assert lines 1425-1426 in EA's own
// C:\Projects\bfme2\Code\GameEngine\Source\GameClient\Gui\InGame\Tactical\Palantir.cpp
// and names Palantir::Impl::TogglePlanningMode; globals and semantics match
// the retail body (TheGameLogic mode 3, own +0x128 gate, local player's
// +0x758 == 2, GameMessage 0x469 through MessageStream slot 0x48).
// Body provenance: placeholder Rva002D2F32Post.cpp (matched, "exact
// identities unproven" views carried over unchanged). The +0x128 owner
// field view claims nothing about Impl's real members.
class GameLogic
{
public:
	char m_pad[0x110];
	int m_110;
};
extern GameLogic *TheGameLogic;

struct Rva002D2F32Mid
{
	char m_pad[0x750];
	int m_750;
};

class PlayerList
{
public:
	char m_pad[0x10];
	Rva002D2F32Mid *m_mid;
};
extern PlayerList *ThePlayerList;

class GameMessage
{
public:
	enum Type
	{
		MSG_RVA469 = 0x469
	};

	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(GameMessage::Type type);
};
extern class MessageStream *TheMessageStream;

class Palantir
{
public:
	class Impl
	{
	public:
		void TogglePlanningMode();

	private:
		char m_pad[0x128];
		unsigned char m_128;
	};
};

void Palantir::Impl::TogglePlanningMode()
{
	if (TheGameLogic->m_110 == 3)
		return;
	if (m_128 == 0)
		return;
	Rva002D2F32Mid *mid = ThePlayerList->m_mid;
	if (mid != 0 && mid->m_750 == 2) {
		GameMessage *m = TheMessageStream->appendMessage(GameMessage::MSG_RVA469);
		m->appendIntegerArgument(0);
		m->appendIntegerArgument(2);
		return;
	}
	GameMessage *m2 = TheMessageStream->appendMessage(GameMessage::MSG_RVA469);
	m2->appendIntegerArgument(2);
}
