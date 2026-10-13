// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// StrategicHUD::StatsDisplayImpl::rva00579D96 @0x00579D96 (class named by
// WorldBuilder's SetRowText 0x00579B17, called on the same this; WB keeps
// these two setters beside it unnamed) 98B slot 5 of 0x0086ED64.
// Float setter with change detection: if arg != m_38, fetch UnicodeString via
// StrategicHUD::FormatResourceMultiplierText 0x00579995, set indexed text via rowed StatsDisplayImpl::SetRowText
// 0x00579B17 with index 4, then store arg to m_38. Callees rowed, vtable slot
// evidence, neighbours Rva00579AB7Dtor and Rva00579E47Delegate share /O1.
// StrategicHUD::StatsDisplayImpl::rva00579D3D @0x00579D3D 89B slot 3 of same vtable.
// Int array setter at +0x2C with same Get/Set pattern via StrategicHUD::FormatBonusText
// 0x00579900 and index+1.
// StrategicHUD::StatsDisplayImpl::rva00579DF8 @0x00579DF8 79B slot 7: the
// power points at +0x3C, shown on row 5 via rowed Rva00579A2FGet 0x00579A2F.
#include "ascii_string.h"
#include "unicode_string.h"

namespace StrategicHUD
{
	UnicodeString FormatResourceMultiplierText(float value);
	UnicodeString FormatBonusText(int value);
	class StatsDisplayImpl;
}
namespace StrategicHUD { UnicodeString __cdecl FormatPowerPointsText(int value); }
namespace StrategicHUD { UnicodeString __cdecl FormatCommandPointsText(int used, int max); }

// The command-points pair at +0x24; retail compares it through the folded
// two-dword equality 0x0007E394 (pinned _rva0007E394CursorEqual).
struct Rva00579CD4CommandPoints
{
	int used;
	int max;
};
extern "C" bool __cdecl rva0007E394CursorEqual(const Rva00579CD4CommandPoints &a, const Rva00579CD4CommandPoints &b);

class StrategicHUD::StatsDisplayImpl
{
public:
	void SetRowText(int index, const UnicodeString &text);	// 0x00579B17
	virtual void rva00579CD4(int used, int max);	// slot 1
	virtual void rva00579D96(float value);	// slot 5
	virtual void rva00579D3D(int index, int value);	// slot 3
	virtual void rva00579DF8(int value);	// slot 7

private:
	int m_level;
	char m_name[4];
	char m_pad0C[0x24 - 0x0C];
	Rva00579CD4CommandPoints m_24;
	int m_2C[2];
	char m_pad34[0x38 - 0x34];
	float m_38;
	int m_3C;
};

void StrategicHUD::StatsDisplayImpl::rva00579D96(float value)
{
	if (value != m_38)
	{
		SetRowText(4, StrategicHUD::FormatResourceMultiplierText(value));
		m_38 = value;
	}
}

void StrategicHUD::StatsDisplayImpl::rva00579D3D(int index, int value)
{
	int *slot = &m_2C[index];
	if (value != *slot)
	{
		SetRowText(index + 1, StrategicHUD::FormatBonusText(value));
		*slot = value;
	}
}

void StrategicHUD::StatsDisplayImpl::rva00579DF8(int value)
{
	if (value != m_3C)
	{
		SetRowText(5, StrategicHUD::FormatPowerPointsText(value));
		m_3C = value;
	}
}

// StrategicHUD::StatsDisplayImpl::rva00579CD4 @0x00579CD4 105B slot 1: the
// command-points pair (used, max) at +0x24, shown on row 0 via
// FormatCommandPointsText 0x00579868. The equal-arm read of max keeps retail's
// register home for the second argument.
void StrategicHUD::StatsDisplayImpl::rva00579CD4(int used, int max)
{
	Rva00579CD4CommandPoints *cur = &m_24;
	if (!rva0007E394CursorEqual(*(Rva00579CD4CommandPoints *)&used, *cur))
	{
		int u = used;
		int m = (max ? max : max);
		SetRowText(0, StrategicHUD::FormatCommandPointsText(u, m));
		cur->max = m;
		cur->used = u;
	}
}
