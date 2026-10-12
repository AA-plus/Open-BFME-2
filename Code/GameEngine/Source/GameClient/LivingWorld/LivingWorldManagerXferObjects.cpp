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
	virtual void slot12();
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
	virtual void slot27();
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

class LivingWorldManager
{
public:
	void rva0021219E(Rva00213D93Target *target);

private:
	unsigned char m_pad000[0x24C];
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
