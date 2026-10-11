// ?rva0028D900@Object@@QAE_NPAM0@Z
// partial score=0.95 date=2026-10-10
// cl: /O1 /DNDEBUG /MD /arch:SSE
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
struct Sub028D900
{
    char m_pad[0x10D];
    unsigned char m_flag10D;
    char m_pad2[0x534 - 0x10D - 1];
    float m_val534;
};
class Object
{
public:
    bool rva0028D900(float *out1, float *out2);
private:
    char m_pad0[4];
    Sub028D900 *m_sub4;
    char m_pad8[0xB0];
    float m_multB8;
};
bool Object::rva0028D900(float *out1, float *out2)
{
    if (m_sub4->m_flag10D & 0x80)
    {
        *out1 = 0.0f;
        *out2 = 0.0f;
        return false;
    }
    float v = 1.5f;
    if (m_sub4)
        v = m_sub4->m_val534;
    float s = max(20.0f, min(150.0f, m_multB8 * v));
    *out1 = 3.0f;
    *out2 = max(20.0f, s * 2.0f);
    return true;
}

// --- LK8 r4 appendix (member-vs-local null-check + coupling data) ---
// Transplant into DrawableDrawLevelNumber.cpp (TU-merged views) reaches the
// documented 151-vs-154B XMM wall identically. Two new findings: (1) a
// LOCAL Sub028D900* (single load, 3 uses) folds the `if (sub)` null test
// away (compiler proves non-null from the earlier deref); MEMBER accesses
// (m_sub4, as in this stash) keep it: structure alone decides, not flags.
// (2) Defining Object::rva0028D900 beside DrawableDrawIconUI's drawIconUI
// breaks drawIconUI (frame 0x30->0x2C, obj EDI->EBX) although renames, view
// edits, macros and structs in isolation verify clean; order-swapping the
// definition does not help. Same unexplained-MSVC-coupling family as the
// CursorEqual case. The body therefore wants a home TU without a sensitive
// sibling (LevelNumber was tried: views merge clean, existing 237B body
// unaffected by the views, only the new function triggers nothing there --
// but the XMM wall itself remains). m_multB8 sits at +0xB8 (not +0xB0).
