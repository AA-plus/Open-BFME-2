// Trivial allocator shims that sit inside the 0x006026E0 run of int-zero
// getters (IntZeroGetters.cpp). The object's first dword after the pad is
// read as a pointer at +0x08, two cdecl callback slots live at +0x54 and
// +0x58, and a flag byte at +0x60. Identity is not recovered: names are
// derived from their addresses. No // cl: line so the frameless /O2 shapes
// match, the same defaults the neighbouring zero getters rely on.

void *operator new[](unsigned n);
void operator delete[](void *p);

class Rva006026E0
{
public:
	char m_pad00[0x4];
	void *m_p04;
	void *m_p08;
	void *m_p0c;
	void *m_p10;
	char m_pad14[0x40];
	void *(__cdecl *m_fn54)(unsigned n);
	void *(__cdecl *m_fn58)(void *p);
	unsigned char m_flags5c;
	char m_pad5d[3];
	unsigned char m_flags60;
	char m_pad61[3];
	unsigned char m_flags64;
	char m_pad65[3];
	unsigned char m_flags68;

	void *alloc(unsigned n);
	void free(void *p);
	int rva006026A0();
	int rva006027B0();
	int get();
	int rva00602870();
	void rva00602680(unsigned char value);
	void rva006027D0(unsigned char value);
	void rva00602830(unsigned char value);
};

void *Rva006026E0::alloc(unsigned n)
{
	if (m_fn54)
		return m_fn54(n);
	return operator new[](n);
}

void Rva006026E0::free(void *p)
{
	if (p)
	{
		if (m_fn58)
			m_fn58(p);
		else
			operator delete[](p);
	}
}

int Rva006026E0::rva006026A0()
{
	if (m_flags5c & 1)
	{
		m_flags5c |= 2;
		return *(int *)((char *)m_p04 + 8);
	}
	return *(int *)((char *)m_p04 + 8);
}

int Rva006026E0::rva006027B0()
{
	if (m_flags64 & 1)
	{
		m_flags64 |= 2;
		return *(int *)((char *)m_p0c + 8);
	}
	return *(int *)((char *)m_p0c + 8);
}

int Rva006026E0::get()
{
	if (m_flags60 & 1)
	{
		m_flags60 |= 2;
		return *(int *)((char *)m_p08 + 8);
	}
	return *(int *)((char *)m_p08 + 8);
}

int Rva006026E0::rva00602870()
{
	if (m_flags68 & 1)
	{
		m_flags68 |= 2;
		return *(int *)((char *)m_p10 + 8);
	}
	return *(int *)((char *)m_p10 + 8);
}

// Native complete 26B leaves at 602680, 6027D0 and 602830, each RET4.
// The first was a whole unattempted body in the gap audit; a narrow native
// byte search found the other two with only the witnessed flag offset changed.
// Their +5C/+60/+68 bytes are already read by the paired rowed getters above.
// If bit0 is set, copy the low argument bit into bit1, preserving all other
// bits. The original owner, flag meanings and argument typedef are unknown;
// the unsigned-byte member ABI and this receiver view remain neutral.
void Rva006026E0::rva00602680(unsigned char value)
{
	if (m_flags5c & 1)
		m_flags5c = (m_flags5c & ~2) | ((value << 1) & 2);
}

void Rva006026E0::rva006027D0(unsigned char value)
{
	if (m_flags60 & 1)
		m_flags60 = (m_flags60 & ~2) | ((value << 1) & 2);
}

void Rva006026E0::rva00602830(unsigned char value)
{
	if (m_flags68 & 1)
		m_flags68 = (m_flags68 & ~2) | ((value << 1) & 2);
}
