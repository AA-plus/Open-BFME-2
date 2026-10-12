// cl: /O2 /MD
// Small Apt-runtime leaf bodies from .text gaps no Ghidra function covers.
// Retail bytes establish every shape; the owning classes are not recovered,
// so each keeps an address-derived name and a view of only the bits it
// touches. Neighbouring rows (0x006CBC10 getters, 0x006CBD60 clip stack)
// place them in the Apt runtime.

// ?set@Rva006CBC20Flag5@@QAEX_N@Z @ 0x006CBC20 (30B): stores a bool into
// bit 5 of the +4 flag word (xor/and/xor bitfield insert).
class Rva006CBC20Flag5
{
public:
	void set(bool value);
private:
	unsigned int m_00;
	unsigned int m_unused0 : 5;
	unsigned int m_flag5 : 1;
};

void Rva006CBC20Flag5::set(bool value)
{
	m_flag5 = value ? 1 : 0;
}

// ?set@Rva006CBDA0Field18@@QAEXH@Z @ 0x006CBDA0 (25B): stores the low two
// bits of an int into bits 18..19 of the +0x5C word.
class Rva006CBDA0Field18
{
public:
	void set(int value);
private:
	char m_pad[0x5C];
	unsigned int m_unused0 : 18;
	unsigned int m_field18 : 2;
};

void Rva006CBDA0Field18::set(int value)
{
	m_field18 = value;
}

// ?set@Rva006E0180Flag16@@QAEXH@Z @ 0x006E0180 (32B): stores a normalised
// int flag into bit 16 of the +0x5C word.
class Rva006E0180Flag16
{
public:
	void set(int value);
private:
	char m_pad[0x5C];
	unsigned int m_unused0 : 16;
	unsigned int m_flag16 : 1;
};

void Rva006E0180Flag16::set(int value)
{
	m_flag16 = value ? 1 : 0;
}

// ?clear@Rva006E3C50Table@@QAEXXZ @ 0x006E3C50 (36B): resets the 16-bit
// count at +0 and zero-fills the +4 slot array over the 16-bit capacity at +2.
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
class Rva006E3C50Table
{
public:
	void clear();
private:
	unsigned short m_count;
	unsigned short m_capacity;
	void **m_slots;
};

void Rva006E3C50Table::clear()
{
	m_count = 0;
	memset(m_slots, 0, m_capacity * sizeof(void *));
}

// ?set@Rva006F6980Bits24@@QAEXH@Z @ 0x006F6980 (31B) and
// ?clear@Rva006F6980Bits24@@QAEXH@Z @ 0x006F69A0 (37B): OR a mask into, or
// mask it out of, the signed 24-bit field at the bottom of the +0x1C word.
class Rva006F6980Bits24
{
public:
	void set(int mask);
	void clear(int mask);
private:
	char m_pad[0x1C];
	int m_bits : 24;
};

void Rva006F6980Bits24::set(int mask)
{
	m_bits |= mask;
}

void Rva006F6980Bits24::clear(int mask)
{
	m_bits &= ~mask;
}
