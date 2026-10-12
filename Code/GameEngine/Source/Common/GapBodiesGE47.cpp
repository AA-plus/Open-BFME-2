// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (forty-seventh
// batch; see GapBodiesGE01.cpp), all from /O2 /arch:SSE /G7 retail regions
// between 0x001541E0 and 0x0019FFFF (reverse/retail_inventory/
// flag_regions.csv). Each begins after its neighbour's padding or ret and
// ends in its own ret. Retail bytes establish every shape; owning classes are
// not recovered, so each keeps an address-derived name and a view of only
// the members it touches.

// --- 0x0015F560 (48B): four floats, returning this; 0x0015F590 (46B): set
// them.
class Rva0015F560
{
public:
	Rva0015F560(float a, float b, float c, float d);
	void rva0015F590(float a, float b, float c, float d);
private:
	float m_a;
	float m_b;
	float m_c;
	float m_d;
};

Rva0015F560::Rva0015F560(float a, float b, float c, float d) : m_a(a), m_b(b), m_c(c), m_d(d)
{
}

void Rva0015F560::rva0015F590(float a, float b, float c, float d)
{
	m_a = a;
	m_b = b;
	m_c = c;
	m_d = d;
}

// --- 0x0015F920 (57B): an identity rotation (when asked) and a zero
// translation; 0x0015F9A0 (56B): a four-word rotation and a three-word
// translation copied in.
struct GapQuat
{
	float x;
	float y;
	float z;
	float w;
};

struct GapVec3
{
	float x;
	float y;
	float z;
};

class Rva0015F920
{
public:
	Rva0015F920(bool identity);
	Rva0015F920(const GapQuat &q, const GapVec3 &t);
private:
	GapQuat m_q;
	GapVec3 m_t;
};

Rva0015F920::Rva0015F920(bool identity)
{
	if (identity)
	{
		m_q.x = 0.0f;
		m_q.y = 0.0f;
		m_q.z = 0.0f;
		m_q.w = 1.0f;
	}
	m_t.x = 0.0f;
	m_t.y = 0.0f;
	m_t.z = 0.0f;
}

Rva0015F920::Rva0015F920(const GapQuat &q, const GapVec3 &t)
{
	m_q = q;
	m_t.x = t.x;
	m_t.y = t.y;
	m_t.z = t.z;
}

// --- 0x00167E04 (24B): copy a three-word value into +0x0C.
struct GapWords3
{
	int a;
	int b;
	int c;
};

class Rva00167E04
{
public:
	void rva00167E04(const GapWords3 &value);
private:
	char m_pad00[0x0C];
	int m_0C;
	int m_10;
	int m_14;
};

void Rva00167E04::rva00167E04(const GapWords3 &value)
{
	m_0C = value.a;
	m_10 = value.b;
	m_14 = value.c;
}

// --- 0x0016EB50 (29B): the +0xA8 item i with a reference added.
struct GapRefItem
{
	int m_00;
	int m_refs;												// +0x04
};

class Rva0016EB50
{
public:
	GapRefItem *rva0016EB50(int i);
private:
	char m_pad00[0xA8];
	GapRefItem *m_items[4];									// +0xA8
};

GapRefItem *Rva0016EB50::rva0016EB50(int i)
{
	GapRefItem *item = m_items[i];
	if (item)
		item->m_refs += 1;
	return m_items[i];
}

// --- 0x00189400 (33B): slot 2 (+8) of the object embedded at +0x23C, then
// the +0x240 word.
class GapSlot2View
{
public:
	virtual void v00();
	virtual void v01();
	virtual void slot2(int value);
};

class Rva00189400
{
public:
	int rva00189400(int value);
private:
	char m_pad00[0x23C];
	GapSlot2View m_23C;
	int m_240;
};

int Rva00189400::rva00189400(int value)
{
	GapSlot2View *target = &m_23C;
	target->slot2(value);
	return m_240;
}

// --- 0x0019AF00 (20B): three zero floats, returning this.
class Rva0019AF00
{
public:
	Rva0019AF00();
private:
	float m_x;
	float m_y;
	float m_z;
};

Rva0019AF00::Rva0019AF00()
{
	m_z = 0.0f;
	m_y = 0.0f;
	m_x = 0.0f;
}
