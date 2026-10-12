// ?rva001B267B@BFME2Encoding2MotionChannel@@QAEXPAIIIPAVVector3@@1@Z
// partial score=0.7 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Oy-
// BFME 2 stream motion channel encoding 2: byte-delta decoders, called from the
// slot 3/4/5 evaluators. Sibling of BFME2Encoding1MotionChannelDecoders.cpp
// (landed 0x001B230A/0x001B2450): same cached-state continue, two outputs,
// 16-frame blocks; each component packet is a filter byte plus 16 bytes
// (17 bytes, stride 51 for Vector3 and 68 for Quaternion), filter scaled by
// Scale * 0.0625 (double, x87), factors are byte values minus 128.
// Layout: Data at +0x28, scale at +0x14, initial values at +0x18,
// frame count at +0xC.
class ChunkLoadClass;
class Vector3 { public: float X, Y, Z; };
class Quaternion { public: float X, Y, Z, W; };
class BFME2MotionChannel {
public:
    virtual bool Load(ChunkLoadClass &);
    virtual ~BFME2MotionChannel();
    virtual int UnknownSlot2();
    virtual void UnknownSlot3();
    virtual void UnknownSlot4();
    virtual void UnknownSlot5();
    virtual int UnknownSlot6();
    int Type, Pivot, Count, Components;
};
// The decode filter table is the data-ledger global ?filtertable@@3PAMA (0x009B6C28,
// BFME2EncodingFilterTableInit.cpp), shared with the encoding 1 decoders.
extern float filtertable[];
class BFME2StreamMotionChannel : public BFME2MotionChannel {
public:
    float Scale;
    float Initial[4];
    unsigned char *Data;
};
class BFME2Encoding2MotionChannel : public BFME2StreamMotionChannel {
public:
    void rva001B267B(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1);
    void rva001B27AB(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1);
};
void BFME2Encoding2MotionChannel::rva001B267B(unsigned int *state, unsigned int from, unsigned int frame, Vector3 *value0, Vector3 *value1)
{
    Vector3 last;
    if (from > frame) {
        from = 0;
        last = *(const Vector3 *)Initial;
    } else
        last = *(const Vector3 *)state;
    unsigned char *packet = Data + (from >> 4) * 51;
    while (from + 1 <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0)
                *value0 = last;
            *value1 = last;
            return;
        }
        unsigned int fi0 = from & 0xF;
        from &= ~0xFu;
        for (int vi = 0; vi < 3; ++vi, packet += 17) {
            float filter = filtertable[*packet] * Scale * 0.0625;
            unsigned int f[1];
            for (unsigned int fi = fi0; fi < 16; ++fi) {
                f[0] = from + fi;
                if (f[0] == frame)
                    ((float *)value0)[vi] = ((float *)&last)[vi];
                else if (f[0] == frame + 1) {
                    ((float *)value1)[vi] = ((float *)&last)[vi];
                    break;
                }
                int factor = (int)packet[1 + fi] - 0x80;
                ((float *)&last)[vi] += (float)factor * filter;
            }
        }
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}
void BFME2Encoding2MotionChannel::rva001B27AB(unsigned int *state, unsigned int from, unsigned int frame, Quaternion *value0, Quaternion *value1)
{
    Quaternion last;
    if (from > frame) {
        from = 0;
        last = *(const Quaternion *)Initial;
    } else
        last = *(const Quaternion *)state;
    unsigned char *packet = Data + (from >> 4) * 68;
    while (from + 1 <= frame + 1) {
        if (from >= (unsigned int)Count) {
            if (value0)
                *value0 = last;
            *value1 = last;
            return;
        }
        unsigned int fi0 = from & 0xF;
        from &= ~0xFu;
        for (int vi = 0; vi < 4; ++vi, packet += 17) {
            float filter = filtertable[*packet] * Scale * 0.0625;
            for (unsigned int fi = fi0; fi < 16; ++fi) {
                unsigned int f = from + fi;
                if (f == frame)
                    ((float *)value0)[vi] = ((float *)&last)[vi];
                else if (f == frame + 1) {
                    ((float *)value1)[vi] = ((float *)&last)[vi];
                    break;
                }
                int factor = (int)packet[1 + fi] - 0x80;
                ((float *)&last)[vi] += (float)factor * filter;
            }
        }
        from += 16;
        if (from > frame)
            value0 = 0;
    }
}
