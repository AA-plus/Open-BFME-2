// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
// AddUpgradeIcons: WB 1627540 names ArmyUnitIcon and this source (line189).
// Native5F4917..5F49F0 is the complete217-byte RET0 body. Unit+8,
// clip+C and upgrade list+10 agree with the factory and DoUpdate siblings.
// Unit upgrade flags+10 and template flags+404 have32 unsigned words;
// UpgradeTemplate image+90 is accessed only after a successful lookup.
// The unsigned bit test and retained unit pointer reproduce every native byte.
// List append uses the existing4-byte storage-ABI provider at2E01C6 through
// its already pinned pointer spelling; this does not assert science semantics
// or introduce another typed fold. Views describe accessed fields only.
#include "ascii_string.h"
#include "unicode_string.h"
namespace _STL {
template<unsigned int N> struct _Base_bitset {
 unsigned int words[N];
 bool _M_is_any() const;
 __forceinline bool test(unsigned int bit) const { return (words[bit >> 5] & (1U << (bit & 31))) != 0; }
};
}
class Rva00406F9C { public: bool rva00406F9C(const void *); };
struct UnitView { int unknown; AsciiString name; int unknown08; int rank; _STL::_Base_bitset<32> upgrades; };
class ThingTemplate;
struct TemplateView { char unknown00[0x404]; _STL::_Base_bitset<32> upgrades; };
class ThingFactory { public: const ThingTemplate *findTemplate(const AsciiString &); };
extern ThingFactory *TheThingFactory;
class UpgradeTemplate;
class UpgradeCenter { public: const UpgradeTemplate *rva0026EEA0(int) const; };
extern UpgradeCenter *TheUpgradeCenter;
class Image;
struct UpgradeView { char unknown00[0x90]; const Image *image; };
class AptMovieClipFrame;
namespace StrategicHUD { class ArmyUnitIconMovieClip { public: ArmyUnitIconMovieClip(AptMovieClipFrame *); void SetUpgradeIconImage(int,const Image *); private: char opaque[0x50]; }; class ArmyMemberIconMovieClip { public: void rva005FC9E0(const Image *); }; }
class Rva0040E6D6Sub { public: void forward(int *); };
struct UnitUpgradeList {
 int *begin,*end,*capacity;
 __forceinline unsigned size() const { return end-begin; }
 __forceinline void push_back(int &id) { ((Rva0040E6D6Sub *)this)->forward(&id); }
};
class Rva005F41AF { public: virtual void DoUpdate(); void rva005F41AF(); };
struct UnitClipHolder { void *p; __forceinline void *get() const { return p; } };
namespace StrategicInGameUI {
class ArmyUnitIcon : public virtual Rva005F41AF {
public: virtual void DoUpdate(); void AddUpgradeIcons();
private: int owner; UnitView *unit; UnitClipHolder clip; UnitUpgradeList upgrades; int unknown1c;
};
}
void StrategicInGameUI::ArmyUnitIcon::AddUpgradeIcons() {
 UnitView *entry = unit;
 const _STL::_Base_bitset<32> *bits = &entry->upgrades;
 if (!bits->_M_is_any()) return;
 const AsciiString &name = entry->name;
 if (((const StringBase<char> *)&name)->isEmpty()) return;
 const ThingTemplate *found = TheThingFactory->findTemplate(name);
 if (!found) return;
 const _STL::_Base_bitset<32> *available = &((const TemplateView *)found)->upgrades;
 if (!((Rva00406F9C *)bits)->rva00406F9C(available)) return;
 for (int id=0; id<1024; ++id) {
  if (bits->test(id) && available->test(id)) {
   const UpgradeTemplate *upgrade = TheUpgradeCenter->rva0026EEA0(id);
   if (!upgrade) continue;
   const Image *image = ((const UpgradeView *)upgrade)->image;
   if (!image) continue;
   ((StrategicHUD::ArmyUnitIconMovieClip *)clip.get())->SetUpgradeIconImage(upgrades.size(), image);
   upgrades.push_back(id);
   if (upgrades.size() >= 4) break;
  }
 }
}

struct TargetRef00217D4C { void *vtable; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 __forceinline TreeHintRef00217D4C(TargetRef00217D4C *p):m_ptr(p) { if(m_ptr) ++m_ptr->references; }
 __forceinline TreeHintRef00217D4C(const TreeHintRef00217D4C &other):m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->references; }
 ~TreeHintRef00217D4C() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
 TargetRef00217D4C *m_ptr;
};
class Rva002BED91 { public: void set(TargetRef00217D4C *); };
class Rva005FC9F0 { public: void rva005FC9E8(const Image *); void rva005FC9F0(int); };
class Rva0037E07C { public: int rva0037E07C(); };
struct StrategicButtonImageView; struct Rva005F01D6In;
namespace StrategicInGameUI { const Image *GetButtonImage(const StrategicButtonImageView *,int); }
const Image *Rva005F01D6Get(Rva005F01D6In *);
// WB1626A60 names CreateMovieClip (this file, line103). Retail5F49F0
// is the complete171-byte counted-return factory, with a secondary receiver:
// owner-1C, unit-18, clip-14, primary receiver-20. The ABI projection keeps
// its address-derived spelling until the enclosing virtual-base contract is
// reconciled. Allocates50 bytes via the established414-byte clip constructor,
// sets portrait/type/count through owned providers, then calls AddUpgradeIcons.
// Capturing each clip before its argument calls preserves retail evaluation
// order; the counted return inlines the reference increment and hidden result.
class Rva005F49F0 { public: TreeHintRef00217D4C rva005F49F0(AptMovieClipFrame *); };
TreeHintRef00217D4C Rva005F49F0::rva005F49F0(AptMovieClipFrame *frame) {
 TargetRef00217D4C *made = (TargetRef00217D4C *)new StrategicHUD::ArmyUnitIconMovieClip(frame);
 Rva002BED91 *holder = (Rva002BED91 *)((char *)this - 0x14);
 holder->set(made);
 int player = *(int *)((char *)*(void **)((char *)this-0x1c)+0x54);
 StrategicHUD::ArmyMemberIconMovieClip *portrait = (StrategicHUD::ArmyMemberIconMovieClip *)*(void **)holder;
 portrait->rva005FC9E0(StrategicInGameUI::GetButtonImage(*(const StrategicButtonImageView **)((char *)this-0x18),player));
 Rva005FC9F0 *type = (Rva005FC9F0 *)*(void **)holder;
 type->rva005FC9E8(Rva005F01D6Get(*(Rva005F01D6In **)((char *)this-0x18)));
 Rva005FC9F0 *quantity = (Rva005FC9F0 *)*(void **)holder;
 quantity->rva005FC9F0((*(Rva0037E07C **)((char *)this-0x18))->rva0037E07C());
 ((StrategicInGameUI::ArmyUnitIcon *)((char *)this-0x20))->AddUpgradeIcons();
 return TreeHintRef00217D4C(*(TargetRef00217D4C **)holder);
}

class Rva001524CA { public: TreeHintRef00217D4C rva001524CA(); };
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
// Complete171-byte help factory5F4254..5F42FF RET4. The secondary
// receiver accesses unit-C and owner-10; fallback consults vbptr-14 and
// calls the independently rowed18-byte empty-help provider1524CA. Original
// virtual method spelling is still unknown. A name accessor reproduces the
// retail retained field pointer; title comes from40C65D for owner playerID54,
// description from template40. Allocates the measured12-byte InGameSimpleHelp
// and returns the same counted-reference ABI used by the clip factory.
class Rva005F4254 {
public:
    TreeHintRef00217D4C rva005F4254();
    __forceinline const AsciiString &getName() const { return (*(UnitView **)((char *)this-0xc))->name; }
};
TreeHintRef00217D4C Rva005F4254::rva005F4254()
{
    const AsciiString *key = &getName();
    if (!((const StringBase<char> *)key)->isEmpty()) {
        const ThingTemplate *found = TheThingFactory->findTemplate(*key);
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
