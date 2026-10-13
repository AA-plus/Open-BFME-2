// ?rva005E5920@Rva005E5920@@QAEHPAXH@Z
// partial score=0.65 date=2026-10-13
// cl: /O2 /DNDEBUG /MD
// ?rva005E5884@Rva005E5884@@QAEHPAXH@Z @0x005E5884 26B.
// Helper-then-member forwarder tail-called from 0x005E5920 when RAMFile write fails.
// Evidence: thiscall ret 8 two ignored stack args; cmp [this+0x40] then [this+0x38]
// null check sharing single or eax minus 1; virtual slot 3 no args returning int.
class Rva005E5884Second
{
public:
	virtual int v0() throw();
	virtual int v1() throw();
	virtual int v2() throw();
	virtual int v3() throw();
};
class Rva005E5884
{
public:
	int rva005E5884(void *a1, int a2);
private:
	char m_pad[0x38];
	Rva005E5884Second *m_38;
	int m_3C;
	int m_40;
};
int Rva005E5884::rva005E5884(void *a1, int a2)
{
	if (m_40 == 0)
	{
		Rva005E5884Second *p = m_38;
		if (p != 0)
			return p->v3();
	}
	return -1;
}

// ?rva005E5920@Rva005E5920@@QAEHPAXH@Z @0x005E5920 34B trial.
// RAMFile::write (rowed 0x00574473) on this; on -1 tail to m_8's rowed
// rva005E5884 with forwarded args. Evidence: thiscall ret 8, cmp -1,
// qualified direct call, jmp tail (see Rva0010BA61Wrappers idiom).
class RAMFile
{
public:
	virtual int write(const void *a, int b);
};
class Rva005E5920 : public RAMFile
{
public:
	int rva005E5920(void *a, int b);
private:
	char m_pad04[4];
	Rva005E5884 *m_8;
};
int Rva005E5920::rva005E5920(void *a, int b)
{
	int r = RAMFile::write(a, b);
	if (r == -1)
		return m_8->rva005E5884(a, b);
	return r;
}
