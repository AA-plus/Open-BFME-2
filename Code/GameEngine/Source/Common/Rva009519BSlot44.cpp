// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00094CEA@Rva009519B@@UAEXXZ, retail 0x00094CEA (80 bytes): slot 44
// (+0xB0) of the CloudEffect record class Rva009519B (vtable 0x00BC81A8,
// see Rva00214F14Init.cpp). While the shared weather state behind the .data
// pointer at 0x00DE4880 (data ledger name g_get_00710fb0) holds 100 at +0x40,
// the record switches to mode 4 (+0xB8), the state's +0x38 triple and its
// +0x69/+0x6A flags are cleared, and so is the record's +0x20 flag. Every
// access rereads the pointer as retail does. Address-derived names; this view
// defines no constructor or destructor and emits no vtable.
struct Rva00094CEAState
{
	unsigned char m_pad00[0x38];
	float m_38;
	float m_3C;
	float m_40;
	unsigned char m_pad44[0x69 - 0x44];
	bool m_69;
	bool m_6A;
};
extern int g_get_00710fb0;	// 0x00DE4880
#define TheCloudState (*(Rva00094CEAState **)&g_get_00710fb0)

class Rva009519B
{
public:
	virtual bool rva0009520C();
	virtual void rva00094C70();
	virtual void rva00094CA9();
	virtual void rva00094CEA();
	virtual void rva00094C58();
private:
	unsigned char m_pad04[0x20 - 0x04];
	bool m_20;		// +0x20
	unsigned char m_pad21[0xB8 - 0x21];
	int m_mode;		// +0xB8
};

// Slots 47, 40 and 41 (retail 0x00094C58, 0x00094C70 and 0x00094CA9, laid
// out just before slot 44): clear the state's +0x38 triple; clear it and
// select mode 1 with +0x69 set; or set +0x38 to one with both flags set and
// select mode 3.
void Rva009519B::rva00094C58()
{
	Rva00094CEAState *state = TheCloudState;
	state->m_38 = state->m_3C = state->m_40 = 0.0f;
}

void Rva009519B::rva00094C70()
{
	TheCloudState->m_38 = 0.0f;
	Rva00094CEAState *state = TheCloudState;
	state->m_3C = state->m_40 = 0.0f;
	TheCloudState->m_69 = true;
	TheCloudState->m_6A = false;
	m_mode = 1;
}

void Rva009519B::rva00094CA9()
{
	Rva00094CEAState *state = TheCloudState;
	state->m_3C = state->m_40 = 0.0f;
	TheCloudState->m_69 = true;
	TheCloudState->m_6A = true;
	TheCloudState->m_38 = 1.0f;
	m_mode = 3;
}

void Rva009519B::rva00094CEA()
{
	if (TheCloudState->m_40 == 100.0f)
	{
		m_mode = 4;
		Rva00094CEAState *state = TheCloudState;
		state->m_38 = state->m_3C = state->m_40 = 0.0f;
		TheCloudState->m_69 = false;
		TheCloudState->m_6A = false;
		m_20 = false;
	}
}

// Slot 15 (retail 0x0009520C, 24 bytes): the +0x20 flag is set and the mode
// is neither 0 nor 4.
bool Rva009519B::rva0009520C()
{
	return m_20 && m_mode != 0 && m_mode != 4;
}
