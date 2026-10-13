// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva00270190Free@@YAXXZ, retail 0x00270190, 24 bytes. Leaf lane.
// Frees global Drawable::s_animationTemplates (data 0x009FEB78) via rowed ??_V@YAXPAX@Z
// (operator delete[] in mem_ops.cpp) when nonzero, then zeroes it.
// /O1 gives and [m],0 and pop-ecx cleanup. Caller is unclaimed
// Catch@00630412 62B. Flags copied from next Rva002701F4Ctor.cpp (/O1).

// Drawable::s_animationTemplates: matched references place it at VA 0xdfeb78 (retail .data initial value 0).
// The object is the 0x38-byte Anim2D node array that Rva00274E7DInit.cpp fills
// in, so it is defined here under the array spelling that unit reads it through
// under the same private Drawable static member: one object and one name. A
// `void *` spelling here would leave the array unit's references unresolved.
struct Rva002D752DNode;
// Table role is independently witnessed by the named icon-template string
// initializer 274E7D; s_animationTemplates is the ZH donor spelling.
class Drawable {
    friend void Rva00270190Free();
    static Rva002D752DNode **s_animationTemplates;
};
Rva002D752DNode **Drawable::s_animationTemplates = 0;
extern void __cdecl operator delete[](void *p);

void __cdecl Rva00270190Free()
{
	if (Drawable::s_animationTemplates)
	{
		operator delete[](Drawable::s_animationTemplates);
		Drawable::s_animationTemplates = 0;
	}
}
