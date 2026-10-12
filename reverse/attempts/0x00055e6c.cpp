// ?rva00055E6C@MilesAudioManager@@QAE_NABVAsciiString@@HHH@Z
// partial score=0.99 date=2026-10-12
// ?rva00055E6C@MilesAudioManager@@QAE_NABVAsciiString@@HHH@Z
// builds inside Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 0x00055E6C (350 bytes): whether a music stream or stacked music of
// the view type already plays the named event and passes the stream
// predicate 0xA8B59. Playing streams must also match the music system.
static __forceinline bool rva00055E6CNameMatches(AudioEventRTS *event, const AsciiString &name)
{
    const AsciiString *eventName = reinterpret_cast<const AsciiString *>(reinterpret_cast<Rva002D9AC3 *>(event)->rva002D9AC3());
    return eventName->compare(name) == 0;
}

bool MilesAudioManager::rva00055E6C(const AsciiString &name, int streamArg, int viewType, int musicSystem)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    for (PlayingAudioList::iterator it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing.get() && playing->m_event->m_info->m_atB0 == 0 && playing->m_event->m_viewType == viewType
            && playing->m_event->m_musicSystem == musicSystem
            && rva00055E6CNameMatches(playing->m_event.get(), name)
            && reinterpret_cast<Rva000A8B59 *>(&playing->m_at0C)->rva000A8B59(streamArg))
            return true;
    }
    MusicStack &stack = m_musicStack[viewType][musicSystem];
    for (MusicStack::iterator music = stack.begin(); music != stack.end(); ++music) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*music);
        if (playing.get() && playing->m_event->m_info->m_atB0 == 0 && playing->m_event->m_viewType == viewType
            && rva00055E6CNameMatches(playing->m_event.get(), name)
            && reinterpret_cast<Rva000A8B59 *>(&playing->m_at0C)->rva000A8B59(streamArg))
            return true;
    }
    return false;
}

