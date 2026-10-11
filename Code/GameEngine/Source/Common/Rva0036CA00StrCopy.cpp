// cl: /Ob0 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
inline void *operator new(unsigned int, void *p) { return p; }
class Rva0036CA00Str {
    void *m_item;
public:
    __declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
    ~Rva0036CA00Str();
};
// Every TU that copies this handle emits the same select-any body; a strong definition here would
// be a duplicate of theirs at link time, so the row is the (noinline) inline form plus an anchor
// that keeps it emitted.
__declspec(noinline) inline Rva0036CA00Str::Rva0036CA00Str(const Rva0036CA00Str &other) : m_item(other.m_item) {
    if (m_item) InterlockedIncrement((long volatile *)((char *)m_item + 4));
}

// ?bfmeAnchorRva0036CA00StrCopy absent-from-retail
void *bfmeAnchorRva0036CA00StrCopy(void *where, const Rva0036CA00Str *src) {
    return new (where) Rva0036CA00Str(*src);
}
