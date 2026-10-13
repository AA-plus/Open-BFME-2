// ?rva0009C422@Rva0009D55BProduct@@UAEX_N@Z
// partial score=0.95 date=2026-10-13
// ?rva0009C422@Rva0009D55BProduct@@UAEX_N@Z
// partial score=0.94 date=2026-10-12
// ?rva0009C422@Rva0009D55BProduct@@UAEX_N@Z
// partial score=0.94 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ??0Rva0009D55BProduct@@QAE@XZ retail 0x0009D55B..0x0009D6E8 (397 bytes EH).
// Product of the W3D game client factory 0x0004C8DD (vtable 0x00BC4738;
// new 0x1D4). Runs the LivingWorld constructor 0x002C0120 (its unwind
// funclet 0x00760638 calls the base dtor 0x002BFB2D) then stores vtable
// 0x00BC89C8 and initialises its own members: six zeroed words (+0xC0)
// two 1.0 floats (+0xD8) five float triples (+0xE0 zero / +0xEC 0.9 /
// +0xF8 +0x104 +0x110 zero) then 0 / 10.0 at +0x11C/+0x120 and 1.0 / 0 /
// pi/6 at +0x134..+0x13C; four 12-byte elements at +0x140 built through
// the vector constructor iterator 0x00001423 with the folded trivial ctor
// 0x0047A6A9; zeroed words and floats at +0x188..+0x1AC; two zeroed int
// pairs (+0x1B0 +0x1B8); an STLport vector at +0x1C0 (folded _Vector_base
// ctor 0x00211E58) and two zeroed words. The deleting dtor 0x0009D9A1 and
// dtor 0x0009D6FA are rowed under the opaque name Rva009D6FA. Member
// meanings element types and the class name are unresolved.
//
// ??1Rva0009D55BProduct@@UAE@XZ retail 0x0009D6FA..0x0009D862 (360 bytes EH),
// the destructor the deleting dtor 0x0009D9A1 calls (pin ??1Rva009D6FA).
// After the rowed 0x0009AB85 shutdown it takes the three render objects at
// +0xC8/+0xCC/+0xD0 out of the +0xC4 scene (scene slot 3) when they report
// being in it (slot 123), releases the five ref-counted words +0xC0..+0xD0
// (inline Release_Ref, Delete_This slot 0) and clears each, then unwinds
// the +0x1D0 texture reference (Release_Ref 0x0021ED10) and the +0x1C0
// vector before the LivingWorld destructor 0x002BFB2D.
#include <vector>
#include "ascii_string.h"
// The +0x1C0 vector's storage is freed inline through the game free
// (0x00030830), as in the sibling water-object units.
void Rva00030830FreeAllocation(void *);
namespace _STL {
 template<> inline void allocator<int>::deallocate(int *p, size_type) const { if (p) Rva00030830FreeAllocation(p); }
}

// 12-byte element whose out-of-line default constructor is the ICF-folded
// trivial ctor 0x0047A6A9 (rowed as ??0ICoord3D@@QAE@XZ among others).
struct ICoord3D
{
	ICoord3D();
	int x;
	int y;
	int z;
};

struct Rva0009D55BVec3
{
	float x, y, z;
	Rva0009D55BVec3(float v) : x(v), y(v), z(v) {}
	Rva0009D55BVec3 &operator=(const Rva0009D55BVec3 &v) { x = v.x; y = v.y; z = v.z; return *this; }
};

struct Rva0009D55BPair
{
	int a, b;
	Rva0009D55BPair() : a(0), b(0) {}
};

class Rva0009AB6B { public: void rva0009AB85(); };
class TextureBaseClass { public: void Release_Ref(); };

#define D55B_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define D55B_SLOTS16(p) D55B_SLOTS4(p##0) D55B_SLOTS4(p##1) D55B_SLOTS4(p##2) D55B_SLOTS4(p##3)

// The ref-counted words: slot 0 deletes, the count is at +4.
class Rva0009D6FARef
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_numRefs == 0) Delete_This(); }
	int m_numRefs;
};
class Rva0009D6FARenderObj : public Rva0009D6FARef
{
public:
	D55B_SLOTS16(r0) D55B_SLOTS16(r1) D55B_SLOTS16(r2) D55B_SLOTS16(r3)
	D55B_SLOTS16(r4) D55B_SLOTS16(r5) D55B_SLOTS16(r6)
	D55B_SLOTS4(r70) D55B_SLOTS4(r71) virtual void r720(); virtual void r721();
	virtual bool isInScene();	// slot 123
};
class Rva0009D6FAScene : public Rva0009D6FARef
{
public:
	virtual void s1(); virtual void s2();
	virtual void removeRenderObject(Rva0009D6FARenderObj *obj);	// slot 3
};
struct Rva0009D6FATexture
{
	Rva0009D6FATexture() : m_ptr(0) {}
	~Rva0009D6FATexture() { if (m_ptr) m_ptr->Release_Ref(); }
	TextureBaseClass *m_ptr;
};
#define D55B_REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

class LivingWorld
{
public:
	LivingWorld();
	virtual ~LivingWorld();
	virtual void rva002BF391(bool active);	// the state handler 0x002BF391

private:
	char m_body[0xC0 - 4];
};

class Rva0009D55BProduct : public LivingWorld
{
public:
	Rva0009D55BProduct();
	virtual ~Rva0009D55BProduct();
	virtual void rva0009C784(unsigned int phase, unsigned int previous);
	virtual void rva0009D862();
	virtual void rva0009DB5A(bool active);
	virtual void rva0009C422(bool active);

private:
	Rva0009D6FARef *m_C0;
	Rva0009D6FAScene *m_C4;
	Rva0009D6FARenderObj *m_C8;
	Rva0009D6FARenderObj *m_CC;
	Rva0009D6FARenderObj *m_D0;
	int m_D4;
	float m_D8;
	float m_DC;
	Rva0009D55BVec3 m_E0;
	Rva0009D55BVec3 m_EC;
	Rva0009D55BVec3 m_F8;
	Rva0009D55BVec3 m_104;
	Rva0009D55BVec3 m_110;
	float m_11C;
	float m_120;
	char m_pad124[0x134 - 0x124];
	float m_134;
	float m_138;
	float m_13C;
	ICoord3D m_140[4];
	char m_pad170[0x188 - 0x170];
	int m_188;
	int m_18C;
	int m_190;
	int m_194;
	float m_198;
	int m_19C;
	float m_1A0;
	float m_1A4;
	float m_1A8;
	float m_1AC;
	Rva0009D55BPair m_1B0;
	Rva0009D55BPair m_1B8;
	std::vector<int> m_1C0;
	int m_1CC;
	Rva0009D6FATexture m_1D0;
};

Rva0009D55BProduct::Rva0009D55BProduct()
	: m_C0(0), m_C4(0), m_C8(0), m_CC(0), m_D0(0), m_D4(0),
	  m_D8(1.0f), m_DC(1.0f),
	  m_E0(0.0f), m_EC(0.9f), m_F8(0.0f), m_104(0.0f), m_110(0.0f),
	  m_11C(0.0f), m_120(10.0f), m_134(1.0f), m_138(0.0f), m_13C(0.52359879f),
	  m_188(0), m_18C(0), m_190(0), m_194(0), m_198(0.0f), m_19C(0), m_1AC(0.0f),
	  m_1CC(0)
{
}

Rva0009D55BProduct::~Rva0009D55BProduct()
{
	((Rva0009AB6B *)this)->rva0009AB85();
	if (m_C8 && m_C4 && m_C8->isInScene())
		m_C4->removeRenderObject(m_C8);
	if (m_CC && m_C4 && m_CC->isInScene())
		m_C4->removeRenderObject(m_CC);
	if (m_D0 && m_C4 && m_D0->isInScene())
		m_C4->removeRenderObject(m_D0);
	D55B_REF_PTR_RELEASE(m_C0);
	D55B_REF_PTR_RELEASE(m_C4);
	D55B_REF_PTR_RELEASE(m_C8);
	D55B_REF_PTR_RELEASE(m_CC);
	D55B_REF_PTR_RELEASE(m_D0);
}

// ?rva0009C784@Rva0009D55BProduct@@UAEXII@Z retail 0x0009C784 (144 bytes,
// ret 8; slot 19 of the product table 0x00BC89C8): after the rowed
// LivingWorld handler 0x002BE7FA, phase 2 clears the +0x198 fade, starts
// the "FadeInGameMovie" transition group (rowed setGroup / enable) and hides
// the engine mouse; phase 3 sets the fade to 1, clears +0x134/+0x138 and
// calls the table's slot 10 with true.
class Rva002BE7FA { public: void rva002BE7FA(unsigned int a, unsigned int b); };
class GameWindowTransitionsHandler { public: void setGroup(AsciiString name, bool immediate); };
extern GameWindowTransitionsHandler *TheTransitionHandler;
class Rva001DBB82OneSetter { public: void enable(); };
class Mouse { public: void _bfme_setEngineVisibility(bool visible); };
extern Mouse *TheMouse;
class Rva0009C784Slots
{
public:
	D55B_SLOTS4(v0) D55B_SLOTS4(v1) virtual void v20(); virtual void v21();
	virtual void slot10(bool flag);
};

void Rva0009D55BProduct::rva0009C784(unsigned int phase, unsigned int previous)
{
	((Rva002BE7FA *)this)->rva002BE7FA(phase, previous);
	if (phase == 2)
	{
		m_198 = 0.0f;
		TheTransitionHandler->setGroup(AsciiString("FadeInGameMovie"), false);
		((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
		TheMouse->_bfme_setEngineVisibility(false);
	}
	else if (phase == 3)
	{
		m_198 = 1.0f;
		m_134 = 0.0f;
		m_138 = 0.0f;
		((Rva0009C784Slots *)this)->slot10(true);
	}
}

// ?rva0009D862@Rva0009D55BProduct@@UAEXXZ retail 0x0009D862 (319 bytes, EH;
// slot 4 of the product table): after the rowed shutdown 0x0009AB85 it
// creates the camera (+0xC0, CameraClass), the scene built on this (+0xC4,
// rowed 0x0009AA0F) and three lights (+0xC8/+0xCC/+0xD0, LightClass type 1),
// sets +0x134 to 1, copies the +0x104 vector to +0xF8 and runs the pinned
// refreshes 0x0009BAA4 and 0x0009CD9B.
class Vector2 { public: float x, y; };
class CameraClass
{
public:
	CameraClass();
	float Get_Aspect_Ratio() const;
	void Set_Viewport(const Vector2 &lo, const Vector2 &hi);
	void Set_Aspect_Ratio(float ratio);
	char m_data[0x3FC];
};
class Rva0009AA0F { public: Rva0009AA0F(int owner); char m_data[0x10C]; };
class LightClass { public: enum LightType { POINT = 0, DIRECTIONAL = 1 }; LightClass(LightType type); char m_data[0x120]; };
class Rva0009C134Host { public: void rva0009BAA4(); void rva0009CD9B(); };

void Rva0009D55BProduct::rva0009D862()
{
	((Rva0009AB6B *)this)->rva0009AB85();
	m_C0 = (Rva0009D6FARef *)new CameraClass;
	m_C4 = (Rva0009D6FAScene *)new Rva0009AA0F((int)this);
	m_C8 = (Rva0009D6FARenderObj *)new LightClass(LightClass::DIRECTIONAL);
	m_CC = (Rva0009D6FARenderObj *)new LightClass(LightClass::DIRECTIONAL);
	m_D0 = (Rva0009D6FARenderObj *)new LightClass(LightClass::DIRECTIONAL);
	m_134 = 1.0f;
	m_F8 = m_104;
	((Rva0009C134Host *)this)->rva0009BAA4();
	((Rva0009C134Host *)this)->rva0009CD9B();
}

// ?rva0009DB5A@Rva0009D55BProduct@@UAEX_N@Z retail 0x0009DB5A (154 bytes,
// ret 4): deactivation first resets the view (rowed 0x0009DA28); the
// LivingWorld handler 0x002BF391 (unrowed, pinned) always runs, but only a
// change of the +0x18 state continues: activation runs the manager's
// rowed cleanup and, with the global data's +0x60 shadow flag, copies the
// manager's +0x1E4 word into the shadow manager, places its light at
// +0x1A0..+0x1A8 and adds the shadows (rowed 0x0009DB47); deactivation runs
// the manager's 0x002141D1 and resets the view again.
class Rva0009D9BD { public: void rva0009DA28(); void rva0009DB47(); };
class LivingWorldManager { public: void rva002142EA(); };
extern LivingWorldManager *TheLivingWorldManager;
class Rva002141D1 { public: void rva002141D1(); };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class W3DShadowManager;
extern W3DShadowManager *TheW3DShadowManager;
class W3DGameClientShadowShim { public: void setLightPosition(int index, float x, float y, float z); };
struct Rva0009DB5AShadowView { void *m_vtbl; int m_04; };
struct Rva0009DB5AGlobalView { unsigned char m_pad[0x60]; bool m_shadows; };
struct Rva0009DB5AManagerView { unsigned char m_pad[0x1E4]; int m_1E4; };
struct Rva0009DB5ALivingWorldView { unsigned char m_pad[0x18]; bool m_active; bool m_viewMode; };

void Rva0009D55BProduct::rva0009DB5A(bool active)
{
	if (!active)
		((Rva0009D9BD *)this)->rva0009DA28();
	if (((Rva0009DB5ALivingWorldView *)this)->m_active == active)
	{
		LivingWorld::rva002BF391(active);
		return;
	}
	LivingWorld::rva002BF391(active);
	if (active)
	{
		TheLivingWorldManager->rva002142EA();
		if (((Rva0009DB5AGlobalView *)TheWritableGlobalData)->m_shadows)
		{
			((Rva0009DB5AShadowView *)TheW3DShadowManager)->m_04 = ((Rva0009DB5AManagerView *)TheLivingWorldManager)->m_1E4;
			((W3DGameClientShadowShim *)TheW3DShadowManager)->setLightPosition(0, m_1A0, m_1A4, m_1A8);
			((Rva0009D9BD *)this)->rva0009DB47();
		}
	}
	else
	{
		((Rva002141D1 *)TheLivingWorldManager)->rva002141D1();
		((Rva0009D9BD *)this)->rva0009DA28();
	}
}

// ?rva0009C422@Rva0009D55BProduct@@UAEX_N@Z retail 0x0009C422 (218 bytes,
// ret 4; slot 20 of the product table): remembers the camera's aspect ratio
// once (+0x1AC) unless the +0x19 view mode is already on, stores the mode,
// and either copies the living-world manager's +0x34 and +0x2C/+0x30 words
// into +0x134/+0xF8/+0xFC and refreshes (0x0009BAA4), or restores the full
// viewport and saved aspect ratio and calls the table's slot 7.
struct Rva0009C422ManagerHead { unsigned char m_pad[0x14]; };
struct Rva0009C422ManagerPart { unsigned char m_pad[0x18]; float m_18; float m_1C; };
struct Rva0009C422ManagerView : public Rva0009C422ManagerHead, public Rva0009C422ManagerPart { Rva0009C422ManagerPart &part() { return *this; } float m_34; };
class Rva0009C422Slots
{
public:
	D55B_SLOTS4(v0) virtual void v4(); virtual void v5(); virtual void v6();
	virtual void slot7();
};

void Rva0009D55BProduct::rva0009C422(bool active)
{
	Rva0009DB5ALivingWorldView *state = (Rva0009DB5ALivingWorldView *)this;
	if (m_1AC == 0.0f && m_C0)
	{
		if (state->m_viewMode)
			return;
		m_1AC = ((CameraClass *)m_C0)->Get_Aspect_Ratio();
	}
	state->m_viewMode = active;
	if (!active)
	{
		if (m_C0)
		{
			Vector2 lo = { 0.0f, 0.0f };
			Vector2 hi = { 1.0f, 1.0f };
			((CameraClass *)m_C0)->Set_Viewport(lo, hi);
			if (m_1AC == 0.0f)
				return;
			((CameraClass *)m_C0)->Set_Aspect_Ratio(m_1AC);
		}
		((Rva0009C422Slots *)this)->slot7();
		return;
	}
	Rva0009C422ManagerView *manager = (Rva0009C422ManagerView *)TheLivingWorldManager;

	m_134 = manager->m_34;
	m_F8.x = (manager->part()).m_18;
	m_F8.y = (manager->part()).m_1C;
	((Rva0009C134Host *)this)->rva0009BAA4();
}
