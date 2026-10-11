// cl: /MD
// ??0Rva004691A5@@QAE@XZ 0x004691A5 18B evidence: and-or inc O1 idioms plus movss; caller 0x474431 constructs 0x1C-byte stack record
class Rva004691A5
{
public:
	Rva004691A5();

private:
	int m_00;
	char m_pad04[0x10];
	float m_14;
	int m_18;
};

Rva004691A5::Rva004691A5() : m_00(0), m_14(0.0f), m_18(-1)
{
}

class Rva00469155
{
public:
	Rva00469155();
	Rva00469155 &operator=(const Rva00469155 &o);

private:
	struct Float3
	{
		float x;
		float y;
		float z;
	};
	Float3 m_pos;
	int m_0C;
};

inline void *operator new(unsigned int, void *p) { return p; }
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00469155::Rva00469155() : m_0C(0)
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
}

// ?bfmeAnchorRva00469155 absent-from-retail
void *bfmeAnchorRva00469155(void *where)
{
	return new (where) Rva00469155();
}


// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva00469155 &Rva00469155::operator=(const Rva00469155 &o)
{
	m_pos = o.m_pos;
	m_0C = o.m_0C;
	return *this;
}

// ?bfmeAnchorRva00469155Assign absent-from-retail
Rva00469155 &bfmeAnchorRva00469155Assign(Rva00469155 *p, const Rva00469155 &o)
{
	return *p = o;
}


// ??0Rva00469187@@QAE@XZ 0x00469187 30B evidence: zero int pair plus two rowed Rva0042526Member 0x4C ctors at +8 +0x54 callers 0x3A484A 0x46F639
class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	unsigned char m_pad[0x4C];
};

class Rva00469187
{
public:
	Rva00469187();

private:
	int m_00;
	int m_04;
	Rva0042526Member m_08;
	Rva0042526Member m_54;
};

Rva00469187::Rva00469187() : m_00(0), m_04(0)
{
}
