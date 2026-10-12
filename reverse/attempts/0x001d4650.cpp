// MMX_idct_DX
// partial score=0.112288967412642 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d4650.md and retail only.
// Full 1777-byte target, not byte exact. No decoder source consulted.
// Native uses 4x4 quadrant-transposed coefficient storage, all 64 products,
// four parallel rows at a time, then four parallel columns at a time.
#include <mmintrin.h>
extern unsigned short Rva009B3A00Table[48];

static __forceinline __m64 constant4(int cosine)
{
    return *reinterpret_cast<const __m64 *>(Rva009B3A00Table + 16 + 4 * cosine);
}

static __forceinline __m64 multiply4(__m64 value, int cosine)
{
    __m64 product = _mm_mulhi_pi16(value, constant4(cosine));
    return cosine < 5 ? _mm_add_pi16(product, value) : product;
}

static __forceinline void pair4(__m64 left, __m64 right, bool rounded,
                               __m64 &difference, __m64 &sum)
{
    difference = _mm_subs_pi16(left, right);
    if (rounded)
        difference = _mm_adds_pi16(difference,
            *reinterpret_cast<const __m64 *>(Rva009B3A00Table + 44));
    sum = _mm_adds_pi16(_mm_adds_pi16(right, right), difference);
    if (rounded) {
        difference = _mm_srai_pi16(difference, 4);
        sum = _mm_srai_pi16(sum, 4);
    }
}

static __forceinline void inverse4(const __m64 input[8], __m64 output[8], bool rounded)
{
    __m64 oddSum17 = _mm_adds_pi16(multiply4(input[1], 0), multiply4(input[7], 6));
    __m64 oddDiff17 = _mm_subs_pi16(multiply4(input[1], 6), multiply4(input[7], 0));
    __m64 oddSum35 = _mm_adds_pi16(multiply4(input[3], 2), multiply4(input[5], 4));
    __m64 oddDiff35 = _mm_subs_pi16(multiply4(input[5], 2), multiply4(input[3], 4));
    __m64 oddDS = _mm_subs_pi16(oddSum17, oddSum35);
    __m64 oddSS = _mm_adds_pi16(_mm_adds_pi16(oddSum35, oddSum35), oddDS);
    __m64 oddDM = _mm_subs_pi16(oddDiff17, oddDiff35);
    __m64 oddSM = _mm_adds_pi16(_mm_adds_pi16(oddDiff35, oddDiff35), oddDM);
    __m64 rotS = multiply4(oddDS, 3);
    __m64 rotM = multiply4(oddDM, 3);
    __m64 evenDiff = _mm_subs_pi16(input[0], input[4]);
    __m64 evenSum = _mm_adds_pi16(_mm_adds_pi16(input[4], input[4]), evenDiff);
    __m64 rotEvenSum = multiply4(evenSum, 3);
    // Native MMX uses saturating, rather than wrapping, add-back here.
    __m64 rotEvenDiff = _mm_adds_pi16(_mm_mulhi_pi16(evenDiff, constant4(3)), evenDiff);
    __m64 pairSum26 = _mm_adds_pi16(multiply4(input[6], 5), multiply4(input[2], 1));
    __m64 pairDiff26 = _mm_subs_pi16(multiply4(input[2], 5), multiply4(input[6], 1));
    __m64 eA = _mm_subs_pi16(rotEvenSum, pairSum26);
    __m64 eB = _mm_adds_pi16(_mm_adds_pi16(pairSum26, pairSum26), eA);
    __m64 oA = _mm_subs_pi16(rotM, pairDiff26);
    __m64 oB = _mm_adds_pi16(_mm_adds_pi16(pairDiff26, pairDiff26), oA);
    __m64 fA = _mm_subs_pi16(rotEvenDiff, rotS);
    __m64 fB = _mm_adds_pi16(_mm_adds_pi16(rotS, rotS), fA);
    pair4(eB, oddSS, rounded, output[7], output[0]);
    pair4(fB, oB, rounded, output[2], output[1]);
    pair4(eA, oddSM, rounded, output[4], output[3]);
    pair4(fA, oA, rounded, output[6], output[5]);
}

static __forceinline void transpose4(const __m64 &a, const __m64 &b,
                                    const __m64 &c, const __m64 &d,
                                    __m64 *destination)
{
    __m64 abLow = _mm_unpacklo_pi16(a, b), abHigh = _mm_unpackhi_pi16(a, b);
    __m64 cdLow = _mm_unpacklo_pi16(c, d), cdHigh = _mm_unpackhi_pi16(c, d);
    destination[0] = _mm_unpacklo_pi32(abLow, cdLow);
    destination[2] = _mm_unpackhi_pi32(abLow, cdLow);
    destination[4] = _mm_unpacklo_pi32(abHigh, cdHigh);
    destination[6] = _mm_unpackhi_pi32(abHigh, cdHigh);
}

extern "C" void __cdecl MMX_idct_DX(const short *coefficients,
                                    const short *quantiser, short *result)
{
    // Retail touches six working-buffer words before dequantisation. Volatile
    // expresses those reads; it is a reconstruction choice, not source proof.
    volatile const int *touch = reinterpret_cast<volatile const int *>(result);
    (void)touch[0]; (void)touch[7]; (void)touch[14];
    (void)touch[21]; (void)touch[28]; (void)touch[31];
    const __m64 *input = reinterpret_cast<const __m64 *>(coefficients);
    const __m64 *quant = reinterpret_cast<const __m64 *>(quantiser);
    __m64 *work = reinterpret_cast<__m64 *>(result);
    // Load each half completely before storing: native reads all eight vectors
    // before writing that half, including when output aliases either input.
    __m64 p0 = _mm_mullo_pi16(input[0], quant[0]);
    __m64 p1 = _mm_mullo_pi16(input[1], quant[1]);
    __m64 p2 = _mm_mullo_pi16(input[2], quant[2]);
    __m64 p3 = _mm_mullo_pi16(input[3], quant[3]);
    __m64 p4 = _mm_mullo_pi16(input[4], quant[4]);
    __m64 p5 = _mm_mullo_pi16(input[5], quant[5]);
    __m64 p6 = _mm_mullo_pi16(input[6], quant[6]);
    __m64 p7 = _mm_mullo_pi16(input[7], quant[7]);
    work[0]=p0; work[1]=p1; work[2]=p2; work[3]=p3;
    work[4]=p4; work[5]=p5; work[6]=p6; work[7]=p7;
    p0 = _mm_mullo_pi16(input[8], quant[8]);
    p1 = _mm_mullo_pi16(input[9], quant[9]);
    p2 = _mm_mullo_pi16(input[10], quant[10]);
    p3 = _mm_mullo_pi16(input[11], quant[11]);
    p4 = _mm_mullo_pi16(input[12], quant[12]);
    p5 = _mm_mullo_pi16(input[13], quant[13]);
    p6 = _mm_mullo_pi16(input[14], quant[14]);
    p7 = _mm_mullo_pi16(input[15], quant[15]);
    work[8]=p0; work[9]=p1; work[10]=p2; work[11]=p3;
    work[12]=p4; work[13]=p5; work[14]=p6; work[15]=p7;
    __m64 rows[8], values[8];
    rows[0]=work[0]; rows[1]=work[2]; rows[2]=work[4]; rows[3]=work[6];
    rows[4]=work[1]; rows[5]=work[3]; rows[6]=work[5]; rows[7]=work[7];
    inverse4(rows, values, false);
    transpose4(values[0],values[1],values[2],values[3],work);
    transpose4(values[4],values[5],values[6],values[7],work+1);
    rows[0]=work[8]; rows[1]=work[10]; rows[2]=work[12]; rows[3]=work[14];
    rows[4]=work[9]; rows[5]=work[11]; rows[6]=work[13]; rows[7]=work[15];
    inverse4(rows, values, false);
    transpose4(values[0],values[1],values[2],values[3],work+8);
    transpose4(values[4],values[5],values[6],values[7],work+9);
    rows[0]=work[0]; rows[1]=work[2]; rows[2]=work[4]; rows[3]=work[6];
    rows[4]=work[8]; rows[5]=work[10]; rows[6]=work[12]; rows[7]=work[14];
    inverse4(rows,values,true);
    work[0]=values[0]; work[2]=values[1]; work[4]=values[2]; work[6]=values[3];
    work[8]=values[4]; work[10]=values[5]; work[12]=values[6]; work[14]=values[7];
    rows[0]=work[1]; rows[1]=work[3]; rows[2]=work[5]; rows[3]=work[7];
    rows[4]=work[9]; rows[5]=work[11]; rows[6]=work[13]; rows[7]=work[15];
    inverse4(rows,values,true);
    work[1]=values[0]; work[3]=values[1]; work[5]=values[2]; work[7]=values[3];
    work[9]=values[4]; work[11]=values[5]; work[13]=values[6]; work[15]=values[7];
    // No EMMS: the caller owns clearing the MMX state.
}
