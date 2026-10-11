// ?rva005F4254@Rva005F4254@@QAE?AUTreeHintRef00217D4C@@XZ
// partial score=0.9699 date=2026-10-11
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native 5F4254..5F42FF, RET4. Complete counted-help factory fallback.
// The negative accesses and virtual-base adjustment are retail evidence;
// the original receiver and method names remain unknown.
#include "ascii_string.h"
#include "unicode_string.h"
struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C {
    TreeHintRef00217D4C(TargetRef00217D4C *p) : m_ptr(p) {
        if (m_ptr) ++m_ptr->references;
    }
    TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {
        if (m_ptr) ++m_ptr->references;
    }
    ~TreeHintRef00217D4C() {
        if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
    }
    TargetRef00217D4C *m_ptr;
};
class Rva001524CA {
public:
    TreeHintRef00217D4C rva001524CA();
};
class ThingTemplate;
class ThingFactory {
public:
    const ThingTemplate *findTemplate(const AsciiString &key);
};
extern ThingFactory *TheThingFactory;
class Rva0037DCA5 {
public:
    void *rva0040C65D(int index);
};
class InGameSimpleHelp {
public:
    InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
private:
    char m_opaque[12];
};
class Rva005F4254 {
public:
    TreeHintRef00217D4C rva005F4254();
};
TreeHintRef00217D4C Rva005F4254::rva005F4254()
{
    Rva0037DCA5 *entry = *(Rva0037DCA5 **)((char *)this - 0xc);
    const AsciiString &key = *(const AsciiString *)((char *)entry + 4);
    if (!((const StringBase<char> *)&key)->isEmpty()) {
        const ThingTemplate *found = TheThingFactory->findTemplate(key);
        if (found) {
            void *owner = *(void **)((char *)this - 0x10);
            UnicodeString *title = (UnicodeString *)(*(Rva0037DCA5 **)((char *)this - 0xc))->rva0040C65D(*(int *)((char *)owner + 0x54));
            if (!title->isEmpty()) {
                const UnicodeString &text = *(const UnicodeString *)((char *)found + 0x40);
                return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(*title, text));
            }
        }
    }
    int offset = (*(int **)((char *)this - 0x14))[1];
    return ((Rva001524CA *)((char *)this + offset - 0x14))->rva001524CA();
}
