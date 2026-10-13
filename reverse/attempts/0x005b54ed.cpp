// ?rva005B54ED@Rva005B566B@@QAEXII_N@Z
// partial score=0.985 date=2026-10-13
// ?rva005B54ED@Rva005B566B@@QAEXII_N@Z
// partial score=0.985 date=2026-10-13
// Retail 0x005B54ED (382B). Owner-embedded port in Rva005B5485.cpp compiles
// 379B (-3B). Prologue reserves 1 home, retail 2 (image/text/key/key2 homes
// permuted across [-0x10]/[-0x14]/[+0x10]/[+0x8]). Text-direct passing helped
// (385->381 in scratch). Untried: (void)image liveness anchor to force
// separate image/text homes; major-edi already matches. Second-block key
// reuses major home [+0x8] in retail, image home [-0x10] in mine.
// Infra KEPT in Rva005B5485.cpp (build-green): manager method decls,
// helper views, Rva005B566B class. Method reverted below.
// t=25 model=muse-spark
// ?rva005B54ED@Rva005B566B@@QAEXII_N@Z @0x005B54ED (382B): hero select with
// per-type icons plus class/type description texts (WB SetCurrentHero branch
// structure; address name kept). Evidence: WB 0x157C3E0 + retail 382B; the
// second description passes fetchLabel directly like the first.
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
        AsciiString key("APT:CahTypeDescription");
        g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetchLabel(TheCreateAHeroManager->GetSubClassDescTag(major, minor)), true);
    }
}
