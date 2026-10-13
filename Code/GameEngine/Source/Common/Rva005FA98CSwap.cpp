// cl: /O1 /EHa /DNDEBUG /MD /Gy
//
// ?rva005FA98CSwap@@YIXPAVRva005FA98C@@HHHHHH@Z @0x005FA98C 84B: fastcall
// guarded swap (this in ecx, edx unused, then five stack words) with an ebp
// frame: d==e returns; b/c are checked against o->m_04->m_18/m_1C, else
// return; the rowed thiscall 0x005FA8F5 (Rva005FA8F5Find.cpp) finds the
// entries for d/e on the same object, the rowed forward 0x00600062 gets their
// +4 words on m_04+8, then the two +4 words are exchanged. ret 0x14.
//
// Evidence for the callee body: retail keeps `this` in ecx across both finds
// (b and c are compared through edx; no esi/edi copy of this), i.e. the
// compiler knew 0x005FA8F5 leaves ecx alone. MSVC only tracks callee register
// use for out-of-line functions defined earlier in the same TU, so the find
// body (identical to Rva005FA8F5Find.cpp) is defined here ahead of the caller;
// /Gy makes the duplicate a COMDAT.
struct Rva005FA8F5Entry
{
	int m_key;
	int m_04;
};

struct Rva005FA8F5 {
	char m_pad[0x34];
	Rva005FA8F5Entry m_entries[3];
	int m_count;
	Rva005FA8F5Entry *rva005FA8F5(int key);
};

struct Rva00A00062Sub
{
	char m_pad[0x10];
};
struct Rva00600062SwapForward { void forward(int a, int b); };

struct Rva005FA98CM04
{
	char m_pad[8];
	Rva00A00062Sub m_sub08;
	int m_18;
	int m_1C;
};

class Rva005FA98C
{
public:
	char m_pad[4];
	Rva005FA98CM04 *m_04;
};

Rva005FA8F5Entry *Rva005FA8F5::rva005FA8F5(int key)
{
	int i = 0;
	for (; i < m_count; ++i) {
		if (m_entries[i].m_key == key)
			break;
	}
	return m_entries + i;
}
void __fastcall rva005FA98CSwap(Rva005FA98C *o, int fwd, int unused, int b, int c, int d, int e)
{
	if (d == e)
		return;
	Rva005FA98CM04 *m = o->m_04;
	if (b != m->m_18)
		return;
	if (c != m->m_1C)
		return;
	Rva005FA8F5Entry *r1 = ((Rva005FA8F5 *)o)->rva005FA8F5(d);
	Rva005FA8F5Entry *r2 = ((Rva005FA8F5 *)o)->rva005FA8F5(e);
	((Rva00600062SwapForward *)&m->m_sub08)->forward(r1->m_04, r2->m_04);
	int t = r1->m_04;
	r1->m_04 = r2->m_04;
	r2->m_04 = t;
}
