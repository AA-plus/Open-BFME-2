// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// partial score=0.95 date=2026-10-13
// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// partial score=0.95 date=2026-10-12
// ?isMusicAlreadyLoaded@AudioManager@@UBE_NXZ
// 2026-10-12 (claude-opus-5-5): 288B == retail with this unit. Visible
// noinline copies of AudioEventInfoRef's ctor (0x00051914) and
// OpaqueRefElement4::operator= (0x00239099), both byte-exact, make cl keep
// the counted info in ESI and release it from there, as retail. Remaining
// 26 diff lines are loop layout only: retail jumps into a top test
// (mov eax,[ebp-0x28]; cmp eax,ebx; je exit) and re-tests music after the
// loop; cl rotates the loop to a bottom test and threads the break past
// the post-loop test. for(;;)/while/for(;cond;) and /G6 /G7 /Os flag sets
// are unchanged. Approved home is MilesAudioManager.cpp.
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include "Common/BfmeAudioEventPrefix136.h"
// Rowed at 0x00239099 (OpaqueRefOwnership.cpp); visible here so the unit
// knows the copy keeps no pointer to its source.
inline __declspec(noinline) OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
{
    if (this != &other) {
        if (other.referent)
            InterlockedIncrement(reinterpret_cast<Long volatile *>(reinterpret_cast<char *>(other.referent) + 4));
        if (referent)
            referent->Release_Ref();
        referent = other.referent;
    }
    return *this;
}
class AudioEventInfo { public: char before49[0x49]; unsigned char flags49; char after4A[0x66]; int kindB0; };
class AudioEventInfoRef
{
public:
 // Rowed at 0x00051914 (AudioEventInfoRefConstructor.cpp); visible so the
 // unit knows the reference keeps no pointer to itself.
 __declspec(noinline) AudioEventInfoRef(const AudioEventInfo *p) : info(p)
 {
  if (info)
   InterlockedIncrement(reinterpret_cast<Long volatile *>(reinterpret_cast<char *>(const_cast<AudioEventInfo *>(info)) + 4));
 }
 const AudioEventInfo *info;
};
struct NonNullAudioRef {
 AudioEventInfoRef value;
 __forceinline NonNullAudioRef(const AudioEventInfo*p):value(p){}
 __forceinline ~NonNullAudioRef(){ ((OpaqueRefCounted*)value.info)->Release_Ref(); }
};
struct ScopedMusicRef {
 OpaqueRefElement4 value;
 __forceinline ScopedMusicRef(){value.referent=0;}
 __forceinline ~ScopedMusicRef(){if(value.referent)value.referent->Release_Ref();}
};
class Rva000411084 { public: void *next(); void *current,*owner; Rva000411084(){}; Rva000411084(const Rva000411084&x):current(x.current),owner(x.owner){} };
class Rva000427195 { public: void *first(Rva000411084*); };
struct AudioEventNode { void *next; AsciiString key; const AudioEventInfo* info; };
class AudioEventRTS { public: void rva002D9ADC(); AsciiString getFilename(); };
class FileSystem { public: bool doesFileExist(const char*)const; };extern FileSystem*TheFileSystem;
class AudioManager { public: virtual bool isMusicAlreadyLoaded()const; private: char prefix[0xb8]; mutable Rva000427195 table; };
bool AudioManager::isMusicAlreadyLoaded()const {
 ScopedMusicRef music;
 Rva000411084 it;
 { Rva000411084 first; table.first(&first); it=first; }
 for(;;) {
  if(!it.current)break;
  const AudioEventInfo *p=((AudioEventNode*)it.current)->info;
  if(p) {
   NonNullAudioRef ref(p);
   const AudioEventInfo *info=ref.value.info;
   if(info->kindB0==0 && !(info->flags49&6))
    music.value=*(const OpaqueRefElement4*)&ref.value;
  }
  it.next();
  if(music.value.referent)break;
 }
 if(!music.value.referent)return true;
 BfmeAudioEventPrefix136 aud(music.value,2);
 ((AudioEventRTS*)&aud)->rva002D9ADC();
 AsciiString name=((AudioEventRTS*)&aud)->getFilename();
 return TheFileSystem->doesFileExist(name.str());
}
