// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bbd60.md plus retail only.
// No decoder source was consulted.
//
// ConvertBoolTrees (retail 0x001BBD60, 521 bytes): for the DC tables, the
// zero-run tables and the AC tables (precedence-major, then plane, then
// band) converts each boolean probability tree to Huffman codes, builds the
// tree and the lookup table, and creates the code arrays. All offsets are
// witnessed in this body; no decoder class identity is asserted.

struct Rva009B6320Node;
extern "C" void __cdecl BoolTreeToHuffCodes(const unsigned char*, unsigned*);
extern "C" void __cdecl ZerosBoolTreeToHuffCodes(unsigned char*, int*);
extern "C" void __cdecl VP6_BuildHuffTree(unsigned*, unsigned*, int);
extern "C" void __cdecl VP6_BuildHuffLookupTable(const unsigned*, unsigned short*);
extern "C" void __cdecl VP6_CreateCodeArray(Rva009B6320Node*, int, int*, unsigned char*, int, int);
// Array extents inferred from this body's strides, not an asserted codec class.
struct Rva009AB320Tables {
    unsigned char pad0000[0x3a0];
    unsigned char at03a0[2][11];
    unsigned char at03b6[2][3][6][11];
    unsigned char pad0542[0x1e];
    unsigned char at0560[2][14];
    unsigned char pad057c[0x3cc];
    int at0948[2][12];
    unsigned char at09a8[2][12];
    unsigned at09c0[2][12];
    unsigned at0a20[2][36];
    int at0b40[3][2][6][12];
    unsigned char at1200[3][2][6][12];
    unsigned at13b0[3][2][6][12];
    unsigned at1a70[3][2][6][36];
    int at2eb0[2][14];
    unsigned char at2f20[2][14];
    int at2f3c[2][14];
    unsigned at2fac[2][42];
    unsigned short at30fc[2][64];
    unsigned short at31fc[3][2][6][64];
    unsigned short at43fc[2][64];
};
extern "C" void __cdecl ConvertBoolTrees(Rva009AB320Tables* s)
{
    int plane,group,band;
    for(plane=0;plane<2;++plane) {
        BoolTreeToHuffCodes(s->at03a0[plane],s->at09c0[plane]);
        VP6_BuildHuffTree(s->at0a20[plane],s->at09c0[plane],12);
        VP6_BuildHuffLookupTable(s->at0a20[plane],s->at30fc[plane]);
        VP6_CreateCodeArray((Rva009B6320Node*)s->at0a20[plane],0,s->at0948[plane],s->at09a8[plane],0,0);
    }
    for(plane=0;plane<2;++plane) {
        ZerosBoolTreeToHuffCodes(s->at0560[plane],s->at2f3c[plane]);
        VP6_BuildHuffTree(s->at2fac[plane],(unsigned*)s->at2f3c[plane],9);
        VP6_BuildHuffLookupTable(s->at2fac[plane],s->at43fc[plane]);
        VP6_CreateCodeArray((Rva009B6320Node*)s->at2fac[plane],0,s->at2eb0[plane],s->at2f20[plane],0,0);
    }
    for(group=0;group<3;++group) {
        for(plane=0;plane<2;++plane) {
            for(band=0;band<6;++band) {
                BoolTreeToHuffCodes(s->at03b6[plane][group][band],s->at13b0[group][plane][band]);
                VP6_BuildHuffTree(s->at1a70[group][plane][band],s->at13b0[group][plane][band],12);
                VP6_BuildHuffLookupTable(s->at1a70[group][plane][band],s->at31fc[group][plane][band]);
                VP6_CreateCodeArray((Rva009B6320Node*)s->at1a70[group][plane][band],0,s->at0b40[group][plane][band],s->at1200[group][plane][band],0,0);
            }
        }
    }
}
