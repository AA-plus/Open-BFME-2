// ?rva0035A8D7@Rva0035A8D7@@QAEXHHH@Z
// partial score=0.97 date=2026-10-12
// ?rva0035A8D7@Rva0035A8D7@@QAEXHHH@Z
// partial score=0.97 date=2026-10-04
// ?rva0035A8D7@Rva0035A8D7@@QAEXHHH@Z
// partial score=0.9 date=2026-10-01
// ?rva0035A8D7@Rva0035A8D7@@QAEXHHH@Z
// partial score=0.90 date=2026-10-01
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?rva0035A8D7@Rva0035A8D7@@QAEXHHH@Z retail 0x0035A8D7 167B
// Honest grid method: bounds-check x vs +0x34 and y vs +0x38, index the
// 16-byte cell array at +0x40, then dispatch on the cell state at +0x0c.
// State 3 checks the first Pod8's second field, state 2 marks the matching
// Pod8 deleted (breaks after first match) and erases when prefix is clean.
// Evidence: leaf lane, EBP frame with xor-first compares plus or -1, caller
// at 0x0035A98C, callee row vector<BfmePod8> erase 0x003FA4DB.
#include <vector>

struct BfmePod8
{
	int a[2];
};

struct RvaCell
{
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > vec;
	int state;
};

class Rva0035A8D7
{
public:
	void rva0035A8D7(int x, int y, int val);

private:
	char _pad0[0x34];
	int m_width;
	int m_height;
	int _pad1;
	RvaCell *m_cells;
};

// ?rva0035A8D7@Rva0035A8D7@@QAEXHHH@Z present-unmatched
void Rva0035A8D7::rva0035A8D7(int x, int y, int val)
{
	RvaCell *base = m_cells;
	if (base == 0)
		return;
	if (x < 0)
		return;
	if (x >= m_width)
		return;
	if (y < 0)
		return;
	if (y >= m_height)
		return;
	RvaCell *c = &base[y * m_width + x];
	switch (c->state) {
	case 0:
		return;
	case 1:
		return;
	case 2: {
		bool b = true;
		if (!c->vec.empty()) {
			for (BfmePod8 *p = c->vec.begin(); p != c->vec.end(); ++p) {
				if (p->a[1] != val) {
					if (p->a[0] != -1)
						b = false;
				} else {
					p->a[0] = -1;
					p->a[1] = 0;
					break;
				}
			}
			if (!b)
				return;
		}
		c->state = 0;
		c->vec.erase(c->vec.begin(), c->vec.end());
		break;
	}
	case 3: {
		if (c->vec.size() >= 1) {
			if (c->vec[0].a[1] != val)
				return;
		}
		c->state = 0;
		break;
	}
	}
}
