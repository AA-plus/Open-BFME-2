// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ?rva000B901D@Rva000B901D@@QAEXHPBURva000B901DNames@@@Z, retail 0x000B901D
// (87 bytes, RET 8): a slot of the W3DModelDraw-family secondary table
// 0x007CBB78 (complete-object +0x0C, so the drawable is read at -4 and the
// render object at +0x44). With a drawable that has an Object (+0xFC) and a
// render object, the first argument and the first of the given names (or no
// name for an empty list) go to the render object's BFME 2 slot +0x1F8 (the
// two-argument virtual HLodClass forwards to its sub-objects, 0x0019BA70).
// Address-derived names.
#include "ascii_string.h"

struct Rva000B901DNames
{
	AsciiString *m_begin;
	AsciiString *m_end;
};

struct Rva000B901DDrawable
{
	unsigned char m_pad000[0xFC];
	void *m_object;	// +0xFC
};

#define RSLOT(n) virtual void s##n();
class Rva000B901DRenderObj
{
public:
	RSLOT(000) RSLOT(001) RSLOT(002) RSLOT(003) RSLOT(004) RSLOT(005) RSLOT(006) RSLOT(007) RSLOT(008) RSLOT(009)
	RSLOT(010) RSLOT(011) RSLOT(012) RSLOT(013) RSLOT(014) RSLOT(015) RSLOT(016) RSLOT(017) RSLOT(018) RSLOT(019)
	RSLOT(020) RSLOT(021) RSLOT(022) RSLOT(023) RSLOT(024) RSLOT(025) RSLOT(026) RSLOT(027) RSLOT(028) RSLOT(029)
	RSLOT(030) RSLOT(031) RSLOT(032) RSLOT(033) RSLOT(034) RSLOT(035) RSLOT(036) RSLOT(037) RSLOT(038) RSLOT(039)
	RSLOT(040) RSLOT(041) RSLOT(042) RSLOT(043) RSLOT(044) RSLOT(045) RSLOT(046) RSLOT(047) RSLOT(048) RSLOT(049)
	RSLOT(050) RSLOT(051) RSLOT(052) RSLOT(053) RSLOT(054) RSLOT(055) RSLOT(056) RSLOT(057) RSLOT(058) RSLOT(059)
	RSLOT(060) RSLOT(061) RSLOT(062) RSLOT(063) RSLOT(064) RSLOT(065) RSLOT(066) RSLOT(067) RSLOT(068) RSLOT(069)
	RSLOT(070) RSLOT(071) RSLOT(072) RSLOT(073) RSLOT(074) RSLOT(075) RSLOT(076) RSLOT(077) RSLOT(078) RSLOT(079)
	RSLOT(080) RSLOT(081) RSLOT(082) RSLOT(083) RSLOT(084) RSLOT(085) RSLOT(086) RSLOT(087) RSLOT(088) RSLOT(089)
	RSLOT(090) RSLOT(091) RSLOT(092) RSLOT(093) RSLOT(094) RSLOT(095) RSLOT(096) RSLOT(097) RSLOT(098) RSLOT(099)
	RSLOT(100) RSLOT(101) RSLOT(102) RSLOT(103) RSLOT(104) RSLOT(105) RSLOT(106) RSLOT(107) RSLOT(108) RSLOT(109)
	RSLOT(110) RSLOT(111) RSLOT(112) RSLOT(113) RSLOT(114) RSLOT(115) RSLOT(116) RSLOT(117) RSLOT(118) RSLOT(119)
	RSLOT(120) RSLOT(121) RSLOT(122) RSLOT(123) RSLOT(124) RSLOT(125)
	virtual void rva0019BA70(int a, const char *name);	// +0x1F8
};
#undef RSLOT

class Rva000B901D
{
public:
	void rva000B901D(int a, const Rva000B901DNames *names);
private:
	Rva000B901DDrawable *drawable() const { return *(Rva000B901DDrawable *const *)((const char *)this - 4); }
	unsigned char m_pad00[0x44];
	Rva000B901DRenderObj *m_renderObject;	// +0x44
};

void Rva000B901D::rva000B901D(int a, const Rva000B901DNames *names)
{
	if (drawable() && drawable()->m_object && m_renderObject)
	{
		if (names->m_begin == names->m_end)
			m_renderObject->rva0019BA70(a, 0);
		else
			m_renderObject->rva0019BA70(a, names->m_begin[0].str());
	}
}
