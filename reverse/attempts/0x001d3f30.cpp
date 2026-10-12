// _MMX_idct10
// partial score=0.19 date=2026-10-12
// cl: /O2 /G6 /DNDEBUG /MD
// Clean-Room: reverse/vp6_cleanroom/specs/001d3f30.md
// Additional permitted contracts: specs/001d35e0.md and specs/001c4300.md.
// MMX_idct10, retail RVA 0x001D3F30, 1724 bytes ending RET at 0x001D45EB.
// Written from approved specs, all 513 retail instructions, and existing
// checked MMX intrinsic helpers. No external decoder source was consulted.
// All 64 transmission words are dequantized, and each 4x4 quadrant transposed
// into the retail working layout before the reduced transform. The native
// zigzag permutation was read at VA 0x00BD8460, not inferred from a source.
// Partial: compiler scheduling, frame and extra ECX/EDX preservation unproven.
#include <mmintrin.h>
extern unsigned short Rva009B3A00Table[48];

static __forceinline __m64 cosine(const __m64 &value, int index) {
    __m64 result = _mm_mulhi_pi16(value, *(__m64 *)(Rva009B3A00Table + 16 + index * 4));
    if (index < 5) result = _mm_add_pi16(result, value);
    return result;
}

static __forceinline void reduced(const __m64 &a, const __m64 &b, const __m64 &c, const __m64 &d,
                                  __m64 *out, int stride, bool finalPass) {
    __m64 sum17 = cosine(b, 0), diff17 = cosine(b, 6);
    __m64 sum35 = cosine(d, 2);
    __m64 diff35 = _mm_subs_pi16(_mm_setzero_si64(), cosine(d, 4));
    __m64 ds = _mm_subs_pi16(sum17, sum35);
    __m64 ss = _mm_adds_pi16(_mm_adds_pi16(sum35, sum35), ds);
    __m64 dm = _mm_subs_pi16(diff17, diff35);
    __m64 sm = _mm_adds_pi16(_mm_adds_pi16(diff35, diff35), dm);
    __m64 rs = cosine(ds, 3), rm = cosine(dm, 3), re = cosine(a, 3);
    __m64 ps = cosine(c, 1), pd = cosine(c, 5);
    __m64 ea = _mm_subs_pi16(re, ps);
    __m64 eb = _mm_adds_pi16(_mm_adds_pi16(ps, ps), ea);
    __m64 oa = _mm_subs_pi16(rm, pd);
    __m64 ob = _mm_adds_pi16(_mm_adds_pi16(pd, pd), oa);
    __m64 fa = _mm_subs_pi16(re, rs);
    __m64 fb = _mm_adds_pi16(_mm_adds_pi16(rs, rs), fa);
    __m64 y7 = _mm_subs_pi16(eb, ss);
    __m64 y2 = _mm_subs_pi16(fb, ob);
    __m64 y4 = _mm_subs_pi16(ea, sm);
    __m64 y6 = _mm_subs_pi16(fa, oa);
    if (finalPass) {
        __m64 round = *(__m64 *)(Rva009B3A00Table + 44);
        y7 = _mm_adds_pi16(y7, round); y2 = _mm_adds_pi16(y2, round);
        y4 = _mm_adds_pi16(y4, round); y6 = _mm_adds_pi16(y6, round);
    }
    __m64 y0 = _mm_adds_pi16(_mm_adds_pi16(ss, ss), y7);
    __m64 y1 = _mm_adds_pi16(_mm_adds_pi16(ob, ob), y2);
    __m64 y3 = _mm_adds_pi16(_mm_adds_pi16(sm, sm), y4);
    __m64 y5 = _mm_adds_pi16(_mm_adds_pi16(oa, oa), y6);
    if (finalPass) {
        y0 = _mm_srai_pi16(y0, 4); y1 = _mm_srai_pi16(y1, 4);
        y2 = _mm_srai_pi16(y2, 4); y3 = _mm_srai_pi16(y3, 4);
        y4 = _mm_srai_pi16(y4, 4); y5 = _mm_srai_pi16(y5, 4);
        y6 = _mm_srai_pi16(y6, 4); y7 = _mm_srai_pi16(y7, 4);
    }
    out[0] = y0; out[stride] = y1; out[2*stride] = y2; out[3*stride] = y3;
    out[4*stride] = y4; out[5*stride] = y5; out[6*stride] = y6; out[7*stride] = y7;
}

static __forceinline void transpose(const __m64 &a, const __m64 &b, const __m64 &c, const __m64 &d, __m64 *out) {
    __m64 ab0 = _mm_unpacklo_pi16(a,b), ab1 = _mm_unpackhi_pi16(a,b);
    __m64 cd0 = _mm_unpacklo_pi16(c,d), cd1 = _mm_unpackhi_pi16(c,d);
    out[0] = _mm_unpacklo_pi32(ab0,cd0); out[2] = _mm_unpackhi_pi32(ab0,cd0);
    out[4] = _mm_unpacklo_pi32(ab1,cd1); out[6] = _mm_unpackhi_pi32(ab1,cd1);
}


static __forceinline __m64 scatterLane(const __m64 &value, int source, int target) {
    __m64 selected = value;
    if (source > target) selected = _mm_srli_si64(selected, 16 * (source - target));
    if (target > source) selected = _mm_slli_si64(selected, 16 * (target - source));
    return _mm_and_si64(selected, *(__m64 *)(Rva009B3A00Table + 4 * target));
}

extern "C" void __cdecl MMX_idct10(const short *input, const short *quantizer, short *output) {
    // Six observed native cache-touch reads; volatile is a reconstruction choice.
    const volatile unsigned int *touch = (const volatile unsigned int *)output;
    (void)touch[0]; (void)touch[7]; (void)touch[14];
    (void)touch[21]; (void)touch[28]; (void)touch[31];
    const __m64 *src = (const __m64 *)input, *q = (const __m64 *)quantizer;
    __m64 products[16];
    for (unsigned i = 0; i != 16; ++i) products[i] = _mm_mullo_pi16(src[i], q[i]);
    __m64 *dst = (__m64 *)output;
    dst[0] = _mm_or_si64(_mm_or_si64(scatterLane(products[0], 0, 0), scatterLane(products[0], 2, 1)),
                         _mm_or_si64(scatterLane(products[0], 3, 2), scatterLane(products[2], 1, 3)));
    dst[1] = _mm_or_si64(_mm_or_si64(scatterLane(products[3], 2, 0), scatterLane(products[4], 0, 1)),
                         _mm_or_si64(scatterLane(products[6], 1, 2), scatterLane(products[7], 3, 3)));
    dst[2] = _mm_or_si64(_mm_or_si64(scatterLane(products[0], 1, 0), scatterLane(products[1], 0, 1)),
                         _mm_or_si64(scatterLane(products[2], 0, 2), scatterLane(products[2], 3, 3)));
    dst[3] = _mm_or_si64(_mm_or_si64(scatterLane(products[3], 3, 0), scatterLane(products[6], 2, 1)),
                         _mm_or_si64(scatterLane(products[7], 2, 2), scatterLane(products[10], 0, 3)));
    dst[4] = _mm_or_si64(_mm_or_si64(scatterLane(products[1], 1, 0), scatterLane(products[1], 3, 1)),
                         _mm_or_si64(scatterLane(products[3], 0, 2), scatterLane(products[4], 2, 3)));
    dst[5] = _mm_or_si64(_mm_or_si64(scatterLane(products[6], 3, 0), scatterLane(products[7], 1, 1)),
                         _mm_or_si64(scatterLane(products[10], 1, 2), scatterLane(products[11], 0, 3)));
    dst[6] = _mm_or_si64(_mm_or_si64(scatterLane(products[1], 2, 0), scatterLane(products[3], 1, 1)),
                         _mm_or_si64(scatterLane(products[4], 1, 2), scatterLane(products[6], 0, 3)));
    dst[7] = _mm_or_si64(_mm_or_si64(scatterLane(products[7], 0, 0), scatterLane(products[10], 2, 1)),
                         _mm_or_si64(scatterLane(products[10], 3, 2), scatterLane(products[13], 1, 3)));
    dst[8] = _mm_or_si64(_mm_or_si64(scatterLane(products[2], 2, 0), scatterLane(products[5], 0, 1)),
                         _mm_or_si64(scatterLane(products[5], 1, 2), scatterLane(products[8], 3, 3)));
    dst[9] = _mm_or_si64(_mm_or_si64(scatterLane(products[9], 3, 0), scatterLane(products[11], 2, 1)),
                         _mm_or_si64(scatterLane(products[12], 2, 2), scatterLane(products[14], 1, 3)));
    dst[10] = _mm_or_si64(_mm_or_si64(scatterLane(products[4], 3, 0), scatterLane(products[5], 2, 1)),
                         _mm_or_si64(scatterLane(products[8], 2, 2), scatterLane(products[9], 0, 3)));
    dst[11] = _mm_or_si64(_mm_or_si64(scatterLane(products[11], 1, 0), scatterLane(products[12], 3, 1)),
                         _mm_or_si64(scatterLane(products[14], 0, 2), scatterLane(products[14], 2, 3)));
    dst[12] = _mm_or_si64(_mm_or_si64(scatterLane(products[5], 3, 0), scatterLane(products[8], 1, 1)),
                         _mm_or_si64(scatterLane(products[9], 1, 2), scatterLane(products[12], 0, 3)));
    dst[13] = _mm_or_si64(_mm_or_si64(scatterLane(products[13], 0, 0), scatterLane(products[13], 3, 1)),
                         _mm_or_si64(scatterLane(products[14], 3, 2), scatterLane(products[15], 2, 3)));
    dst[14] = _mm_or_si64(_mm_or_si64(scatterLane(products[8], 0, 0), scatterLane(products[9], 2, 1)),
                         _mm_or_si64(scatterLane(products[11], 3, 2), scatterLane(products[12], 1, 3)));
    dst[15] = _mm_or_si64(_mm_or_si64(scatterLane(products[13], 2, 0), scatterLane(products[15], 0, 1)),
                         _mm_or_si64(scatterLane(products[15], 1, 2), scatterLane(products[15], 3, 3)));

    __m64 rows[8];
    reduced(dst[0], dst[2], dst[4], dst[6], rows, 1, false);
    transpose(rows[4], rows[5], rows[6], rows[7], dst + 1);
    transpose(rows[0], rows[1], rows[2], rows[3], dst);
    reduced(dst[0], dst[2], dst[4], dst[6], dst, 2, true);
    reduced(dst[1], dst[3], dst[5], dst[7], dst + 1, 2, true);
    // Preserve the active MMX state: the caller owns the clear-state operation.
}
