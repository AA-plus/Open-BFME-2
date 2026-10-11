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

// --- 2026-10-11 LK8r4 appendix (independent convergence; yielding to LK7) ---
// LK8 rebuilt a V1 shape from retail bytes and confirms LK7's residues (1)
// and (3): the [esp0-20] dword (writes 0, 1, esp; never read) is real and is
// the only frame delta vs a natural /O2 lowering. Firm additions: (a) all
// four small callees are callee-cleanup (ctor/copy/!= ret4, proven from
// their epilogs), so frame math must model ret4 (else slots drift); with it,
// ctor1 reads [esp0+8] = the SECOND C arg (suffix) and ctor3 reads [esp0+4]
// = the FIRST (path), resolving LK7 residue (2): sTarget is the suffix, the
// path temp reuses sImport's dead slot; (b) Load@0x6D1F80 ends ret8 (two
// pointer args); the copy sources &sTarget and the pushed Load arg is
// &pathTemp, i.e. the by-value Load param is FIRST despite the (ref,val)
// header guess. LK8 banked a 0.45->0.7 partial under these findings, reverted
// its Code/ shape, and leaves the last 15B to LK7's lane (no competing
// claim). Honest open item stays the [esp0-20] dword idiom.
