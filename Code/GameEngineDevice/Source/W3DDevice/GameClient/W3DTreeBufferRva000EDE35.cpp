// W3DTreeBuffer constructor, retail 0x000EDE35 (210B). The vtable 0x00BCEEA4
// names the class; the layout is established by the landed W3DTreeBuffer*
// siblings: base Rva000E6AC0 (ctor rowed 0x000E6AC0), 1200 records of 0xE8 at
// +0x5C0 (ctor rowed as ??0Rva000EB08C@@QAE@XZ at 0x000EB27F), dirty byte
// +0x44545, ObjectCreationList-style 12-byte member at +0x44548 (ctor pinned
// as ??0Rva0052413E@@QAE@XZ at 0x001F81BF), 64 types of 0x5C at +0x44558
// (ctor ??0Rva000EC67F@@QAE@XZ at 0x000EC67F, dtor at 0x000EC6E1). The two
// member arrays get their ??_L vector-constructor-iterator calls from the
// element ctor/dtor declarations.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include <string.h>

class Rva000E6AC0Base
{
public:
	Rva000E6AC0Base() {}
	virtual ~Rva000E6AC0Base() {}
};

class Rva000E6AC0 : public Rva000E6AC0Base
{
public:
	Rva000E6AC0();
	virtual ~Rva000E6AC0();
private:
	unsigned char m_storage[0x5C0 - 4];
};

class Rva0052413E
{
public:
	Rva0052413E() throw();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

class Rva000EB08C
{
public:
	Rva000EB08C();
	~Rva000EB08C();
private:
	unsigned char m_storage[0xE8];
};

class Rva000EC67F
{
public:
	Rva000EC67F();
	~Rva000EC67F();
private:
	unsigned char m_storage[0x5C];
};

class Rva000EA24D
{
public:
	void rva000EA24D();
};

class Rva00066A9ASub
{
public:
	void tailA();
};

class W3DTreeBuffer : public Rva000E6AC0
{
public:
	W3DTreeBuffer();
private:
	Rva000EB08C m_records[1200];		// +0x5C0
	int m_count;				// +0x44540
	unsigned char m_44544;
	unsigned char m_44545;
	unsigned char m_44546;
	unsigned char m_44547;
	Rva0052413E m_objects;			// +0x44548
	unsigned char m_44554;
	unsigned char m_44555;
	unsigned char m_44556;
	unsigned char m_44557;
	Rva000EC67F m_types[64];		// +0x44558
	int m_typeCount;			// +0x45C58
	int m_45c5c;
	int m_45c60;
	unsigned char m_45c64;
};

W3DTreeBuffer::W3DTreeBuffer()
{
	m_44554 = 0;
	m_44546 = 0;
	for (int i = 0; i < 64; ++i)
		((int *)&m_types[i])[0] = 0;
	((Rva000EA24D *)this)->rva000EA24D();
	m_44554 = 1;
	memset(&m_records[0], 0, sizeof(m_records));
	m_45c60 = 1;
	m_45c64 = 0;
	((Rva00066A9ASub *)this)->tailA();
}
