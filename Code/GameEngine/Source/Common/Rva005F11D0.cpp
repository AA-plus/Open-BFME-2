// cl: /O1 /MD /EHs /D_CRTIMP=
// Native5F11D0 complete63B range destructor: destroy first/end through5EF5EF,
// then free first through30830. Its EH action7A4C3F passes the range object
// itself to the existing14B free-first-pointer body7FAB3. A local guard's
// address was the wrong lifetime model; real base storage gives the native
// this-based unwind and the same automatic release after normal destruction.
// Only first/end0/4 are accessed; the enclosing105B destructor5F1295 gives
// this member the12B slot34..40. The trailing word and original type are unknown.
struct Rva005F0647;
void __cdecl Rva005EF5EFClear(Rva005F0647 *first, Rva005F0647 *last);
namespace _STL { void __cdecl free(void *block); }
template<class T> class Rva005F11D0Storage
{
public:
 T *m_first;
 T *m_last;
 unsigned char m_unmodelled08[4];
 ~Rva005F11D0Storage() { if(m_first) _STL::free(m_first); }
};
class Rva005F11D0 : public Rva005F11D0Storage<Rva005F0647>
{
public:
 ~Rva005F11D0();
};
typedef char RangeSlotHas12Bytes[sizeof(Rva005F11D0)==12 ? 1 : -1];
Rva005F11D0::~Rva005F11D0()
{
 Rva005EF5EFClear(m_first,m_last);
}
