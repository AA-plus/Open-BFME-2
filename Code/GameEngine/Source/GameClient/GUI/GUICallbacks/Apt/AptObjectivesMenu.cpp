// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// stlport
// GetNthVisibleObjectiveIndex: native 0x004E43F2..0x004E4446, 84 bytes, cdecl.
// WB 0x013266A0 names the helper and AptObjectivesMenu.cpp:415; its two
// nested searches preserve retail's top-tested scan and saved current index.
// The inner loop finds one visible objective; the outer loop skips visible
// objectives until the requested row is reached. Exhaustion returns -1.
// Existing Objective%d callers pin the address-derived ABI name below.
// Target bytes and the existing getter prove the +4 vector of 8-byte records,
// holder +0x10 list, and call to the rowed visibility getter at 0x0042680D.
#include <vector>
#include "ascii_string.h"

struct Rva004266A1Rec
{
	AsciiString text;
	unsigned char flag0;
	unsigned char flag1;
	unsigned char flag2;
};

struct Rva004266A1
{
	char pad[4];
	_STL::vector<Rva004266A1Rec> vec;
	unsigned char rva0042680D(int index);
};

struct Rva0039B95FHolder
{
	char pad[0x10];
	Rva004266A1 *m_list;
};

extern Rva0039B95FHolder *g_00E031E8;

int __cdecl Rva004E43F2(int skip)
{
	Rva0039B95FHolder *tracker = g_00E031E8;
	if (!tracker)
		return -1;
	else
	{
		Rva004266A1 *list = tracker->m_list;
		if (!list)
			return -1;
		else
		{
			int result = -1;
			int count = (int)list->vec.size();
			int i = 0;
			while (true)
			{
				while (true)
				{
					if (i >= count)
						return -1;
					int cur = i++;
					if (list->rva0042680D(cur))
					{
						result = cur;
						break;
					}
				}
				if (skip <= 0)
					break;
				--skip;
			}
			return result;
		}
	}
}
