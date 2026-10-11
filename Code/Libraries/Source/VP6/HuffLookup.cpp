// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean room: reverse/vp6_cleanroom/specs/001c6ba0.md and 001c6c20.md plus
// retail only. No decoder source was consulted.
//
// Huffman tree helpers over 12-byte nodes: VP6_BuildHuffLookupTable (retail
// 0x001C6BA0) expands the tree into 64 six-bit prefix entries, and
// VP6_CreateCodeArray (retail 0x001C6C20) assigns prefix codes and lengths
// depth first.

// VP6_BuildHuffLookupTable: only the low byte is needed before loading a
// complete node from the tree. Bitfield initialization preserves the unused
// bits without treating the compiler scratch word as an incoming argument.
union Vp6TreeNodeBits {
    unsigned value;
    struct { unsigned low:8; unsigned high:24; } bytes;
    struct { unsigned leaf:1; unsigned index:7; unsigned rest:24; } fields;
};

// RVA 0x001C6BA0
extern "C" void __cdecl VP6_BuildHuffLookupTable(const unsigned *tree, unsigned short *output)
{
    Vp6TreeNodeBits node;
    for (int index=0; index<64; ++index) {
        int prefix=0;
        node.bytes.low=0;
        int bit=6;
        do {
            ++prefix;
            --bit;
            int branch=index>>bit;
            if(branch & 1) node.value=tree[node.fields.index*3+1];
            else node.value=tree[node.fields.index*3];
        } while(!node.fields.leaf && bit>0);
        unsigned result=node.fields.index;
        unsigned low=node.fields.leaf;
        result=(result | (prefix<<11))<<1;
        result|=low;
        output[index]=(unsigned short)result;
    }
}

// A left leaf does not terminate the walk: the right child is processed too.
// Node indices are re-read after output writes, preserving retail alias
// behavior.
struct Vp6HuffNode { unsigned m_first,m_second,m_unused; };

// RVA 0x001C6C20
extern "C" void __cdecl VP6_CreateCodeArray(Vp6HuffNode *nodes,int node,int *codes,unsigned char *lengths,int code,int depth)
{
    if(nodes[node].m_first & 1) {
        codes[(nodes[node].m_first>>1)&0x7f]=code<<1;
        lengths[(nodes[node].m_first>>1)&0x7f]=(unsigned char)(depth+1);
    } else {
        VP6_CreateCodeArray(nodes,(nodes[node].m_first>>1)&0x7f,codes,lengths,code+code,depth+1);
    }
    if(nodes[node].m_second & 1) {
        codes[(nodes[node].m_second>>1)&0x7f]=(code<<1)+1;
        lengths[(nodes[node].m_second>>1)&0x7f]=(unsigned char)(depth+1);
    } else {
        VP6_CreateCodeArray(nodes,(nodes[node].m_second>>1)&0x7f,codes,lengths,code+code+1,depth+1);
    }
}
