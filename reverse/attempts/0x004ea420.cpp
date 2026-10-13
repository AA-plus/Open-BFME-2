// ?rva004EA420@Rva004EA420@@QAEXXZ
// partial score=0.9836 date=2026-10-13
// ?rva004EA420@Rva004EA420@@QAEXXZ
// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x004EA420..0x004EA4E4 (197B). If the global pointer vector at
// 0x00E04494 is empty and Rva004EA2C5Get()>0, reserves it, walks GameLogic
// objects (getFirstObject 0x0023CAD2) and for each whose +4 record has an
// AsciiString at +0x64 equal to the global AsciiString 0x00E04490
// (StringBase compare 0x000069D6) creates an Rva00596F18 (rowed ctor
// 0x00596EEF), sets its Coord3D from object+0x38 (rowed 0x00573A00), copies
// object+0x44 to item+0x3C and push_backs it (rowed 0x004DFCB0); next at
// object+0x8C.
#include <vector>
#include "ascii_string.h"
#include "Coord3D.h"

class Object;
class GameLogic
{
public:
	Object *getFirstObject();
};
extern GameLogic *TheGameLogic;

int Rva004EA2C5Get();

class ModuleData;

class Rva00573A00
{
public:
	void rva00573A00(const Coord3D *pos);
};

class Rva00596F18 : public Rva00573A00
{
public:
	Rva00596F18(void *arg);
private:
	char m_pad[0x74];
};

extern _STL::vector<const ModuleData *> g_00E04494;
extern AsciiString g_00E04490;

class Rva004EA420
{
public:
	void rva004EA420();
};

void Rva004EA420::rva004EA420()
{
	if (!g_00E04494.empty())
		return;
	int count = Rva004EA2C5Get();
	if (count <= 0)
		return;
	g_00E04494.reserve(count);
	int index = 0;
	Object *obj = TheGameLogic->getFirstObject();
	if (!obj)
		return;
	do
	{
		char *record = *(char **)((char *)obj + 4);
		if (((const StringBase<char> *)(record + 0x64))->compare(*(const StringBase<char> *)&g_00E04490) == 0)
		{
			Rva00596F18 *item = new Rva00596F18((void *)index++);
			item->rva00573A00((const Coord3D *)((char *)obj + 0x38));
			*(int *)((char *)item + 0x3C) = *(int *)((char *)obj + 0x44);
			g_00E04494.push_back((const ModuleData *)item);
		}
		obj = *(Object **)((char *)obj + 0x8C);
	} while (obj);
}
