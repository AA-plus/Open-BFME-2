// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// Two startup initializers of named registrations (the counted-note family
// of Rva0052B894Registration, whose rowed constructor 0x0052B894 registers
// the name and writes the base vptr): each builds the label, constructs the
// global over it, installs the derived vtable and registers the rowed atexit
// thunk that runs the shared destructor 0x005C47A3.
//  - ?rva007B4874@@YAXXZ retail 0x007B4874 (87 bytes): "StrengthenArmy" at
//    0x00E065B8, vtable 0x00C74698, thunk 0x007B96F8.
//  - ?rva007B48CB@@YAXXZ retail 0x007B48CB (87 bytes): "UpgradeTroops" at
//    0x00E065BC, vtable 0x00C7475C, thunk 0x007B9702.
// Two more of the same family, never attempted before (their starts are
// EH-prolog starts that Ghidra did not list): ?rva007B33C5@@YAXXZ retail
// 0x007B33C5 (87 bytes): "SpawnArmy" at 0x00E04500, vtable 0x00C63398, thunk
// 0x007B9035; ?rva007B481D@@YAXXZ retail 0x007B481D (87 bytes):
// "IncreaseCommandPoints" at 0x00E065B4, vtable 0x00C745A0, thunk 0x007B96EE.
// The application classes are unknown; names are address-derived.

#include "ascii_string.h"
extern "C" int __cdecl atexit(void (__cdecl *callback)());

class Rva0052B894Registration
{
public:
	Rva0052B894Registration(const AsciiString &name);
	const void *const *m_vtable;
};

extern unsigned int g_Va00E04500;
extern unsigned int g_Va00E065B4;
extern unsigned int g_Va00E065B8;
extern unsigned int g_Va00E065BC;
extern const void *const g_Va00C63398[];
extern const void *const g_Va00C745A0[];
extern const void *const g_Va00C74698[];
extern const void *const g_Va00C7475C[];
void rva007B9035();
void rva007B96EE();
void rva007B96F8();
void rva007B9702();

void rva007B4874()
{
	{
		AsciiString label("StrengthenArmy");
		Rva0052B894Registration &registration = *(Rva0052B894Registration *)&g_Va00E065B8;
		registration.Rva0052B894Registration::Rva0052B894Registration(label);
		registration.m_vtable = g_Va00C74698;
	}
	atexit(rva007B96F8);
}

void rva007B48CB()
{
	{
		AsciiString label("UpgradeTroops");
		Rva0052B894Registration &registration = *(Rva0052B894Registration *)&g_Va00E065BC;
		registration.Rva0052B894Registration::Rva0052B894Registration(label);
		registration.m_vtable = g_Va00C7475C;
	}
	atexit(rva007B9702);
}

void rva007B33C5()
{
	{
		AsciiString label("SpawnArmy");
		Rva0052B894Registration &registration = *(Rva0052B894Registration *)&g_Va00E04500;
		registration.Rva0052B894Registration::Rva0052B894Registration(label);
		registration.m_vtable = g_Va00C63398;
	}
	atexit(rva007B9035);
}

void rva007B481D()
{
	{
		AsciiString label("IncreaseCommandPoints");
		Rva0052B894Registration &registration = *(Rva0052B894Registration *)&g_Va00E065B4;
		registration.Rva0052B894Registration::Rva0052B894Registration(label);
		registration.m_vtable = g_Va00C745A0;
	}
	atexit(rva007B96EE);
}
