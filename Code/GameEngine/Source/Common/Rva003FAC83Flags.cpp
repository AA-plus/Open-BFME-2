// cl: /DNDEBUG /MD
// Flag refreshers on the map-node payload whose pinned callers sit at
// 0x00213AA1..0x00213C4C. Each sets the +0x32 byte, then tail-calls the
// 0x003FAC83 dispatcher. The bit0/bit2 siblings 0x003FACB4 and 0x003FAD2B
// stay out pending their independent byte checks (see re_attempts).
// Names are address-derived (see the symbols.csv pins).

class Rva003FAB93 { public: void rva003FAB93(); };
class Rva003FAC3F { public: void rva003FAC3F(); };

class Rva003FAC83
{
public:
	void rva003FAC83();
	void rva003FAD9A();
	void rva003FAD2B();
	void rva003FADA3();

private:
	// WB 0x0105FE70 carries BitFlags<7>::test at the two call sites.
	// Keeping the index as an inline parameter preserves retail's shifts.
	bool test(int bit) const { return ((m_state >> bit) & 1) != 0; }
	char m_pad00[0x18];
	unsigned int m_state;
	char m_pad1c[0x14];
	bool m_30;
	bool m_31;
	bool m_32;
};

// Native 0x003FAC83..0x003FACB4; WB 0x0105FE70 confirms both guards
// and calls. The concrete payload and member names remain unresolved.
void Rva003FAC83::rva003FAC83()
{
	if (m_31 == 0 || m_32 == 0)
		goto checkBit5;
	if (test(4) && m_30 != 0)
		return;
	((Rva003FAB93 *)this)->rva003FAB93();
	return;
checkBit5:
	if (test(5))
		return;
	((Rva003FAC3F *)this)->rva003FAC3F();
}

// 0x003FAD9A 9B
void Rva003FAC83::rva003FAD9A()
{
	m_32 = true;
	rva003FAC83();
}

// 0x003FADA3 18B
void Rva003FAC83::rva003FADA3()
{
	m_32 = !((m_state >> 3) & 1);
	rva003FAC83();
}

// Native 0x003FAD2B..0x003FAD4A: a byte test for bit zero is distinct
// from the indexed word test. This is a read of the same little-endian flags.
void Rva003FAC83::rva003FAD2B()
{
 if ((*(const unsigned char *)&m_state & 1) != 0 || test(2))
  m_31 = false;
 else
  m_31 = true;
 rva003FAC83();
}
