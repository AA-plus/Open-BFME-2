// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0055BBAE@Rva003ADFB2@@QAE_NH@Z, retail 0x0055BBAE (139 bytes, RET 4):
// slot 10 of the FX module table whose deleting destructor is rowed as
// Rva003ADFB2 (its xfer 0x0055BB5C reads the colour at +0x94 and the index at
// +0xAC). Given a blend mode, modes 1, 2 and 6 report whether the colour is
// nearly black (component sum under 0.03) and mode 5 whether it is nearly
// white (component product over 0.97), each only while the current record
// (+0xAC into the 16-byte records at +0x1C) has no entry; other modes always
// answer true. Address-derived names.
struct Rva0055BBAERecord
{
	int m_entry;
	unsigned char m_pad04[0x0C];
};

class Rva003ADFB2
{
public:
	bool rva0055BBAE(int mode);
private:
	unsigned char m_pad00[0x1C];
	Rva0055BBAERecord m_records[7];	// +0x1C
	unsigned char m_pad8C[0x94 - 0x8C];
	float m_red;			// +0x94
	float m_green;			// +0x98
	float m_blue;			// +0x9C
	unsigned char m_padA0[0xAC - 0xA0];
	int m_current;			// +0xAC
};

bool Rva003ADFB2::rva0055BBAE(int mode)
{
	switch (mode)
	{
	case 1:
	case 2:
	case 6:
		return m_records[m_current].m_entry == 0 && 0.03f > m_blue + m_green + m_red;
	case 5:
		return m_records[m_current].m_entry == 0 && m_blue * m_green * m_red > 0.97f;
	}
	return true;
}
