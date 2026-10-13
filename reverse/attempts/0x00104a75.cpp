// ?rva00104A75@Rva001041D8@@QAEXXZ
// partial score=0.98 date=2026-10-13
// ?rva00104A75@Rva001041D8@@QAEXXZ
// partial score=0.98 date=2026-10-13
// ?rva00104A75@Rva001041D8@@QAEXXZ
// partial score=0.98 date=2026-10-13
// ?rva00104A75@Rva001041D8@@QAEXXZ
// partial score=0.98 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
// ?rva00104A75@Rva001041D8@@QAEXXZ retail 0x00104A75..0x00104BDA (357 bytes,
// RET): slot 16 of the 0x88-byte object's vtable 0x00BCF770 (destructor
// 0x001041D8 and constructor 0x0010461F, Rva001041D8Dtor.cpp; the W3D
// Palantir lead there stays unproven). With a source at +0x20, it draws the
// four-sided ring between the outer corners at +0x48 and the inner corners
// at +0x68 through the display's 2D renderer (TheDisplay slot 95): the ring
// geometry is rebuilt first (0x00104359) when the rowed check 0x00104195
// sees the saved corners at +0x28 move, the renderer takes the texture at
// +0x24 (0x000456C9) with its +0x48 flag set, its first word is held at 1
// for the draw and restored after, and each side is two triangles through
// the rowed 0x001049C7 with the UV rectangle at source +0x14, then the
// renderer draws (0x0011A040).
//
// Its own unit: the dtor unit links today, and 0x00104359 and 0x0011A040
// have no definition yet. Target facts: boundary, vtable slot, callees and
// member offsets from retail; all names are address-derived.
#include "Coord2D.h"

class TextureClass;
template<class T> class RefCountPtr
{
public:
	T *Referent;
};

class Render2DClass
{
public:
	int m_state;
	char m_04[0x48 - 4];
	bool m_48;
};

void Rva001049C7AddTriangle(Render2DClass *renderer,
	const Coord2D *v0, const Coord2D *v1, const Coord2D *v2,
	const Coord2D *uv0, const Coord2D *uv1, const Coord2D *uv2);

// The renderer's texture setter, rowed under an address-derived owner.
class Rva000456C9
{
public:
	void rva000456C9(const RefCountPtr<TextureClass> *texture);
};

// The renderer's draw, pinned under an address-derived owner.
class Rva0011A040Target
{
public:
	void rva0011A040();
};

class Display
{
public:
#define DISPLAY_SLOT(n) virtual void slot##n();
	DISPLAY_SLOT(00) DISPLAY_SLOT(01) DISPLAY_SLOT(02) DISPLAY_SLOT(03)
	DISPLAY_SLOT(04) DISPLAY_SLOT(05) DISPLAY_SLOT(06) DISPLAY_SLOT(07)
	DISPLAY_SLOT(08) DISPLAY_SLOT(09) DISPLAY_SLOT(10) DISPLAY_SLOT(11)
	DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14) DISPLAY_SLOT(15)
	DISPLAY_SLOT(16) DISPLAY_SLOT(17) DISPLAY_SLOT(18) DISPLAY_SLOT(19)
	DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23)
	DISPLAY_SLOT(24) DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27)
	DISPLAY_SLOT(28) DISPLAY_SLOT(29) DISPLAY_SLOT(30) DISPLAY_SLOT(31)
	DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34) DISPLAY_SLOT(35)
	DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38) DISPLAY_SLOT(39)
	DISPLAY_SLOT(40) DISPLAY_SLOT(41) DISPLAY_SLOT(42) DISPLAY_SLOT(43)
	DISPLAY_SLOT(44) DISPLAY_SLOT(45) DISPLAY_SLOT(46) DISPLAY_SLOT(47)
	DISPLAY_SLOT(48) DISPLAY_SLOT(49) DISPLAY_SLOT(50) DISPLAY_SLOT(51)
	DISPLAY_SLOT(52) DISPLAY_SLOT(53) DISPLAY_SLOT(54) DISPLAY_SLOT(55)
	DISPLAY_SLOT(56) DISPLAY_SLOT(57) DISPLAY_SLOT(58) DISPLAY_SLOT(59)
	DISPLAY_SLOT(60) DISPLAY_SLOT(61) DISPLAY_SLOT(62) DISPLAY_SLOT(63)
	DISPLAY_SLOT(64) DISPLAY_SLOT(65) DISPLAY_SLOT(66) DISPLAY_SLOT(67)
	DISPLAY_SLOT(68) DISPLAY_SLOT(69) DISPLAY_SLOT(70) DISPLAY_SLOT(71)
	DISPLAY_SLOT(72) DISPLAY_SLOT(73) DISPLAY_SLOT(74) DISPLAY_SLOT(75)
	DISPLAY_SLOT(76) DISPLAY_SLOT(77) DISPLAY_SLOT(78) DISPLAY_SLOT(79)
	DISPLAY_SLOT(80) DISPLAY_SLOT(81) DISPLAY_SLOT(82) DISPLAY_SLOT(83)
	DISPLAY_SLOT(84) DISPLAY_SLOT(85) DISPLAY_SLOT(86) DISPLAY_SLOT(87)
	DISPLAY_SLOT(88) DISPLAY_SLOT(89) DISPLAY_SLOT(90) DISPLAY_SLOT(91)
	DISPLAY_SLOT(92) DISPLAY_SLOT(93) DISPLAY_SLOT(94)
#undef DISPLAY_SLOT
	virtual Render2DClass *get2DRenderer();
};
extern Display *TheDisplay;

// The UV rectangle the source carries at +0x14.
struct Rva00104A75Rect
{
	Coord2D lo;
	Coord2D hi;
};

struct Rva00104A75Source
{
	char m_00[0x14];
	Rva00104A75Rect m_uv;
};

// Holds the renderer's first word at a value for a scope and restores it.
struct Rva00104A75StateHold
{
	Rva00104A75StateHold(Render2DClass *renderer, int value)
		: m_renderer(renderer), m_saved(renderer->m_state)
	{
		renderer->m_state = value;
	}
	~Rva00104A75StateHold() { m_renderer->m_state = m_saved; }
	Render2DClass *m_renderer;
	int m_saved;
};

class Rva001041D8
{
public:
	void rva00104A75();
	void rva00104359();
	bool rva00104195();

private:
	char m_00[0x20];
	Rva00104A75Source *m_source;
	RefCountPtr<TextureClass> m_texture;
	Coord2D m_saved[4];
	Coord2D m_outer[4];
	Coord2D m_inner[4];
};

// The saved-corner check 0x00104195 is rowed under its own owner.
class Rva00104195
{
public:
	bool rva00104195();
};

void Rva001041D8::rva00104A75()
{
	if (!m_source)
		return;
	Render2DClass *renderer = TheDisplay->get2DRenderer();
	if (!renderer)
		return;
	if (((Rva00104195 *)this)->rva00104195())
		rva00104359();
	renderer->m_48 = true;
	((Rva000456C9 *)renderer)->rva000456C9(&m_texture);
	Rva00104A75StateHold hold(renderer, 1);
	const Rva00104A75Rect *uv = &m_source->m_uv;
	for (int i = 0; i < 4; i++) {
		int next = i + 1;
		if (next >= 4)
			next = i - 3;
		Coord2D *innerNext = &m_inner[next];
		Coord2D *outerNext = &m_outer[next];
		Coord2D uv0;		uv0.x = uv->lo.x;
		uv0.y = uv->lo.y;
		Coord2D uv1;
		uv1.x = uv->hi.x;
		uv1.y = uv->lo.y;
		Coord2D uv2;
		uv2.x = uv->hi.x;
		uv2.y = uv->hi.y;
		Coord2D uv3;
		uv3.x = uv->lo.x;
		uv3.y = uv->hi.y;
		Rva001049C7AddTriangle(renderer, &m_outer[i], &m_inner[i], innerNext, &uv0, &uv1, &uv2);
		Rva001049C7AddTriangle(renderer, &m_outer[i], innerNext, outerNext, &uv0, &uv2, &uv3);
	}
	((Rva0011A040Target *)renderer)->rva0011A040();
}
