// ?rva00213C6E@LivingWorldManager@@QAEXPAVRva00213D93Target@@@Z
// partial score=0.93 date=2026-10-13
// ?rva00213C6E@LivingWorldManager@@QAEXPAVRva00213D93Target@@@Z
// partial score=0.9 date=2026-10-12
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0021219E@LivingWorldManager@@QAEXPAVRva00213D93Target@@@Z, retail
// 0x0021219E..0x002122D4 (310 bytes, EH, ret 4): the object-list block of the
// LivingWorldManager's xfer (pinned name; called from 0x00213D93 with the
// xfer, ahead of 0x00213C6E). Version 1. Loading reads a count, and for each
// record xfers a temporary Rva003FD789 named "loadObject" (rowed ctor
// 0x003FD716, xfer 0x003FD6BD, dtor 0x003FD789) and, when an object of the
// record's name exists in the +0x24C list (rowed lookup 0x002120C2), moves it
// to the record's position (rowed 0x003FD690). Saving counts the list entries
// whose +0x11 flag is set, writes the count and xfers each of them through
// their slot 3. The list entries are Rva003FD789 records (name +0x1C, position
// +0x20, flag +0x11, per the rowed ctor and xfer). Identities beyond these
// addresses are not established.
#include <vector>
#include "ascii_string.h"

typedef int Int;

class Snapshot;

class Xfer
{
public:
	void Version1();								// 0x000053EE
	virtual ~Xfer();
	virtual bool isLoading();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);		// slot 12
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *value);	// slot 27
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual Xfer &xferInt(Int *value);				// slot 31
};

class Rva00213D93Target;

struct Coord
{
	float x;
	float y;
	float z;
};

class LivingWorldManager;

class Rva003FD789
{
public:
	Rva003FD789(const StringBase<char> &name);		// 0x003FD716
	virtual ~Rva003FD789();							// 0x003FD789
	virtual void slot01();
	virtual void slot02();
protected:
	virtual void xfer(Xfer *xfer);					// 0x003FD6BD, slot 3
	friend class LivingWorldManager;
public:
	unsigned char m_pad04[0x11 - 4];
	bool m_11;										// +0x11
	unsigned char m_pad12[0x1C - 0x12];
	AsciiString m_name;								// +0x1C
	Coord m_position;								// +0x20
};

struct Rva002120C2Entry;

class Rva002120A4
{
public:
	Rva002120C2Entry *rva002120C2(const AsciiString &name);	// 0x002120C2
};

class Rva003FD690
{
public:
	void rva003FD690(const Coord *position);		// 0x003FD690
};

// The named-object table at +0x204 (an AsciiString-keyed hash table: nodes
// {next +0, key +4, object +8}, element count +0x10), reached through its
// rowed find 0x00056F61 and first/next cursor helpers 0x00427195/0x00411084.
// The cursor type the rowed first-helper returns (AudioFileCacheDestructor.cpp).
struct AudioCacheCursor
{
	struct { void *first, *second; } s;
	AudioCacheCursor(void *a, void *b) { s.first = a; s.second = b; }
	AudioCacheCursor(const AudioCacheCursor &v) { s.first = v.s.first; s.second = v.s.second; }
};

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);			// 0x00056F61
};

class Rva000427195
{
public:
	AudioCacheCursor rva00427195();					// 0x00427195
};

class Rva000411084
{
public:
	void *next();										// 0x00411084
};

// A table object: a Snapshot with its name at +4.
class Rva00213C6EObject
{
public:
	void *m_vtbl;
	AsciiString m_name;								// +0x04
};

struct Rva00213C6ENode
{
	Rva00213C6ENode *m_next;
	AsciiString m_key;								// +0x04
	Rva00213C6EObject *m_object;					// +0x08

	Rva00213C6EObject *object() const { return m_object; }
};

// The object the load path creates for a name the table lacks (rowed ctor,
// whose parameter the ledger spells int; it receives the name's address).
class Rva00210EF1
{
public:
	Rva00210EF1(int name);							// 0x00210EF1
private:
	unsigned char m_bytes[0x34];
};

class LivingWorldManager
{
public:
	void rva0021219E(Rva00213D93Target *target);
	void rva00213C6E(Rva00213D93Target *target);

private:
	unsigned char m_pad000[0x204];
	unsigned char m_table[0x10];					// +0x204
	unsigned int m_tableCount;						// +0x214
	unsigned char m_pad218[0x24C - 0x218];
	_STL::vector<Rva003FD789 *> m_objects;			// +0x24C
};

void LivingWorldManager::rva0021219E(Rva00213D93Target *target)
{
	Xfer *xfer = (Xfer *)target;
	xfer->Version1();
	if (xfer->isLoading())
	{
		Int count;
		xfer->xferInt(&count);
		for (Int i = 0; i < count; ++i)
		{
			Rva003FD789 record(*(const StringBase<char> *)&AsciiString("loadObject"));
			record.xfer(xfer);
			Rva002120C2Entry *object = ((Rva002120A4 *)this)->rva002120C2(record.m_name);
			if (object)
				((Rva003FD690 *)object)->rva003FD690(&record.m_position);
		}
	}
	else
	{
		Int count = 0;
		unsigned int i;
		for (i = 0; i < m_objects.size(); ++i)
		{
			if (m_objects[i]->m_11)
				++count;
		}
		xfer->xferInt(&count);
		for (unsigned int j = 0; j < m_objects.size(); ++j)
		{
			Rva003FD789 *object = m_objects[j];
			if (object->m_11)
				object->xfer(xfer);
		}
	}
}

// ?rva00213C6E@LivingWorldManager@@QAEXPAVRva00213D93Target@@@Z, retail
// 0x00213C6E..0x00213D93 (293 bytes, EH, ret 4): the named-object block the
// same xfer (0x00213D93) runs next. Loading reads a count and, per entry, a
// name, then xfers the table's object of that name, or a new 0x34-byte
// Rva00210EF1 built from the name when the table has none. Saving writes the
// table's element count, then each object's name (+4) and the object.
void LivingWorldManager::rva00213C6E(Rva00213D93Target *target)
{
	Xfer *xfer = (Xfer *)target;
	if (xfer->isLoading())
	{
		Int count;
		xfer->xferInt(&count);
		for (Int i = 0; i < count; ++i)
		{
			AsciiString name;
			xfer->xferAsciiString(&name);
			Rva00213C6ENode *node = (Rva00213C6ENode *)((Rva00056F61 *)m_table)->rva00056F61(&name);
			if (node == 0)
				xfer->xferSnapshot((Snapshot *)new Rva00210EF1((int)&name));
			else
				xfer->xferSnapshot((Snapshot *)node->m_object);
		}
	}
	else
	{
		{
		Int count = m_tableCount;
		xfer->xferInt(&count);
		}
		volatile AudioCacheCursor it = ((Rva000427195 *)m_table)->rva00427195();
		Rva00213C6ENode *node;
		while ((node = (Rva00213C6ENode *)it.s.first) != 0)
		{
			{
			AsciiString name(node->object()->m_name);
			xfer->xferAsciiString(&name);
			}
			xfer->xferSnapshot((Snapshot *)node->object());
			((Rva000411084 *)&it)->next();
		}
	}
}
