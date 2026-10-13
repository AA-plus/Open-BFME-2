// ?rva005D3D97@SelectionUIImpl@@QAEXXZ
// partial score=0.85 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C() : m_ptr(0) {}
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
        if (m_ptr) ++m_ptr->references;
    }
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
    __forceinline ~TreeHintRef00217D4C() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
};
class SelectionUIImpl {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    void rva005D3D97();
private:
    char m_pad04[0x20];
    int m_20;                        // +0x20
    TreeHintRef00217D4C m_aptRef;    // +0x24
};
void SelectionUIImpl::rva005D3D97()
{
    s9();
    s4();
    m_20 = 0;
    TreeHintRef00217D4C temp;
    m_aptRef = temp;
}
