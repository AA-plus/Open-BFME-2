// ?rva005B54ED@Rva005B566B@@QAEXII_N@Z
// partial score=0.985 date=2026-10-13
// ?rva005B54ED@Rva005B566B@@QAEXII_N@Z
// partial score=0.985 date=2026-10-13
// Retail 0x005B54ED (382B). True home AptCreateAHeroClass.cpp (rowed sibling
// rva005B566B, /O1 flags) compiles 381B (-1B, was 379B in wrong TU).
// Remaining wall: prologue reserves 1 home, retail 2 (image/text/key/key2
// homes permuted; text-direct passing helped 385->381). True home confirmed
// by rowed sibling idioms. Infra KEPT (manager/view/class ext, green).
// t=30 model=muse-spark
// ?rva005B54ED@Rva005B566B@@QAEXII_N@Z @0x005B54ED (382B): hero select with
// per-type icons plus class/type description texts. Evidence: WB 0x157C3E0
// branch structure + retail 382B; loop and description idioms shared with
// the rowed rva005B566B above; both descriptions pass fetchLabel directly.
void Rva005B566B::rva005B54ED(unsigned major, unsigned minor, bool animate)
{
    CreateAHeroData *hero = reinterpret_cast<Rva0040A3D2 *>(&heroes)->rva0040A3D2(major, minor);
    if (!hero)
        return;
    screen->hero.rva005B21DA(hero, true, animate ? 1 : 0);
    unsigned count = TheCreateAHeroManager->rva00219D52(major);
    for (unsigned i = 0; i < count; ++i) {
        const AsciiString &image = TheCreateAHeroManager->GetButtonImageName(major, i);
        AsciiString key;
        key.format("Cah::TypeIcon%d", i);
        reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager)->rva002239FA(key, image);
    }
    {
        AsciiString key("APT:CahClassDescription");
        g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetchLabel(TheCreateAHeroManager->GetClassDescTag(major)), true);
    }
    {
        AsciiString key = "APT:CahTypeDescription";
        g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetchLabel(TheCreateAHeroManager->GetSubClassDescTag(major, minor)), true);
    }
}
