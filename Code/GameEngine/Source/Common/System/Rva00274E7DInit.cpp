// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /DNDEBUG /MD /GX
// ?Rva00274E7DInit@@YAXXZ, retail 0x00274E7D (1147B): UI image table init.
// Evidence: 4 literal finds via ImageCollection 0x002D92F6 into g_00DFEB70/74/80/84,
// new 0x38 array into g_00DFEB78, 12 rva finds via 0x002D752D from g_00DBB660..694
// into array slots 0-2/4-9/11-13 with slot 10 zeroed, 4 literal finds into
// g_00DFEB88/8C/90/94, flag g_00DFEB6C; unblocks 0x002797BD; prev/next flags.
#include "ascii_string.h"

void *__cdecl operator new[](unsigned int size);

class Image;
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

struct Rva002D752DNode;
class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
};

extern ImageCollection *TheMappedImageCollection;
class Rva002D752D; extern class Anim2DCollection *TheAnim2DCollection;
extern const Image *g_00DFEB70;
extern const Image *g_00DFEB74;
extern const Image *g_00DFEB80;
extern const Image *g_00DFEB84;
extern const Image *g_00DFEB88;
extern const Image *g_00DFEB8C;
extern const Image *g_00DFEB90;
extern const Image *g_00DFEB94;
extern unsigned char g_00DFEB6C;
// The 0x38-byte Anim2D node array's object is defined under this same spelling in
// Rva00270190.cpp (the unit that frees it), so it is only declared here.
extern Rva002D752DNode **g_00DFEB78;
// The image slots and the Anim2D node array are written by this very function,
// so they are only declared above and defined here as tentative (uninitialised)
// objects: their addresses sit past .data's raw end (file offset 0x009DCC08), so
// retail loads them zero, and an explicit `= 0` would let MSVC fold the flag test
// into a literal and drop the early return. The twelve Anim2D template names are
// retail's own pointers at RVA 0x009BB660..0x009BB694 into .rdata; each one is
// transcribed as the string it points at.
unsigned char g_00DFEB6C;
const Image *g_00DFEB70;
const Image *g_00DFEB74;
const Image *g_00DFEB80;
const Image *g_00DFEB84;
const Image *g_00DFEB88;
const Image *g_00DFEB8C;
const Image *g_00DFEB90;
const Image *g_00DFEB94;
const char *g_00DBB660 = "DefaultHeal";
const char *g_00DBB664 = "StructureHeal";
const char *g_00DBB668 = "VehicleHeal";
const char *g_00DBB670 = "BombTimed";
const char *g_00DBB674 = "BombRemote";
const char *g_00DBB678 = "Disabled";
const char *g_00DBB67C = "BattlePlanIcon_Bombard";
const char *g_00DBB680 = "BattlePlanIcon_HoldTheLine";
const char *g_00DBB684 = "BattlePlanIcon_SeekAndDestroy";
const char *g_00DBB68C = "Enthusiastic";
const char *g_00DBB690 = "Subliminal";
const char *g_00DBB694 = "CarBomb";
extern const char *g_00DBB660;
extern const char *g_00DBB664;
extern const char *g_00DBB668;
extern const char *g_00DBB670;
extern const char *g_00DBB674;
extern const char *g_00DBB678;
extern const char *g_00DBB67C;
extern const char *g_00DBB680;
extern const char *g_00DBB684;
extern const char *g_00DBB68C;
extern const char *g_00DBB690;
extern const char *g_00DBB694;

void Rva00274E7DInit(void)
{
	if (g_00DFEB6C)
		return;
	{
		AsciiString tmp("SCPAmmoFull");
		g_00DFEB70 = TheMappedImageCollection->findImageByName(tmp);
	}
	{
		AsciiString tmp("SCPAmmoEmpty");
		g_00DFEB74 = TheMappedImageCollection->findImageByName(tmp);
	}
	{
		AsciiString tmp("ContainPip");
		g_00DFEB80 = TheMappedImageCollection->findImageByName(tmp);
	}
	{
		AsciiString tmp("ContainPipFrame");
		g_00DFEB84 = TheMappedImageCollection->findImageByName(tmp);
	}
	g_00DFEB78 = (Rva002D752DNode **)operator new[](0x38);
	{
		AsciiString tmp(g_00DBB660);
		g_00DFEB78[0] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB664);
		g_00DFEB78[1] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB668);
		g_00DFEB78[2] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB670);
		g_00DFEB78[4] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB674);
		g_00DFEB78[5] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB678);
		g_00DFEB78[6] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB67C);
		g_00DFEB78[7] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB680);
		g_00DFEB78[8] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB684);
		g_00DFEB78[9] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	g_00DFEB78[10] = 0;
	{
		AsciiString tmp(g_00DBB68C);
		g_00DFEB78[11] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB690);
		g_00DFEB78[12] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp(g_00DBB694);
		g_00DFEB78[13] = ((Rva002D752D *)TheAnim2DCollection)->rva002D752D(*(const StringBase<char> *)&tmp);
	}
	{
		AsciiString tmp("Good_Vet");
		g_00DFEB88 = TheMappedImageCollection->findImageByName(tmp);
	}
	{
		AsciiString tmp("Good_Vet_Dot");
		g_00DFEB8C = TheMappedImageCollection->findImageByName(tmp);
	}
	{
		AsciiString tmp("Evil_Vet");
		g_00DFEB90 = TheMappedImageCollection->findImageByName(tmp);
	}
	{
		AsciiString tmp("Evil_Vet_Dot");
		g_00DFEB94 = TheMappedImageCollection->findImageByName(tmp);
	}
	g_00DFEB6C = 1;
}
