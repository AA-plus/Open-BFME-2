// Retail stores the entry point at VA 0x006D7B50 in the +0x9C slot.
// Its matched provider is rva002D7B50 in VslotSmallBodiesAG.cpp; naming it
// gives the store a relocation when the linked image moves. The owner's
// identity and the slot's purpose remain unknown.
void rva002D7B50(int a, int b);

class Rva0028576DDwordImmSetter
{
public:
	void apply();

	char m_lead[0x9C];
	unsigned int m_value;
};

void Rva0028576DDwordImmSetter::apply()
{
	m_value = (unsigned int)&rva002D7B50;
}
