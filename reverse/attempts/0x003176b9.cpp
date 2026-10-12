// ?Rva003176B9@@YAPAXVAsciiString@@@Z
// partial score=0.85 date=2026-10-13
// ?Rva003176B9@@YAPAXVAsciiString@@@Z
// partial score=0.85 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
// FRAGMENT for Code/GameEngine/Source/GameClient/GUI/Rva0031763ACtorDtorAssign.cpp (needs its Rva0031763A view + AsciiString).
// Retail is ONE 190B function 0x003176B9..0x00317776 (ret 4); the queue 94B Ghidra boundary splits head from tail at 0x00317717 (head jumps out, no ret).
// Decoded: by-value AsciiString param (param dtor 0x36410 at end, ret 4); local Rva0031763A via rowed ctor; by-value temp via rowed StringBase copy 0x365F0;
// rowed WindowLayoutInfo::load 0x31742C on reinterpreted &local (layout relation unproven); false->NULL; local+0x10 fnptr (field_10 per winCreateFromScript view):
// null->rowed new 0x2FDA0 + rowed QM ctor 0x538C0E + rowed attach 0x538C6D, else call it; result in esi; dtor via rowed 0x3175D1.
// WALL: frame sub 0x34 + saves ebx/esi/edi + local at [ebp-0x40] vs ours sub 0x30 + esi-only + [ebp-0x3C]; retail ebx/edi saved but never used.
// Tried: result-var, screen-var (plain + pre-init), early returns. Next: probe extra-block-scope temps or wrapper-struct locals.

// ?Rva003176B9@@YAPAXVAsciiString@@@Z @0x003176B9 190B (retail 0x003176B9..
// 0x00317776; the queue's 94B Ghidra boundary splits the head from its tail
// at 0x00317717). Loads the named layout into a local Rva0031763A parse
// struct via rowed WindowLayoutInfo::load 0x0031742C (by-value AsciiString
// temp through rowed StringBase copy 0x00365F0); the layout relationship is
// unproven (0x44 info vs 0x2C struct) so the call goes through a
// reinterpret_cast. load-false returns 0; otherwise the struct's +0x10 word
// is a factory: null makes a rowed BfmeQuickMatchScreenBase (0x24 via rowed
// operator new 0x2FDA0, rowed no-arg ctor 0x538C0E, rowed attach 0x538C6D),
// else the factory is called with the struct. Returns the object (esi).
class WindowLayoutInfo
{
public:
	bool load(AsciiString name);
};

class BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreenBase();
	void bfmeAttach(void *info);

private:
	unsigned char m_pad00[0x24];
};

typedef void *(*Rva003176B9Factory)(Rva0031763A *info);

void *Rva003176B9(AsciiString name)
{
	Rva0031763A info;
	if (!reinterpret_cast<WindowLayoutInfo *>(&info)->load(name))
		return 0;
	if (*(void **)((char *)&info + 0x10) == 0)
	{
		BfmeQuickMatchScreenBase *screen = new BfmeQuickMatchScreenBase;
		screen->bfmeAttach(&info);
		return screen;
	}
	return (*(Rva003176B9Factory *)((char *)&info + 0x10))(&info);
}
