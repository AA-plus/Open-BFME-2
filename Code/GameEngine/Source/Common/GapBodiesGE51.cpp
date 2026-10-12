// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (fifty-first
// batch; see GapBodiesGE01.cpp), all from the /O1 /arch:SSE /G7 retail region
// that starts at 0x001D8E99 (reverse/retail_inventory/flag_regions.csv). Each
// begins after its neighbour's padding or ret and ends in its own ret or tail
// jump. Retail bytes establish every shape; owning classes are not
// recovered, so each keeps an address-derived name and a view of only the
// members it touches. Callees and globals use the ledger's existing
// spellings.

class AsciiString;
class Image;

// --- 0x001E352C (12B): the +0x20 word of the leading object, or INT_MAX
// without one; 0x001E353C (3B): bump the leading word.
struct GapLimitHolder
{
	char m_pad00[0x20];
	int m_20;
};

class Rva001E352C
{
public:
	int rva001E352C() const;
private:
	GapLimitHolder *m_holder;
};

int Rva001E352C::rva001E352C() const
{
	if (m_holder == 0)
		return 0x7FFFFFFF;
	return m_holder->m_20;
}

class Rva001E353C
{
public:
	void rva001E353C();
private:
	int m_count;
};

void Rva001E353C::rva001E353C()
{
	++m_count;
}

// --- 0x001E381E / 0x001E382F (17B each): floats at +0x538 / +0x53C;
// 0x001E3840 (28B): bit n of the +0x4B8 mask.
class Rva001E381E
{
public:
	void rva001E381E(float value);
	void rva001E382F(float value);
	bool rva001E3840(int bit) const;
private:
	char m_pad00[0x4B8];
	unsigned int m_4B8;
	char m_pad4BC[0x538 - 0x4BC];
	float m_538;
	float m_53C;
};

void Rva001E381E::rva001E381E(float value)
{
	m_538 = value;
}

void Rva001E381E::rva001E382F(float value)
{
	m_53C = value;
}

bool Rva001E381E::rva001E3840(int bit) const
{
	return (m_4B8 & (1 << bit)) != 0;
}

// --- 0x001E417C (24B): lower the +0x40 float to a value.

class Rva001E417C
{
public:
	void rva001E417C(float value);

private:
	char m_pad00[0x40];
	float m_40;
};

void Rva001E417C::rva001E417C(float value)
{
	if (m_40 > value)
		m_40 = value;
}


// --- 0x001EAE2E (8B) / 0x001EAE36 (13B): set / read bit 4 of the +0x438
// byte.
class Rva001EAE2E
{
public:
	void rva001EAE2E();
	int rva001EAE36() const;
private:
	char m_pad00[0x438];
	unsigned char m_438;
};

void Rva001EAE2E::rva001EAE2E()
{
	m_438 |= 0x10;
}

int Rva001EAE2E::rva001EAE36() const
{
	return (m_438 >> 4) & 1;
}

// --- 0x001EAF9B (21B) / 0x001EAFB0 (17B): distance between and advance of
// cursors over 0xAC-byte records.
struct GapRecordAC
{
	char m_bytes[0xAC];
};

struct GapRecordCursor
{
	GapRecordAC *m_at;
};

int rva001EAF9B(const GapRecordCursor &a, const GapRecordCursor &b)
{
	return b.m_at - a.m_at;
}

void rva001EAFB0(GapRecordCursor &cursor, int n)
{
	cursor.m_at += n;
}

// --- 0x001EB0EA (17B): the +0xC1 flag of the optional +0x10 object.
struct GapFlagC1
{
	char m_pad00[0xC1];
	bool m_C1;
};

class Rva001EB0EA
{
public:
	bool rva001EB0EA() const;
private:
	char m_pad00[0x10];
	GapFlagC1 *m_10;
};

bool Rva001EB0EA::rva001EB0EA() const
{
	if (m_10)
		return m_10->m_C1;
	return false;
}

// --- 0x001EB118 (24B): push a block onto g_freeList001EB130; 0x001EB786
// (24B): pop one from g_freelistPool00DB8FEC for a single element.
extern void *g_freeList001EB130;

class FreelistPool
{
public:
	void *pop();
};

extern FreelistPool g_freelistPool00DB8FEC;

class Rva001EB118
{
public:
	void rva001EB118(void *block, unsigned int n);
	void *rva001EB786(unsigned int n, const void *hint);
};

void Rva001EB118::rva001EB118(void *block, unsigned int n)
{
	if (block)
	{
		*(void **)block = g_freeList001EB130;
		g_freeList001EB130 = block;
	}
}

void *Rva001EB118::rva001EB786(unsigned int n, const void *hint)
{
	if (n > 1)
		return 0;
	return g_freelistPool00DB8FEC.pop();
}

// --- 0x001EDFCB (30B): the i-th of the 0x38 names at VA 0x00DB9058, or
// "???" out of range.
extern const char **g_00DB9058;

class Rva001EDFCB
{
public:
	const char *rva001EDFCB(int i) const;
};

const char *Rva001EDFCB::rva001EDFCB(int i) const
{
	const char *name;
	if (i >= 0 && i < 0x38)
		name = ((const char **)&g_00DB9058)[i];
	else
		name = "???";
	return name;
}

// --- 0x001EF05B (20B): two wide strings differ, through the rowed
// StringBase<unsigned short>::compare 0x00006A7A.
template <class T> class StringBase
{
public:
	int compare(const StringBase<T> &that) const;
};

bool rva001EF05B(const StringBase<unsigned short> &a, const StringBase<unsigned short> &b)
{
	return a.compare(b) != 0;
}

// --- 0x001F34BF (28B): advance the +0x178C counter; true while it does not
// cover every bit of the +0x1790 mask.
class Rva001F34BF
{
public:
	bool rva001F34BF();
private:
	char m_pad00[0x178C];
	unsigned int m_counter;									// +0x178C
	unsigned int m_mask;									// +0x1790
};

bool Rva001F34BF::rva001F34BF()
{
	++m_counter;
	return (m_mask & m_counter) != m_mask;
}

// --- 0x001FD1E8 / 0x001FD20E (19B each): look up the +0x16C / +0x178 image
// names through TheMappedImageCollection's rowed findImageByName.
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class Rva001FD1E8
{
public:
	const Image *rva001FD1E8();
	const Image *rva001FD20E();
private:
	char m_pad00[0x16C];
	char m_name16C[0x178 - 0x16C];							// +0x16C (an AsciiString)
	char m_name178[4];										// +0x178 (an AsciiString)
};

const Image *Rva001FD1E8::rva001FD1E8()
{
	return TheMappedImageCollection->findImageByName(*(const AsciiString *)m_name16C);
}

const Image *Rva001FD1E8::rva001FD20E()
{
	return TheMappedImageCollection->findImageByName(*(const AsciiString *)m_name178);
}

// --- 0x001FD348 (31B): the 0x1DC-byte record in [+0x0C, +0x10) whose +0x10
// id matches, or null.
struct GapRecord1DC
{
	char m_pad00[0x10];
	int m_id;												// +0x10
	char m_pad14[0x1DC - 0x14];
};

class Rva001FD348
{
public:
	GapRecord1DC *rva001FD348(int id);
private:
	char m_pad00[0x0C];
	GapRecord1DC *m_begin;									// +0x0C
	GapRecord1DC *m_end;									// +0x10
};

GapRecord1DC *Rva001FD348::rva001FD348(int id)
{
	for (GapRecord1DC *r = m_begin; r != m_end; ++r)
		if (r->m_id == id)
			return r;
	return 0;
}

// --- 0x001FDBEB / 0x001FDBFD (18B each): copy construction through the
// rowed assignments 0x001FD8DF / 0x001FD952.
struct Rva001FD42B
{
	Rva001FD42B(const Rva001FD42B &that);
	Rva001FD42B *rva001FD8DF(const Rva001FD42B &that);	// 0x001FD8DF
};

Rva001FD42B::Rva001FD42B(const Rva001FD42B &that)
{
	rva001FD8DF(that);
}

struct Rva001FD458
{
	Rva001FD458(const Rva001FD458 &that);
	Rva001FD458 *rva001FD952(const Rva001FD458 &that);	// 0x001FD952
};

Rva001FD458::Rva001FD458(const Rva001FD458 &that)
{
	rva001FD952(that);
}
