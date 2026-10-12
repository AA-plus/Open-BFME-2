// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4440.md plus retail only.
// No decoder source was consulted.
//
// UtilMachineSpecificConfig (retail 0x001C4440, 766 bytes): cdecl and
// argument free. Probes the CPU tier with GetProcessorFlags and fills the
// two 65-entry IDCT dispatch tables plus twelve block-function globals for
// the WMT, MMX or generic tier. Every slot target and its order follow the
// spec.
//
// Installs the per-CPU-tier "spread table" function-pointer blob for the
// BFME video/image codec: two 65-slot arrays (offsets 0xA4 and 0x1C4 from
// this blob, indexed by byte offset 0..0x100 in steps of 4, split 2/9/54
// between a low-, mid- and tail-range filler) plus twelve individually
// named slots scattered through the same blob.  Sibling of the plain
// (non-looping) installer in PostProcMachineSpecificConfig.cpp: same
// GetProcessorFlags probe and same tier-C / tier-A / generic order,
// but this one only ever loads its filler set into two big arrays and a
// dozen named cells, never into the small dispatch table there.
//
// g_bfmeTableJX (retail 0x01356B60, pinned elsewhere as a plain int) is
// array1's first slot; every other field in the blob is reached by a
// constant byte offset from its address, since nothing else in the blob
// carries a name yet.

extern "C" void __cdecl GetProcessorFlags(int *pTierA, int *pTierB, int *pTierC);
extern int g_bfmeTableJX;

// Individually named blob cells (not part of either 65-slot array); no real
// identity yet, address-derived names, pinned in reverse/symbols.csv.
extern void *g_bfmeSlotABC;
// g_bfmeSlotABC: matched references place it at VA 0xe22d00 (zero-filled .bss).
void * g_bfmeSlotABC;
extern void *g_bfmeSlotB40;
extern void *g_bfmeSlotB44;
// g_bfmeSlotB44: matched references place it at VA 0xe22d0c (zero-filled .bss).
void * g_bfmeSlotB44;
extern void *g_bfmeSlotB48;
extern void *g_bfmeSlotB4C;
// g_bfmeSlotB4C: matched references place it at VA 0xe22d14 (zero-filled .bss).
void * g_bfmeSlotB4C;
extern void *g_bfmeSlotB50;
// g_bfmeSlotB50: matched references place it at VA 0xe22d18 (zero-filled .bss).
void * g_bfmeSlotB50;
extern void *g_bfmeSlotB54;
// g_bfmeSlotB54: matched references place it at VA 0xe22d1c (zero-filled .bss).
void * g_bfmeSlotB54;
extern void *g_bfmeSlotB58;
// g_bfmeSlotB58: matched references place it at VA 0xe22d20 (zero-filled .bss).
void * g_bfmeSlotB58;
extern void *g_bfmeSlotB5C;
// g_bfmeSlotB5C: matched references place it at VA 0xe22d24 (zero-filled .bss).
void * g_bfmeSlotB5C;
extern void *g_bfmeSlotD84;
// g_bfmeSlotD84: matched references place it at VA 0xe22f64 (zero-filled .bss).
void * g_bfmeSlotD84;
extern void *g_bfmeSlotD88;
// g_bfmeSlotD88: matched references place it at VA 0xe22f68 (zero-filled .bss).
void * g_bfmeSlotD88;
extern void *g_bfmeSlotD8C;
// g_bfmeSlotD8C: matched references place it at VA 0xe22f6c (zero-filled .bss).
void * g_bfmeSlotD8C;

// Landed callees, declared with their real signatures so the mangled name
// matches their existing row.
extern "C" void __cdecl UnpackBlock_C(const unsigned char *, unsigned short *, int);
extern "C" void __cdecl AverageBlock_MMX(const void *, const void *, void *, int);

// VP6 block reconstruction helpers recovered from the clean-room specs
// (Code/Libraries/Source/VP6/ReconMmx.cpp and ReconWmt.cpp), declared with
// the extern "C" signatures those units define.
extern "C" void __cdecl MMXReconIntra(void *, unsigned char *, const short *, unsigned int);
extern "C" void __cdecl MmxReconInter(void *, unsigned char *, const unsigned char *, const short *, unsigned int);
extern "C" void __cdecl Copy12x12_MMX(const unsigned char *, unsigned char *, unsigned int, unsigned int);
extern "C" void __cdecl UnpackBlock_MMX(const unsigned char *, short *, unsigned int);
extern "C" void __cdecl SubtractBlock_MMX(const unsigned char *, short *, unsigned int);
extern "C" void __cdecl ReconBlock_MMX(const short *, const short *, unsigned char *, unsigned int);
extern "C" void __cdecl WmtReconIntra(void *, unsigned char *, const short *, unsigned int);
extern "C" void __cdecl WmtReconInter(void *, unsigned char *, const unsigned char *, const short *, unsigned int);

// Unconverted gen-dump callees that already carry a functions.csv row (the
// row is the candidate; no new pin needed).
extern "C" void __cdecl ScalarReconInterHalfPixel2(void);
extern "C" void __cdecl MmxReconInterHalfPixel2(void *, void *, const void *, const void *, const void *, int);
extern "C" void __cdecl CopyBlockMMX(const void *, void *, int);
extern void __cdecl d_009c74f0(void);
extern "C" void __cdecl WmtReconInterHalfPixel2(void *, void *, const void *, const void *, const void *, int);
extern "C" void __cdecl Wmt_IDct10_Dx(const void *, const void *, void *);

// Slot fillers with neither a real identity nor a ghidra-boundary row yet;
// address-derived names, pinned in reverse/symbols.csv.
extern "C" void __cdecl FilterBlockBil_8_wmt(void);
extern "C" void __cdecl FilterBlockBil_8_mmx(void);
extern void __cdecl Rva009A8110(void);
extern void __cdecl Rva009A74D0(void);
extern void __cdecl Rva009C6D20(void);
extern void __cdecl Rva009A7030(void);
extern "C" void __cdecl AverageBlock_C(void);
extern "C" void __cdecl FilterBlock_mmx(void *, void *, void *, int, int, int, int);
extern "C" void __cdecl FilterBlock_C(const unsigned char *, const unsigned char *, unsigned short *, unsigned int, int, int, int);
extern "C" void __cdecl SubtractBlock_C(void);
extern "C" void __cdecl ScalarReconInter(void);
extern "C" void __cdecl ReconBlock_C(void);
extern "C" void __cdecl ScalarReconIntra(short *, unsigned char *, const short *, int);
extern void __cdecl Rva009C80C0(void);
extern "C" void __cdecl Wmt_IDct_Dx(const void *, const void *, void *);
extern "C" void __cdecl MMX_idct10(void);
extern "C" void __cdecl MMX_idct(void);
extern "C" void __cdecl MMX_idct1(void);
extern "C" void __cdecl MMX_idct10_DX(void);
extern "C" void __cdecl MMX_idct_DX(void);
extern void __cdecl Rva009C6360(void);
extern void __cdecl Rva009C5D60(void);
extern void __cdecl Rva009C5890(void);

typedef void (__cdecl *BfmeSpreadFn)();

extern "C" void __cdecl UtilMachineSpecificConfig(void)
{
	int tierA, tierB, tierC;
	unsigned int i;

	GetProcessorFlags(&tierA, &tierB, &tierC);

	if (tierC)
	{
		BfmeSpreadFn low = (BfmeSpreadFn)&Rva009C80C0;
		BfmeSpreadFn mid = (BfmeSpreadFn)&Wmt_IDct10_Dx;
		BfmeSpreadFn tail = (BfmeSpreadFn)&Wmt_IDct_Dx;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = tail;
		}

		mid = (BfmeSpreadFn)&MMX_idct10;
		tail = (BfmeSpreadFn)&MMX_idct;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = tail;
		}

		g_bfmeSlotD8C = (void *)&WmtReconIntra;
		g_bfmeSlotD84 = (void *)&WmtReconInter;
		g_bfmeSlotB58 = (void *)&WmtReconInterHalfPixel2;
		g_bfmeSlotB48 = (void *)&Rva009C6D20;
		g_bfmeSlotB4C = (void *)&AverageBlock_MMX;
		g_bfmeSlotB50 = (void *)&UnpackBlock_MMX;
		g_bfmeSlotD88 = (void *)&ReconBlock_MMX;
		g_bfmeSlotB5C = (void *)&SubtractBlock_MMX;
		g_bfmeSlotB44 = (void *)&CopyBlockMMX;
		g_bfmeSlotABC = (void *)&FilterBlockBil_8_wmt;
		g_bfmeSlotB54 = (void *)&d_009c74f0;
		g_bfmeSlotB40 = (void *)&Copy12x12_MMX;
		return;
	}

	if (tierA)
	{
		BfmeSpreadFn low = (BfmeSpreadFn)&MMX_idct1;
		BfmeSpreadFn mid = (BfmeSpreadFn)&MMX_idct10;
		BfmeSpreadFn tail = (BfmeSpreadFn)&MMX_idct;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120 + i) = tail;
		}

		mid = (BfmeSpreadFn)&MMX_idct10_DX;
		tail = (BfmeSpreadFn)&MMX_idct_DX;

		for (i = 0; i <= 0x100; i += 4) {
			if (i <= 4)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = low;
			else if (i <= 0x28)
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = mid;
			else
				*(BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0 + i) = tail;
		}

		g_bfmeSlotD8C = (void *)&MMXReconIntra;
		g_bfmeSlotD84 = (void *)&MmxReconInter;
		g_bfmeSlotB58 = (void *)&MmxReconInterHalfPixel2;
		g_bfmeSlotB48 = (void *)&Rva009C6D20;
		g_bfmeSlotB4C = (void *)&AverageBlock_MMX;
		g_bfmeSlotB50 = (void *)&UnpackBlock_MMX;
		g_bfmeSlotD88 = (void *)&ReconBlock_MMX;
		g_bfmeSlotB5C = (void *)&SubtractBlock_MMX;
		g_bfmeSlotB44 = (void *)&CopyBlockMMX;
		g_bfmeSlotABC = (void *)&FilterBlockBil_8_mmx;
		g_bfmeSlotB54 = (void *)&FilterBlock_mmx;
		g_bfmeSlotB40 = (void *)&Copy12x12_MMX;
		return;
	}

	{
		BfmeSpreadFn low = (BfmeSpreadFn)&Rva009C6360;
		BfmeSpreadFn mid = (BfmeSpreadFn)&Rva009C5D60;
		BfmeSpreadFn tail = (BfmeSpreadFn)&Rva009C5890;
		BfmeSpreadFn *cell;

		for (cell = (BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x120);
		     (int)cell <= (int)((char *)&g_bfmeTableJX + 0x220);
		     cell = (BfmeSpreadFn *)((char *)cell + 4)) {
			if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x124))
				*cell = low;
			else if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x148))
				*cell = mid;
			else
				*cell = tail;
		}

		for (cell = (BfmeSpreadFn *)((char *)&g_bfmeTableJX + 0x0);
		     (int)cell <= (int)((char *)&g_bfmeTableJX + 0x100);
		     cell = (BfmeSpreadFn *)((char *)cell + 4)) {
			if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x4))
				*cell = low;
			else if ((int)cell <= (int)((char *)&g_bfmeTableJX + 0x28))
				*cell = mid;
			else
				*cell = tail;
		}

		g_bfmeSlotB48 = (void *)&Rva009A7030;
		g_bfmeSlotD8C = (void *)&ScalarReconIntra;
		g_bfmeSlotD84 = (void *)&ScalarReconInter;
		g_bfmeSlotB58 = (void *)&ScalarReconInterHalfPixel2;
		g_bfmeSlotB4C = (void *)&AverageBlock_C;
		g_bfmeSlotB50 = (void *)&UnpackBlock_C;
		g_bfmeSlotD88 = (void *)&ReconBlock_C;
		g_bfmeSlotB5C = (void *)&SubtractBlock_C;
		g_bfmeSlotB44 = (void *)&Rva009A74D0;
		g_bfmeSlotABC = (void *)&Rva009A8110;
		g_bfmeSlotB54 = (void *)&FilterBlock_C;
		g_bfmeSlotB40 = (void *)&Copy12x12_MMX;
	}
}

// ?g_bfmeSlotB40@@3PAXA: matched references place it at VA 0xe22d08; also referenced as ?g_rva01356B40@@3P6AXPAX0HH@ZA.
void * g_bfmeSlotB40 = 0;
#pragma comment(linker, "/alternatename:?g_rva01356B40@@3P6AXPAX0HH@ZA=?g_bfmeSlotB40@@3PAXA")
// ?g_bfmeSlotB48@@3PAXA: matched references place it at VA 0xe22d10; also referenced as ?g_bfmeToneReady@@3P6AXXZA.
void * g_bfmeSlotB48 = 0;
#pragma comment(linker, "/alternatename:?g_bfmeToneReady@@3P6AXXZA=?g_bfmeSlotB48@@3PAXA")
