// ?rva0005BE59@MilesAudioManager@@QAEXPAXM0@Z
// partial score=0.97 date=2026-10-12
// ?rva0005BE59@MilesAudioManager@@QAEXPAXM0@Z
// Bank for 0x0005BE59 (789 B, RET 0xC; WB twin 0x0079F2C0), BFME 2's
// view-scoped Zero Hour adjustVolumeOfPlayingAudio, in
// Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp.
// Below is the diff against that unit (as of 2026-10-12) that compiles to
// 782 B with every call, the EH frame and all register roles of retail.
// Levers that got it there:
//  * a visible __declspec(noinline) in-class copy of rva0005A9F8 that reads
//    the playing pointer BY VALUE (a `*&` reference binding counts as
//    retaining the address): only then does cl keep the PlayingAudioRef's
//    pointer in EBX (EBX=0 doubling as its initial value) across the calls,
//    as retail does;
//  * the 3D loop alone reads the event into a local and compares through the
//    inline getViewType() (retail: event in EDI, iterator spilled to memory);
//  * a `MusicStack &stack` local (begin/end copies from +0, not +0x10) and a
//    queued loop whose end is cached in the for-initialiser.
// Remaining 7 B: retail rotates the music-stack inner loop (cmp [ebp-0x30],
// esi; je at the top, with EAX carrying viewType to both exits) where cl
// emits init; jmp cond. while/do/if-break/_M_cur/!(==)/post-increment/
// end-first (0x55FCA's form)/row pointer/typed (const AsciiString&,float,int)
// signature all keep the jmp form; the volume/pan stack slots are also swapped
// (retail volume and sample3D at -0x18, pan at -0x20).
#if 0
740a741,742
> extern "C" __declspec(dllimport) void __stdcall AIL_sample_volume_pan(void *sample, float *volume, float *pan);
> extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_volume_pan(void *sample, float volume, float pan);
961a964,979
> // Views 0x0005A9F8 reads through (as in its own unit).
> class Rva001D990C { public: bool rva001D990C(int v); };
> class Rva0005117B { public: float rva0005117B(float v); };
> struct Rva0005A9F8AudioEvent {
>     char m_pad00[8];
>     Rva001D990C *m_info;
>     char m_pad0C[0x52 - 0x0C];
>     bool m_flag52;
> };
> struct Rva0005A9F8PlayingAudio {
>     char m_pad00[0x1C];
>     Rva0005A9F8AudioEvent *m_event;
>     char m_pad20[0x30 - 0x20];
>     float m_fadeFrame;
> };
> 
1050c1068,1083
<     float rva0005A9F8(void *ref, int a, int b);
---
>     // Rowed at 0x0005A9F8 (MilesAudioManagerRva0005A9F8.cpp); visible here
>     // and kept out of line so callers know it does not hold on to the
>     // playing reference it reads.
>     __declspec(noinline) float rva0005A9F8(void *ref, int a, int b)
>     {
>         Rva0005A9F8PlayingAudio *playing = *(Rva0005A9F8PlayingAudio **)ref;
>         Rva0005A9F8AudioEvent *event = playing->m_event;
>         float volume = rva00059AD0(event, a);
>         if (b == 1)
>             volume *= ((Rva0005117B *)this)->rva0005117B(playing->m_fadeFrame);
>         event = playing->m_event;
>         if (event->m_flag52 && volume < 0.01f && event->m_info != 0
>             && !event->m_info->rva001D990C(2))
>             volume = 0.01f;
>         return volume;
>     }
5243a5277,5350
>     }
> }
> 
> // Retail 0x0005BE59 (pinned, RET 0xC; WorldBuilder twin 0x0079F2C0): BFME 2's
> // view-scoped form of Zero Hour's adjustVolumeOfPlayingAudio. For every
> // playing sound, 3D sound and non-music stream of the view type whose event
> // name matches (an empty name matches all) it refreshes the event's volume
> // (0x592B8) and hands the recomputed level (0x5A9F8) to the sample or stream;
> // matching music on the view's two stacks and matching queued events only get
> // the refresh (the queued loop passes the last playing event, as retail does).
> // The float argument is unused.
> void MilesAudioManager::rva0005BE59(void *slot, float value, void *index)
> {
>     const AsciiString &eventName = *reinterpret_cast<const AsciiString *>(slot);
>     int viewType = reinterpret_cast<int>(index);
>     PlayingAudioRef playing;
>     PlayingAudioList::iterator it;
>     for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
>         playing = *it;
>         if (playing.get()
>             && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                 || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
>             && playing->m_event->m_viewType == viewType) {
>             void *sample = get2DSampleHandleForPlayingAudio(&playing);
>             if (sample) {
>                 rva000592B8(playing->m_event.get());
>                 float pan;
>                 float volume = rva0005A9F8(&playing, 1, 1);
>                 AIL_sample_volume_pan(sample, 0, &pan);
>                 AIL_set_sample_volume_pan(sample, volume, pan);
>             }
>         }
>     }
>     for (PlayingAudioList::iterator it3D = m_playing3DSounds.begin(); it3D != m_playing3DSounds.end(); ++it3D) {
>         playing = *it3D;
>         if (playing.get()
>             && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                 || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)) {
>             AudioEventRTS *event = playing->m_event.get();
>             if (event->getViewType() == viewType) {
>                 void *sample3D = get3DSampleHandleForPlayingAudio(playing);
>                 if (sample3D) {
>                     rva000592B8(event);
>                     AIL_set_3D_sample_volume(sample3D, rva0005A9F8(&playing, 1, 1));
>                 }
>             }
>         }
>     }
>     for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
>         playing = *it;
>         if (playing.get()
>             && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                 || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
>             && playing->m_event->m_viewType == viewType
>             && playing->m_event->m_info->m_atB0 != 3) {
>             rva000592B8(playing->m_event.get());
>             ((Rva000A8AEE *)&playing->m_at0C)->rva000A8AEE(rva0005A9F8(&playing, 1, 1));
>         }
>     }
>     for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
>         MusicStack &stack = m_musicStack[viewType][musicSystem];
>         for (MusicStack::iterator music = stack.begin(), end = stack.end(); music != end; ++music) {
>             playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
>             if (playing.get()
>                 && (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>                     || reinterpret_cast<const BfmeAudioEventInfoNameView *>(playing->m_event->m_info)->getEventName() == eventName)
>                 && playing->m_event->m_viewType == viewType)
>                 rva000592B8(playing->m_event.get());
>         }
>     }
>     for (QueuedAudioEvents::iterator event = m_queuedEvents[viewType].begin(), queuedEnd = m_queuedEvents[viewType].end(); event != queuedEnd; ++event) {
>         if (reinterpret_cast<const StringBase<char> *>(&eventName)->isEmpty()
>             || reinterpret_cast<const BfmeAudioEventInfoNameView *>(event->m_info)->getEventName() == eventName)
>             rva000592B8(playing->m_event.get());
#endif
