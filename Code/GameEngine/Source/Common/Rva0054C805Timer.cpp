// cl: /O1 /G6 /DNDEBUG /MD
// Rva0054C805::rva0054C805, retail 0x0054C805 (49 bytes, RET4).
// __thiscall timer update: unless the state at +0x14 is 0 or 3, store
// timeGetTime() - (int)(seconds * -1000.0f) at +0x24. The caller at 0x0054C877
// (Rva0054C88A::rva0054C877) forwards its float argument unchanged. The
// -1000.0f operand is the compiler literal pooled at 0x00C08A34.
// Class and member names are address-derived; the layout is an ABI view.
// The reference binding is a codegen lever (retail loads the argument before
// the literal and keeps the receiver in esi); it makes no claim about the
// original source qualifiers.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Rva0054C805
{
public:
	void rva0054C805(float seconds);

private:
	char m_pad00[0x14];
	int m_state;
	char m_pad18[0x0C];
	int m_deadline;
};

void Rva0054C805::rva0054C805(float seconds)
{
	if (m_state == 0)
		return;
	if (m_state == 3)
		return;
	const volatile float &delay = seconds;
	m_deadline = timeGetTime() - (int)(delay * -1000.0f);
}
