// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva0052B5FD@Rva0052B5FD@@QAEPAVRva005C4A91@@ABVAsciiString@@@Z retail
// 0x0052B5FD 55B: new(0x18) plus rowed ctor 0x005C49EF with EH null guard,
// returning the object (retail's shared xor eax zero is the null result; the
// caller 0x0052B661 returns it in turn).
// Evidence: callee rows for new 0x0002FDA0 and ctor; caller at 0x0052B661;
// neighbours Rva0052B024Loop and RvaLookupFieldOrZeroFamily share /O1.
#include "ascii_string.h"
class Rva005C4A91
{
public:
	Rva005C4A91(const AsciiString &s);
private:
	char m_pad[0x18];
};
class Rva0052B5FD
{
public:
	Rva005C4A91 *rva0052B5FD(const AsciiString &s);
};
Rva005C4A91 *Rva0052B5FD::rva0052B5FD(const AsciiString &s)
{
	return new Rva005C4A91(s);
}
