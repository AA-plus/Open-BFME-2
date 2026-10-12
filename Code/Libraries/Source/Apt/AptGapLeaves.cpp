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
