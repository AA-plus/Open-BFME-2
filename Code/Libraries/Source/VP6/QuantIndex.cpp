// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7070.md 001b71c0.md plus retail
// only. No decoder source was consulted.
struct BfmeS1040;
extern "C" void __cdecl VP6_init_dequantizer(BfmeS1040 *s, int version); // 0x001B70A0
extern void (__cdecl *g_bfmeHook1040)(BfmeS1040 *s);   // 0x00E22F74

// 0x007D8560 identity index (ledger g_rva01142408), 0x007D8460 zig-zag order.
extern int g_rva01142408[];
extern unsigned int vp6DequantIndex[64];

struct Quantizer
{
	int frameQ;
	int quality;
	unsigned char pad0[0x30];
	int cached;
	int thresholds[64];
	int *index;
	unsigned char inverse[64];
};

// RVA 0x001B7070
extern "C" void __cdecl VP6_BuildQuantIndex_Generic(Quantizer *q)
{
	q->index = g_rva01142408;
	for (int i = 0; i < 64; ++i)
		q->inverse[vp6DequantIndex[i]] = (unsigned char)i;
}

// RVA 0x001B71C0: rebuild the index and dequantizer when the quality changed.
extern "C" void __cdecl VP6_UpdateQ(Quantizer *q, int version)
{
	if (q->thresholds[q->frameQ] != q->cached)
	{
		q->cached = q->quality;
		((void (__cdecl *)(Quantizer *))g_bfmeHook1040)(q);
		VP6_init_dequantizer((BfmeS1040 *)q, version);
	}
}
