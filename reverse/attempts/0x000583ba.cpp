// ?rva000583BA@MilesAudioManager@@QAEXIIH@Z
// partial score=0.97 date=2026-10-12
// ?rva000583BA@MilesAudioManager@@QAEXIIH@Z
// partial score=0.97 date=2026-10-12
// Apply to MilesAudioManager.cpp: replace `char at694[0x698 - 0x694];` with
// `unsigned int m_at694;` (+0x694), declare
// `void rva000583BA(unsigned int affect, unsigned int viewMask, int arg);`
// after rva00060309, and add the body below (placed before 0x000606CE).
// Current master (visible PlayingAudioRef::operator= lever, the one that
// closed 0x000603ED) now keeps the ref in EDI and releases it without a
// reload as retail does: 467 vs 471 bytes. The only residue is loops 1 and 2
// (sounds, 3D sounds): retail loads the view type into EAX then MOV ECX,EAX
// before SHL; cl loads it straight into ECX (2 bytes each). The streams loop
// matches. Tried: operand order, 1U, (int) cast, >>&1, an inline
// viewTypeInMask(mask,type) helper; all keep the direct ECX load.
// Native 000583BA..00058591. Under the mutex, pauses every sound (affect bit
// 0x02), 3D sound (0x04) and stream whose class meets affect in the view
// types of viewMask: bit 0x20 marks the playing audio at +0x4A, otherwise
// +0x49, then pauseResumeSound applies it. Music (0x10) records the views
// at +0x694/+0x690, pending requests are flagged through 0x577E3, and
// unless arg is set the per-view masks at +0x6C0/+0x6B4 remember affect.
void MilesAudioManager::rva000583BA(unsigned int affect, unsigned int viewMask, int arg)
{
    MilesMutexGuard guard(&m_mutex, 0);
    PlayingAudioRef playing;
    PlayingAudioList::iterator it;
    if (affect & 0x02) {
        for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
            playing = *it;
            if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))) {
                if (affect & 0x20)
                    playing->m_at4A = true;
                else
                    playing->m_at49 = true;
                pauseResumeSound(playing);
            }
        }
    }
    if (affect & 0x04) {
        for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it) {
            playing = *it;
            if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))) {
                if (affect & 0x20)
                    playing->m_at4A = true;
                else
                    playing->m_at49 = true;
                pauseResumeSound(playing);
            }
        }
    }
    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing.get() && (viewMask & (1 << playing->m_event->m_viewType))
            && (playing->m_event->getSoundClass() & affect)) {
            if (affect & 0x20)
                playing->m_at4A = true;
            else
                playing->m_at49 = true;
            pauseResumeSound(playing);
        }
    }
    if (affect & 0x10) {
        if (affect & 0x20)
            m_at694 |= viewMask;
        else
            m_at690 |= viewMask;
    }
    rva000577E3(affect, viewMask, true);
    if (!arg) {
        for (int viewType = 0; viewType < 3; ++viewType) {
            if (viewMask & (1 << viewType)) {
                if (affect & 0x20)
                    m_at6C0[viewType] |= affect & ~0x20;
                else
                    m_at6B4[viewType] |= affect;
            }
        }
    }
}


