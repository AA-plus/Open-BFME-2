// ?rva00278440@Rva00278440Host@@QAEXH@Z
// partial score=1.0 date=2026-10-12
// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/GameEngine/Include /Ireference/shims/bfme2_ascii
// Native27824D..278341 selects a counted4-byte audio reference. The ZH
// Drawable audio getters are a semantic lead; BFME selectors and fallback
// policy are reconstructed from this native body, so its name remains neutral.
// Field10C and record choice+4 are target accesses. The ABI views bind owned
// constructors51914/A8C7C/2390CB and factory274DD4, not invented callee names.
// The owned31B copy is a null-tested InterlockedIncrement and is declared
// nonthrowing by its provider; this suppresses an extra fallback EH state.
#include "Common/BfmeAudioEventPrefix136.h"
class AudioEventInfo;
class AudioEventInfoRef {public:AudioEventInfoRef(const AudioEventInfo *);AudioEventInfoRef():value(0){} OpaqueRefCounted *value;};
class Rva0036CA00Str {
public:
 AudioEventInfoRef handle;
 Rva0036CA00Str() {}
 Rva0036CA00Str(const AudioEventInfo *p):handle(p){}
 Rva0036CA00Str(const Rva0036CA00Str &) throw();
 ~Rva0036CA00Str(){OpaqueRefCounted *const volatile &value=handle.value;if(value)value->Release_Ref();}
};
class Rva002390CB {
public:
 Rva002390CB(const Rva002390CB &);
 void *unknown;
 Rva0036CA00Str choice;
};
Rva0036CA00Str Rva00274DD4();
// The same by-value four-byte owner is passed by the verified map-properties
// caller at 0x0029576F. It is released after the string temporary at this entry.
struct Rva0010F149Handle
{
 Rva0010F149Handle(const Rva0010F149Handle &);
 ~Rva0010F149Handle() { if (referent) referent->Release_Ref(); }
 OpaqueRefCounted *referent;
};
class Rva004EC166
{
public:
 void rva00433403(const AsciiString &);
};
class Drawable {
public:
 char pad100[0x100];
 int customNameID;
 char pad104[8];
 const AudioEventInfo *raw;
 char pad110[0x38];
 int secondaryHandle;
 char pad14c[0x11c];
 unsigned int flags268;
 char pad26c[0x1dc];
 unsigned char flag448;
 unsigned char flag449;
 unsigned char flag44A;
 Rva002390CB rva0027756D(int);
 Rva002390CB rva00276893();
 Rva0036CA00Str rva0027824D(int);
 void rva002781DA(Rva0010F149Handle);
 void rva002743D7();
 void rva002784EB();
};
Rva0036CA00Str Drawable::rva0027824D(int selector)
{
 if(selector!=3 && raw) {
  bool different;
  different=raw!=(const AudioEventInfo *)Rva00274DD4().handle.value;
  if(different)return Rva0036CA00Str(raw);
 } else {
  Rva002390CB first=rva0027756D(selector);
  if(first.choice.handle.value)return first.choice;
  if(selector!=0 && selector!=3){Rva002390CB fallback=rva0027756D(0);if(fallback.choice.handle.value)return fallback.choice;}
 }
 return Rva0036CA00Str();
}

// Native 0x002781DA..0x0027824D: by-value audio-info rename, RET4.
// Target facts: Drawable receiver from the matched map-properties caller;
// identifier +0x100, incoming name +8, exact format literal and all callees.
// Donor audio naming is a semantic lead only; the original method name is unknown.
void Drawable::rva002781DA(Rva0010F149Handle info)
{
 AsciiString name;
 name.format(" CUSTOM %d ", customNameID);
 name.concat(*reinterpret_cast<const AsciiString *>(
  reinterpret_cast<const char *>(info.referent) + 8));
 reinterpret_cast<Rva004EC166 *>(info.referent)->rva00433403(name);
}

class Rva001D98BD { public: int rva001D9781(); };
template<int N> class DrawableAudioSlots : public DrawableAudioSlots<N-1>
{ public: virtual void unused(char (*)[N])=0; };
template<> class DrawableAudioSlots<0> {};
class DrawableAudioView : public DrawableAudioSlots<25>
{ public: virtual int add(BfmeAudioEventPrefix136 *); };
class DrawableAudioStatusView : public DrawableAudioSlots<52>
{ public: virtual bool active(int); };
class AudioManager;
extern AudioManager *TheAudio;
class Rva00278341Host
{
public:
 char pad100[0x100];
 DrawableID identifier;
 char pad104[0xc];
 OpaqueRefElement4 playing;
 char pad114[0x30];
 int playingHandle;
 char pad148[0x2ff];
 unsigned char flag447;
 unsigned char flag448;
 unsigned char flag449;
 unsigned char flag44A;
 unsigned char flag44B;
 void rva00278341(int selector, int permanent);
};

// Native181-byte entry: two stack words, event prefix88 and owned handle4.
// Target offsets and calls establish this shape; the semantic ambient-start
// lead comes from BFME1 Drawable, not a recovered original method identity.
void Rva00278341Host::rva00278341(int selector, int permanent)
{
 Drawable *drawable=reinterpret_cast<Drawable *>(this);
 drawable->rva002743D7();
 Rva0036CA00Str info=drawable->rva0027824D(selector);
 if(info.handle.value && (!(unsigned char)permanent ||
     (unsigned char)reinterpret_cast<Rva001D98BD *>(info.handle.value)->rva001D9781()))
 {
  const OpaqueRefElement4 &owner=reinterpret_cast<const OpaqueRefElement4 &>(info);
  BfmeAudioEventPrefix136 event(owner,identifier);
  playingHandle=reinterpret_cast<DrawableAudioView *>(TheAudio)->add(&event);
  playing=owner;
 }
 flag44B=0;
}

// Target235-byte refresh: keyed record29 supplies its counted +4 choice;
// the temporary record dies after that copy, before the event is constructed.
void Drawable::rva002784EB()
{
 if(flag449 && flag448 && flag44A && ((static_cast<unsigned char>(flags268>>29)&1)!=0) &&
    !reinterpret_cast<DrawableAudioStatusView *>(TheAudio)->active(secondaryHandle))
 {
  Rva0036CA00Str info=rva00276893().choice;
  if(info.handle.value)
  {
   const OpaqueRefElement4 &owner=reinterpret_cast<const OpaqueRefElement4 &>(info);
   BfmeAudioEventPrefix136 event(owner,static_cast<DrawableID>(customNameID));
   secondaryHandle=reinterpret_cast<DrawableAudioView *>(TheAudio)->add(&event);
  }
 }
}

// Native278440..2784AF complete111B RET4. The matched2784AF wrapper
// and WB CB11D0 establish the receiver, selector and three flag-byte guard.
// Compare the selected counted owner with field110 and restart only on change.
// The local volatile reference in the owner destructor retains the two native
// reads around EH-state reset; it is a scheduling choice, not a claim that
// the historical member was volatile. The saved current owner preserves the
// native field load and memory-left comparison; the callee may replace it.
class Rva00278440Host : public Rva00278341Host
{ public: void rva00278440(int selector); };
// ?Rva00278440Host::rva00278440 present-unmatched
void Rva00278440Host::rva00278440(int selector)
{
 if(flag447 && flag448 && flag44A)
 {
  Rva0036CA00Str info=reinterpret_cast<Drawable *>(this)->rva0027824D(selector);
  OpaqueRefCounted *current=playing.referent;
  if(info.handle.value!=current)rva00278341(selector,0);
 }
}
