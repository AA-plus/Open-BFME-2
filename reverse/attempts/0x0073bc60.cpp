// ?rva0073BC60@Gen_008F7CD0@@QBEXHHPAUBfmeCellOut@@@Z
// partial score=0.9 date=2026-10-13
// BFME1 BfmeConv1574.cpp adapted to the target constants below.
// Target identity: Ghidra boundary 0x73BD70/131 bytes and the direct calls
// to the target-matched coordinate helpers at 0x739840 and 0x739870.
// Target bytes establish three accepted index values, a 20-bit mask, and
// four 16-bit words of stride between corresponding bits. Target helper
// 0x73A260 supplies the cell pointer; its observed row-major stride is 0xA8.
// Gen_008F7CD0, BfmeCellFD and member names are provisional donor labels;
// the complete target cell layout is not asserted here.

typedef float Real;

struct BfmePointFD
{
	Real x;
	Real y;
};

class BfmeCellFD;

struct BfmeCellOut;

class Gen_008F7CD0
{
public:
	int bfmeCellSum(const BfmePointFD *point, int index,
		unsigned int mask) const;
	void rva0073BC60(int mask, int index, BfmeCellOut *out) const;
	BfmeCellFD *bfmeAt(int x, int y) const;
	int bfmeCellX(Real value) const;
	int bfmeCellY(Real value) const;

private:
	char m_bfmeHead[4];					// +0x00
	Real m_bfmeOriginX;					// +0x04
	Real m_bfmeOriginY;					// +0x08
	char m_bfmeMid[16];					// +0x0C
	Real m_bfmeStep;					// +0x1C
	Real m_bfmeScale;					// +0x20
	int m_bfmeWidth;					// +0x24
	int m_bfmeHeight;					// +0x28
	BfmeCellFD *m_bfmeCells;				// +0x2C
};

struct BfmeCellOut
{
	Real x;
	Real y;
	Real z;
};

// ?bfmeCellSum@Gen_008F7CD0@@QBEHPBUBfmePointFD@@HI@Z
int Gen_008F7CD0::bfmeCellSum(const BfmePointFD *point, int index,
	unsigned int mask) const
{
	if (mask == 0)
		return 0;

	if (index < 0 || index >= 3)
		return 0;

	mask &= 0xfffff;

	BfmeCellFD *cell = bfmeAt(bfmeCellX(point->x), bfmeCellY(point->y));

	if (cell == 0)
		return 0;

	int total = 0;
	if (mask != 0)
	{
		unsigned short *words = (unsigned short *)((char *)cell
			+ index * 2 + 6);

		do
		{
			if ((mask & 1) != 0)
				total += *words;

			mask >>= 1;
			words += 4;
		}
		while (mask != 0);
	}

	return total;
}

// Retail 0x0073BC60, 262 bytes: the cell with the largest index-masked
// bit sum, reported as step-scaled column/row with a zero third lane.
// Same Gen_008F7CD0 grid as bfmeCellSum (20-bit mask, three indices,
// 0xA8 row stride); the +0x1C step scales the winning column and row.
// The empty grid keeps the first cell; ties keep the earlier row.
void Gen_008F7CD0::rva0073BC60(int mask, int index, BfmeCellOut *out) const
{
	if (mask == 0)
		return;
	if (index < 0 || index >= 3)
		return;
	mask &= 0xFFFFF;
	const char *cells = (const char *)m_bfmeCells;
	const char *finish = cells + m_bfmeHeight * m_bfmeWidth * 0xA8;
	const char *cell = cells;
	int best = 0;
	const char *bestCell = cell;
	if (cell != finish)
	{
		do
		{
			int total = 0;
			if (mask != 0)
			{
				unsigned int m = (unsigned int)mask;
				const unsigned short *words = (const unsigned short *)(cell + index * 2 + 6);
				do
				{
					if ((m & 1) != 0)
						total += *words;
					m >>= 1;
					words += 4;
				} while (m != 0);
			}
			if (total > best)
			{
				best = total;
				bestCell = cell;
			}
			cell += 0xA8;
		} while (cell != finish);
	}
	unsigned int row = (unsigned int)((bestCell - cells) / 0xA8);
	out->x = (Real)(row % (unsigned int)m_bfmeWidth) * m_bfmeStep;
	out->y = (Real)(row / (unsigned int)m_bfmeWidth) * m_bfmeStep;
	out->z = 0.0f;
}

