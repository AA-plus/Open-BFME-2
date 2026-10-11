// cl: /EHsc
// Clean room: reverse/vp6_cleanroom/specs/001d5540.md plus retail only.
// No decoder source was consulted.
// CpuProbe_Sse2Executes retail 0x001D5540 (126 bytes): runs one SSE2
// instruction inside a structured exception frame; 1 when it executes, 0 when
// it faults. Unreferenced in retail.
#include <excpt.h>

extern "C" int __cdecl CpuProbe_Sse2Executes(void)
{
	// Retail's SEH funclets read the exception code into and back out of this
	// local before the handler returns zero.
	volatile unsigned int code;
	__try {
		__asm { xorpd xmm0, xmm0 }
	} __except ((code = *(*(unsigned int **)GetExceptionInformation()),
			EXCEPTION_EXECUTE_HANDLER)) {
		(void)code;
		return 0;
	}
	return 1;
}
