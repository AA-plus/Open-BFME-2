// ?processPlayingList@MilesAudioManager@@QAEXPAVRva00052B3D@@@Z
// partial score=0.9 date=2026-10-12
// Banked 0x5C23C MilesAudioManager::processPlayingList attempt (TU: Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp,
// git diff of the TU in the attempt also added: PlayingAudio bool m_at47 (+0x47), m_at4C (+0x4C); AudioEventInfo float m_at1C;
// vtable slot108(AudioEventRTS*) bool / slot109 float; GlobalVolumeData::rva000520F4(const AudioEventInfoRef&, int);
// class Rva002DA318 { bool rva002DA318(); }; extern const float BfmeZeroRange; decls processFade(PlayingAudioRef&) (0x53448, banked).

class Rva000535CC
{
public:
    void rva000535CC(void *p);
private:
    char at00[0x10];
    AudioSettings *m_audioSettings;
    char at14[0x6AC - 0x14];
    bool m_at6AC;
    char at6AD[0x6B0 - 0x6AD];
    int m_at6B0;
};

void Rva000535CC::rva000535CC(void *p)
{
    if ((*(PlayingAudio **)p)->m_at4C == 0)
        return;
    if (m_at6AC != 0)
        return;
    (*(PlayingAudio **)p)->m_at4C = 0;
    if (m_at6B0 != 0)
        return;
    (*(PlayingAudio **)p)->m_at45 = 1;
    (*(PlayingAudio **)p)->m_at30 = (float)m_audioSettings->m_at78;
}

// Retail 0x00052F1E: an event stays audible below the settings' +0xB8
// cutoff when its info's type bit 3 is set, its priority is 4 or its +0x1C
// reaches the cutoff.
bool MilesAudioManager::rva00052F1E(void *event)
{
    AudioEventRTS *e = (AudioEventRTS *)event;
    if ((e->m_info->m_type & 8) || e->m_info->m_priority == 4 || e->m_info->m_at1C >= m_audioSettings->m_atB8)
        return true;
    return false;
}


extern const float BfmeZeroRange;  // data-ledger zero at VA 0x00BBAEAC

// Retail 0x0005C23C (WorldBuilder twin 0x007A14A0, unnamed; Zero Hour's
// processPlayingList is the semantic guide): every playing 2D sound, 3D
// sound and stream applies pending pauses, fades and volume changes and
// leaves its list once stopped or finished; the 3D pass also moves its
// sample. The first two music streams of the current view type are handed
// back in streams, the rest of it filled with the stream list's end.
void MilesAudioManager::processPlayingList(Rva00052B3D *streams)
{
    PlayingAudioRef playing;
    OpaqueRefList::iterator it;

    it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playingSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        PlayingAudio *audio = playing.get();
        if (!audio) {
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
            continue;
        }
        if (m_at6A5 || (audio->m_at4C && !m_at6AC)) {
            ((Rva000535CC *)this)->rva000535CC(&playing);
            rva000535A6(playing);
            pauseResumeSound(playing);
        }
        if (((Rva002DA318 *)audio->m_event.operator->())->rva002DA318())
            audio->m_event->m_at4C = true;
        if (audio->m_event->m_at4C && (audio->m_event->m_info->m_control & 0x10))
            audio->m_at44 = true;
        bool fading = processFade(playing);
        bool done = audio->m_at30 >= (float)m_audioSettings->m_at78 && !audio->m_at45 && !audio->m_at47;
        if (done && audio->m_at48) {
            if (audio->m_event->hasMoreLoops())
                rva0005AA72(playing);
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
        } else if (audio->m_status == 1 || done) {
            AIL_stop_sample(get2DSampleHandleForPlayingAudio(&playing));
            it = reinterpret_cast<OpaqueRefList &>(m_playingSounds).erase(it);
        } else {
            if (reinterpret_cast<GlobalVolumeData *>(m_volumeData[audio->m_event->m_viewType])->rva000520F4(*reinterpret_cast<const AudioEventInfoRef *>(&audio->m_event->m_info), 0)
                || m_at6A5 || fading || audio->m_at4F)
                adjustPlayingVolume(&playing);
            if (m_at6A8)
                rva00052FA0(playing);
            ++it;
        }
    }

    it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).begin();
    while (it != reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        PlayingAudio *audio = playing.get();
        if (!audio) {
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
            continue;
        }
        if (m_at6A5 || (audio->m_at4C && !m_at6AC)) {
            ((Rva000535CC *)this)->rva000535CC(&playing);
            rva000535A6(playing);
            pauseResumeSound(playing);
        }
        if (((Rva002DA318 *)audio->m_event.operator->())->rva002DA318())
            audio->m_event->m_at4C = true;
        if (audio->m_event->m_at4C && (audio->m_event->m_info->m_control & 0x10))
            audio->m_at44 = true;
        processFade(playing);
        bool done = audio->m_at30 >= (float)m_audioSettings->m_at78 && !audio->m_at45 && !audio->m_at47;
        void *sample3D = get3DSampleHandleForPlayingAudio(playing);
        if (done && audio->m_at48) {
            if (audio->m_event->hasMoreLoops())
                rva0005AA72(playing);
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
        } else if (audio->m_status == 1 || done) {
            if (sample3D)
                AIL_stop_3D_sample(sample3D);
            it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
        } else if (!sample3D) {
            ++it;
        } else {
            bool valid;
            BfmeEventPositionView pos = Rva0005160FGet(audio->m_event.operator->(), valid);
            if (valid) {
            if (slot108(audio->m_event.operator->())) {
                audio->m_at46 = true;
                audio->m_at47 = false;
            } else if (audio->m_at46) {
                audio->m_at46 = false;
                audio->m_at47 = true;
            }
            float volume = rva0005A9F8(&playing, 0, 0);
            AudioEventRTS *event = audio->m_event.operator->();
            bool audible = rva00052F1E(event);
            if (m_audioSettings->m_atB8 > volume && !audible) {
                if (event->hasMoreLoops())
                    rva0005AA72(playing);
                AIL_register_3D_EOS_callback(sample3D, 0);
                it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
                continue;
            }
            setOcclusionLevels(playing, &pos);
            bool retest = false;
            if (m_at6A9 && audio->m_event->m_info->m_reverbWetLevel > BfmeZeroRange)
                rva00055C5D(playing, &retest);
            if (m_at6A8 || retest)
                rva00052FA0(playing);
            float level = rva0005A9F8(&playing, 1, 1);
            AIL_set_3D_position(sample3D, pos.x, pos.y, -pos.z);
            AIL_set_3D_sample_volume(sample3D, level);
            ++it;
            } else {
                if (audio->m_event->hasMoreLoops())
                    rva0005AA72(playing);
                AIL_register_3D_EOS_callback(sample3D, 0);
                it = reinterpret_cast<OpaqueRefList &>(m_playing3DSounds).erase(it);
            }
        }
    }

    OpaqueRefList::iterator *found = reinterpret_cast<OpaqueRefList::iterator *>(streams);
    int count = 0;
    OpaqueRefList &list = reinterpret_cast<OpaqueRefList &>(m_playingStreams);
    it = list.begin();
    while (it != list.end()) {
        playing = *reinterpret_cast<const PlayingAudioRef *>(&*it);
        PlayingAudio *audio = playing.get();
        if (!audio) {
            it = list.erase(it);
            continue;
        }
        if (m_at6A5 || (audio->m_at4C && !m_at6AC)) {
            ((Rva000535CC *)this)->rva000535CC(&playing);
            rva000535A6(playing);
            pauseResumeSound(playing);
        }
        if (((Rva002DA318 *)audio->m_event.operator->())->rva002DA318())
            audio->m_event->m_at4C = true;
        if (audio->m_event->m_info->m_atB0 == 3) {
            if (audio->m_event->m_viewType == m_at678)
                found[count++] = it;
            ++it;
            continue;
        }
        if (audio->m_event->m_at4C) {
            if (audio->m_event->m_info->m_control & 0x10)
                audio->m_at44 = true;
            else
                audio->m_status = 1;
        }
        bool fading = processFade(playing);
        bool done = audio->m_at30 >= (float)m_audioSettings->m_at78 && !audio->m_at45 && !audio->m_at47;
        if (done && audio->m_at48) {
            if (audio->m_event->hasMoreLoops())
                rva0005AA72(playing);
            ((MilesStreamRef *)&audio->m_at0C)->rva000A8AC0();
            it = list.erase(it);
        } else if (audio->m_status == 1 || done) {
            ((MilesStreamRef *)&audio->m_at0C)->rva000A8AC0();
            it = list.erase(it);
        } else {
            if (m_at6A8)
                rva00052FA0(playing);
            if (reinterpret_cast<GlobalVolumeData *>(m_volumeData[audio->m_event->m_viewType])->rva000520F4(*reinterpret_cast<const AudioEventInfoRef *>(&audio->m_event->m_info), 0)
                || fading || m_at6A5 || audio->m_at4F)
                adjustPlayingVolume(&playing);
            ++it;
        }
    }
    for (; count < 2; ++count)
        found[count] = list.end();
}
