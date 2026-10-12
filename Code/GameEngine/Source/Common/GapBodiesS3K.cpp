// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Table-reached bodies from .text gaps no ledger row covers (seat-3 batch K;
// see GapBodiesS3A.cpp). Retail bytes establish every shape; owning classes
// are not recovered unless a callee names them, so each keeps an
// address-derived name and a view of only the members it touches.

// --- 0x000CF370 (74B): W3DFloorDraw's slot in its +0x10 interface: whether
// the argument matches (rowed 0x000CF0D6) any 0x4C-byte record of the
// module data's +0x24 vector; on a change of that answer, latch it (+0x07 of
// the interface) and run the rowed W3DFloorDraw 0x000CF2CF.
class Rva000CF0D6
{
public:
	bool test(const Rva000CF0D6 *other) const;				// 0x000CF0D6
	char m_pad[0x4C];
};

struct Rva000CF370Records
{
	Rva000CF0D6 *m_begin;
	Rva000CF0D6 *m_end;
	Rva000CF0D6 *m_capacity;
	Rva000CF0D6 *begin() const { return m_begin; }
	Rva000CF0D6 *end() const { return m_end; }
	bool empty() const { return m_begin == m_end; }
};

struct Rva000CF370Data
{
	char m_pad[0x24];
	Rva000CF370Records m_records;							// +0x24
};

class W3DFloorDrawBase0
{
public:
	virtual void b0();
	Rva000CF370Data *m_data;								// +0x04
	int m_08;
	int m_0C;
};

class W3DFloorDrawIface
{
public:
	virtual void rva000CF370(const Rva000CF0D6 *what, int b, int c);
	char m_04, m_05, m_06;
	bool m_matched;											// +0x07 of the interface
};

class W3DFloorDraw : public W3DFloorDrawBase0, public W3DFloorDrawIface
{
public:
	virtual void rva000CF370(const Rva000CF0D6 *what, int b, int c);
	void rva000CF2CF();										// 0x000CF2CF
};

void W3DFloorDraw::rva000CF370(const Rva000CF0D6 *what, int, int)
{
	if (!m_data->m_records.empty())
	{
		bool matched = false;
		Rva000CF0D6 *end = m_data->m_records.end();
		for (Rva000CF0D6 *it = m_data->m_records.begin(); it != end; ++it)
		{
			if (what->test(it))
			{
				matched = true;
				break;
			}
		}
		if (matched != m_matched)
		{
			m_matched = matched;
			rva000CF2CF();
		}
	}
}
