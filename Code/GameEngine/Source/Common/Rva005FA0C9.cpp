// cl: /O1 /G6 /DNDEBUG /MD
// ?rva005FA0C9Init@@YIPAVRva005FA0C9@@PAV1@HPAURva005FA0C9A@@HH@Z @0x005FA0C9
// 46B evidence: fastcall wrapper (this, unused edx, a, b, c).
// The callee 0x005F9DCB is the thiscall PlayerPageFrame constructor:
// ECX supplies this, five stack arguments, RET 0x14, no EDX input.
// Pass (a->m_04, &a->m_08, "Ally", b, c); installs vtable
// 0x00C79D78 by literal store (fixed-base game.dat, no reloc needed);
// returns this; ret 0xC. Same shape as 0x005FA0F7 (vtable const differs).
// TU-local view only.
class AsciiString;
struct Rva005F91F3Src;
struct Rva005FA0C9A
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva005FA0C9
{
public:
	char m_pad[4];
};

namespace StrategicHUD {
class PlayerPageFrame
{
public:
	PlayerPageFrame(int level, const AsciiString &name, const char *side,
		int index, const Rva005F91F3Src &record);
};
}


Rva005FA0C9 *__fastcall rva005FA0C9Init(Rva005FA0C9 *o, int fwd, Rva005FA0C9A *a, int b, int c)
{
	((StrategicHUD::PlayerPageFrame *)o)->StrategicHUD::PlayerPageFrame::PlayerPageFrame(a->m_04, *(const AsciiString *)&a->m_08,
		"Ally", b, *(const Rva005F91F3Src *)c);
	((int *)o)[0] = 0x00C79D78;
	return o;
}
