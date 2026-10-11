// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b7610.md plus retail only.
// No decoder source was consulted.
//
// VP6_quantize_c (retail 0x001B7610, 500 bytes): quantizes a 64-coefficient
// block in scan order with a dead zone widened by the current zero run; the
// compiler unrolls the loop by three. The plane selector (6 bytes at image
// 0x00BD8760) and the scan order (64 dwords at 0x00BD8460) are retail data.
#include <string.h>

extern unsigned char g_Rva01142608[];
extern int g_rva01142308[];

struct Rva009A6780State {
    int index,at0004;
    short at0008[8],at0018[8],at0028[8];
    unsigned char pad0038[0x158];
    int at0190[2][64],at0390[2][64],at0590[2][64],at0790[2][64];
};

extern "C" void __cdecl VP6_quantize_c(Rva009A6780State* s,const short* src,short* dst,unsigned char mode)
{
    unsigned char run=0;
    int bank=g_Rva01142608[mode];
    int* multipliers=s->at0190[bank];
    int* offsets=s->at0390[bank];
    int* thresholds=s->at0590[bank];
    int* runs=s->at0790[bank];
    memset(dst,0,128);
    int value=src[0];
    int threshold=thresholds[0];
    if(value>=threshold) dst[0]=(short)(((value+offsets[0])*multipliers[0])>>16);
    else if(value<=-threshold) dst[0]=(short)(((value-offsets[0])*multipliers[0]+65535)>>16);
    else run=1;
    for(unsigned int i=1;i<64;i++) {
        int pos=g_rva01142308[i];
        if(src[pos]>=thresholds[pos]+runs[run]) {
            dst[i]=(short)(((src[pos]+offsets[pos])*multipliers[pos])>>16);
            run=0;
        } else if(src[pos]<=-thresholds[pos]-runs[run]) {
            dst[i]=(short)(((src[pos]-offsets[pos])*multipliers[pos]+65535)>>16);
            run=0;
        } else ++run;
    }
}
