// _MMX_idct10_DX
// partial score=0.1112266112 date=2026-10-12
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d4d50.md and retail only.
// Partial bank: reduced MMX inverse DCT; no decoder reference source consulted.
// Output checked against retail: six spec fixtures and 256 deterministic
// randomized ten-coefficient inputs with full-range signed quantizers.
// Not byte exact: 1390 bytes versus 1034, aligned 88-byte compiler frame,
// different MMX register allocation; retail additionally preserves EDX/ECX.
// In-place trial was larger (1422 bytes). No MMX clear belongs here.
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

extern "C" void __cdecl MMX_idct10_DX(short *input, short *quantizer, short *output) {
    // Retail touches these cache lines before producing output.
    volatile int *touch = (volatile int *)output;
    (void)touch[0]; (void)touch[7]; (void)touch[14];
    (void)touch[21]; (void)touch[28]; (void)touch[31];
    __m64 *src = (__m64 *)input, *q = (__m64 *)quantizer, *dst = (__m64 *)output;
    __m64 a = _mm_mullo_pi16(src[0],q[0]), b = _mm_mullo_pi16(src[2],q[2]);
    __m64 c = _mm_mullo_pi16(src[4],q[4]), d = _mm_mullo_pi16(src[6],q[6]);
    dst[0]=a; dst[1]=_mm_setzero_si64(); dst[2]=b; dst[3]=_mm_setzero_si64();
    dst[4]=c; dst[5]=_mm_setzero_si64(); dst[6]=d; dst[7]=_mm_setzero_si64();
    dst[8]=_mm_setzero_si64(); dst[9]=_mm_setzero_si64();
    dst[10]=_mm_setzero_si64(); dst[11]=_mm_setzero_si64();
    dst[12]=_mm_setzero_si64(); dst[13]=_mm_setzero_si64();
    dst[14]=_mm_setzero_si64(); dst[15]=_mm_setzero_si64();
    __m64 rows[8]; reduced(a,b,c,d,rows,1,false);
    transpose(rows[4],rows[5],rows[6],rows[7],dst+1);
    transpose(rows[0],rows[1],rows[2],rows[3],dst);
    reduced(dst[0],dst[2],dst[4],dst[6],dst,2,true);
    reduced(dst[1],dst[3],dst[5],dst[7],dst+1,2,true);
    // MMX cleanup belongs to the caller, matching the retail contract.
}



