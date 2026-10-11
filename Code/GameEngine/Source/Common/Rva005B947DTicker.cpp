// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "unicode_string.h"
// ?rva005B947D@AptOnlineHome@@QAEXHHH@Z @0x005B947D 104B
// Ticker formatted row: formats m_64's text plus two ints through rowed
// UnicodeString::format with fmt at VA 0x00C73BD0, then sets it under the
// index through rowed rva005B9378. Evidence: member +0x64 (UnicodeString
// m_64 in AptOnlineHome dtor TU), TheNullChr fallback at VA 0x00BBB5C4,
// callees rowed format/rva005B9378/releaseBuffer, 6 callers in 0x005B95B8.
class Rva005B9378
{
public:
	void rva005B9378(int index, const UnicodeString &value);
};

extern const unsigned short g_00C73BD0[];

class AptOnlineHome
{
public:
	void rva005B947D(int index, int a, int b);
private:
	char m_pad[0x64];
	UnicodeString m_64;	// +0x64
};

void AptOnlineHome::rva005B947D(int index, int a, int b)
{
	UnicodeString tmp;
	tmp.format(g_00C73BD0, a, m_64.str(), b);
	((Rva005B9378 *)this)->rva005B9378(index, tmp);
}

struct FactionStatBlock
{
	int wins[4];
	int losses[4];
};

extern FactionStatBlock g_Va00E06484;
extern FactionStatBlock g_Va00E064A4;
extern FactionStatBlock g_Va00E064C4;
extern FactionStatBlock g_Va00E064E4;
extern FactionStatBlock g_Va00E06504;
extern FactionStatBlock g_Va00E06524;

template<class T> inline const T &onlineHomeMax(const T &a, const T &b)
{
	return a < b ? b : a;
}

float rva005B909F(int *selected, int category)
{
	int t0 = g_Va00E06484.losses[category] + g_Va00E06484.wins[category];
	float r0 = float(g_Va00E06484.wins[category] * 100) / float(onlineHomeMax(t0, 1));

	int t1 = g_Va00E064A4.losses[category] + g_Va00E064A4.wins[category];
	float r1 = float(g_Va00E064A4.wins[category] * 100) / float(onlineHomeMax(t1, 1));

	int t2 = g_Va00E064C4.losses[category] + g_Va00E064C4.wins[category];
	float r2 = float(g_Va00E064C4.wins[category] * 100) / float(onlineHomeMax(t2, 1));

	int t3 = g_Va00E064E4.losses[category] + g_Va00E064E4.wins[category];
	float r3 = float(g_Va00E064E4.wins[category] * 100) / float(onlineHomeMax(t3, 1));

	int t4 = g_Va00E06504.losses[category] + g_Va00E06504.wins[category];
	float r4 = float(g_Va00E06504.wins[category] * 100) / float(onlineHomeMax(t4, 1));

	int t5 = g_Va00E06524.losses[category] + g_Va00E06524.wins[category];
	float r5 = float(g_Va00E06524.wins[category] * 100) / float(onlineHomeMax(t5, 1));

	FactionStatBlock *sel = reinterpret_cast<FactionStatBlock *>(selected);
	int ts = sel->losses[category] + sel->wins[category];
	float rs = float(sel->wins[category] * 100) / float(onlineHomeMax(ts, 1));

	float sum = r5 + r4 + r3 + r2 + r1 + r0;
	return rs / onlineHomeMax(sum, 1.0f) * 100.0f;
}
