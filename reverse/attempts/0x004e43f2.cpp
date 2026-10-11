// ?Rva004E43F2@@YAHH@Z
// partial score=0.93 date=2026-10-11
// cl: /O1 /MD
// stlport
// ?Rva004E43F2@@YAHH@Z (pinned callers' name) @0x004E43F2 84B: the skip-th
// objective of TheMissionObjectiveTracker (g_00E031E8, GameEngineInit's
// "TheMissionObjectiveTracker") that rowed rva0042680D accepts, or -1.
// 2026-10-11 rebank: nested else scopes reproduce retail's three save levels
// (none / EDI / EBX ESI) exactly. Remaining wall (86B vs 84B): retail keeps
// one top-of-loop `cmp ebx,esi / jge` and saves EBP after the count; cl
// rotates the loop (guard plus bottom `jl`) under while, for(;;)+break,
// for+continue and block-scoped forms alike.
#include <vector>
class AsciiString { public: AsciiString(const AsciiString &); AsciiString &operator=(const AsciiString &); __forceinline ~AsciiString() { releaseBuffer(); } protected: void releaseBuffer(); private: void *m_data; };
struct Rva004266A1Rec { AsciiString text; unsigned char flag0; unsigned char flag1; unsigned char flag2; };
struct Rva004266A1 { char pad[4]; _STL::vector<Rva004266A1Rec> vec; unsigned char rva0042680D(int index); };
struct Rva0039B95FHolder { char pad[0x10]; Rva004266A1 *m_list; };
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
			int i = 0;
			int count = (int)list->vec.size();
			while (i < count)
			{
				int cur = i;
				i++;
				if (list->rva0042680D(cur))
				{
					if (skip > 0)
						--skip;
					else
						return cur;
				}
			}
			return -1;
		}
	}
}
