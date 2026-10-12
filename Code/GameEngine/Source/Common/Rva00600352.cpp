// cl: /DNDEBUG /MD /EHsc
// ?rva00600352Init@@YIPAVRva00600352@@PAV1@HHHHH@Z @0x00600352 39B evidence:
// fastcall init (this, fwd-dead-forwarded, a, b, c, d-dead): chains to
// pinned fastcall ?rva00600305@@YIXPAVRva00600305Obj@@HHHH@Z @0x00600305
// with (this, fwd, a, b, c) pushed c,b,a; m_08 = a; installs vtable 0x00C7A620 by
// literal store; returns this; ret 0x10. Same fastcall family as 0x005F8E37.
// TU-local view only.
class Rva00600305Obj;
void __fastcall rva00600305(Rva00600305Obj *o, int fwd, int s1, int s2, int s3);

class Rva00600352
{
public:
	char m_pad[8];
	int m_08;
};

Rva00600352 *__fastcall rva00600352Init(Rva00600352 *o, int fwd, int volatile a, int b, int c, int d)
{
	rva00600305((Rva00600305Obj *)o, fwd, b, c, d);
	o->m_08 = a;
	((int *)o)[0] = 0x00C7A620;
	return o;
}

// ??0Rva006003FC@@QAE@PAX00@Z, native 600432..6004A5 (115B, EH, RET 0xC;
// callers the three player-page constructors 0x005FB14E, 0x005FB30A and
// 0x005FB4DF): over the zeroing counted base (Rva0007DF07, destructor
// 0x004E84A4 as its unwind action) it builds its +8 member through the
// constructor above, called as the thiscall it is (owner, two inputs and
// the player's colour with full alpha; the colour comes from the third
// input's object through 0x003F468D and RGBColor::getAsInt at +0x184), then
// copies the third input's three words to +0x14. Address-derived names;
// the member constructor's thiscall spelling is pinned at 0x00600352.
struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};
class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
	Rva0007DF07() {}
	virtual ~Rva0007DF07();
};
#include "../../../Libraries/Include/Lib/RGBColor.h"
// 0x003F468D returns the player as an int (its rowed spelling).
class Rva003F468D { public: int rva003F468D(int a, int b); };
struct Rva006003FCPlayer
{
	unsigned char m_pad000[0x184];
	RGBColor m_color;				// +0x184
	const RGBColor *getColor() const { return &m_color; }
};
struct Rva006003FCInputs
{
	Rva003F468D *m_source;
	int m_a;
	int m_b;
};
class Rva006003FCMember
{
public:
	Rva006003FCMember(void *owner, void *first, void *second, unsigned int color);	// 0x00600352
private:
	unsigned char m_data[0x0c];
};
static __forceinline unsigned int Rva006003FCColor(const Rva006003FCInputs *in)
{
	return ((Rva006003FCPlayer *)in->m_source->rva003F468D(in->m_a, in->m_b))->getColor()->getAsInt() | 0xff000000;
}
class Rva006003FC : public Rva0007DF07
{
public:
	Rva006003FC(void *first, void *second, void *third);
private:
	Rva006003FCMember m_08;			// +0x08
	Rva006003FCInputs m_14;			// +0x14
};
Rva006003FC::Rva006003FC(void *first, void *second, void *third)
	: m_08(this, first, second, Rva006003FCColor((const Rva006003FCInputs *)third))
{
	const Rva006003FCInputs *in = (const Rva006003FCInputs *)third;
	m_14.m_source = in->m_source;
	m_14.m_a = in->m_a;
	m_14.m_b = in->m_b;
}
