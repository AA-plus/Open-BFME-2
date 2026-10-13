// ?rva0054034A@Rva0054034A@@QAE_NH@Z
// partial score=0.6 date=2026-10-13
// ?rva0054034A@Rva0054034A@@QAE_NH@Z
// partial score=0.6 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Rva0054034A::rva0054034A, retail 0x0054034A (200 B; WB 0x00455B00,
// unnamed): a hinted search of a sorted vector of 40-byte records keyed by
// their first word (+0x10). The cached index (+0x1C) answers directly when
// the key falls in its slot; otherwise the slot is re-found with the rowed
// lower_bound wrapper 0x00540301 and stepped back when the key is past the
// end or between records. Returns whether the key is present. Names are
// structural.
#include <vector>

struct BfmePod40
{
	int m_00;
	char m_pad04[0x24];
};

BfmePod40 *rva00540301(BfmePod40 *first, BfmePod40 *last, const BfmePod40 &value);	// 0x00540301

class Rva0054034A
{
public:
	bool rva0054034A(int key);
private:
	char m_pad00[0x10];
	_STL::vector<BfmePod40> m_records;	// +0x10
	int m_hint;							// +0x1C
};

bool Rva0054034A::rva0054034A(int key)
{
	int hint = m_hint;
	if (hint >= 0 && (unsigned int)hint < m_records.size())
	{
		const BfmePod40 *rec = &m_records[hint];
		int found = rec->m_00;
		if (key >= found && ((unsigned int)(hint + 1) >= m_records.size() || key < rec[1].m_00))
			return found == key;
	}

	if (m_records.empty())
	{
		m_hint = -1;
		return false;
	}

	BfmePod40 *first = m_records.begin();
	int index = rva00540301(first, m_records.end(), (const BfmePod40 &)key) - first;
	m_hint = index;
	if ((unsigned int)index >= m_records.size() || (index > 0 && first[index].m_00 != key))
		m_hint = index - 1;
	return m_records[m_hint].m_00 == key;
}
