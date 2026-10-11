// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4390.md plus retail only.
// No decoder source was consulted.
// GetProcessorFlags retail 0x001C4390 (169 bytes: the code to the ret at
// 0x001C441B, then its 4-entry jump table and 13-byte class table). Asks the
// CPU identification routine (retail 0x001D5470, non-zero when the SSE2 class
// is detected) for a processor type index (12 when it returns non-zero, else
// 1) and writes the MMX, XMM and WMT flags that the index selects. The
// selector cases are spelled out so the compiler regenerates both tables.

extern "C" int __cdecl CpuProbe_VendorSse2(void);

extern "C" void __cdecl GetProcessorFlags(int *mmxFlag, int *xmmFlag, int *wmtFlag)
{
	unsigned int processorType = 1;
	if (CpuProbe_VendorSse2())
		processorType = 0xc;
	switch (processorType)
	{
	case 0: case 2: case 4: case 5: case 8: case 9: case 10:
		*mmxFlag = 0;
		*xmmFlag = 0;
		*wmtFlag = 0;
		break;
	case 1: case 3: case 6: case 7:
		*mmxFlag = 1;
		*xmmFlag = 0;
		*wmtFlag = 0;
		break;
	case 11:
		*mmxFlag = 1;
		*xmmFlag = 1;
		*wmtFlag = 0;
		break;
	case 12:
		*mmxFlag = 1;
		*xmmFlag = 1;
		*wmtFlag = 1;
		break;
	}
}
