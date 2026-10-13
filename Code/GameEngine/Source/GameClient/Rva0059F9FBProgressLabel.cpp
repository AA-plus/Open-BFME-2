// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
// Retail 0x0059F9FB..0x0059FB4F is the complete 340-byte RET10 progress-label
// routine the EH-prolog chapter scan found unrowed, in the online custom-match
// chapter next to the rowed 0x0059F9D7/0x0059F9E9 OpenConnectionScreen
// forwarders.  Target facts: arg0 (int) is handed to the rowed
// ?Rva0059F296Set@@YAXHABVUnicodeString@@@Z 0x0059F296; arg1 (int) selects one
// of the connection labels in the order 2,3,4,5,1,0,default; arg2/arg3 (bytes)
// choose the three-way case-2 label; case 0 assigns the wide literal L" ";
// every other arm assigns TheGameText->fetch(label, 0) into a UnicodeString
// local and the fetch return temporary lands in the dead arg2 stack slot.
// The labels are GUI:WaitingForManglerResponse / GUI:WaitingForMangledPort /
// GUI:ReceivedPorts / GUI:WaitingForResponse / GUI:ConnectionDone /
// GUI:ConnectionFailed / GUI:WaitingToBeginConnection /
// GUI:UnknownConnectionState.  Eight EH states, one per fetch arm plus state 0.
// The function has no other name evidence, so it keeps an address-derived name;
// TheGameText is declared as the 15-slot view whose fetch is the rowed call.
#include "unicode_string.h"

class AsciiString;
void Rva0059F296Set(int playerID, const UnicodeString &text);

class Rva0059F9FBText {
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual UnicodeString fetch(const char *label, bool *exists);
};
extern Rva0059F9FBText *TheGameText;

class Rva0059F9FB { public: void rva0059F9FB(int playerID, int state, bool first, bool second); };

void Rva0059F9FB::rva0059F9FB(int playerID, int state, bool first, bool second)
{
	UnicodeString text;
	if (state == 2) {
		if (!first)
			text = TheGameText->fetch("GUI:WaitingForManglerResponse", 0);
		else if (!second)
			text = TheGameText->fetch("GUI:WaitingForMangledPort", 0);
		else
			text = TheGameText->fetch("GUI:ReceivedPorts", 0);
	}
	else if (state == 3)
		text = TheGameText->fetch("GUI:WaitingForResponse", 0);
	else if (state == 4)
		text = TheGameText->fetch("GUI:ConnectionDone", 0);
	else if (state == 5)
		text = TheGameText->fetch("GUI:ConnectionFailed", 0);
	else if (state == 1)
		text = TheGameText->fetch("GUI:WaitingToBeginConnection", 0);
	else if (state == 0)
		text = L" ";
	else
		text = TheGameText->fetch("GUI:UnknownConnectionState", 0);
	Rva0059F296Set(playerID, text);
}
