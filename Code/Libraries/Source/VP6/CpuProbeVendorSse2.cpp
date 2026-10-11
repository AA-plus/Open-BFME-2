// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean room: reverse/vp6_cleanroom/specs/001d5470.md plus retail only. No
// decoder source was consulted.
//
// CpuProbe_VendorSse2 retail 0x001D5470 (208 bytes): returns 1 when the
// processor vendor string is GenuineIntel or AuthenticAMD and CPUID leaf 1
// reports SSE2 (EDX bit 26), else 0. The CPUID leaf 0 and 1 reads are inline
// assembly; the whole body sits in a structured exception frame whose filter
// always selects the handler (the handler returns 0), and the 208-byte row
// covers the filter and handler funclets retail places after the body.

#include <excpt.h>
extern "C" unsigned long __cdecl _exception_code(void);
#define GetExceptionCode _exception_code


extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *, const char *, unsigned int);

extern "C" int __cdecl CpuProbe_VendorSse2(void)
{
	char vendor[12];
	int result;

	result = 0;
	__try
	{
		__asm
		{
			lea	esi, vendor
			mov	eax, 0
			cpuid
			mov	dword ptr [esi], ebx
			mov	dword ptr [esi+4], edx
			mov	dword ptr [esi+8], ecx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		unsigned long code = GetExceptionCode();
		if (code)
			return result;
		return result;
	}

	if (strncmp(vendor, "GenuineIntel", 12) == 0
		|| strncmp(vendor, "AuthenticAMD", 12) == 0)
	{
		__asm
		{
			mov	eax, 1
			cpuid
			test	edx, 04000000h
			je	no_sse2
			mov	result, 1
		no_sse2:
			nop
		}
	}

	return result;
}
