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
namespace StrategicHUD { class ArmyUnitIconMovieClip { public: void SetUpgradeIconImage(int,const Image *); }; }
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
