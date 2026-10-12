// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no ledger row covered (third
// file; see GapBodiesSeat1A.cpp). Retail bytes establish every shape; owning
// classes are not recovered unless named, so each keeps an address-derived
// name and a view of only the members it touches. Callees are the ledger's
// existing rows under their current spellings.
#include "GameLogicObjectLookupView.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

extern GameLogic *TheGameLogic;

enum ObjectStatusTypes { OBJECT_STATUS_22 = 0x16 };

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool set);		// 0x0023DB0E
	void rva00346C53(ObjectStatusTypes status, bool set);	// 0x00346C53
	void rva0037710C(ObjectStatusTypes status);
};

// --- 0x0034BA7A (36B): -1 until TheGameLogic's frame reaches +0x20, then
// clears status 0x16 on the +0x18 record's +0x14 object and returns 0.
struct Rva0034BA7ARecord
{
	char m_pad00[0x14];
	Object *m_obj;
};

class Rva0034BA7A
{
public:
	int rva0034BA7A();
private:
	char m_pad00[0x18];
	Rva0034BA7ARecord *m_18;
	int m_1C;
	unsigned int m_20;
};

int Rva0034BA7A::rva0034BA7A()
{
	if (m_20 < TheGameLogic->getFrame())
		return -1;
	m_18->m_obj->setStatus(OBJECT_STATUS_22, false);
	return 0;
}

// --- 0x0037710C (14B): clears a status through the rowed 0x00346C53.
void Object::rva0037710C(ObjectStatusTypes status)
{
	rva00346C53(status, false);
}

// --- 0x003699BB (15B): the object with the +0x3C id.
class Rva003699BB
{
public:
	Object *rva003699BB() const;
private:
	char m_pad00[0x3C];
	ObjectID m_id;
};

Object *Rva003699BB::rva003699BB() const
{
	return TheGameLogic->findObjectByID(m_id);
}

// --- 0x00360C06 (25B): ORs seven words of another set into this one.
class Rva00360C06
{
public:
	void rva00360C06(const Rva00360C06 &other);
private:
	unsigned int m_words[7];
};

void Rva00360C06::rva00360C06(const Rva00360C06 &other)
{
	for (int i = 0; i < 7; ++i)
		m_words[i] |= other.m_words[i];
}

// --- 0x00360C64 (15B): the indexed 0x94-byte record at *(+0).
struct Rva00360C64Record
{
	char m_data[0x94];
};

class Rva00360C64
{
public:
	Rva00360C64Record *rva00360C64(int index);
private:
	Rva00360C64Record *m_records;
};

Rva00360C64Record *Rva00360C64::rva00360C64(int index)
{
	return &m_records[index];
}

// --- Setters: 0x00362461 (10B) byte +0x45; 0x003664F4 (12B) halfword +8;
// 0x003673AA (17B) float +0x530; 0x00373C81 (17B) float +0x358;
// 0x0037E179 (17B) float +0xCC; 0x003915EA/0x003915FB (17B) floats +0x280
// and +0x324; 0x0037ADA4 (18B) +0x0C capped at 100.
class Rva00362461
{
public:
	void rva00362461(bool value);
	void rva003664F4(short value);
	void rva003673AA(float value);
	void rva00373C81(float value);
	void rva0037E179(float value);
	void rva003915EA(float value);
	void rva003915FB(float value);
	void rva0037ADA4(int value);
private:
	char m_pad00[8];
	short m_08;
	char m_pad0A[0x0C - 0x0A];
	int m_0C;
	char m_pad10[0x45 - 0x10];
	bool m_45;
	char m_pad46[0xCC - 0x46];
	float m_CC;
	char m_padD0[0x280 - 0xD0];
	float m_280;
	char m_pad284[0x324 - 0x284];
	float m_324;
	char m_pad328[0x358 - 0x328];
	float m_358;
	char m_pad35C[0x530 - 0x35C];
	float m_530;
};

void Rva00362461::rva00362461(bool value)
{
	m_45 = value;
}

void Rva00362461::rva003664F4(short value)
{
	m_08 = value;
}

void Rva00362461::rva003673AA(float value)
{
	m_530 = value;
}

void Rva00362461::rva00373C81(float value)
{
	m_358 = value;
}

void Rva00362461::rva0037E179(float value)
{
	m_CC = value;
}

void Rva00362461::rva003915EA(float value)
{
	m_280 = value;
}

void Rva00362461::rva003915FB(float value)
{
	m_324 = value;
}

void Rva00362461::rva0037ADA4(int value)
{
	if (value >= 100)
		value = 100;
	m_0C = value;
}

// --- 0x003685C1 (14B): the rowed 0x0036748E for slot 6.
class Rva0036748E
{
public:
	void rva0036748E(int slot, bool value);					// 0x0036748E
	void rva003685C1(bool value);
};

void Rva0036748E::rva003685C1(bool value)
{
	rva0036748E(6, value);
}

// --- 0x0036CB77 (29B): constructor clearing a record (+0x14 to -1).
class Rva0036CB77
{
public:
	Rva0036CB77();
private:
	int m_00;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};

Rva0036CB77::Rva0036CB77() : m_00(0), m_04(false), m_08(0), m_0C(0), m_10(0), m_14(-1), m_18(0), m_1C(false)
{
}

// --- 0x00372DAB (13B): TheAI's pathfinder-side (+0x10) rowed 0x002E8FE5.
class AI;
extern AI *TheAI;

class Rva002E9042
{
public:
	void rva002E8FE5(void *arg);							// 0x002E8FE5
};

struct Rva00372DABAIView
{
	char m_pad00[0x10];
	Rva002E9042 *m_10;
};

class Rva00372DAB
{
public:
	void rva00372DAB(void *arg);
};

void Rva00372DAB::rva00372DAB(void *arg)
{
	((Rva00372DABAIView *)TheAI)->m_10->rva002E8FE5(arg);
}

// --- 0x00373F1C (16B): the current element of the +0 cursor (+0x0C past
// +4 is the end), or 0.
struct Rva00373F1CCursor
{
	int m_00;
	int *m_end;
	int m_08;
	int *m_cur;
};

class Rva00373F1C
{
public:
	int rva00373F1C() const;
private:
	Rva00373F1CCursor *m_cursor;
};

int Rva00373F1C::rva00373F1C() const
{
	Rva00373F1CCursor *cursor = m_cursor;
	if (cursor->m_cur == cursor->m_end)
		return 0;
	return *cursor->m_cur;
}

// --- 0x00375AE7 (16B): the rowed squared distance to the argument's +0x38
// point.
class BfmeVec3EJ;

class Gen_000E5A50
{
public:
	float bfmeDistanceSquared(const BfmeVec3EJ *point) const;	// 0x001E435D
	float rva00375AE7(const Gen_000E5A50 *other) const;
	char m_pad00[0x38];
	Coord3D m_38;
};

float Gen_000E5A50::rva00375AE7(const Gen_000E5A50 *other) const
{
	return bfmeDistanceSquared((const BfmeVec3EJ *)&other->m_38);
}

// --- 0x0037E87A (30B): sets the +0xCC float of the record the rowed
// 0x0037E421 finds.
struct Rva0037E87ARecord
{
	char m_pad00[0xCC];
	float m_CC;
};

class Rva0037E421
{
public:
	void *rva0037E421(int id);								// 0x0037E421
	void rva0037E87A(int id, float value);
};

void Rva0037E421::rva0037E87A(int id, float value)
{
	Rva0037E87ARecord *record = (Rva0037E87ARecord *)rva0037E421(id);
	if (record)
		record->m_CC = value;
}

// --- 0x00380AE6, 0x00380AF9 (19B each): wrapper constructors handing the
// address of their word to the rowed ref-counted constructors 0x0023E8D8 /
// 0x00380AB1.
class Rva0023E8D8
{
public:
	Rva0023E8D8(void *p);									// 0x0023E8D8
private:
	void *m_impl;
};

class Rva00380AB1
{
public:
	Rva00380AB1(void *p);									// 0x00380AB1
private:
	void *m_impl;
};

class Rva00380AE6 : public Rva0023E8D8
{
public:
	Rva00380AE6(int value);
};

Rva00380AE6::Rva00380AE6(int value) : Rva0023E8D8(&value)
{
}

class Rva00380AF9 : public Rva00380AB1
{
public:
	Rva00380AF9(int value);
};

Rva00380AF9::Rva00380AF9(int value) : Rva00380AB1(&value)
{
}

// --- 0x00381440 (18B, cdecl): the +0x684 member of the object at VA
// 0x00E03354, or null.
extern int g_Va00A03354;

void *Rva00381440()
{
	char *p = (char *)g_Va00A03354;
	return p ? p + 0x684 : 0;
}

// --- 0x00381D1A, 0x0038888E (19B each): a 16-byte block at +0xCC / +0x148
// with its size.
class Rva00381D1A
{
public:
	void *rva00381D1A(int *size);
	void *rva0038888E(int *size);
private:
	char m_pad000[0xCC];
	char m_CC[0x148 - 0xCC];
	char m_148[16];
};

void *Rva00381D1A::rva00381D1A(int *size)
{
	*size = 16;
	return m_CC;
}

void *Rva00381D1A::rva0038888E(int *size)
{
	*size = 16;
	return m_148;
}

// --- 0x003821D7 (11B): assigns the +0x90 member (rowed operator=).
class Rva00235A37
{
public:
	Rva00235A37 &operator=(const Rva00235A37 &other);		// 0x00235A37
};

class Rva003821D7
{
public:
	Rva00235A37 &rva003821D7(const Rva00235A37 &value);
private:
	char m_pad00[0x90];
	Rva00235A37 m_90;
};

Rva00235A37 &Rva003821D7::rva003821D7(const Rva00235A37 &value)
{
	return m_90 = value;
}

// --- 0x00388823 (20B): any of four slots set; 0x00388837 (14B): the
// rowed CRC of the 16 bytes.
unsigned __cdecl ComputeCRC(const unsigned char *data, unsigned size, unsigned crc);	// 0x003EC8F7

class Rva00388823
{
public:
	bool rva00388823() const;
	unsigned rva00388837() const;
private:
	int m_slots[4];
};

bool Rva00388823::rva00388823() const
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_slots[i] != 0)
			return true;
	}
	return false;
}

unsigned Rva00388823::rva00388837() const
{
	return ComputeCRC((const unsigned char *)this, 16, 0);
}

// --- 0x00388BFA (18B): forwards to GameSpy's peerSetQuietMode; the
// receiver is unused.
typedef void *PEER;
typedef int PEERBool;
extern "C" void peerSetQuietMode(PEER peer, PEERBool quiet);

class Rva00388BFA
{
public:
	void rva00388BFA(PEER peer, PEERBool quiet);
};

void Rva00388BFA::rva00388BFA(PEER peer, PEERBool quiet)
{
	peerSetQuietMode(peer, quiet);
}

// --- 0x00388CFC (19B): copy constructor of a flag and a word;
// 0x00388D9D (11B): +0x10 equals +0.
class Rva00388CFC
{
public:
	Rva00388CFC(const Rva00388CFC &other);
private:
	bool m_00;
	int m_04;
};

Rva00388CFC::Rva00388CFC(const Rva00388CFC &other) : m_00(other.m_00), m_04(other.m_04)
{
}

class Rva00388D9D
{
public:
	int rva00388D9D() const;
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

int Rva00388D9D::rva00388D9D() const
{
	return m_10 == m_00;
}

// --- 0x0039165D (10B): byte setter +0x1D; 0x003959A3 (18B): the pointer
// count of the +0x80 vector; 0x0039ABF2 (13B): +0x18 with -1 read as 0;
// 0x0039B6CD (33B): three words at +0xE0.
struct Rva003959A3Vector
{
	void **m_start;
	void **m_finish;
};

static __forceinline int Rva003959A3Count(const Rva003959A3Vector *v) { return v->m_finish - v->m_start; }

class Rva0039165D
{
public:
	void rva0039165D(bool value);
	int rva003959A3() const;
	int rva0039ABF2() const;
	void rva0039B6CD(int a, int b, int c);
private:
	char m_pad00[0x18];
	int m_18;
	char m_pad1C[0x1D - 0x1C];
	bool m_1D;
	char m_pad1E[0x80 - 0x1E];
	Rva003959A3Vector m_80;
	char m_pad88[0xE0 - 0x88];
	int m_E0;
	int m_E4;
	int m_E8;
};

void Rva0039165D::rva0039165D(bool value)
{
	m_1D = value;
}

int Rva0039165D::rva003959A3() const
{
	return Rva003959A3Count(&m_80);
}

int Rva0039165D::rva0039ABF2() const
{
	int value = m_18;
	return value != -1 ? value : 0;
}

void Rva0039165D::rva0039B6CD(int a, int b, int c)
{
	m_E0 = a;
	m_E4 = b;
	m_E8 = c;
}

// --- 0x003A44DF (14B) and 0x003A450C (15B): count of and the indexed
// 0xA0-byte record of the vector at +0.
struct Rva003A44DFRecord
{
	char m_data[0xA0];
};

class Rva003A44DF
{
public:
	int rva003A44DF() const;
	Rva003A44DFRecord *rva003A450C(int index);
private:
	Rva003A44DFRecord *m_start;
	Rva003A44DFRecord *m_finish;
};

int Rva003A44DF::rva003A44DF() const
{
	return m_finish - m_start;
}

Rva003A44DFRecord *Rva003A44DF::rva003A450C(int index)
{
	return &m_start[index];
}

// --- 0x003B0C9F (10B): adds to +8; 0x003B2534 (12B): copies a word to
// +0x24; 0x003B8B7B (10B): the +0x10-indexed word of the +0x14 array.
class Rva003B0C9F
{
public:
	void rva003B0C9F(int value);
	void rva003B2534(const int *value);
	int rva003B8B7B() const;
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int *m_14;
	char m_pad18[0x24 - 0x18];
	int m_24;
};

void Rva003B0C9F::rva003B0C9F(int value)
{
	m_08 += value;
}

void Rva003B0C9F::rva003B2534(const int *value)
{
	m_24 = *value;
}

int Rva003B0C9F::rva003B8B7B() const
{
	return m_14[m_10];
}

// --- 0x003B0E93 (15B, cdecl): bit 7 of the +0x108 byte.
struct Rva003B0E93Record
{
	char m_pad000[0x108];
	unsigned char m_108;
};

int Rva003B0E93(const Rva003B0E93Record *rec)
{
	return rec->m_108 >> 7;
}

// --- 0x003B24DB (23B): latches +0 or clears +4 by the flag, then stores it
// at +1.
class Rva003B24DB
{
public:
	void rva003B24DB(bool value);
private:
	bool m_00;
	bool m_01;
	int m_04;
};

void Rva003B24DB::rva003B24DB(bool value)
{
	if (value)
		m_00 = true;
	else
		m_04 = 0;
	m_01 = value;
}

// --- 0x003B260F (31B): the predecessor (next at +4) of a node in the +0x30
// list, null for the head or when absent.
struct Rva003B260FNode
{
	int m_00;
	Rva003B260FNode *m_next;
};

class Rva003B260F
{
public:
	Rva003B260FNode *rva003B260F(Rva003B260FNode *node) const;
private:
	char m_pad00[0x30];
	Rva003B260FNode *m_head;
};

Rva003B260FNode *Rva003B260F::rva003B260F(Rva003B260FNode *node) const
{
	Rva003B260FNode *cur = m_head;
	if (cur == node)
		return 0;
	while (cur)
	{
		if (cur->m_next == node)
			return cur;
		cur = cur->m_next;
	}
	return 0;
}

// --- 0x003E3BAE (13B): bit 2 of the +0x438 byte.
class Rva003E3BAE
{
public:
	bool rva003E3BAE() const;
private:
	char m_pad000[0x438];
	unsigned char m_438;
};

bool Rva003E3BAE::rva003E3BAE() const
{
	return (m_438 >> 2) & 1;
}

// --- 0x003E4B74 (15B): the second argument's +8 count is not positive;
// 0x003EFCC0 (17B): stores the second word through an optional pointer.
struct Rva003E4B74Arg
{
	int m_00;
	int m_04;
	int m_08;
};

class Rva003E4B74
{
public:
	bool rva003E4B74(int unused, const Rva003E4B74Arg *arg);
	void rva003EFCC0(int *out, int value);
};

bool Rva003E4B74::rva003E4B74(int, const Rva003E4B74Arg *arg)
{
	return arg->m_08 <= 0;
}

void Rva003E4B74::rva003EFCC0(int *out, int value)
{
	if (out)
		*out = value;
}

// --- 0x003EF5E8 (19B): zeroes the +0x1C position; 0x003EFE63 (15B): clears
// +0x17C and the +0x1A3 flag.
class Rva003EF5E8
{
public:
	void rva003EF5E8();
	void rva003EFE63();
private:
	char m_pad000[0x1C];
	float m_1C;
	float m_20;
	float m_24;
	char m_pad028[0x17C - 0x28];
	int m_17C;
	char m_pad180[0x1A3 - 0x180];
	bool m_1A3;
};

void Rva003EF5E8::rva003EF5E8()
{
	m_1C = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
}

void Rva003EF5E8::rva003EFE63()
{
	m_17C = 0;
	m_1A3 = false;
}

// --- 0x003F0038 (11B): +0 equals +4; 0x003F0043 (14B): flag +0x34 set and
// +0x20 non-zero; 0x003F0051 (14B): +0x20 non-zero and flag +0x34 clear.
class Rva003F0038
{
public:
	int rva003F0038() const;
	int rva003F0043() const;
	int rva003F0051() const;
private:
	int m_00;
	int m_04;
	char m_pad08[0x20 - 8];
	int m_20;
	char m_pad24[0x34 - 0x24];
	bool m_34;
};

int Rva003F0038::rva003F0038() const
{
	return m_00 == m_04;
}

int Rva003F0038::rva003F0043() const
{
	return m_34 && m_20 != 0;
}

int Rva003F0038::rva003F0051() const
{
	return m_20 != 0 && !m_34;
}

// --- 0x003F4332 (16B) and 0x003F452B (13B): the first word of / the
// indexed 0x30-byte record at *(+4); 0x003F449C (13B): the indexed 0x68-byte
// record at *(+0x10); 0x003F4627 (13B): the indexed 0x1C-byte record at
// *(+0x18).
struct Rva003F4332Record
{
	int m_00;
	char m_pad04[0x30 - 4];
};

struct Rva003F449CRecord
{
	char m_data[0x68];
};

struct Rva003F4627Record
{
	char m_data[0x1C];
};

class Rva003F4332
{
public:
	int rva003F4332(int index) const;
	Rva003F4332Record *rva003F452B(int index);
	Rva003F449CRecord *rva003F449C(int index);
	Rva003F4627Record *rva003F4627(int index);
private:
	int m_00;
	Rva003F4332Record *m_04;
	int m_08;
	int m_0C;
	Rva003F449CRecord *m_10;
	int m_14;
	Rva003F4627Record *m_18;
};

int Rva003F4332::rva003F4332(int index) const
{
	return m_04[index].m_00;
}

Rva003F4332Record *Rva003F4332::rva003F452B(int index)
{
	return &m_04[index];
}

Rva003F449CRecord *Rva003F4332::rva003F449C(int index)
{
	return &m_10[index];
}

Rva003F4627Record *Rva003F4332::rva003F4627(int index)
{
	return &m_18[index];
}

// --- 0x003F2371 (17B), 0x003F2382 (18B): the rowed hooks applied to the
// argument twice (the first widened from a halfword); 0x003F3126 (13B): the
// second hook on the +4 word twice.
int Rva003F1DD5Hook(int a, int b);							// 0x003F1DD5
int Rva003F1E2EHook(int a, int b);							// 0x003F1E2E

class Rva003F2371
{
public:
	int rva003F2371(short value);
	int rva003F2382(int value);
	int rva003F3126() const;
private:
	int m_00;
	int m_04;
};

int Rva003F2371::rva003F2371(short value)
{
	return Rva003F1DD5Hook(value, value);
}

int Rva003F2371::rva003F2382(int value)
{
	return Rva003F1E2EHook(value, value);
}

int Rva003F2371::rva003F3126() const
{
	return Rva003F1E2EHook(m_04, m_04);
}

// --- 0x003FD18F (10B): byte setter +0x51; 0x003FE1C8 (19B): stores the
// +0x5C flag and, when set, runs the rowed 0x003FDFFB.
class Rva003FDEAD
{
public:
	void rva003FDFFB();										// 0x003FDFFB
	void rva003FD18F(bool value);
	void rva003FE1C8(bool value);
private:
	char m_pad00[0x51];
	bool m_51;
	char m_pad52[0x5C - 0x52];
	bool m_5C;
};

void Rva003FDEAD::rva003FD18F(bool value)
{
	m_51 = value;
}

void Rva003FDEAD::rva003FE1C8(bool value)
{
	m_5C = value;
	if (value)
		rva003FDFFB();
}

// --- 0x004047CE (11B): the indexed float at +0x50; 0x0040CA56 (11B): +0x2C
// kept only when 1.
class Rva004047CE
{
public:
	float rva004047CE(int index) const;
	void rva0040CA56();
private:
	char m_pad00[0x2C];
	int m_2C;
	char m_pad30[0x50 - 0x30];
	float m_50[1];
};

float Rva004047CE::rva004047CE(int index) const
{
	return m_50[index];
}

void Rva004047CE::rva0040CA56()
{
	if (m_2C != 1)
		m_2C = 0;
}

// --- 0x005AB7BA (10B): byte setter +0x28; 0x005DB8E4 (19B): adds 1.0 to
// the +8 float; 0x005E3ED3 (15B): the +0x10 record's +8 word by value.
struct Rva005E3ED3Record
{
	int m_00;
	int m_04;
	int m_08;
};

struct Rva005E3ED3Word
{
	Rva005E3ED3Word(int v) : m_value(v) {}
	int m_value;
};

class Rva005AB7BA
{
public:
	void rva005AB7BA(bool value);
	void rva005DB8E4();
	Rva005E3ED3Word rva005E3ED3() const;
private:
	int m_00;
	int m_04;
	float m_08;
	int m_0C;
	Rva005E3ED3Record *m_10;
	char m_pad14[0x28 - 0x14];
	bool m_28;
};

void Rva005AB7BA::rva005AB7BA(bool value)
{
	m_28 = value;
}

void Rva005AB7BA::rva005DB8E4()
{
	m_08 += 1.0f;
}

Rva005E3ED3Word Rva005AB7BA::rva005E3ED3() const
{
	return Rva005E3ED3Word(m_10->m_08);
}

// --- 0x005D3C1F (12B): clears the +0x32 flag, then the rowed 0x005D3AF2;
// the word argument is unused.
class Rva005D3AF2
{
public:
	void rva005D3AF2();										// 0x005D3AF2
	void rva005D3C1F(int unused);
private:
	char m_pad00[0x32];
	bool m_32;
};

void Rva005D3AF2::rva005D3C1F(int)
{
	m_32 = false;
	rva005D3AF2();
}

// --- 0x005D7745 (17B) and 0x005D7756 (16B): set / read the +0x18 flag of
// the indexed entry of the +0x10 pointer array.
struct Rva005D7745Entry
{
	char m_pad00[0x18];
	bool m_18;
};

class Rva005D7745
{
public:
	void rva005D7745(int index);
	bool rva005D7756(int index) const;
private:
	char m_pad00[0x10];
	Rva005D7745Entry **m_10;
};

void Rva005D7745::rva005D7745(int index)
{
	m_10[index]->m_18 = true;
}

bool Rva005D7745::rva005D7756(int index) const
{
	return m_10[index]->m_18;
}

// --- 0x005DDDF0 (17B): hands this pair's two words to the argument's rowed
// 0x005DDBAB.
class Rva005DDBAB
{
public:
	void rva005DDBAB(int a, int b);							// 0x005DDBAB
};

class Rva005DDDF0
{
public:
	void rva005DDDF0(Rva005DDBAB *target);
private:
	int m_00;
	int m_04;
};

void Rva005DDDF0::rva005DDDF0(Rva005DDBAB *target)
{
	target->rva005DDBAB(m_00, m_04);
}

// --- 0x005E0D27, 0x005E0D31 (10B each): the +0 object's slots 5 and 6;
// the word argument is unused.
class Rva005E0D27Target
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void slot5();
	virtual void slot6();
};

class Rva005E0D27
{
public:
	void rva005E0D27(int value);
	void rva005E0D31(int value);
private:
	Rva005E0D27Target *m_target;
};

void Rva005E0D27::rva005E0D27(int)
{
	m_target->slot5();
}

void Rva005E0D27::rva005E0D31(int)
{
	m_target->slot6();
}

// --- 0x005E2D66 (14B): the indexed flag of the +0x30 array of the +4
// record.
struct Rva005E2D66Record
{
	char m_pad00[0x30];
	bool m_flags[1];
};

class Rva005E2D66
{
public:
	bool rva005E2D66(int index) const;
private:
	int m_00;
	Rva005E2D66Record *m_04;
};

bool Rva005E2D66::rva005E2D66(int index) const
{
	return m_04->m_flags[index];
}
