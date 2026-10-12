// _DeblockNonFilteredBand_WMT
// partial score=0.085765952 date=2026-10-12
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001d0340.md and retail only.
// Partial bank: C++ SSE2 intrinsics from the retail-checked value contract.
// Complete 960-instruction boundary: 0x001D0340..0x001D1323 RET.
// Output plane and unsigned activity accumulators match 240 Unicorn trials:
// 0/1/2/4 blocks, flat/ramp/low-noise/full-byte planes, fixed q
// 0/1/3/4/63/127/128/255 plus seeded mixed tables, loop limits0..127.
// This emits3875B versus4068B: frame0x354 versus0x144 and different
// register/save/staging shape. Scalar1797B and initial SSE3907B are
// weaker shapes; direct intrinsics alone made no difference. No EMMS.
#include <emmintrin.h>
extern int *g_rva01356A9C;
struct DeblockPostProcView { char opaque00[12]; unsigned frameQ;
    char opaque10[20]; int *blockQ; unsigned *activity; };


#define twice(v) _mm_add_epi16((v),(v))
static __forceinline __m128i absDifference(const __m128i &a,const __m128i &b) {
    return _mm_or_si128(_mm_subs_epu16(a,b),_mm_subs_epu16(b,a));
}
static __forceinline __m128i activity(const __m128i *p) {
    __m128i center=_mm_set1_epi16(128),ones=_mm_set1_epi16(1);
    __m128i v=_mm_sub_epi16(p[0],center),sum=v,square=_mm_mullo_epi16(v,v);
    for(int k=1;k<4;++k) {v=_mm_sub_epi16(p[k],center);sum=_mm_add_epi16(sum,v);square=_mm_add_epi16(square,_mm_mullo_epi16(v,v));}
    return _mm_sub_epi16(square,_mm_mullo_epi16(_mm_srai_epi16(sum,1),_mm_srai_epi16(_mm_add_epi16(sum,ones),1)));
}
static __forceinline __m128i differenceMask(const __m128i &a,const __m128i &b,const __m128i &q) {
    return _mm_srai_epi16(_mm_sub_epi16(absDifference(a,b),q),15);
}
static __forceinline __m128i select(const __m128i &yes,const __m128i &no,const __m128i &mask) {
    return _mm_or_si128(_mm_and_si128(yes,mask),_mm_andnot_si128(mask,no));
}
static __forceinline __m128i roundBlend(const __m128i &weighted,const __m128i &original,const __m128i &mask) {
    return select(_mm_srai_epi16(weighted,4),original,mask);
}
static __forceinline void filter(const __m128i *p,__m128i *out,unsigned q,int limit,bool vertical,
    unsigned &firstActivity,unsigned &secondActivity) {
    __m128i a=activity(p+1),b=activity(p+5),quant=_mm_set1_epi16((short)q);
    __m128i threshold=_mm_mullo_epi16(_mm_mullo_epi16(_mm_set1_epi16(3),quant),quant);
    threshold=vertical ? _mm_srli_epi16(threshold,5) : _mm_srai_epi16(threshold,5);
    __m128i first=_mm_andnot_si128(_mm_srai_epi16(a,15),_mm_srai_epi16(_mm_sub_epi16(a,threshold),15));
    __m128i second=_mm_andnot_si128(_mm_srai_epi16(b,15),_mm_srai_epi16(_mm_sub_epi16(b,threshold),15));
    __m128i mask=_mm_and_si128(_mm_and_si128(first,second),differenceMask(p[4],p[5],quant));
    __m128i correction=_mm_srai_epi16(_mm_add_epi16(_mm_add_epi16(_mm_sub_epi16(p[3],p[6]),_mm_add_epi16(twice(_mm_sub_epi16(p[5],p[4])),_mm_sub_epi16(p[5],p[4]))),_mm_set1_epi16(4)),3);
    __m128i sign=_mm_srai_epi16(correction,15);
    __m128i mag=_mm_subs_epi16(_mm_xor_si128(correction,sign),sign);
    __m128i bound=_mm_set1_epi16((short)limit),distance=_mm_sub_epi16(bound,mag);
    __m128i distanceSign=_mm_srai_epi16(distance,15);
    distance=_mm_subs_epi16(_mm_xor_si128(distance,distanceSign),distanceSign);
    correction=_mm_mullo_epi16(_mm_subs_epu16(bound,distance),_mm_or_si128(sign,_mm_set1_epi16(1)));
    __m128i zero=_mm_setzero_si128();
    __m128i fallback0=_mm_unpacklo_epi8(_mm_packus_epi16(_mm_add_epi16(p[4],correction),zero),zero);
    __m128i fallback1=_mm_unpacklo_epi8(_mm_packus_epi16(_mm_sub_epi16(p[5],correction),zero),zero);
    __m128i outer0=select(p[0],p[1],differenceMask(p[0],p[1],quant));
    __m128i outer1=select(p[9],p[8],differenceMask(p[9],p[8],quant));
    __m128i rolling=_mm_add_epi16(_mm_add_epi16(_mm_add_epi16(_mm_add_epi16(_mm_add_epi16(twice(outer0),outer0),p[1]),p[2]),p[3]),_mm_add_epi16(p[4],_mm_set1_epi16(4)));
    out[0]=roundBlend(_mm_add_epi16(_mm_sub_epi16(twice(_mm_add_epi16(rolling,p[1])),p[4]),p[5]),p[1],mask);
    rolling=_mm_add_epi16(_mm_sub_epi16(rolling,outer0),p[5]);
    out[1]=roundBlend(_mm_add_epi16(_mm_sub_epi16(twice(_mm_add_epi16(rolling,p[2])),p[5]),p[6]),p[2],mask);
    rolling=_mm_add_epi16(_mm_sub_epi16(rolling,outer0),p[6]);
    out[2]=roundBlend(_mm_add_epi16(_mm_sub_epi16(twice(_mm_add_epi16(rolling,p[3])),p[6]),p[7]),p[3],mask);
    rolling=_mm_add_epi16(_mm_sub_epi16(rolling,outer0),p[7]);
    out[3]=roundBlend(_mm_add_epi16(_mm_sub_epi16(_mm_sub_epi16(_mm_add_epi16(twice(_mm_add_epi16(rolling,p[4])),outer0),p[1]),p[7]),p[8]),fallback0,mask);
    rolling=_mm_add_epi16(_mm_sub_epi16(rolling,p[1]),p[8]);
    out[4]=roundBlend(_mm_add_epi16(_mm_sub_epi16(_mm_sub_epi16(_mm_add_epi16(twice(_mm_add_epi16(rolling,p[5])),p[1]),p[2]),p[8]),outer1),fallback1,mask);
    rolling=_mm_add_epi16(_mm_sub_epi16(rolling,p[2]),outer1);
    out[5]=roundBlend(_mm_sub_epi16(_mm_add_epi16(twice(_mm_add_epi16(rolling,p[6])),p[2]),p[3]),p[6],mask);
    rolling=_mm_add_epi16(_mm_sub_epi16(rolling,p[3]),outer1);
    out[6]=roundBlend(_mm_sub_epi16(_mm_add_epi16(twice(_mm_add_epi16(rolling,p[7])),p[3]),p[4]),p[7],mask);
    rolling=_mm_add_epi16(_mm_sub_epi16(rolling,p[4]),outer1);
    out[7]=roundBlend(_mm_sub_epi16(_mm_add_epi16(twice(_mm_add_epi16(rolling,p[8])),p[4]),p[5]),p[8],mask);
    __declspec(align(16)) unsigned short av[8],bv[8];
    _mm_store_si128((__m128i *)av,a);_mm_store_si128((__m128i *)bv,b);
    for(int k=0;k<8;++k) {firstActivity+=av[k];secondActivity+=bv[k];}
}
static __forceinline void transposeStore(__m128i *out,unsigned char *dst,unsigned pitch) {
    __m128i zero=_mm_setzero_si128();
    __m128i a=_mm_unpacklo_epi8(_mm_packus_epi16(out[0],zero),_mm_packus_epi16(out[1],zero));
    __m128i b=_mm_unpacklo_epi8(_mm_packus_epi16(out[2],zero),_mm_packus_epi16(out[3],zero));
    __m128i c=_mm_unpacklo_epi8(_mm_packus_epi16(out[4],zero),_mm_packus_epi16(out[5],zero));
    __m128i d=_mm_unpacklo_epi8(_mm_packus_epi16(out[6],zero),_mm_packus_epi16(out[7],zero));
    __m128i ab0=_mm_unpacklo_epi16(a,b),ab1=_mm_unpackhi_epi16(a,b);
    __m128i cd0=_mm_unpacklo_epi16(c,d),cd1=_mm_unpackhi_epi16(c,d);
    __m128i r01=_mm_unpacklo_epi32(ab0,cd0),r23=_mm_unpackhi_epi32(ab0,cd0);
    __m128i r45=_mm_unpacklo_epi32(ab1,cd1),r67=_mm_unpackhi_epi32(ab1,cd1);
    _mm_storel_epi64((__m128i *)dst,r01);_mm_storel_epi64((__m128i *)(dst+pitch),_mm_srli_si128(r01,8));
    _mm_storel_epi64((__m128i *)(dst+2*pitch),r23);_mm_storel_epi64((__m128i *)(dst+3*pitch),_mm_srli_si128(r23,8));
    _mm_storel_epi64((__m128i *)(dst+4*pitch),r45);_mm_storel_epi64((__m128i *)(dst+5*pitch),_mm_srli_si128(r45,8));
    _mm_storel_epi64((__m128i *)(dst+6*pitch),r67);_mm_storel_epi64((__m128i *)(dst+7*pitch),_mm_srli_si128(r67,8));
}
extern "C" void __cdecl DeblockNonFilteredBand_WMT(DeblockPostProcView *post,
    unsigned char *source,unsigned char *destination,unsigned pitch,
    unsigned across,unsigned firstBlock,const unsigned *quantizerScale) {
    int limit=(short)g_rva01356A9C[post->frameQ];
    __m128i p[10],out[8],zero=_mm_setzero_si128();
    for(unsigned offset=0;offset<across;++offset) {
        unsigned index=firstBlock+offset;
        unsigned q=quantizerScale[post->blockQ[index+across]];
        for(int k=0;k<10;++k)
            p[k]=_mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)(source+offset*8+(k-5)*pitch)),zero);
        filter(p,out,q,limit,false,post->activity[index],post->activity[index+across]);
        for(int k=0;k<8;++k)
            _mm_storel_epi64((__m128i *)(destination+offset*8+(k-4)*pitch),_mm_packus_epi16(out[k],zero));
        if(offset) {
            q=quantizerScale[post->blockQ[index]];
            unsigned char *edge=destination-8*pitch+offset*8;
            for(int k=0;k<10;++k) for(int row=0;row<8;++row)
                p[k].m128i_i16[row]=edge[row*pitch+k-5];
            filter(p,out,q,limit,true,post->activity[index-1],post->activity[index]);
            transposeStore(out,edge-4,pitch);
        }
    }
}




