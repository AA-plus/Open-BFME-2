// Installs per-CPU-tier function pointers into the BFME video/image codec
// dispatch table: 26 contiguous slots plus one standalone outlier slot.
// Probes the tier via GetProcessorFlags (0x009B3A90, parked partial --
// declared extern and pinned since a pin does not require the callee to be
// converted): the SSE tier (top flag set) expands the loop-filter limit
// table for the SIMD filters (FillLoopFilterLimitValues_MMX) and installs the
// full SIMD set; the MMX tier (basic flag set) does the same expansion and
// installs the MMX-only set (mostly shared with the SSE tier); otherwise the
// generic scalar/table-driven set installs directly with no expansion.
// Sibling of bfmeFilterPairMmx, bfmeExpandMmx, the *FastDeInterlace family and
// BfmeLimitedEdgeFilters.cpp.

extern "C" void __cdecl GetProcessorFlags(int *pTierA, int *pTierB, int *pTierC);

// VP6 clean-room bodies (Code/Libraries/Source/VP6/), declared with the
// extern "C" signatures those units define.
struct POSTPROC_INSTANCE;
extern "C" void __cdecl FillLoopFilterLimitValues_MMX(void);
extern "C" int *__cdecl SetupDeblockValueArray_ForMMX(POSTPROC_INSTANCE *, int);
extern "C" int *__cdecl SetupBoundingValueArray_ForMMX(POSTPROC_INSTANCE *, int);
extern "C" void __cdecl LastVerticalBand_1_2_Scale_MMX(unsigned char *, unsigned int, unsigned int);

// Landed siblings, declared with their real signatures so the mangled name
// matches their existing row.
extern void __cdecl bfmeFilterPairMmx(void *, void *, int, const void *);
extern void __cdecl bfmeExpandMmx(const void *, int, void *);
extern "C" void __cdecl HorizontalLine_1_2_Scale_C(const void *, int, void *, int);
extern void __cdecl bfmeExpand3to5Mmx(const void *, int, void *);
extern void __cdecl bfmeExpand4to5Mmx(const void *, int, void *);
extern "C" void __cdecl VerticalBand_1_2_Scale_MMX(void *, int, int);
extern void __cdecl bfmeInterpRows6Mmx(void *, int, int);
extern void __cdecl bfmeInterpRows2Mmx(void *, int, int);
extern void __cdecl bfmeInterpRows5Mmx(void *, int, int);
extern void __cdecl bfmeInterpRowsMmx(void *, int, int);
extern "C" void __cdecl WmtFastDeInterlace(void *, void *, unsigned int, int, int);
extern "C" void __cdecl MmxFastDeInterlace(void *, void *, unsigned int, int, int);
extern "C" void __cdecl CFastDeInterlace(void *, void *, unsigned int, int, int);
extern void __cdecl Rva009AF570FilterVert(void *, unsigned char *, int, const int *);
extern void __cdecl Rva009AF6A0FilterHoriz(void *, unsigned char *, int, const int *);
extern "C" int * __cdecl SetupBoundingValueArray_Generic(POSTPROC_INSTANCE *, int);
extern "C" int * __cdecl SetupDeblockValueArray_Generic(POSTPROC_INSTANCE *, int);
extern void __cdecl Rva009B3650FilterVert(void *, unsigned char *, int, const int *);
extern void __cdecl Rva009B3710FilterHoriz(void *, unsigned char *, int, const int *);
extern void __cdecl Rva009AF840FilterVert(int, unsigned char *, int);
extern void __cdecl Rva009AFA60FilterHoriz(int, unsigned char *, int);
extern void __cdecl Rva009AFCA0FilterVert(int, unsigned char *, int);
extern void __cdecl Rva009AFEC0FilterHoriz(int, unsigned char *, int);

// Unconverted gen-dump callees that already carry a functions.csv row (the
// row is the candidate; no new pin needed).
extern void __cdecl bfmeFilterBlockMmx(void *, void *, int, void *);
extern "C" void __cdecl Rva009C2620Vp6FilterDiag4(void *, void *, void *, int, int, int *);
extern "C" void __cdecl Rva009C2320Vp6FilterDiag4(void *, void *, void *, int, int, int *);
extern void __cdecl d_009bebb0(void);
extern void __cdecl d_009bfa40(void);
extern void __cdecl d_009b9700(void);
extern void __cdecl d_009c1ed0(void);
struct Rva009C2170Ctx;
extern void __cdecl bfmeDeblockEdgeByIndexMmx(Rva009C2170Ctx *, void *, int);
extern void __cdecl bfmeFilterBlockByIndexMmx(int, void *, int);
extern void __cdecl bfmeFilterBlockPairByIndexMmx(int, void *, int);
extern void __cdecl bfmeFilterRowByIndex8Mmx(int, void *, int);
extern void __cdecl bfmeFilterRowByIndex12Mmx(int, void *, int);
extern void __cdecl d_009bd470(void);
extern "C" void __cdecl Rva009BD470Vp6FilterSse(void *, void *, void *, int, int);
extern void __cdecl d_009c0a30(void);
extern "C" void __cdecl Rva009BE180Vp6FilterWideV2(void *, void *, void *, int, int, int *);
extern "C" void __cdecl Rva009BD750Vp6FilterWide(void *, void *, void *, int, int, int *);
extern void __cdecl d_009b8130(void);
extern void __cdecl d_009a5f50(void);

// Slot fillers with neither a real identity nor a ghidra-boundary row yet;
// address-derived names, pinned in reverse/symbols.csv.
extern void __cdecl Rva009B6D80(void);
extern void __cdecl Rva009BD570(void);
extern "C" void __cdecl Rva009BA790(void);
extern void __cdecl Rva009B18D0(void);
extern void __cdecl Rva009B10E0(void);
extern void __cdecl Rva009ACF90(void);
extern void __cdecl Rva009ADD80(void);
extern void __cdecl Rva009AE6A0(void);
extern "C" void __cdecl VerticalBand_1_2_Scale_C(unsigned char *, int, unsigned int);
extern "C" void __cdecl LastVerticalBand_1_2_Scale_C(unsigned char *, int, unsigned int);
extern void __cdecl Rva009A9550(const void *, int, void *);
extern void __cdecl Rva009A9660(unsigned char *, int, unsigned int);
extern void __cdecl Rva009A9720(unsigned char *, int, unsigned int);
extern void __cdecl Rva009A91D0(void);
extern void __cdecl Rva009A92D0(unsigned char *, int, unsigned int);
extern void __cdecl Rva009A9370(void);
extern "C" void __cdecl ClampLevels_C(void *, int, int, int, int);

typedef void (__cdecl *BfmeDispatchFn)();

struct BfmeCodecDispatchTable
{
	BfmeDispatchFn slot[26];
};

// Shared by the native post-filter dispatcher: table base VA 0x00E22F7C.
BfmeCodecDispatchTable g_bfmeCodecDispatch;
static BfmeDispatchFn g_bfmeCodecDispatchOutlier;

void __cdecl bfmeInstallCpuDispatchTable(void)
{
	int tierA, tierB, tierC;
	GetProcessorFlags(&tierA, &tierB, &tierC);
	if (tierC)
	{
		FillLoopFilterLimitValues_MMX();
		g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&bfmeFilterBlockMmx;
		g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&bfmeFilterPairMmx;
		g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&SetupBoundingValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&SetupDeblockValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&Rva009C2620Vp6FilterDiag4;
		g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&Rva009C2320Vp6FilterDiag4;
		g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&d_009bebb0;
		g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&d_009bfa40;
		g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&d_009b9700;
		g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&d_009c1ed0;
		g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&bfmeDeblockEdgeByIndexMmx;
		g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&bfmeExpandMmx;
		g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&bfmeExpand3to5Mmx;
		g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&bfmeExpand4to5Mmx;
		g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&VerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&LastVerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&bfmeInterpRows6Mmx;
		g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&bfmeInterpRows2Mmx;
		g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&bfmeInterpRows5Mmx;
		g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&bfmeInterpRowsMmx;
		g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&bfmeFilterBlockByIndexMmx;
		g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&bfmeFilterRowByIndex8Mmx;
		g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&bfmeFilterBlockPairByIndexMmx;
		g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&bfmeFilterRowByIndex12Mmx;
		g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&WmtFastDeInterlace;
		g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&Rva009BD470Vp6FilterSse;
		g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&d_009c0a30;
		return;
	}
	if (tierA)
	{
		FillLoopFilterLimitValues_MMX();
		g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&bfmeFilterBlockMmx;
		g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&bfmeFilterPairMmx;
		g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&SetupBoundingValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&SetupDeblockValueArray_ForMMX;
		g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&Rva009BE180Vp6FilterWideV2;
		g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&Rva009BD750Vp6FilterWide;
		g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&Rva009B6D80;
		g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&d_009b8130;
		g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&d_009b9700;
		g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&d_009c1ed0;
		g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&bfmeDeblockEdgeByIndexMmx;
		g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&bfmeExpandMmx;
		g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&bfmeExpand3to5Mmx;
		g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&bfmeExpand4to5Mmx;
		g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&VerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&LastVerticalBand_1_2_Scale_MMX;
		g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&bfmeInterpRows6Mmx;
		g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&bfmeInterpRows2Mmx;
		g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&bfmeInterpRows5Mmx;
		g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&bfmeInterpRowsMmx;
		g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&bfmeFilterBlockByIndexMmx;
		g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&bfmeFilterRowByIndex8Mmx;
		g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&bfmeFilterBlockPairByIndexMmx;
		g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&bfmeFilterRowByIndex12Mmx;
		g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&MmxFastDeInterlace;
		g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&Rva009BD570;
		g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&Rva009BA790;
		return;
	}
	g_bfmeCodecDispatch.slot[15] = (BfmeDispatchFn)&Rva009AF570FilterVert;
	g_bfmeCodecDispatch.slot[23] = (BfmeDispatchFn)&Rva009AF6A0FilterHoriz;
	g_bfmeCodecDispatch.slot[2] = (BfmeDispatchFn)&SetupBoundingValueArray_Generic;
	g_bfmeCodecDispatch.slot[1] = (BfmeDispatchFn)&SetupDeblockValueArray_Generic;
	g_bfmeCodecDispatch.slot[16] = (BfmeDispatchFn)&Rva009B18D0;
	g_bfmeCodecDispatch.slot[24] = (BfmeDispatchFn)&Rva009B10E0;
	g_bfmeCodecDispatch.slot[10] = (BfmeDispatchFn)&Rva009ACF90;
	g_bfmeCodecDispatch.slot[13] = (BfmeDispatchFn)&Rva009ADD80;
	g_bfmeCodecDispatch.slot[21] = (BfmeDispatchFn)&Rva009AE6A0;
	g_bfmeCodecDispatch.slot[9] = (BfmeDispatchFn)&Rva009B3650FilterVert;
	g_bfmeCodecDispatch.slot[25] = (BfmeDispatchFn)&Rva009B3710FilterHoriz;
	g_bfmeCodecDispatch.slot[8] = (BfmeDispatchFn)&HorizontalLine_1_2_Scale_C;
	g_bfmeCodecDispatch.slot[4] = (BfmeDispatchFn)&VerticalBand_1_2_Scale_C;
	g_bfmeCodecDispatch.slot[17] = (BfmeDispatchFn)&LastVerticalBand_1_2_Scale_C;
	g_bfmeCodecDispatch.slot[20] = (BfmeDispatchFn)&Rva009A9550;
	g_bfmeCodecDispatch.slot[18] = (BfmeDispatchFn)&Rva009A9660;
	g_bfmeCodecDispatch.slot[12] = (BfmeDispatchFn)&Rva009A9720;
	g_bfmeCodecDispatchOutlier = (BfmeDispatchFn)&Rva009A91D0;
	g_bfmeCodecDispatch.slot[7] = (BfmeDispatchFn)&Rva009A92D0;
	g_bfmeCodecDispatch.slot[6] = (BfmeDispatchFn)&Rva009A9370;
	g_bfmeCodecDispatch.slot[22] = (BfmeDispatchFn)&Rva009AF840FilterVert;
	g_bfmeCodecDispatch.slot[5] = (BfmeDispatchFn)&Rva009AFA60FilterHoriz;
	g_bfmeCodecDispatch.slot[11] = (BfmeDispatchFn)&Rva009AFCA0FilterVert;
	g_bfmeCodecDispatch.slot[14] = (BfmeDispatchFn)&Rva009AFEC0FilterHoriz;
	g_bfmeCodecDispatch.slot[3] = (BfmeDispatchFn)&CFastDeInterlace;
	g_bfmeCodecDispatch.slot[19] = (BfmeDispatchFn)&ClampLevels_C;
	g_bfmeCodecDispatch.slot[0] = (BfmeDispatchFn)&d_009a5f50;
}

// Retail 0x001B9D10, 157 bytes. Demo relocation mapping recovers the
// missing start; dispatch slot 7 supplies the callback identity. Layout and
// weights follow retail loads and stores; the already-matched slot 6 scalar
// interpolator is the source-shape guide. This five-row variant interpolates
// between rows 0 and 5 rather than copying its final output row. The old
// address-derived donor spelling does not assert an original source name.
void __cdecl Rva009A92D0(unsigned char *source, int stride, unsigned int bytes)
{
    unsigned char *cursor = source;
    while (bytes > 0)
    {
        unsigned int second = cursor[stride];
        unsigned int first = cursor[0];
        unsigned int firstWeight = first * 51;
        unsigned int secondWeight = second * 205;
        cursor[stride] = (unsigned char)((firstWeight + secondWeight + 128) >> 8);
        unsigned int fourth;
        unsigned int third;
        third = cursor[stride * 2];
        unsigned int thirdWeight = third * 154;
        fourth = cursor[stride * 3];
        cursor[stride * 2] = (unsigned char)((second * 102 + thirdWeight + 128) >> 8);
        cursor[stride * 3] = (unsigned char)((fourth * 102 + thirdWeight + 128) >> 8);
        cursor[stride * 4] = (unsigned char)((cursor[stride * 5] * 51 + fourth * 205 + 128) >> 8);
        ++cursor;
        --bytes;
    }
}
