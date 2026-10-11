// cl: /O2 /Ireference/shims/bfme2_ascii /EHsc /MD
// ShroudManager::Data::DoSmallFill, native 0x0073AAE0..0x0073AD8D (685B, RET 0xC).
// Identity: WB 0x17E0670 names the body and its exact warning text; native
// UpdateCellsTouched 0x0073AD90 calls it for small geometry.
// Semantic guide: BFME 1 575ba2b PartitionData_doSmallFill.cpp (COI list
// model, addCoverage link order, WWMath fld/fistp float-to-int idiom); BFME 2
// replaces the circular fill with this rectangular one (target-only facts:
// half-cell radius clamp, floor of the four cell edges, row ranges from the
// grid's rowed 0x0073A2A0 and the 0xA8 cell / 0x10 COI strides).
// The row walk returns its end iterator into the row's first-cell slot, which
// is written back only when the row was non-empty.
#include "ascii_string.h"

class Debug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual Debug &slot20(float value);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4c(int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5c();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug &slot6c(int first, int second, int third);
};

extern Debug *theDebug;

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);
extern "C" __declspec(dllimport) double __cdecl floor(double value);

// WWMath::Float_To_Long idiom.
__forceinline int smallFillInteger(float value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

struct SmallFillCOI;

class BfmeCellFD
{
public:
	SmallFillCOI *first;
	char opaque04[0xA8 - 4];
};

struct SmallFillCOI
{
	BfmeCellFD *cell;
	void *owner;
	SmallFillCOI **previous;
	SmallFillCOI *next;
};

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
	char opaque00[4];
	float originX, originY;
	char opaque0C[0x1C - 0xC];
	float cellSize, scale;
};

class SmallFillNamedObject
{
public:
	virtual AsciiString name();
};

class ShroudManager
{
public:
	class Data
	{
	public:
		bool DoSmallFill(float x, float y, float radius);
		Gen_008F7CD0 *grid;
		SmallFillNamedObject *object;
		char opaque08[0x1C - 8];
		SmallFillCOI *coi;
	};
};

// Link each cell of [first, last) to the next free COI; returns the end iterator.
__forceinline BfmeCellFD *smallFillRow(SmallFillCOI *&out, BfmeCellFD *first, BfmeCellFD *const &last)
{
	while (first != last)
	{
		BfmeCellFD *cell = first;
		SmallFillCOI *current = out++;
		++first;
		current->cell = cell;
		SmallFillCOI *next = cell->first;
		current->next = next;
		if (next)
			next->previous = &current->next;
		current->previous = (SmallFillCOI **)cell;
		cell->first = current;
	}
	return first;
}

__forceinline Debug &smallFillName(Debug &stream, const AsciiString &name)
{
	stream.slot38(name.str());
	return stream;
}

bool ShroudManager::Data::DoSmallFill(float x, float y, float radius)
{
	float cellSize = grid->cellSize;
	if (radius > cellSize * 0.5f)
	{
		bfmeRva000387C0() && (_bfme_debugRecordCallsite(1), theDebug->slot60(),
			(smallFillName(theDebug->slot6c(0, 0, 0).slot38("Object "),
				object ? object->name() : AsciiString("*unknown*"))
				.slot38(" is too large for 'small' geometry.\nRadius given is ").slot20(radius).slot38(" but maximum radius for small geometry is ")
				.slot20(grid->cellSize * 0.5f).slot38("; truncating.\n\nIn order to fix this problem either set the geometry of the given object\nto non-small or reduce the geometry major radius.\n")).slot4c(2), true);
		radius = grid->cellSize * 0.5f;
	}
	SmallFillCOI *out = coi;
	int firstX = smallFillInteger((float)floor((double)((x - radius - grid->originX) * grid->scale)));
	int lastX = smallFillInteger((float)floor((double)((x + radius - grid->originX) * grid->scale)));
	int firstY = smallFillInteger((float)floor((double)((y - radius - grid->originY) * grid->scale)));
	int lastY = smallFillInteger((float)floor((double)((y + radius - grid->originY) * grid->scale)));
	while (firstY <= lastY)
	{
		BfmeCellFD *first, *last;
		grid->rva0073A2A0(&first, &last, firstX, lastX, firstY);
		++firstY;
		if (first != last)
			first = smallFillRow(out, first, last);
	}
	return true;
}
