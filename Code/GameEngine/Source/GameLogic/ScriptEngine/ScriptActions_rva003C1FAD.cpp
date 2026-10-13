// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD -GX -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003C1FADDestroy@ScriptActions@@QAEXXZ @0x003C1FAD 49B
// Destroy flagged GameLogic objects via rowed getFirstObject 0x0023CAD2
// and destroyObject 0x00242C09. Evidence: caller 0x003CDA80;
// neighbours 0x003C0FEA 0x003C10D8; global TheGameLogic.
class Object {
public:
	char m_pad8c[0x8c];
	Object *m_next;
	char m_pad9[0x1c8 - 0x8c - 4];
	unsigned char m_flags1c8;
};

class GameLogic {
public:
	Object *getFirstObject();
	void destroyObject(Object *o);
};

extern GameLogic *TheGameLogic;

void ScriptActions::Rva003C1FADDestroy(void)
{
	Object *o = TheGameLogic->getFirstObject();
	while (o != 0) {
		if ((o->m_flags1c8 & 0x20) != 0)
			TheGameLogic->destroyObject(o);
		o = o->m_next;
	}
}
