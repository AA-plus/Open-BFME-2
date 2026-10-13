// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob2
// ??1Gen_003A8BE0@@QAE@XZ 0x002160C4 68B evidence: dtor over three StringBase<char> at +0 +4 +8 via releaseBuffer row 0x00036410 with EH states; callers 0x00216120 0x00217019 and Unwind funclet; unblocks 0x00216108
#include "ascii_string.h"
class Gen_003A8BE0 {
    AsciiString m_0;
    AsciiString m_4;
    AsciiString m_8;
public:
    ~Gen_003A8BE0();
};
Gen_003A8BE0::~Gen_003A8BE0()
{
}
