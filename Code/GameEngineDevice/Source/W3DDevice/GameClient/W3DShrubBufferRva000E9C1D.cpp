// W3DShrubBuffer constructor, retail 0x000E9C1D (194B). The vtable is
// 0x00BCECB8 (RTTI names W3DShrubBuffer) and the layout is established by the
// landed W3DShrubBuffer* siblings: base Rva000E6AC0 (ctor rowed 0x000E6AC0),
// 2000 records of 0xA0 at +0x1958, count +0x4FB58, ObjectCreationList-style
// 12-byte member at +0x4FB60 (ctor pinned as ??0Rva0052413E@@QAE@XZ at
// 0x001F81BF), 64 types of 0x5C at +0x4FB70. The two member arrays get their
// ??_H / ??_L vector-constructor-iterator calls from the element ctor/dtor
// declarations, which is why this source only needs the member types.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc

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
	Rva0052413E();
	~Rva0052413E();
private:
	unsigned char m_storage[12];
};

class Rva000E9C1DRecord
{
public:
	Rva000E9C1DRecord();
private:
	unsigned char m_storage[0xA0];
};

class Rva000E9C1DType
{
public:
	Rva000E9C1DType();
	~Rva000E9C1DType();
private:
	unsigned char m_storage[0x5C];
};

class Rva000E7016
{
public:
	void rva000E7016();
};

class Rva00066A9ASub
{
public:
	void tailB();
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva00DFE758Holder
{
	char m_pad[0x20];
	int m_20;
};

class W3DShrubBuffer : public Rva000E6AC0
{
public:
	W3DShrubBuffer();
private:
	unsigned char m_pad5c0[0x1958 - 0x5C0];
	Rva000E9C1DRecord m_records[2000];	// +0x1958
	int m_count;				// +0x4FB58
	unsigned char m_4fb5c, m_4fb5d, m_4fb5e, m_4fb5f;
	Rva0052413E m_objects;			// +0x4FB60
	unsigned char m_4fb6c, m_4fb6d, m_4fb6e, m_4fb6f;
	Rva000E9C1DType m_types[64];		// +0x4FB70
	int m_numTypes;				// +0x51270
	int m_51274;
	int m_51278;
	int m_5127c;
};

W3DShrubBuffer::W3DShrubBuffer()
	: m_count(0)
{
	m_5127c = 0;
	m_4fb6c = 0;
	m_4fb5e = 0;
	for (int i = 0; i < 64; ++i)
		((int *)&m_types[i])[0] = 0;
	((Rva000E7016 *)this)->rva000E7016();
	m_4fb6c = 1;
	m_51278 = (*(Rva00DFE758Holder **)&TheWritableGlobalData)->m_20;
	((Rva00066A9ASub *)this)->tailB();
}
