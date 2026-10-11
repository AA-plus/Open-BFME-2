// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b5910.md plus retail only.
// No decoder source was consulted.
//
// VP6_SetPbParam (retail 0x001B5910, 432 bytes): dispatches on a command code
// (above 9 does nothing) to set the post-processing level, the CPU-free
// percentage, the clamps, the de-interlace and add-noise modes, or the
// reference frames of a decoder instance.

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
struct Rva009A9070Context;
struct Rva009A9070Source;
// SetAddNoiseMode at 0x001B6920 (VP6 clean room).
extern "C" void __cdecl SetAddNoiseMode(void *, int);
extern "C" void __cdecl CopyFrame(Rva009A9070Context *, Rva009A9070Source *, int);
extern "C" void __cdecl VP6_SetPbParam(void *context, unsigned selector, int value)
{
    if (selector > 9) return;
again:
    switch (selector) {
    case 1: {
        unsigned area = *(unsigned *)((char *)context + 0x1b4) * *(unsigned *)((char *)context + 0x1b0);
        double ratio = sqrt((double)area) / (double)((*(unsigned *)((char *)context + 0x1a4) * value) / 100u) * 100.0;
        *(int *)((char *)context + 0x1a8) = value;
        if (ratio > 150.0) *(int *)((char *)context + 0x1a0) = 0;
        else if (ratio > 100.0) *(int *)((char *)context + 0x1a0) = 8;
        else if (ratio > 90.0) *(int *)((char *)context + 0x1a0) = 4;
        else if (ratio > 80.0) *(int *)((char *)context + 0x1a0) = 5;
        else *(int *)((char *)context + 0x1a0) = 6;
        return;
    }
    case 9:
        *(int *)((char *)context + 0x4948) = value;
        SetAddNoiseMode(*(void **)((char *)context + 0x298), value);
        return;
    case 7:
        CopyFrame(*(Rva009A9070Context **)((char *)context + 0x298), (Rva009A9070Source *)value, *(int *)((char *)context + 0x254));
        CopyFrame(*(Rva009A9070Context **)((char *)context + 0x298), (Rva009A9070Source *)value, *(int *)((char *)context + 0x24c));
        return;
    case 0:
        if (value == 9) { value = 70; selector = 1; goto again; }
        *(int *)((char *)context + 0x1a0) = value;
        *(int *)((char *)context + 0x1a8) = 0;
        return;
    case 8: *(int *)((char *)context + 0x4944) = value; return;
    case 5: *(int *)((char *)context + 0x493c) = value; return;
    case 6: *(int *)((char *)context + 0x4940) = value; return;
    default: return;
    }
}
