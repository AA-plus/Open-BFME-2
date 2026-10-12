// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no ledger row covered (second
// file; see GapBodiesSeat1A.cpp). Retail bytes establish every shape; owning
// classes are not recovered unless named, so each keeps an address-derived
// name and a view of only the members it touches. Callees are the ledger's
// existing rows under their current spellings.
#include "ascii_string.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

// --- 0x002C1F6F (16B): unlinks the head node (next at +4) and returns it by
// value; the word argument is unused.
struct Rva002C1F6FNode
{
	int m_00;
	Rva002C1F6FNode *m_next;
};

struct Rva002C1F6FIterator
{
	Rva002C1F6FIterator(Rva002C1F6FNode *node) : m_node(node) {}
	Rva002C1F6FNode *m_node;
};

class Rva002C1F6F
{
public:
	Rva002C1F6FIterator rva002C1F6F(int unused);
private:
	Rva002C1F6FNode *m_head;
};

Rva002C1F6FIterator Rva002C1F6F::rva002C1F6F(int)
{
	Rva002C1F6FNode *node = m_head;
	m_head = node->m_next;
	return Rva002C1F6FIterator(node);
}

// --- 0x002C580F (17B): float setter +0x560; 0x002C5887 (20B): stores a
// by-value position at +0x554; 0x002CEF9B (15B): halfword setter +0x5D8.
class Rva002C580F
{
public:
	void rva002C580F(float value);
	void rva002C5887(Coord3D pos);
	void rva002CEF9B(short value);
private:
	char m_pad000[0x554];
	Coord3D m_554;
	float m_560;
	char m_pad564[0x5D8 - 0x564];
	short m_5D8;
};

void Rva002C580F::rva002C580F(float value)
{
	m_560 = value;
}

void Rva002C580F::rva002C5887(Coord3D pos)
{
	m_554 = pos;
}

void Rva002C580F::rva002CEF9B(short value)
{
	m_5D8 = value;
}

// --- 0x002C5DBD (19B, cdecl): whether the string equals the text.
int Rva002C5DBD(const char *text, const AsciiString *str)
{
	return str->compare(text) == 0;
}

// --- 0x002C71CA (23B): whether +0x439 has bits outside the mask;
// 0x002C7218 (17B): the +4 record's +0x128 word is clear; 0x002C75FA (17B):
// the +4 record's +0x35C flag, false without one; 0x002C7447 (19B) and
// 0x002C745A (15B): toggle / set the indexed flag of the +0x36 array;
// 0x002C74CB (14B) and 0x002C74EA (17B): the indexed 0x1C-byte record at
// +0x44 and 0x4C-byte record at +0x194.
struct Rva002C7218Record
{
	char m_pad000[0x128];
	int m_128;
	char m_pad12C[0x35C - 0x12C];
	bool m_35C;
};

struct Rva002C74CBRecord
{
	char m_data[0x1C];
};

struct Rva002C74EARecord
{
	char m_data[0x4C];
};

class Rva002C71CA
{
public:
	int rva002C71CA(int mask) const;
	bool rva002C7218() const;
	bool rva002C75FA() const;
	void rva002C7447(int index);
	void rva002C745A(int index, bool value);
	Rva002C74CBRecord *rva002C74CB(int index);
	Rva002C74EARecord *rva002C74EA(int index);
private:
	int m_00;
	Rva002C7218Record *m_04;
	char m_pad08[0x36 - 8];
	bool m_flags[0x44 - 0x36];
	Rva002C74CBRecord m_44[(0x194 - 0x44) / 0x1C];
	Rva002C74EARecord m_194[1];
	char m_pad1E0[0x439 - 0x194 - 0x4C];
	unsigned char m_439;
};

int Rva002C71CA::rva002C71CA(int mask) const
{
	return (m_439 & ~mask) != 0;
}

bool Rva002C71CA::rva002C7218() const
{
	return m_04->m_128 == 0;
}

bool Rva002C71CA::rva002C75FA() const
{
	if (m_04)
		return m_04->m_35C;
	return false;
}

void Rva002C71CA::rva002C7447(int index)
{
	m_flags[index] = !m_flags[index];
}

void Rva002C71CA::rva002C745A(int index, bool value)
{
	m_flags[index] = value;
}

Rva002C74CBRecord *Rva002C71CA::rva002C74CB(int index)
{
	return &m_44[index];
}

Rva002C74EARecord *Rva002C71CA::rva002C74EA(int index)
{
	return &m_194[index];
}

// --- 0x002C751E (17B, cdecl): zeroes a 0x1C-byte record through the CRT
// memset thunk 0x006291AE.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

void Rva002C751E(Rva002C74CBRecord *record)
{
	ji_006291ae(record, 0, 0x1C);
}

// --- 0x002C92B8 (36B) and 0x002C92DC (30B): the rowed 0x002C9217 with the
// height difference of two records (+0x40) or the negated +8 value.
struct Rva002C92B8Record
{
	char m_pad00[8];
	float m_08;
	char m_pad0C[0x40 - 0x0C];
	float m_40;
};

class BfmeRangedWeaponTemplate
{
public:
	float rva002C9217(void *arg, float value);				// 0x002C9217
	float rva002C92B8(void *arg, const Rva002C92B8Record *from, const Rva002C92B8Record *to);
	float rva002C92DC(void *arg, const Rva002C92B8Record *rec);
};

float BfmeRangedWeaponTemplate::rva002C92B8(void *arg, const Rva002C92B8Record *from, const Rva002C92B8Record *to)
{
	return rva002C9217(arg, to->m_40 - from->m_40);
}

float BfmeRangedWeaponTemplate::rva002C92DC(void *arg, const Rva002C92B8Record *rec)
{
	return rva002C9217(arg, 0.0f - rec->m_08);
}

// --- 0x002C9846 (16B) and 0x002C9856 (21B): Object distance helpers over
// this or the other object's +0x38 position.
class Object
{
public:
	float rva002C97E8(const Coord3D *a, const Coord3D *b) const;					// 0x002C97E8
	float rva002636F6(const Coord3D *pos, const void *other, const Coord3D *otherPos) const;	// 0x002636F6
	float rva002C9846(const Coord3D *pos) const;
	float rva002C9856(const Coord3D *pos, const Object *other) const;
	char m_pad00[0x38];
	Coord3D m_pos;
};

float Object::rva002C9846(const Coord3D *pos) const
{
	return rva002C97E8(&m_pos, pos);
}

float Object::rva002C9856(const Coord3D *pos, const Object *other) const
{
	return rva002636F6(pos, other, &other->m_pos);
}

// --- 0x002D2CED (18B, cdecl): two pointed-to characters are equal.
int Rva002D2CED(const char *a, const char *b)
{
	return *a == *b;
}

// --- 0x002D3609 (12B): bit 0 of the +0x24 byte of the +0x78 record of the
// +0x10 object.
struct Rva002D3609Inner
{
	char m_pad00[0x24];
	unsigned char m_bit0 : 1;
};

struct Rva002D3609Outer
{
	char m_pad00[0x78];
	Rva002D3609Inner *m_78;
};

class Rva002D3609
{
public:
	bool rva002D3609() const;
private:
	char m_pad00[0x10];
	Rva002D3609Outer *m_10;
};

bool Rva002D3609::rva002D3609() const
{
	return m_10->m_78->m_bit0;
}

// --- 0x002D3993 (10B): sum of +0x14, +0x0C and +4.
class Rva002D3993
{
public:
	int rva002D3993() const;
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

int Rva002D3993::rva002D3993() const
{
	return m_14 + m_0C + m_04;
}

// --- 0x002D948E..0x002D94BE (16B each): percentages at +0x20..+0x2C as
// multipliers (1 + p/100).
class Rva002D948E
{
public:
	float rva002D948E() const;
	float rva002D949E() const;
	float rva002D94AE() const;
	float rva002D94BE() const;
private:
	char m_pad00[0x20];
	float m_20;
	float m_24;
	float m_28;
	float m_2C;
};

float Rva002D948E::rva002D948E() const
{
	return m_20 * 0.01f + 1.0f;
}

float Rva002D948E::rva002D949E() const
{
	return m_24 * 0.01f + 1.0f;
}

float Rva002D948E::rva002D94AE() const
{
	return m_28 * 0.01f + 1.0f;
}

float Rva002D948E::rva002D94BE() const
{
	return m_2C * 0.01f + 1.0f;
}

// --- 0x002D955A..0x002D95F1: a one-of state at +0x38 with its value at
// +0x34: setters for states 1, 3, 4 and 5 (only from that state or the
// unset state 6) and getters for states 3, 4 and 5.
class Rva002D955A
{
public:
	void rva002D955A(int value);
	void rva002D9583(int value);
	int rva002D959F() const;
	void rva002D95AC(int value);
	int rva002D95C8() const;
	void rva002D95D5(int value);
	int rva002D95F1() const;
private:
	char m_pad00[0x34];
	int m_value;
	int m_state;
};

void Rva002D955A::rva002D955A(int value)
{
	if (m_state == 1 || m_state == 6)
	{
		m_value = value;
		m_state = 1;
	}
}

void Rva002D955A::rva002D9583(int value)
{
	if (m_state == 3 || m_state == 6)
	{
		m_value = value;
		m_state = 3;
	}
}

int Rva002D955A::rva002D959F() const
{
	if (m_state == 3)
		return m_value;
	return 0;
}

void Rva002D955A::rva002D95AC(int value)
{
	if (m_state == 4 || m_state == 6)
	{
		m_value = value;
		m_state = 4;
	}
}

int Rva002D955A::rva002D95C8() const
{
	if (m_state == 4)
		return m_value;
	return 0;
}

void Rva002D955A::rva002D95D5(int value)
{
	if (m_state == 5 || m_state == 6)
	{
		m_value = value;
		m_state = 5;
	}
}

int Rva002D955A::rva002D95F1() const
{
	if (m_state == 5)
		return m_value;
	return 0;
}

// --- 0x002DABD7 (11B) and 0x002DABE2 (14B): the indexed word of the +0x64
// and +0xD4 arrays; 0x002DAC08 (14B) float setter +0x18; 0x002DB995 (10B)
// byte setter +0x6F.
class Rva002DABD7
{
public:
	int *rva002DABD7(int index);
	int *rva002DABE2(int index);
	void rva002DAC08(float value);
	void rva002DB995(bool value);
private:
	char m_pad00[0x18];
	float m_18;
	char m_pad1C[0x64 - 0x1C];
	int m_64[(0x6F - 0x64) / 4];
	char m_pad70[0x6F - 0x64 - ((0x6F - 0x64) / 4) * 4];
	bool m_6F;
	char m_pad70b[0xD4 - 0x70];
	int m_D4[1];
};

int *Rva002DABD7::rva002DABD7(int index)
{
	return &m_64[index];
}

int *Rva002DABD7::rva002DABE2(int index)
{
	return &m_D4[index];
}

void Rva002DABD7::rva002DAC08(float value)
{
	m_18 = value;
}

void Rva002DABD7::rva002DB995(bool value)
{
	m_6F = value;
}

// --- 0x002D644C (20B): the rowed 0x002D563D lookup returned by value.
struct Rva0046AC52Key;
struct Rva0046AC52Pair
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva0046AC52
{
public:
	Rva0046AC52Pair rva002D563D(const Rva0046AC52Key &key);	// 0x002D563D
	Rva0046AC52Pair rva002D644C(const Rva0046AC52Key &key);
};

Rva0046AC52Pair Rva0046AC52::rva002D644C(const Rva0046AC52Key &key)
{
	return rva002D563D(key);
}

#define GAP_V1(n) virtual void v##n();
#define GAP_V10(n) GAP_V1(n##0) GAP_V1(n##1) GAP_V1(n##2) GAP_V1(n##3) GAP_V1(n##4) GAP_V1(n##5) GAP_V1(n##6) GAP_V1(n##7) GAP_V1(n##8) GAP_V1(n##9)

// --- 0x002DBA07 (18B): opens a wide-named file through the rowed
// 0x00600676 with a zero third argument.
class File;

class FileSystem
{
public:
	File *rva00600676(const unsigned short *name, int mode, int flags);	// 0x00600676
	File *rva002DBA07(const unsigned short *name, int mode);
};

File *FileSystem::rva002DBA07(const unsigned short *name, int mode)
{
	return rva00600676(name, mode, 0);
}

// --- 0x002DBD64 (28B): assignment copying +4 and the +8 position (the
// vptr stays).
class Rva002DBD64
{
public:
	virtual ~Rva002DBD64();
	Rva002DBD64 &operator=(const Rva002DBD64 &other);
private:
	int m_04;
	Coord3D m_08;
};

Rva002DBD64 &Rva002DBD64::operator=(const Rva002DBD64 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	return *this;
}

// --- 0x002E060A (19B): the +0x24 position by value.
class Rva002E060A
{
public:
	Coord3D rva002E060A() const;
private:
	char m_pad00[0x24];
	Coord3D m_24;
};

Coord3D Rva002E060A::rva002E060A() const
{
	return m_24;
}

// --- 0x002E0F81 (16B): +0x298 plus the rowed 0x002E0C68 count.
class Rva002E0C68
{
public:
	int rva002E0C68();										// 0x002E0C68
	int rva002E0F81();
private:
	char m_pad000[0x298];
	int m_298;
};

int Rva002E0C68::rva002E0F81()
{
	int base = m_298;
	return rva002E0C68() + base;
}

// --- 0x002E37B1 (18B): the rowed 0x0030B7C2 test of a point against the
// +8 shape.
struct Rva0030B7C2Point;
class Rva0030B719Shape;
bool rva0030B7C2(const Rva0030B7C2Point *point, Rva0030B719Shape *shape);	// 0x0030B7C2

class Rva002E37B1
{
public:
	bool rva002E37B1(const Rva0030B7C2Point *point);
private:
	int m_00;
	int m_04;
	int m_shape;
};

bool Rva002E37B1::rva002E37B1(const Rva0030B7C2Point *point)
{
	return rva0030B7C2(point, (Rva0030B719Shape *)&m_shape);
}

// --- 0x002E3889 (22B, cdecl) and 0x002E3A67 (19B): more than two 8-byte
// records in the +8 vector.
struct Rva002E3889Record
{
	int m_00;
	int m_04;
};

struct Rva002E3889Vector
{
	char m_pad00[8];
	Rva002E3889Record *m_start;
	Rva002E3889Record *m_finish;
	bool rva002E3A67() const;
};

bool Rva002E3889(const Rva002E3889Vector *v)
{
	return v->m_finish - v->m_start > 2;
}

bool Rva002E3889Vector::rva002E3A67() const
{
	return m_finish - m_start > 2;
}

// --- 0x002E6B19 (23B): sets bit 0 of the +0x2C word of the +0 record;
// 0x002E6C60 (18B): bit 1 of it, 0 without a record.
struct Rva002E6B19Record
{
	char m_pad00[0x2C];
	unsigned int m_bit0 : 1;
	unsigned int m_bit1 : 1;
};

class Rva002E6B19
{
public:
	void rva002E6B19(unsigned char value);
	unsigned int rva002E6C60() const;
private:
	Rva002E6B19Record *m_record;
};

void Rva002E6B19::rva002E6B19(unsigned char value)
{
	m_record->m_bit0 = value != 0;
}

unsigned int Rva002E6B19::rva002E6C60() const
{
	if (m_record)
		return m_record->m_bit1;
	return 0;
}

// --- 0x002E6CBE (26B): constructor of a path record.
class Rva002E6CBE
{
public:
	Rva002E6CBE(int value);
private:
	int m_00;
	bool m_04;
	bool m_05;
	int m_08;
	bool m_0C;
};

Rva002E6CBE::Rva002E6CBE(int value) : m_00(value), m_04(false), m_05(false), m_08(-1), m_0C(false)
{
}

// --- 0x002E6DB8 (12B, cdecl): the indexed mask of the table at VA
// 0x00DBD33C.
extern unsigned int g_00DBD33C[16];

unsigned int Rva002E6DB8(int index)
{
	return g_00DBD33C[index];
}

// --- 0x002E73FB (25B): a pathfinding cell test over the cell's +0x0C flags
// word; only the cell argument is used.
struct Rva002E734ECell
{
	char m_pad00[0x0C];
	unsigned int m_flags;
};

class Rva002E734E
{
public:
	int rva002E73FB(int unused, const Rva002E734ECell *cell, int x, int y);
private:
	int m_00;
	int m_x;
	int m_y;
};

int Rva002E734E::rva002E73FB(int, const Rva002E734ECell *cell, int, int)
{
	return (cell->m_flags & 0x3F0) != 0x10;
}

// --- 0x002E7FC7 (19B, cdecl): the next index, wrapping 0x1FF to 0.
int Rva002E7FC7(int index)
{
	return index != 0x1FF ? index + 1 : 0;
}

// --- 0x002EEA5A, 0x002EEA72 (24B each): one node from the rowed pools at
// VA 0x00DBD4B0 and 0x00DBD4C8, none for a count above one.
class Rva002EB448
{
public:
	void *rva002EB448();									// 0x002EB448
};
class Rva002E8548;
extern Rva002E8548 g_IntKeyedTreeNodePool;
extern Rva002E8548 g_Va00DBD4C8;

class Rva002EEA5A
{
public:
	void *rva002EEA5A(unsigned int count, const void *hint);
	void *rva002EEA72(unsigned int count, const void *hint);
};

void *Rva002EEA5A::rva002EEA5A(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return ((Rva002EB448 *)&g_IntKeyedTreeNodePool)->rva002EB448();
}

void *Rva002EEA5A::rva002EEA72(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return ((Rva002EB448 *)&g_Va00DBD4C8)->rva002EB448();
}

// --- 0x002FD661 (10B): the +4 object's rowed 0x002CACD7 of this.
class Rva002CA9CA
{
public:
	float rva002CACD7(const void *other);					// 0x002CACD7
};

class Rva002FD661
{
public:
	float rva002FD661();
private:
	int m_00;
	Rva002CA9CA *m_04;
};

float Rva002FD661::rva002FD661()
{
	return m_04->rva002CACD7(this);
}

// --- 0x002FD7DC (19B): the +0x10 pathfinder's rowed 0x002F0F07, then
// ThePlayerList's slot 10.
class Pathfinder
{
public:
	void rva002F0F07();										// 0x002F0F07
};

class PlayerList;
extern PlayerList *ThePlayerList;

class Rva002FD7DCPlayerListView
{
public:
	GAP_V10(0)
	virtual void slot10();
};

class Rva002FD7DC
{
public:
	void rva002FD7DC();
private:
	char m_pad00[0x10];
	Pathfinder *m_10;
};

void Rva002FD7DC::rva002FD7DC()
{
	m_10->rva002F0F07();
	((Rva002FD7DCPlayerListView *)ThePlayerList)->slot10();
}

// --- 0x002FDEF1 (32B): the +0x104 word for indices 1..3, else the +0x110
// one.
class Rva002FDEF1
{
public:
	int rva002FDEF1(int index) const;
private:
	char m_pad000[0x104];
	int m_104[3];
	int m_110;
};

int Rva002FDEF1::rva002FDEF1(int index) const
{
	if (index >= 1 && index <= 3)
		return m_104[index];
	return m_110;
}
