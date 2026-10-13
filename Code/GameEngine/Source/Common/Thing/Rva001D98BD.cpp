// cl: /DNDEBUG /MD
// ?rva001D98BD@Rva001D98BD@@QAE_NH@Z @0x001D98BD 79B unlock
// Recursive predicate: +0xB0 type; 5 means internal node over vector at +0x80/+0x84
// of 8B entries whose first dword is child pointer, else compare type to arg.
// Caller 0x0005AF27 passes int through; self-call at 0x001D98E4.
// Neighbour FXBoneInfoAssign shares /O1 flags; no floats or EH.
//
// Also here: the 0x001D9781 sibling, the same internal-node walk (type 5 over
// the child vector) as an "any child qualifies" predicate; its own self-call
// at 0x001D97AC. Its WorldBuilder twin is the debug body wb 0x00ABE250. The
// retail block layout (the return-true block right after the flag test, the
// others sharing it) comes from the explicit if/else with a return in every
// arm, not from early returns followed by a fall-out.
class Rva001D98BD
{
public:
	bool rva001D98BD(int v);
	bool rva001D9781();
private:
	unsigned char m_pad00[0x4C];
	unsigned char m_4C;
	unsigned char m_pad4D[0x80 - 0x4D];
	struct Entry
	{
		Rva001D98BD *child;
		int unk;
	};
	Entry *m_begin;
	Entry *m_end;
	unsigned char m_pad88[0xB0 - 0x88];
	int m_B0;
};

bool Rva001D98BD::rva001D98BD(int v)
{
	int t = m_B0;
	if (t == 5) {
		Entry *end = m_end;
		Entry *beg = m_begin;
		bool ok = false;
		for (Entry *p = beg; p != end; ++p) {
			Rva001D98BD *child = p->child;
			if (child) {
				if (!child->rva001D98BD(v))
					return false;
				ok = true;
			}
		}
		return ok;
	} else {
		return t == v;
	}
}

// 0x001D9781 88B: type 5 is true when the flag byte (+0x4C bit 0) is set or
// any child of the vector qualifies; types 0 and 3 or the flag are true for
// the leaf kinds.
bool Rva001D98BD::rva001D9781()
{
	if (m_B0 == 5) {
		if (m_4C & 1) {
			return true;
		} else {
			Entry *beg = m_begin;
			Entry *end = m_end;
			for (Entry *p = beg; p != end; ++p) {
				Rva001D98BD *child = p->child;
				if (child && child->rva001D9781())
					return true;
			}
			return false;
		}
	} else {
		return m_B0 == 0 || m_B0 == 3 || (m_4C & 1);
	}
}
