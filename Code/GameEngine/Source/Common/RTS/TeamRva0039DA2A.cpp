// cl: /DNDEBUG /MD
// ?rva0039DA2A@Team@@QBEPAUCoord3D@@PAU2@@Z @ 0x0039DA2A 202B (ours 202B exact size/count, 0 structural, 0 register)
// Team centroid: averages live member positions.
// Explicit result-buffer ABI view: WB EF5250 and retail79DADE return the
// result address in EAX. Callers may consume it directly or ignore it; this
// reconciles the former void-output and aggregate-return declarations. Walks via rowed iterate_TeamMemberList 0x263864 + DLINK advance pin 0x263526 (pin 5911),
// skips Object+0x438 bit0 dead + Object+0x94 bit0 status (TeamHasAnyObjects precedent), sums Object+0x38/0x3C/0x40 Coord3D,
// divides by count via the 1.0f literal at 0xBBB8D8. Neighbours rva0039D9E3/rva0039DC63 share /O1 flags + 24B iterator.
// Near miss: X accumulation operand order (retail movss sum/addss pos vs ours movss pos/addss sum, 2 insns) + global reloc;
// Y/Z, frame, dec-chain-free SSE arithmetic, empty/average shared write tail (ox=x oz=z oy=y order) all exact.

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object;

template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
    OBJCLASS *m_cur;
    unsigned char m_targetAbiState[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};

class Object
{
public:
    unsigned char m_pad0[4];
    void *m_template;
    unsigned char m_pad08[0x38 - 0x08];
    Coord3D m_position;
    unsigned char m_pad44[0x94 - 0x44];
    unsigned char m_status94;
    unsigned char m_pad95[0x258 - 0x95];
    void *m_ai;
    unsigned char m_pad25C[0x438 - 0x25C];
    unsigned char m_dead;
};

struct Rva0039E9A1Slot
{
    unsigned char m_padB0[0xB0];
    Coord3D m_pos;
    unsigned char m_flagBC;
};

class Team
{
public:
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
    Coord3D *rva0039DA2A(Coord3D *out) const;
    Coord3D *rva0039E9A1(Coord3D *out) const;
private:
    unsigned char m_pad00[0x30];
    int m_slotBase30;
};

Coord3D *Team::rva0039DA2A(Coord3D *out) const
{
    Coord3D sum;
    sum.x = 0.0f;
    sum.y = 0.0f;
    sum.z = 0.0f;
    int count = 0;
    for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
        Object *cur = iter.cur();
        if ((cur->m_dead & 1) != 0)
            continue;
        if ((cur->m_status94 & 1) != 0)
            continue;
        sum.x = *(const volatile float *)&sum.x + cur->m_position.x;
        sum.y += cur->m_position.y;
        sum.z += cur->m_position.z;
        ++count;
    }
    float ox;
    float oy;
    float oz;
    if (count > 0) {
        float inv = 1.0f / (float)count;
        ox = sum.x * inv;
        oy = sum.y * inv;
        oz = sum.z * inv;
    }
    else {
        ox = sum.x;
        oz = sum.z;
        oy = sum.y;
    }
    out->x = ox;
    out->y = oy;
    out->z = oz;
    return out;
}

// ?rva0039E9A1@Team@@QBEPAUCoord3D@@PAU2@@Z, retail 0x0039E9A1, 63 bytes.
// Flagged position slot at (m_slotBase30 + 0x12C): when the slot pointer
// is set and its +0xBC flag is nonzero, its +0xB0 Coord3D is the answer;
// otherwise the live-member centroid rva0039DA2A fills it in. Both paths
// hand the output pointer back (retail keeps out in eax at the shared
// return), so the call is a real call, not a tail jump. The +0x30 base
// plus 0x12C add and the two early-outs are retail facts; the slot
// owner's identity beyond this relation is unresolved.
Coord3D *Team::rva0039E9A1(Coord3D *out) const
{
    const Rva0039E9A1Slot *slot = (const Rva0039E9A1Slot *)(m_slotBase30 + 0x12C);
    if (slot != 0 && slot->m_flagBC != 0)
    {
        const Coord3D *pos = &slot->m_pos;
        out->x = pos->x;
        out->y = pos->y;
        out->z = pos->z;
        return out;
    }
    rva0039DA2A(out);
    return out;
}
