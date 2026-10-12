// _MMX_idct10_DX
// partial score=0.1 date=2026-10-12
// cl: /O1 /G6 /DNDEBUG /MD
// Clean-Room: reverse/vp6_cleanroom/specs/001d4d50.md
// Additional permitted contract: reverse/vp6_cleanroom/specs/001d35e0.md.
// Implemented from those specs, all 1034 retail bytes, and the existing
// FillIdctConstants.cpp provider. No external decoder source was consulted.
// A readable MMX intrinsic draft; byte exactness is not yet established.
#include <mmintrin.h>

// Existing 96-byte global populated by fillidctconstants; no new data alias.
extern unsigned short Rva009B3A00Table[48];

static __forceinline __m64 cosineProduct(__m64 value, unsigned int word, bool addBack)
{
    __m64 result = _mm_mulhi_pi16(value, *reinterpret_cast<const __m64 *>(Rva009B3A00Table + word));
    return addBack ? _mm_add_pi16(result, value) : result;
}

static __forceinline void inverseFour(const __m64 input[4], __m64 output[8], bool round)
{
    __m64 odd17 = cosineProduct(input[1], 16, true);
    __m64 diff17 = cosineProduct(input[1], 40, false);
    __m64 odd35 = cosineProduct(input[3], 24, true);
    __m64 diff35 = _mm_subs_pi16(_mm_setzero_si64(), cosineProduct(input[3], 32, true));
    __m64 oddDS = _mm_subs_pi16(odd17, odd35);
    __m64 oddSS = _mm_adds_pi16(_mm_adds_pi16(odd35, odd35), oddDS);
    __m64 oddDM = _mm_subs_pi16(diff17, diff35);
    __m64 oddSM = _mm_adds_pi16(_mm_adds_pi16(diff35, diff35), oddDM);
    __m64 rotS = cosineProduct(oddDS, 28, true);
    __m64 rotM = cosineProduct(oddDM, 28, true);
    __m64 even = cosineProduct(input[0], 28, true);
    __m64 pairSum = cosineProduct(input[2], 20, true);
    __m64 pairDiff = cosineProduct(input[2], 36, false);
    __m64 eA = _mm_subs_pi16(even, pairSum);
    __m64 eB = _mm_adds_pi16(_mm_adds_pi16(pairSum, pairSum), eA);
    __m64 oA = _mm_subs_pi16(rotM, pairDiff);
    __m64 oB = _mm_adds_pi16(_mm_adds_pi16(pairDiff, pairDiff), oA);
    __m64 fA = _mm_subs_pi16(even, rotS);
    __m64 fB = _mm_adds_pi16(_mm_adds_pi16(rotS, rotS), fA);
    __m64 d7 = _mm_subs_pi16(eB, oddSS);
    __m64 d2 = _mm_subs_pi16(fB, oB);
    __m64 d4 = _mm_subs_pi16(eA, oddSM);
    __m64 d6 = _mm_subs_pi16(fA, oA);
    if (round) {
        const __m64 bias = *reinterpret_cast<const __m64 *>(Rva009B3A00Table + 44);
        d7 = _mm_adds_pi16(d7, bias);
        d2 = _mm_adds_pi16(d2, bias);
        d4 = _mm_adds_pi16(d4, bias);
        d6 = _mm_adds_pi16(d6, bias);
    }
    __m64 d0 = _mm_adds_pi16(_mm_adds_pi16(oddSS, oddSS), d7);
    __m64 d1 = _mm_adds_pi16(_mm_adds_pi16(oB, oB), d2);
    __m64 d3 = _mm_adds_pi16(_mm_adds_pi16(oddSM, oddSM), d4);
    __m64 d5 = _mm_adds_pi16(_mm_adds_pi16(oA, oA), d6);
    output[0] = round ? _mm_srai_pi16(d0, 4) : d0;
    output[1] = round ? _mm_srai_pi16(d1, 4) : d1;
    output[2] = round ? _mm_srai_pi16(d2, 4) : d2;
    output[3] = round ? _mm_srai_pi16(d3, 4) : d3;
    output[4] = round ? _mm_srai_pi16(d4, 4) : d4;
    output[5] = round ? _mm_srai_pi16(d5, 4) : d5;
    output[6] = round ? _mm_srai_pi16(d6, 4) : d6;
    output[7] = round ? _mm_srai_pi16(d7, 4) : d7;
}

static __forceinline void transposeFour(const __m64 input[4], __m64 *output, unsigned int step)
{
    __m64 abLow = _mm_unpacklo_pi16(input[0], input[1]);
    __m64 abHigh = _mm_unpackhi_pi16(input[0], input[1]);
    __m64 cdLow = _mm_unpacklo_pi16(input[2], input[3]);
    __m64 cdHigh = _mm_unpackhi_pi16(input[2], input[3]);
    output[0] = _mm_unpacklo_pi32(abLow, cdLow);
    output[step] = _mm_unpackhi_pi32(abLow, cdLow);
    output[2 * step] = _mm_unpacklo_pi32(abHigh, cdHigh);
    output[3 * step] = _mm_unpackhi_pi32(abHigh, cdHigh);
}

extern "C" void __cdecl MMX_idct10_DX(const short *input, const short *quantizer, short *output)
{
    // Force the six retail cache-touch reads. This is a reconstruction choice,
    // not evidence that the original output pointer was volatile-qualified.
    const volatile unsigned int *touch = reinterpret_cast<const volatile unsigned int *>(output);
    (void)touch[0]; (void)touch[7]; (void)touch[14];
    (void)touch[21]; (void)touch[28]; (void)touch[31];
    __m64 coefficients[4];
    coefficients[0] = _mm_mullo_pi16(*reinterpret_cast<const __m64 *>(input), *reinterpret_cast<const __m64 *>(quantizer));
    coefficients[1] = _mm_mullo_pi16(*reinterpret_cast<const __m64 *>(input + 8), *reinterpret_cast<const __m64 *>(quantizer + 8));
    coefficients[2] = _mm_mullo_pi16(*reinterpret_cast<const __m64 *>(input + 16), *reinterpret_cast<const __m64 *>(quantizer + 16));
    coefficients[3] = _mm_mullo_pi16(*reinterpret_cast<const __m64 *>(input + 24), *reinterpret_cast<const __m64 *>(quantizer + 24));
    __m64 *block = reinterpret_cast<__m64 *>(output);
    const __m64 zero = _mm_setzero_si64();
    block[0] = coefficients[0]; block[1] = zero;
    block[2] = coefficients[1]; block[3] = zero;
    block[4] = coefficients[2]; block[5] = zero;
    block[6] = coefficients[3]; block[7] = zero;
    block[8] = zero; block[9] = zero; block[10] = zero; block[11] = zero;
    block[12] = zero; block[13] = zero; block[14] = zero; block[15] = zero;
    __m64 rowResult[8];
    inverseFour(coefficients, rowResult, false);
    transposeFour(rowResult, block, 2);
    transposeFour(rowResult + 4, block + 1, 2);
    __m64 columnInput[4];
    __m64 columnResult[8];
    columnInput[0] = block[0]; columnInput[1] = block[2];
    columnInput[2] = block[4]; columnInput[3] = block[6];
    inverseFour(columnInput, columnResult, true);
    for (unsigned int row = 0; row != 8; ++row) block[2 * row] = columnResult[row];
    columnInput[0] = block[1]; columnInput[1] = block[3];
    columnInput[2] = block[5]; columnInput[3] = block[7];
    inverseFour(columnInput, columnResult, true);
    for (unsigned int row2 = 0; row2 != 8; ++row2) block[2 * row2 + 1] = columnResult[row2];
    // Leave the MMX state active, as retail does; the caller owns ClearMmx.
}
