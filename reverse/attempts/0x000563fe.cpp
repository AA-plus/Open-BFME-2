// ?rva000563FE@MilesAudioManager@@QAEXPAVXfer@@H@Z
// partial score=0.98 date=2026-10-12
// ?rva000563FE@MilesAudioManager@@QAEXPAVXfer@@H@Z
// Bank for 0x000563FE (194 B, RET 8; WB twin 0x0079AA60) in
// Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp.
// Needs in that unit: AudioEventRTS +0x2C as `float m_at2C` (split at18),
// the member declaration `void rva000563FE(Xfer *xfer, int handle);`, and
// `class Rva002D9FD9Arg; class Rva002D9FD9Owner { public: void
// rva002D9FD9(Rva002D9FD9Arg *xfer); };`. Compiles to 198 B: every call,
// branch and the float/volume handling match; the one wall is the playing
// reference: retail loads it into EDI right after the 0x55FCA lookup and
// tests and finally releases it from EDI, while cl keeps the EH-tracked
// holder in memory (reloads through EAX, releases from [ebp-0x10]). The
// event pointer (a scalar local whose address is also passed) does stay in
// ESI. Tried: PlayingAudioRef, a public-field holder, a holder without a
// constructor, a scalar copy right after the lookup (197 B, stages ECX->EDI
// and still releases from memory), an inline pointer-typed lookup wrapper
// and retyping 0x55FCA's third parameter as PlayingAudioRef* (no change).
// Retail 0x000563FE (address-derived, RET 8; WorldBuilder twin 0x0079AA60):
// xfers one logical handle's event. The event and its playing record come
// from the 0x55FCA lookup; it counts as present only when found, not
// flagged at +0x4C and not finished (+0x44). After the present flag, a
// present event is xferred with the record's pending extra volume applied
// when one is set (+0x40 > 0), then its own volume is put back.
void MilesAudioManager::rva000563FE(Xfer *xfer, int handle)
{
    PlayingAudioRef playing;
    AudioEventRTS *event;
    bool present = rva00055FCA(handle, reinterpret_cast<void **>(&event), reinterpret_cast<int>(&playing));
    if (present) {
        if (event == 0)
            present = false;
        else if (event->m_at4C)
            present = false;
        if (playing.get() != 0 && playing->m_at44)
            present = false;
    }
    xfer->xferBool(&present);
    if (present) {
        float volume = event->m_at2C;
        if (playing.get() != 0 && playing->m_at40 > 0.0f)
            reinterpret_cast<Rva00481FAFFloatSlot *>(event)->store(playing->m_at3C);
        reinterpret_cast<Rva002D9FD9Owner *>(event)->rva002D9FD9(reinterpret_cast<Rva002D9FD9Arg *>(xfer));
        reinterpret_cast<Rva00481FAFFloatSlot *>(event)->store(volume);
    }
}
