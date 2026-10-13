// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
//
// Two of a four-strong homogeneous family at 0x003BD32B..0x003BD391
// (34B each, dump range 18). Each resolves the 0x00E031E8 global's +0x10
// slot to a Rva004266A1 (the rowed QAEEH family at 0x0042680D proves the
// class) and forwards (index - 1, flag). The two callees differ only in the
// stored byte offset (+5 vs +6 in their bodies, read from retail); the flag
// is the pushed 0/1.
//
// ?rva003BD32B@ScriptActions@@QAEXH@Z @0x003BD32B: callee 0x0042682B, flag 1.
// ?rva003BD36F@ScriptActions@@QAEXH@Z @0x003BD36F: callee 0x00426914, flag 1.
// 0x003BD34D and 0x003BD391 (flag 0) need the global read twice instead of a
// named holder local: with the local the slot10 load goes to ecx (32 B).
class Rva004266A1
{
public:
	void rva0042682B(int index, unsigned char value);
	void rva00426914(int index, unsigned char value);
};

struct Rva004266A1Holder
{
	char m_pad[0x10];
	Rva004266A1 *m_slot10;
};

// g_00E031E8 is only an alias of the owned global g_00E031E8 (ledger names column); this unit reads the owner through its own view type.
extern struct Rva0039B95FHolder *g_00E031E8;
#define g_00E031E8 (*(Rva004266A1Holder * *)&g_00E031E8)

void ScriptActions::rva003BD32B(int index)
{
	Rva004266A1Holder *holder = g_00E031E8;
	if (holder == 0)
		return;
	Rva004266A1 *p = holder->m_slot10;
	if (p == 0)
		return;
	p->rva0042682B(index - 1, 1);
}

void ScriptActions::rva003BD36F(int index)
{
	Rva004266A1Holder *holder = g_00E031E8;
	if (holder == 0)
		return;
	Rva004266A1 *p = holder->m_slot10;
	if (p == 0)
		return;
	p->rva00426914(index - 1, 1);
}

// ?rva003BD34D@ScriptActions@@QAEXH@Z @0x003BD34D: callee 0x0042682B, flag 0. Codegen: the
// global is read again for the slot load (no named holder local), which keeps
// retail's eax shape for the flag-0 spelling (a named holder emits ecx, 32 B).
void ScriptActions::rva003BD34D(int index)
{
	if ((g_00E031E8) == 0)
		return;
	Rva004266A1 *p = (g_00E031E8)->m_slot10;
	if (p == 0)
		return;
	p->rva0042682B(index - 1, 0);
}

// ?rva003BD391@ScriptActions@@QAEXH@Z @0x003BD391: callee 0x00426914, flag 0; same spelling as
// 0x003BD34D.
void ScriptActions::rva003BD391(int index)
{
	if ((g_00E031E8) == 0)
		return;
	Rva004266A1 *p = (g_00E031E8)->m_slot10;
	if (p == 0)
		return;
	p->rva00426914(index - 1, 0);
}
