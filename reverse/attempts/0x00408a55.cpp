// ?rva00408A55@CreateAHeroData@@QAE_NXZ
// partial score=0.754196642685851 date=2026-10-11
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Ob2 /EHs /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Isolated reconstruction of native 408A55..408C11, 444 bytes, RET0.
// Save-path and map50 view follow the independently verified 4074CF writer.
// Native returns a bool; the current void-return pin needs reconciliation before landing.
#include "ascii_string.h"
#include "unicode_string.h"
#include <map>
struct TreeHintPayload001F8ACB { unsigned value; };
typedef _STL::map<AsciiString, TreeHintPayload001F8ACB> StringPayloadMap;
namespace _STL {
template <> TreeHintPayload001F8ACB &map<AsciiString, TreeHintPayload001F8ACB>::operator[](const AsciiString &);
}
class GameState;
extern GameState *TheGameState;
class Rva002DC74A { public: UnicodeString rva002DC74A(const UnicodeString &) const; };
class Rva0021937DTarget { public: void rva00407E94(); };
struct _iobuf;
extern "C" {
__declspec(dllimport) _iobuf *__cdecl _wfopen(const unsigned short *, const unsigned short *);
__declspec(dllimport) char *__cdecl fgets(char *, int, _iobuf *);
__declspec(dllimport) int __cdecl fclose(_iobuf *);
}
class CreateAHeroData {
    char unknown00[0x4C];
    AsciiString filename;
    StringPayloadMap stats;
public:
    bool rva00408A55();
};
bool CreateAHeroData::rva00408A55()
{
    if (reinterpret_cast<const StringBase<char> *>(&filename)->isEmpty())
        return false;
    UnicodeString path = reinterpret_cast<const Rva002DC74A *>(TheGameState)->rva002DC74A(UnicodeString(filename));
    _iobuf *file = _wfopen(path.str(), reinterpret_cast<const unsigned short *>(L"r"));
    char buffer[1024];
    bool result = false;
    if (file != 0) {
      if (fgets(buffer, sizeof(buffer), file)) {
        do {
        AsciiString line(buffer);
        line.trim();
        AsciiString key;
        AsciiString value;
        line.nextToken(&key, "=");
        value.set(line.str() + 1);
        key.trim();
        value.trim();
        if (!key.isEmpty()) {
            if (value.isEmpty())
                stats[key].value = 0;
            else
                stats[key].value = atoi(value.str());
        }
        } while (fgets(buffer, sizeof(buffer), file));
      }
      fclose(file);
      reinterpret_cast<Rva0021937DTarget *>(this)->rva00407E94();
      result = true;
    }
    return result;
}
