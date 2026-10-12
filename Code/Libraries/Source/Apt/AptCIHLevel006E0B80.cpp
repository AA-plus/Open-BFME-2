// cl: /O2 /MD
// ?rva006E0B80@AptCIH@@QBEHH@Z, retail 0x006E0B80, 103 bytes.
// Level-indexed ancestor field accessor, "nLvl >= 0" assert at line 0x85C via
// file string at 0x008EB4A8. Evidence: rowed-assert helper shape shared with
// AptCIHEventHandlers neighbours; +0x48 parent chain depth count with -1 on
// over-level; +0x58 low-17-bit sign-extended result; callers at
// 0x006E2493/0x006E249F compare results signed; same /O2 shape as neighbours.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(__debugbreak, _ReadWriteBarrier)
class AptCIH {
    virtual void vtableSlot0();
    unsigned char _pad[0x40];
    void *m_44;
    AptCIH *m_parent;
    void *m_4C;
    unsigned char _pad3[8];
    int m_code;
public:
    int rva006E0B80(int nLvl) const;
    int rva006E0B60() const;
    bool rva006E2460(const AptCIH *other) const;
    void *rva006E0FB0() const;
    void *rva006E1020() const;
    void *rva006E1100() const;
    void *rva006E1170() const;
    void *rva006E1090() const;
    void rva006E1F00(int mask);
    const AptCIH *rva006E0CB0() const;
    bool rva006E0C50(const AptCIH *other) const;
    bool rva006E0BF0() const;
};
int AptCIH::rva006E0B80(int nLvl) const
{
    if (nLvl < 0) {
        g_bfmeAptAssertAtE17734("nLvl >= 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x85C);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    int depth = 0;
    for (const AptCIH *p = m_parent; p; p = p->m_parent)
        ++depth;
    if (nLvl > depth)
        return -1;
    const AptCIH *node = this;
    if (depth != nLvl) {
        int steps = depth - nLvl;
        do {
            node = node->m_parent;
        } while (--steps != 0);
    }
    return (node->m_code << 15) >> 15;
}

// ?rva006E2460@AptCIH@@QBE_NPBV1@@Z, retail 0x006E2460, 104 bytes.
// Ancestor-code comparison, true when other sorts strictly below this at the
// first differing level. Evidence: chain lane, calls rowed
// rva006E0B80 twice per level with the same index; self/depth-zero guards;
// caller at 0x006FB21E; same /O2 shape and AptCIH layout as above.
bool AptCIH::rva006E2460(const AptCIH *other) const
{
    int depth = 0;
    for (const AptCIH *p = m_parent; p; p = p->m_parent)
        ++depth;
    if (this == other || depth == 0)
        return false;
    for (int i = 0; i <= depth; ++i) {
        int a = rva006E0B80(i);
        int b = other->rva006E0B80(i);
        if (b < a)
            return true;
        if (b > a)
            break;
    }
    return false;
}

// ?rva006E0FB0@AptCIH@@QBEPAXXZ, retail 0x006E0FB0, 103 bytes.
// Static-text field accessor at +0x4C guarded by type 0x10 and defined checks,
// "this" assert at line 0xC9 and "isStaticTextInst()" at 0x87 via AptCIH.h.
// Evidence: rowed getters 0x6DBB30 and 0x6DC010; unlock lane; caller at
// 0x006E18FD; same /O2 AptCIH layout as neighbours. Barrier keeps the +0x4C
// load late (retail test-je-int3-mov, no hoist); emits no bytes.
class Rva006DBB30SarDwordField
{
public:
    int get() const;
};

class BfmeAptValue006DCD20
{
public:
    bool isUndefined() const;
    int isCharacterInst() const;
};

void *AptCIH::rva006E0FB0() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xC9);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() != 0x10 || ((const BfmeAptValue006DCD20 *)this)->isUndefined()) {
        g_bfmeAptAssertAtE17734("isStaticTextInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x87);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    _ReadWriteBarrier();
    return m_4C;
}

// ?rva006E0CB0@AptCIH@@QBEPBV1@XZ, retail 0x006E0CB0, 134 bytes.
// Parent-chain walker returning first ancestor (or self) whose get() is 0x12
// or 0x13 with !isUndefined(), "this" asserts at lines 0xD3 and 0xD8.
// Evidence: rowed getters 0x6DBB30 and 0x6DC010; unlock lane unblocking 7
// callers; same /O2 AptCIH layout (m_parent +0x48) as neighbours.
const AptCIH *AptCIH::rva006E0CB0() const
{
    const AptCIH *node = this;
    for (;;) {
        if (!node) {
            g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xD3);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (((const Rva006DBB30SarDwordField *)node)->get() == 0x12 && !((const BfmeAptValue006DCD20 *)node)->isUndefined())
            return node;
        if (!node) {
            g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xD8);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (((const Rva006DBB30SarDwordField *)node)->get() == 0x13 && !((const BfmeAptValue006DCD20 *)node)->isUndefined())
            return node;
        node = node->m_parent;
    }
}

// ?rva006E0C50@AptCIH@@QBE_NPBV1@@Z, retail 0x006E0C50, 85 bytes.
// Parent-chain membership test with !isUndefined() guard, +0x48 walk.
// Evidence: leaf with caller at 0x006FB209; rowed isUndefined 0x6DC010;
// same /O2 AptCIH layout as neighbours.
bool AptCIH::rva006E0C50(const AptCIH *other) const
{
    if (((const BfmeAptValue006DCD20 *)this)->isUndefined()) {
        g_bfmeAptAssertAtE17734("!this->isUndefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x8A8);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    for (const AptCIH *p = m_parent; p; p = p->m_parent) {
        if (other == p)
            return true;
    }
    return false;
}

// ?rva006E0BF0@AptCIH@@QBE_NXZ, retail 0x006E0BF0, 89 bytes.
// Ancestor float-threshold walk with !isUndefined() guard, +0x44/+0x2C check.
// Evidence: gap between 0x6E0B80 and 0x6E0C50; rowed isUndefined 0x6DC010;
// caller at 0x006FB1CD; same /O2 AptCIH layout as neighbours.
struct Rva006E0BF0Aux {
    unsigned char _pad[0x2C];
    float m_2C;
};
bool AptCIH::rva006E0BF0() const
{
    if (((const BfmeAptValue006DCD20 *)this)->isUndefined()) {
        g_bfmeAptAssertAtE17734("!this->isUndefined()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCIH.cpp", 0x885);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    for (const AptCIH *node = this; node; node = node->m_parent) {
        const Rva006E0BF0Aux *aux = (const Rva006E0BF0Aux *)node->m_44;
        if (aux && aux->m_2C < 0.5f)
            return false;
    }
    return true;
}

// ?rva006E1020@AptCIH@@QBEPAXXZ, retail 0x006E1020, 103 bytes.
// Morph-inst field accessor at +0x4C guarded by type 0x11 and defined checks,
// "this" assert at line 0xCE and "isMorphInst()" at 0x8C via AptCIH.h.
// Evidence: rowed getters 0x6DBB30 and 0x6DC010; unlock lane unblocking 2
// callers; same /O2 AptCIH layout as neighbours. Barrier keeps the +0x4C
// load late (retail test-je-int3-mov, no hoist); emits no bytes.
void *AptCIH::rva006E1020() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xCE);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() != 0x11 || ((const BfmeAptValue006DCD20 *)this)->isUndefined()) {
        g_bfmeAptAssertAtE17734("isMorphInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x8C);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    _ReadWriteBarrier();
    return m_4C;
}

// ?rva006E1100@AptCIH@@QBEPAXXZ, retail 0x006E1100, 103 bytes.
// Shape-inst field accessor at +0x4C guarded by type 0x0C and defined checks,
// "this" assert at line 0xBF and "isShapeInst()" at 0xA0 via AptCIH.h.
// Evidence: rowed getters 0x6DBB30 and 0x6DC010; unlock lane unblocking 1
// caller; same /O2 AptCIH layout as neighbours. Barrier keeps the +0x4C
// load late (retail test-je-int3-mov, no hoist); emits no bytes.
void *AptCIH::rva006E1100() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xBF);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() != 0x0C || ((const BfmeAptValue006DCD20 *)this)->isUndefined()) {
        g_bfmeAptAssertAtE17734("isShapeInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xA0);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    _ReadWriteBarrier();
    return m_4C;
}

// ?rva006E1170@AptCIH@@QBEPAXXZ, retail 0x006E1170, 51 bytes.
// Character-inst field accessor at +0x4C guarded by isCharacterInst check
// at line 0xA5 via AptCIH.h. Evidence: rowed 0x6E0200; unlock lane unblocking
// 3 callers; same /O2 AptCIH layout as neighbours.
void *AptCIH::rva006E1170() const
{
    if ((unsigned char)((const BfmeAptValue006DCD20 *)this)->isCharacterInst() == 0) {
        g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xA5);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    _ReadWriteBarrier();
    return m_4C;
}

// ?rva006E1090@AptCIH@@QBEPAXXZ, retail 0x006E1090, 103 bytes.
// Button-inst field accessor at +0x4C guarded by type 0x0E and defined checks,
// "this" assert at line 0xB5 and "isButtonInst()" at 0x92 via AptCIH.h.
// Evidence: finish lane from banked 0x93 stash reverse/attempts/0x006e1090.cpp;
// rowed getters 0x6DBB30 and 0x6DC010; same /O2 AptCIH layout as neighbours.
// Barrier keeps the +0x4C load late (retail test-je-int3-mov, no hoist).
void *AptCIH::rva006E1090() const
{
    if (!this) {
        g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xB5);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    if (((const Rva006DBB30SarDwordField *)this)->get() != 0x0E || ((const BfmeAptValue006DCD20 *)this)->isUndefined()) {
        g_bfmeAptAssertAtE17734("isButtonInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x92);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    _ReadWriteBarrier();
    return m_4C;
}

// ?rva006E1F00@AptCIH@@QAEXH@Z, retail 0x006E1F00, 132 bytes (RET 4;
// callers AptAnimationPoolData::_tickNewInsts, the display-list
// instantiation 0x006F85E0 and three Rva006FB860 updates): sets the
// instance data's (0x006E1090) +0x18 mask; when it changes, clears the
// +0x1C display list (AptDisplayList::clear(false)) and re-submits every
// 0x44-byte record of the character (+0x0C: count +0x2C, records +0x30)
// whose +0x00 bits meet the mask through the pinned submit 0x006F8B70,
// with the record's +0x04 id, this instance, its +0x24 transform and +0x0C
// colour. Address-derived names for the instance and record views.
struct Rva006E1F00Record
{
	unsigned int m_mask;			// +0x00
	int m_id;						// +0x04
	unsigned char m_pad08[0x0c - 0x08];
	unsigned char m_color[0x24 - 0x0c];	// +0x0C
	float m_transform[(0x44 - 0x24) / 4];	// +0x24
};
struct Rva006E1F00Character
{
	unsigned char m_pad00[0x2c];
	int m_count;					// +0x2C
	Rva006E1F00Record *m_records;	// +0x30
};
class BfmeSubmitter1283
{
public:
	void bfmeSubmit1283(int a1, int a2, int a3, int a4, int a5, int a6, int a7, float *a8, int a9, int a10, int a11, int a12);	// 0x006F8B70
};
class AptDisplayList { public: void clear(bool deep); };	// 0x006F80C0
struct Rva006E1F00Instance
{
	unsigned char m_pad00[0x0c];
	Rva006E1F00Character *m_character;	// +0x0C
	unsigned char m_pad10[0x18 - 0x10];
	unsigned int m_mask;			// +0x18
	AptDisplayList m_displayList;	// +0x1C
};

void AptCIH::rva006E1F00(int mask)
{
    Rva006E1F00Instance *instance = (Rva006E1F00Instance *)rva006E1090();
    if (mask == (int)instance->m_mask)
        return;
    instance->m_mask = mask;
    instance->m_displayList.clear(false);
    for (int i = 0; i < instance->m_character->m_count; ++i)
    {
        if (instance->m_mask & instance->m_character->m_records[i].m_mask)
        {
            Rva006E1F00Record &record = instance->m_character->m_records[i];
            ((BfmeSubmitter1283 *)&instance->m_displayList)->bfmeSubmit1283(0, i, record.m_id, 0, (int)this, 0, -1,
                record.m_transform, (int)record.m_color, 0, 0, 0);
        }
    }
}

// ?rva006E0B60@AptCIH@@QBEHXZ, retail 0x006E0B60 (25B). Ghidra-unlisted depth
// of this CIH in its +0x48 parent chain (0 for a root), the same chain the
// level accessor above walks. Address-derived name.
int AptCIH::rva006E0B60() const
{
    int depth = 0;
    for (AptCIH *p = m_parent; p != 0; p = p->m_parent)
        ++depth;
    return depth;
}
