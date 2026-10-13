// cl: -Oy- -GR- -EHsc-
// NAT::reconnectPlayers @0x005A69C0 140B (WorldBuilder name, its
// __FUNCTION__ string "NAT::reconnectPlayers"; WB calls GameSlot::isHuman
// and PortNegotiationSchema::reconnectPlayers as retail does): two-slot validated swap
// prep. After the predicate and triple ushort-guard (a<8, b<8, a!=b), both
// slots must be present and human (pinned 0x3FF0F1); the +0x28 sub-object
// consumes the full (a, b, c) via the pinned 3-arg callee 0x5DC187, then
// +0x10 stamps 1 while the byte table clears the non-current index. All
// call targets read from retail REL32; true identities unproven.
struct Rva005A69C0Obj
{
	bool IsHuman();
};

struct Rva005A69C0Sub
{
	void Do3(int a, int b, int c);
	bool Q1(int j, int i);
	void *Q2(int j, int i);
	bool rva005DBC2E(int i, int j);
};

struct NAT
{
	char pad0[8];
	Rva005A69C0Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	char pad1[0x28 - 0x18];
	Rva005A69C0Sub m_28;
	char pad2[0x8e4 - 0x29];
	unsigned char m_8E4[8];
	int m_8EC[8];
	int *m_90C[8];

	bool rva005A6709();
	void reconnectPlayers(int a, int b, int c);
	void rva005A6CA5();
	void rva005A6D47();
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern int g_rva005A6CA5Limit;

void NAT::reconnectPlayers(int a, int b, int c)
{
	if (!rva005A6709())
		return;
	if ((unsigned short)a >= 8)
		return;
	if ((unsigned short)b >= 8)
		return;
	if ((unsigned short)a == (unsigned short)b)
		return;
	int an = (unsigned short)a;
	Rva005A69C0Obj *oa = m_8[an];
	if (oa == 0)
		return;
	int bn = (unsigned short)b;
	if (m_8[bn] == 0)
		return;
	if (!oa->IsHuman())
		return;
	if (!m_8[bn]->IsHuman())
		return;
	m_28.Do3(a, b, c);
	if (an == m_14) {
		m_10 = 1;
		m_8E4[bn] = 0;
	} else {
		m_10 = 1;
		m_8E4[an] = 0;
	}
}

// NAT::rva005A6CA5 @0x005A6CA5 162B (unnamed in WB): pair scan over the 8 slots.
// For each present human slot pair (i, j) with i != j, the +0x28 sub-object
// runs its two queries; a surviving response whose +0x10 timestamp is older
// than the limit invokes the sibling reconnectPlayers(i, j, 0). Same class as reconnectPlayers: the
// sibling call passes this untouched, and Check/IsHuman reuse their pins.
void NAT::rva005A6CA5()
{
	NAT *self = this;
	if (!rva005A6709())
		return;
	int stamp = timeGetTime();
	int i = 0;
	do {
		Rva005A69C0Obj *o = m_8[i];
		if (o != 0 && o->IsHuman()) {
			int j = 0;
			do {
				if (i != j) {
					Rva005A69C0Obj *o2 = m_8[j];
					if (o2 != 0 && o2->IsHuman()) {
						Rva005A69C0Sub *q = (Rva005A69C0Sub *)((char *)self + 0x28);
						if (q->Q1(i, j)) {
							void *r = q->Q2(i, j);
							if (r != 0) {
								int t = *(int *)((char *)r + 0x10);
								if (t != 0 && (unsigned)(stamp - t) > (unsigned)g_rva005A6CA5Limit)
									reconnectPlayers(i, j, 0);
							}
						}
					}
				}
				++j;
			} while (j < 8);
		}
		++i;
	} while (i < 8);
}

// NAT::rva005A6D47 @0x005A6D47 101B (unnamed in WB, twin at 0x014E3C60): the
// retry pass over the same slot pairs. For each present human pair (i, j)
// with i != j whose +0x28 schema reports the retries over their limit
// (0x5DBC2E, WB PortNegotiationSchema::isRetryConnectingOverLimit), the pair
// is reconnected with the third argument 1. WB inlines the gate the retail
// body calls (0x5A6709); its loops are the same.
void NAT::rva005A6D47()
{
	if (!rva005A6709())
		return;
	int i = 0;
	do {
		Rva005A69C0Obj *o = m_8[i];
		if (o != 0 && o->IsHuman()) {
			int j = 0;
			do {
				if (i != j) {
					Rva005A69C0Obj *o2 = m_8[j];
					if (o2 != 0 && o2->IsHuman()) {
						if (m_28.rva005DBC2E(i, j))
							reconnectPlayers(i, j, 1);
					}
				}
				++j;
			} while (j < 8);
		}
		++i;
	} while (i < 8);
}

// ICF-folded twin of NAT::rva005A6D47 above (same 101 bytes at 0x005A6D47):
// Rva005A6D47 mirrors the NAT members this scan reads (slot array at +8,
// schema at +0x28), and the two NAT member calls keep their targets through
// layout-compatible casts, so every load, call and loop matches exactly.
class Rva005A6D47
{
public:
	void rva005A6D47();
private:
	char pad0[8];
	Rva005A69C0Obj **m_8;
	int m_C;
	int m_10;
	int m_14;
	char pad1[0x28 - 0x18];
	Rva005A69C0Sub m_28;
};

void Rva005A6D47::rva005A6D47()
{
	if (!((NAT *)this)->rva005A6709())
		return;
	int i = 0;
	do {
		Rva005A69C0Obj *o = m_8[i];
		if (o != 0 && o->IsHuman()) {
			int j = 0;
			do {
				if (i != j) {
					Rva005A69C0Obj *o2 = m_8[j];
					if (o2 != 0 && o2->IsHuman()) {
						if (m_28.rva005DBC2E(i, j))
							((NAT *)this)->reconnectPlayers(i, j, 1);
					}
				}
				++j;
			} while (j < 8);
		}
		++i;
	} while (i < 8);
}
