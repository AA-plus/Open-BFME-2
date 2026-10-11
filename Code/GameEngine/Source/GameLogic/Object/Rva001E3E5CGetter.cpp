// cl: /O1 /MD
// ?rva001E3E5C@Rva001E3E5C@@QBE_NXZ, retail 0x001E3E5C (17 bytes).
// Target evidence: thiscall bool getter (pin in reverse/symbols.csv, called
// from Object::rva0028C428 on a Rva0028AC4EEntry): load the pointer at this+4,
// result 0 unless it is non-null, else its int at +0x0C is >= 1.
// Codegen finding: the retail xor eax,eax / setge al pair needs the result held
// in an int-width local whose low byte is returned (bool locals give xor al,al,
// a bool/!= 0 normalisation costs seven more bytes).
// Identity of the receiver and the pointed-to record is address-derived.

struct Rva001E3E5CRecord
{
	int m_unread[3];
	int m_value0C;	// +0x0C
};

class Rva001E3E5C
{
public:
	bool rva001E3E5C() const;

private:
	int m_unread00;
	const Rva001E3E5CRecord *m_record04;	// +0x04
};

bool Rva001E3E5C::rva001E3E5C() const
{
	const Rva001E3E5CRecord *record = m_record04;
	int result = 0;
	if (record)
		result = record->m_value0C >= 1;
	return *(bool *)&result;
}
