// ?removePlayingAudio@MilesAudioManager@@UAEXABVAsciiString@@H@Z
// partial score=0.99 date=2026-10-11
// ?removePlayingAudio@MilesAudioManager@@UAEXABVAsciiString@@H@Z
// partial score=0.99 date=2026-10-11 (round 5)
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Append to Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// at master e08dd83e34 (BfmeAudioEventInfoNameView, Rva000554A9 and
// BfmeStringTailRecord144::m_info are already declared there). Measured:
// 876B == retail 876B; all bytes equal except 3 instructions in the music
// stack loop's viewType test (retail: mov eax,[esi+0x1c]; mov ecx,[ebp+0xc];
// cmp [eax+0x30],ecx -- ours reuses the dying audio register esi:
// mov esi,[esi+0x1c]; mov eax,[ebp+0xc]; cmp [esi+0x30],eax).
// Closed this round: queued sweep through m_queuedEvents[viewType] directly
// (no reference; cl then folds &_M_finish to (viewType+0x13)*0xC and parks
// &queued in the dead viewType slot, as retail) which also fixed the music
// loop's peeled first compare and ecx/eax; `pending` initialised at its
// declaration (begin() writes it in place).
// Tried without effect on the residue: a separate `track` local, playing.get()
// everywhere, inline bfmeSameEvent helper, inverted/nested conditions, a
// remove flag, viewType == ... order, stack pointer / row pointer forms,
// reinterpret_cast reference copy of *music.

static __forceinline const AsciiString &bfmeEventName(const AudioEventInfo *info)
{
    return reinterpret_cast<const BfmeAudioEventInfoNameView *>(info)->getEventName();
}

void MilesAudioManager::removePlayingAudio(const AsciiString &eventName, int viewType)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    PlayingAudio *audio;
    OpaqueRefList::iterator it;

    it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
        } else {
            ++it;
        }
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
        } else {
            ++it;
        }
    }
    it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingStreams).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        audio = playing.get();
        if (audio && bfmeEventName(audio->m_event->m_info) == eventName
            && audio->m_event->m_viewType == viewType) {
            releaseMilesHandles(*audio);
            it = reinterpret_cast<OpaqueRefList &>(m_playingStreams).erase(it);
        } else {
            ++it;
        }
    }

    for (int musicSystem = 0; musicSystem < 2; ++musicSystem) {
        MusicStack &stack = m_musicStack[viewType][musicSystem];
        MusicStack::iterator music = stack.begin();
        while (music != stack.end()) {
            playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
            audio = playing.get();
            if (audio && bfmeEventName(audio->m_event->m_info) == eventName
                && audio->m_event->m_viewType == viewType) {
                music = stack.erase(music);
            } else {
                ++music;
            }
        }
    }

    QueuedAudioEvents::iterator event = m_queuedEvents[viewType].begin();
    while (event != m_queuedEvents[viewType].end()) {
        if (bfmeEventName(event->m_info) == eventName) {
            unmapPhysicalHandle(event->m_playingHandle);
            event = (QueuedAudioEvents::iterator)reinterpret_cast<Rva000554A9 &>(m_queuedEvents[viewType]).rva000554A9(event);

        } else {
            ++event;
        }
    }

    Rva00051107AudioRequestSet::iterator pending = m_requestSet.begin();

    while (pending != m_requestSet.end()) {
        if ((*pending)->m_pendingEvent.get()
            && bfmeEventName((*pending)->m_pendingEvent->m_info) == eventName) {
            Rva00051107AudioRequestSet::iterator doomed = pending;
            ++pending;
            Rva00051107AudioRequest *request = *doomed;
            reinterpret_cast<Rva00051B89KeyedSet &>(m_requestSet).erase(
                reinterpret_cast<Rva00051B89KeyedSet::iterator &>(doomed));
            deleteAudioRequest(request);
        } else {
            ++pending;
        }
    }

    Rva00051107AudioRequestList::iterator request = m_audioRequests.begin();
    while (request != m_audioRequests.end()) {
        if ((*request)->m_request == 0 && (*request)->m_pendingEvent.get()
            && bfmeEventName((*request)->m_pendingEvent->m_info) == eventName) {
            request = m_audioRequests.erase(request);
        } else {
            ++request;
        }
    }
}
