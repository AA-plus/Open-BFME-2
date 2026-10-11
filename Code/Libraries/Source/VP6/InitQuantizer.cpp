// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b71f0.md plus retail only.
// No decoder source was consulted.
//
// VP6_init_quantizer (retail 0x001B71F0, 945 bytes): cdecl builder of the
// fixed-point reciprocal quantizer multipliers, rounding values, zero-bin
// sizes and zero-run corrections for both planes from the frame Q index.
// The second (version) argument is unused.

#include <string.h>
extern short g_Rva01141D08[],g_Rva01141D88[];
extern unsigned g_Rva01141708[],g_Rva01141808[];
extern int g_Rva01142008[],g_Rva01141E08[],g_Rva01141B08[],g_Rva01141908[];
extern int g_Rva01142108[],g_Rva01141F08[],g_Rva01141C08[],g_Rva01141A08[];
// g_Rva01142208: matched references place it at VA 0xbd8360 (retail .rdata contents).
int g_Rva01142208[64] = {
	-8, 0, 5, 0xa, 0xa, 0xa, 0xa, 0xa,
	0xf, 0xf, 0xf, 0xf, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
	0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
	0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
};
extern double g_Rva01142610;
// g_Rva01142610: matched references place it at VA 0xbd8768 (retail .rdata value 65536.0).
double g_Rva01142610 = 65536.0;
// g_Rva01142608: matched references place it at VA 0xbd8760; retail contents, sized to the
// 0x8-byte gap before the next known global there.
unsigned char g_Rva01142608[8] = {
	0, 0, 0, 0, 1, 1, 0, 0,
};
// g_rva01142308: matched references place it at VA 0xbd8460; retail contents, sized to the
// 0x100-byte gap before the next known global there.
int g_rva01142308[64] = {
	0, 1, 8, 16, 9, 2, 3, 10,
	17, 24, 32, 25, 18, 11, 4, 5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13, 6, 7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63,
};
struct Rva009A6780State {
    int index,at0004;
    short at0008[8],at0018[8],at0028[8];
    unsigned char pad0038[0x158];
    int at0190[2][64],at0390[2][64],at0590[2][64],at0790[2][64];
};
extern "C" void __cdecl VP6_init_quantizer(Rva009A6780State* s,int version)
{
    int index=s->index;
    double reciprocal=1.0/(g_Rva01141D08[index]*4);
    reciprocal*=g_Rva01142610;
    s->at0190[0][0]=(int)(reciprocal+0.5);
    s->at0390[0][0]=g_Rva01142008[index];
    s->at0590[0][0]=g_Rva01141E08[index];
    int i;
    for(i=1;i<64;++i) {
        reciprocal=1.0/(g_Rva01141708[s->index]*4);
        reciprocal*=g_Rva01142610;
        s->at0190[0][i]=(int)(reciprocal+0.5);
        s->at0390[0][i]=g_Rva01141B08[s->index];
        s->at0590[0][i]=g_Rva01141908[s->index];
    }
    index=s->index;
    reciprocal=1.0/(g_Rva01141D88[index]*4);
    reciprocal*=g_Rva01142610;
    s->at0190[1][0]=(int)(reciprocal+0.5);
    s->at0390[1][0]=g_Rva01142108[index];
    s->at0590[1][0]=g_Rva01141F08[index];
    for(i=1;i<64;++i) {
        reciprocal=1.0/(g_Rva01141808[s->index]*4);
        reciprocal*=g_Rva01142610;
        s->at0190[1][i]=(int)(reciprocal+0.5);
        s->at0390[1][i]=g_Rva01141C08[s->index];
        s->at0590[1][i]=g_Rva01141A08[s->index];
    }
    for(i=0;i<8;++i) {
        s->at0008[i]=(short)s->at0390[0][1];
        s->at0018[i]=(short)s->at0190[0][1];
        s->at0028[i]=(short)s->at0590[0][1]-1;
    }
    for(i=0;i<64;++i) {
        s->at0790[0][i]=(int)(g_Rva01141708[s->index]*g_Rva01142208[i]*4)/100;
        s->at0790[1][i]=(int)(g_Rva01141808[s->index]*g_Rva01142208[i]*4)/100;
    }
}
