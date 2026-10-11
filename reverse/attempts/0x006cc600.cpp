// ?Rva006CC600@@YAXPBDPAD@Z
// partial score=0.95 date=2026-10-11
// V2 shape (LK7 r4, 2026-10-11): 290/305B vs retail 0x006CC600.
// Compiles in Code/Libraries/Source/Apt/Apt.cpp (needs its EAStringC view +
// copy-ctor/rva006D30D0 decls, AptLinker::Load decl, g_bfmeAptImportAtE176FC
// define, tickAssert + g_bfmeAptInitAtE17700). All callees bound to rowed names.
// Residues: (1) [E-20] dword pair ([esp+4]=0 pre-assert, =1 pre-cmp; EH/home
// traffic with no source found after bool/int/BOOL/extra-scope/volatile probes);
// (2) C-string load [esp+0x24] (frame math forces [E+4]=retaddr; paradox open);
// (3) prolog order (mov-fs-first vs retail push-first, same bytes).
// See findings.log LK7-06:40/07:xx entries for the full slot map + disassembly.
// ?Rva006CC600@@YAXPBDPAD@Z @0x006CC600 305B: Apt.cpp's import-target guard
// (the assert file/lines 802/805 name it): refuse a target suffix of
// "#import", then forward (target,suffix) to the linker Load at rowed
// 0x006D1F80. All callees rowed (EAStringC 6D4C80/6D3010/6D2FC0/6D30D0).
extern unsigned char g_bfmeAptImportAtE176FC;
unsigned char g_bfmeAptImportAtE176FC;
void Rva006CC600(const char *path,char *suffix)
{
 tickAssert(g_bfmeAptInitAtE17700,"bInitialized","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x322);
 EAStringC target(path);
 bool isImport;
 {
  EAStringC import("#import");
  isImport = !target.rva006D30D0(&import);
 }
 if (isImport) {
  g_bfmeAptAssertAtE17734("sTarget != AptNativeString(\"#import\") && \"Please use AptPreloadFile instead of a target of '#import' now.\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x325);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 g_bfmeAptImportAtE176FC = 0;
 g_bfmeAptLinkerAtE176F8->Load(EAStringC(target),EAStringC(suffix));
}
