// BuildQueueDetailsPanel observer: queued army unit, native 0x005E868F (337 B).
// WorldBuilder supplies the callback and owner identity. Native observer entry
// is Impl+0x0C; callers, member accesses and constructors prove the layouts.
// STLport 4.5.3 insertion at 0x005E8293 (189 B) is recovered from the pinned
// reference cee35b7d8ca077d7255f1c39cb69e9fd9627aa85 and native calls.
// The placement-copy and copy-backward bodies must remain visible: their
// no-escape behavior controls register allocation and temporary stack homes.
// See reverse/attempt_evidence/0x005e868f_crack_i.txt.
class Rva004E3184;
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/vendor/stlport
class Rva005E7ED7;
struct Rva005E76AEContext;
class Rva005E72B4Queue;

namespace StrategicHUD
{
class BuildQueueIconSlot
{
public:
	virtual bool v0();
	virtual void v1(void *listener);
	virtual void v2();
	virtual void v3(void *value);
	virtual void v4();
	virtual void v5(int value);
	virtual void v6();
	virtual void SetQuantity(int quantity);
	virtual void v8();
	virtual void SetState(int state);
};
}

// Impl::GetIconAtQueueIndex in WorldBuilder (rowed address-named, 0x005E73E4).
class Rva005E73E4
{
public:
	void *rva005E73E4(int queueIndex);
};

// The icon's help hide check (rowed address-named, 0x005E73B2).
class Rva005E73B2
{
public:
	void rva005E73B2();
};


class Rva005F830A {
public: virtual ~Rva005F830A();
private: void *m_heap;
};
class Rva005EObserver08 {
public:
 virtual void v0(void *) {} virtual void v1(void *) {} virtual void v2(void *) {}
 ~Rva005EObserver08() {}
};
class Rva005EObserver0C {
public:
 virtual void v0(Rva005E72B4Queue &) {}
 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitDequeued(Rva005E72B4Queue &,int)=0;
 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitQueued(Rva005E72B4Queue &,int)=0;
 ~Rva005EObserver0C() {}
};
struct Rva005E71C6Ref;
#include <stl/_algobase.h>
namespace _STL { template <> inline const unsigned int &max<unsigned int>(const unsigned int &a,const unsigned int &b){return a<b?b:a;} }
#include <vector>

namespace StrategicInGameUI
{
class BuildQueueDetailsPanel
{
public:
	class Impl;
};

class BuildQueueDetailsPanel::Impl : public Rva005F830A, public Rva005EObserver08, public Rva005EObserver0C
{
public:
	class Icon;
	class InProgressIcon;
	friend class Icon;
 friend class InProgressIcon;
	friend class ::Rva005E7ED7;

 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitQueued(Rva005E72B4Queue &,int);
 virtual void onLivingWorldBuildingNuggetSpawnArmyUnitDequeued(Rva005E72B4Queue &,int);
	void SelectQueueIndex(int queueIndex);
	void ShowUnitStats(int queueIndex); // 0x005E7B28 (WorldBuilder name, pinned)

private:
	Icon *GetIconAtQueueIndex(int queueIndex) { return (Icon *)((Rva005E73E4 *)this)->rva005E73E4(queueIndex); }

 void *m_owner;
 void *m_help; // native hover-help caller follows +14
 Rva005E76AEContext *m_context;
 Rva005E72B4Queue *m_queue;
 InProgressIcon *m_first;
 _STL::vector<Rva005E71C6Ref> m_icons;
	int m_selectedQueueIndex; // +0x30, -1 when none
};

// The +0x1C member cleared by the ctor and destroyed on unwind.
struct Rva005E7D77Member
{
	Rva005E7D77Member() : m_value(0) {}
	~Rva005E7D77Member();

	int m_value;
};

// Target facts: vtable 0x00877F14 = { 0x005E7DF7, 0x005E712A, 0x005E73DC,
// 0x005E7977, 0x005E715F, 0x005E7166 }: the icon slot's listener. WorldBuilder
// names slots 0..3 OnBuildQueueIconSlotLeftClicked / RightClicked / RollOut /
// RollOver; slots 4 and 5 (clear / set +0x21) are unnamed there.
class BuildQueueDetailsPanel::Impl::Icon
{
public:
	Icon(Impl *owner, int queueIndex, StrategicHUD::BuildQueueIconSlot *iconSlot, void *value10, int value14, int quantity);
	~Icon(); // native constructor EH calls existing 61B body5E7C19
	void Select();
	void Deselect(); // 0x005E7111 (rowed)
	void rva005E7C56();
	void rva005E789A(); // 0x005E789A (pinned)

	virtual void OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRightClicked(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E715F(StrategicHUD::BuildQueueIconSlot *slot);
	virtual void rva005E7166(StrategicHUD::BuildQueueIconSlot *slot);

friend class ::Rva005E7ED7;
private:
	StrategicHUD::BuildQueueIconSlot *GetIconSlot() { return m_iconSlot; }

	Impl *m_owner;									// +0x04
	int m_queueIndex;								// +0x08
	StrategicHUD::BuildQueueIconSlot *m_iconSlot;	// +0x0C
	void *m_10;										// +0x10
	int m_14;										// +0x14
	int m_quantity;									// +0x18
	Rva005E7D77Member m_1c;							// +0x1C
	bool m_selected;								// +0x20
	bool m_21;										// +0x21
};
}

struct Rva005E72B4Production { int *begin,*end,*capacity; };
class Rva005E72B4Queue { public:
 virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
 virtual bool slot4(int,Rva004E3184 *);
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual int slot12();
 virtual const Rva005E72B4Production *slot13();
};
struct Rva005E72B4Entry { char bytes[8]; };
class Rva0007DF07 {
public:
 inline Rva0007DF07() : m_refCount(0) {}
 virtual ~Rva0007DF07() {}
 void AddRef() { ++m_refCount; }
private: int m_refCount;
};
class Rva005E7ED7 : public StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon, public Rva0007DF07 {
public:
 typedef StrategicInGameUI::BuildQueueDetailsPanel::Impl Owner;
 Rva005E7ED7(Owner *,int);
 void MoveTo(int);
 virtual ~Rva005E7ED7();
private: StrategicHUD::BuildQueueIconSlot *slot;
};
class StrategicInGameUI::BuildQueueDetailsPanel::Impl::InProgressIcon : public StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon {
public:
 InProgressIcon(Impl *,bool);
 void Init(bool);
private: StrategicHUD::BuildQueueIconSlot *m_progressSlot;
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva005E71C6Ref {
 Rva005E7ED7 *object; Rva005E7ED7 *operator->()const {return object;}
 Rva005E71C6Ref(const Rva005E71C6Ref &r):object(r.object){if(object)object->AddRef();}
 Rva005E71C6Ref &operator=(const Rva005E71C6Ref &);
 Rva005E71C6Ref(Rva005E7ED7 *p) : object(p) { if(object) object->AddRef(); }
 ~Rva005E71C6Ref() { if(object) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)(Rva0007DF07 *)object); }
};
class Rva005E7198;
inline Rva005E71C6Ref &Rva005E71C6Ref::operator=(const Rva005E71C6Ref &r){if(this==&r)return *this;Rva005E7ED7 *n=r.object;if(n)n->AddRef();Rva005E7ED7 *o=object;if(o)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)(Rva0007DF07*)o);object=r.object;return *this;}
namespace _STL {template <> __declspec(nothrow) void _Construct<Rva005E71C6Ref,Rva005E71C6Ref>(Rva005E71C6Ref *p,const Rva005E71C6Ref &r){new(p) Rva005E71C6Ref(r);}}
Rva005E7198 *__cdecl Rva005E7256CopyBackward(Rva005E7198 *,Rva005E7198 *,Rva005E7198 *,void *,int);
namespace _STL {__declspec(noinline) Rva005E71C6Ref *__copy_backward_ptrs(Rva005E71C6Ref *f,Rva005E71C6Ref *l,Rva005E71C6Ref *r,const __false_type &){char tag;return (Rva005E71C6Ref*)Rva005E7256CopyBackward((Rva005E7198*)f,(Rva005E7198*)l,(Rva005E7198*)r,&tag,0);}}
class Rva005E7D72;
class Rva005E7FE2 { public: void reset(Rva005E7D72 *); };
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::onLivingWorldBuildingNuggetSpawnArmyUnitQueued(Rva005E72B4Queue &nugget,int index)
{
 if(index>7) return;
 if(index<=m_selectedQueueIndex) ++m_selectedQueueIndex;
 if(index==0) {
  if(m_first) m_first->Init(false);
  else ((Rva005E7FE2 *)&m_first)->reset((Rva005E7D72 *)new StrategicInGameUI::BuildQueueDetailsPanel::Impl::InProgressIcon(this,false));
  index=1;
 }
 const Rva005E72B4Production *production=m_queue->slot13();
 if((unsigned)(production->end-production->begin)>1) {
  if(m_icons.size()>=7) {
   m_icons.pop_back();
  }
  int size=m_icons.size();
  for(int i=index-1;i<size;++i) m_icons[i]->MoveTo(i+2);
  Rva005E71C6Ref icon(new Rva005E7ED7(this,index));
  m_icons.insert(m_icons.begin()+index-1,icon);
  if(index==m_selectedQueueIndex) icon->Select();
 }
}
