// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /G7
// ?setEmoticon@Drawable@@QAEXABV?$StringBase@D@@H@Z @0x002736BA 155B: Drawable find-or-create Anim2D at +0x354 slot 10 via container g_00DFF068 and TheGameLogic frame; neighbours Drawable_rva00273648 Drawable_rva00273755; callers 0x0036E1C3 0x003BC996.
#include "ascii_string.h"

struct Rva002D752DNode;
class Rva002D752D
{
public:
	Rva002D752DNode *rva002D752D(const StringBase<char> &name);
};

// g_00DFF068 is only an alias of the owned global TheAnim2DCollection (ledger names column); this unit reads the owner through its own view type.
extern class Anim2DCollection *TheAnim2DCollection;
#define g_00DFF068 (*(Rva002D752D * *)&TheAnim2DCollection)

class Rva00270025
{
public:
	virtual ~Rva00270025();
	void *m_items[14];
	int m_vals[14];
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
private:
	unsigned char m_pad[0x354];
	Rva00270025 *m_354;
};

class GameLogic
{
public:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

class Anim2DTemplate;
class Anim2DCollection;
class Anim2D
{
public:
	Anim2D(Anim2DTemplate *tmpl, Anim2DCollection *coll);
private:
	unsigned char m_pad[0x34];
};

void *__cdecl operator new(unsigned int size) throw();

class Drawable
{
public:
	void rva002736A8();
	void setEmoticon(const StringBase<char> &name, int val);
};

// ?rva002736A8@Drawable@@QAEXXZ present-unmatched
// ?rva002D752D@Rva002D752D@@QAEPAURva002D752DNode@@ABV?$StringBase@D@@@Z present-unmatched
// ?rva00270BA8@Rva00270BA8@@QAEPAVRva00270025@@XZ present-unmatched
void Drawable::setEmoticon(const StringBase<char> &name, int val)
{
	rva002736A8();
	Rva002D752DNode *found = g_00DFF068->rva002D752D(name);
	if (found == 0)
		return;
	if (((Rva00270BA8 *)this)->rva00270BA8()->m_items[10] != 0)
		return;
	Anim2D *anim = new Anim2D((Anim2DTemplate *)found, (Anim2DCollection *)g_00DFF068);
	((Rva00270BA8 *)this)->rva00270BA8()->m_items[10] = anim;
	int v;
	if (val >= 0)
		v = TheGameLogic->m_frame + val;
	else
		v = 0x3fffffff;
	((Rva00270BA8 *)this)->rva00270BA8()->m_vals[10] = v;
}
