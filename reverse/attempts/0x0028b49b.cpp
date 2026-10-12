// ?rva0028B49B@Object@@QAEXPAPAV1@0@Z
// partial score=0.94 date=2026-10-12
// ?rva0028B49B@Object@@QAEXPAPAV1@0@Z
// 2026-10-12 (claude-opus-5-5): +0x90 as a small link wrapper (operator=
// returning *this, pointer conversion) reproduces retail's lea eax,&m_prev /
// store / mov eax,esi test and ESI/EDX roles at 51 B. Only left: retail loads
// *ppTail before the m_next clear; reading it first (named local, inline
// helper taking it by value) restores the order but swaps ESI/EDX. Needs the
// region flags /O1 /arch:SSE /G7 explicitly in a new unit.
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc

// ?isInList@Object@@QBE_NPAPAV1@@Z, retail 0x0028B47C (31 bytes).
// Object::isInList checks the intrusive list links at +0x8C/+0x90.
// Evidence: BFME1 donor Object.cpp:3124 `Bool result = m_prev || m_next ||
// *pListHead == this`, and the sole retail caller GameLogic::friend_awakenUpdateModule
// (0x0024297F) passes &GameLogic+0xAC as pListHead with this=obj.
//
// 0x0028B4CE follows isInList and BFME's two-list prepend 0x0028B49B in
// retail as setLayer does in Zero Hour's Object.cpp; its body changed shape
// in BFME, so the name stays address-derived.

typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Object;

class TerrainLogic
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05(); virtual void vslot06(); virtual void vslot07();
	virtual void vslot08(); virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14(); virtual void vslot15();
	virtual void vslot16(); virtual void vslot17(); virtual void vslot18(); virtual void vslot19();
	virtual void vslot20(); virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24(); virtual void vslot25(); virtual void vslot26(); virtual void vslot27();
	virtual void vslot28(); virtual void vslot29(); virtual void vslot30(); virtual void vslot31();
	virtual void vslot32(); virtual void vslot33(); virtual void vslot34(); virtual void vslot35();
	virtual void vslot36(); virtual void vslot37(); virtual void vslot38(); virtual void vslot39();
	virtual void vslot40(); virtual void vslot41(); virtual void vslot42();
	virtual Bool vslot43(Object *obj, int layer, Bool flag);
};
extern TerrainLogic *TheTerrainLogic;

// The object at Object+0xA4 (see ObjectRvaSmallGetters.cpp).
class Rva004DD843
{
public:
	void rva004DE2ED();
};

struct ObjectLink
{
	ObjectLink &operator=(Object *p) { m_ptr = p; return *this; }
	operator Object *() const { return m_ptr; }
	Object *m_ptr;
};
class Object
{
public:
	Bool isInList(Object **pListHead) const;
	void rva0028B4CE(PathfindLayerEnum layer);
	void rva0028B49B(Object **ppHead, Object **ppTail);

private:
	unsigned char m_pre[0x8C];
	Object *m_next; // +0x8C
	ObjectLink m_prev; // +0x90
	unsigned char m_pad94[0xA4 - 0x94];
	Rva004DD843 *m_a4; // +0xA4
	unsigned char m_padA8[0x40C - 0xA8];
	PathfindLayerEnum m_layer; // +0x40C
};

Bool Object::isInList(Object **pListHead) const
{
	Bool result = m_prev || m_next || *pListHead == this;
	return result;
}

// ?rva0028B4CE@Object@@QAEXW4PathfindLayerEnum@@@Z, retail 0x0028B4CE (67B):
// the +0x40C layer setter in setLayer's position. On a change away from a
// non-ground layer it calls TheTerrainLogic's slot 43 with (this, old
// layer, true) - the arguments of Zero Hour's debug-only
// objectInteractsWithBridgeLayer check - then stores the layer and notifies
// the Object+0xA4 object through the pinned 0x004DE2ED.
void Object::rva0028B4CE(PathfindLayerEnum layer)
{
	if (layer != m_layer)
	{
		if (m_layer != LAYER_GROUND)
			TheTerrainLogic->vslot43(this, m_layer, true);
		m_layer = layer;
		if (m_a4)
			m_a4->rva004DE2ED();
	}
}

// ?rva0028B49B@Object@@QAEXPAPAVObject@@0@Z, retail 0x0028B49B (51B):
// tail-append to a (head, tail) pair: link after the old tail, take over
// an empty head, become the tail. Called once, by GameLogic's awake-module
// friend at 0x00242B19 with (&GameLogic+0xAC, &GameLogic+0xB0).
void Object::rva0028B49B(Object **ppHead, Object **ppTail)
{
	m_next = 0;
	m_prev = *ppTail;
	if (m_prev)
		((Object *)m_prev)->m_next = this;
	if (*ppHead == 0)
		*ppHead = this;
	*ppTail = this;
}
