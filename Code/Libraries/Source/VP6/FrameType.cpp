// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bd570.md and 001bd580.md plus
// retail only. No decoder source was consulted.
// Native 1BD570..1BD57E and 1BD580..1BD58A: cdecl leaf accessors of the
// decoder instance's frame type byte at +0x1AC (also written by the frame
// header reader at 0x001BD050).
struct PB_INSTANCE
{
	unsigned char pad0[0x1AC];
	unsigned char frameType;
};

// RVA 0x001BD570..0x001BD57E: store the frame type byte.
extern "C" void __cdecl VP6_SetFrameType(PB_INSTANCE *pbi, unsigned char frameType)
{
	pbi->frameType = frameType;
}

// RVA 0x001BD580..0x001BD58A: return the frame type byte in AL.
extern "C" unsigned char __cdecl VP6_GetFrameType(PB_INSTANCE *pbi)
{
	return pbi->frameType;
}
