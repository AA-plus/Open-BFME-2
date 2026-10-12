// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/bfme2_ascii
// Native56D671..56D690 complete31B RET4, allocation factory410223..41025D
// calls here at41024A with270 bytes. Dtor56D690 establishes the shared
// Rva0056D690 neutral identity, vtable C6DAC4 and AsciiString at26C.
// The base constructor is the independently rowed Apt screen provider5C96EB;
// its former Locomotor identity is refuted by its base/table and realLocomotor
// at1E449A. The AptComponents BinkGameWindow::Create branch selects410223.
// Only the base26C prefix and forwarded opaque context ABI are modeled;
// no original receiver or context type name is asserted.
// Canonical AsciiString default construction is defined initialization.
#include "ascii_string.h"
class Rva005C96EB
{
public:
	Rva005C96EB(void *ctx);
	virtual ~Rva005C96EB();
private:
	char m_pad[0x26C - 4];
};

class Rva0056D690 : public Rva005C96EB
{
public:
	Rva0056D690(void *ctx);
	virtual ~Rva0056D690();
private:
	AsciiString m_26C;
};

Rva0056D690::Rva0056D690(void *ctx)
	: Rva005C96EB(ctx)
{
}
