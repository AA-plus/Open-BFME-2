// ??1Rva003B35B1@@UAE@XZ
// partial score=0.95 date=2026-10-13
// ??1Rva003B35B1@@UAE@XZ
// partial score=0.95 date=2026-10-01
// ??1Rva003B35B1@@UAE@XZ
// cl: /O1 /MD /EHsc
// ??1Rva003B35B1@@UAE@XZ retail 0x003B35B1 177B. Vtable 0x0081F424, base
// Snapshot (vtable 0x007BB554 restored last). Retail's unwind map: base at
// +0, narrow strings at +4/+8/+0xC, a 16-byte record with a string at +0xC
// placed at +0x10 (dtor folds with GeometryRecord's 0x0004F82B), string at
// +0x44. Owned pointers at +0x30 and +0x34[2] are released through slot 0
// with flag 0, then operator delete (also for null).
// NEAR MISS: EH states, frame and first release exact; the loop body reads
// `cmp [edi],0; je; mov ecx,[edi]` where retail loads ecx first and tests
// it (1 byte longer). Local-variable, if/else, ::delete and inline-helper
// bodies move the counter into ebx instead.
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

class Rva003B35B1Owned
{
public:
	virtual void *v0(int x);
};
void __cdecl operator delete(void *p);

struct Rva003B35B1Record
{
	int m_00;
	int m_04;
	int m_08;
	StringBase<char> m_0C;
};

class Rva003B35B1 : public Snapshot
{
public:
	virtual ~Rva003B35B1();
private:
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	Rva003B35B1Record m_10;
	char m_pad20[0x10];
	Rva003B35B1Owned *m_30;
	Rva003B35B1Owned *m_34[2];
	char m_pad3C[0x08];
	StringBase<char> m_44;
};

Rva003B35B1::~Rva003B35B1()
{
	::operator delete(m_30 ? m_30->v0(0) : 0);
	for (int i = 0; i < 2; ++i)
		::operator delete(m_34[i] ? m_34[i]->v0(0) : 0);
}
