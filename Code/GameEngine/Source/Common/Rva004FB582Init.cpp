// cl: /O1 /DNDEBUG /MD /EHsc
//
// 0x004FB582 (126B): channel-driven init. One-time init of the channel
// object at 0x00E04508 (its first byte is the done flag), three channel
// queries off the target's +0x14 field into +0x0C/+0x10/+0x14, then a
// by-value slot call on each of the +0x68/+0x74/+0x80 subobjects. All
// seven callees are pinned, not recovered; identities unproven.

class Rva0050366B
{
public:
	void rva0050366B();
};

class Rva00501DF1
{
public:
	int rva00501DF1(int v);
};

class Rva00501813
{
public:
	int rva00501813(int v);
};

class Rva00501844
{
public:
	int rva00501844(int v);
};

struct Rva004FB582Slot
{
	int m_a;	// +0x00
	int m_b;	// +0x04
};

class Rva003FA4DB
{
public:
	void rva003FA4DB(Rva004FB582Slot v);

public:
	Rva004FB582Slot m_slot;	// +0x00
};

class Rva002BF70F
{
public:
	void rva002BF70F(Rva004FB582Slot v);

public:
	Rva004FB582Slot m_slot;	// +0x00
};

class Rva005B129F
{
public:
	void rva005B129F(Rva004FB582Slot v);

public:
	Rva004FB582Slot m_slot;	// +0x00
};

struct Rva00E04508Channel
{
	unsigned char m_initialized;	// +0x00 done flag
};

// The data ledger owns this address in Rva007B6880Thunks.cpp.
extern unsigned int g_Va00E04508;

struct Rva004FB582Target
{
	char m_pad[0x14];
	int val14;	// +0x14 queried field
};

class Rva004FB582Owner
{
public:
	void rva004FB582();

private:
	Rva004FB582Target *m_00;	// +0x00 (queried target)
	char m_pad04[8];		// +0x04..0x0B
	int m_0C;			// +0x0C
	int m_10;			// +0x10
	int m_14;			// +0x14
	char m_pad18[0x50];		// +0x18..0x67
	Rva003FA4DB m_68;		// +0x68
	char m_pad70[4];		// +0x70..0x73
	Rva002BF70F m_74;		// +0x74
	char m_pad7C[4];		// +0x7C..0x7F
	Rva005B129F m_80;		// +0x80
};

void Rva004FB582Owner::rva004FB582()
{
	Rva00E04508Channel *channel = (Rva00E04508Channel *)&g_Va00E04508;
	if (!channel->m_initialized)
	{
		((Rva0050366B *)channel)->rva0050366B();
		channel->m_initialized = 1;
	}
	if (m_00)
	{
		m_0C = ((Rva00501DF1 *)channel)->rva00501DF1(m_00->val14);
		m_10 = ((Rva00501813 *)channel)->rva00501813(m_00->val14);
		m_14 = ((Rva00501844 *)channel)->rva00501844(m_00->val14);
	}
	m_68.rva003FA4DB(m_68.m_slot);
	m_74.rva002BF70F(m_74.m_slot);
	m_80.rva005B129F(m_80.m_slot);
}

// 0x004FB8A8 (124B): re-runs the channel init unconditionally, then for each
// LivingWorld player (TheLivingWorldLogic +0x8C vector, the rowed bounds-
// checked lookup 0x002B52A8) clears the +0x50 word of the player's +0x4C
// subobject (this owner's +0x04) and makes the same three slot calls, +0x80
// first. Identity unproven; address-derived name.
class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva004FB8A8PlayerVector
{
	int size() const { return m_end - m_begin; }
	Rva002E2903Player **m_begin;
	Rva002E2903Player **m_end;
};

struct Rva004FB8A8Players
{
	char m_pad[0x8C];
	Rva004FB8A8PlayerVector m_players;	// +0x8C
};

class Rva004FB8A8Slots
{
public:
	char m_pad00[4];
	int m_04;					// player +0x50
	char m_pad08[0x60];
	Rva003FA4DB m_68;
	char m_pad70[4];
	Rva002BF70F m_74;
	char m_pad7C[4];
	Rva005B129F m_80;
};

void rva004FB8A8()
{
	((Rva0050366B *)&g_Va00E04508)->rva0050366B();
	for (int i = 0; i < ((Rva004FB8A8Players *)TheLivingWorldLogic)->m_players.size(); ++i)
	{
		Rva004FB8A8Slots *slots = (Rva004FB8A8Slots *)((char *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(i) + 0x4C);
		slots->m_04 = 0;
		slots->m_80.rva005B129F(slots->m_80.m_slot);
		slots->m_68.rva003FA4DB(slots->m_68.m_slot);
		slots->m_74.rva002BF70F(slots->m_74.m_slot);
	}
}
