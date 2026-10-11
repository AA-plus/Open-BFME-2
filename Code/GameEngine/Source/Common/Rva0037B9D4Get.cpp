// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Rva0037B9D4Get, retail 0x0037B9D4, 116 bytes. Returns a UnicodeString
// built from the narrow string that the rowed GlobalData::rva002360DE
// 0x002360DE returns for TheWritableGlobalData, converted through the rowed
// UnicodeString(const AsciiString &) 0x006CB6D0 and then suffixed with the
// wide literal at 0x00C18798.
// Retail's unwind map tracks the returned narrow string as a temporary of
// the constructing expression (state 1), the local (states 2/3) and the
// return slot (state 0). The banked 0.95 attempt released the narrow string
// by hand and missed state 1.
typedef int Int;
typedef unsigned short WideChar;
#define NULL 0
#include "ascii_string.h"
#include "unicode_string.h"
class GlobalData
{
public:
    AsciiString rva002360DE() const;
private:
    char m_pad[0x1240];
    AsciiString m_string1240;
};
extern GlobalData *TheWritableGlobalData;
// Retail's own 20-byte wide string at RVA 0x00818798 (.rdata, file offset
// 0x00817BD8): "Replays\" in UTF-16 followed by the terminating NUL and the
// NUL that keeps the array's ten words on retail's own alignment - 20 bytes is
// the ledger's bound, and the ASCII bytes that follow ("GUI") belong to retail's
// next literal. The rowed body below concatenates it onto the save-game
// directory the global data supplies, which is why the suffix is a string and
// not a code view.
// Symbol ?g_00C18798@@3QBGB, transcribed below.
extern const WideChar g_00C18798[] = { 'R', 'e', 'p', 'l', 'a', 'y', 's', '\\', 0, 0 };
UnicodeString Rva0037B9D4Get()
{
    UnicodeString wtmp(TheWritableGlobalData->rva002360DE());
    wtmp.concat(g_00C18798);
    return wtmp;
}
