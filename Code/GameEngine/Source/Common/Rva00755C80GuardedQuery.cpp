// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva00755C80GuardedQuery.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva00755C80@@YAXXZ 0x0007A75E (21B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// 0x00755C80 -- store a method result from a global pointer, or skip.
//
//     mov ecx,[GLOBAL_PTR] / test ecx,ecx / je end / call <ILT> /
//     mov [GLOBAL_RESULT],eax / end: ret
//
// Retail loads the pointer into ecx (8b 0d, 6 bytes) rather than the eax
// short form, which is what a thiscall on that pointer looks like. A free
// function under the same guard compiles to a1 and comes out one byte short.

class W3DHordeModelDrawManager
{
public:
	int rva0007A54B(void);
};

extern W3DHordeModelDrawManager *TheW3DHordeModelDrawManager;
extern int g_Va001FDEB0;

// @?Rva00755C80@@YAXXZ 0x00755C80
void Rva00755C80(void)
{
	if (TheW3DHordeModelDrawManager)
		g_Va001FDEB0 = TheW3DHordeModelDrawManager->rva0007A54B();
}
