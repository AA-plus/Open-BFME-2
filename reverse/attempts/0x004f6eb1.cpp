// ?Rva004F6EB1Heap@@YAXPAURva004F6352@@U1@@Z
// partial score=0.8 date=2026-10-13
// cl: /O1 /EHsc /MD
// scratch for 0x004F6EB1 (heap sift with ownership-transfer release)
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};
struct Rva004F6352
{
	int m_00;
	int m_04;
	TreeHintRef00217D4C m_08;
	Rva004F6352(const Rva004F6352 &other);
	Rva004F6352 &operator=(const Rva004F6352 &other);
	~Rva004F6352();
};
struct Rva004F6EB1Key
{
	char m_pad[8];
	int m_key;
};
static int KeyOf(const Rva004F6352 *r)
{
	return ((Rva004F6EB1Key *)(r->m_00))->m_key;
}
void Rva004F6EB1Heap(Rva004F6352 *pos, Rva004F6352 value)
{
	Rva004F6352 *cursor = &pos[-1];
	while (KeyOf((const Rva004F6352 *)&value) > KeyOf(cursor))
	{
		*(cursor + 1) = *cursor;
		--cursor;
	}
	*(cursor + 1) = value;
	if (value.m_08.m_ptr)
		ReleaseTreeHintRef00217D4C(value.m_08.m_ptr);
}
