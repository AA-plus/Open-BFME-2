// ?translate@HotKeyManager@@QAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// partial score=0.997 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Native 00359556..003596AD; WB1132720 HotKeyManager::translate.
// ZH HotKeyTranslator supplies the raw-key/string translation spine. BFME2
// adds bound message actions and permits the first modifier group alone.
// Map storage is viewed through the existing int-key/int-value provider;
// retail independently proves the action pointer occupies node+0x14.
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"

union GameMessageArgumentType { int integer; unsigned char key; };
class GameMessage {
public:
 const GameMessageArgumentType *getArgument(int index) const;
 char unknown[0x10];
 int type;
};
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
class Keyboard { public: unsigned short getPrintableKey(unsigned char key, int shift); };
extern Keyboard *TheKeyboard;
class HotKeyActionView {
public:
 virtual void slot0();
 virtual bool isBlocked(void *context);
 virtual bool isEnabled(void *context);
 virtual bool execute(void *context);
};
// Names of these action methods are structural inferences from their use;
// only the virtual slots and bool results are established by target evidence.

class Rva003593E8 {
public: bool rva003593E8(const AsciiString &key, bool modifier);
};
class HotKeyManager {
public:
 GameMessageDisposition translate(const GameMessage *message);
 void rva00358A53();
 void rva00358ACB();
private:
 char unknown[0x24];
 _STL::map<int,int> actions;
};
GameMessageDisposition HotKeyManager::translate(const GameMessage *message)
{
 int type = message->type;
 _STL::map<int,int>::iterator found = actions.find(type);
 if (found._M_node != actions.end()._M_node) {
  int &handle = found->second;
  if (!((HotKeyActionView *)handle)->isBlocked(0)) {
   if (((HotKeyActionView *)handle)->isEnabled(0)) {
    if (((HotKeyActionView *)handle)->execute(0)) rva00358A53();
   } else {
    rva00358ACB();
   }
   return DESTROY_MESSAGE;
  }
 }
 if (type == 0x16) {
  int keyState = message->getArgument(1)->integer;
  int modifiers = 0;
  bool firstModifierOnly = false;
  if (keyState & 0x430) { modifiers |= 0x10; firstModifierOnly = true; }
  if (keyState & 0x0C) { modifiers |= 4; firstModifierOnly = false; }
  if (keyState & 0xC0) { modifiers |= 0x40; firstModifierOnly = false; }
  if (modifiers != 0 && !firstModifierOnly) return KEEP_MESSAGE;
  unsigned short key = TheKeyboard->getPrintableKey(message->getArgument(0)->key, 0);
  UnicodeString unicode;
  unicode = key;
  AsciiString ascii;
  ascii.translate(unicode);
  if (((Rva003593E8 *)this)->rva003593E8(ascii, firstModifierOnly)) return DESTROY_MESSAGE;
 }
 return KEEP_MESSAGE;
}
