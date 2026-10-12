// cl: /O1 /G7 /arch:SSE /GX- /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Small GameEngine bodies from .text gaps no ledger row covered (each begins
// after its neighbour's padding or return and ends in its own ret). Retail
// bytes establish every shape below; the owning classes are not recovered, so
// each keeps an address-derived name and a view of only the members it
// touches. Callees are the ledger's existing rows under their current
// spellings.
#include "GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "RTS/XYDistanceCallView.h"

extern GameLogic *TheGameLogic;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// --- 0x00203582 (19B): adds the argument to the float at +0x48.
class Rva00203582
{
public:
	void rva00203582(float delta);
private:
	char m_pad00[0x48];
	float m_48;
};

void Rva00203582::rva00203582(float delta)
{
	m_48 += delta;
}

// --- 0x00203671 (23B): stores a non-negative argument into
// TheWritableGlobalData's word at +0xAC8; the receiver is unused.
struct Rva00203671GlobalDataView
{
	char m_pad000[0xAC8];
	int m_AC8;
};

class Rva00203671
{
public:
	void rva00203671(int value);
};

void Rva00203671::rva00203671(int value)
{
	if (value >= 0)
		((Rva00203671GlobalDataView *)TheWritableGlobalData)->m_AC8 = value;
}

// --- 0x00203E65 (17B): 1 when TheGameLogic->rva001DCD1C() is false, else 0
// (sibling of the rowed 0x00203688/0x00203693 wrappers).
class Rva00203E65
{
public:
	int rva00203E65();
};

int Rva00203E65::rva00203E65()
{
	return !TheGameLogic->rva001DCD1C();
}

// --- 0x00205A1B (16B): returns by value a pair {0, &this[+0x0C]}.
struct Rva00205A1BPair
{
	Rva00205A1BPair(void *p) : m_00(0), m_04(p) {}
	int m_00;
	void *m_04;
};

class Rva00205A1B
{
public:
	Rva00205A1BPair rva00205A1B();
private:
	char m_pad00[0x0C];
	int m_0C;
};

Rva00205A1BPair Rva00205A1B::rva00205A1B()
{
	return Rva00205A1BPair(&m_0C);
}

// --- 0x00210EAC (19B): returns a zero float pair by value; both word
// arguments and the receiver are unused.
struct Rva00210EACCoord2D
{
	Rva00210EACCoord2D(float ax, float ay) : x(ax), y(ay) {}
	float x;
	float y;
};

class Rva00210EAC
{
public:
	Rva00210EACCoord2D rva00210EAC(int a, int b);
};

Rva00210EACCoord2D Rva00210EAC::rva00210EAC(int, int)
{
	return Rva00210EACCoord2D(0.0f, 0.0f);
}

// --- 0x00215E5F (16B): 1 when the argument's first word equals this one's.
class Rva00215E5F
{
public:
	int rva00215E5F(const Rva00215E5F *other);
private:
	int m_00;
};

int Rva00215E5F::rva00215E5F(const Rva00215E5F *other)
{
	return other->m_00 == m_00;
}

// --- 0x00215E87 (18B): the index of the first null of two slots, else 2.
class Rva00215E87
{
public:
	unsigned int rva00215E87();
private:
	void *m_slots[2];
};

unsigned int Rva00215E87::rva00215E87()
{
	unsigned int i;
	for (i = 0; i < 2; ++i)
	{
		if (m_slots[i] == 0)
			return i;
	}
	return 2;
}

// --- 0x0021917A (18B): cdecl equality of two pointed-to words.
int Rva0021917A(const int *a, const int *b)
{
	return *b == *a;
}

// --- 0x0021982A (16B): the halfword at +4 of the node the first word points
// at, or 0 without a node.
struct Rva0021982ANode
{
	int m_00;
	unsigned short m_04;
};

class Rva0021982A
{
public:
	int rva0021982A();
private:
	Rva0021982ANode **m_node;
};

int Rva0021982A::rva0021982A()
{
	Rva0021982ANode *node = *m_node;
	if (node)
		return node->m_04;
	return 0;
}

// --- 0x002224DE (32B): false past the fourteenth 0x28-byte record at +0xF0,
// else the inverse of that record's second flag bit.
struct Rva002224DERecord
{
	unsigned char m_flag0 : 1;
	unsigned char m_flag1 : 1;
	char m_pad01[0x27];
};

class Rva002224DE
{
public:
	bool rva002224DE(unsigned int index);
private:
	char m_pad00[0xF0];
	Rva002224DERecord m_records[14];
};

bool Rva002224DE::rva002224DE(unsigned int index)
{
	if (index >= 14)
		return false;
	return !m_records[index].m_flag1;
}

// --- 0x002226A2 (28B): constructor from a flag and an eight-byte pair.
struct Rva002226A2Pair
{
	int m_00;
	int m_04;
};

class Rva002226A2
{
public:
	Rva002226A2(const bool &flag, const Rva002226A2Pair &pair);
private:
	bool m_00;
	Rva002226A2Pair m_04;
};

Rva002226A2::Rva002226A2(const bool &flag, const Rva002226A2Pair &pair) : m_00(flag), m_04(pair)
{
}

// --- 0x00225A81 (18B): copies an eight-byte pair to +0x38.
class Rva00225A81
{
public:
	void rva00225A81(const Rva002226A2Pair &pair);
private:
	char m_pad00[0x38];
	Rva002226A2Pair m_38;
};

void Rva00225A81::rva00225A81(const Rva002226A2Pair &pair)
{
	m_38 = pair;
}

// --- 0x0022CF6E, 0x0022CF9F (18B each): the rowed timing hooks applied to
// the argument twice, as the rowed 0x0022D189 setter calls the first.
int Rva0022CB5CHook(int a, int b);
int Rva0022CC0EHook(int a, int b);

class Rva0022CF6E
{
public:
	int rva0022CF6E(int value);
	int rva0022CF9F(int value);
};

int Rva0022CF6E::rva0022CF6E(int value)
{
	return Rva0022CB5CHook(value, value);
}

int Rva0022CF6E::rva0022CF9F(int value)
{
	return Rva0022CC0EHook(value, value);
}

// --- 0x0022D979 (20B): sets the timing value from the pointed word through
// the rowed 0x0022D189 setter and returns this.
class Rva00077710Value
{
public:
	void rva0022D189(int value);
	Rva00077710Value &rva0022D979(const int &value);
	int m_a;
	int m_b;
};

Rva00077710Value &Rva00077710Value::rva0022D979(const int &value)
{
	rva0022D189(value);
	return *this;
}

// --- 0x0023262C (23B): whether the halfword at +6 of the indexed 8-byte
// record at +0x18 shares a bit with the mask.
struct Rva0023262CRecord
{
	char m_pad00[6];
	unsigned short m_bits;
};

class Rva0023262C
{
public:
	int rva0023262C(unsigned char index, int mask);
private:
	char m_pad00[0x18];
	Rva0023262CRecord m_records[1];
};

int Rva0023262C::rva0023262C(unsigned char index, int mask)
{
	return (m_records[index].m_bits & mask) != 0;
}

// --- 0x0023426A (30B): constructor from an eight-byte pair and a halfword;
// 0x002342C5 (16B): copies the first halfword out and returns 1.
class Rva0023426A
{
public:
	Rva0023426A(const Rva002226A2Pair &pair, const short &value);
	int rva002342C5(short *out) const;
private:
	Rva002226A2Pair m_00;
	short m_08;
};

Rva0023426A::Rva0023426A(const Rva002226A2Pair &pair, const short &value) : m_00(pair), m_08(value)
{
}

int Rva0023426A::rva002342C5(short *out) const
{
	*out = *(const short *)&m_00;
	return 1;
}

// --- 0x00239B11 (24B): one node from the freelist pool at VA 0x00DBA5E0
// (rowed pop), none for a count above one; the second word is unused.
class FreelistPool
{
public:
	void *pop();
};
extern FreelistPool g_freelistPool00DBA5E0;

class Rva00239B11
{
public:
	void *rva00239B11(unsigned int count, const void *hint);
};

void *Rva00239B11::rva00239B11(unsigned int count, const void *)
{
	if (count > 1)
		return 0;
	return g_freelistPool00DBA5E0.pop();
}

// --- 0x0023DB48 (16B): latches +0x38 into an unset +0x40 and returns it.
class Rva0023DB48
{
public:
	int rva0023DB48();
private:
	char m_pad00[0x38];
	int m_38;
	int m_3C;
	int m_40;
};

int Rva0023DB48::rva0023DB48()
{
	if (m_40 == 0)
		m_40 = m_38;
	return m_40;
}

// --- 0x0023E887 (28B): constructor copying a word and building the string
// at +4 from the source's text.
struct Rva0023E887Source
{
	int m_00;
	const char *m_text;
};

class Rva0023E887
{
public:
	Rva0023E887(const Rva0023E887Source &source);
private:
	int m_00;
	AsciiString m_text;
};

Rva0023E887::Rva0023E887(const Rva0023E887Source &source) : m_00(source.m_00), m_text(source.m_text)
{
}

// --- 0x00254628 (34B) and 0x002546EB (34B): module-data field parsers,
// each the rowed base table 0x004CE29D at offset 8 then its own table (VA
// 0x00BF247C, VA 0x00BF2534); 0x0025464A (52B) and 0x0025470D (52B): their
// INI factories over 0x11C-byte data built by the rowed constructors
// 0x0025460F and 0x002546D2 (the latter folds with RadarUpgradeModuleData's).
struct FieldParse;
class ModuleData;

class MultiIniFieldParse
{
public:
	void add(const FieldParse *table, unsigned int offset);	// 0x0002BC6E
};

class INI
{
public:
	void initFromINIMultiProc(void *what, void (*proc)(MultiIniFieldParse &p));	// 0x0002DEB5
};

int Rva004CE29DGet(void);
extern const FieldParse s_Rva00254628FieldParse[];			// VA 0x00BF247C
extern const FieldParse s_Rva002546EBFieldParse[];			// VA 0x00BF2534

class Rva0025460F
{
public:
	Rva0025460F();
private:
	char m_pad[0x11C];
};

class RadarUpgradeModuleData
{
public:
	RadarUpgradeModuleData();
private:
	unsigned char m_pad[0x11C];
};

class Rva00254628ModuleData
{
public:
	static void rva00254628(MultiIniFieldParse &p);
	static ModuleData *rva0025464A(INI *ini);
};

void Rva00254628ModuleData::rva00254628(MultiIniFieldParse &p)
{
	p.add((const FieldParse *)Rva004CE29DGet(), 8);
	p.add(s_Rva00254628FieldParse, 0);
}

ModuleData *Rva00254628ModuleData::rva0025464A(INI *ini)
{
	Rva0025460F *data = new Rva0025460F;
	if (ini)
		ini->initFromINIMultiProc(data, rva00254628);
	return (ModuleData *)data;
}

class Rva002546EBModuleData
{
public:
	static void rva002546EB(MultiIniFieldParse &p);
	static ModuleData *rva0025470D(INI *ini);
};

void Rva002546EBModuleData::rva002546EB(MultiIniFieldParse &p)
{
	p.add((const FieldParse *)Rva004CE29DGet(), 8);
	p.add(s_Rva002546EBFieldParse, 0);
}

ModuleData *Rva002546EBModuleData::rva0025470D(INI *ini)
{
	RadarUpgradeModuleData *data = new RadarUpgradeModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, rva002546EB);
	return (ModuleData *)data;
}

// --- 0x0025F342 (67B): swaps a marker into the +0x80 list in place of the
// one with the same name, returning the unlinked one (or null); 0x0025F3AE
// (69B): unlinks and deletes the marker with the argument's name.
class CameraMarker
{
public:
	~CameraMarker();										// 0x0029D7C2
	CameraMarker *m_next;
	AsciiString m_name;
};

class Rva0025F342
{
public:
	CameraMarker *rva0025F342(CameraMarker *marker);
	void rva0025F3AE(const CameraMarker *marker);
private:
	char m_pad00[0x80];
	CameraMarker *m_markers;
};

CameraMarker *Rva0025F342::rva0025F342(CameraMarker *marker)
{
	CameraMarker *old = 0;
	for (CameraMarker **link = &m_markers; *link; link = &(*link)->m_next)
	{
		CameraMarker *cur = *link;
		if (cur->m_name.compare(marker->m_name) == 0)
		{
			old = *link;
			*link = marker;
			marker->m_next = old->m_next;
			old->m_next = 0;
			break;
		}
	}
	return old;
}

void Rva0025F342::rva0025F3AE(const CameraMarker *marker)
{
	for (CameraMarker **link = &m_markers; *link; link = &(*link)->m_next)
	{
		CameraMarker *cur = *link;
		if (cur->m_name.compare(marker->m_name) == 0)
		{
			CameraMarker *old = *link;
			*link = old->m_next;
			delete old;
			break;
		}
	}
}

// --- 0x002602C1 (25B): constructor from a unicode string and a word.
class Rva002602C1
{
public:
	Rva002602C1(const UnicodeString &text, int value);
private:
	UnicodeString m_text;
	int m_04;
};

Rva002602C1::Rva002602C1(const UnicodeString &text, int value) : m_text(text), m_04(value)
{
}

// --- 0x00260DCF (13B): bit 3 of the byte at +0x438.
class Rva00260DCF
{
public:
	bool rva00260DCF() const;
private:
	char m_pad000[0x438];
	unsigned char m_438;
};

bool Rva00260DCF::rva00260DCF() const
{
	return (m_438 >> 3) & 1;
}

// --- 0x00260DDC (17B) and 0x0026223A (17B): the +4 word of the record at
// +0x04 / +0x50, or 999999 without one.
struct Rva00260DDCRecord
{
	int m_00;
	int m_04;
};

class Rva00260DDC
{
public:
	int rva00260DDC() const;
private:
	int m_00;
	Rva00260DDCRecord *m_record;
};

int Rva00260DDC::rva00260DDC() const
{
	if (m_record)
		return m_record->m_04;
	return 999999;
}

class Rva0026223A
{
public:
	int rva0026223A() const;
	int rva00262254() const;
private:
	char m_pad00[0x50];
	Rva00260DDCRecord *m_record;
	int m_54;
};

int Rva0026223A::rva0026223A() const
{
	if (m_record)
		return m_record->m_04;
	return 999999;
}

// 0x00262254 (15B): a record is present and +0x54 is -1.
int Rva0026223A::rva00262254() const
{
	return m_record != 0 && m_54 == -1;
}

// --- 0x00262263 (14B): byte +8 set and byte +0x0A clear.
class Rva00262263
{
public:
	int rva00262263() const;
private:
	char m_pad00[8];
	bool m_08;
	bool m_09;
	bool m_0A;
};

int Rva00262263::rva00262263() const
{
	return m_08 && !m_0A;
}

// --- 0x00260E0D (17B): 1 when the object is not on an airborne locomotor.
enum ObjectStatusTypes { OBJECT_STATUS_4 = 4 };

class Object
{
public:
	bool isUsingAirborneLocomotor() const;					// 0x0028B81E
	int rva0028B511() const;								// 0x0028B511
	bool rva00292FAC() const;								// 0x00292FAC
	bool testStatus(ObjectStatusTypes status) const;		// 0x0004E536
	void rva0028D611(Object *other, int a, int b);
	int m_pad00[0x74 / 4];
	int m_74;												// +0x74
	char m_pad78[0x244 - 0x78];
	void **m_modules;										// +0x244, null-terminated
	char m_pad248[0x484 - 0x248];
	int m_484;												// +0x484
};

class Rva00260E0D
{
public:
	int rva00260E0D(const Object *obj);
};

int Rva00260E0D::rva00260E0D(const Object *obj)
{
	return !obj->isUsingAirborneLocomotor();
}

// --- 0x00260F3B (21B): the argument's +0x304 word equals this +8 word.
struct Rva00260F3BOther
{
	char m_pad000[0x304];
	int m_304;
};

class Rva00260F3B
{
public:
	int rva00260F3B(const Rva00260F3BOther *other);
private:
	int m_00;
	int m_04;
	int m_08;
};

int Rva00260F3B::rva00260F3B(const Rva00260F3BOther *other)
{
	return other->m_304 == m_08;
}

// --- 0x00261750 (30B): whether the +8 template's rowed isEquivalentTo the
// argument's +4 template agrees with the +0x0C flag; 0x0026176E (34B): the
// same over the rowed 0x00376A62 test of that template's +0x64 name.
class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *tmpl) const;	// 0x0033BB04
};

class Rva00376A62
{
public:
	bool rva00376A62(const StringBase<char> &val);			// 0x00376A62
};

struct Rva00261750Template
{
	char m_pad00[0x64];
	AsciiString m_name;
};

struct Rva00261750Arg
{
	int m_00;
	const void *m_04;
};

class Rva00261750
{
public:
	int rva00261750(const Rva00261750Arg *arg);
	int rva0026176E(const Rva00261750Arg *arg);
private:
	int m_00;
	int m_04;
	void *m_08;
	bool m_0C;
};

int Rva00261750::rva00261750(const Rva00261750Arg *arg)
{
	return ((ThingTemplate *)m_08)->isEquivalentTo((const ThingTemplate *)arg->m_04) == m_0C;
}

int Rva00261750::rva0026176E(const Rva00261750Arg *arg)
{
	return ((Rva00376A62 *)m_08)->rva00376A62(*(const StringBase<char> *)&((const Rva00261750Template *)arg->m_04)->m_name) == m_0C;
}

// --- 0x002619AE (19B): the argument's rowed BitFlags<69>::test of this
// +0x108.
template <int N> class BitFlags
{
public:
	bool test(const void *other) const;
};

class Rva002619AE
{
public:
	bool rva002619AE(const BitFlags<69> *flags);
private:
	char m_pad000[0x108];
	int m_108;
};

bool Rva002619AE::rva002619AE(const BitFlags<69> *flags)
{
	return flags->test(&m_108);
}

// --- 0x002628E0 (25B): the +0x224 owner's rowed removeFromMatching of the
// argument's +0x74 word and the second argument.
class Rva00331CBAVectorOwner
{
public:
	void removeFromMatching(int entry, int key);			// 0x00331CBA
};

struct Rva002628E0Arg
{
	char m_pad00[0x74];
	int m_74;
};

class Rva002628E0
{
public:
	void rva002628E0(const Rva002628E0Arg *arg, int key);
private:
	char m_pad000[0x224];
	Rva00331CBAVectorOwner m_owner;
};

void Rva002628E0::rva002628E0(const Rva002628E0Arg *arg, int key)
{
	m_owner.removeFromMatching(arg->m_74, key);
}

// --- 0x00262B7D (44B): TheAI's pathfinder (+0x10) validates a position for
// the +8 object with its rowed 0x0028B511 answer and this +0x1DC word.
struct Coord3D;
class Pathfinder
{
public:
	bool IsValidMovementPositionForObject(const Coord3D *pos, int a, int b, const Object *obj);	// 0x002E909F
};

class AI;
extern AI *TheAI;

struct Rva00262B7DAIView
{
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};

class Rva00262B7D
{
public:
	bool rva00262B7D(const Coord3D *pos);
private:
	char m_pad000[8];
	Object *m_obj;
	char m_pad00C[0x1DC - 0x0C];
	int m_1DC;
};

bool Rva00262B7D::rva00262B7D(const Coord3D *pos)
{
	Rva00262B7DAIView *ai = (Rva00262B7DAIView *)TheAI;
	Object *obj = m_obj;
	int value = m_1DC;
	Pathfinder *pathfinder = ai->m_pathfinder;
	return pathfinder->IsValidMovementPositionForObject(pos, obj->rva0028B511(), value, obj);
}

// --- 0x002636E6 (16B): the rowed squared distance to the argument's +0x38
// point.
class Rva002636E6Arg
{
public:
	char m_pad00[0x38];
	Rva000CBA20Point *m_point;
};

class Rva002636E6 : public Rva000CBA20
{
public:
	float rva002636E6(const Rva002636E6Arg *arg);
};

float Rva002636E6::rva002636E6(const Rva002636E6Arg *arg)
{
	return distSq((const Rva000CBA20Point *)&arg->m_point);
}

// --- 0x002638CC, 0x002638E4 (14B each): Locomotor flag setters for flags 6
// and 3 through the rowed private setFlag.
class Locomotor
{
public:
	enum LocoFlag { LOCO_FLAG_3 = 3, LOCO_FLAG_6 = 6 };
	void rva002638CC(bool value);
	void rva002638E4(bool value);
private:
	void setFlag(LocoFlag flag, bool value);				// 0x001E3459
};

void Locomotor::rva002638CC(bool value)
{
	setFlag(LOCO_FLAG_6, value);
}

void Locomotor::rva002638E4(bool value)
{
	setFlag(LOCO_FLAG_3, value);
}

// --- 0x00265681 (16B): returns by value the word the +4 handle's pointer
// addresses.
struct Rva00265681Word
{
	Rva00265681Word(int v) : m_value(v) {}
	int m_value;
};

class Rva00265681
{
public:
	Rva00265681Word rva00265681();
private:
	int m_00;
	int **m_handle;
};

Rva00265681Word Rva00265681::rva00265681()
{
	return Rva00265681Word(**m_handle);
}

// --- 0x0026891F (27B): constructor storing two words, then the rowed
// 0x002654D6 reset.
class Rva002654D6
{
public:
	Rva002654D6(int a, int b);
	void rva002654D6();										// 0x002654D6
private:
	int m_00;
	int m_04;
};

Rva002654D6::Rva002654D6(int a, int b) : m_00(a), m_04(b)
{
	rva002654D6();
}

// --- 0x00268B0C (20B, cdecl): whether the string differs from the text.
int Rva00268B0C(const AsciiString *str, const char *text)
{
	return str->compare(text) != 0;
}

// --- 0x0026FCF9 (14B): the indexed word of the array at +0x148.
class Rva0026FCF9
{
public:
	int rva0026FCF9(int index) const;
private:
	char m_pad000[0x148];
	int m_words[1];
};

int Rva0026FCF9::rva0026FCF9(int index) const
{
	return m_words[index];
}

// --- 0x0027175F (26B): 1 when the +0xFC object answers the rowed
// 0x00292FAC test.
class Rva0027175F
{
public:
	int rva0027175F() const;
private:
	char m_pad00[0xFC];
	Object *m_obj;
};

int Rva0027175F::rva0027175F() const
{
	if (m_obj && m_obj->rva00292FAC())
		return 1;
	return 0;
}

// --- 0x0027229B (15B): bit 20 of +0x98 clear.
class Rva0027229B
{
public:
	bool rva0027229B() const;
private:
	char m_pad00[0x98];
	unsigned int m_98;
};

bool Rva0027229B::rva0027229B() const
{
	bool set = (m_98 >> 20) & 1;
	return !set;
}

struct GapVoidVector
{
	void **m_start;
	void **m_finish;
	void **m_end;
};

static __forceinline int GapVoidVectorCount(const GapVoidVector *v) { return v->m_finish - v->m_start; }

// Dummy virtual slots for call views; only the slot index matters.
#define GAP_V1(n) virtual void v##n();
#define GAP_V10(n) GAP_V1(n##0) GAP_V1(n##1) GAP_V1(n##2) GAP_V1(n##3) GAP_V1(n##4) GAP_V1(n##5) GAP_V1(n##6) GAP_V1(n##7) GAP_V1(n##8) GAP_V1(n##9)

// --- 0x00272366 (45B): the +0x14C holder's object's slot-42 answer, when
// there is one, handles the three arguments in its slot 0; else false.
class Rva00272366Handler
{
public:
	virtual bool handle(int a, int b, int c);
};

class Rva00272366Target
{
public:
	GAP_V10(0) GAP_V10(1) GAP_V10(2) GAP_V10(3)
	GAP_V1(40) GAP_V1(41)
	virtual Rva00272366Handler *getHandler();				// slot 42
	GAP_V1(43) GAP_V1(44) GAP_V1(45) GAP_V1(46) GAP_V1(47) GAP_V1(48) GAP_V1(49)
	GAP_V1(50) GAP_V1(51) GAP_V1(52) GAP_V1(53)
	virtual void slot54(int a, int b);						// slot 54
};

class Rva00272366Holder
{
public:
	Rva00272366Target *get() const { return m_target; }
private:
	Rva00272366Target *m_target;
};

class Rva00272366
{
public:
	bool rva00272366(int a, int b, int c);
private:
	__forceinline Rva00272366Handler *handler() const
	{
		if (m_holder)
		{
			Rva00272366Target *target = m_holder->get();
			if (target)
				return target->getHandler();
		}
		return 0;
	}
	char m_pad000[0x14C];
	Rva00272366Holder *m_holder;
};

bool Rva00272366::rva00272366(int a, int b, int c)
{
	Rva00272366Handler *h = handler();
	if (h)
		return h->handle(a, b, c);
	return false;
}


// --- 0x002785D6 (37B): changes the +0x447 flag, then on set the rowed
// 0x002783F6(0), on clear the rowed 0x002743D7; 0x0027862C (24B): changes the
// +0x449 flag, then the rowed 0x002784EB.
class Rva002783F6Host
{
public:
	void rva002783F6(int value);							// 0x002783F6
};

class Drawable
{
public:
	void rva002743D7();										// 0x002743D7
	void rva002784EB();										// 0x002784EB
	void rva002785D6(bool value);
	void rva0027862C(bool value);
private:
	char m_pad000[0x447];
	bool m_447;
	bool m_448;
	bool m_449;
};

void Drawable::rva002785D6(bool value)
{
	if (m_447 != value)
	{
		m_447 = value;
		if (value)
			((Rva002783F6Host *)this)->rva002783F6(0);
		else
			rva002743D7();
	}
}

void Drawable::rva0027862C(bool value)
{
	if (m_449 != value)
	{
		m_449 = value;
		rva002784EB();
	}
}

// --- 0x0027C226 (10B, cdecl): sets the word at VA 0x00DBB708.
extern int g_Va00DBB708;

void Rva0027C226(int value)
{
	g_Va00DBB708 = value;
}

// --- 0x0027C280 (36B): stores three floats at +0x1C.
class Rva0027C280
{
public:
	void rva0027C280(float x, float y, float z);
private:
	char m_pad00[0x1C];
	float m_1C;
	float m_20;
	float m_24;
};

void Rva0027C280::rva0027C280(float x, float y, float z)
{
	m_1C = x;
	m_20 = y;
	m_24 = z;
}

// --- 0x0028565F (19B): calls the cdecl function pointer at +0x9C;
// 0x002856B7 (15B): the argument is at most +0x3C.
class Rva0028565F
{
public:
	int rva0028565F(int a, int b);
	bool rva002856B7(int value) const;
private:
	char m_pad00[0x3C];
	int m_3C;
	char m_pad40[0x9C - 0x40];
	int (*m_9C)(int a, int b);
};

int Rva0028565F::rva0028565F(int a, int b)
{
	return m_9C(a, b);
}

bool Rva0028565F::rva002856B7(int value) const
{
	return value <= m_3C;
}

// --- 0x00285760 (13B): drops a reference (+4) and frees through the rowed
// 0x0020DAE0 at zero.
void Rva0020DAE0(void *p);

class Rva00285760
{
public:
	void rva00285760();
private:
	int m_00;
	int m_refs;
};

void Rva00285760::rva00285760()
{
	if (--m_refs == 0)
		Rva0020DAE0(this);
}

// --- 0x00285A0A (12B, cdecl): the argument's slot 11 with 0.
class Rva00285A0ATarget
{
public:
	GAP_V10(0) GAP_V1(10)
	virtual void slot11(int value);
};

void Rva00285A0A(Rva00285A0ATarget *target)
{
	target->slot11(0);
}

// --- 0x00285A16, 0x0028878C (16B each): the rowed comparisons of the first
// argument with the second; the receiver is unused.
class Rva00285672
{
public:
	bool rva00285672(const Rva00285672 &other) const;		// 0x00285672
};

class ExperienceLevel
{
public:
	bool rva00288621(const ExperienceLevel &other) const;	// 0x00288621
};

class Rva00285A16
{
public:
	bool rva00285A16(const Rva00285672 *a, const Rva00285672 &b);
	bool rva0028878C(const ExperienceLevel *a, const ExperienceLevel &b);
};

bool Rva00285A16::rva00285A16(const Rva00285672 *a, const Rva00285672 &b)
{
	return a->rva00285672(b);
}

bool Rva00285A16::rva0028878C(const ExperienceLevel *a, const ExperienceLevel &b)
{
	return a->rva00288621(b);
}

// --- 0x0028667F (20B): the rowed 0x00286214 find returned by value.
struct Rva00286214Node;
struct Rva0028667FIterator
{
	Rva0028667FIterator(Rva00286214Node *node) : m_node(node) {}
	Rva00286214Node *m_node;
};

class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);	// 0x00286214
	Rva0028667FIterator rva0028667F(const Rva00285672 *key);
};

Rva0028667FIterator Rva00286214::rva0028667F(const Rva00285672 *key)
{
	return Rva0028667FIterator(rva00286214(key));
}

// --- 0x002895AF (11B): erases every marker through the rowed erase.
class CameraMarkerVec
{
public:
	CameraMarker *erase(CameraMarker *first, CameraMarker *last);	// 0x0048D042
	void rva002895AF();
	CameraMarker *m_start;
	CameraMarker *m_finish;
	CameraMarker *m_end;
};

void CameraMarkerVec::rva002895AF()
{
	erase(m_start, m_finish);
}

// --- Object-region leaves: 0x0028A638 (12B) +0x464 set; 0x0028A644 (12B)
// bit 1 of +0x438; float setters 0x0028A6B6 (+0x444), 0x0028A7C7 (+0x200),
// 0x0028BB8D (+0x1B8); 0x0028A7B7 (16B) byte +1 equals the argument;
// 0x0028A84B (23B) bit test of +0x30; 0x0028B975 (15B) resets +0x490/+0x48C;
// 0x0028C8CD (18B) and 0x0028F2E6 (18B) pointer-vector counts at +0x234 and
// +0x4A4.
class Rva0028A638
{
public:
	bool rva0028A638() const;
	bool rva0028A644() const;
	void rva0028A6B6(float value);
	void rva0028A7C7(float value);
	void rva0028BB8D(float value);
	void rva0028B975();
	int rva0028C8CD() const;
	int rva0028F2E6() const;
private:
	char m_pad000[0x1B8];
	float m_1B8;
	char m_pad1BC[0x200 - 0x1BC];
	float m_200;
	char m_pad204[0x234 - 0x204];
	GapVoidVector m_234;
	char m_pad240[0x438 - 0x240];
	unsigned char m_438;
	char m_pad439[0x444 - 0x439];
	float m_444;
	char m_pad448[0x464 - 0x448];
	int m_464;
	char m_pad468[0x48C - 0x468];
	bool m_48C;
	char m_pad48D[0x490 - 0x48D];
	int m_490;
	char m_pad494[0x4A4 - 0x494];
	GapVoidVector m_4A4;
};

bool Rva0028A638::rva0028A638() const
{
	return m_464 != 0;
}

bool Rva0028A638::rva0028A644() const
{
	return (m_438 >> 1) & 1;
}

void Rva0028A638::rva0028A6B6(float value)
{
	m_444 = value;
}

void Rva0028A638::rva0028A7C7(float value)
{
	m_200 = value;
}

void Rva0028A638::rva0028BB8D(float value)
{
	m_1B8 = value;
}

void Rva0028A638::rva0028B975()
{
	m_490 = -1;
	m_48C = false;
}

int Rva0028A638::rva0028C8CD() const
{
	return GapVoidVectorCount(&m_234);
}

int Rva0028A638::rva0028F2E6() const
{
	return GapVoidVectorCount(&m_4A4);
}

class Rva0028A7B7
{
public:
	int rva0028A7B7(int value) const;
	int rva0028A84B(int bit) const;
private:
	unsigned char m_00;
	unsigned char m_01;
	char m_pad02[0x30 - 2];
	int m_30;
};

int Rva0028A7B7::rva0028A7B7(int value) const
{
	return m_01 == value;
}

int Rva0028A7B7::rva0028A84B(int bit) const
{
	return ((1 << bit) & m_30) != 0;
}

// --- 0x0028BC29 (18B): the +0x23C field's rowed flag, false without one.
class Rva003B8ACFCmpBoolField
{
public:
	bool get() const;										// 0x003B8ACF
};

class Rva0028BC29
{
public:
	bool rva0028BC29() const;
private:
	char m_pad000[0x23C];
	Rva003B8ACFCmpBoolField *m_field;
};

bool Rva0028BC29::rva0028BC29() const
{
	if (m_field == 0)
		return false;
	return m_field->get();
}

// --- 0x0028C59F (14B): zeroes twenty bytes of this through the CRT memset
// thunk 0x006291AE.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Rva0028C59F
{
public:
	void rva0028C59F();
private:
	int m_words[5];
};

void Rva0028C59F::rva0028C59F()
{
	ji_006291ae(this, 0, 0x14);
}

// --- 0x0028D611 (111B): unless the other object shares this one's +0x484
// relation (against its +0x74 id) or both carry one, each module whose
// +0x0C interface (slot 1) yields a handler passes it the three arguments,
// stopping when this object has status 4.
class Rva0028D611Handler
{
public:
	virtual void handle(Object *other, int a, int b);
};

class Rva0028D611Interface
{
public:
	virtual void s0();
	virtual Rva0028D611Handler *getHandler();
};

void Object::rva0028D611(Object *other, int a, int b)
{
	if (other == 0 || m_484 == other->m_74)
		return;
	if (other->m_484 != 0 && m_74 != 0)
		return;
	for (void **module = m_modules; *module; ++module)
	{
		Rva0028D611Handler *handler = ((Rva0028D611Interface *)((char *)*module + 0x0C))->getHandler();
		if (handler)
		{
			if (testStatus(OBJECT_STATUS_4))
				return;
			handler->handle(other, a, b);
		}
	}
}

// --- 0x00282206 (12B): pops the last 8-byte element, running its rowed
// destructor 0x0027EA49.
class Rva0027EA49
{
public:
	~Rva0027EA49();											// 0x0027EA49
private:
	int m_00;
	int m_04;
};

class Rva00282206
{
public:
	void rva00282206();
private:
	Rva0027EA49 *m_start;
	Rva0027EA49 *m_finish;
};

void Rva00282206::rva00282206()
{
	--m_finish;
	m_finish->~Rva0027EA49();
}

// --- 0x00282794 (11B): reserves the +0x578 module-data vector;
// 0x0028A665 (11B): the +0x330 material pass's texture for a stage;
// 0x0028C8BD (11B): ORs a bitset into +0x284.
class ModuleData;
class TextureClass;
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector
	{
	public:
		void reserve(unsigned int n);
	private:
		T *m_start;
		T *m_finish;
		T *m_end;
	};
	template <int N> struct _Base_bitset
	{
		void _M_do_or(const _Base_bitset &other);
		unsigned int m_words[N / 32];
	};
}

class MaterialPassClass
{
public:
	TextureClass *Peek_Texture(int stage) const;			// 0x002C7469
};

class Rva00282794
{
public:
	void rva00282794(unsigned int n);
	TextureClass *rva0028A665(int stage) const;
	void rva0028C8BD(const _STL::_Base_bitset<32> &bits);
private:
	char m_pad000[0x284];
	_STL::_Base_bitset<32> m_284;
	char m_pad288[0x330 - 0x288];
	MaterialPassClass m_330;
	char m_pad331[0x578 - 0x331];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_578;
};

void Rva00282794::rva00282794(unsigned int n)
{
	m_578.reserve(n);
}

TextureClass *Rva00282794::rva0028A665(int stage) const
{
	return m_330.Peek_Texture(stage);
}

void Rva00282794::rva0028C8BD(const _STL::_Base_bitset<32> &bits)
{
	m_284._M_do_or(bits);
}
