// cl: /MD
//
// ?rva0006ED36@Rva0006ED36@@QAEXPAX@Z @0x0006ED36 (31B).
// Stores arg at +0x814 then virtual slot 12 on member at +0x108 then clears.
// Evidence: 7 callers in 0x87D42 family; ecx+0x814 store plus ecx+0x108
// vtable call at +0x30 plus and [esi] 0 clear; ret 4 one void* arg.

class Rva0006ED36Sub
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void rva0006ED55();
};

class Rva0006ED36
{
public:
	void rva0006ED36(void *p);
	void rva0006EE27(void *p);
private:
	char m_pad00[0x108];
	Rva0006ED36Sub m_sub;
	char m_pad10C[0x118 - 0x108 - 4];
	void *m_slot118;
	char m_pad11C[0x814 - 0x118 - 4];
	void *m_slot814;
};

void Rva0006ED36::rva0006ED36(void *p)
{
	m_slot814 = p;
	m_sub.rva0006ED55();
	m_slot814 = 0;
}

void Rva0006ED36::rva0006EE27(void *p)
{
	m_slot118 = p;
	m_sub.rva0006ED55();
	m_slot118 = 0;
}

// ?rva0006ED55@Rva0006ED55@@UAEXXZ @0x0006ED55 (26B): that slot 12 itself,
// compiled against the +0x108 subobject. When the +0x814 pointer the
// callers above set is non-null, it hands the whole object and that pointer
// to the rowed 0x00118660 render call. Same object as above, viewed through
// its two bases (the primary one with its own table at offset 0).
bool Rva00118660Call(void *owner, void *camera);

class Rva0006ED55Primary
{
public:
	virtual void p00();
private:
	char m_pad04[0x108 - 4];
};

class Rva0006ED55 : public Rva0006ED55Primary, public Rva0006ED36Sub
{
public:
	virtual void rva0006ED55();
private:
	char m_pad10C[0x814 - 0x10C];
	void *m_slot814;
};

void Rva0006ED55::rva0006ED55()
{
	if (m_slot814)
		Rva00118660Call(this, m_slot814);
}
