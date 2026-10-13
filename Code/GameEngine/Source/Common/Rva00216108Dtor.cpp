// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob2
// ??1Rva00216108@@QAE@XZ 0x00216108 53B evidence: outer dtor with AsciiString at +0 and Gen_003A8BE0 at +4 via rowed inner dtor plus releaseBuffer; chain from 0x002160C4 landing; callers 0x002161C5 0x0021678F 0x00217008
#include "ascii_string.h"
class Gen_003A8BE0 {
    AsciiString m_0;
    AsciiString m_4;
    AsciiString m_8;
public:
    ~Gen_003A8BE0();
};
class Rva00216108 {
    AsciiString m_0;
    Gen_003A8BE0 m_4;
public:
    ~Rva00216108();
};
Rva00216108::~Rva00216108()
{
}
