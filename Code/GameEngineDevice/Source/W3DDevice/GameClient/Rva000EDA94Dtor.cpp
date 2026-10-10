// cl: /O1 /MD /EHsc
// ??1Rva000EDA94@@UAE@XZ, retail 0x000EDA94..0x000EDB39 (165 bytes, EH):
// the destructor of a tree-buffer subclass (opaque pin of its scalar
// deleting destructor; table 0x00BCEEA4) over the rowed base Rva000E6AC0
// (destructor 0x000E6C6F). It releases and clears the reference held by
// each of its 64 tree types at +0x44558, then its parts die: the 64 tree
// types (rowed ??1Rva00735D80TreeType 0x000EC6E1 through the eh vector
// destructor iterator), the +0x44548 wrapper (inline destructor running the
// rowed 0x0008B470; out-of-line copy 0x0008B4CD for the unwind map), the
// 1200 0xE8-byte records at +0x5C0 (element destructor is the shared bare
// return 0x000B3FD0), and the base. Identities beyond the rowed callees
// are not established.
class Rva000E6AC0
{
public:
	virtual ~Rva000E6AC0();
private:
	unsigned char m_pad04[0x5C0 - 4];
};

struct Rva000EDA94Record
{
	~Rva000EDA94Record();
	unsigned char m_data[0xE8];
};

class Rva0008B470
{
public:
	~Rva0008B470();
private:
	void *m_data[4];
};

struct Rva0008B4CD
{
	~Rva0008B4CD() {}
	Rva0008B470 m_vector;
};

class Rva000EDA94Ref
{
public:
	virtual void Delete_This();
	void Release_Ref() { if (--m_refs == 0) Delete_This(); }
private:
	int m_refs;
};

class Rva00735D80TreeType
{
public:
	~Rva00735D80TreeType();
	Rva000EDA94Ref *m_ref;
private:
	unsigned char m_pad04[0x5C - 4];
};

class Rva000EDA94 : public Rva000E6AC0
{
public:
	virtual ~Rva000EDA94();
private:
	Rva000EDA94Record m_records[0x4B0];		// +0x5C0
	unsigned char m_pad44540[0x44548 - 0x44540];
	Rva0008B4CD m_member44548;			// +0x44548
	Rva00735D80TreeType m_types[0x40];		// +0x44558
};

Rva000EDA94::~Rva000EDA94()
{
	for (int i = 0; i < 0x40; ++i)
	{
		if (m_types[i].m_ref)
		{
			m_types[i].m_ref->Release_Ref();
			m_types[i].m_ref = 0;
		}
	}
}
