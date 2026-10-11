// Retail RVA 009AC660, 1279 bytes. Offset-derived view: no class identity claimed.
// ESI input is witnessed by the sole caller at 009ACB60.
// The external harness exists only to let MSVC select the private static ABI.
struct Rva009AC5D0State;
struct BfmeBits1186;
struct BfmeS1040;
struct CodecState;
extern "C" unsigned __cdecl ReadHeaderBits(Rva009AC5D0State*, unsigned);
extern "C" void __cdecl VP6_InitQTables(unsigned char*);
extern "C" void __cdecl VP6_StartDecode(BfmeBits1186*, unsigned char*);
// Post-processing setters at 0x001B6900 and 0x001B6910 (VP6 clean room).
extern "C" void __cdecl SetPPInterlacedMode(void*,int);
extern "C" void __cdecl SetDeInterlaceMode(void*,int);
extern "C" int __cdecl VP6_bitread(void *, int);
extern "C" int __cdecl VP6_InitFrameDetails(CodecState*);
extern "C" int __cdecl VP6_DecodeBool(void*,int);
extern "C" void __cdecl VP6_UpdateQ(BfmeS1040*,int);
extern "C" void* __cdecl memset(void*,int,unsigned);
#pragma intrinsic(memset)
#define U(o) (*(unsigned*)(s+(o)))
#define B(o) (*(unsigned char*)(s+(o)))
#define P(o) (*(unsigned char**)(s+(o)))

static int Rva009AC660ReadHeader(unsigned char* s)
{
    Rva009AC5D0State* bits=(Rva009AC5D0State*)(s+0x450c);
    B(0x1ac)=(unsigned char)ReadHeaderBits(bits,1);
    unsigned char index=(unsigned char)ReadHeaderBits(bits,6);
    U(0x944)=(unsigned char)ReadHeaderBits(bits,1);
    BfmeBits1186* decoder;
    if (!B(0x1ac)) {
        B(0x19c)=(unsigned char)ReadHeaderBits(bits,5);
        B(0x19d)=(unsigned char)ReadHeaderBits(bits,2);
        if (B(0x19c)>7) return 0;
        // Retail passes a second unused slot to the existing one-argument callee.
        ((void (__cdecl *)(unsigned char*,unsigned char))VP6_InitQTables)(P(0x13c),B(0x19c));
        U(0x1dc)=(unsigned char)ReadHeaderBits(bits,1);
        if (!U(0x944) && B(0x19d)) {
            decoder=(BfmeBits1186*)(s+0x150);
            VP6_StartDecode(decoder,P(0x450c)+2);
        } else {
            decoder=(BfmeBits1186*)(s+0x150);
            VP6_StartDecode(decoder,P(0x450c)+4);
            U(0x451c)=ReadHeaderBits(bits,16);
        }
        SetPPInterlacedMode(P(0x298),U(0x1dc));
        if (U(0x1dc)) SetDeInterlaceMode(P(0x298),U(0x4944));
        unsigned a=(unsigned char)VP6_bitread(decoder,8)*2u;
        unsigned b=(unsigned char)VP6_bitread(decoder,8)*2u;
        unsigned c=(unsigned char)VP6_bitread(decoder,8)*2u;
        unsigned d=(unsigned char)VP6_bitread(decoder,8)*2u;
        if (!U(0x1cc)) U(0x1cc)=1;
        if (!U(0x1d4)) U(0x1d4)=1;
        unsigned oldB=U(0x1f8)*U(0x1c8)*8/U(0x1cc);
        unsigned oldA=U(0x1d0)*U(0x1f4)*8/U(0x1d4);
        U(0x1e0)=d*8;
        U(0x1e4)=c*8;
        if (a>=c) { U(0x1d0)=1; U(0x1d4)=1; }
        else if (a*5>=c*4) { U(0x1d0)=5; U(0x1d4)=4; }
        else if (a*5>=c*3) { U(0x1d0)=5; U(0x1d4)=3; }
        else { U(0x1d0)=2; U(0x1d4)=1; }
        if (b>=d) { U(0x1c8)=1; U(0x1cc)=1; }
        else if (b*5>=d*4) { U(0x1c8)=5; U(0x1cc)=4; }
        else if (b*5>=d*3) { U(0x1c8)=5; U(0x1cc)=3; }
        else { U(0x1c8)=2; U(0x1cc)=1; }
        unsigned newB=U(0x1c8)*b*8/U(0x1cc);
        unsigned newA=U(0x1d0)*a*8/U(0x1d4);
        U(0x234)=newB;
        U(0x238)=newA;
        U(0x1d8)=VP6_bitread(decoder,2);
        if (a!=U(0x1f4) || b!=U(0x1f8)) {
            U(0x1b0)=b*8;
            U(0x1b4)=a*8;
            VP6_InitFrameDetails((CodecState*)s);
        }
        if (P(0x264) && (oldB!=newB || oldA!=newA)) {
            memset(P(0x264),0,(U(0x240)+32)*(U(0x23c)+32));
            unsigned n=(U(0x240)+32)*(U(0x23c)+32);
            memset(P(0x264)+n,128,n/2);
        }
        if (B(0x19d)) {
            if (VP6_DecodeBool(decoder,128)) {
                B(0x692)=2;
                U(0x694)=VP6_bitread(decoder,5)<<5;
                B(0x693)=(unsigned char)VP6_bitread(decoder,3);
            } else B(0x692)=VP6_DecodeBool(decoder,128)!=0;
        }
    } else {
        if (!U(0x944) && B(0x19d)) {
            decoder=(BfmeBits1186*)(s+0x150);
            VP6_StartDecode(decoder,P(0x450c)+1);
        } else {
            decoder=(BfmeBits1186*)(s+0x150);
            VP6_StartDecode(decoder,P(0x450c)+3);
            U(0x451c)=ReadHeaderBits(bits,16);
        }
        U(0x698)=VP6_DecodeBool(decoder,128);
        if (B(0x19d)) {
            B(0x4534)=(unsigned char)VP6_DecodeBool(decoder,128);
            if (B(0x4534)) B(0x4534)=(unsigned char)VP6_DecodeBool(decoder,128) | (B(0x4534)<<1);
        }
    }
    U(0x4520)=VP6_DecodeBool(decoder,128);
    *(unsigned*)P(0x13c)=index;
    unsigned char* table=P(0x13c);
    *(unsigned*)(table+4)=((unsigned*)(table+0x3c))[index];
    // Retail zero-extends this byte into the outgoing four-byte stack slot.
    // Preserve the existing callee identity while expressing the narrow call-site ABI.
    ((void (__cdecl *)(BfmeS1040*,unsigned char))VP6_UpdateQ)((BfmeS1040*)P(0x13c),B(0x19c));
    return 1;
}

// VP6_LoadFrame retail 0x001BD550..0x001BD56B (28 bytes), cdecl.
// Clean room: reverse/vp6_cleanroom/specs/001bd550.md plus retail only.
// Calls the frame header reader above with the instance in ESI (its private
// static convention, which needs the caller in this unit) and returns 1 when
// it succeeded, else 0. Retail keeps the 1 in EDI across the call.
extern "C" int __cdecl VP6_LoadFrame(unsigned char* s)
{
    int result = 1;
    if (!Rva009AC660ReadHeader(s))
        result = 0;
    return result;
}

#undef U
#undef B
#undef P

