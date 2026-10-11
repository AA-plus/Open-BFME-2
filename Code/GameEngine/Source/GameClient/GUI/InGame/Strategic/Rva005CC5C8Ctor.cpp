// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??0Rva005CC5C8@@QAE@HHABVAsciiString@@PAHPBURva005CC5C8Context@@@Z, retail
// 0x005CC543 (133 bytes, RET 0x14): the constructor of the strategic HUD
// region-details panel whose destructor is rowed as Rva005CC5C8 (vtable
// 0x00C74EAC; sole caller 0x005CC698). Over the rowed
// StrategicHUD::RegionDetailsMovieClip(level, name, region) base it keeps
// its owner word (+8), the region pointer (+0x0C) and a copy of the
// context's 16-byte record (+0x10..+0x1C, the region record first); a
// region the local living-world player (rowed 0x002B2B66) does not own
// (record +0x13C) switches the panel to mode 2 (rowed 0x005E3049). The
// vtable store is an explicit member with a TU-local stand-in; this unit
// emits no vtable.
#include "ascii_string.h"

namespace StrategicHUD
{
class RegionDetailsMovieClip
{
public:
	RegionDetailsMovieClip(int level, const AsciiString &name, int region);
	~RegionDetailsMovieClip();
protected:
	const void *m_vtable;		// +0x00
	unsigned char m_pad04[4];
	int m_owner;			// +0x08
};
}

struct Rva005CC5C8Region
{
	unsigned char m_pad000[0x13C];
	int m_ownerPlayer;		// +0x13C
};

struct Rva005CC5C8Record
{
	Rva005CC5C8Region *m_region;
	int m_04;
	int m_08;
	int m_0C;
};

struct Rva005CC5C8Context
{
	int m_00;
	Rva005CC5C8Record m_record;	// +0x04
};

class Rva002B2B66 { public: int rva002B2B66(); };
class Rva005E3049 { public: void rva005E3049(int mode, int flag); };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

static int s_vtable;

class Rva005CC5C8 : public StrategicHUD::RegionDetailsMovieClip
{
public:
	Rva005CC5C8(int owner, int level, const AsciiString &name, int *region, const Rva005CC5C8Context *context);
private:
	int *m_region;			// +0x0C
	Rva005CC5C8Record m_record;	// +0x10
};

Rva005CC5C8::Rva005CC5C8(int owner, int level, const AsciiString &name, int *region, const Rva005CC5C8Context *context)
	: StrategicHUD::RegionDetailsMovieClip(level, name, *region)
{
	m_owner = owner;
	m_vtable = &s_vtable;
	m_region = region;
	m_record.m_region = context->m_record.m_region;
	m_record.m_04 = context->m_record.m_04;
	m_record.m_08 = context->m_record.m_08;
	m_record.m_0C = context->m_record.m_0C;
	int regionOwner = m_record.m_region->m_ownerPlayer;
	if (regionOwner != ((Rva002B2B66 *)TheLivingWorldLogic)->rva002B2B66())
		((Rva005E3049 *)this)->rva005E3049(2, 0);
}
