// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
#include "Coord2D.h"
#include "Coord3D.h"

class Rva002D3627Host
{
public:
	bool rva002BF5B0(const Coord2D *input, Coord3D *output);
};
class Vector3;
class Rva002BF4F3
{
public:
	bool rva002BF5B0(const Vector3 *input, Vector3 *output);
};
extern Rva002D3627Host *g_00DFEF18;

class Rva00319AA0Target
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5(const Coord3D *position);
};

// The 0x00318B83 getter, under its rowed Drawable spelling; the records it
// returns and the 0x00538D17 / 0x003195C9 callees keep their ledger names,
// which are address-derived ABI views, not identities of this receiver.
struct TWheelInfo;
class Drawable
{
public:
	const TWheelInfo *getWheelInfo() const;
};

struct Rva00538CEFPair;
class Rva00538CEF
{
public:
	bool rva00538D17(Rva00538CEFPair *out);
};

class Rva003195C9Owner
{
public:
	void rva003195C9();
};

struct Rva003197B7Record
{
	unsigned char m_bytes[16];
};
struct Rva003197B7Records
{
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	Rva003197B7Record *m_begin;
	Rva003197B7Record *m_end;
};

class Rva00319AA0
{
public:
	void rva00319AA0(const Coord2D *position);
	void rva003197B7();
private:
	unsigned char m_head[0x3C];
	Coord2D m_cachedPosition;
	Coord2D m_position;
	unsigned char m_unknown4C[0x3C];
	Rva00319AA0Target *m_target;
};

// Native 0x00319AA0..0x00319B0A ends RET 4. It copies the two coordinate
// words to +0x44/+0x48, calls the 55-byte same-receiver helper 0x003197B7,
// then, when +0x88 is nonnull, maps a zero-height local through 0x002BF5B0
// and passes it to target vslot 5. The helper's own native tail calls the
// RET-0 0x003195C9 without stack arguments. All receiver, target and helper
// names are address-derived ABI views; original class identities are unknown.
void Rva00319AA0::rva00319AA0(const Coord2D *position)
{
	m_position = *position;
	rva003197B7();
	if (m_target)
	{
		Coord3D world = { m_position.x, m_position.y, 0.0f };
		((Rva002BF4F3 *)g_00DFEF18)->rva002BF5B0((const Vector3 *)&m_position, (Vector3 *)&world);
		m_target->slot5(&world);
	}
}

// Native 0x003197B7..0x003197EE (55B): nullable record collection from
// 0x00318B83; with any 16-byte records, 0x00538D17 writes the XY from them to
// +0x3C/+0x40, otherwise +0x44/+0x48 is copied there; then a tail call to
// 0x003195C9. The non-empty test is written `size() > 0`, which keeps
// retail's sar/je rather than cl's folded test of the byte count.
void Rva00319AA0::rva003197B7()
{
	Rva003197B7Records *records = (Rva003197B7Records *)
		reinterpret_cast<const Drawable *>(this)->getWheelInfo();
	if (records && records->size() > 0)
		((Rva00538CEF *)records)->rva00538D17((Rva00538CEFPair *)&m_cachedPosition);
	else
		m_cachedPosition = m_position;
	((Rva003195C9Owner *)this)->rva003195C9();
}
